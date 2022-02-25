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
#include <linux/workqueue.h>
#include <linux/if_vlan.h>

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

#if defined (CONFIG_RALINK_MT7628)
#include "ra_switch_mt7628.h"
#endif

#if defined (CONFIG_RA_HW_NAT) || defined (CONFIG_RA_HW_NAT_MODULE)
#include "../../../net/nat/hw_nat/ra_nat.h"
#endif

#define MT7628_NUM_PORTS        7
#define MT7628_PORT_CPU         6
#define MT7628_MAX_VLAN         4095    /* 有效的vlan值范围：1～4094  */
#define MT7628_SUPP_VLAN_NUM    16
#define MT7628_PHY_PORT_NUM     5       /* 物理端口数目 */
#define MT7628_PORT_LINK_OFFSET 25      /* phy port link状态在寄存器0x0080中的偏置 */
#define MT7628_DEV_PREX         "eth0"
#define MT7628_CARRIER_OFF_NUM  10      /* carrier off 事件平滑次数 */
#define MT7628_CARRIER_ON_NUM   3       /* carrier on 事件平滑次数 */

#define BITM(_count)	(BIT(_count) - 1)
#define BITS(_shift, _count)	(BITM(_count) << _shift)

#define _ESW_REG(x)	(*((volatile u32 *)(RALINK_ETH_SW_BASE + x)))

#define GET_BIT_OF(value, bit)	(((value) & (1 << (bit))) >> (bit))
#define SET_BIT_OF(value, bit)	((value) |= (1 << (bit)))
#define CLEAR_BIT_OF(value, bit)	((value) &= (~(1 << (bit))))

#define MT7628_REG_OP_FLUSH 0x1
#define MT7628_REG_OP_LOAD 0x2

#define SWITCH_WORK_DELAY 2000 /* 2000ms */

//#define MT_DBG(fmt, ...) printk("MT7628 %s(%d): " fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
#define MT_DBG(fmt, args...)

struct mt7628_data {
	char buf[32];
	struct switch_dev dev;
	/* all fields below are cleared on reset */
	u16 vlan_id[MT7628_SUPP_VLAN_NUM];    /*初始为无效值0*/
	u8 vlan_table[MT7628_SUPP_VLAN_NUM];  /*用于存放vlan对应的member*/
	u8 vlan_tagged[MT7628_SUPP_VLAN_NUM]; /*用于标识每个member是否打tag*/
	u16 pvid[MT7628_NUM_PORTS];           /*初始值为无效值0*/
	bool vlan;                            /*强制支持vlan，该值暂时不用*/

	struct delayed_work switch_work;      /*用于周期检测端口的carrier状态*/
	struct net_device *vlan_dev[MT7628_SUPP_VLAN_NUM];
	u8 vlan_carrier_off_cnt[MT7628_SUPP_VLAN_NUM]; /*统计每个vlan设备连续carrier off的次数*/
	u8 vlan_carrier_on_cnt[MT7628_SUPP_VLAN_NUM];  /*统计每个vlan设备连续carrier on的次数*/
	u32 old_port_status;
};

#define to_mt7628(_dev) container_of(_dev, struct mt7628_data, dev)

static struct mt7628_data *mt7628 = NULL;
static int mt7628_carrier_check = 0;

/* 通过vlan_id值来获取该vlan_id在mt7628->vlan_id数组的下标，找不到，返回-1 
   如果传入的vlan_id为0，则用于查找一个未被使用的空闲位置 */
static int mt7628_get_index_by_vlan_id(u16 vlan_id)
{
	int i = 0;

	if(mt7628 == NULL)
	{
		return -1;
	}

	for(i = 0; i < MT7628_SUPP_VLAN_NUM; i++)
	{
		if(mt7628->vlan_id[i] == vlan_id)
		{
			return i;
		}
	}

	return -1;
}


static int mt7628_get_phy_reg_val(struct switch_dev *dev, int phy_index, struct switch_val *val)
{
	struct mt7628_data *mt = to_mt7628(dev);
	unsigned int reg = 0;
	u32 getValue = 0;
	char *buf = mt->buf;
	
	sscanf(val->value.s, "%x", &reg);
	
	mii_mgr_read(phy_index, reg, &getValue);
	
	val->len = snprintf(buf, sizeof(mt->buf), "%x", getValue);
	val->value.s = buf;
	
	return 0;
}

static int mt7628_set_phy_reg_val(struct switch_dev *dev, int phy_index, struct switch_val *val)
{
	unsigned int reg = 0;
	unsigned int value = 0;

	sscanf(val->value.s, "%x-%x", &reg, &value);
	
	mii_mgr_write(phy_index, reg, value);

	return 0;
}

static int mt7628_sw_get_reg_val(struct switch_dev *dev, int reg, int *val)
{
	*val = _ESW_REG(reg);
	return 0;
}

static void mt7628_sw_set_reg_val(struct switch_dev *dev, int reg, int val)
{
	_ESW_REG(reg) = val;
}

static void mt7628sw_enable_port(struct mt7628_data *mt, unsigned port)
{
	unsigned int regValue = 0;
	
	mii_mgr_read(port, 0x0 ,&regValue);
	regValue &= (~(0x1 << 11));
	mii_mgr_write(port, 0x0, regValue);
}

static void mt7628sw_disable_port(struct mt7628_data *mt, unsigned port)
{
	unsigned int regValue = 0;
	
	mii_mgr_read(port, 0x0 ,&regValue);
	regValue |= (0x1 << 11);
	mii_mgr_write(port, 0x0, regValue);
}

/* 当前并没有用到set vid 和 get vid两个操作 */
static int
mt7628_set_vid(struct switch_dev *dev, const struct switch_attr *attr,
		struct switch_val *val)
{
	int ret = 0;
	struct mt7628_data *mt = to_mt7628(dev);

	MT_DBG("set vid(%d)", val->value.i);

	/* 该vlan未设置过 */
	if(mt7628_get_index_by_vlan_id(val->value.i) < 0)
	{
		/*找一个空闲的位置保存*/
		if((ret = mt7628_get_index_by_vlan_id(0)) >= 0)
		{
			mt->vlan_id[ret] = val->value.i;
			MT_DBG("put vid(%d) into index(%d)", val->value.i, ret);
		}
		else  /*vlan条目已满*/
		{
			MT_DBG("set vid(%d) fail due to vlan_id table full");
			return -1;
		}
	}

	/*已保存过*/
	return 0;
}

static int
mt7628_get_vid(struct switch_dev *dev, const struct switch_attr *attr,
		struct switch_val *val)
{
	val->value.i = val->port_vlan;

	return 0;
}

static int
mt7628_set_pvid(struct switch_dev *dev, int port, int vlan)
{
	struct mt7628_data *mt = to_mt7628(dev);

	MT_DBG("set port(%d) pvid(%d)", port, vlan);

	if (vlan >= dev->vlans)
		return -EINVAL;

	mt->pvid[port] = vlan;
	
	return 0;
}

static int
mt7628_get_pvid(struct switch_dev *dev, int port, int *vlan)
{
	struct mt7628_data *mt = to_mt7628(dev);
	*vlan = mt->pvid[port];
	
	return 0;
}

static int
mt7628_get_ports(struct switch_dev *dev, struct switch_val *val)
{
	struct mt7628_data *mt = to_mt7628(dev);
	u8 ports = 0;
	int ret = 0;
	int i;

	/* 找到该vlan存放的位置 */
	if((ret = mt7628_get_index_by_vlan_id(val->port_vlan)) < 0)
	{
		MT_DBG("vlan(%d) is not exist ", val->port_vlan);
		return -1;
	}

	ports = mt->vlan_table[ret];
	val->len = 0;

	for (i = 0; i < mt->dev.ports; i++) 
	{
		struct switch_port *p;

		if (!(ports & (1 << i)))
			continue;

		p = &val->value.ports[val->len++];
		p->id = i;
		if (mt->vlan_tagged[ret] & (1 << i))
			p->flags = (1 << SWITCH_PORT_FLAG_TAGGED);
		else
			p->flags = 0;
	}
	return 0;
}

static int
mt7628_set_ports(struct switch_dev *dev, struct switch_val *val)
{
	struct mt7628_data *mt = to_mt7628(dev);
	u8 *vt = NULL;
	int ret = 0;
	int i = 0;

	MT_DBG("set vlan(%d) ports", val->port_vlan);

	/* 找到该vlan存放的位置 */
	if((ret = mt7628_get_index_by_vlan_id(val->port_vlan)) < 0)
	{
		/*MT_DBG("vlan(%d) is not exist ", val->port_vlan);*/

		/* 找一个空闲的位置保存lan(由于当前set vid操作不会执行，所以，通过set ports来保存vlan) */
		if((ret = mt7628_get_index_by_vlan_id(0)) >= 0)
		{
			mt->vlan_id[ret] = val->port_vlan;
			MT_DBG("put vid(%d) into index(%d)", val->port_vlan, ret);
		}
		else  /*vlan条目已满*/
		{
			MT_DBG("set vid(%d) fail due to vlan_id table full");
			return -1;
		}
	}

	vt = &mt->vlan_table[ret];
	*vt = 0;

	for (i = 0; i < val->len; i++) 
	{
		struct switch_port *p = &val->value.ports[i];

		if (p->flags & (1 << SWITCH_PORT_FLAG_TAGGED))
		{
			mt->vlan_tagged[ret] |= (1 << p->id);
		}
		else
		{
			mt->vlan_tagged[ret] &= ~(1 << p->id);
		}

		*vt |= 1 << p->id;
	}
	
	return 0;
}

static int
mt7628_set_vlan(struct switch_dev *dev, const struct switch_attr *attr,
		struct switch_val *val)
{
	struct mt7628_data *mt = to_mt7628(dev);

	mt->vlan = !!val->value.i;
	return 0;
}

static int
mt7628_get_vlan(struct switch_dev *dev, const struct switch_attr *attr,
		struct switch_val *val)
{
	struct mt7628_data *mt = to_mt7628(dev);
	val->value.i = mt->vlan;
	return 0;
}

static int
mt7628_set_max_frame_size(struct switch_dev *dev, const struct switch_attr *attr,
		struct switch_val *val)
{
	return 0;
}

static int
mt7628_get_max_frame_size(struct switch_dev *dev, const struct switch_attr *attr,
		struct switch_val *val)
{
	val->value.i = 0;
	return 0;
}


static void
mt7628_vtu_op(struct mt7628_data *mt, u32 op)
{
	u32 addr = 0;
	u32 value = 0;
	u32 shift_val = 0;
	int i = 0;
	
	if (MT7628_REG_OP_FLUSH & op)
	{
		MT_DBG("fluash vlan_id/member/pvid/untag registers.");
		for (i = 0; i < 4; i++)
		{
			_ESW_REG(MT_7628_VLAN_MEM_REG_ADDR_0 + i * 4) = 0;
		}

		for (i = 0; i < 8; i++)
		{
			_ESW_REG(MT_7628_VLAN_ID_REG_ADDR_0 + i * 4) = 0;
		}

		for (i = 0; i < 4; i++)
		{
			if(i == 3)
			{
				value = _ESW_REG(MT_7628_PVID_REG_ADDR_0 + i * 4);
				_ESW_REG(MT_7628_PVID_REG_ADDR_0 + i * 4) = (value & 0xfffff000);
			}
			else
			{
				_ESW_REG(MT_7628_PVID_REG_ADDR_0 + i * 4) = 0;
			}
		}

		for (i = 0; i < 4; i++)
		{
			/*缺省都打tag*/
			_ESW_REG(MT_7628_UNTAG_REG_ADDR_0 + i * 4) = 0;
		}		
	}

	if (MT7628_REG_OP_LOAD & op)
	{
		/* 使用MT_7628_UNTAG_REG_ADDR_0对vlan进行打tag */
		value = _ESW_REG(MT_7628_PORT_CTRL_2_ADDR);
		_ESW_REG(MT_7628_PORT_CTRL_2_ADDR) = (value | 0x00008000);

		MT_DBG("load vlan_id/member/pvid/untag to registers.");

		for(i = 0; i < MT7628_SUPP_VLAN_NUM; i++)
		{
			if(mt->vlan_id[i] == 0)
			{
				continue;
			}

			/* 设置vlan id */
			addr = MT_7628_VLAN_ID_REG_ADDR_0 + (i / 2) * 4;
			value = _ESW_REG(addr);
			shift_val = ((i % 2) * 12);
			_ESW_REG(addr) = ((mt->vlan_id[i] << shift_val) | (value & (~(0xfff << shift_val))));

			/* 设置vlan对应的member */
			addr = MT_7628_VLAN_MEM_REG_ADDR_0 + (i / 4) * 4;
			value = _ESW_REG(addr);
			shift_val = ((i % 4) * 8);
			_ESW_REG(addr) = ((mt->vlan_table[i] << shift_val) | (value & (~(0xff << shift_val))));

			/* 设置每个member对应的tag */
			addr = MT_7628_UNTAG_REG_ADDR_0 + (i / 4) * 4;
			value = _ESW_REG(addr);
			shift_val = ((i % 4) * 7);
			_ESW_REG(addr) = ((~mt->vlan_tagged[i] << shift_val) | (value & (~(0x7f << shift_val))));

		}

		for(i = 0; i < mt->dev.ports; i++)
		{
			if(mt->pvid[i] == 0)
			{
				continue;
			}

			/* 设置PVID */
			addr = MT_7628_PVID_REG_ADDR_0 + (i / 2) * 4;
			value = _ESW_REG(addr);
			shift_val = ((i % 2) * 12);
			_ESW_REG(addr) = ((mt->pvid[i] << shift_val) | (value & (~(0xfff << shift_val))));
		}
	}
}

static int
mt7628_hw_apply(struct switch_dev *dev)
{
	struct mt7628_data *mt = to_mt7628(dev);

	/* 清空vlan、member、PVID、untag寄存器 */
	mt7628_vtu_op(mt, MT7628_REG_OP_FLUSH);

	/* 加载配置数据到清空vlan、member、PVID、untag寄存器 */
	mt7628_vtu_op(mt, MT7628_REG_OP_LOAD);

	return 0;
}

static int
mt7628_reset_switch(struct switch_dev *dev)
{
	struct mt7628_data *mt = to_mt7628(dev);

	MT_DBG("switch reset");

	/* Wait for transmit queues to drain. */
	msleep(2);

	/* Reset the switch. */
	_ESW_REG(MT_7628_RESET_ADDR) = 1;

	memset(mt->vlan_id, 0, sizeof(u16) * MT7628_SUPP_VLAN_NUM);
	memset(mt->vlan_table, 0, sizeof(u8) * MT7628_SUPP_VLAN_NUM);
	memset(mt->vlan_tagged, 0, sizeof(u8) * MT7628_SUPP_VLAN_NUM);
	memset(mt->pvid, 0, sizeof(u16) * MT7628_NUM_PORTS);
	mt->vlan=false;

	return 0;
}

static int
mt7628_get_port_link(struct switch_dev *dev, int port,
		     struct switch_port_link *link)
{
	u32 status = 0;
	int portStatisBit = 0;
	int portSpeedBit = 0;
	int portDuplexBit = 0;
	int speed = 0;

	if (port >= MT7628_NUM_PORTS)
	{
		return -EINVAL;
	}
	
	status = _ESW_REG(MT_7628_POA_ADDR);

	/* Get status */
	portStatisBit = port + MT7628_PORT_LINK_OFFSET;
	link->link = GET_BIT_OF(status, portStatisBit);

	if (!link->link)
	{
		return 0;
	}
	else
	{
		link->link = true;
	}

	/* Get duplex */
	portDuplexBit = port + 9;
	link->duplex = GET_BIT_OF(status, portDuplexBit);
	
	link->tx_flow = 0;
	link->rx_flow = 0;
	
	/* Get speed */
	if (MT7628_PORT_CPU == port)
	{
		portSpeedBit = 7;
		speed = GET_BIT_OF(status, portSpeedBit);
		portSpeedBit = 8;
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
	}
	else
	{
		portSpeedBit = port;
		speed = GET_BIT_OF(status, portSpeedBit);
		switch (speed)
		{
		case 0:
			link->speed = SWITCH_PORT_SPEED_10;
			break;
		case 1:
			link->speed = SWITCH_PORT_SPEED_100;
			break;
		}
	}

	return 0;
}

static int
mt7628_get_port_stats(struct switch_dev *dev, int port,
		      struct switch_port_stats *stats)
{
	u32 status = 0;

	if (port >= MT7628_NUM_PORTS)
	{
		return -EINVAL;
	}
	
	status = _ESW_REG(0x150+port*4);

	stats->rx_bytes = 0;
	stats->tx_bytes = status & 0xffff;

	return 0;
}

static int vlandev_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	struct net_device *dev = ptr;

	ASSERT_RTNL();

	switch (event) {
	case NETDEV_UP:
		if (is_vlan_dev(dev))
			mt7628_carrier_check = 1;
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}

static struct notifier_block vlandev_notifier = {
	.notifier_call = vlandev_event,
};

static int mt7628_get_vlan_dev(struct mt7628_data *mt, int vlan_id, struct net_device **vlan_dev)
{
	char name[32] = {0};

	sprintf(name, "%s.%d", MT7628_DEV_PREX, vlan_id);
	(*vlan_dev) = dev_get_by_name(&init_net, name);
	if((*vlan_dev) != NULL)
	{
		dev_put(*vlan_dev);
		return 1;
	}

	return 0;
}

static int
mt7628_work(struct work_struct *work)
{
	int i = 0;
	int ret = 0;
	u32 port_status = 0;
	u32 value = 0;
	struct net_device *vlan_dev = NULL;
	struct mt7628_data *mt = mt7628;

	if(mt == NULL)
	{
		return 0;
	}

	for(i = 0; i < MT7628_PHY_PORT_NUM; i++)
	{
		value = _ESW_REG(MT_7628_POA_ADDR);
		if(GET_BIT_OF(value, i + MT7628_PORT_LINK_OFFSET))
		{
			port_status |= 1 << i;
		}
	}

	/*MT_DBG("new port status=%x", port_status);*/
	//if(((mt->old_port_status ^ port_status) != 0) || mt7628_carrier_check)
	{
		//mt7628_carrier_check = 0;

		for(i = 0; i < MT7628_SUPP_VLAN_NUM; i++)
		{
			if(mt->vlan_id[i] == 0)
			{
				continue;
			}

			ret = mt7628_get_vlan_dev(mt, mt->vlan_id[i], &vlan_dev);
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
					if(mt->vlan_carrier_on_cnt[i] > MT7628_CARRIER_ON_NUM)
					{
						mt->vlan_carrier_on_cnt[i] = 0;
						MT_DBG("%s is on", vlan_dev->name);
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
					if(mt->vlan_carrier_off_cnt[i] > MT7628_CARRIER_OFF_NUM)
					{
						mt->vlan_carrier_off_cnt[i] = 0;
						MT_DBG("%s is off", vlan_dev->name);
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
	mt7628_work(work);
	schedule_delayed_work(&mt7628->switch_work, msecs_to_jiffies(SWITCH_WORK_DELAY));
}

static struct switch_attr mt7628_globals[] = {
	{
		.type = SWITCH_TYPE_INT,
		.name = "enable_vlan",
		.description = "Enable VLAN mode",
		.set = mt7628_set_vlan,
		.get = mt7628_get_vlan,
		.max = 1
	},{
		.type = SWITCH_TYPE_INT,
		.name = "max_frame_size",
		.description = "Max frame size can be received and transmitted by mac",
		.set = mt7628_set_max_frame_size,
		.get = mt7628_get_max_frame_size,
		.max = 9018
	},
};

static struct switch_attr mt7628_port[] = {
};

static struct switch_attr mt7628_vlan[] = {
	{
		.type = SWITCH_TYPE_INT,
		.name = "vid",
		.description = "VLAN ID",
		.set = mt7628_set_vid,
		.get = mt7628_get_vid,
		.max = 4094,
	},
};

static const struct switch_dev_ops mt7628_ops = {
	.attr_global = {
		.attr = mt7628_globals,
		.n_attr = ARRAY_SIZE(mt7628_globals),
	},
	.attr_port = {
		.attr = mt7628_port,
		.n_attr = ARRAY_SIZE(mt7628_port),
	},
	.attr_vlan = {
		.attr = mt7628_vlan,
		.n_attr = ARRAY_SIZE(mt7628_vlan),
	},
	.get_port_pvid = mt7628_get_pvid,
	.set_port_pvid = mt7628_set_pvid,
	.get_vlan_ports = mt7628_get_ports,
	.set_vlan_ports = mt7628_set_ports,
	.apply_config = mt7628_hw_apply,
	.reset_switch = mt7628_reset_switch,
	.get_port_link = mt7628_get_port_link,
	.get_port_stats = mt7628_get_port_stats,
	.get_reg_val = mt7628_sw_get_reg_val,
    .set_reg_val = mt7628_sw_set_reg_val,
    .get_phy_reg_val = mt7628_get_phy_reg_val,
    .set_phy_reg_val = mt7628_set_phy_reg_val,
};

int setup_switch(struct net_device *dev)
{
	struct switch_dev *swdev;
	u32 value = 0;

	mt7628 = kzalloc(sizeof(struct mt7628_data), GFP_KERNEL);
	if (!mt7628)
	{
		return -1;
	}

	memset(mt7628, 0, sizeof(struct mt7628_data));
	
	swdev = &mt7628->dev;
	
	swdev->name = "MT7628";
	swdev->ports = MT7628_NUM_PORTS;

	swdev->cpu_port = MT7628_PORT_CPU;
	swdev->vlans = MT7628_MAX_VLAN;
	swdev->ops = &mt7628_ops;

	INIT_DELAYED_WORK(&mt7628->switch_work, switch_work_func);

	if (register_switch(swdev, dev) < 0)
	{
		goto err_free;
	}

	/* 使用MT_7628_UNTAG_REG_ADDR_0对vlan进行打tag */
	value = _ESW_REG(MT_7628_PORT_CTRL_2_ADDR);
	_ESW_REG(MT_7628_PORT_CTRL_2_ADDR) = (value | 0x00008000);

	pr_info("%s: Found an %s\n", dev->name, swdev->name);

	schedule_delayed_work(&mt7628->switch_work, msecs_to_jiffies(SWITCH_WORK_DELAY));

	return 0;

err_free:
	kfree(mt7628);
	return -1;
}


