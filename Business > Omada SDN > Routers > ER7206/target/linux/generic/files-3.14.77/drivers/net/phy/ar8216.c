/*
 * ar8216.c: AR8216 switch driver
 *
 * Copyright (C) 2009 Felix Fietkau <nbd@openwrt.org>
 * Copyright (C) 2011-2012 Gabor Juhos <juhosg@openwrt.org>
 * Copyright (C) 2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

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
#include <linux/ar8216_platform.h>
#include <linux/workqueue.h>
#include <linux/of_device.h>
#include <linux/leds.h>
#include <linux/gpio.h>
#include <linux/regmap.h>
#include <linux/if_vlan.h>
#include <linux/rtnetlink.h>

#include "ar8216.h"

/* size of the vlan table */
#define AR8X16_MAX_VLANS	4096
#define AR8X16_PROBE_RETRIES	10
#define AR8X16_MAX_PORTS	8

#define AR8XXX_MIB_WORK_DELAY	2000 /* msecs */

#define AR8XXX_MAX_FRAME_SIZE   9018

#define AR8XXX_CARRIER_OFF_NUM  10      /* carrier off 事件平滑次数 */
#define AR8XXX_CARRIER_ON_NUM   3       /* carrier on 事件平滑次数 */
#define AR8XXX_STABLE_NUM       30      /* 网口稳定的次数，当网口连续在1分钟内没有插拔动作时，通过检测网口的状态来判定是否进行carrier的检测 */


struct ar8xxx_priv;

#define AR8XXX_CAP_GIGE			BIT(0)
#define AR8XXX_CAP_MIB_COUNTERS		BIT(1)

enum {
	AR8XXX_VER_AR8216 = 0x01,
	AR8XXX_VER_AR8236 = 0x03,
	AR8XXX_VER_AR8316 = 0x10,
	AR8XXX_VER_AR8327 = 0x12,
	AR8XXX_VER_AR8337 = 0x13,
};

struct ar8xxx_mib_desc {
	unsigned int size;
	unsigned int offset;
	const char *name;
};

struct ar8xxx_chip {
	unsigned long caps;

	int (*hw_init)(struct ar8xxx_priv *priv);
	void (*cleanup)(struct ar8xxx_priv *priv);

	void (*init_globals)(struct ar8xxx_priv *priv);
	void (*init_port)(struct ar8xxx_priv *priv, int port);
	void (*setup_port)(struct ar8xxx_priv *priv, int port, u32 egress,
			   u32 ingress, u32 members, u32 pvid);
	u32 (*read_port_status)(struct ar8xxx_priv *priv, int port);
	int (*atu_flush)(struct ar8xxx_priv *priv);
	void (*vtu_flush)(struct ar8xxx_priv *priv);
	void (*vtu_load_vlan)(struct ar8xxx_priv *priv, u32 vid, u32 port_mask);
	int (*atu_dump)(struct ar8xxx_priv *priv);

	const struct ar8xxx_mib_desc *mib_decs;
	unsigned num_mibs;
};

enum ar8327_led_pattern {
	AR8327_LED_PATTERN_OFF = 0,
	AR8327_LED_PATTERN_BLINK,
	AR8327_LED_PATTERN_ON,
	AR8327_LED_PATTERN_RULE,
};

struct ar8327_led_entry {
	unsigned reg;
	unsigned shift;
};

struct ar8327_led {
	struct led_classdev cdev;
	struct ar8xxx_priv *sw_priv;

	char *name;
	bool active_low;
	u8 led_num;
	enum ar8327_led_mode mode;

	struct mutex mutex;
	spinlock_t lock;
	struct work_struct led_work;
	bool enable_hw_mode;
	enum ar8327_led_pattern pattern;
};

struct ar8327_data {
	u32 port0_status;
	u32 port6_status;

	struct ar8327_led **leds;
	unsigned int num_leds;
};

struct ar8xxx_priv {
	struct switch_dev dev;
	struct mii_bus *mii_bus;
	struct phy_device *phy;

	u32 (*read)(struct ar8xxx_priv *priv, int reg);
	void (*write)(struct ar8xxx_priv *priv, int reg, u32 val);
	u32 (*rmw)(struct ar8xxx_priv *priv, int reg, u32 mask, u32 val);

	int (*get_port_link)(unsigned port);

	const struct net_device_ops *ndo_old;
	struct net_device_ops ndo;
	struct mutex reg_mutex;
	u8 chip_ver;
	u8 chip_rev;
	const struct ar8xxx_chip *chip;
	union {
		struct ar8327_data ar8327;
	} chip_data;
	bool initialized;
	bool port4_phy;
	char buf[2048];

	bool init;
	bool mii_lo_first;

	struct mutex mib_lock;
	struct delayed_work mib_work;
	int mib_next_port;
	u64 *mib_stats;

	struct list_head list;
	unsigned int use_count;

	/* all fields below are cleared on reset */
	bool vlan;
	u16 vlan_id[AR8X16_MAX_VLANS];
	u8 vlan_table[AR8X16_MAX_VLANS];
	u8 vlan_tagged;
	u16 pvid[AR8X16_MAX_PORTS];

	/* mirroring */
	bool mirror_rx;
	bool mirror_tx;
	int source_port;
	int monitor_port;

	int max_frame_size;
	struct regmap *regmap;

	/* if set, the vlan interface is UP */
	u8 vlan_status[AR8X16_MAX_VLANS];
	struct net_device *vlan_dev[AR8X16_MAX_VLANS];
	u32 old_port_status;

	/*当前是2秒检测一次*/
	u8 start_carrier_cnt; /*配置之后才进行端口检测，否则启动过程中会提前把接口down掉*/
	u8 vlan_carrier_off_cnt[AR8X16_MAX_VLANS]; /*统计每个vlan设备连续carrier off的次数*/
	u8 vlan_carrier_on_cnt[AR8X16_MAX_VLANS];  /*统计每个vlan设备连续carrier on的次数*/
	u8 stable_cnt;/*网口稳定的次数*/
};

#define MIB_DESC(_s , _o, _n)	\
	{			\
		.size = (_s),	\
		.offset = (_o),	\
		.name = (_n),	\
	}

static const struct ar8xxx_mib_desc ar8216_mibs[] = {
	MIB_DESC(1, AR8216_STATS_RXBROAD, "RxBroad"),
	MIB_DESC(1, AR8216_STATS_RXPAUSE, "RxPause"),
	MIB_DESC(1, AR8216_STATS_RXMULTI, "RxMulti"),
	MIB_DESC(1, AR8216_STATS_RXFCSERR, "RxFcsErr"),
	MIB_DESC(1, AR8216_STATS_RXALIGNERR, "RxAlignErr"),
	MIB_DESC(1, AR8216_STATS_RXRUNT, "RxRunt"),
	MIB_DESC(1, AR8216_STATS_RXFRAGMENT, "RxFragment"),
	MIB_DESC(1, AR8216_STATS_RX64BYTE, "Rx64Byte"),
	MIB_DESC(1, AR8216_STATS_RX128BYTE, "Rx128Byte"),
	MIB_DESC(1, AR8216_STATS_RX256BYTE, "Rx256Byte"),
	MIB_DESC(1, AR8216_STATS_RX512BYTE, "Rx512Byte"),
	MIB_DESC(1, AR8216_STATS_RX1024BYTE, "Rx1024Byte"),
	MIB_DESC(1, AR8216_STATS_RXMAXBYTE, "RxMaxByte"),
	MIB_DESC(1, AR8216_STATS_RXTOOLONG, "RxTooLong"),
	MIB_DESC(2, AR8216_STATS_RXGOODBYTE, "RxGoodByte"),
	MIB_DESC(2, AR8216_STATS_RXBADBYTE, "RxBadByte"),
	MIB_DESC(1, AR8216_STATS_RXOVERFLOW, "RxOverFlow"),
	MIB_DESC(1, AR8216_STATS_FILTERED, "Filtered"),
	MIB_DESC(1, AR8216_STATS_TXBROAD, "TxBroad"),
	MIB_DESC(1, AR8216_STATS_TXPAUSE, "TxPause"),
	MIB_DESC(1, AR8216_STATS_TXMULTI, "TxMulti"),
	MIB_DESC(1, AR8216_STATS_TXUNDERRUN, "TxUnderRun"),
	MIB_DESC(1, AR8216_STATS_TX64BYTE, "Tx64Byte"),
	MIB_DESC(1, AR8216_STATS_TX128BYTE, "Tx128Byte"),
	MIB_DESC(1, AR8216_STATS_TX256BYTE, "Tx256Byte"),
	MIB_DESC(1, AR8216_STATS_TX512BYTE, "Tx512Byte"),
	MIB_DESC(1, AR8216_STATS_TX1024BYTE, "Tx1024Byte"),
	MIB_DESC(1, AR8216_STATS_TXMAXBYTE, "TxMaxByte"),
	MIB_DESC(1, AR8216_STATS_TXOVERSIZE, "TxOverSize"),
	MIB_DESC(2, AR8216_STATS_TXBYTE, "TxByte"),
	MIB_DESC(1, AR8216_STATS_TXCOLLISION, "TxCollision"),
	MIB_DESC(1, AR8216_STATS_TXABORTCOL, "TxAbortCol"),
	MIB_DESC(1, AR8216_STATS_TXMULTICOL, "TxMultiCol"),
	MIB_DESC(1, AR8216_STATS_TXSINGLECOL, "TxSingleCol"),
	MIB_DESC(1, AR8216_STATS_TXEXCDEFER, "TxExcDefer"),
	MIB_DESC(1, AR8216_STATS_TXDEFER, "TxDefer"),
	MIB_DESC(1, AR8216_STATS_TXLATECOL, "TxLateCol"),
};

static const struct ar8xxx_mib_desc ar8236_mibs[] = {
	MIB_DESC(1, AR8236_STATS_RXBROAD, "RxBroad"),
	MIB_DESC(1, AR8236_STATS_RXPAUSE, "RxPause"),
	MIB_DESC(1, AR8236_STATS_RXMULTI, "RxMulti"),
	MIB_DESC(1, AR8236_STATS_RXFCSERR, "RxFcsErr"),
	MIB_DESC(1, AR8236_STATS_RXALIGNERR, "RxAlignErr"),
	MIB_DESC(1, AR8236_STATS_RXRUNT, "RxRunt"),
	MIB_DESC(1, AR8236_STATS_RXFRAGMENT, "RxFragment"),
	MIB_DESC(1, AR8236_STATS_RX64BYTE, "Rx64Byte"),
	MIB_DESC(1, AR8236_STATS_RX128BYTE, "Rx128Byte"),
	MIB_DESC(1, AR8236_STATS_RX256BYTE, "Rx256Byte"),
	MIB_DESC(1, AR8236_STATS_RX512BYTE, "Rx512Byte"),
	MIB_DESC(1, AR8236_STATS_RX1024BYTE, "Rx1024Byte"),
	MIB_DESC(1, AR8236_STATS_RX1518BYTE, "Rx1518Byte"),
	MIB_DESC(1, AR8236_STATS_RXMAXBYTE, "RxMaxByte"),
	MIB_DESC(1, AR8236_STATS_RXTOOLONG, "RxTooLong"),
	MIB_DESC(2, AR8236_STATS_RXGOODBYTE, "RxGoodByte"),
	MIB_DESC(2, AR8236_STATS_RXBADBYTE, "RxBadByte"),
	MIB_DESC(1, AR8236_STATS_RXOVERFLOW, "RxOverFlow"),
	MIB_DESC(1, AR8236_STATS_FILTERED, "Filtered"),
	MIB_DESC(1, AR8236_STATS_TXBROAD, "TxBroad"),
	MIB_DESC(1, AR8236_STATS_TXPAUSE, "TxPause"),
	MIB_DESC(1, AR8236_STATS_TXMULTI, "TxMulti"),
	MIB_DESC(1, AR8236_STATS_TXUNDERRUN, "TxUnderRun"),
	MIB_DESC(1, AR8236_STATS_TX64BYTE, "Tx64Byte"),
	MIB_DESC(1, AR8236_STATS_TX128BYTE, "Tx128Byte"),
	MIB_DESC(1, AR8236_STATS_TX256BYTE, "Tx256Byte"),
	MIB_DESC(1, AR8236_STATS_TX512BYTE, "Tx512Byte"),
	MIB_DESC(1, AR8236_STATS_TX1024BYTE, "Tx1024Byte"),
	MIB_DESC(1, AR8236_STATS_TX1518BYTE, "Tx1518Byte"),
	MIB_DESC(1, AR8236_STATS_TXMAXBYTE, "TxMaxByte"),
	MIB_DESC(1, AR8236_STATS_TXOVERSIZE, "TxOverSize"),
	MIB_DESC(2, AR8236_STATS_TXBYTE, "TxByte"),
	MIB_DESC(1, AR8236_STATS_TXCOLLISION, "TxCollision"),
	MIB_DESC(1, AR8236_STATS_TXABORTCOL, "TxAbortCol"),
	MIB_DESC(1, AR8236_STATS_TXMULTICOL, "TxMultiCol"),
	MIB_DESC(1, AR8236_STATS_TXSINGLECOL, "TxSingleCol"),
	MIB_DESC(1, AR8236_STATS_TXEXCDEFER, "TxExcDefer"),
	MIB_DESC(1, AR8236_STATS_TXDEFER, "TxDefer"),
	MIB_DESC(1, AR8236_STATS_TXLATECOL, "TxLateCol"),
	MIB_DESC(1, AR8236_STATS_RXUNICAST, "RxUnicast"),
	MIB_DESC(1, AR8236_STATS_TXUNICAST, "TxUnicast"),
};

static DEFINE_MUTEX(ar8xxx_dev_list_lock);
static LIST_HEAD(ar8xxx_dev_list);

static inline struct ar8xxx_priv *
swdev_to_ar8xxx(struct switch_dev *swdev)
{
	return container_of(swdev, struct ar8xxx_priv, dev);
}

static inline bool ar8xxx_has_gige(struct ar8xxx_priv *priv)
{
	return priv->chip->caps & AR8XXX_CAP_GIGE;
}

static inline bool ar8xxx_has_mib_counters(struct ar8xxx_priv *priv)
{
	return priv->chip->caps & AR8XXX_CAP_MIB_COUNTERS;
}

static inline bool chip_is_ar8216(struct ar8xxx_priv *priv)
{
	return priv->chip_ver == AR8XXX_VER_AR8216;
}

static inline bool chip_is_ar8236(struct ar8xxx_priv *priv)
{
	return priv->chip_ver == AR8XXX_VER_AR8236;
}

static inline bool chip_is_ar8316(struct ar8xxx_priv *priv)
{
	return priv->chip_ver == AR8XXX_VER_AR8316;
}

static inline bool chip_is_ar8327(struct ar8xxx_priv *priv)
{
	return priv->chip_ver == AR8XXX_VER_AR8327;
}

static inline bool chip_is_ar8337(struct ar8xxx_priv *priv)
{
	return priv->chip_ver == AR8XXX_VER_AR8337;
}

static inline void
split_addr(u32 regaddr, u16 *r1, u16 *r2, u16 *page)
{
	regaddr >>= 1;
	*r1 = regaddr & 0x1e;

	regaddr >>= 5;
	*r2 = regaddr & 0x7;

	regaddr >>= 3;
	*page = regaddr & 0x1ff;
}

static u32
ar8xxx_mii_read(struct ar8xxx_priv *priv, int reg)
{
	struct mii_bus *bus = priv->mii_bus;
	u16 r1, r2, page;
	u16 lo, hi;

	split_addr((u32) reg, &r1, &r2, &page);

	mutex_lock(&bus->mdio_lock);

	bus->write(bus, 0x18, 0, page);
	usleep_range(1000, 2000); /* wait for the page switch to propagate */
	lo = bus->read(bus, 0x10 | r2, r1);
	hi = bus->read(bus, 0x10 | r2, r1 + 1);

	mutex_unlock(&bus->mdio_lock);

	return (hi << 16) | lo;
}

static void
ar8xxx_mii_write(struct ar8xxx_priv *priv, int reg, u32 val)
{
	struct mii_bus *bus = priv->mii_bus;
	u16 r1, r2, r3;
	u16 lo, hi;

	split_addr((u32) reg, &r1, &r2, &r3);
	lo = val & 0xffff;
	hi = (u16) (val >> 16);

	mutex_lock(&bus->mdio_lock);

	bus->write(bus, 0x18, 0, r3);
	usleep_range(1000, 2000); /* wait for the page switch to propagate */
	if (priv->mii_lo_first) {
		bus->write(bus, 0x10 | r2, r1, lo);
		bus->write(bus, 0x10 | r2, r1 + 1, hi);
	} else {
		bus->write(bus, 0x10 | r2, r1 + 1, hi);
		bus->write(bus, 0x10 | r2, r1, lo);
	}

	mutex_unlock(&bus->mdio_lock);
}

static u32
ar8xxx_mii_rmw(struct ar8xxx_priv *priv, int reg, u32 mask, u32 val)
{
	struct mii_bus *bus = priv->mii_bus;
	u16 r1, r2, page;
	u16 lo, hi;
	u32 ret;

	split_addr((u32) reg, &r1, &r2, &page);

	mutex_lock(&bus->mdio_lock);

	bus->write(bus, 0x18, 0, page);
	usleep_range(1000, 2000); /* wait for the page switch to propagate */

	lo = bus->read(bus, 0x10 | r2, r1);
	hi = bus->read(bus, 0x10 | r2, r1 + 1);

	ret = hi << 16 | lo;
	ret &= ~mask;
	ret |= val;

	lo = ret & 0xffff;
	hi = (u16) (ret >> 16);

	if (priv->mii_lo_first) {
		bus->write(bus, 0x10 | r2, r1, lo);
		bus->write(bus, 0x10 | r2, r1 + 1, hi);
	} else {
		bus->write(bus, 0x10 | r2, r1 + 1, hi);
		bus->write(bus, 0x10 | r2, r1, lo);
	}

	mutex_unlock(&bus->mdio_lock);

	return ret;
}


static void
ar8xxx_phy_dbg_write(struct ar8xxx_priv *priv, int phy_addr,
		     u16 dbg_addr, u16 dbg_data)
{
	struct mii_bus *bus = priv->mii_bus;

	mutex_lock(&bus->mdio_lock);
	bus->write(bus, phy_addr, MII_ATH_DBG_ADDR, dbg_addr);
	bus->write(bus, phy_addr, MII_ATH_DBG_DATA, dbg_data);
	mutex_unlock(&bus->mdio_lock);
}

static void
ar8xxx_phy_dbg_read(struct ar8xxx_priv *priv, int phy_addr,
		     u16 dbg_addr, u16 *dbg_data)
{
	struct mii_bus *bus = priv->mii_bus;

	mutex_lock(&bus->mdio_lock);
	bus->write(bus, phy_addr, MII_ATH_DBG_ADDR, dbg_addr);
	*dbg_data = bus->read(bus, phy_addr, MII_ATH_DBG_DATA);
	mutex_unlock(&bus->mdio_lock);
}

static void
ar8xxx_phy_mmd_write(struct ar8xxx_priv *priv, int phy_addr, u16 addr, u16 data)
{
	struct mii_bus *bus = priv->mii_bus;

	mutex_lock(&bus->mdio_lock);
	bus->write(bus, phy_addr, MII_ATH_MMD_ADDR, addr);
	bus->write(bus, phy_addr, MII_ATH_MMD_DATA, data);
	mutex_unlock(&bus->mdio_lock);
}

static inline u32
ar8xxx_rmw(struct ar8xxx_priv *priv, int reg, u32 mask, u32 val)
{
	return priv->rmw(priv, reg, mask, val);
}

static inline void
ar8xxx_reg_set(struct ar8xxx_priv *priv, int reg, u32 val)
{
	priv->rmw(priv, reg, 0, val);
}

static int
ar8xxx_reg_wait(struct ar8xxx_priv *priv, u32 reg, u32 mask, u32 val,
		unsigned timeout)
{
	int i;

	for (i = 0; i < timeout; i++) {
		u32 t;

		t = priv->read(priv, reg);
		if ((t & mask) == val)
			return 0;

		usleep_range(1000, 2000);
	}

	return -ETIMEDOUT;
}

static int
ar8xxx_mib_op(struct ar8xxx_priv *priv, u32 op)
{
	unsigned mib_func;
	int ret;

	lockdep_assert_held(&priv->mib_lock);

	if (chip_is_ar8327(priv) || chip_is_ar8337(priv))
		mib_func = AR8327_REG_MIB_FUNC;
	else
		mib_func = AR8216_REG_MIB_FUNC;

	/* Capture the hardware statistics for all ports */
	ar8xxx_rmw(priv, mib_func, AR8216_MIB_FUNC, (op << AR8216_MIB_FUNC_S));

	/* Wait for the capturing to complete. */
	ret = ar8xxx_reg_wait(priv, mib_func, AR8216_MIB_BUSY, 0, 10);
	if (ret)
		goto out;

	ret = 0;

out:
	return ret;
}

static int
ar8xxx_mib_capture(struct ar8xxx_priv *priv)
{
	return ar8xxx_mib_op(priv, AR8216_MIB_FUNC_CAPTURE);
}

static int
ar8xxx_mib_flush(struct ar8xxx_priv *priv)
{
	return ar8xxx_mib_op(priv, AR8216_MIB_FUNC_FLUSH);
}

static void
ar8xxx_mib_fetch_port_stat(struct ar8xxx_priv *priv, int port, bool flush)
{
	unsigned int base;
	u64 *mib_stats;
	int i;

	WARN_ON(port >= priv->dev.ports);

	lockdep_assert_held(&priv->mib_lock);

	if (chip_is_ar8327(priv) || chip_is_ar8337(priv))
		base = AR8327_REG_PORT_STATS_BASE(port);
	else if (chip_is_ar8236(priv) ||
		 chip_is_ar8316(priv))
		base = AR8236_REG_PORT_STATS_BASE(port);
	else
		base = AR8216_REG_PORT_STATS_BASE(port);

	mib_stats = &priv->mib_stats[port * priv->chip->num_mibs];
	for (i = 0; i < priv->chip->num_mibs; i++) {
		const struct ar8xxx_mib_desc *mib;
		u64 t;

		mib = &priv->chip->mib_decs[i];
		t = priv->read(priv, base + mib->offset);
		if (mib->size == 2) {
			u64 hi;

			hi = priv->read(priv, base + mib->offset + 4);
			t |= hi << 32;
		}

		if (flush)
			mib_stats[i] = 0;
		else
			mib_stats[i] += t;
	}
}

static void
ar8216_read_port_link(struct ar8xxx_priv *priv, int port,
		      struct switch_port_link *link)
{
	u32 status;
	u32 speed;

	memset(link, '\0', sizeof(*link));

	status = priv->chip->read_port_status(priv, port);

	link->aneg = !!(status & AR8216_PORT_STATUS_LINK_AUTO);
	if (link->aneg) {
		link->link = !!(status & AR8216_PORT_STATUS_LINK_UP);
	} else {
		link->link = true;

		if (priv->get_port_link) {
			int err;

			err = priv->get_port_link(port);
			if (err >= 0)
				link->link = !!err;
		}
	}

	if (!link->link)
		return;

	link->duplex = !!(status & AR8216_PORT_STATUS_DUPLEX);
	link->tx_flow = !!(status & AR8216_PORT_STATUS_TXFLOW);
	link->rx_flow = !!(status & AR8216_PORT_STATUS_RXFLOW);

	speed = (status & AR8216_PORT_STATUS_SPEED) >>
		 AR8216_PORT_STATUS_SPEED_S;

	switch (speed) {
	case AR8216_PORT_SPEED_10M:
		link->speed = SWITCH_PORT_SPEED_10;
		break;
	case AR8216_PORT_SPEED_100M:
		link->speed = SWITCH_PORT_SPEED_100;
		break;
	case AR8216_PORT_SPEED_1000M:
		link->speed = SWITCH_PORT_SPEED_1000;
		break;
	default:
		link->speed = SWITCH_PORT_SPEED_UNKNOWN;
		break;
	}
}

static struct sk_buff *
ar8216_mangle_tx(struct net_device *dev, struct sk_buff *skb)
{
	struct ar8xxx_priv *priv = dev->phy_ptr;
	unsigned char *buf;

	if (unlikely(!priv))
		goto error;

	if (!priv->vlan)
		goto send;

	if (unlikely(skb_headroom(skb) < 2)) {
		if (pskb_expand_head(skb, 2, 0, GFP_ATOMIC) < 0)
			goto error;
	}

	buf = skb_push(skb, 2);
	buf[0] = 0x10;
	buf[1] = 0x80;

send:
	return skb;

error:
	dev_kfree_skb_any(skb);
	return NULL;
}

static void
ar8216_mangle_rx(struct net_device *dev, struct sk_buff *skb)
{
	struct ar8xxx_priv *priv;
	unsigned char *buf;
	int port, vlan;

	priv = dev->phy_ptr;
	if (!priv)
		return;

	/* don't strip the header if vlan mode is disabled */
	if (!priv->vlan)
		return;

	/* strip header, get vlan id */
	buf = skb->data;
	skb_pull(skb, 2);

	/* check for vlan header presence */
	if ((buf[12 + 2] != 0x81) || (buf[13 + 2] != 0x00))
		return;

	port = buf[0] & 0xf;

	/* no need to fix up packets coming from a tagged source */
	if (priv->vlan_tagged & (1 << port))
		return;

	/* lookup port vid from local table, the switch passes an invalid vlan id */
	vlan = priv->vlan_id[priv->pvid[port]];

	buf[14 + 2] &= 0xf0;
	buf[14 + 2] |= vlan >> 8;
	buf[15 + 2] = vlan & 0xff;
}

static int
ar8216_wait_bit(struct ar8xxx_priv *priv, int reg, u32 mask, u32 val)
{
	int timeout = 20;
	u32 t = 0;

	while (1) {
		t = priv->read(priv, reg);
		if ((t & mask) == val)
			return 0;

		if (timeout-- <= 0)
			break;

		udelay(10);
	}

	pr_err("ar8216: timeout on reg %08x: %08x & %08x != %08x\n",
	       (unsigned int) reg, t, mask, val);
	return -ETIMEDOUT;
}

static void
ar8216_vtu_op(struct ar8xxx_priv *priv, u32 op, u32 val)
{
	if (ar8216_wait_bit(priv, AR8216_REG_VTU, AR8216_VTU_ACTIVE, 0))
		return;
	if ((op & AR8216_VTU_OP) == AR8216_VTU_OP_LOAD) {
		val &= AR8216_VTUDATA_MEMBER;
		val |= AR8216_VTUDATA_VALID;
		priv->write(priv, AR8216_REG_VTU_DATA, val);
	}
	op |= AR8216_VTU_ACTIVE;
	priv->write(priv, AR8216_REG_VTU, op);
}

static void
ar8216_vtu_flush(struct ar8xxx_priv *priv)
{
	ar8216_vtu_op(priv, AR8216_VTU_OP_FLUSH, 0);
}

static void
ar8216_vtu_load_vlan(struct ar8xxx_priv *priv, u32 vid, u32 port_mask)
{
	u32 op;

	op = AR8216_VTU_OP_LOAD | (vid << AR8216_VTU_VID_S);
	ar8216_vtu_op(priv, op, port_mask);
}

static int
ar8216_atu_flush(struct ar8xxx_priv *priv)
{
	int ret;

	ret = ar8216_wait_bit(priv, AR8216_REG_ATU, AR8216_ATU_ACTIVE, 0);
	if (!ret)
		priv->write(priv, AR8216_REG_ATU, AR8216_ATU_OP_FLUSH);

	return ret;
}

static u32
ar8216_read_port_status(struct ar8xxx_priv *priv, int port)
{
	return priv->read(priv, AR8216_REG_PORT_STATUS(port));
}

static void
ar8216_setup_port(struct ar8xxx_priv *priv, int port, u32 egress, u32 ingress,
		  u32 members, u32 pvid)
{
	u32 header;

	if (chip_is_ar8216(priv) && priv->vlan && port == AR8216_PORT_CPU)
		header = AR8216_PORT_CTRL_HEADER;
	else
		header = 0;

	ar8xxx_rmw(priv, AR8216_REG_PORT_CTRL(port),
		   AR8216_PORT_CTRL_LEARN | AR8216_PORT_CTRL_VLAN_MODE |
		   AR8216_PORT_CTRL_SINGLE_VLAN | AR8216_PORT_CTRL_STATE |
		   AR8216_PORT_CTRL_HEADER | AR8216_PORT_CTRL_LEARN_LOCK,
		   AR8216_PORT_CTRL_LEARN | header |
		   (egress << AR8216_PORT_CTRL_VLAN_MODE_S) |
		   (AR8216_PORT_STATE_FORWARD << AR8216_PORT_CTRL_STATE_S));

	ar8xxx_rmw(priv, AR8216_REG_PORT_VLAN(port),
		   AR8216_PORT_VLAN_DEST_PORTS | AR8216_PORT_VLAN_MODE |
		   AR8216_PORT_VLAN_DEFAULT_ID,
		   (members << AR8216_PORT_VLAN_DEST_PORTS_S) |
		   (ingress << AR8216_PORT_VLAN_MODE_S) |
		   (pvid << AR8216_PORT_VLAN_DEFAULT_ID_S));
}

static int
ar8216_hw_init(struct ar8xxx_priv *priv)
{
	return 0;
}

static void
ar8216_init_globals(struct ar8xxx_priv *priv)
{
	/* standard atheros magic */
	priv->write(priv, 0x38, 0xc000050e);

	ar8xxx_rmw(priv, AR8216_REG_GLOBAL_CTRL,
		   AR8216_GCTRL_MTU, 1518 + 8 + 2);
}

static void
ar8216_init_port(struct ar8xxx_priv *priv, int port)
{
	/* Enable port learning and tx */
	priv->write(priv, AR8216_REG_PORT_CTRL(port),
		AR8216_PORT_CTRL_LEARN |
		(4 << AR8216_PORT_CTRL_STATE_S));

	priv->write(priv, AR8216_REG_PORT_VLAN(port), 0);

	if (port == AR8216_PORT_CPU) {
		priv->write(priv, AR8216_REG_PORT_STATUS(port),
			AR8216_PORT_STATUS_LINK_UP |
			(ar8xxx_has_gige(priv) ?
                                AR8216_PORT_SPEED_1000M : AR8216_PORT_SPEED_100M) |
			AR8216_PORT_STATUS_TXMAC |
			AR8216_PORT_STATUS_RXMAC |
			(chip_is_ar8316(priv) ? AR8216_PORT_STATUS_RXFLOW : 0) |
			(chip_is_ar8316(priv) ? AR8216_PORT_STATUS_TXFLOW : 0) |
			AR8216_PORT_STATUS_DUPLEX);
	} else {
		priv->write(priv, AR8216_REG_PORT_STATUS(port),
			AR8216_PORT_STATUS_LINK_AUTO);
	}
}

static const struct ar8xxx_chip ar8216_chip = {
	.caps = AR8XXX_CAP_MIB_COUNTERS,

	.hw_init = ar8216_hw_init,
	.init_globals = ar8216_init_globals,
	.init_port = ar8216_init_port,
	.setup_port = ar8216_setup_port,
	.read_port_status = ar8216_read_port_status,
	.atu_flush = ar8216_atu_flush,
	.vtu_flush = ar8216_vtu_flush,
	.vtu_load_vlan = ar8216_vtu_load_vlan,

	.num_mibs = ARRAY_SIZE(ar8216_mibs),
	.mib_decs = ar8216_mibs,
};

static void
ar8236_setup_port(struct ar8xxx_priv *priv, int port, u32 egress, u32 ingress,
		  u32 members, u32 pvid)
{
	ar8xxx_rmw(priv, AR8216_REG_PORT_CTRL(port),
		   AR8216_PORT_CTRL_LEARN | AR8216_PORT_CTRL_VLAN_MODE |
		   AR8216_PORT_CTRL_SINGLE_VLAN | AR8216_PORT_CTRL_STATE |
		   AR8216_PORT_CTRL_HEADER | AR8216_PORT_CTRL_LEARN_LOCK,
		   AR8216_PORT_CTRL_LEARN |
		   (egress << AR8216_PORT_CTRL_VLAN_MODE_S) |
		   (AR8216_PORT_STATE_FORWARD << AR8216_PORT_CTRL_STATE_S));

	ar8xxx_rmw(priv, AR8236_REG_PORT_VLAN(port),
		   AR8236_PORT_VLAN_DEFAULT_ID,
		   (pvid << AR8236_PORT_VLAN_DEFAULT_ID_S));

	ar8xxx_rmw(priv, AR8236_REG_PORT_VLAN2(port),
		   AR8236_PORT_VLAN2_VLAN_MODE |
		   AR8236_PORT_VLAN2_MEMBER,
		   (ingress << AR8236_PORT_VLAN2_VLAN_MODE_S) |
		   (members << AR8236_PORT_VLAN2_MEMBER_S));
}

static int
ar8236_hw_init(struct ar8xxx_priv *priv)
{
	int i;
	struct mii_bus *bus;

	if (priv->initialized)
		return 0;

	/* Initialize the PHYs */
	bus = priv->mii_bus;
	for (i = 0; i < 5; i++) {
		mdiobus_write(bus, i, MII_ADVERTISE,
			      ADVERTISE_ALL | ADVERTISE_PAUSE_CAP |
			      ADVERTISE_PAUSE_ASYM);
		mdiobus_write(bus, i, MII_BMCR, BMCR_RESET | BMCR_ANENABLE);
	}
	msleep(1000);

	priv->initialized = true;
	return 0;
}

static void
ar8236_init_globals(struct ar8xxx_priv *priv)
{
	/* enable jumbo frames */
	ar8xxx_rmw(priv, AR8216_REG_GLOBAL_CTRL,
		   AR8316_GCTRL_MTU, 9018 + 8 + 2);

	/* Enable MIB counters */
	ar8xxx_rmw(priv, AR8216_REG_MIB_FUNC, AR8216_MIB_FUNC | AR8236_MIB_EN,
		   (AR8216_MIB_FUNC_NO_OP << AR8216_MIB_FUNC_S) |
		   AR8236_MIB_EN);
}

static const struct ar8xxx_chip ar8236_chip = {
	.caps = AR8XXX_CAP_MIB_COUNTERS,
	.hw_init = ar8236_hw_init,
	.init_globals = ar8236_init_globals,
	.init_port = ar8216_init_port,
	.setup_port = ar8236_setup_port,
	.read_port_status = ar8216_read_port_status,
	.atu_flush = ar8216_atu_flush,
	.vtu_flush = ar8216_vtu_flush,
	.vtu_load_vlan = ar8216_vtu_load_vlan,

	.num_mibs = ARRAY_SIZE(ar8236_mibs),
	.mib_decs = ar8236_mibs,
};

static int
ar8316_hw_init(struct ar8xxx_priv *priv)
{
	int i;
	u32 val, newval;
	struct mii_bus *bus;

	val = priv->read(priv, AR8316_REG_POSTRIP);

	if (priv->phy->interface == PHY_INTERFACE_MODE_RGMII) {
		if (priv->port4_phy) {
			/* value taken from Ubiquiti RouterStation Pro */
			newval = 0x81461bea;
			pr_info("ar8316: Using port 4 as PHY\n");
		} else {
			newval = 0x01261be2;
			pr_info("ar8316: Using port 4 as switch port\n");
		}
	} else if (priv->phy->interface == PHY_INTERFACE_MODE_GMII) {
		/* value taken from AVM Fritz!Box 7390 sources */
		newval = 0x010e5b71;
	} else {
		/* no known value for phy interface */
		pr_err("ar8316: unsupported mii mode: %d.\n",
		       priv->phy->interface);
		return -EINVAL;
	}

	if (val == newval)
		goto out;

	priv->write(priv, AR8316_REG_POSTRIP, newval);

	if (priv->port4_phy &&
	    priv->phy->interface == PHY_INTERFACE_MODE_RGMII) {
		/* work around for phy4 rgmii mode */
		ar8xxx_phy_dbg_write(priv, 4, 0x12, 0x480c);
		/* rx delay */
		ar8xxx_phy_dbg_write(priv, 4, 0x0, 0x824e);
		/* tx delay */
		ar8xxx_phy_dbg_write(priv, 4, 0x5, 0x3d47);
		msleep(1000);
	}

	/* Initialize the ports */
	bus = priv->mii_bus;
	for (i = 0; i < 5; i++) {
		/* initialize the port itself */
		mdiobus_write(bus, i, MII_ADVERTISE,
			ADVERTISE_ALL | ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM);
		mdiobus_write(bus, i, MII_CTRL1000, ADVERTISE_1000FULL);
		mdiobus_write(bus, i, MII_BMCR, BMCR_RESET | BMCR_ANENABLE);
	}

	msleep(1000);

out:
	priv->initialized = true;
	return 0;
}

static void
ar8316_init_globals(struct ar8xxx_priv *priv)
{
	/* standard atheros magic */
	priv->write(priv, 0x38, 0xc000050e);

	/* enable cpu port to receive multicast and broadcast frames */
	priv->write(priv, AR8216_REG_FLOOD_MASK, 0x003f003f);

	/* enable jumbo frames */
	ar8xxx_rmw(priv, AR8216_REG_GLOBAL_CTRL,
		   AR8316_GCTRL_MTU, 9018 + 8 + 2);

	/* Enable MIB counters */
	ar8xxx_rmw(priv, AR8216_REG_MIB_FUNC, AR8216_MIB_FUNC | AR8236_MIB_EN,
		   (AR8216_MIB_FUNC_NO_OP << AR8216_MIB_FUNC_S) |
		   AR8236_MIB_EN);
}

static const struct ar8xxx_chip ar8316_chip = {
	.caps = AR8XXX_CAP_GIGE | AR8XXX_CAP_MIB_COUNTERS,
	.hw_init = ar8316_hw_init,
	.init_globals = ar8316_init_globals,
	.init_port = ar8216_init_port,
	.setup_port = ar8216_setup_port,
	.read_port_status = ar8216_read_port_status,
	.atu_flush = ar8216_atu_flush,
	.vtu_flush = ar8216_vtu_flush,
	.vtu_load_vlan = ar8216_vtu_load_vlan,

	.num_mibs = ARRAY_SIZE(ar8236_mibs),
	.mib_decs = ar8236_mibs,
};

static int
ar8327_atu_dump(struct ar8xxx_priv *priv)
{
	u32 ret;
	u32 i = 0, len = 0, entry_len = 0;
	volatile u32 reg[4] = {0,0,0,0};
	u8 addr[ETH_ALEN] = { 0 };
	char *buf;

	buf = priv->buf;
	memset(priv->buf, 0, sizeof(priv->buf));
	do {
		ret = ar8216_wait_bit(priv, AR8327_REG_ATU_FUNC,
				      AR8327_ATU_FUNC_BUSY, 0);
		if(ret != 0)
			return -ETIMEDOUT;

		reg[3] = AR8327_ATU_FUNC_BUSY | AR8327_ATU_FUNC_OP_GET_NEXT;
		priv->write(priv, AR8327_REG_ATU_DATA0, reg[0]);
		priv->write(priv, AR8327_REG_ATU_DATA1, reg[1]);
		priv->write(priv, AR8327_REG_ATU_DATA2, reg[2]);
		priv->write(priv, AR8327_REG_ATU_FUNC, reg[3]);

		ret = ar8216_wait_bit(priv, AR8327_REG_ATU_FUNC,
				      AR8327_ATU_FUNC_BUSY, 0);
		if(ret != 0)
			return -ETIMEDOUT;

		reg[0] = priv->read(priv, AR8327_REG_ATU_DATA0);
		reg[1] = priv->read(priv, AR8327_REG_ATU_DATA1);
		reg[2] = priv->read(priv, AR8327_REG_ATU_DATA2);
		reg[3] = priv->read(priv, AR8327_REG_ATU_FUNC);

		if((reg[2] & 0xf) == 0)
			break;

		for(i=2; i<6; i++)
			addr[i] = (reg[0] >> ((5 - i) << 3)) & 0xff;
		for(i=0; i<2; i++)
			addr[i] = (reg[1] >> ((1 - i) << 3)) & 0xff;

		len += snprintf(buf+len, sizeof(priv->buf) - len, "MAC: %02x:%02x:%02x:%02x:%02x:%02x ",
						addr[0],addr[1],addr[2],addr[3],addr[4],addr[5]);
		len += snprintf(buf+len, sizeof(priv->buf) - len, "PORTMAP: 0x%02x\n", ((reg[1] >> 16) & 0x7f));

		reg[2] |= 0xf;

		if (!entry_len)
			entry_len = len;

		if (sizeof(priv->buf) - len <= entry_len)
			break;
	}while(1);

	return len;
}


static u32
ar8327_get_pad_cfg(struct ar8327_pad_cfg *cfg)
{
	u32 t;

	if (!cfg)
		return 0;

	t = 0;
	switch (cfg->mode) {
	case AR8327_PAD_NC:
		break;

	case AR8327_PAD_MAC2MAC_MII:
		t = AR8327_PAD_MAC_MII_EN;
		if (cfg->rxclk_sel)
			t |= AR8327_PAD_MAC_MII_RXCLK_SEL;
		if (cfg->txclk_sel)
			t |= AR8327_PAD_MAC_MII_TXCLK_SEL;
		break;

	case AR8327_PAD_MAC2MAC_GMII:
		t = AR8327_PAD_MAC_GMII_EN;
		if (cfg->rxclk_sel)
			t |= AR8327_PAD_MAC_GMII_RXCLK_SEL;
		if (cfg->txclk_sel)
			t |= AR8327_PAD_MAC_GMII_TXCLK_SEL;
		break;

	case AR8327_PAD_MAC_SGMII:
		t = AR8327_PAD_SGMII_EN;

		/*
		 * WAR for the QUalcomm Atheros AP136 board.
		 * It seems that RGMII TX/RX delay settings needs to be
		 * applied for SGMII mode as well, The ethernet is not
		 * reliable without this.
		 */
		t |= cfg->txclk_delay_sel << AR8327_PAD_RGMII_TXCLK_DELAY_SEL_S;
		t |= cfg->rxclk_delay_sel << AR8327_PAD_RGMII_RXCLK_DELAY_SEL_S;
		if (cfg->rxclk_delay_en)
			t |= AR8327_PAD_RGMII_RXCLK_DELAY_EN;
		if (cfg->txclk_delay_en)
			t |= AR8327_PAD_RGMII_TXCLK_DELAY_EN;

		if (cfg->sgmii_delay_en)
			t |= AR8327_PAD_SGMII_DELAY_EN;

		break;

	case AR8327_PAD_MAC2PHY_MII:
		t = AR8327_PAD_PHY_MII_EN;
		if (cfg->rxclk_sel)
			t |= AR8327_PAD_PHY_MII_RXCLK_SEL;
		if (cfg->txclk_sel)
			t |= AR8327_PAD_PHY_MII_TXCLK_SEL;
		break;

	case AR8327_PAD_MAC2PHY_GMII:
		t = AR8327_PAD_PHY_GMII_EN;
		if (cfg->pipe_rxclk_sel)
			t |= AR8327_PAD_PHY_GMII_PIPE_RXCLK_SEL;
		if (cfg->rxclk_sel)
			t |= AR8327_PAD_PHY_GMII_RXCLK_SEL;
		if (cfg->txclk_sel)
			t |= AR8327_PAD_PHY_GMII_TXCLK_SEL;
		break;

	case AR8327_PAD_MAC_RGMII:
		t = AR8327_PAD_RGMII_EN;
		t |= cfg->txclk_delay_sel << AR8327_PAD_RGMII_TXCLK_DELAY_SEL_S;
		t |= cfg->rxclk_delay_sel << AR8327_PAD_RGMII_RXCLK_DELAY_SEL_S;
		if (cfg->rxclk_delay_en)
			t |= AR8327_PAD_RGMII_RXCLK_DELAY_EN;
		if (cfg->txclk_delay_en)
			t |= AR8327_PAD_RGMII_TXCLK_DELAY_EN;
		break;

	case AR8327_PAD_PHY_GMII:
		t = AR8327_PAD_PHYX_GMII_EN;
		break;

	case AR8327_PAD_PHY_RGMII:
		t = AR8327_PAD_PHYX_RGMII_EN;
		break;

	case AR8327_PAD_PHY_MII:
		t = AR8327_PAD_PHYX_MII_EN;
		break;
	}

	return t;
}

static void
ar8327_phy_fixup(struct ar8xxx_priv *priv, int phy)
{
	u16 val;
	switch (priv->chip_rev) {
	case 1:
		/* For 100M waveform */
		ar8xxx_phy_dbg_write(priv, phy, 0, 0x02ea);
		/* Turn on Gigabit clock */
		ar8xxx_phy_dbg_write(priv, phy, 0x3d, 0x68a0);
		break;

	case 2:
		ar8xxx_phy_mmd_write(priv, phy, 0x7, 0x3c);
		ar8xxx_phy_mmd_write(priv, phy, 0x4007, 0x0);
		/* fallthrough */
	case 4:
		ar8xxx_phy_mmd_write(priv, phy, 0x3, 0x800d);
		ar8xxx_phy_mmd_write(priv, phy, 0x4003, 0x803f);

		ar8xxx_phy_dbg_write(priv, phy, 0x3d, 0x6860);
		ar8xxx_phy_dbg_write(priv, phy, 0x5, 0x2c46);
		ar8xxx_phy_dbg_write(priv, phy, 0x3c, 0x6000);
		ar8xxx_phy_dbg_read(priv, phy, 0, &val);
		val &= ~AR8337_PHY_MANU_CTRL_EN;
		ar8xxx_phy_dbg_write(priv, phy, 0, val);
		break;
	}
}

static u32
ar8327_get_port_init_status(struct ar8327_port_cfg *cfg)
{
	u32 t;

	if (!cfg->force_link)
		return AR8216_PORT_STATUS_LINK_AUTO;

	t = AR8216_PORT_STATUS_TXMAC | AR8216_PORT_STATUS_RXMAC;
	t |= cfg->duplex ? AR8216_PORT_STATUS_DUPLEX : 0;
	t |= cfg->rxpause ? AR8216_PORT_STATUS_RXFLOW : 0;
	t |= cfg->txpause ? AR8216_PORT_STATUS_TXFLOW : 0;

	switch (cfg->speed) {
	case AR8327_PORT_SPEED_10:
		t |= AR8216_PORT_SPEED_10M;
		break;
	case AR8327_PORT_SPEED_100:
		t |= AR8216_PORT_SPEED_100M;
		break;
	case AR8327_PORT_SPEED_1000:
		t |= AR8216_PORT_SPEED_1000M;
		break;
	}

	return t;
}

#define AR8327_LED_ENTRY(_num, _reg, _shift) \
	[_num] = { .reg = (_reg), .shift = (_shift) }

static const struct ar8327_led_entry
ar8327_led_map[AR8327_NUM_LEDS] = {
	AR8327_LED_ENTRY(AR8327_LED_PHY0_0, 0, 14),
	AR8327_LED_ENTRY(AR8327_LED_PHY0_1, 1, 14),
	AR8327_LED_ENTRY(AR8327_LED_PHY0_2, 2, 14),

	AR8327_LED_ENTRY(AR8327_LED_PHY1_0, 3, 8),
	AR8327_LED_ENTRY(AR8327_LED_PHY1_1, 3, 10),
	AR8327_LED_ENTRY(AR8327_LED_PHY1_2, 3, 12),

	AR8327_LED_ENTRY(AR8327_LED_PHY2_0, 3, 14),
	AR8327_LED_ENTRY(AR8327_LED_PHY2_1, 3, 16),
	AR8327_LED_ENTRY(AR8327_LED_PHY2_2, 3, 18),

	AR8327_LED_ENTRY(AR8327_LED_PHY3_0, 3, 20),
	AR8327_LED_ENTRY(AR8327_LED_PHY3_1, 3, 22),
	AR8327_LED_ENTRY(AR8327_LED_PHY3_2, 3, 24),

	AR8327_LED_ENTRY(AR8327_LED_PHY4_0, 0, 30),
	AR8327_LED_ENTRY(AR8327_LED_PHY4_1, 1, 30),
	AR8327_LED_ENTRY(AR8327_LED_PHY4_2, 2, 30),
};

static void
ar8327_set_led_pattern(struct ar8xxx_priv *priv, unsigned int led_num,
		       enum ar8327_led_pattern pattern)
{
	const struct ar8327_led_entry *entry;

	entry = &ar8327_led_map[led_num];
	ar8xxx_rmw(priv, AR8327_REG_LED_CTRL(entry->reg),
		   (3 << entry->shift), pattern << entry->shift);
}

static void
ar8327_led_work_func(struct work_struct *work)
{
	struct ar8327_led *aled;
	u8 pattern;

	aled = container_of(work, struct ar8327_led, led_work);

	spin_lock(&aled->lock);
	pattern = aled->pattern;
	spin_unlock(&aled->lock);

	ar8327_set_led_pattern(aled->sw_priv, aled->led_num,
			       pattern);
}

static void
ar8327_led_schedule_change(struct ar8327_led *aled, u8 pattern)
{
	if (aled->pattern == pattern)
		return;

	aled->pattern = pattern;
	schedule_work(&aled->led_work);
}

static inline struct ar8327_led *
led_cdev_to_ar8327_led(struct led_classdev *led_cdev)
{
	return container_of(led_cdev, struct ar8327_led, cdev);
}

static int
ar8327_led_blink_set(struct led_classdev *led_cdev,
		     unsigned long *delay_on,
		     unsigned long *delay_off)
{
	struct ar8327_led *aled = led_cdev_to_ar8327_led(led_cdev);

	if (*delay_on == 0 && *delay_off == 0) {
		*delay_on = 125;
		*delay_off = 125;
	}

	if (*delay_on != 125 || *delay_off != 125) {
		/*
		 * The hardware only supports blinking at 4Hz. Fall back
		 * to software implementation in other cases.
		 */
		return -EINVAL;
	}

	spin_lock(&aled->lock);

	aled->enable_hw_mode = false;
	ar8327_led_schedule_change(aled, AR8327_LED_PATTERN_BLINK);

	spin_unlock(&aled->lock);

	return 0;
}

static void
ar8327_led_set_brightness(struct led_classdev *led_cdev,
			  enum led_brightness brightness)
{
	struct ar8327_led *aled = led_cdev_to_ar8327_led(led_cdev);
	u8 pattern;
	bool active;

	active = (brightness != LED_OFF);
	active ^= aled->active_low;

	pattern = (active) ? AR8327_LED_PATTERN_ON :
			     AR8327_LED_PATTERN_OFF;

	spin_lock(&aled->lock);

	aled->enable_hw_mode = false;
	ar8327_led_schedule_change(aled, pattern);

	spin_unlock(&aled->lock);
}

static ssize_t
ar8327_led_enable_hw_mode_show(struct device *dev,
			       struct device_attribute *attr,
			       char *buf)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct ar8327_led *aled = led_cdev_to_ar8327_led(led_cdev);
	ssize_t ret = 0;

	spin_lock(&aled->lock);
	ret += sprintf(buf, "%d\n", aled->enable_hw_mode);
	spin_unlock(&aled->lock);

	return ret;
}

static ssize_t
ar8327_led_enable_hw_mode_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf,
				size_t size)
{
        struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct ar8327_led *aled = led_cdev_to_ar8327_led(led_cdev);
	u8 pattern;
	u8 value;
	int ret;

	ret = kstrtou8(buf, 10, &value);
	if (ret < 0)
		return -EINVAL;

	spin_lock(&aled->lock);

	aled->enable_hw_mode = !!value;
	if (aled->enable_hw_mode)
		pattern = AR8327_LED_PATTERN_RULE;
	else
		pattern = AR8327_LED_PATTERN_OFF;

	ar8327_led_schedule_change(aled, pattern);

	spin_unlock(&aled->lock);

	return size;
}

static DEVICE_ATTR(enable_hw_mode,  S_IRUGO | S_IWUSR,
		   ar8327_led_enable_hw_mode_show,
		   ar8327_led_enable_hw_mode_store);

static int
ar8327_led_register(struct ar8xxx_priv *priv, struct ar8327_led *aled)
{
	int ret;

	ret = led_classdev_register(NULL, &aled->cdev);
	if (ret < 0)
		return ret;

	if (aled->mode == AR8327_LED_MODE_HW) {
		ret = device_create_file(aled->cdev.dev,
					 &dev_attr_enable_hw_mode);
		if (ret)
			goto err_unregister;
	}

	return 0;

err_unregister:
	led_classdev_unregister(&aled->cdev);
	return ret;
}

static void
ar8327_led_unregister(struct ar8327_led *aled)
{
	if (aled->mode == AR8327_LED_MODE_HW)
		device_remove_file(aled->cdev.dev, &dev_attr_enable_hw_mode);

	led_classdev_unregister(&aled->cdev);
	cancel_work_sync(&aled->led_work);
}

static int
ar8327_led_create(struct ar8xxx_priv *priv,
		  const struct ar8327_led_info *led_info)
{
	struct ar8327_data *data = &priv->chip_data.ar8327;
	struct ar8327_led *aled;
	int ret;

	if (!IS_ENABLED(CONFIG_AR8216_PHY_LEDS))
		return 0;

	if (!led_info->name)
		return -EINVAL;

	if (led_info->led_num >= AR8327_NUM_LEDS)
		return -EINVAL;

	aled = kzalloc(sizeof(*aled) + strlen(led_info->name) + 1,
		       GFP_KERNEL);
	if (!aled)
		return -ENOMEM;

	aled->sw_priv = priv;
	aled->led_num = led_info->led_num;
	aled->active_low = led_info->active_low;
	aled->mode = led_info->mode;

	if (aled->mode == AR8327_LED_MODE_HW)
		aled->enable_hw_mode = true;

	aled->name = (char *)(aled + 1);
	strcpy(aled->name, led_info->name);

	aled->cdev.name = aled->name;
	aled->cdev.brightness_set = ar8327_led_set_brightness;
	aled->cdev.blink_set = ar8327_led_blink_set;
	aled->cdev.default_trigger = led_info->default_trigger;

	spin_lock_init(&aled->lock);
	mutex_init(&aled->mutex);
	INIT_WORK(&aled->led_work, ar8327_led_work_func);

	ret = ar8327_led_register(priv, aled);
	if (ret)
		goto err_free;

	data->leds[data->num_leds++] = aled;

	return 0;

err_free:
	kfree(aled);
	return ret;
}

static void
ar8327_led_destroy(struct ar8327_led *aled)
{
	ar8327_led_unregister(aled);
	kfree(aled);
}

static void
ar8327_leds_init(struct ar8xxx_priv *priv)
{
	struct ar8327_data *data;
	unsigned i;

	if (!IS_ENABLED(CONFIG_AR8216_PHY_LEDS))
		return;

	data = &priv->chip_data.ar8327;

	for (i = 0; i < data->num_leds; i++) {
		struct ar8327_led *aled;

		aled = data->leds[i];

		if (aled->enable_hw_mode)
			aled->pattern = AR8327_LED_PATTERN_RULE;
		else
			aled->pattern = AR8327_LED_PATTERN_OFF;

		ar8327_set_led_pattern(priv, aled->led_num, aled->pattern);
	}
}

static void
ar8327_leds_cleanup(struct ar8xxx_priv *priv)
{
	struct ar8327_data *data = &priv->chip_data.ar8327;
	unsigned i;

	if (!IS_ENABLED(CONFIG_AR8216_PHY_LEDS))
		return;

	for (i = 0; i < data->num_leds; i++) {
		struct ar8327_led *aled;

		aled = data->leds[i];
		ar8327_led_destroy(aled);
	}

	kfree(data->leds);
}

static int
ar8327_hw_config_pdata(struct ar8xxx_priv *priv,
		       struct ar8327_platform_data *pdata)
{
	struct ar8327_led_cfg *led_cfg;
	struct ar8327_data *data;
	u32 pos, new_pos;
	u32 t;

	if (!pdata)
		return -EINVAL;

	priv->get_port_link = pdata->get_port_link;

	data = &priv->chip_data.ar8327;

	data->port0_status = ar8327_get_port_init_status(&pdata->port0_cfg);
	data->port6_status = ar8327_get_port_init_status(&pdata->port6_cfg);

	t = ar8327_get_pad_cfg(pdata->pad0_cfg);
	if (chip_is_ar8337(priv))
		t |= AR8337_PAD_MAC06_EXCHANGE_EN;

	priv->write(priv, AR8327_REG_PAD0_MODE, t);
	t = ar8327_get_pad_cfg(pdata->pad5_cfg);
	priv->write(priv, AR8327_REG_PAD5_MODE, t);
	t = ar8327_get_pad_cfg(pdata->pad6_cfg);
	priv->write(priv, AR8327_REG_PAD6_MODE, t);

	pos = priv->read(priv, AR8327_REG_POWER_ON_STRIP);
	new_pos = pos;

	led_cfg = pdata->led_cfg;
	if (led_cfg) {
		if (led_cfg->open_drain)
			new_pos |= AR8327_POWER_ON_STRIP_LED_OPEN_EN;
		else
			new_pos &= ~AR8327_POWER_ON_STRIP_LED_OPEN_EN;

		priv->write(priv, AR8327_REG_LED_CTRL0, led_cfg->led_ctrl0);
		priv->write(priv, AR8327_REG_LED_CTRL1, led_cfg->led_ctrl1);
		priv->write(priv, AR8327_REG_LED_CTRL2, led_cfg->led_ctrl2);
		priv->write(priv, AR8327_REG_LED_CTRL3, led_cfg->led_ctrl3);

		if (new_pos != pos)
			new_pos |= AR8327_POWER_ON_STRIP_POWER_ON_SEL;
	}

	if (pdata->sgmii_cfg) {
		t = pdata->sgmii_cfg->sgmii_ctrl;
		if (priv->chip_rev == 1)
			t |= AR8327_SGMII_CTRL_EN_PLL |
			     AR8327_SGMII_CTRL_EN_RX |
			     AR8327_SGMII_CTRL_EN_TX;
		else
			t &= ~(AR8327_SGMII_CTRL_EN_PLL |
			       AR8327_SGMII_CTRL_EN_RX |
			       AR8327_SGMII_CTRL_EN_TX);

		priv->write(priv, AR8327_REG_SGMII_CTRL, t);

		if (pdata->sgmii_cfg->serdes_aen)
			new_pos &= ~AR8327_POWER_ON_STRIP_SERDES_AEN;
		else
			new_pos |= AR8327_POWER_ON_STRIP_SERDES_AEN;
	}

	priv->write(priv, AR8327_REG_POWER_ON_STRIP, new_pos);

	if (pdata->leds && pdata->num_leds) {
		int i;

		data->leds = kzalloc(pdata->num_leds * sizeof(void *),
				     GFP_KERNEL);
		if (!data->leds)
			return -ENOMEM;

		for (i = 0; i < pdata->num_leds; i++)
			ar8327_led_create(priv, &pdata->leds[i]);
	}

	return 0;
}

#ifdef CONFIG_OF
static int
ar8327_hw_config_of(struct ar8xxx_priv *priv, struct device_node *np)
{
	const __be32 *paddr;
	int len;
	int i;

	paddr = of_get_property(np, "qca,ar8327-initvals", &len);
	if (!paddr || len < (2 * sizeof(*paddr)))
		return -EINVAL;

	len /= sizeof(*paddr);

	for (i = 0; i < len - 1; i += 2) {
		u32 reg;
		u32 val;

		reg = be32_to_cpup(paddr + i);
		val = be32_to_cpup(paddr + i + 1);

		switch (reg) {
		case AR8327_REG_PORT_STATUS(0):
			priv->chip_data.ar8327.port0_status = val;
			break;
		case AR8327_REG_PORT_STATUS(6):
			priv->chip_data.ar8327.port6_status = val;
			break;
		default:
			priv->write(priv, reg, val);
			break;
		}
	}

	return 0;
}
#else
static inline int
ar8327_hw_config_of(struct ar8xxx_priv *priv, struct device_node *np)
{
	return -EINVAL;
}
#endif

static void
ar8327_port_phy_linkdown(struct ar8xxx_priv *priv, int port)
{
	struct mii_bus *bus;
	u16 val;

	bus = priv->mii_bus;

	mdiobus_write(bus, port - 1, MII_CTRL1000, 0);
	mdiobus_write(bus, port - 1, MII_ADVERTISE, 0);
	mdiobus_write(bus, port - 1, MII_BMCR, BMCR_RESET | BMCR_ANENABLE);
	ar8xxx_phy_dbg_read(priv, port - 1, AR8337_PHY_DEBUG_0, &val);
	val |= AR8337_PHY_MANU_CTRL_EN;
	ar8xxx_phy_dbg_write(priv, port - 1, AR8337_PHY_DEBUG_0, val);
	/*disable transmit*/
	ar8xxx_phy_dbg_read(priv, port - 1, AR8337_PHY_DEBUG_2, &val);
	val &= 0xf00f;
	ar8xxx_phy_dbg_write(priv, port - 1, AR8337_PHY_DEBUG_2, val);

}

static void
ar8327_phy_linkdown(struct ar8xxx_priv *priv)
{
	int i;

	for (i = 0; i < AR8327_NUM_PHYS; i++)
		ar8327_port_phy_linkdown(priv, i + 1);
}

static void
ar8327_port_phy_init(struct ar8xxx_priv *priv, int port)
{
	struct mii_bus *bus;

	bus = priv->mii_bus;
	ar8327_phy_fixup(priv, port - 1);

	/* start aneg on the PHY */
	mdiobus_write(bus, port - 1, MII_ADVERTISE, ADVERTISE_ALL |
					     ADVERTISE_PAUSE_CAP |
					     ADVERTISE_PAUSE_ASYM);
	mdiobus_write(bus, port - 1, MII_CTRL1000, ADVERTISE_1000FULL);
	mdiobus_write(bus, port - 1, MII_BMCR, BMCR_RESET | BMCR_ANENABLE);

}

static void
ar8327_phy_init(struct ar8xxx_priv *priv)
{
	int i;

	for (i = 0; i < AR8327_NUM_PHYS; i++)
		ar8327_port_phy_init(priv, i + 1);

	msleep(1000);
}

static int
ar8327_hw_init(struct ar8xxx_priv *priv)
{
	int ret;

	if (priv->phy->dev.of_node)
		ret = ar8327_hw_config_of(priv, priv->phy->dev.of_node);
	else
		ret = ar8327_hw_config_pdata(priv,
					     priv->phy->dev.platform_data);

	if (ret)
		return ret;

	ar8327_leds_init(priv);
	ar8327_phy_init(priv);
	return 0;
}

static void
ar8327_cleanup(struct ar8xxx_priv *priv)
{
	ar8327_leds_cleanup(priv);
}

static void
ar8327_init_globals(struct ar8xxx_priv *priv)
{
	u32 t;

	/* enable CPU port and disable mirror port */
	t = AR8327_FWD_CTRL0_CPU_PORT_EN |
	    AR8327_FWD_CTRL0_MIRROR_PORT;
	priv->write(priv, AR8327_REG_FWD_CTRL0, t);

	/* forward multicast and broadcast frames to CPU */
	t = (AR8327_PORTS_ALL << AR8327_FWD_CTRL1_UC_FLOOD_S) |
	    (AR8327_PORTS_ALL << AR8327_FWD_CTRL1_MC_FLOOD_S) |
	    (AR8327_PORTS_ALL << AR8327_FWD_CTRL1_BC_FLOOD_S);
	priv->write(priv, AR8327_REG_FWD_CTRL1, t);

	/* enable jumbo frames */
	ar8xxx_rmw(priv, AR8327_REG_MAX_FRAME_SIZE,
		   AR8327_MAX_FRAME_SIZE_MTU, 9018 + 8 + 2);

	/* Enable MIB counters */
	ar8xxx_reg_set(priv, AR8327_REG_MODULE_EN,
		       AR8327_MODULE_EN_MIB);
}

static void
ar8327_init_port(struct ar8xxx_priv *priv, int port)
{
	u32 t;

	if (port == AR8216_PORT_CPU)
		t = priv->chip_data.ar8327.port0_status;
	else if (port == 6)
		t = priv->chip_data.ar8327.port6_status;
	else
		t = AR8216_PORT_STATUS_LINK_AUTO;

	if (port != AR8216_PORT_CPU && port != 6) {
		/*hw limitation:if configure mac when there is traffic,
		port MAC may work abnormal. Need disable lan&wan mac at fisrt*/
		priv->write(priv, AR8327_REG_PORT_STATUS(port), 0);
		msleep(100);
		t |= AR8216_PORT_STATUS_FLOW_CONTROL;
		priv->write(priv, AR8327_REG_PORT_STATUS(port), t);
	} else {
		priv->write(priv, AR8327_REG_PORT_STATUS(port), t);
	}

	priv->write(priv, AR8327_REG_PORT_HEADER(port), 0);

	priv->write(priv, AR8327_REG_PORT_VLAN0(port), 0);

	t = AR8327_PORT_VLAN1_OUT_MODE_UNTOUCH << AR8327_PORT_VLAN1_OUT_MODE_S;
	priv->write(priv, AR8327_REG_PORT_VLAN1(port), t);

	t = AR8327_PORT_LOOKUP_LEARN;
	t |= AR8216_PORT_STATE_FORWARD << AR8327_PORT_LOOKUP_STATE_S;
	priv->write(priv, AR8327_REG_PORT_LOOKUP(port), t);
}

static u32
ar8327_read_port_status(struct ar8xxx_priv *priv, int port)
{
	return priv->read(priv, AR8327_REG_PORT_STATUS(port));
}

static int
ar8327_atu_flush(struct ar8xxx_priv *priv)
{
	int ret;

	ret = ar8216_wait_bit(priv, AR8327_REG_ATU_FUNC,
			      AR8327_ATU_FUNC_BUSY, 0);
	if (!ret)
		priv->write(priv, AR8327_REG_ATU_FUNC,
			    AR8327_ATU_FUNC_OP_FLUSH | AR8327_ATU_FUNC_BUSY);

	return ret;
}

static void
ar8327_vtu_op(struct ar8xxx_priv *priv, u32 op, u32 val)
{
	if (ar8216_wait_bit(priv, AR8327_REG_VTU_FUNC1,
			    AR8327_VTU_FUNC1_BUSY, 0))
		return;

	if ((op & AR8327_VTU_FUNC1_OP) == AR8327_VTU_FUNC1_OP_LOAD)
		priv->write(priv, AR8327_REG_VTU_FUNC0, val);

	op |= AR8327_VTU_FUNC1_BUSY;
	priv->write(priv, AR8327_REG_VTU_FUNC1, op);
}

static void
ar8327_vtu_flush(struct ar8xxx_priv *priv)
{
	ar8327_vtu_op(priv, AR8327_VTU_FUNC1_OP_FLUSH, 0);
}

static void
ar8327_vtu_load_vlan(struct ar8xxx_priv *priv, u32 vid, u32 port_mask)
{
	u32 op;
	u32 val;
	int i;

	op = AR8327_VTU_FUNC1_OP_LOAD | (vid << AR8327_VTU_FUNC1_VID_S);
	val = AR8327_VTU_FUNC0_VALID | AR8327_VTU_FUNC0_IVL;
	for (i = 0; i < AR8327_NUM_PORTS; i++) {
		u32 mode;

		if ((port_mask & BIT(i)) == 0)
			mode = AR8327_VTU_FUNC0_EG_MODE_NOT;
		else if (priv->vlan == 0)
			mode = AR8327_VTU_FUNC0_EG_MODE_KEEP;
		else if (priv->vlan_tagged & BIT(i))
			mode = AR8327_VTU_FUNC0_EG_MODE_TAG;
		else
			mode = AR8327_VTU_FUNC0_EG_MODE_UNTAG;

		val |= mode << AR8327_VTU_FUNC0_EG_MODE_S(i);
	}
	ar8327_vtu_op(priv, op, val);
}

static void
ar8327_setup_port(struct ar8xxx_priv *priv, int port, u32 egress, u32 ingress,
		  u32 members, u32 pvid)
{
	u32 t;
	u32 mode;

	t = pvid << AR8327_PORT_VLAN0_DEF_SVID_S;
	t |= pvid << AR8327_PORT_VLAN0_DEF_CVID_S;
	priv->write(priv, AR8327_REG_PORT_VLAN0(port), t);

	mode = AR8327_PORT_VLAN1_OUT_MODE_UNMOD;
	switch (egress) {
	case AR8216_OUT_KEEP:
		mode = AR8327_PORT_VLAN1_OUT_MODE_UNTOUCH;
		break;
	case AR8216_OUT_STRIP_VLAN:
		mode = AR8327_PORT_VLAN1_OUT_MODE_UNTAG;
		break;
	case AR8216_OUT_ADD_VLAN:
		mode = AR8327_PORT_VLAN1_OUT_MODE_TAG;
		break;
	}

	t = AR8327_PORT_VLAN1_PORT_VLAN_PROP;
	t |= mode << AR8327_PORT_VLAN1_OUT_MODE_S;
	priv->write(priv, AR8327_REG_PORT_VLAN1(port), t);

	t = members;
	t |= AR8327_PORT_LOOKUP_LEARN;
	t |= ingress << AR8327_PORT_LOOKUP_IN_MODE_S;
	t |= AR8216_PORT_STATE_FORWARD << AR8327_PORT_LOOKUP_STATE_S;
	priv->write(priv, AR8327_REG_PORT_LOOKUP(port), t);
}

static const struct ar8xxx_chip ar8327_chip = {
	.caps = AR8XXX_CAP_GIGE | AR8XXX_CAP_MIB_COUNTERS,
	.hw_init = ar8327_hw_init,
	.cleanup = ar8327_cleanup,
	.init_globals = ar8327_init_globals,
	.init_port = ar8327_init_port,
	.setup_port = ar8327_setup_port,
	.read_port_status = ar8327_read_port_status,
	.atu_flush = ar8327_atu_flush,
	.vtu_flush = ar8327_vtu_flush,
	.vtu_load_vlan = ar8327_vtu_load_vlan,
	.atu_dump = ar8327_atu_dump,

	.num_mibs = ARRAY_SIZE(ar8236_mibs),
	.mib_decs = ar8236_mibs,
};

static int
ar8xxx_atu_dump(struct switch_dev *dev,
		       const struct switch_attr *attr,
		       struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	int len=0;

	if(priv->chip->atu_dump) {
		len = priv->chip->atu_dump(priv);
		if(len >= 0){
			val->value.s = priv->buf;
			val->len = len;
		}else
			val->len = -1;
	}

	return 0;
}

static int
ar8xxx_atu_flush(struct switch_dev *dev,
		       const struct switch_attr *attr,
		       struct switch_val *val)
{
	int ret = 0;
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);

	if(priv->chip->atu_flush)
		ret = priv->chip->atu_flush(priv);
	return ret;
}



static int
ar8xxx_sw_set_vlan(struct switch_dev *dev, const struct switch_attr *attr,
		   struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	priv->vlan = !!val->value.i;
	return 0;
}

static int
ar8xxx_sw_get_vlan(struct switch_dev *dev, const struct switch_attr *attr,
		   struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	val->value.i = priv->vlan;
	return 0;
}


static int
ar8xxx_sw_set_pvid(struct switch_dev *dev, int port, int vlan)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);

	/* make sure no invalid PVIDs get set */

	if (vlan >= dev->vlans)
		return -EINVAL;

	priv->pvid[port] = vlan;
	return 0;
}

static int
ar8xxx_sw_get_pvid(struct switch_dev *dev, int port, int *vlan)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	*vlan = priv->pvid[port];
	return 0;
}

static int
ar8xxx_sw_set_port_linkdown(struct switch_dev *dev,
			   const struct switch_attr *attr,
			   struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);

	if (val->value.i == 1)
		ar8327_port_phy_linkdown(priv, val->port_vlan);
	else
		ar8327_port_phy_init(priv, val->port_vlan);

	return 0;
}

static int
ar8xxx_sw_set_linkdown(struct switch_dev *dev,
			   const struct switch_attr *attr,
			   struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);

	if (val->value.i == 1)
		ar8327_phy_linkdown(priv);
	else
		ar8327_phy_init(priv);

	return 0;
}

static int
ar8xxx_sw_set_vid(struct switch_dev *dev, const struct switch_attr *attr,
		  struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	priv->vlan_id[val->port_vlan] = val->value.i;
	return 0;
}

static int
ar8xxx_sw_get_vid(struct switch_dev *dev, const struct switch_attr *attr,
		  struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	val->value.i = priv->vlan_id[val->port_vlan];
	return 0;
}

static int
ar8xxx_sw_get_port_link(struct switch_dev *dev, int port,
			struct switch_port_link *link)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);

	ar8216_read_port_link(priv, port, link);
	return 0;
}

static int
ar8xxx_sw_get_ports(struct switch_dev *dev, struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	u8 ports = priv->vlan_table[val->port_vlan];
	int i;

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
ar8xxx_sw_set_ports(struct switch_dev *dev, struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	u8 *vt = &priv->vlan_table[val->port_vlan];
	int i, j;

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
			for (j = 0; j < AR8X16_MAX_VLANS; j++) {
				if (j == val->port_vlan)
					continue;
				priv->vlan_table[j] &= ~(1 << p->id);
			}
		}

		*vt |= 1 << p->id;
	}
	return 0;
}

static void
ar8327_set_mirror_regs(struct ar8xxx_priv *priv)
{
	int port;

	/* reset all mirror registers */
	ar8xxx_rmw(priv, AR8327_REG_FWD_CTRL0,
		   AR8327_FWD_CTRL0_MIRROR_PORT,
		   (0xF << AR8327_FWD_CTRL0_MIRROR_PORT_S));
	for (port = 0; port < AR8327_NUM_PORTS; port++) {
		ar8xxx_rmw(priv, AR8327_REG_PORT_LOOKUP(port),
			   AR8327_PORT_LOOKUP_ING_MIRROR_EN,
			   0);

		ar8xxx_rmw(priv, AR8327_REG_PORT_HOL_CTRL1(port),
			   AR8327_PORT_HOL_CTRL1_EG_MIRROR_EN,
			   0);
	}

	/* now enable mirroring if necessary */
	if (priv->source_port >= AR8327_NUM_PORTS ||
	    priv->monitor_port >= AR8327_NUM_PORTS ||
	    priv->source_port == priv->monitor_port) {
		return;
	}

	ar8xxx_rmw(priv, AR8327_REG_FWD_CTRL0,
		   AR8327_FWD_CTRL0_MIRROR_PORT,
		   (priv->monitor_port << AR8327_FWD_CTRL0_MIRROR_PORT_S));

	if (priv->mirror_rx)
		ar8xxx_rmw(priv, AR8327_REG_PORT_LOOKUP(priv->source_port),
			   AR8327_PORT_LOOKUP_ING_MIRROR_EN,
			   AR8327_PORT_LOOKUP_ING_MIRROR_EN);

	if (priv->mirror_tx)
		ar8xxx_rmw(priv, AR8327_REG_PORT_HOL_CTRL1(priv->source_port),
			   AR8327_PORT_HOL_CTRL1_EG_MIRROR_EN,
			   AR8327_PORT_HOL_CTRL1_EG_MIRROR_EN);
}

static void
ar8216_set_mirror_regs(struct ar8xxx_priv *priv)
{
	int port;

	/* reset all mirror registers */
	ar8xxx_rmw(priv, AR8216_REG_GLOBAL_CPUPORT,
		   AR8216_GLOBAL_CPUPORT_MIRROR_PORT,
		   (0xF << AR8216_GLOBAL_CPUPORT_MIRROR_PORT_S));
	for (port = 0; port < AR8216_NUM_PORTS; port++) {
		ar8xxx_rmw(priv, AR8216_REG_PORT_CTRL(port),
			   AR8216_PORT_CTRL_MIRROR_RX,
			   0);

		ar8xxx_rmw(priv, AR8216_REG_PORT_CTRL(port),
			   AR8216_PORT_CTRL_MIRROR_TX,
			   0);
	}

	/* now enable mirroring if necessary */
	if (priv->source_port >= AR8216_NUM_PORTS ||
	    priv->monitor_port >= AR8216_NUM_PORTS ||
	    priv->source_port == priv->monitor_port) {
		return;
	}

	ar8xxx_rmw(priv, AR8216_REG_GLOBAL_CPUPORT,
		   AR8216_GLOBAL_CPUPORT_MIRROR_PORT,
		   (priv->monitor_port << AR8216_GLOBAL_CPUPORT_MIRROR_PORT_S));

	if (priv->mirror_rx)
		ar8xxx_rmw(priv, AR8216_REG_PORT_CTRL(priv->source_port),
			   AR8216_PORT_CTRL_MIRROR_RX,
			   AR8216_PORT_CTRL_MIRROR_RX);

	if (priv->mirror_tx)
		ar8xxx_rmw(priv, AR8216_REG_PORT_CTRL(priv->source_port),
			   AR8216_PORT_CTRL_MIRROR_TX,
			   AR8216_PORT_CTRL_MIRROR_TX);
}

static void
ar8327_set_max_frame_size_regs(struct ar8xxx_priv *priv)
{
	ar8xxx_rmw(priv, AR8327_REG_MAX_FRAME_SIZE,
			AR8327_MAX_FRAME_SIZE_MTU,
			(priv->max_frame_size + 8 + 2));
}

static void
ar8216_set_max_frame_size_regs(struct ar8xxx_priv *priv)
{
	if(chip_is_ar8216(priv))
		ar8xxx_rmw(priv, AR8216_REG_GLOBAL_CTRL,
				AR8216_GCTRL_MTU,
				(priv->max_frame_size + 8 + 2));
	else if(chip_is_ar8316(priv))
		ar8xxx_rmw(priv, AR8216_REG_GLOBAL_CTRL,
				AR8316_GCTRL_MTU,
				(priv->max_frame_size + 8 + 2));
	else if(chip_is_ar8236(priv))
		ar8xxx_rmw(priv, AR8216_REG_GLOBAL_CTRL,
				AR8236_GCTRL_MTU,
				(priv->max_frame_size + 8 + 2));
}


static void
ar8xxx_set_mirror_regs(struct ar8xxx_priv *priv)
{
	if (chip_is_ar8327(priv) || chip_is_ar8337(priv)) {
		ar8327_set_mirror_regs(priv);
	} else {
		ar8216_set_mirror_regs(priv);
	}
}

static void
ar8xxx_set_max_frame_size_regs(struct ar8xxx_priv *priv)
{
	if (chip_is_ar8327(priv) || chip_is_ar8337(priv)) {
		ar8327_set_max_frame_size_regs(priv);
	} else {
		ar8216_set_max_frame_size_regs(priv);
	}
}


static int
ar8xxx_sw_hw_apply(struct switch_dev *dev)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	u8 portmask[AR8X16_MAX_PORTS];
	int i, j;

	mutex_lock(&priv->reg_mutex);
	/* flush all vlan translation unit entries */
	priv->chip->vtu_flush(priv);

	memset(portmask, 0, sizeof(portmask));
	if (!priv->init) {
		/* calculate the port destination masks and load vlans
		 * into the vlan translation unit */
		for (j = 0; j < AR8X16_MAX_VLANS; j++) {
			u8 vp = priv->vlan_table[j];

			if (!vp)
				continue;

			for (i = 0; i < dev->ports; i++) {
				u8 mask = (1 << i);
				if (vp & mask)
					portmask[i] |= vp & ~mask;
			}

			priv->chip->vtu_load_vlan(priv, priv->vlan_id[j],
						 priv->vlan_table[j]);
		}
	} else {
		/* vlan disabled:
		 * isolate all ports, but connect them to the cpu port */
		for (i = 0; i < dev->ports; i++) {
			if (i == AR8216_PORT_CPU)
				continue;

			portmask[i] = 1 << AR8216_PORT_CPU;
			portmask[AR8216_PORT_CPU] |= (1 << i);
		}
	}

	/* update the port destination mask registers and tag settings */
	for (i = 0; i < dev->ports; i++) {
		int egress, ingress;
		int pvid;

		if (priv->vlan) {
			pvid = priv->vlan_id[priv->pvid[i]];
			if (priv->vlan_tagged & (1 << i))
				egress = AR8216_OUT_ADD_VLAN;
			else
				egress = AR8216_OUT_STRIP_VLAN;
			ingress = AR8216_IN_SECURE;
		} else {
			pvid = i;
			egress = AR8216_OUT_KEEP;
			ingress = AR8216_IN_PORT_ONLY;
		}

		priv->chip->setup_port(priv, i, egress, ingress, portmask[i],
				       pvid);
	}

	ar8xxx_set_mirror_regs(priv);
	ar8xxx_set_max_frame_size_regs(priv);


	priv->start_carrier_cnt = 1;
	memset(priv->vlan_carrier_off_cnt, 0, AR8X16_MAX_VLANS);
	memset(priv->vlan_carrier_on_cnt, 0, AR8X16_MAX_VLANS);

	mutex_unlock(&priv->reg_mutex);
	return 0;
}

static int
ar8xxx_sw_reset_switch(struct switch_dev *dev)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	int i;

	mutex_lock(&priv->reg_mutex);
	memset(&priv->vlan, 0, sizeof(struct ar8xxx_priv) -
		offsetof(struct ar8xxx_priv, vlan));

	for (i = 0; i < AR8X16_MAX_VLANS; i++)
		priv->vlan_id[i] = i;

	/* Configure all ports */
	for (i = 0; i < dev->ports; i++)
		priv->chip->init_port(priv, i);

	priv->mirror_rx = false;
	priv->mirror_tx = false;
	priv->source_port = 0;
	priv->monitor_port = 0;
	priv->max_frame_size = AR8XXX_MAX_FRAME_SIZE;

	priv->chip->init_globals(priv);

	mutex_unlock(&priv->reg_mutex);

	return ar8xxx_sw_hw_apply(dev);
}

static int
ar8xxx_sw_set_reset_mibs(struct switch_dev *dev,
			 const struct switch_attr *attr,
			 struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	unsigned int len;
	int ret;

	if (!ar8xxx_has_mib_counters(priv))
		return -EOPNOTSUPP;

	mutex_lock(&priv->mib_lock);

	len = priv->dev.ports * priv->chip->num_mibs *
	      sizeof(*priv->mib_stats);
	memset(priv->mib_stats, '\0', len);
	ret = ar8xxx_mib_flush(priv);
	if (ret)
		goto unlock;

	ret = 0;

unlock:
	mutex_unlock(&priv->mib_lock);
	return ret;
}

static int
ar8xxx_sw_set_mirror_rx_enable(struct switch_dev *dev,
			       const struct switch_attr *attr,
			       struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);

	mutex_lock(&priv->reg_mutex);
	priv->mirror_rx = !!val->value.i;
	ar8xxx_set_mirror_regs(priv);
	mutex_unlock(&priv->reg_mutex);

	return 0;
}

static int
ar8xxx_sw_get_mirror_rx_enable(struct switch_dev *dev,
			       const struct switch_attr *attr,
			       struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	val->value.i = priv->mirror_rx;
	return 0;
}

static int
ar8xxx_sw_set_mirror_tx_enable(struct switch_dev *dev,
			       const struct switch_attr *attr,
			       struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);

	mutex_lock(&priv->reg_mutex);
	priv->mirror_tx = !!val->value.i;
	ar8xxx_set_mirror_regs(priv);
	mutex_unlock(&priv->reg_mutex);

	return 0;
}

static int
ar8xxx_sw_get_mirror_tx_enable(struct switch_dev *dev,
			       const struct switch_attr *attr,
			       struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	val->value.i = priv->mirror_tx;
	return 0;
}

static int
ar8xxx_sw_set_mirror_monitor_port(struct switch_dev *dev,
				  const struct switch_attr *attr,
				  struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);

	mutex_lock(&priv->reg_mutex);
	priv->monitor_port = val->value.i;
	ar8xxx_set_mirror_regs(priv);
	mutex_unlock(&priv->reg_mutex);

	return 0;
}

static int
ar8xxx_sw_get_mirror_monitor_port(struct switch_dev *dev,
				  const struct switch_attr *attr,
				  struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	val->value.i = priv->monitor_port;
	return 0;
}

static int
ar8xxx_sw_set_mirror_source_port(struct switch_dev *dev,
				 const struct switch_attr *attr,
				 struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);

	mutex_lock(&priv->reg_mutex);
	priv->source_port = val->value.i;
	ar8xxx_set_mirror_regs(priv);
	mutex_unlock(&priv->reg_mutex);

	return 0;
}

static int
ar8xxx_sw_get_mirror_source_port(struct switch_dev *dev,
				 const struct switch_attr *attr,
				 struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	val->value.i = priv->source_port;
	return 0;
}

static int
ar8xxx_sw_set_port_reset_mib(struct switch_dev *dev,
			     const struct switch_attr *attr,
			     struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	int port;
	int ret;

	if (!ar8xxx_has_mib_counters(priv))
		return -EOPNOTSUPP;

	port = val->port_vlan;
	if (port >= dev->ports)
		return -EINVAL;

	mutex_lock(&priv->mib_lock);
	ret = ar8xxx_mib_capture(priv);
	if (ret)
		goto unlock;

	ar8xxx_mib_fetch_port_stat(priv, port, true);

	ret = 0;

unlock:
	mutex_unlock(&priv->mib_lock);
	return ret;
}

static int
ar8xxx_sw_get_port_mib(struct switch_dev *dev,
		       const struct switch_attr *attr,
		       struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	const struct ar8xxx_chip *chip = priv->chip;
	u64 *mib_stats;
	int port;
	int ret;
	char *buf = priv->buf;
	int i, len = 0;

	if (!ar8xxx_has_mib_counters(priv))
		return -EOPNOTSUPP;

	port = val->port_vlan;
	if (port >= dev->ports)
		return -EINVAL;

	mutex_lock(&priv->mib_lock);
	ret = ar8xxx_mib_capture(priv);
	if (ret)
		goto unlock;

	ar8xxx_mib_fetch_port_stat(priv, port, false);

	len += snprintf(buf + len, sizeof(priv->buf) - len,
			"Port %d MIB counters\n",
			port);

	mib_stats = &priv->mib_stats[port * chip->num_mibs];
	for (i = 0; i < chip->num_mibs; i++)
		len += snprintf(buf + len, sizeof(priv->buf) - len,
				"%-12s: %llu\n",
				chip->mib_decs[i].name,
				mib_stats[i]);

	val->value.s = buf;
	val->len = len;

	ret = 0;

unlock:
	mutex_unlock(&priv->mib_lock);
	return ret;
}

static int
ar8xxx_sw_set_max_frame_size(struct switch_dev *dev,
				 const struct switch_attr *attr,
				 struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);

	mutex_lock(&priv->reg_mutex);
	priv->max_frame_size = val->value.i;
	ar8xxx_set_max_frame_size_regs(priv);
	mutex_unlock(&priv->reg_mutex);

	return 0;
}

static int
ar8xxx_sw_get_max_frame_size(struct switch_dev *dev,
				 const struct switch_attr *attr,
				 struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	val->value.i = priv->max_frame_size;
	return 0;
}


static struct switch_attr ar8xxx_sw_attr_globals[] = {
	{
		.type = SWITCH_TYPE_INT,
		.name = "enable_vlan",
		.description = "Enable VLAN mode",
		.set = ar8xxx_sw_set_vlan,
		.get = ar8xxx_sw_get_vlan,
		.max = 1
	},
	{
		.type = SWITCH_TYPE_NOVAL,
		.name = "reset_mibs",
		.description = "Reset all MIB counters",
		.set = ar8xxx_sw_set_reset_mibs,
	},
	{
		.type = SWITCH_TYPE_INT,
		.name = "enable_mirror_rx",
		.description = "Enable mirroring of RX packets",
		.set = ar8xxx_sw_set_mirror_rx_enable,
		.get = ar8xxx_sw_get_mirror_rx_enable,
		.max = 1
	},
	{
		.type = SWITCH_TYPE_INT,
		.name = "enable_mirror_tx",
		.description = "Enable mirroring of TX packets",
		.set = ar8xxx_sw_set_mirror_tx_enable,
		.get = ar8xxx_sw_get_mirror_tx_enable,
		.max = 1
	},
	{
		.type = SWITCH_TYPE_INT,
		.name = "mirror_monitor_port",
		.description = "Mirror monitor port",
		.set = ar8xxx_sw_set_mirror_monitor_port,
		.get = ar8xxx_sw_get_mirror_monitor_port,
		.max = AR8216_NUM_PORTS - 1
	},
	{
		.type = SWITCH_TYPE_INT,
		.name = "mirror_source_port",
		.description = "Mirror source port",
		.set = ar8xxx_sw_set_mirror_source_port,
		.get = ar8xxx_sw_get_mirror_source_port,
		.max = AR8216_NUM_PORTS - 1
	},
	{
		.type = SWITCH_TYPE_INT,
		.name = "max_frame_size",
		.description = "Max frame size can be received and transmitted by mac",
		.set = ar8xxx_sw_set_max_frame_size,
		.get = ar8xxx_sw_get_max_frame_size,
		.max = AR8XXX_MAX_FRAME_SIZE
	},
	{
		.type = SWITCH_TYPE_NOVAL,
		.name = "flush_arl",
		.description = "Flush ARL table",
		.set = ar8xxx_atu_flush,
	},
	{
		.type = SWITCH_TYPE_STRING,
		.name = "dump_arl",
		.description = "Dump ARL table with mac and port map",
		.get = ar8xxx_atu_dump,
	},
};

static struct switch_attr ar8327_sw_attr_globals[] = {
	{
		.type = SWITCH_TYPE_INT,
		.name = "enable_vlan",
		.description = "Enable VLAN mode",
		.set = ar8xxx_sw_set_vlan,
		.get = ar8xxx_sw_get_vlan,
		.max = 1
	},
	{
		.type = SWITCH_TYPE_NOVAL,
		.name = "reset_mibs",
		.description = "Reset all MIB counters",
		.set = ar8xxx_sw_set_reset_mibs,
	},
	{
		.type = SWITCH_TYPE_INT,
		.name = "enable_mirror_rx",
		.description = "Enable mirroring of RX packets",
		.set = ar8xxx_sw_set_mirror_rx_enable,
		.get = ar8xxx_sw_get_mirror_rx_enable,
		.max = 1
	},
	{
		.type = SWITCH_TYPE_INT,
		.name = "enable_mirror_tx",
		.description = "Enable mirroring of TX packets",
		.set = ar8xxx_sw_set_mirror_tx_enable,
		.get = ar8xxx_sw_get_mirror_tx_enable,
		.max = 1
	},
	{
		.type = SWITCH_TYPE_INT,
		.name = "mirror_monitor_port",
		.description = "Mirror monitor port",
		.set = ar8xxx_sw_set_mirror_monitor_port,
		.get = ar8xxx_sw_get_mirror_monitor_port,
		.max = AR8327_NUM_PORTS - 1
	},
	{
		.type = SWITCH_TYPE_INT,
		.name = "mirror_source_port",
		.description = "Mirror source port",
		.set = ar8xxx_sw_set_mirror_source_port,
		.get = ar8xxx_sw_get_mirror_source_port,
		.max = AR8327_NUM_PORTS - 1
	},
	{
		.type = SWITCH_TYPE_INT,
		.name = "max_frame_size",
		.description = "Max frame size can be received and transmitted by mac",
		.set = ar8xxx_sw_set_max_frame_size,
		.get = ar8xxx_sw_get_max_frame_size,
		.max = AR8XXX_MAX_FRAME_SIZE
	},
	{
		.type = SWITCH_TYPE_NOVAL,
		.name = "flush_arl",
		.description = "Flush ARL table",
		.set = ar8xxx_atu_flush,
	},
	{
		.type = SWITCH_TYPE_STRING,
		.name = "dump_arl",
		.description = "Dump ARL table with mac and port map",
		.get = ar8xxx_atu_dump,
	},
	{
		.type = SWITCH_TYPE_INT,
		.name = "linkdown",
		.description = "Link down all the PHYs",
		.set = ar8xxx_sw_set_linkdown,
		.max = 1
	},
};

static struct switch_attr ar8xxx_sw_attr_port[] = {
	{
		.type = SWITCH_TYPE_NOVAL,
		.name = "reset_mib",
		.description = "Reset single port MIB counters",
		.set = ar8xxx_sw_set_port_reset_mib,
	},
	{
		.type = SWITCH_TYPE_STRING,
		.name = "mib",
		.description = "Get port's MIB counters",
		.set = NULL,
		.get = ar8xxx_sw_get_port_mib,
	},
	{
		.type = SWITCH_TYPE_INT,
		.name = "linkdown",
		.description = "Link down single phy",
		.set = ar8xxx_sw_set_port_linkdown,
		.max = 1
	},
};

static struct switch_attr ar8xxx_sw_attr_vlan[] = {
	{
		.type = SWITCH_TYPE_INT,
		.name = "vid",
		.description = "VLAN ID (0-4094)",
		.set = ar8xxx_sw_set_vid,
		.get = ar8xxx_sw_get_vid,
		.max = 4094,
	},
};

static const struct switch_dev_ops ar8xxx_sw_ops = {
	.attr_global = {
		.attr = ar8xxx_sw_attr_globals,
		.n_attr = ARRAY_SIZE(ar8xxx_sw_attr_globals),
	},
	.attr_port = {
		.attr = ar8xxx_sw_attr_port,
		.n_attr = ARRAY_SIZE(ar8xxx_sw_attr_port),
	},
	.attr_vlan = {
		.attr = ar8xxx_sw_attr_vlan,
		.n_attr = ARRAY_SIZE(ar8xxx_sw_attr_vlan),
	},
	.get_port_pvid = ar8xxx_sw_get_pvid,
	.set_port_pvid = ar8xxx_sw_set_pvid,
	.get_vlan_ports = ar8xxx_sw_get_ports,
	.set_vlan_ports = ar8xxx_sw_set_ports,
	.apply_config = ar8xxx_sw_hw_apply,
	.reset_switch = ar8xxx_sw_reset_switch,
	.get_port_link = ar8xxx_sw_get_port_link,
};

static const struct switch_dev_ops ar8327_sw_ops = {
	.attr_global = {
		.attr = ar8327_sw_attr_globals,
		.n_attr = ARRAY_SIZE(ar8327_sw_attr_globals),
	},
	.attr_port = {
		.attr = ar8xxx_sw_attr_port,
		.n_attr = ARRAY_SIZE(ar8xxx_sw_attr_port),
	},
	.attr_vlan = {
		.attr = ar8xxx_sw_attr_vlan,
		.n_attr = ARRAY_SIZE(ar8xxx_sw_attr_vlan),
	},
	.get_port_pvid = ar8xxx_sw_get_pvid,
	.set_port_pvid = ar8xxx_sw_set_pvid,
	.get_vlan_ports = ar8xxx_sw_get_ports,
	.set_vlan_ports = ar8xxx_sw_set_ports,
	.apply_config = ar8xxx_sw_hw_apply,
	.reset_switch = ar8xxx_sw_reset_switch,
	.get_port_link = ar8xxx_sw_get_port_link,
};

static int
ar8xxx_id_chip(struct ar8xxx_priv *priv)
{
	u32 val;
	u16 id;
	int i;

	val = priv->read(priv, AR8216_REG_CTRL);
	if (val == ~0)
		return -ENODEV;

	id = val & (AR8216_CTRL_REVISION | AR8216_CTRL_VERSION);
	for (i = 0; i < AR8X16_PROBE_RETRIES; i++) {
		u16 t;

		val = priv->read(priv, AR8216_REG_CTRL);
		if (val == ~0)
			return -ENODEV;

		t = val & (AR8216_CTRL_REVISION | AR8216_CTRL_VERSION);
		if (t != id)
			return -ENODEV;
	}

	priv->chip_ver = (id & AR8216_CTRL_VERSION) >> AR8216_CTRL_VERSION_S;
	priv->chip_rev = (id & AR8216_CTRL_REVISION);

	switch (priv->chip_ver) {
	case AR8XXX_VER_AR8216:
		priv->chip = &ar8216_chip;
		break;
	case AR8XXX_VER_AR8236:
		priv->chip = &ar8236_chip;
		break;
	case AR8XXX_VER_AR8316:
		priv->chip = &ar8316_chip;
		break;
	case AR8XXX_VER_AR8327:
		priv->mii_lo_first = true;
		priv->chip = &ar8327_chip;
		break;
	case AR8XXX_VER_AR8337:
		priv->mii_lo_first = true;
		priv->chip = &ar8327_chip;
		break;
	default:
		pr_err("ar8216: Unknown Atheros device [ver=%d, rev=%d]\n",
		       priv->chip_ver, priv->chip_rev);

		return -ENODEV;
	}

	return 0;
}

static void
ar8xxx_mib_work_func(struct work_struct *work)
{
	struct ar8xxx_priv *priv;
	int err;

	priv = container_of(work, struct ar8xxx_priv, mib_work.work);

	mutex_lock(&priv->mib_lock);

	err = ar8xxx_mib_capture(priv);
	if (err)
		goto next_port;

	ar8xxx_mib_fetch_port_stat(priv, priv->mib_next_port, false);

next_port:
	priv->mib_next_port++;
	if (priv->mib_next_port >= priv->dev.ports)
		priv->mib_next_port = 0;

	mutex_unlock(&priv->mib_lock);
	schedule_delayed_work(&priv->mib_work,
			      msecs_to_jiffies(AR8XXX_MIB_WORK_DELAY));
}

static int
ar8xxx_mib_init(struct ar8xxx_priv *priv)
{
	unsigned int len;

	if (!ar8xxx_has_mib_counters(priv))
		return 0;

	BUG_ON(!priv->chip->mib_decs || !priv->chip->num_mibs);

	len = priv->dev.ports * priv->chip->num_mibs *
	      sizeof(*priv->mib_stats);
	priv->mib_stats = kzalloc(len, GFP_KERNEL);

	if (!priv->mib_stats)
		return -ENOMEM;

	return 0;
}

static void
ar8xxx_mib_start(struct ar8xxx_priv *priv)
{
	if (!ar8xxx_has_mib_counters(priv))
		return;

	schedule_delayed_work(&priv->mib_work,
			      msecs_to_jiffies(AR8XXX_MIB_WORK_DELAY));
}

static void
ar8xxx_mib_stop(struct ar8xxx_priv *priv)
{
	if (!ar8xxx_has_mib_counters(priv))
		return;

	cancel_delayed_work(&priv->mib_work);
}

static struct ar8xxx_priv *
ar8xxx_create(void)
{
	struct ar8xxx_priv *priv;

	priv = kzalloc(sizeof(struct ar8xxx_priv), GFP_KERNEL);
	if (priv == NULL)
		return NULL;

	mutex_init(&priv->reg_mutex);
	mutex_init(&priv->mib_lock);
	INIT_DELAYED_WORK(&priv->mib_work, ar8xxx_mib_work_func);

	return priv;
}

static void
ar8xxx_free(struct ar8xxx_priv *priv)
{
	if (priv->chip && priv->chip->cleanup)
		priv->chip->cleanup(priv);

	kfree(priv->mib_stats);
	kfree(priv);
}

static struct ar8xxx_priv *
ar8xxx_create_mii(struct mii_bus *bus)
{
	struct ar8xxx_priv *priv;

	priv = ar8xxx_create();
	if (priv) {
		priv->mii_bus = bus;
		priv->read = ar8xxx_mii_read;
		priv->write = ar8xxx_mii_write;
		priv->rmw = ar8xxx_mii_rmw;
	}

	return priv;
}

static int
ar8xxx_probe_switch(struct ar8xxx_priv *priv)
{
	struct switch_dev *swdev;
	int ret;

	ret = ar8xxx_id_chip(priv);
	if (ret)
		return ret;

	swdev = &priv->dev;
	swdev->cpu_port = AR8216_PORT_CPU;
	swdev->ops = &ar8xxx_sw_ops;

	if (chip_is_ar8316(priv)) {
		swdev->name = "Atheros AR8316";
		swdev->vlans = AR8X16_MAX_VLANS;
		swdev->ports = AR8216_NUM_PORTS;
	} else if (chip_is_ar8236(priv)) {
		swdev->name = "Atheros AR8236";
		swdev->vlans = AR8216_NUM_VLANS;
		swdev->ports = AR8216_NUM_PORTS;
	} else if (chip_is_ar8327(priv)) {
		swdev->name = "Atheros AR8327";
		swdev->vlans = AR8X16_MAX_VLANS;
		swdev->ports = AR8327_NUM_PORTS;
		swdev->ops = &ar8327_sw_ops;
	} else if (chip_is_ar8337(priv)) {
		swdev->name = "Atheros AR8337";
		swdev->vlans = AR8X16_MAX_VLANS;
		swdev->ports = AR8327_NUM_PORTS;
		swdev->ops = &ar8327_sw_ops;
	} else {
		swdev->name = "Atheros AR8216";
		swdev->vlans = AR8216_NUM_VLANS;
		swdev->ports = AR8216_NUM_PORTS;
	}

	ret = ar8xxx_mib_init(priv);
	if (ret)
		return ret;

	return 0;
}

static int
ar8xxx_start(struct ar8xxx_priv *priv)
{
	int ret;

	priv->init = true;

	ret = priv->chip->hw_init(priv);
	if (ret)
		return ret;

	ret = ar8xxx_sw_reset_switch(&priv->dev);
	if (ret)
		return ret;

	priv->init = false;

	ar8xxx_mib_start(priv);

	return 0;
}

static int
ar8xxx_phy_config_init(struct phy_device *phydev)
{
	struct ar8xxx_priv *priv = phydev->priv;
	struct net_device *dev = phydev->attached_dev;
	int ret;

	if (WARN_ON(!priv))
		return -ENODEV;

	if (chip_is_ar8327(priv) || chip_is_ar8337(priv)) {
		if(phydev->addr == 0)
			ar8327_phy_init(priv);
		return 0;
	}

	priv->phy = phydev;

	if (phydev->addr != 0) {
		if (chip_is_ar8316(priv)) {
			/* switch device has been initialized, reinit */
			priv->dev.ports = (AR8216_NUM_PORTS - 1);
			priv->initialized = false;
			priv->port4_phy = true;
			ar8316_hw_init(priv);
			return 0;
		}

		return 0;
	}

	ret = ar8xxx_start(priv);
	if (ret)
		return ret;

	/* VID fixup only needed on ar8216 */
	if (chip_is_ar8216(priv)) {
		dev->phy_ptr = priv;
		dev->priv_flags |= IFF_NO_IP_ALIGN;
		dev->eth_mangle_rx = ar8216_mangle_rx;
		dev->eth_mangle_tx = ar8216_mangle_tx;
	}

	return 0;
}

static int ar8xxx_carrier_check;

static int vlandev_event(struct notifier_block *this, unsigned long event,
			 void *ptr)
{
	struct net_device *dev = ptr;

	ASSERT_RTNL();

	switch (event) {
	case NETDEV_UP:
		if (is_vlan_dev(dev))
			ar8xxx_carrier_check = 1;
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}


static struct notifier_block vlandev_notifier = {
	.notifier_call = vlandev_event,
};

static int 
ar8xxx_get_vlan_dev(struct phy_device *phydev, int vlanID)
{
	struct ar8xxx_priv *priv = phydev->priv;
	uint8_t  name[10];

	sprintf(name, "%s.%d\0", phydev->attached_dev->name, vlanID);
	priv->vlan_dev[vlanID] = dev_get_by_name(&init_net, name);
	if(priv->vlan_dev[vlanID] != NULL){
		dev_put(priv->vlan_dev[vlanID]);
		return 1;
	}
	return 0;
}

static int ar8xxx_carrier_proc(struct phy_device *phydev, int port_status)
{
	struct ar8xxx_priv *priv = phydev->priv;
	int i = 0, ret = 0;

	for(i = 0; i < AR8X16_MAX_VLANS; i++) {
		priv->vlan_dev[i] = NULL;
		ret = ar8xxx_get_vlan_dev(phydev, i);
		if (!ret)
			continue;

		if(((port_status & priv->vlan_table[i]) != 0) && (priv->vlan_status[i] == 0)){
			priv->vlan_carrier_off_cnt[i] = 0;
			if(!netif_carrier_ok(priv->vlan_dev[i]))
			{
				priv->vlan_carrier_on_cnt[i]++;
				if(priv->vlan_carrier_on_cnt[i] > AR8XXX_CARRIER_ON_NUM)
				{
					priv->vlan_carrier_on_cnt[i] = 0;
					pr_info("%s is on\n", priv->vlan_dev[i]->name);
					netif_carrier_on(priv->vlan_dev[i]);
					priv->vlan_status[i] = 1;
				}
			}
			else
			{
				priv->vlan_carrier_on_cnt[i] = 0;
			}
		} else if( (priv->vlan_table[i] != 0) && ((port_status & priv->vlan_table[i]) == 0)) {
			priv->vlan_carrier_on_cnt[i] = 0;
			if(netif_carrier_ok(priv->vlan_dev[i]))
			{
				priv->vlan_carrier_off_cnt[i]++;
				if(priv->vlan_carrier_off_cnt[i] > AR8XXX_CARRIER_OFF_NUM)
				{
					priv->vlan_carrier_off_cnt[i] = 0;
					pr_info("%s is off\n", priv->vlan_dev[i]->name);
					netif_carrier_off(priv->vlan_dev[i]);
					priv->vlan_status[i] = 0;
				}
			}
			else
			{
				priv->vlan_carrier_off_cnt[i] = 0;
			}
		}
	}

	return 0;
}


static int
ar8xxx_phy_read_status(struct phy_device *phydev)
{
	struct ar8xxx_priv *priv = phydev->priv;
	struct switch_port_link link;
	struct switch_dev *dev;
	int ret = 0;
	int i, port_status = 0;

/*
	if (phydev->addr != 0)
		return genphy_read_status(phydev);
*/

	dev = (struct switch_dev *)priv;
	for(i = 1; i < dev->ports; i++) {
		ar8216_read_port_link(priv, i, &link);
		if(link.link)
			port_status |= 1 << i;
	}

	if(priv->start_carrier_cnt)
	{
		if((priv->old_port_status ^ port_status) != 0)
		{
			priv->stable_cnt = 0;
		}
		else
		{
			priv->stable_cnt++;
			if(priv->stable_cnt > AR8XXX_STABLE_NUM)
			{
				priv->stable_cnt = AR8XXX_STABLE_NUM;
			}
		}
	}
	priv->old_port_status = port_status;

	if((priv->start_carrier_cnt) 
		&& ((priv->stable_cnt < AR8XXX_STABLE_NUM) || ar8xxx_carrier_check))
	{
		ar8xxx_carrier_check = 0;
		(void)ar8xxx_carrier_proc(phydev, port_status);
	}

	ar8216_read_port_link(priv, AR8216_PORT_CPU/*phydev->addr*/, &link);
	phydev->link = !!link.link;
	if (!phydev->link)
		return 0;

	switch (link.speed) {
	case SWITCH_PORT_SPEED_10:
		phydev->speed = SPEED_10;
		break;
	case SWITCH_PORT_SPEED_100:
		phydev->speed = SPEED_100;
		break;
	case SWITCH_PORT_SPEED_1000:
		phydev->speed = SPEED_1000;
		break;
	default:
		phydev->speed = 0;
	}
	phydev->duplex = link.duplex ? DUPLEX_FULL : DUPLEX_HALF;

	/* flush the address translation unit */
	/* Should not flush ATU(acl/fdb table), fix bug170924 by liwei.
	mutex_lock(&priv->reg_mutex);
	ret = priv->chip->atu_flush(priv);
	mutex_unlock(&priv->reg_mutex);
	*/

	phydev->state = PHY_RUNNING;
	netif_carrier_on(phydev->attached_dev);
	phydev->adjust_link(phydev->attached_dev);

	return ret;
}

static int
ar8xxx_phy_config_aneg(struct phy_device *phydev)
{
	if (phydev->addr == 0)
		return 0;

	return genphy_config_aneg(phydev);
}

static const u32 ar8xxx_phy_ids[] = {
	0x004dd033,
	0x004dd034, /* AR8327 */
	0x004dd036, /* AR8337 */
	0x004dd041,
	0x004dd042,
};

static bool
ar8xxx_phy_match(u32 phy_id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ar8xxx_phy_ids); i++)
		if (phy_id == ar8xxx_phy_ids[i])
			return true;

	return false;
}

static bool
ar8xxx_is_possible(struct mii_bus *bus)
{
	unsigned i;

	for (i = 0; i < 4; i++) {
		u32 phy_id;

		phy_id = mdiobus_read(bus, i, MII_PHYSID1) << 16;
		phy_id |= mdiobus_read(bus, i, MII_PHYSID2);
		if (!ar8xxx_phy_match(phy_id)) {
			pr_debug("ar8xxx: unknown PHY at %s:%02x id:%08x\n",
				 dev_name(&bus->dev), i, phy_id);
			return false;
		}
	}

	return true;
}

static int ar8xxx_regmap_read(void *ctx, uint32_t reg, uint32_t *val) {
	struct ar8xxx_priv *priv = (struct ar8xxx_priv *) ctx;

	*val = ar8xxx_mii_read(priv, reg);

	return 0;
}

static int ar8xxx_regmap_write(void *ctx, uint32_t reg, uint32_t val) {
	struct ar8xxx_priv *priv = (struct ar8xxx_priv *) ctx;

	ar8xxx_mii_write(priv, reg, val);

	return 0;
}

static const struct regmap_range ar8xxx_readable_ranges[] = {
	regmap_reg_range(0x0000, 0x00e0), /* Global control */
	regmap_reg_range(0x0100, 0x0168), /* EEE control */
	regmap_reg_range(0x0200, 0x0270), /* Parser control */
	regmap_reg_range(0x0400, 0x0454), /* ACL */
	regmap_reg_range(0x0600, 0x0718), /* Lookup */
	regmap_reg_range(0x0800, 0x0b70), /* QM */
	regmap_reg_range(0x0C00, 0x0c80), /* PKT */
};

static struct regmap_access_table ar8xxx_readable_table = {
	.yes_ranges = ar8xxx_readable_ranges,
	.n_yes_ranges = ARRAY_SIZE(ar8xxx_readable_ranges),
};

struct regmap_config ar8xxx_regmap_config = {
	.reg_bits = 16,
	.val_bits = 32,
	.reg_stride = 4,
	.max_register = 0x0c80, /* end PKT range */
	.reg_read = ar8xxx_regmap_read,
	.reg_write = ar8xxx_regmap_write,
	.rd_table = &ar8xxx_readable_table,
};

static int
ar8xxx_phy_probe(struct phy_device *phydev)
{
	struct ar8xxx_priv *priv;
	struct switch_dev *swdev;
	int ret;

	if (!ar8xxx_is_possible(phydev->bus))
		return -ENODEV;

	mutex_lock(&ar8xxx_dev_list_lock);
	list_for_each_entry(priv, &ar8xxx_dev_list, list)
		if (priv->mii_bus == phydev->bus)
			goto found;

	priv = ar8xxx_create_mii(phydev->bus);
	if (priv == NULL) {
		ret = -ENOMEM;
		goto unlock;
	}

	ret = ar8xxx_probe_switch(priv);
	if (ret)
		goto free_priv;

	swdev = &priv->dev;
	swdev->alias = dev_name(&priv->mii_bus->dev);
	ret = register_switch(swdev, NULL);
	if (ret)
		goto free_priv;

	priv->regmap = devm_regmap_init(&phydev->dev, NULL, priv,
					&ar8xxx_regmap_config);

	if (IS_ERR(priv->regmap))
		pr_warn("%s: regmap initialization failed", swdev->devname);

	pr_info("%s: %s rev. %u switch registered on %s\n",
		swdev->devname, swdev->name, priv->chip_rev,
		dev_name(&priv->mii_bus->dev));

found:
	priv->use_count++;

	if (phydev->addr == 0) {
		if (ar8xxx_has_gige(priv)) {
			phydev->supported = SUPPORTED_1000baseT_Full;
			phydev->advertising = ADVERTISED_1000baseT_Full;
		} else {
			phydev->supported = SUPPORTED_100baseT_Full;
			phydev->advertising = ADVERTISED_100baseT_Full;
		}

		if (chip_is_ar8327(priv) || chip_is_ar8337(priv)) {
			priv->phy = phydev;

			ret = ar8xxx_start(priv);
			if (ret)
				goto err_unregister_switch;
		}
	} else {
		if (ar8xxx_has_gige(priv)) {
			phydev->supported |= SUPPORTED_1000baseT_Full;
			phydev->advertising |= ADVERTISED_1000baseT_Full;
		}
	}

	phydev->priv = priv;

	list_add(&priv->list, &ar8xxx_dev_list);

	mutex_unlock(&ar8xxx_dev_list_lock);

	return 0;

err_unregister_switch:
	if (--priv->use_count)
		goto unlock;

	unregister_switch(&priv->dev);

free_priv:
	ar8xxx_free(priv);
unlock:
	mutex_unlock(&ar8xxx_dev_list_lock);
	return ret;
}

static void
ar8xxx_phy_detach(struct phy_device *phydev)
{
	struct net_device *dev = phydev->attached_dev;

	if (!dev)
		return;

	dev->phy_ptr = NULL;
	dev->priv_flags &= ~IFF_NO_IP_ALIGN;
	dev->eth_mangle_rx = NULL;
	dev->eth_mangle_tx = NULL;
}

static void
ar8xxx_phy_remove(struct phy_device *phydev)
{
	struct ar8xxx_priv *priv = phydev->priv;

	if (WARN_ON(!priv))
		return;

	phydev->priv = NULL;
	if (--priv->use_count > 0)
		return;

	mutex_lock(&ar8xxx_dev_list_lock);
	list_del(&priv->list);
	mutex_unlock(&ar8xxx_dev_list_lock);

	unregister_switch(&priv->dev);
	ar8xxx_mib_stop(priv);
	ar8xxx_free(priv);
}

static struct phy_driver ar8xxx_phy_driver = {
	.phy_id		= 0x004d0000,
	.name		= "Atheros AR8216/AR8236/AR8316",
	.phy_id_mask	= 0xffff0000,
	.features	= PHY_BASIC_FEATURES,
	.probe		= ar8xxx_phy_probe,
	.remove		= ar8xxx_phy_remove,
	.detach		= ar8xxx_phy_detach,
	.config_init	= ar8xxx_phy_config_init,
	.config_aneg	= ar8xxx_phy_config_aneg,
	.read_status	= ar8xxx_phy_read_status,
	.driver		= { .owner = THIS_MODULE },
};

int __init
ar8xxx_init(void)
{
	register_netdevice_notifier(&vlandev_notifier);
	return phy_driver_register(&ar8xxx_phy_driver);
}

void __exit
ar8xxx_exit(void)
{
	phy_driver_unregister(&ar8xxx_phy_driver);
	unregister_netdevice_notifier(&vlandev_notifier);
}

module_init(ar8xxx_init);
module_exit(ar8xxx_exit);
MODULE_LICENSE("GPL");

