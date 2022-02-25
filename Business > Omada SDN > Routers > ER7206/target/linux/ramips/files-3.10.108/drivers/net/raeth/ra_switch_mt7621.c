/*
 *  Driver for the built-in ethernet switch of the Atheros AR7240 SoC
 *  Copyright (c) 2013 The Linux Foundation. All rights reserved.
 *  Copyright (c) 2010 Gabor Juhos <juhosg@openwrt.org>
 *  Copyright (c) 2010 Felix Fietkau <nbd@openwrt.org>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 *
 */

#include <linux/etherdevice.h>
#include <linux/list.h>
#include <linux/netdevice.h>
#include <linux/phy.h>
#include <linux/mii.h>
#include <linux/bitops.h>
#include <net/switch.h>

#include "ra2882ethreg.h"
#include "raether.h"
#include "ra_mac.h"
#include "ra_ioctl.h"
#include "ra_rfrw.h"
#ifdef CONFIG_RAETH_NETLINK
#include "ra_netlink.h"
#endif
#if defined (CONFIG_RAETH_QOS)
#include "ra_qos.h"
#endif

#if defined (CONFIG_RALINK_MT7621)
#include "ra_switch_mt7621.h"
#endif

#if defined (CONFIG_RA_HW_NAT) || defined (CONFIG_RA_HW_NAT_MODULE)
#include "../../../net/nat/hw_nat/ra_nat.h"
#endif

#define MT7621_NUM_PORTS 7
#define MT7621_PORT_CPU 6
#define MT7621_MAX_VLANS 4096
#define MT7621_PHY_MAX_PORT 4

//#define BITM(_count)	(BIT(_count) - 1)
//#define BITS(_shift, _count)	(BITM(_count) << _shift)

#define _ESW_REG(x)	(*((volatile u32 *)(RALINK_ETH_SW_BASE + x)))

#define GET_BIT_OF(value, bit)	(((value) & (1 << (bit))) >> (bit))
#define SET_BIT_OF(value, bit)	((value) |= (1 << (bit)))
#define CLEAR_BIT_OF(value, bit)	((value) &= (~(1 << (bit))))

#define MT7621_VTU_OP_FLUSH 0x1
#define MT7621_VTU_OP_LOAD 0x2

#define MT7621_DEV_PREX         "eth1"
#define MT7621_CARRIER_OFF_NUM  10      /* carrier off 事件平滑次数 */
#define MT7621_CARRIER_ON_NUM   3       /* carrier on 事件平滑次数 */
#define SWITCH_WORK_DELAY 2000 /* 2000ms */

struct mt7621_data {
	char buf[4096];
	struct switch_dev dev;
	/* all fields below are cleared on reset */
	u16 vlan_id[MT7621_MAX_VLANS];
	u8 vlan_table[MT7621_MAX_VLANS];
	u8 vlan_tagged[MT7621_MAX_VLANS];
	u16 pvid[MT7621_NUM_PORTS];
	bool vlan;
	char wan_dev_name[64];
	
	struct delayed_work switch_work;      /*用于周期检测端口的carrier状态*/
	struct net_device *vlan_dev[MT7621_MAX_VLANS];
	u8 vlan_carrier_off_cnt[MT7621_MAX_VLANS]; /*统计每个vlan设备连续carrier off的次数*/
	u8 vlan_carrier_on_cnt[MT7621_MAX_VLANS];  /*统计每个vlan设备连续carrier on的次数*/
	u32 old_port_status;
};

#define to_mt7621(_dev) container_of(_dev, struct mt7621_data, dev)

static struct mt7621_data *mt7621 = NULL;


static void IsSwitchVlanTableBusy(void)
{
	int j = 0;
	unsigned int value = 0;

	for (j = 0; j < 20; j++) {
	    mii_mgr_read(31, 0x90, &value);
	    if ((value & 0x80000000) == 0 ){ //table busy
		break;
	    }
	    udelay(70000);
	}
	if (j == 20)
	    printk("set vlan timeout value=0x%x.\n", value);
}

static int mt7621_get_phy_reg_val(struct switch_dev *dev, int phy_index, struct switch_val *val)
{
	struct mt7621_data *mt = to_mt7621(dev);
	unsigned int reg = 0;
	u32 getValue = 0;
	char *buf = mt->buf;
	
	sscanf(val->value.s, "%x", &reg);
	
	mii_mgr_read(phy_index, reg, &getValue);
	
	val->len = snprintf(buf, sizeof(mt->buf), "%x", getValue);
    val->value.s = buf;
	
	return 0;
}

static int mt7621_set_phy_reg_val(struct switch_dev *dev, int phy_index, struct switch_val *val)
{
	unsigned int reg = 0;
    unsigned int value = 0;

    sscanf(val->value.s, "%x-%x", &reg, &value);
	
	mii_mgr_write(phy_index, reg, value);

	return 0;
}

static int mt7621_sw_get_reg_val(struct switch_dev *dev, int reg, int *val)
{
	mii_mgr_read(0x1f,reg, val);
	return 0;
}

static int mt7621_sw_set_reg_val(struct switch_dev *dev, int reg, int val)
{
    mii_mgr_write(0x1f,reg, val);
    return 0;
}

#if 0
static void mt7621sw_enable_port(struct mt7621_data *mt, unsigned port)
{
	unsigned int regValue = 0;

	mii_mgr_read(port, 0x0 ,&regValue);
	regValue &= (~(0x1 << 11));
	mii_mgr_write(port, 0x0, regValue);

}

static void mt7621sw_disable_port(struct mt7621_data *mt, unsigned port)
{
	unsigned int regValue = 0;

	mii_mgr_read(port, 0x0 ,&regValue);
	regValue |= (0x1 << 11);
	mii_mgr_write(port, 0x0, regValue);

}
#endif

static void mt7621sw_setup(struct mt7621_data *mt)
{
	/* Enable CPU port, and enable mirror port */
    mii_mgr_write(0x1f,0x2604, 0x20ff0003);/*set cpuport as untag mode*/
    mii_mgr_write(0x1f,0x2610, 0x81000000);/*set cpuport as translation mode*/

}

static int mt7621sw_reset(struct mt7621_data *mt)
{
#if 0
	int i;

	/* Set all ports to disabled state. */
	for (i = 0; i < MT7621_NUM_PORTS; i++)
	{
		mt7621sw_disable_port(mt, i);
	}
#endif
	/* Wait for transmit queues to drain. */
	msleep(2);

	/* Reset the switch. */
    //mii_mgr_write(31, 0x7000, 0x3); //reset switch
    udelay(100);
	
	mt7621sw_setup(mt);
	
	memset(mt->vlan_id, 0, sizeof(u16) * MT7621_MAX_VLANS);
	memset(mt->vlan_table, 0, sizeof(u8) * MT7621_MAX_VLANS);
	memset(mt->vlan_tagged, 0, sizeof(u8) * MT7621_MAX_VLANS);
	memset(mt->pvid, 0, sizeof(u16) * MT7621_NUM_PORTS);
	mt->vlan = false;
	
	return 0;
}

static void mt7621sw_setup_port(struct mt7621_data *mt, unsigned port, u8 portmask)
{
	u32 vid;
	int addr;
	u32 status = 0;


    //set PVID
	vid = mt->pvid[port];
	addr = 0x2014 | (port<<8);
	
	/* CPU port */
	//if (MT7621_PORT_CPU == port)
	//{
	//	vid = 1;
	//}
	
	status = 0x10000 + vid;

	mii_mgr_write(31, addr, status);//set PVID
	
}

static int
mt7621_set_vid(struct switch_dev *dev, const struct switch_attr *attr,
		struct switch_val *val)
{
	struct mt7621_data *mt = to_mt7621(dev);
	mt->vlan_id[val->port_vlan] = val->value.i;
	
	return 0;
}

static int
mt7621_get_vid(struct switch_dev *dev, const struct switch_attr *attr,
		struct switch_val *val)
{
	struct mt7621_data *mt = to_mt7621(dev);
	val->value.i = mt->vlan_id[val->port_vlan];

	return 0;
}

static int
mt7621_set_pvid(struct switch_dev *dev, int port, int vlan)
{
	struct mt7621_data *mt = to_mt7621(dev);

	/* make sure no invalid PVIDs get set */

	if (vlan >= dev->vlans)
		return -EINVAL;

	mt->pvid[port] = vlan;
	
	return 0;
}

static int
mt7621_get_pvid(struct switch_dev *dev, int port, int *vlan)
{
	struct mt7621_data *mt = to_mt7621(dev);
	*vlan = mt->pvid[port];
	
	return 0;
}

static int
mt7621_get_ports(struct switch_dev *dev, struct switch_val *val)
{
	struct mt7621_data *mt = to_mt7621(dev);
	u8 ports = mt->vlan_table[val->port_vlan];
	int i;

	val->len = 0;
	for (i = 0; i < mt->dev.ports; i++) {
		struct switch_port *p;

		if (!(ports & (1 << i)))
			continue;

		p = &val->value.ports[val->len++];
		p->id = i;
		if (mt->vlan_tagged[val->port_vlan] & (1 << i))
			p->flags = (1 << SWITCH_PORT_FLAG_TAGGED);
		else
			p->flags = 0;
	}
	return 0;
}

static int
mt7621_set_ports(struct switch_dev *dev, struct switch_val *val)
{
	struct mt7621_data *mt = to_mt7621(dev);
	u8 *vt = &mt->vlan_table[val->port_vlan];
	int i;
	
	*vt = 0;
	mt->vlan_tagged[val->port_vlan] = 0;
	for (i = 0; i < val->len; i++) {
		struct switch_port *p = &val->value.ports[i];

		if (p->flags & (1 << SWITCH_PORT_FLAG_TAGGED))
			mt->vlan_tagged[val->port_vlan] |= (1 << p->id);
		else {
			mt->vlan_tagged[val->port_vlan] &= ~(1 << p->id);
			//mt->pvid[p->id] = val->port_vlan;
			
			/* make sure that an untagged port does not
			 * appear in other vlans */
			//for (j = 0; j < MT7621_MAX_VLANS; j++) {
			//	if (j == val->port_vlan)
			//		continue;
			//	mt->vlan_table[j] &= ~(1 << p->id);
			//}
		}

		*vt |= 1 << p->id;
	}
	
	return 0;
}

static int
mt7621_set_vlan(struct switch_dev *dev, const struct switch_attr *attr,
		struct switch_val *val)
{
	struct mt7621_data *mt = to_mt7621(dev);
	mt->vlan = !!val->value.i;
	return 0;
}

static int
mt7621_get_vlan(struct switch_dev *dev, const struct switch_attr *attr,
		struct switch_val *val)
{
	struct mt7621_data *mt = to_mt7621(dev);
	val->value.i = mt->vlan;
	return 0;
}

static int
mt7621_set_max_frame_size(struct switch_dev *dev, const struct switch_attr *attr,
		struct switch_val *val)
{
	return 0;
}

static int
mt7621_get_max_frame_size(struct switch_dev *dev, const struct switch_attr *attr,
		struct switch_val *val)
{
	val->value.i = 0;
	return 0;
}


static void
mt7621_vtu_op(struct mt7621_data *mt, u32 op, u16 vid, u32 val, u32 tagged)
{
	unsigned int value = 0;
	unsigned int member = 0;
	unsigned int cmd = 0;
	int i = 0;
	int reop_cnt = 0;

	printk("mt7621_vtu_op op:%d vid:%d, val:%d, tagged:%x\n", op, vid, val, tagged);
	
	if (MT7621_VTU_OP_FLUSH & op)
	{

	}
	else if (MT7621_VTU_OP_LOAD & op)
	{
reop:
        //set vlan member
        value = (val << 16); 
        value |= (1 << 30);//IVL=1
	value |= (1 << 28);//Per Vlan Egress Control
        value |= 1;//valid
        /*0x94 104f0001 prot member0~3+6(4f=01001111)*/
	//set vlan tagged
	for (i = 0; i < mt->dev.ports; i++) {
		if (tagged & (1 << i)) {
			member |= (0x2 << (i * 2));
		}
	}
        IsSwitchVlanTableBusy();
        mii_mgr_write(0x1f, 0x94, value);
	mii_mgr_write(0x1f, 0x98, member);

        cmd = (0x80001000 + vid);  //w_vid_cmd
        mii_mgr_write(0x1f, 0x90, cmd);

        IsSwitchVlanTableBusy();

	if (reop_cnt++ < 2){
		unsigned int rvalue = 0;
		unsigned int rmember = 0;

		cmd = (0x80000000 + vid);  //read_vid_cmd
		mii_mgr_write(0x1f, 0x90, cmd);
		mii_mgr_read(0x1f, 0x94, &rvalue);
		mii_mgr_read(0x1f, 0x98, &rmember);
		if ((rvalue & value) != value)
		{
			printk("retry1 value:%x, member:%x, rvalue:%x, rmember:%x\n", value, member, rvalue, rmember);
			printk("retry1 mt7621_vtu_op op:%d vid:%d, val:%d, tagged:%x\n", op, vid, val, tagged);
			goto reop;
		}
		if ((rmember & member) != member)
		{
			printk("retry2 value:%x, member:%x, rvalue:%x, rmember:%x\n", value, member, rvalue, rmember);
			printk("retry2 mt7621_vtu_op op:%d vid:%d, val:%d, tagged:%x\n", op, vid, val, tagged);
			goto reop;
		}
	}
	}
}

static int
mt7621_hw_apply(struct switch_dev *dev)
{
	struct mt7621_data *mt = to_mt7621(dev);
	u8 portmask[MT7621_NUM_PORTS];
	int i, j;
	
	/* flush all vlan translation unit entries */
	mt7621_vtu_op(mt, MT7621_VTU_OP_FLUSH, 0, 0, 0);

	memset(portmask, 0, sizeof(portmask));
	if (mt->vlan) {
		/* calculate the port destination masks and load vlans
		 * into the vlan translation unit */
		for (j = 0; j < MT7621_MAX_VLANS; j++) {
			u8 vp = mt->vlan_table[j];

			if (!vp)
				continue;

			for (i = 0; i < mt->dev.ports; i++) {
				u8 mask = (1 << i);
				if (vp & mask)
					portmask[i] |= vp & ~mask;
			}

			mt7621_vtu_op(mt, MT7621_VTU_OP_LOAD, j, mt->vlan_table[j], mt->vlan_tagged[j]);
		}
	} else {
		/* vlan disabled:
		 * isolate all ports, but connect them to the cpu port */
		for (i = 0; i < mt->dev.ports; i++) {
			if (i == MT7621_PORT_CPU)
				continue;

			portmask[i] = 1 << MT7621_PORT_CPU;
			portmask[MT7621_PORT_CPU] |= (1 << i);
		}
	}

	/* update the port destination mask registers and tag settings */
	for (i = 0; i < mt->dev.ports; i++)
	{
		mt7621sw_setup_port(mt, i, portmask[i]);
	}

	return 0;
}

static int
mt7621_reset_switch(struct switch_dev *dev)
{
	struct mt7621_data *mt = to_mt7621(dev);
	
	mt7621sw_reset(mt);
	return 0;
}

static int
mt7621_get_port_link(struct switch_dev *dev, int port,
		     struct switch_port_link *link)
{
	u32 status = 0;
	int portSpeedBit = 0;
	int speed = 0;

	if (port >= MT7621_NUM_PORTS)
	{
		return -EINVAL;
	}

    /*3008,3108,3208,3308,3408,3508,3608 for 7 ports regedits*/
	//status = _ESW_REG(0x3008 | port << 8);
    mii_mgr_read(0x1f, (0x3008 | port << 8), &status);

	/* Get status */
	link->link = GET_BIT_OF(status, 0);

	if (!link->link)
	{
		return 0;
	}
	else
	{
		link->link = true;
	}

	/* Get duplex */
	link->duplex = GET_BIT_OF(status, 1);
	
	link->tx_flow = 0;
	link->rx_flow = 0;
	

	
	portSpeedBit = 2;
	speed = GET_BIT_OF(status, portSpeedBit);
	portSpeedBit = 3;
	speed |= (GET_BIT_OF(status, portSpeedBit) << 1);
	switch (speed)
	{
	case 0:
		link->speed = SWITCH_PORT_SPEED_10;
		break;
	case 1:
		link->speed = SWITCH_PORT_SPEED_100;
		break;
	case 2:
		link->speed = SWITCH_PORT_SPEED_1000;
		break;
	}
	

	return 0;
}

static int
mt7621_get_port_stats(struct switch_dev *dev, int port,
		      struct switch_port_stats *stats)
{
	u32 status = 0;

	if (port >= MT7621_NUM_PORTS)
	{
		return -EINVAL;
	}
	
	//status = _ESW_REG(0x150+port*4);
    mii_mgr_read(0x1f, (0x150+port*4), &status);

	stats->rx_bytes = 0;
	stats->tx_bytes = status & 0xffff;

	return 0;
}

struct mib_reg {
	unsigned long reg_addr;
	char *ctrl_name;
} mib_ctrls[] = {
	{.reg_addr=0x4000, .ctrl_name="txDropPacket"},
	{.reg_addr=0x4004, .ctrl_name="txCrcPacket"},
	{.reg_addr=0x4008, .ctrl_name="txUnicastPacket"},
	{.reg_addr=0x400c, .ctrl_name="txMulticastPacket"},
	{.reg_addr=0x4010, .ctrl_name="txBroadcastPacket"},
	{.reg_addr=0x4014, .ctrl_name="txCollisionEvent"},
	{.reg_addr=0x4018, .ctrl_name="txSingleCollisionEvent"},
	{.reg_addr=0x401c, .ctrl_name="txMultipleCollisionEvent"},
	{.reg_addr=0x4020, .ctrl_name="txDeferredEvent"},
	{.reg_addr=0x4024, .ctrl_name="txLateCollisionEvent"},
	{.reg_addr=0x4028, .ctrl_name="txExcessiveCollisionEvent"},
	{.reg_addr=0x402c, .ctrl_name="txPausePacket"},
	{.reg_addr=0x4030, .ctrl_name="txPacketLenIn64byte"},
	{.reg_addr=0x4034, .ctrl_name="txPacketLenIn65byte"},
	{.reg_addr=0x4038, .ctrl_name="txPacketLenIn128byte"},
	{.reg_addr=0x403c, .ctrl_name="txPacketLenIn256byte"},
	{.reg_addr=0x4040, .ctrl_name="txPacketLenIn512byte"},
	{.reg_addr=0x4044, .ctrl_name="txPacketLenIn1024byte"},
	{.reg_addr=0x4048, .ctrl_name="txOctetCounterLowDoubleWord"},
	{.reg_addr=0x404c, .ctrl_name="txOctetCounterHighDoubleWord"},
	{.reg_addr=0x4060, .ctrl_name="rxDropPacket"},
	{.reg_addr=0x4064, .ctrl_name="rxFilteringPacket"},
	{.reg_addr=0x4068, .ctrl_name="rxUnicastPacket"},
	{.reg_addr=0x406c, .ctrl_name="rxMulticastPacket"},
	{.reg_addr=0x4070, .ctrl_name="rxBroadcastPacket"},
	{.reg_addr=0x4074, .ctrl_name="rxAlignmentErrorPacket"},
	{.reg_addr=0x4078, .ctrl_name="rxCrcErrorPacket"},
	{.reg_addr=0x407c, .ctrl_name="rxUndersizePacket"},
	{.reg_addr=0x4080, .ctrl_name="rxFragmentErrorPacket"},
	{.reg_addr=0x4084, .ctrl_name="rxOversizePacket"},
	{.reg_addr=0x4088, .ctrl_name="rxJabberErrorPacket"},
	{.reg_addr=0x408c, .ctrl_name="rxPausePacket"},
	{.reg_addr=0x4090, .ctrl_name="rxPacketLenIn64byte"},
	{.reg_addr=0x4094, .ctrl_name="rxPacketLenIn65byte"},
	{.reg_addr=0x4098, .ctrl_name="rxPacketLenIn128byte"},
	{.reg_addr=0x409c, .ctrl_name="rxPacketLenIn256byte"},
	{.reg_addr=0x40a0, .ctrl_name="rxPacketLenIn512byte"},
	{.reg_addr=0x40a4, .ctrl_name="rxPacketLenIn1024byte"},
	{.reg_addr=0x40a8, .ctrl_name="rxOctetCounterLowDoubleWord"},
	{.reg_addr=0x40ac, .ctrl_name="rxOctetCounterHighDoubleWord"},
	{.reg_addr=0x40b0, .ctrl_name="rxCtrlDropPacket"},
	{.reg_addr=0x40b4, .ctrl_name="rxIngressDropPacket"},
	{.reg_addr=0x40b8, .ctrl_name="rxAclDropPacket"},
	{.reg_addr=0x40d0, .ctrl_name="txPortMibCounterHalfFullStatus"},
	{.reg_addr=0x40d4, .ctrl_name="rxPortMibCounterHalfFullStatus"}
};

static int
mt7621_sw_get_port_mib(struct switch_dev *dev,
                       const struct switch_attr *attr,
                       struct switch_val *val)
{
	int port;
	int len = 0;
	char *buf = NULL;
	int reg_index = 0;
	u32 reg_val = 0;

	struct mt7621_data *mt = to_mt7621(dev);
	buf = mt->buf;

	port = val->port_vlan;
	memset(buf, 0, sizeof(mt->buf));
	len += snprintf(buf + len, sizeof(mt->buf) - len,
		"Port %d MIB counters\n", port);

	for (; reg_index < ARRAY_SIZE(mib_ctrls); reg_index++) {
		mii_mgr_read(0x1f, mib_ctrls[reg_index].reg_addr + (port * 0x100), &reg_val);
		len += snprintf(buf + len, sizeof(mt->buf) - len,
			"%-36s: %u\n",
			mib_ctrls[reg_index].ctrl_name,
			reg_val);
	}

	val->value.s = buf;
	val->len = len;
	return 0;
}

static int
mt7621_sw_reset_port_mib(struct switch_dev *dev,
                           const struct switch_attr *attr,
                           struct switch_val *val)
{
	int port;

	port = val->port_vlan;

	return 0;	
}

static int
mt7621_get_wan_device_name(struct switch_dev *dev, const struct switch_attr *attr, struct switch_val *val)
{
	int len = 0;
	struct mt7621_data *mt = to_mt7621(dev);;

	snprintf(mt->buf, sizeof(mt->buf), "%s", mt->wan_dev_name);
	val->value.s = mt->buf;
	val->len = len;
	return 0;
}

static int
mt7621_set_wan_device_name(struct switch_dev *dev, const struct switch_attr *attr, struct switch_val *val)
{
	struct mt7621_data *mt = to_mt7621(dev);

	snprintf(mt->wan_dev_name, sizeof(mt->wan_dev_name), "%s", val->value.s);
	return 0;
}

static struct switch_attr mt7621_globals[] = {
	{
		.type = SWITCH_TYPE_INT,
		.name = "enable_vlan",
		.description = "Enable VLAN mode",
		.set = mt7621_set_vlan,
		.get = mt7621_get_vlan,
		.max = 1
	},{
		.type = SWITCH_TYPE_INT,
		.name = "max_frame_size",
		.description = "Max frame size can be received and transmitted by mac",
		.set = mt7621_set_max_frame_size,
		.get = mt7621_get_max_frame_size,
		.max = 9018
	},
	{
		.type = SWITCH_TYPE_STRING,
		.name = "wan_dev_name",
		.description = "wan device name for hotplug monitor.",
		.set = mt7621_set_wan_device_name,
		.get = mt7621_get_wan_device_name,
	}
};

static struct switch_attr mt7621_port[] = {
        {
                .type = SWITCH_TYPE_NOVAL,
                .name = "reset_mib",
                .description = "Reset single port MIB counters",
                .set = mt7621_sw_reset_port_mib,
                .get = NULL,
        },
        {
                .type = SWITCH_TYPE_STRING,
                .name = "mib",
                .description = "Get port's MIB counters",
                .set = NULL,
                .get = mt7621_sw_get_port_mib,
        },
};

static struct switch_attr mt7621_vlan[] = {
	{
		.type = SWITCH_TYPE_INT,
		.name = "vid",
		.description = "VLAN ID",
		.set = mt7621_set_vid,
		.get = mt7621_get_vid,
		.max = 4094,
	},
};

static const struct switch_dev_ops mt7621_ops = {
	.attr_global = {
		.attr = mt7621_globals,
		.n_attr = ARRAY_SIZE(mt7621_globals),
	},
	.attr_port = {
		.attr = mt7621_port,
		.n_attr = ARRAY_SIZE(mt7621_port),
	},
	.attr_vlan = {
		.attr = mt7621_vlan,
		.n_attr = ARRAY_SIZE(mt7621_vlan),
	},
	.get_port_pvid = mt7621_get_pvid,
	.set_port_pvid = mt7621_set_pvid,
	.get_vlan_ports = mt7621_get_ports,
	.set_vlan_ports = mt7621_set_ports,
	.apply_config = mt7621_hw_apply,
	.reset_switch = mt7621_reset_switch,
	.get_port_link = mt7621_get_port_link,
	.get_port_stats = mt7621_get_port_stats,
	.get_reg_val = mt7621_sw_get_reg_val,
    .set_reg_val = mt7621_sw_set_reg_val,
    .get_phy_reg_val = mt7621_get_phy_reg_val,
    .set_phy_reg_val = mt7621_set_phy_reg_val,
};

static int mt7621_get_vlan_dev(struct mt7621_data *mt, int vlan_id, struct net_device **vlan_dev)
{
	char name[32] = {0};

	sprintf(name, "%s.%d", mt->wan_dev_name[0]?mt->wan_dev_name:MT7621_DEV_PREX, vlan_id);
	(*vlan_dev) = dev_get_by_name(&init_net, name);
	if((*vlan_dev) != NULL)
	{
		dev_put(*vlan_dev);
		return 1;
	}

	return 0;
}

static int
mt7621_work(struct work_struct *work)
{
	int i = 0;
	int ret = 0;
	u32 port_status = 0;
	u32 status = 0;
	struct net_device *vlan_dev = NULL;
	struct mt7621_data *mt = mt7621;

	if(mt == NULL)
	{
		return 0;
	}


	for(i = 0; i <= MT7621_PHY_MAX_PORT; i++)
	{
		mii_mgr_read(0x1f, (0x3008 | i << 8), &status);
		/* Get status */
		if (GET_BIT_OF(status, 0))
		{
			port_status |= 1 << i;
		}
	}

	/*MT_DBG("new port status=%x", port_status);*/
	//if(((mt->old_port_status ^ port_status) != 0) || mt7628_carrier_check)
	{
		//mt7628_carrier_check = 0;

		for(i = 1; i < MT7621_MAX_VLANS; i++)
		{
			if(mt->vlan_table[i] == 0)
			{
				continue;
			}

			ret = mt7621_get_vlan_dev(mt, i, &vlan_dev);
			if (!ret)
			{
				continue;
			}

			if((port_status & mt->vlan_table[i]) != 0)
			{
				mt->vlan_carrier_off_cnt[i] = 0;
				if(!netif_carrier_ok(vlan_dev))
				{
					mt->vlan_carrier_on_cnt[i]++;
					if(mt->vlan_carrier_on_cnt[i] > MT7621_CARRIER_ON_NUM)
					{
						mt->vlan_carrier_on_cnt[i] = 0;
						printk(KERN_ALERT"%s is on", vlan_dev->name);
						netif_carrier_on(vlan_dev);
					}
				}
				else
				{
					mt->vlan_carrier_on_cnt[i] = 0;
				}
			}
			else if((port_status & mt->vlan_table[i]) == 0)
			{
				mt->vlan_carrier_on_cnt[i] = 0;
				if(netif_carrier_ok(vlan_dev))
				{
					mt->vlan_carrier_off_cnt[i]++;
					if(mt->vlan_carrier_off_cnt[i] > MT7621_CARRIER_OFF_NUM)
					{
						mt->vlan_carrier_off_cnt[i] = 0;
						printk(KERN_ALERT"%s is off", vlan_dev->name);
						netif_carrier_off(vlan_dev);
					}
				}
				else
				{
					mt->vlan_carrier_off_cnt[i] = 0;
				}
			}
		}
	}
        //mt->old_port_status = port_status;

        return 0;
}
static void switch_work_func(struct work_struct *work)
{
	mt7621_work(work);
	schedule_delayed_work(&mt7621->switch_work, msecs_to_jiffies(SWITCH_WORK_DELAY));
}

int setup_switch_mt7621(struct net_device *dev)
{
	struct switch_dev *swdev;
	int i = 0;

	mt7621 = kzalloc(sizeof(struct mt7621_data), GFP_KERNEL);
	if (!mt7621)
	{
		return -1;
	}
	
	swdev = &mt7621->dev;
	
	swdev->name = "MT7621";
	swdev->ports = MT7621_NUM_PORTS;

	swdev->cpu_port = MT7621_PORT_CPU;
	swdev->vlans = MT7621_MAX_VLANS;
	swdev->ops = &mt7621_ops;

	INIT_DELAYED_WORK(&mt7621->switch_work, switch_work_func);

	if (register_switch(swdev, dev) < 0)
	{
		goto err_free;
	}
	
	/* initialize defaults */
	for (i = 0; i < MT7621_MAX_VLANS; i++)
	{
		mt7621->vlan_id[i] = i;
	}

	pr_info("%s: Found an %s\n", dev->name, swdev->name);
	schedule_delayed_work(&mt7621->switch_work, msecs_to_jiffies(SWITCH_WORK_DELAY));

	return 0;

err_free:
	kfree(mt7621);
	return -1;
}


