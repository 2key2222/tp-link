/*
 * Copyright (C) 2016 Stefan Roese <sr@denx.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _CONFIG_MVEBU_ARMADA_8K_H
#define _CONFIG_MVEBU_ARMADA_8K_H

#define CONFIG_LAST_STAGE_INIT

#define CONFIG_DEFAULT_CONSOLE		"console=ttyS0,115200"

/* USB 2.0 */
#define CONFIG_SYS_USB_EHCI_MAX_ROOT_PORTS 3

/* USB 3.0 */
#define CONFIG_SYS_USB_XHCI_MAX_ROOT_PORTS 3

#include <configs/mvebu_armada-common.h>

/*
 * High Level Configuration Options (easy to change)
 */
#define CONFIG_SYS_TCLK		250000000	/* 250MHz */
#define CONFIG_NR_DRAM_BANKS	2

/*
 * SPI Flash configuration
 */
#define CONFIG_KIRKWOOD_SPI

/* Environment in MMC */
#define CONFIG_SYS_MMC_ENV_DEV		0

#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_MAX_CHIPS	1
#define CONFIG_SYS_NAND_ONFI_DETECTION
#define CONFIG_SYS_NAND_USE_FLASH_BBT

/*
 * Ethernet Driver configuration
 */
#define CONFIG_PHY_GIGE		/* GbE speed/duplex detect */
#define CONFIG_ARP_TIMEOUT	200
#define CONFIG_NET_RETRY_COUNT	50

/*
 * PCI configuration
 */
#ifdef CONFIG_PCIE_DW_MVEBU
#define CONFIG_E1000
#define CONFIG_CMD_PCI
#endif

/* RTC configuration */
#ifdef CONFIG_MVEBU_RTC
#define ERRATA_FE_3124064
#define CONFIG_CMD_DATE
#endif

/* #define FORCE_PROBE_RTL8367C */
#define CONFIG_PHY_REALTEK 
#define MDC_MDIO_OPERATION

#endif /* _CONFIG_MVEBU_ARMADA_8K_H */
