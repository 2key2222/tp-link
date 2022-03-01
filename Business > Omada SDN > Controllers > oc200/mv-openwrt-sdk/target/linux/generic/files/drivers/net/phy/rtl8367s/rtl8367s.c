#include <linux/if.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/if_ether.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/netlink.h>
#include <linux/bitops.h>
#include <net/genetlink.h>
#include <linux/switch.h>
#include <linux/delay.h>
#include <linux/phy.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/lockdep.h>
#include <linux/workqueue.h>
#include <linux/platform_device.h>
#include <linux/leds.h>
#include <linux/interrupt.h>
#include <linux/if_vlan.h>
#include <linux/rtnetlink.h>
#include <linux/proc_fs.h>
#include "rtl8367s.h"
#include "rtl8367s_api.h"

#ifdef CONFIG_OF
#include <linux/of.h>
#endif

#define DBGINFO(fmt, ...) printk("#####################%s(%d): " fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
//#define DBGINFO(fmt, args...)

#define RTL8367S_MAX_VLANS      4095
#define RTL8367S_MAX_PORTS      8
#define RTL8367S_PORT_CPU       6

#define SWITCH_WORK_DELAY (100)

struct rtl8367s_priv {
        struct switch_dev dev;
        struct phy_device *phy;
        const struct net_device_ops *ndo_old;
        struct net_device_ops ndo;
        char buf[4096];

        bool mii_lo_first;

        /* all fields below are cleared on reset */
        u16 vlan_id[RTL8367S_MAX_VLANS];
        u8 vlan_table[RTL8367S_MAX_VLANS];
        u8 vlan_tagged[RTL8367S_MAX_VLANS];
        u16 pvid[RTL8367S_MAX_PORTS];
        int vlan_changed;

        /* if set, the vlan interface is UP */
        u8 vlan_status[RTL8367S_MAX_VLANS];
        struct net_device *vlan_dev[RTL8367S_MAX_VLANS];
        u32 old_port_status;
        struct delayed_work switch_work;
};

#define to_rtl8367s(_dev) container_of(_dev, struct rtl8367s_priv, dev)

u32 rtl8367s_reg_read(struct mii_bus *mii, u32 reg)
{
        u32 val;
        ret_t ret;

        ret = rtk_switch_getReg(reg, &val);
        if (ret != RT_ERR_OK) {
                DBGINFO("can not get value of reg[%x]", reg);
                return 0xffffffff;
        }

        DBGINFO("reg = %x, value=%x", reg, val);
        return val;
}

u32 rtl8367s_reg_write(struct mii_bus *mii, u32 reg, u32 val)
{
        ret_t ret;

        ret = rtk_switch_setReg(reg, val);
        if (ret != RT_ERR_OK) {
                DBGINFO("can not write val[%d] to reg[%x]", val, reg);
                return -1;
        }

        DBGINFO("write val[%d] to reg[%x]", val, reg);
        return 0;
}

/*
 * change power down or up phy in vlan ports when vlan net device down or up, only
 * work when vlan netdevice down or up
 *
 * @phydev: phy_device for rtl8367s_priv
 * @vid: vlan id
 * @linkup: up or down phylink
 *
 * attention: in rtl8367s switchs, port 0 connected to phy 0, port1 connected
 * to phy1, etc... port 6 has no phy connected.
 */
int rtl8367s_change_vlan_phylink(struct phy_device *phydev, int vid, bool linkup)
{
        int i = 0;
        u8 ports = 0;
        u32 phy_ctl = 0x0;
        const u32 phy_ctl_reg_base = 0x2000;
        struct rtl8367s_priv *priv = phydev->priv;
        u32 reg_ctl = 0x0;

        ports = priv->vlan_table[vid];
        for (i = 0; i < priv->dev.ports; i++) {
                const int max_port_num = 5;

                /* only port 0,1,2,3,4 corresponding phy */
                if (i >= max_port_num)
                        continue;

                /* port in vlan and not a tag port */
                if (!(ports & (1 << i)) || priv->vlan_tagged[vid] & (1 << i))
                        continue;

                /* Phy ctrl register, each phy ctrl offset range from 0x00 - 0x1f,
                 *      size 32(1 << 5).
                 * e.g. phy0: 0x2000(0x00 ~ 0x1f)
                 *      phy0: 0x2000(0x20 ~ 0x3f)
                 */
                reg_ctl = phy_ctl_reg_base + (i << 5) + MII_BMCR;
                rtk_switch_getReg(reg_ctl, &phy_ctl);

                if (linkup)
                        rtk_switch_setReg(reg_ctl, phy_ctl & ~BMCR_PDOWN);
                else
                        rtk_switch_setReg(reg_ctl, phy_ctl | BMCR_PDOWN);
        }

        return 0;
}

static void
rtl8367s_vtu_load_vlan(struct rtl8367s_priv *priv, u32 vid, u32 port_mask)
{
        rtk_vlan_cfg_t vlan;
        int i;
        rtk_port_t logicalPort;

        DBGINFO("vid=%d, port_mask=%x, tag=%x", vid, port_mask, priv->vlan_tagged[vid]);

        memset(&vlan, 0x00, sizeof(rtk_vlan_cfg_t));
        for (i = 0; i < RTL8367S_MAX_PORTS; i++) {
                logicalPort = rtk_switch_port_P2L_get(i);
                if (port_mask & BIT(i)) {
                        RTK_PORTMASK_PORT_SET(vlan.mbr, logicalPort);

                        if ((priv->vlan_tagged[vid] & BIT(i)) == 0) {
                                RTK_PORTMASK_PORT_SET(vlan.untag, logicalPort);
                        }
                }
        }

        vlan.ivl_en = ENABLED;

        rtk_vlan_set(vid, &vlan);

        for (i = 0; i < RTL8367S_MAX_PORTS; i++) {
                logicalPort = rtk_switch_port_P2L_get(i);
        if (UNDEFINE_PORT == logicalPort)
        {
            continue;
        }

        rtk_vlan_portPvid_set(logicalPort, priv->pvid[i], 0);
        DBGINFO("set pvid, lport=%d, vid=%d", logicalPort, priv->pvid[i]);
        }
}

static int
rtl8367s_sw_set_reg_val(struct switch_dev *dev, int reg, int val)
{
        rtk_switch_setReg(reg, val);
        return 0;
};

static int
rtl8367s_sw_get_reg_val(struct switch_dev *dev, int reg, int *val)
{
        DBGINFO("start");
        rtk_switch_getReg(reg, val);
        return 0;
};

static int
rtl8367s_sw_get_phy_reg_val(struct switch_dev *dev, int phy_index, struct switch_val *val)
{
    struct rtl8367s_priv *priv = to_rtl8367s(dev);
    rtk_uint32 reg = 0;
    rtk_uint32 reg_val = 0;
    char *buf = priv->buf;
    int ret = 0;


    sscanf(val->value.s, "%x", &reg);

    ret = rtk_switch_getPHYReg(phy_index, reg, &reg_val);
        DBGINFO("phyNo = %d, register = %d, value = %x, ret = %d", phy_index, reg, reg_val, ret);

    val->len = snprintf(buf, sizeof(priv->buf), "%x", reg_val);
    val->value.s = buf;

    return 0;
}

static int
rtl8367s_sw_set_phy_reg_val(struct switch_dev *dev, int phy_index, struct switch_val *val)
{
    rtk_uint32 reg = 0;
    rtk_uint32 reg_val = 0;

    sscanf(val->value.s, "%x-%x", &reg, &reg_val);
        DBGINFO("phyNo = %d, register = %d, value = %x", phy_index, reg, reg_val);

    return rtk_switch_setPHYReg(phy_index, reg, reg_val);
}

static int
rtl8367s_sw_set_pvid(struct switch_dev *dev, int port, int vlan)
{
        struct rtl8367s_priv *priv = to_rtl8367s(dev);

        DBGINFO("port=%d, vid=%d", port, vlan);

        /* make sure no invalid PVIDs get set */
        if (vlan >= dev->vlans)
                return -EINVAL;

        priv->pvid[port] = vlan;
        return 0;
}

static int
rtl8367s_sw_get_pvid(struct switch_dev *dev, int port, int *vlan)
{
        struct rtl8367s_priv *priv = to_rtl8367s(dev);
        DBGINFO("start");
        *vlan = priv->pvid[port];
        return 0;
}
//
static int
rtl8367s_sw_set_vid(struct switch_dev *dev, const struct switch_attr *attr,
                  struct switch_val *val)
{
        struct rtl8367s_priv *priv = to_rtl8367s(dev);
        DBGINFO("start");
        priv->vlan_id[val->port_vlan] = val->value.i;
        return 0;
}

static int
rtl8367s_sw_get_vid(struct switch_dev *dev, const struct switch_attr *attr,
                  struct switch_val *val)
{
        struct rtl8367s_priv *priv = to_rtl8367s(dev);
        DBGINFO("start");
        val->value.i = priv->vlan_id[val->port_vlan];
        return 0;
}

static int
rtl8367s_sw_get_port_link(struct switch_dev *dev, int port,
                        struct switch_port_link *link)
{
        rtk_port_mac_ability_t portStatus;
        rtk_port_t logicalPort;
        rtk_api_ret_t ret;

        logicalPort = rtk_switch_port_P2L_get(port);

        ret = rtk_port_macStatus_get(logicalPort, &portStatus);
        if (ret != RT_ERR_OK) {
        DBGINFO("rtk_port_macStatus_get failed");
                return -1;
        }

        link->link = !!portStatus.link;
        link->duplex = !!portStatus.duplex;
        link->aneg = !!portStatus.nway;
        link->tx_flow = !!portStatus.txpause;
        link->rx_flow = !!portStatus.rxpause;

        switch (portStatus.speed) {
        case PORT_SPEED_10M:
                link->speed = SWITCH_PORT_SPEED_10;
                break;
        case PORT_SPEED_100M:
                link->speed = SWITCH_PORT_SPEED_100;
                break;
        case PORT_SPEED_1000M:
                link->speed = SWITCH_PORT_SPEED_1000;
                break;
        default:
                link->speed = 0;
        }

        return 0;
}

static int
rtl8367s_sw_get_ports(struct switch_dev *dev, struct switch_val *val)
{
        struct rtl8367s_priv *priv = to_rtl8367s(dev);
        u8 ports = priv->vlan_table[val->port_vlan];
        int i;

        val->len = 0;
        for (i = 0; i < dev->ports; i++) {
                struct switch_port *p;

                if (!(ports & (1 << i)))
                        continue;

                p = &val->value.ports[val->len++];
                p->id = i;
                if (priv->vlan_tagged[val->port_vlan] & (1 << i))
                        p->flags = (1 << SWITCH_PORT_FLAG_TAGGED);
                else
                        p->flags = 0;
        }
        return 0;
}

static int
rtl8367s_sw_set_ports(struct switch_dev *dev, struct switch_val *val)
{
        struct rtl8367s_priv *priv = to_rtl8367s(dev);
        u8 *vt = &priv->vlan_table[val->port_vlan];
        int i, j;

        DBGINFO("vid=%d, len=%d", val->port_vlan, val->len);

        *vt = 0;
        for (i = 0; i < val->len; i++) {
                struct switch_port *p = &val->value.ports[i];
                if (p->flags & (1 << SWITCH_PORT_FLAG_TAGGED)) {
                        priv->vlan_tagged[val->port_vlan] |= (1 << p->id);
                } else {
                        priv->vlan_tagged[val->port_vlan] &= ~(1 << p->id);
                        /*priv->pvid[p->id] = val->port_vlan;*/

                        /* make sure that an untagged port does not
                         * appear in other vlans */
                        /*for (j = 0; j < RTL8367S_MAX_VLANS; j++) {
                                if (j == val->port_vlan)
                                        continue;
                                priv->vlan_table[j] &= ~(1 << p->id);
                        }*/
                }

                *vt |= 1 << p->id;
        }
        priv->vlan_changed = 1;
        return 0;
}

static int
rtl8367s_sw_hw_apply(struct switch_dev *dev)
{
        struct rtl8367s_priv *priv = to_rtl8367s(dev);
        u8 portmask[RTL8367S_MAX_PORTS];
        int i, j;

    DBGINFO("#######$$$*****apply_config**************\r\n");
        memset(portmask, 0, sizeof(portmask));

        /* calculate the port destination masks and load vlans
         * into the vlan translation unit */
        for (j = 0; j < RTL8367S_MAX_VLANS; j++) {
                u8 vp = priv->vlan_table[j];

                if (!vp)
                        continue;

                for (i = 0; i < dev->ports; i++) {
                        u8 mask = (1 << i);
                        if (vp & mask)
                                portmask[i] |= vp & ~mask;
                }

                rtl8367s_vtu_load_vlan(priv, j, priv->vlan_table[j]);
        }

        return 0;
}
//
static int
rtl8367s_sw_reset_switch(struct switch_dev *dev)
{
        int i = 0;
        u32 val = 0;

        DBGINFO("start");

        /* open smart speed down function, bit3 => 1000M->100M and bit5 => 100M->10M */
        for (i = UTP_PORT0; i <= UTP_PORT4; i++)
        {
                rtl8367c_getAsicPHYOCPReg(i, 0xa442, &val);
                rtl8367c_setAsicPHYOCPReg(i, 0xa442, val | (1 << 3) | (1 << 5));
        }
        return 0;
}

static int
rtl8367s_sw_get_port_mib(struct switch_dev *dev,
                       const struct switch_attr *attr,
                       struct switch_val *val)
{
        struct rtl8367s_priv *priv = to_rtl8367s(dev);
        int port;
        int len;
        char *buf = NULL;
        rtk_api_ret_t ret;
        rtk_port_t logicalPort;
        rtk_stat_port_cntr_t cntr;
    rtk_uint32 mibIndex = 0;
    rtk_uint32 *accessPtr = NULL;
    const rtk_uint16 mibLength[STAT_PORT_CNTR_END]= {
        2,1,1,1,1,1,1,1,1,
        2,1,1,1,1,1,1,1,1,1,1,
        2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    char *cntr_name[] = {
        "ifInOctets",
        "dot3StatsFCSErrors",
        "dot3StatsSymbolErrors",
        "dot3InPauseFrames",
        "dot3ControlInUnknownOpcodes",
        "etherStatsFragments",
        "etherStatsJabbers",
        "ifInUcastPkts",
        "etherStatsDropEvents",
        "etherStatsOctets",
        "etherStatsUndersizePkts",
        "etherStatsOversizePkts",
        "etherStatsPkts64Octets",
        "etherStatsPkts65to127Octets",
        "etherStatsPkts128to255Octets",
        "etherStatsPkts256to511Octets",
        "etherStatsPkts512to1023Octets",
        "etherStatsPkts1024toMaxOctets",
        "etherStatsMcastPkts",
        "etherStatsBcastPkts",
        "ifOutOctets",
        "dot3StatsSingleCollisionFrames",
        "dot3StatsMultipleCollisionFrames",
        "dot3StatsDeferredTransmissions",
        "dot3StatsLateCollisions",
        "etherStatsCollisions",
        "dot3StatsExcessiveCollisions",
        "dot3OutPauseFrames",
        "dot1dBasePortDelayExceededDiscards",
        "dot1dTpPortInDiscards",
        "ifOutUcastPkts",
        "ifOutMulticastPkts",
        "ifOutBrocastPkts",
        "outOampduPkts",
        "inOampduPkts",
        "pktgenPkts",
        "inMldChecksumError",
        "inIgmpChecksumError",
        "inMldSpecificQuery",
        "inMldGeneralQuery",
        "inIgmpSpecificQuery",
        "inIgmpGeneralQuery",
        "inMldLeaves",
        "inIgmpLeaves",
        "inIgmpJoinsSuccess",
        "inIgmpJoinsFail",
        "inMldJoinsSuccess",
        "inMldJoinsFail",
        "inReportSuppressionDrop",
        "inLeaveSuppressionDrop",
        "outIgmpReports",
        "outIgmpLeaves",
        "outIgmpGeneralQuery",
        "outIgmpSpecificQuery",
        "outMldReports",
        "outMldLeaves",
        "outMldGeneralQuery",
        "outMldSpecificQuery",
        "inKnownMulticastPkts",
        "ifInMulticastPkts",
        "ifInBroadcastPkts",
        "ifOutDiscards"};

        port = val->port_vlan;
        logicalPort = rtk_switch_port_P2L_get(port);
        DBGINFO("port = %d, logicalPort = %d", port, logicalPort);

    memset(&cntr, 0, sizeof(cntr));
    ret = rtk_stat_port_getAll(logicalPort, &cntr);
    DBGINFO("rtk_stat_port_getAll ret = %d", ret);

        len = 0;
        buf = priv->buf;
    
    memset(buf, 0, sizeof(priv->buf));
    len += snprintf(buf + len, sizeof(priv->buf) - len, 
                    "Port %d MIB counters\n", port);

    accessPtr = (rtk_uint32*)&cntr;
    for (mibIndex=0; mibIndex < STAT_PORT_CNTR_END; mibIndex ++)
    {
        if (2 == mibLength[mibIndex])
        {
            len += snprintf(buf + len, sizeof(priv->buf) - len, 
                            "%-36s: %llu\n",
                            cntr_name[mibIndex],
                            *(rtk_uint64*)accessPtr);
        }
        else if (1 == mibLength[mibIndex])
        {
            len += snprintf(buf + len, sizeof(priv->buf) - len, 
                            "%-36s: %u\n",
                            cntr_name[mibIndex],
                            *accessPtr);
        }
        else
        {
            DBGINFO("invalid mibLength");
        }


        accessPtr += mibLength[mibIndex];
    }

        val->value.s = buf;
        val->len = len;

        return 0;
}

static int
rtl8367s_sw_reset_port_mib(struct switch_dev *dev,
                           const struct switch_attr *attr,
                           struct switch_val *val)
{
        int port;
        rtk_port_t logicalPort;
    rtk_api_ret_t ret = 0;

        port = val->port_vlan;
        logicalPort = rtk_switch_port_P2L_get(port);

    ret = rtk_stat_port_reset(logicalPort);
    DBGINFO("rtk_stat_port_reset: port = %d, logicalPort = %d, ret = %d", port, logicalPort, ret);

    return 0;
}

static int
swconfig_set_port_mirrors(struct switch_dev *dev, const struct switch_attr *attr, struct switch_val *val)
{
    rtk_api_ret_t ret = 0;
    rtk_port_t port = val->port_vlan;
    rtk_port_t logicalPort = 0;
    rtk_portmask_t rx_portmask;
    rtk_portmask_t tx_portmask;
        struct switch_port *ports = val->value.ports;
        int i;

    if (port >= dev->ports)
    {
        printk("%s:%d: invalid port = %d, dev->ports = %d\r\n", __func__, __LINE__, port, dev->ports);
        return -EINVAL;
    }

        logicalPort = rtk_switch_port_P2L_get(port);

    /*rtk_mirror_portIso_set(1);*/
    RTK_PORTMASK_CLEAR(rx_portmask);
    RTK_PORTMASK_CLEAR(tx_portmask);

        for (i = 0; i < val->len; i ++) {
        DBGINFO("ports[%d].id = %d, flags = %x", i, ports[i].id, ports[i].flags);
                if (ports[i].id >= dev->ports || ports[i].id == port)
        {
            printk("%s:%d: invalid port = %d, dev->ports = %d, mirroring_port = %d\r\n", __func__, __LINE__, ports[i].id, dev->ports, port);
            return -EINVAL;
        }

                if (ports[i].flags & (1 << SWITCH_PORT_FLAG_TAGGED))
        {
            DBGINFO("Add port %d to tx portmask", ports[i].id);
            RTK_PORTMASK_PORT_SET(tx_portmask, rtk_switch_port_P2L_get(ports[i].id));
        }
        else
        {
            DBGINFO("Add port %d to rx portmask", ports[i].id);
            RTK_PORTMASK_PORT_SET(rx_portmask, rtk_switch_port_P2L_get(ports[i].id));
        }
        }

        ret = rtk_mirror_portBased_set(logicalPort, &rx_portmask, &tx_portmask);
    DBGINFO("rtk_mirror_portBased_set ret = %d", ret);

    return ret;
}

static int
swconfig_get_port_mirrors(struct switch_dev *dev, const struct switch_attr *attr, struct switch_val *val)
{
    rtk_api_ret_t ret = 0;
    rtk_port_t port = val->port_vlan;
    rtk_port_t logicalPort = 0;
    rtk_port_t tmpPort = 0;
    rtk_port_t mirroring_port = 0;
    rtk_portmask_t rx_portmask;
    rtk_portmask_t tx_portmask;
        struct switch_port *ports = val->value.ports;

    if (port >= dev->ports)
    {
        printk("%s:%d: invalid port = %d, dev->ports = %d\r\n", __func__, __LINE__, port, dev->ports);
        return -EINVAL;
    }

        logicalPort = rtk_switch_port_P2L_get(port);

    /*rtk_mirror_portIso_set(1);*/
    RTK_PORTMASK_CLEAR(rx_portmask);
    RTK_PORTMASK_CLEAR(tx_portmask);

        ret = rtk_mirror_portBased_get(&mirroring_port, &rx_portmask, &tx_portmask);
    DBGINFO("rtk_mirror_portBased_get ret = %d", ret);

    val->len = 0;
    if (RT_ERR_OK == ret && logicalPort == mirroring_port)
    {
        RTK_PORTMASK_SCAN(rx_portmask, tmpPort)
        {
            ports[val->len].id = rtk_switch_port_L2P_get(tmpPort);
            ports[val->len].flags = 0;
            val->len ++;
        }

        RTK_PORTMASK_SCAN(tx_portmask, tmpPort)
        {
            ports[val->len].id = rtk_switch_port_L2P_get(tmpPort);
            ports[val->len].flags = (1 << SWITCH_PORT_FLAG_TAGGED);
            val->len ++;
        }
    }

    return ret;
}

static struct switch_attr rtl8367s_port[] = {
        {
                .type = SWITCH_TYPE_NOVAL,
                .name = "reset_mib",
                .description = "Reset single port MIB counters",
                .set = rtl8367s_sw_reset_port_mib,
                .get = NULL,
        },
        {
                .type = SWITCH_TYPE_STRING,
                .name = "mib",
                .description = "Get port's MIB counters",
                .set = NULL,
                .get = rtl8367s_sw_get_port_mib,
        },
        {
                .type = SWITCH_TYPE_PORTS,
                .name = "mirrors",
                .description = "Port mirror",
                .set = swconfig_set_port_mirrors,
                .get = swconfig_get_port_mirrors,
        },
};

static struct switch_attr rtl8367s_vlan[] = {
        {
                .type = SWITCH_TYPE_INT,
                .name = "vid",
                .description = "VLAN ID (0-4094)",
                .set = rtl8367s_sw_set_vid,
                .get = rtl8367s_sw_get_vid,
                .max = 4094,
        },
};

static int
rtl8367s_sw_set_max_frame_size(struct switch_dev *dev, const struct switch_attr *attr,
                   struct switch_val *val)
{
        DBGINFO("start");
        return 0;
}

static int
rtl8367s_sw_get_max_frame_size(struct switch_dev *dev, const struct switch_attr *attr,
                   struct switch_val *val)
{
        DBGINFO("start");
        return 0;
}

static struct switch_attr rtl8367s_globals[] = {
        {
                .type = SWITCH_TYPE_INT,
                .name = "max_frame_size",
                .description = "Max frame size can be received and transmitted by mac",
                .set = rtl8367s_sw_set_max_frame_size,
                .get = rtl8367s_sw_get_max_frame_size,
                .max = 9018
        },
};

static const struct switch_dev_ops rtl8367s_sw_ops = {
        .attr_global = {
                .attr = rtl8367s_globals,
                .n_attr = ARRAY_SIZE(rtl8367s_globals),
        },
        .attr_port = {
                .attr = rtl8367s_port,
                .n_attr = ARRAY_SIZE(rtl8367s_port),
        },
        .attr_vlan = {
                .attr = rtl8367s_vlan,
                .n_attr = ARRAY_SIZE(rtl8367s_vlan),
        },
        .get_port_pvid = rtl8367s_sw_get_pvid,
        .set_port_pvid = rtl8367s_sw_set_pvid,
        .get_vlan_ports = rtl8367s_sw_get_ports,
        .set_vlan_ports = rtl8367s_sw_set_ports,
        .apply_config = rtl8367s_sw_hw_apply,
        .reset_switch = rtl8367s_sw_reset_switch,
        .get_port_link = rtl8367s_sw_get_port_link,
        /*.get_reg_val = rtl8367s_sw_get_reg_val,
        .set_reg_val = rtl8367s_sw_set_reg_val,
    .get_phy_reg_val = rtl8367s_sw_get_phy_reg_val,
    .set_phy_reg_val = rtl8367s_sw_set_phy_reg_val,*/
};

#ifdef CONFIG_SWCONFIG_LEDS

struct rtl8367s_led_data {
	struct led_classdev cdev;
	unsigned group;
	unsigned port;
	int active_low;
};

struct rtl8367s_led_priv {
	int lednum;
	struct rtl8367s_led_data leds_dat[];
};


struct rtl8367s_led {
	const char *name;
	unsigned group;
	unsigned port;
	int active_low;
};

struct rtl8367s_led_platform_data {
	int lednum;
	struct rtl8367s_led *leds;
};

static void rtl8367s_led_set(struct led_classdev *led_cdev,
	enum led_brightness value)
{
	/* real work for switch led */
	struct rtl8367s_led_data *led_dat = 
		container_of(led_cdev, struct rtl8367s_led_data, cdev);
	int level;

	if (value == LED_OFF)
		level = 0;
	else
		level = 1;

	if (led_dat->active_low)
		level = !level;

	rtl8367c_force_port_led(led_dat->group, led_dat->port, level);
}

static int rtl8367s_led_probe(struct platform_device *pdev)
{
	int i = 0;
	int ret;
	struct rtl8367s_led_platform_data *pdata = pdev->dev.platform_data;
	struct rtl8367s_led_priv *priv;

	priv = devm_kzalloc(&pdev->dev,
				sizeof(struct rtl8367s_led_priv) + pdata->lednum * sizeof(struct rtl8367s_led_data), GFP_KERNEL);
	priv->lednum = pdata->lednum;

	for (i = 0; i < pdata->lednum; i++) {
		priv->leds_dat[i].cdev.name = pdata->leds[i].name;
		priv->leds_dat[i].cdev.default_trigger = NULL;
		priv->leds_dat[i].cdev.brightness_set = rtl8367s_led_set;
		priv->leds_dat[i].cdev.brightness = LED_OFF;
		priv->leds_dat[i].port = pdata->leds[i].port;
		priv->leds_dat[i].group = pdata->leds[i].group;
		priv->leds_dat[i].active_low = pdata->leds[i].active_low;

		ret = led_classdev_register(&pdev->dev, &(priv->leds_dat[i].cdev));
		if (ret < 0)
			return ret;
	}

	platform_set_drvdata(pdev, priv);

	return 0;

}

static int rtl8367s_led_remove(struct platform_device *pdev)
{
	int i = 0;
	struct rtl8367s_led_priv *priv = platform_get_drvdata(pdev);

	for (i = 0; i < priv->lednum; i++)
		led_classdev_unregister(&(priv->leds_dat[i].cdev));

	platform_set_drvdata(pdev, NULL);
	devm_kfree(&pdev->dev, priv);
	return 0;
}

struct platform_driver rtl8367s_led_drv = {
		.probe = rtl8367s_led_probe,
		.remove= rtl8367s_led_remove,
		.driver 	= {
			.name	= "rtl8367s_leds",
			.owner	= THIS_MODULE,
		}
};

struct rtl8367s_led rtl8367s_leds[5] =
		{{.name = "SWITCH_LED_0", .port = 0, .group = 0, .active_low = 1},
		 {.name = "SWITCH_LED_1", .port = 1, .group = 0, .active_low = 1},
		 {.name = "SWITCH_LED_2", .port = 2, .group = 0, .active_low = 0},
		 {.name = "SWITCH_LED_3", .port = 3, .group = 0, .active_low = 1},
		 {.name = "SWITCH_LED_4", .port = 4, .group = 0, .active_low = 0}};

struct rtl8367s_led_platform_data rtl8367s_led_pdata = {
		.lednum = 5,
		.leds = rtl8367s_leds
};

static int
_rtl8367s_led_sysctrl(void)
{
	platform_driver_register(&rtl8367s_led_drv);
	platform_device_register_resndata(NULL, "rtl8367s_leds", -1, NULL, 0,
				&rtl8367s_led_pdata, sizeof(rtl8367s_led_pdata));
	/* change default settings */
    rtk_led_groupConfig_set(LED_GROUP_0, LED_CONFIG_LEDOFF);   /* control by swconfig leds*/
    rtk_led_groupConfig_set(LED_GROUP_1, LED_CONFIG_LINK_ACT); /* control by switch hw */
	return 0;
}
#else
static int
_rtl8367s_led_sysctrl(void){return 0;}
#endif

static int
_rtl8367s_led_config(void)
{
    rtk_portmask_t portmask;

    RTK_PORTMASK_PORT_SET(portmask, UTP_PORT0);
    RTK_PORTMASK_PORT_SET(portmask, UTP_PORT1);
    RTK_PORTMASK_PORT_SET(portmask, UTP_PORT2);
    RTK_PORTMASK_PORT_SET(portmask, UTP_PORT3);
    RTK_PORTMASK_PORT_SET(portmask, UTP_PORT4);

    rtk_led_enable_set(LED_GROUP_0, &portmask);
    rtk_led_enable_set(LED_GROUP_1, &portmask);
    rtk_led_operation_set(LED_OP_PARALLEL);
    rtk_led_blinkRate_set(LED_BLINKRATE_32MS);
    rtk_led_groupConfig_set(LED_GROUP_0, LED_CONFIG_SPD1000ACT);
    rtk_led_groupConfig_set(LED_GROUP_1, LED_CONFIG_SPD10010ACT);

	return _rtl8367s_led_sysctrl();
}

/*extern void swconfig_leds_trig_by_source(struct switch_dev *, int);*/

static void switch_work_func(struct work_struct *work)
{
        struct rtl8367s_priv *priv;
		struct phy_device *pdev;

        priv = container_of(work, struct rtl8367s_priv, switch_work.work);
		pdev = priv->phy;

        rtk_switch_setReg(0x1101, 0x0);
		rtk_switch_setReg(0x1102, 0xffff);

		/*swconfig_leds_trig_by_source(&priv->dev, 1);*/

		rtk_switch_setReg(0x1101, 0x9);

		enable_irq(pdev->irq);
}

static irqreturn_t rtl8367s_handle_irq(int irq, void *dev_id)
{
	struct rtl8367s_priv *priv = (struct rtl8367s_priv *)dev_id;

	/* printk(KERN_ERR"[%s,%d]:interrupt occured: %d\n", __FUNCTION__, __LINE__, irq); */
	disable_irq_nosync(irq);
	schedule_delayed_work(&priv->switch_work,
						  msecs_to_jiffies(SWITCH_WORK_DELAY));
	return IRQ_HANDLED;
}

static int
rtl8367s_interrupt_init(struct phy_device *pdev)
{
	struct rtl8367s_priv *priv = pdev->priv;
	int ret;
	unsigned int irq;

	/*swconfig_leds_trig_by_source(&priv->dev, 1);*/

	rtk_switch_setReg(0x1100, 0x1);	/* active low */
	rtk_switch_setReg(0x1101, 0x0);	/* disable all */
	rtk_switch_setReg(0x1102, 0xffff); /* clear all status */
	rtk_switch_setReg(0x1101, 0x9);	/* enable link & speed interrupt */

	irq = pdev->irq;
	ret = request_irq(irq, rtl8367s_handle_irq, 0, "RTL8367S_IRQ", priv);
	if (ret) {
		printk(KERN_ERR"Could not acquire Switch IRQ %d\n", irq);
		return ret;
	}
	return 0;
}

static int
rtl8367s_interrupt_fini(struct phy_device *pdev)
{
	struct rtl8367s_priv *priv = pdev->priv;

	free_irq(pdev->irq, priv);
	/*swconfig_leds_trig_by_source(&priv->dev, 0);*/
	return 0;
}

int genphy_config_init_global(struct phy_device *phydev);
static int
rtl8367s_config_init(struct phy_device *pdev)
{
        struct rtl8367s_priv *priv = pdev->priv;
        struct net_device *dev = pdev->attached_dev;
        struct switch_dev *swdev;
        int ret;

        DBGINFO("start");
        printk(KERN_ERR"@@@@@@@@@@@@@@@@@@@@rtl8367s_config_init\r\n");

        if (!priv) {
                priv = kzalloc(sizeof(struct rtl8367s_priv), GFP_KERNEL);
                if (priv == NULL)
                        return -ENOMEM;

        printk(KERN_ERR"@@@@@@@@@@@@@@@@@@@@rtl8367s_config_init: kzalloc pdev->priv = %p\r\n", priv);
        }
       else
       {
           printk(KERN_ERR"@@@@@@@@@@@@@@@@@@@@rtl8367s_config_init: already has pdev->priv = %p\r\n", priv);
           return 0;
       }


        printk(KERN_ERR"@@@@@@@@@@@@@@@@@@@@rtl8367s led settings\r\n");
        _rtl8367s_led_config();
 
        priv->phy = pdev;

        pdev->priv = priv;
        pdev->supported |= SUPPORTED_1000baseT_Full | SUPPORTED_Pause;
        pdev->advertising = pdev->supported;
        /*genphy_config_init_global(pdev);*/

        swdev = &priv->dev;
        swdev->cpu_port = RTL8367S_PORT_CPU;
        swdev->ops = &rtl8367s_sw_ops;
        swdev->ports = RTL8367S_MAX_PORTS;
        swdev->name = "RTL8367S";
        swdev->vlans = RTL8367S_MAX_VLANS;

        INIT_DELAYED_WORK(&priv->switch_work, switch_work_func);

        /*ret = register_switch(&priv->dev, pdev->attached_dev);
        if (ret)
                goto err_free_priv;*/

        ret = rtl8367s_sw_reset_switch(&priv->dev);
        if (ret)
                goto err_free_priv;

        /*dev->phy_ptr = priv;*/

        rtk_vlan_init();

        rtk_port_rgmiiDelayExt_set(EXT_PORT1,1,7);

        rtk_switch_setReg(0x6602, 0x28A0); /* ¹Ø±ÕÔ¤¼ÓÖØ*/
        rtk_switch_setReg(0x6601, 0x0482); 
        rtk_switch_setReg(0x6600, 0x00C0);

       /* schedule_delayed_work(&priv->switch_work,
                      msecs_to_jiffies(SWITCH_WORK_DELAY)); */
    	rtl8367s_interrupt_init(pdev);

        return 0;

err_free_priv:
    pdev->priv = NULL;
        kfree(priv);
        return ret;
}

static int rtl8367s_carrier_check;

static int vlandev_event(struct notifier_block *this, unsigned long event,
			 void *ptr)
{
	struct net_device *dev = ptr;

	ASSERT_RTNL();

	switch (event) {
	case NETDEV_UP:
		if (is_vlan_dev(dev))
			rtl8367s_carrier_check = 1;
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}


static struct notifier_block vlandev_notifier = {
	.notifier_call = vlandev_event,
};

static int rtl8367s_get_vlan_dev(struct phy_device *phydev, int vlanID)
{
        struct rtl8367s_priv *priv = phydev->priv;
        uint8_t  name[32] = {0};

        DBGINFO("dev:%s,vlan:%d",phydev->attached_dev->name,vlanID);
        sprintf(name, "%s.%d", phydev->attached_dev->name, vlanID);
        priv->vlan_dev[vlanID] = dev_get_by_name(&init_net, name);
        if(priv->vlan_dev[vlanID] != NULL){
                DBGINFO("");
                dev_put(priv->vlan_dev[vlanID]);
                return 1;
        }

        DBGINFO("");
        return 0;
}

static int
rtl8367s_read_status(struct phy_device *phydev)
{
        struct rtl8367s_priv *priv = phydev->priv;
        struct switch_dev *dev;
        int ret = 0;
        int i, port_status = 0;
        rtk_port_mac_ability_t portStatus;

        dev = (struct switch_dev *)priv;
        for(i = UTP_PORT0; i <= UTP_PORT4; i++) {
                rtk_port_macStatus_get(i, &portStatus);
                if(portStatus.link)
                        port_status |= 1 << i;
        }

      //DBGINFO("new port status=%x,phydev:%s", port_status,phydev->drv->name);
        if((priv->old_port_status ^ port_status) != 0 ||
            rtl8367s_carrier_check || priv->vlan_changed) {
                rtl8367s_carrier_check = 0;
                priv->vlan_changed = 0;

                for(i = 0; i < RTL8367S_MAX_VLANS; i++) {
                        if(((port_status & priv->vlan_table[i]) != 0) &&
                                        (priv->vlan_status[i] == 0)){
                                /*if(unlikely(priv->vlan_dev[i] == NULL)) {
                                        ret = rtl8367s_get_vlan_dev(phydev, i);
                                } else
                                        ret = 1;*/
                                priv->vlan_dev[i] = NULL;
                                ret = rtl8367s_get_vlan_dev(phydev, i);

                                if(ret == 1) {
                                        netif_carrier_on(priv->vlan_dev[i]);
                                        priv->vlan_status[i] = 1;
                                }
                        } else if( (priv->vlan_table[i] != 0) &&
                                        ((port_status & priv->vlan_table[i]) == 0)) {
                                /*if(unlikely(priv->vlan_dev[i] == NULL)) {
                                        ret = rtl8367s_get_vlan_dev(phydev, i);
                                } else
                                        ret = 1;*/
                                priv->vlan_dev[i] = NULL;
                                ret = rtl8367s_get_vlan_dev(phydev, i);

                                if(ret == 1) {
                                        netif_carrier_off(priv->vlan_dev[i]);
                                        priv->vlan_status[i] = 0;
                                }
                        }
                }
        }
        priv->old_port_status = port_status;

        rtk_port_macStatus_get(EXT_PORT0, &portStatus);
        phydev->link = !!portStatus.link;
        if (!phydev->link)
                return 0;

        switch (portStatus.speed) {
        case PORT_SPEED_10M:
                phydev->speed = SPEED_10;
                break;
        case PORT_SPEED_100M:
                phydev->speed = SPEED_100;
                break;
        case PORT_SPEED_1000M:
                phydev->speed = SPEED_1000;
                break;
        default:
                phydev->speed = 0;
        }
        phydev->duplex = portStatus.duplex ? DUPLEX_FULL : DUPLEX_HALF;

        phydev->state = PHY_RUNNING;
        netif_carrier_on(phydev->attached_dev);
        phydev->adjust_link(phydev->attached_dev);

        return ret;
}

static int
rtl8367s_config_aneg(struct phy_device *phydev)
{
        DBGINFO("start");
        return genphy_config_aneg(phydev);
}

static int
rtl8367s_probe(struct phy_device *pdev)
{
        DBGINFO("start");
    printk(KERN_ERR"@@@@@@@@@@@@rtl8367s_probe");
        return 0;
}

static void
rtl8367s_remove(struct phy_device *pdev)
{
        struct rtl8367s_priv *priv = pdev->priv;
        struct net_device *dev = pdev->attached_dev;

        DBGINFO("start");
    printk(KERN_ERR"@@@@@@@@@@@@rtl8367s_remove");

        if (!priv)
                return;

		rtl8367s_interrupt_fini(pdev);

        /*dev->priv_flags &= ~IFF_NO_IP_ALIGN;*/

        /*unregister_switch(&priv->dev);*/
        cancel_delayed_work(&priv->switch_work);

    pdev->priv = NULL;
        kfree(priv);
}

static struct phy_driver rtl8367s_driver = {
        .phy_id             = 0x001cc942,
        .name               = "Realtek RTL8367S",
        .phy_id_mask    = 0xffff0000,
        .features           = PHY_BASIC_FEATURES,
        .probe              = rtl8367s_probe,
        .remove             = rtl8367s_remove,
        .config_init    = rtl8367s_config_init,
        .config_aneg    = rtl8367s_config_aneg,
        .read_status    = rtl8367s_read_status,
        /*.driver             = { .owner = THIS_MODULE },*/
};

#define PROC_RTK_PORT_DIR_NAME "rtk_port"
#define PROC_RTK_PORT0_NAME    "port0"
#define PROC_RTK_PORT1_NAME    "port1"


static struct proc_dir_entry *parents_proc_entry = NULL;

static int port0_state_proc_show(struct seq_file *m, void *v)
{
    rtk_port_mac_ability_t portStatus;

	if(NULL == m)
	{
		printk("Internal error.\n");
		return 1;
	}

    memset(&portStatus, 0, sizeof(portStatus));
    if(RT_ERR_OK != rtk_port_macStatus_get(UTP_PORT0, &portStatus))
    {
		printk("rtk_port_macStatus_get fail.\n");
		return 1;
    }

	seq_printf(m, "%u\n", portStatus.link);

	return 0;
}

static int port0_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, port0_state_proc_show, file->f_path.dentry->d_iname);
}

static int port1_state_proc_show(struct seq_file *m, void *v)
{
    rtk_port_mac_ability_t portStatus;

	if(NULL == m)
	{
		printk("Internal error.\n");
		return 1;
	}

    memset(&portStatus, 0, sizeof(portStatus));
    if(RT_ERR_OK != rtk_port_macStatus_get(UTP_PORT1, &portStatus))
    {
		printk("rtk_port_macStatus_get fail.\n");
		return 1;
    }

	seq_printf(m, "%u\n", portStatus.link);

	return 0;
}

static int port1_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, port1_state_proc_show, file->f_path.dentry->d_iname);
}

static const struct file_operations port0_proc_fops = 
{
	.open = port0_proc_open,
	.read = seq_read,
	.write = NULL,
	.release = single_release,
};

static const struct file_operations port1_proc_fops = 
{
	.open = port1_proc_open,
	.read = seq_read,
	.write = NULL,
	.release = single_release,
};


int __init
rtl8367s_init(void)
{
        struct proc_dir_entry *port0_entry = NULL;
        struct proc_dir_entry *port1_entry = NULL;

        DBGINFO("start");
        register_netdevice_notifier(&vlandev_notifier);

        /* create proc file */
        parents_proc_entry = proc_mkdir(PROC_RTK_PORT_DIR_NAME, NULL);
        if (NULL == parents_proc_entry)
        {
            printk("mkdir for rtk port failed");
            goto fail;
        }

        port0_entry = proc_create(PROC_RTK_PORT0_NAME, S_IRUGO, parents_proc_entry, &port0_proc_fops);
        if (NULL == port0_entry)
        {
            printk("create port0 entry failed");
            goto fail;
        }

        port1_entry = proc_create(PROC_RTK_PORT1_NAME, S_IRUGO, parents_proc_entry, &port1_proc_fops);
        if (NULL == port1_entry)
        {
            printk("create port1 entry failed");
            goto fail;
        }

        return phy_driver_register(&rtl8367s_driver, THIS_MODULE);

fail:
        if (NULL == port0_entry)
        {
            remove_proc_entry(PROC_RTK_PORT0_NAME, parents_proc_entry);
        }
        if (NULL == port1_entry)
        {
            remove_proc_entry(PROC_RTK_PORT1_NAME, parents_proc_entry);
        }
    
        if (NULL == parents_proc_entry)
        {
            remove_proc_entry(PROC_RTK_PORT_DIR_NAME, NULL);
        }
        return -1;
}

void __exit
rtl8367s_exit(void)
{
        DBGINFO("start");
        phy_driver_unregister(&rtl8367s_driver);
}

module_init(rtl8367s_init);
module_exit(rtl8367s_exit);
MODULE_DESCRIPTION("Realtek RTL8367S ethernet switch driver");
MODULE_AUTHOR("tp-link");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("rtl8367s");
