
#ifndef __AR8236_H__
#define __AR8236_H__

#include <common.h>
#include <net.h>
#include <netdev.h>
#include <config.h>
#include <malloc.h>
#include <asm/io.h>
#include <phy.h>
#include <miiphy.h>
#include <watchdog.h>
#include <linux/compat.h>
#include <linux/mbus.h>
#include <fdtdec.h>
#include <fdt.h>
#include <pci.h>
#include <config/arch/mvebu.h>
#include <command.h>

#define PORT_SWITCH_ID_AR8236		0x004dd043

#define AR8236_PORT_OFFSET(_i)		(0x0100 * (_i + 1))

#define AR8236_REG_CTRL			0x0000
#define   AR8236_CTRL_REVISION		BITS(0, 8)
#define   AR8236_CTRL_REVISION_S	0
#define   AR8236_CTRL_VERSION		BITS(8, 8)
#define   AR8236_CTRL_VERSION_S		8
#define   AR8236_CTRL_RESET		BIT(31)

#define AR8236_REG_PORT_STATUS(_i)	(AR8236_PORT_OFFSET(_i) + 0x0000)
#define   AR8236_PORT_STATUS_SPEED	BITS(0,2)
#define   AR8236_PORT_STATUS_SPEED_S	0
#define   AR8236_PORT_STATUS_TXMAC	BIT(2)
#define   AR8236_PORT_STATUS_RXMAC	BIT(3)
#define   AR8236_PORT_STATUS_TXFLOW	BIT(4)
#define   AR8236_PORT_STATUS_RXFLOW	BIT(5)
#define   AR8236_PORT_STATUS_DUPLEX	BIT(6)
#define   AR8236_PORT_STATUS_TX_HALF_FLOW	BIT(7)
#define   AR8236_PORT_STATUS_LINK_UP	BIT(8)
#define   AR8236_PORT_STATUS_LINK_AUTO	BIT(9)
#define   AR8236_PORT_STATUS_LINK_PAUSE	BIT(10)
#define   AR8236_PORT_STATUS_LINK_FLOW_EN	BIT(12)

#define AR8236_REG_PORT_CTRL(_i)	(AR8236_PORT_OFFSET(_i) + 0x0004)
/* port forwarding state */
#define   AR8236_PORT_CTRL_STATE	BITS(0, 3)
#define   AR8236_PORT_CTRL_STATE_S	0
#define   AR8236_PORT_CTRL_LEARN_LOCK	BIT(7)
/* egress 802.1q mode */
#define   AR8236_PORT_CTRL_VLAN_MODE	BITS(8, 2)
#define   AR8236_PORT_CTRL_VLAN_MODE_S	8
#define   AR8236_PORT_CTRL_IGMP_SNOOP	BIT(10)
#define   AR8236_PORT_CTRL_HEADER	BIT(11)
#define   AR8236_PORT_CTRL_MAC_LOOP	BIT(12)
#define   AR8236_PORT_CTRL_SINGLE_VLAN	BIT(13)
#define   AR8236_PORT_CTRL_LEARN	BIT(14)
#define   AR8236_PORT_CTRL_MIRROR_TX	BIT(16)
#define   AR8236_PORT_CTRL_MIRROR_RX	BIT(17)

#define AR8236_REG_MIB_FUNC		0x0080
#define   AR8236_MIB_TIMER		BITS(0, 16)
#define   AR8236_MIB_AT_HALF_EN		BIT(16)
#define   AR8236_MIB_BUSY		BIT(17)
#define   AR8236_MIB_FUNC		BITS(24, 3)
#define   AR8236_MIB_FUNC_S		24
#define   AR8236_MIB_FUNC_NO_OP		0x0
#define   AR8236_MIB_FUNC_FLUSH		0x1
#define   AR8236_MIB_FUNC_CAPTURE	0x3
#define   AR8236_MIB_EN			BIT(30)

/* port speed */
enum {
        AR8236_PORT_SPEED_10M = 0,
        AR8236_PORT_SPEED_100M = 1,
        AR8236_PORT_SPEED_1000M = 2,
        AR8236_PORT_SPEED_ERR = 3,
};

struct ar8236_dev {
	unsigned int phy_addr;
	unsigned int port_mask;
	int id;
	int cpu_port;	/* The switch port to which the CPU is attached */
};

enum ar8236_sw_opts {
	AR8236_SW_INFO,
	AR8236_SW_READ,
	AR8236_SW_WRITE,
	AR8236_SW_LED,
	AR8236_SW_NA
};

#endif
