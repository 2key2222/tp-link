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

#define MT_7628_PVID_REG_ADDR_0        (0x40)
#define MT_7628_VLAN_ID_REG_ADDR_0     (0x50)
#define MT_7628_VLAN_MEM_REG_ADDR_0    (0x70)
#define MT_7628_UNTAG_REG_ADDR_0       (0x100)


#define MT_7628_POA_ADDR               (0x80)
#define MT_7628_RESET_ADDR             (0xA0)
#define MT_7628_PORT_CTRL_2_ADDR       (0x98)

int setup_switch(struct net_device *dev);
