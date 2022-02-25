/*!Copyright (c) 2015-2016 TP-LINK Technologies CO.,LTD.
 *All rights reserved.
 *
 *\file     rtl8370mb.c
 *\brief    driver of RTL8370MB (see TL-WVR458G 2.0).
 *
 *\author   LiuZenglin <LiuZenglin@tp-link.net>
 *\version  1.0.0
 *\date     05/03/2016
 *
 *\history  \arg 1.0.0 05/03/2016, LiuZenglin, Create file.
 */


/**********************************************************************/
/*                          CONFIGURATIONS                            */
/**********************************************************************/

/**********************************************************************/
/*                          INCLUDE_FILES                             */
/**********************************************************************/
#include "linux/if.h"
#include "linux/module.h"
#include "linux/init.h"
#include "linux/list.h"
#include "linux/if_ether.h"
#include "linux/skbuff.h"
#include "linux/netdevice.h"
#include "linux/netlink.h"
#include "linux/bitops.h"
#include "net/genetlink.h"
#include "net/switch.h"
#include "linux/delay.h"
#include "linux/phy.h"
#include "linux/netdevice.h"
#include "linux/etherdevice.h"
#include "linux/lockdep.h"
#include "linux/workqueue.h"

#include "../rtk_error.h"
#include "../rtk_types.h"
#include "../rtl8367c_asicdrv_phy.h"
#include "../smi.h"
#include "../port.h"
#include "../stat.h"
#include "../vlan.h"
#include "../mirror.h"
#include "../l2.h"
#include "../rtk_switch.h"
#include "asm/mach-ath79/ar71xx_regs.h"

#ifdef CONFIG_OF
#include "linux/of.h"
#endif

/**********************************************************************/
/*                           DEFINES                                  */
/**********************************************************************/
//#define DBGINFO(fmt, ...) printk("#####################%s(%d): " fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
#define DBGINFO(fmt, args...)

#define RTL8367S_MAX_VLANS      128
#define RTL8367S_MAX_PORTS      8
#define RTL8367S_PORT_CPU       6
#define RTL8370MB_MAX_PORTS     10
#define RTL8370MB_PORT_CPU      8

#define SWITCH_WORK_DELAY 2000 /* 2000ms */

typedef enum mirror_mode_e
{
    MODE_INGRESS = 0,
    MODE_EGRESS,
    MODE_BOTH,
    MODE_MAX
} mirror_mode_t;
extern void MDC_MDIO_READ(rtk_uint32 preamble_len, rtk_uint32 phy_id, rtk_uint32 register_id, rtk_uint32 *pData);
extern void MDC_MDIO_WRITE(rtk_uint32 preamble_len, rtk_uint32 phy_id, rtk_uint32 register_id, rtk_uint32 data);

/**********************************************************************/
/*                            TYPES                                   */
/**********************************************************************/
struct rtl8367s_priv {
        struct switch_dev dev;
        struct phy_device *phy;
        const struct net_device_ops *ndo_old;
        struct net_device_ops ndo;
        char buf[4096];

        bool mii_lo_first;

        /* all fields below are cleared on reset */
        u16 vlan_id[RTL8367S_MAX_VLANS];
        u16 vlan_table[RTL8367S_MAX_VLANS];
        u16 vlan_tagged;
        u16 pvid[RTK_SWITCH_PORT_NUM];
        /* if set, the vlan interface is UP */
        u16 vlan_status[RTL8367S_MAX_VLANS];
        struct net_device *vlan_dev[RTL8367S_MAX_VLANS];
        u32 old_port_status;
        struct delayed_work switch_work;
};

#define to_rtl8367s(_dev) container_of(_dev, struct rtl8367s_priv, dev)

/**********************************************************************/
/*                            EXTERN_PROTOTYPES                       */
/**********************************************************************/

/**********************************************************************/
/*                            LOCAL_PROTOTYPES                        */
/**********************************************************************/

/**********************************************************************/
/*                            VARIABLES                               */
/**********************************************************************/

/**********************************************************************/
/*                            LOCAL_FUNCTIONS                         */
/**********************************************************************/
u32 rtl8367s_reg_read(struct mii_bus *mii, u32 reg)
{
        u32 val;
        ret_t ret;

        ret = rtl8367c_getAsicReg(reg, &val);
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

        ret = rtl8367c_setAsicReg(reg, val);
        if (ret != RT_ERR_OK) {
                DBGINFO("can not write val[%d] to reg[%x]", val, reg);
                return -1;
        }

        DBGINFO("write val[%d] to reg[%x]", val, reg);
        return 0;
}


/**********************************************************************/
/*                            PUBLIC_FUNCTIONS                        */
/**********************************************************************/
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
        u16 ports = 0;
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
                rtl8367c_getAsicReg(reg_ctl, &phy_ctl);

                if (linkup)
                        rtl8367c_setAsicReg(reg_ctl, phy_ctl & ~BMCR_PDOWN);
                else
                        rtl8367c_setAsicReg(reg_ctl, phy_ctl | BMCR_PDOWN);
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
        for (i = 0; i < priv->dev.ports; i++) {
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

        for (i = 0; i < priv->dev.ports; i++) {
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
        rtl8367c_setAsicReg(reg, val);
        return 0;
};

static int
rtl8367s_sw_get_reg_val(struct switch_dev *dev, int reg, int *val)
{
        DBGINFO("start");
        rtl8367c_getAsicReg(reg, val);
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

    if (phy_index == 9)
    {
        MDC_MDIO_READ(MDC_MDIO_PREAMBLE_LEN, 5, reg, &reg_val);
    }
    else
    {
        ret = rtl8367c_getAsicPHYReg(phy_index, reg, &reg_val);
            DBGINFO("phyNo = %d, register = %d, value = %x, ret = %d", phy_index, reg, reg_val, ret);
    }

    val->len = snprintf(buf, sizeof(priv->buf), "%x", reg_val);
    val->value.s = buf;

    return 0;
}

static int
rtl8367s_sw_set_phy_reg_val(struct switch_dev *dev, int phy_index, struct switch_val *val)
{
    int ret = 0;
    rtk_uint32 reg = 0;
    rtk_uint32 reg_val = 0;

    sscanf(val->value.s, "%x-%x", &reg, &reg_val);
        DBGINFO("phyNo = %d, register = %d, value = %x", phy_index, reg, reg_val);

    if (phy_index == 9)
    {
        MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, 5, reg, reg_val);
    }
    else
    {
        ret = rtl8367c_setAsicPHYReg(phy_index, reg, reg_val);
    }
    return ret;
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

        /*!<读取外部phy  */
        if (port == 9)
        {
            unsigned int status0;
            unsigned int status1;
    	    MDC_MDIO_READ(MDC_MDIO_PREAMBLE_LEN, 5, 0x1, &status0);
    	    MDC_MDIO_READ(MDC_MDIO_PREAMBLE_LEN, 5, 0x1a, &status1);
    	    link->link = !!(status1 & 0x4);
            link->aneg = !!(status0 & 0x8);
            link->duplex = !!(status1 & 0x8);
            link->tx_flow = !!(status1 & 0x40);
            link->rx_flow = !!(status1 & 0x80);
            portStatus.speed = ((status1 & 0x30)>> 4);
        }
        else
        {
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
        }

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
        printk("[%d], link %d, speed %d, an %d, duplex %d, txpau %d, rxpau %d\r\n",
            port, link->link, link->speed, link->aneg, link->duplex, link->tx_flow, link->rx_flow);

        return 0;
}

static int
rtl8367s_sw_get_ports(struct switch_dev *dev, struct switch_val *val)
{
        struct rtl8367s_priv *priv = to_rtl8367s(dev);
        u16 ports = priv->vlan_table[val->port_vlan];
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
        u16 *vt = &priv->vlan_table[val->port_vlan];
        int i, j;

        DBGINFO("vid=%d, len=%d", val->port_vlan, val->len);

        *vt = 0;
        for (i = 0; i < val->len; i++) {
                struct switch_port *p = &val->value.ports[i];
                if (p->flags & (1 << SWITCH_PORT_FLAG_TAGGED)) {
                        priv->vlan_tagged |= (1 << p->id);
                } else {
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
        u16 portmask[RTK_SWITCH_PORT_NUM];
        int i, j;

        DBGINFO("start");

        memset(portmask, 0, sizeof(portmask));

        /* calculate the port destination masks and load vlans
         * into the vlan translation unit */
        for (j = 0; j < RTL8367S_MAX_VLANS; j++) {
                u16 vp = priv->vlan_table[j];

                if (!vp)
                        continue;

                for (i = 0; i < dev->ports; i++) {
                        u16 mask = (1 << i);
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
        DBGINFO("start");

        /* open smart speed down function, bit3 => 1000M->100M and bit5 => 100M->10M */
        rtl_open_smart_speeddown();

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
	rtk_portmask_t portmask;
	struct switch_port *ports = NULL;
	int i = 0;
	mirror_mode_t mode = 0;

	ports = val->value.ports;
	if(!ports)
	{
		return -EINVAL;
		printk("Error : The ports is null.\r\n");
	}		

	if (port >= dev->ports)
	{
		printk("%s:%d: invalid port = %d, dev->ports = %d\r\n", __func__, __LINE__, port, dev->ports);
		return -EINVAL;
	}

	logicalPort = rtk_switch_port_P2L_get(port);

	/*rtk_mirror_portIso_set(1);*/
	RTK_PORTMASK_CLEAR(portmask);
	RTK_PORTMASK_CLEAR(rx_portmask);
	RTK_PORTMASK_CLEAR(tx_portmask);

	for (i = 0; i < val->len; i ++)
	{		
		if (ports[i].id >= dev->ports)
		{
			printk("%s:%d: invalid  port = %d, dev->ports = %d\r\n", __func__, __LINE__, ports[i].id, dev->ports);
			return -EINVAL;
		}

		/* get the mirror mode, 0:ingress, 1:egress, 2:both */
		if (unlikely(ports[i].flags & (1 << SWITCH_PORT_FLAG_TAGGED)))
		{
			DBGINFO("Mirror mode [%d], 0:ingress, 1:egress, 2:both.\n", ports[i].id);
			mode = ports[i].id;			
		}
		else
		{
			/* mirror port != source port */
			if(ports[i].id == port)
			{
				printk("%s:%d: invalid mirroring_port = %d\r\n", __func__, __LINE__, ports[i].id);
				return -EINVAL;
			}
			
			DBGINFO("Add port %d to portmask.\n", ports[i].id);
			RTK_PORTMASK_PORT_SET(portmask, rtk_switch_port_P2L_get(ports[i].id));
		}
	}

	if(MODE_INGRESS == mode)
	{
		memcpy(&rx_portmask, &portmask, sizeof(rtk_portmask_t));
	}
	else if (MODE_EGRESS == mode)
	{

		memcpy(&tx_portmask, &portmask, sizeof(rtk_portmask_t));
	}
	else
	{
		memcpy(&rx_portmask, &portmask, sizeof(rtk_portmask_t));
		memcpy(&tx_portmask, &portmask, sizeof(rtk_portmask_t));
	}

	ret = rtk_mirror_portBased_set(logicalPort, &rx_portmask, &tx_portmask);
	DBGINFO(" rtk_mirror_portBased_set rx_portmask=[%d], tx_portmask=[%d], ret = [%d]", rx_portmask.bits[0], tx_portmask.bits[0], ret);

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
                        rtk_l2_ucastAddr_t l2_entry;
                        rtk_mac_t mac_addr;
                        
                        if (lan_dev->dev_addr == NULL)
                            return;

                        memcpy(mac_addr.octet, lan_dev->dev_addr, ETH_ALEN);
                        memset(&l2_entry, 0x0, sizeof(rtk_l2_ucastAddr_t));

                        l2_entry.port = EXT_PORT0;
                        l2_entry.ivl = 1;
                        l2_entry.cvid = 1;
                        l2_entry.is_static = 1;
                        rtk_l2_addr_add(&mac_addr, &l2_entry);
                        return;
                }
        }

        schedule_delayed_work(&priv->switch_work,
                              msecs_to_jiffies(SWITCH_WORK_DELAY));
}

/*!<检查phy id是否一致  */
static int
rtl_probe(struct phy_device *pdev)
{
    rtk_uint32 phy_id = 0;
    rtk_uint32 value = 0;

    DBGINFO("start, dev id %#x, drv id %#x\r\n", pdev->phy_id, pdev->drv->phy_id);
    if (pdev->phy_id == pdev->drv->phy_id)
        return 0;
    else 
        return -ENODATA;
}

static int
rtl8367s_config_init(struct phy_device *pdev)
{
        struct rtl8367s_priv *priv = pdev->priv;
        struct net_device *dev = pdev->attached_dev;
        struct switch_dev *swdev;
        int ret;

        DBGINFO("start");

        if (!priv) {
                priv = kzalloc(sizeof(struct rtl8367s_priv), GFP_KERNEL);
                if (priv == NULL)
                        return -ENOMEM;
        }

        priv->phy = pdev;

        pdev->priv = priv;
        pdev->supported |= SUPPORTED_1000baseT_Full | SUPPORTED_Pause;
        pdev->advertising = pdev->supported;

        swdev = &priv->dev;
        swdev->cpu_port = RTL8367S_PORT_CPU;
        swdev->ops = &rtl8367s_sw_ops;
        swdev->ports = RTL8367S_MAX_PORTS;
        swdev->name = "Realtek 8367S";
        swdev->id = CHIP_RTL8367C;
        swdev->vlans = RTL8367S_MAX_VLANS;

        INIT_DELAYED_WORK(&priv->switch_work, switch_work_func);

        ret = register_switch(&priv->dev, pdev->attached_dev);
        if (ret)
                goto err_free_priv;

        ret = rtl8367s_sw_reset_switch(&priv->dev);
        if (ret)
                goto err_free_priv;

        dev->phy_ptr = priv;

        //rtk_switch_init();
        rtk_port_phyEnableAll_set(ENABLED);

        rtk_vlan_init();

        schedule_delayed_work(&priv->switch_work,
                      msecs_to_jiffies(SWITCH_WORK_DELAY));
        return 0;

err_free_priv:
        kfree(priv);
        return ret;
}

static int rtl8367s_get_vlan_dev(struct phy_device *phydev, int vlanID)
{
        struct rtl8367s_priv *priv = phydev->priv;
        uint8_t  name[32] = {0};

        DBGINFO("start");
        sprintf(name, "%s.%d\0", phydev->attached_dev->name, vlanID);
        priv->vlan_dev[vlanID] = dev_get_by_name(&init_net, name);
        if(priv->vlan_dev[vlanID] != NULL){
                dev_put(priv->vlan_dev[vlanID]);
                return 1;
        }

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

//      DBGINFO("new port status=%x", port_status);

        if((priv->old_port_status ^ port_status) != 0) {
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


static void
rtl8367s_remove(struct phy_device *pdev)
{
        struct rtl8367s_priv *priv = pdev->priv;
        struct net_device *dev = pdev->attached_dev;

        DBGINFO("start");

        if (!priv)
                return;

        dev->priv_flags &= ~IFF_NO_IP_ALIGN;

        unregister_switch(&priv->dev);
        cancel_delayed_work(&priv->switch_work);

        kfree(priv);
}

static struct phy_driver rtl8367s_driver = {
        .phy_id         = 0x001cc942,
        .name           = "Realtek 8367S",
        .phy_id_mask    = 0xffffffff,
        .features       = PHY_BASIC_FEATURES,
        .probe          = rtl_probe,
        .remove         = rtl8367s_remove,
        .config_init    = &rtl8367s_config_init,
        .config_aneg    = &rtl8367s_config_aneg,
        .read_status    = &rtl8367s_read_status,
        .driver         = { .owner = THIS_MODULE },
};

#define RTL8367_CHIP_RESET_REG			0x1322
#define   RTL8367_GPHY_RESET_SW			BIT(6)
#define   RTL8367_SDES_RESET_SW			BIT(3)
#define   RTL8367_CHIP_RESET_SW			BIT(1)
#define   RTL8367_CHIP_RESET_HW			BIT(0)
#define RTL8367_RESET_DELAY	1000	/* msecs*/
static int rtl8367c_reset_chip(void)
{
	int timeout = 10;
	int err;
	u32 data;
	u32 rst = RTL8367_CHIP_RESET_SW | RTL8367_SDES_RESET_SW | RTL8367_GPHY_RESET_SW;

    /*!<
        因为 chip_reset 会导致 led blinking ，不符合产品需求，因此我最终会使用 sw_reset + phy_reset 方式。
    */
	rtl8367c_setAsicReg(RTL8367_CHIP_RESET_REG, rst);
	msleep(RTL8367_RESET_DELAY);

	do {
		rtl8367c_getAsicReg(RTL8367_CHIP_RESET_REG, &data);
		if (!(data & rst))
			break;

		msleep(1);
	} while (--timeout);

	if (!timeout) {
		printk("ERROR: chip reset timed out\n");
		return -ETIMEDOUT;
	}

	return 0;
}

static int
rtl8370mb_config_init(struct phy_device *pdev)
{
        struct rtl8367s_priv *priv = pdev->priv;
        struct net_device *dev = pdev->attached_dev;
        struct switch_dev *swdev;
        int ret;

        printk("=======>>>>>>>>rtl8370mb_config_init\r\n");
        ret = rtl8367c_reset_chip();
        if (ret != 0) return ret;
        rtk_switch_init();

        if (!priv) {
                priv = kzalloc(sizeof(struct rtl8367s_priv), GFP_KERNEL);
                if (priv == NULL)
                        return -ENOMEM;
        }

        priv->phy = pdev;

        pdev->priv = priv;
        pdev->supported |= SUPPORTED_1000baseT_Full | SUPPORTED_Pause;
        pdev->advertising = pdev->supported;

        swdev = &priv->dev;
        swdev->cpu_port = RTL8370MB_PORT_CPU;
        swdev->ops = &rtl8367s_sw_ops;
        swdev->ports = RTL8370MB_MAX_PORTS;
        swdev->name = "Realtek 8370MB";
        swdev->id = CHIP_RTL8370B;
        swdev->vlans = RTL8367S_MAX_VLANS;

        INIT_DELAYED_WORK(&priv->switch_work, switch_work_func);

        ret = register_switch(&priv->dev, pdev->attached_dev);
        if (ret)
        {
                DBGINFO("register switch failed.\r\n");
                goto err_free_priv;
        }
        DBGINFO("register switch done.\r\n");

        ret = rtl8367s_sw_reset_switch(&priv->dev);
        if (ret)
                goto err_free_priv;

        dev->phy_ptr = priv;

        rtk_vlan_init();
        //rtk_port_phyEnableAll_set(ENABLED);
		
		void __iomem *base = NULL;    
        base = ioremap(AR71XX_MII_BASE, AR71XX_MII_SIZE);       
        if (base) {             
                __raw_writel(0x1b838116,base + 0x18);
        }       
        iounmap(base);
        msleep(1000);

        schedule_delayed_work(&priv->switch_work,
                      msecs_to_jiffies(SWITCH_WORK_DELAY));
        return 0;

err_free_priv:
        kfree(priv);
        return ret;
}

static int rtl8370mb_get_vlan_dev(struct phy_device *phydev, int vlanID)
{
        struct rtl8367s_priv *priv = phydev->priv;
        uint8_t  name[32] = {0};

        DBGINFO("start");
        sprintf(name, "%s.%d\0", phydev->attached_dev->name, vlanID);
        priv->vlan_dev[vlanID] = dev_get_by_name(&init_net, name);
        if(priv->vlan_dev[vlanID] != NULL){
                dev_put(priv->vlan_dev[vlanID]);
                return 1;
        }

        return 0;
}

static int
rtl8370mb_read_status(struct phy_device *phydev)
{
        int data, speed;
        struct rtl8367s_priv *priv = phydev->priv;
        struct switch_dev *dev;
        int ret = 0;
        int i, port_status = 0;
        rtk_port_mac_ability_t portStatus;

        dev = (struct switch_dev *)priv;
        for(i = UTP_PORT0; i <= UTP_PORT7; i++) {
                rtk_port_macStatus_get(i, &portStatus);
                if(portStatus.link)
                        port_status |= 1 << i;
        }

    	/*!<port9  */
    	data = phydev->bus->read(phydev->bus, 5, 0x1a);
    	/*!<linkup  */
    	if (data & 0x4)
    	{
    	    static int curspeed = PORT_SPEED_1000M;
            port_status |= (1 << 9);
            speed = ((data & 0x30)>> 4);
            /*!<速率变化要更新RGMII接口速率  */
            if (speed != curspeed)
            {
	            rtk_port_mac_ability_t mac_ability = {0};
	            curspeed = speed;
            	mac_ability.duplex = 1;
            	mac_ability.forcemode = 1;
            	mac_ability.speed = speed;
            	mac_ability.link = 1;
            	mac_ability.rxpause = 1;
            	mac_ability.txpause = 1;
            	mac_ability.nway = 0;
                rtk_port_macForceLinkExt_set(EXT_PORT1, MODE_EXT_RGMII, &mac_ability);
            }
         }

        DBGINFO("new port status=%x", port_status);

        if((priv->old_port_status ^ port_status) != 0) {
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
rtl8370mb_config_aneg(struct phy_device *phydev)
{
        DBGINFO("start");
        return genphy_config_aneg(phydev);
}

static void
rtl8370mb_remove(struct phy_device *pdev)
{
        struct rtl8367s_priv *priv = pdev->priv;
        struct net_device *dev = pdev->attached_dev;

        DBGINFO("start");

        if (!priv)
                return;

        dev->priv_flags &= ~IFF_NO_IP_ALIGN;

        unregister_switch(&priv->dev);
        cancel_delayed_work(&priv->switch_work);

        kfree(priv);
}

static struct phy_driver rtl8370mb_driver = {
        .phy_id         = 0x001cc982,
        .name           = "Realtek 8370MB",
        .phy_id_mask    = 0xffffffff,
        .features       = PHY_BASIC_FEATURES,
        .probe          = rtl_probe,
        .remove         = rtl8370mb_remove,
        .config_init    = &rtl8370mb_config_init,
        .config_aneg    = &rtl8370mb_config_aneg,
        .read_status    = &rtl8370mb_read_status,
        .driver         = { .owner = THIS_MODULE },
};

static int
rtl8211f_remove(struct phy_device *pdev)
{
        DBGINFO("start");
        return 0;
}
static int
rtl8211f_config_init(struct phy_device *pdev)
{
    int data;

	/*!<enable port9  */
	data = pdev->bus->read(pdev->bus, pdev->addr, 0);
    DBGINFO("start, data %#x, addr %d, phyid %d\r\n", data, pdev->addr, pdev->phy_id);
	data &= ~(1 << 11);
	data |= (1 << 8);
	pdev->bus->write(pdev->bus, pdev->addr, 0, data);
	/*!<port 9 LED由PHY驱动  */
	pdev->bus->write(pdev->bus, pdev->addr, 0x1f, 0xd04);
	data = pdev->bus->read(pdev->bus, pdev->addr, 0x10);
	pdev->bus->write(pdev->bus, pdev->addr, 0x10, data | 0xb);
	pdev->bus->write(pdev->bus, pdev->addr, 0x1f, 0);

    return 0;
}

static struct phy_driver rtl8211f_driver = {
        .phy_id         = 0x001cc916,
        .name           = "Realtek 8211F",
        .phy_id_mask    = 0xffffffff,
        .features       = PHY_BASIC_FEATURES,
        .probe          = rtl_probe,
        .remove         = rtl8211f_remove,
        .config_init    = &rtl8211f_config_init,
        .driver         = { .owner = THIS_MODULE },
};

int /*__init*/
rtl8367s_init(void)
{
        DBGINFO("start");
//        phy_driver_register(&rtl8367s_driver);
        phy_driver_register(&rtl8370mb_driver);
        phy_driver_register(&rtl8211f_driver);

        return 0;
}

void /*__exit*/
rtl8367s_exit(void)
{
        DBGINFO("start");
//        phy_driver_unregister(&rtl8367s_driver);
        phy_driver_unregister(&rtl8370mb_driver);
        phy_driver_unregister(&rtl8211f_driver);
}


