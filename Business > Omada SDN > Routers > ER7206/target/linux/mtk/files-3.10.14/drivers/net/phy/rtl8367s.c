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
#include <uapi/linux/switch.h>
#include <linux/delay.h>
#include <linux/phy.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/lockdep.h>
#include <linux/workqueue.h>
#include "rtl8367s.h"
#include "rtl8367s_api.h"
#include <linux/platform_device.h>

#ifdef CONFIG_OF
#include <linux/of.h>
#endif

//#define DBGINFO(fmt, ...) printk("#####################%s(%d): " fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
#define DBGINFO(fmt, args...)

#define RTL8367S_MAX_VLANS      4095
#define RTL8367S_MAX_PORTS      8
#define RTL8367S_PORT_CPU       7

#define SWITCH_WORK_DELAY 2000 /* 2000ms */


//extern void switch_ioctl_set(int (*hook) (struct net_device *, struct ifreq *, int));
extern rtk_api_ret_t rtk_vlan_portIgrFilterEnable_set(rtk_port_t port, rtk_enable_t igr_filter);
extern rtk_api_ret_t rtk_port_isolation_set(rtk_port_t port, rtk_portmask_t *pPortmask);
extern rtk_api_ret_t rtk_port_isolation_get(rtk_port_t port, rtk_portmask_t *pPortmask);

extern void rtk_set_cpuTagKeep(void);
extern void rtk_clear_cpuTagKeep(void);

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
        u8 vlan_tagged;
        u16 pvid[RTL8367S_MAX_PORTS];
        /* if set, the vlan interface is UP */
        u8 vlan_status[RTL8367S_MAX_VLANS];
        struct net_device *vlan_dev[RTL8367S_MAX_VLANS];
        u32 old_port_status;
        struct delayed_work switch_work;
};

typedef struct _portability
{
	rtk_uint32 portnum;
    rtk_uint32 speed;
    rtk_uint32 duplex;
    rtk_uint32 link;
    rtk_uint32 aneg;
    rtk_uint32 tx_flow;
    rtk_uint32 rx_flow;
}portability;

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
                if (!(ports & (1 << i)) || priv->vlan_tagged & (1 << i))
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

        DBGINFO("vid=%d, port_mask=%x, tag=%x", vid, port_mask, priv->vlan_tagged);

        memset(&vlan, 0x00, sizeof(rtk_vlan_cfg_t));
        for (i = 0; i < RTL8367S_MAX_PORTS; i++) {
                logicalPort = rtk_switch_port_P2L_get(i);
                if (port_mask & BIT(i)) {
                        RTK_PORTMASK_PORT_SET(vlan.mbr, logicalPort);

                        if ((priv->vlan_tagged & BIT(i)) == 0) {
                                RTK_PORTMASK_PORT_SET(vlan.untag, logicalPort);
                        }
                }
        }

        vlan.ivl_en = ENABLED;

        rtk_vlan_set(vid, &vlan);
        DBGINFO("vlan.mbr=%x, vlan.untag=%x", vlan.mbr, vlan.untag);

        for (i = 0; i < RTL8367S_MAX_PORTS; i++) {
                logicalPort = rtk_switch_port_P2L_get(i);
                if (port_mask & BIT(i)) {
                        rtk_vlan_portPvid_set(logicalPort, vid, 0);
                        DBGINFO("set pvid, lport=%d, vid=%d", logicalPort, vid);
                }
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

        DBGINFO("start");
        val->len = 0;
        for (i = 0; i < dev->ports; i++) {
                struct switch_port *p;

                if (!(ports & (1 << i)))
                        continue;

                p = &val->value.ports[val->len++];
                p->id = i;
                if (priv->vlan_tagged & (1 << i))
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
                        DBGINFO("p->flags : %x,set switch port %d vlan_tagged",p->flags, p->id);
                        priv->vlan_tagged |= (1 << p->id);
                } else {
                
                        DBGINFO("SWITCH_PORT_FLAG_TAGGED not setted,set switch port %d vlan_tagged to zero", p->id);
                        priv->vlan_tagged &= ~(1 << p->id);
                        priv->pvid[p->id] = val->port_vlan;

                        /* make sure that an untagged port does not
                         * appear in other vlans */
                        for (j = 0; j < RTL8367S_MAX_VLANS; j++) {
                                if (j == val->port_vlan)
                                        continue;
                                priv->vlan_table[j] &= ~(1 << p->id);
                        }
                }

                *vt |= 1 << p->id;
        }
        return 0;
}

static int
rtl8367s_sw_hw_apply(struct switch_dev *dev)
{
        struct rtl8367s_priv *priv = to_rtl8367s(dev);
        u8 portmask[RTL8367S_MAX_PORTS];
        int i, j;

        DBGINFO("start");

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
        .get_reg_val = rtl8367s_sw_get_reg_val,
        .set_reg_val = rtl8367s_sw_set_reg_val,
    .get_phy_reg_val = rtl8367s_sw_get_phy_reg_val,
    .set_phy_reg_val = rtl8367s_sw_set_phy_reg_val,
};

static void switch_work_func(struct work_struct *work)
{
        struct net_device *lan_dev;
        struct rtl8367s_priv *priv;
        const unsigned char zero_mac[ETH_ALEN] = {0};

        priv = container_of(work, struct rtl8367s_priv, switch_work.work);
        lan_dev = dev_get_by_name(&init_net, "br-lan");

        if (lan_dev) {
                dev_put(lan_dev);

                if (memcmp(zero_mac, lan_dev->dev_addr, sizeof(zero_mac))) {
                        bind_static_lan_mac(lan_dev->dev_addr);
                        return;
                }
        }

        schedule_delayed_work(&priv->switch_work,
                              msecs_to_jiffies(SWITCH_WORK_DELAY));
}

static int rtl8376s__getPortLinkStatus(struct net_device *dev, struct ifreq *ifr)
{
  
	rtk_port_mac_ability_t portStatus;
	rtk_port_t logicalPort;
	rtk_api_ret_t ret;
	portability  link;
	u32 port = 0;
	
	if(NULL == ifr->ifr_data)
		return -EFAULT;
		
	port = ((portability*)(ifr->ifr_data))->portnum;
	
	if (port > RTL8367S_MAX_PORTS)
		return -EFAULT;

	logicalPort = rtk_switch_port_P2L_get(port);

	ret = rtk_port_macStatus_get(logicalPort, &portStatus);
	if (ret != RT_ERR_OK) {
	DBGINFO("rtk_port_macStatus_get failed");
			return -1;
	}

	link.portnum = port;
	link.link = !!portStatus.link;
	link.duplex = !!portStatus.duplex;
	link.aneg = !!portStatus.nway;
	link.tx_flow = !!portStatus.txpause;
	link.rx_flow = !!portStatus.rxpause;
	

	switch (portStatus.speed) {
	case PORT_SPEED_10M:
			link.speed = SWITCH_PORT_SPEED_10;
			break;
	case PORT_SPEED_100M:
			link.speed = SWITCH_PORT_SPEED_100;
			break;
	case PORT_SPEED_1000M:
			link.speed = SWITCH_PORT_SPEED_1000;
			break;
	default:
			link.speed = 0;
	}
	
    if (copy_to_user(ifr->ifr_data, &link, sizeof(portability)))
    {
        return -EFAULT;
    }

    return 0;
}


#define SIOCGPORTSTATUS		(SIOCDEVPRIVATE | 0x09)
 int rtl8376s__ioctl_handler(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	int ret;

	switch (cmd) 
	{

	case SIOCGPORTSTATUS:
		ret = rtl8376s__getPortLinkStatus(dev, ifr);
		return ret;
	default:
			break;
	}

	return -EOPNOTSUPP;
}




#ifdef CONFIG_OF
static const struct of_device_id rtl8367s_match[] = {
	{ .compatible = "realtek,rtl8367s" },
	{ .compatible = "Realtek_8367S" },
	{},
};
MODULE_DEVICE_TABLE(of, rtl8367s_match);
#endif

static int rtl8367s_switch_init(struct rtl8367s_priv *priv)
{
	struct switch_dev *dev = &priv->dev;
	int err = 0;
	
	INIT_DELAYED_WORK(&priv->switch_work, switch_work_func);
			
	if(NULL != dev)
	{

		dev->name = "Realtek_8367S";
		dev->cpu_port = RTL8367S_PORT_CPU;
		dev->ports = RTL8367S_MAX_PORTS;
		dev->vlans = RTL8367S_MAX_VLANS;
		dev->ops = &rtl8367s_sw_ops;
		dev->alias = "eth0";
		err = register_switch(dev, NULL);
		if (err)
			printk("switch registration failed\n");
	}		

        err = rtl8367s_sw_reset_switch(dev);
		if (err)
			printk("switch rtl8367s_sw_reset_switch failed\n");

       // dev->phy_ptr = priv;

        //rtk_switch_init();
        //rtk_port_phyEnableAll_set(ENABLED);

        rtk_vlan_init();
#if 0
        void __iomem *base = NULL;    
        base = ioremap(AR71XX_MII_BASE, AR71XX_MII_SIZE);       
        if (base) {             
                __raw_writel(0x1b838116,base + 0x18);
        }       
        iounmap(base);
        msleep(1000);
#endif
        schedule_delayed_work(&priv->switch_work,
                      msecs_to_jiffies(SWITCH_WORK_DELAY));

	return err;
}

static int  rtl8367s_probe(struct platform_device *pdev)
{
	
	int err;
	struct rtl8367s_priv *priv = kzalloc(sizeof(struct rtl8367s_priv), GFP_KERNEL);
	if (!priv) {
		return -ENODEV;
	}	
	
	//extern int rtk_int_pre(void);
	//rtk_int_pre();
	
	printk("@@@@rtl8367s_probe start\n");

	platform_set_drvdata(pdev, priv);
#if 1
	err = rtl8367s_switch_init(priv);
	if (err)
		goto err_clear_drvdata;
#endif
	printk("@@@@rtl8367s_probe OK\n");	

	return 0;

 err_clear_drvdata:
	printk("@@@@rtl8367s_probe fail\n");
	platform_set_drvdata(pdev, NULL);
	kfree(priv);
	return err;
}

static int rtl8367s_remove(struct platform_device *pdev)
{
	struct rtl8367s_priv *priv = platform_get_drvdata(pdev);
	if (priv) {
		platform_set_drvdata(pdev, NULL);
		kfree(priv);
	}
	printk("@@@@rtl8367s_remove\n");
	return 0;
}

static void rtl8367s_shutdown(struct platform_device *pdev)
{
	printk("@@@@rtl8367s_shutdown\n");
}



static struct platform_driver rtl8367s_driver = {
	.driver = {
		.name		= "Realtek_8367S",
		.owner		= THIS_MODULE,
#ifdef CONFIG_OF
		.of_match_table = of_match_ptr(rtl8367s_match),
#endif
	},
	.probe		= rtl8367s_probe,
	.remove		= rtl8367s_remove,
	.shutdown	= rtl8367s_shutdown,
};



module_platform_driver(rtl8367s_driver);

MODULE_DESCRIPTION("Realtek_8367S");
MODULE_AUTHOR("Gabor Juhos <juhosg@openwrt.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" "Realtek_8367S");
