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

#define BITM(_count)	(BIT(_count) - 1)
#define BITS(_shift, _count)	(BITM(_count) << _shift)

#define _ESW_REG(x)	(*((volatile u32 *)(RALINK_ETH_SW_BASE + x)))

#define GET_BIT_OF(value, bit)	(((value) & (1 << (bit))) >> (bit))
#define SET_BIT_OF(value, bit)	((value) |= (1 << (bit)))
#define CLEAR_BIT_OF(value, bit)	((value) &= (~(1 << (bit))))

#define MT7621_VTU_OP_FLUSH 0x1
#define MT7621_VTU_OP_LOAD 0x2


struct mt7621_data {
	char buf[32];
	struct switch_dev dev;
	/* all fields below are cleared on reset */
	u16 vlan_id[MT7621_MAX_VLANS];
	u8 vlan_table[MT7621_MAX_VLANS];
	u8 vlan_tagged;
	u16 pvid[MT7621_NUM_PORTS];
	bool vlan;
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

static void mt7621_sw_set_reg_val(struct switch_dev *dev, int reg, int val)
{
    mii_mgr_write(0x1f,reg, val);
}

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

static void mt7621sw_setup(struct mt7621_data *mt)
{
	int i = 0;
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
	mt->vlan_tagged = 0;
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
	if (MT7621_PORT_CPU == port)
	{
		vid = 1;
	}
	
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
		if (mt->vlan_tagged & (1 << i))
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
	int i, j;
	
	*vt = 0;
	for (i = 0; i < val->len; i++) {
		struct switch_port *p = &val->value.ports[i];

		if (p->flags & (1 << SWITCH_PORT_FLAG_TAGGED))
			mt->vlan_tagged |= (1 << p->id);
		else {
			mt->vlan_tagged &= ~(1 << p->id);
			mt->pvid[p->id] = val->port_vlan;
			
			/* make sure that an untagged port does not
			 * appear in other vlans */
			for (j = 0; j < MT7621_MAX_VLANS; j++) {
				if (j == val->port_vlan)
					continue;
				mt->vlan_table[j] &= ~(1 << p->id);
			}
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
mt7621_vtu_op(struct mt7621_data *mt, u32 op, u16 vid, u32 val)
{
	u32 addr = 0;
	u32 member = 0;
	u32 vlaniden = 0;
    unsigned int value = 0;
	int i = 0;
    int j = 0;

    printk("mt7621_vtu_op op:%d vid:%d, val:%d\n", op, vid, val);
	
	if (MT7621_VTU_OP_FLUSH & op)
	{

	}
	else if (MT7621_VTU_OP_LOAD & op)
	{

        //set vlan member
        value = (val << 16); 
        value |= (1 << 30);//IVL=1
        value |= 1;//valid
        /*0x94 104f0001 prot member0~3+6(4f=01001111)*/
        IsSwitchVlanTableBusy();
        mii_mgr_write(0x1f, 0x94, value);

        value = (0x80001000 + vid);  //w_vid_cmd
        mii_mgr_write(0x1f, 0x90, value);

        IsSwitchVlanTableBusy();
	}
}

static int
mt7621_hw_apply(struct switch_dev *dev)
{
	struct mt7621_data *mt = to_mt7621(dev);
	u8 portmask[MT7621_NUM_PORTS];
	int i, j;
	
	/* flush all vlan translation unit entries */
	mt7621_vtu_op(mt, MT7621_VTU_OP_FLUSH, 0, 0);

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

			mt7621_vtu_op(mt, MT7621_VTU_OP_LOAD, j, mt->vlan_table[j]);
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
	int portStatisBit = 0;
	int portSpeedBit = 0;
	int portDuplexBit = 0;
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
};

static struct switch_attr mt7621_port[] = {
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

	return 0;

err_free:
	kfree(mt7621);
	return -1;
}


