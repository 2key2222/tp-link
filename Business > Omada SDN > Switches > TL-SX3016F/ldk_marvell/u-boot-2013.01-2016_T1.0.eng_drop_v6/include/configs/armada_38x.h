/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
/*******************************************************************************
   Copyright (C) Marvell International Ltd. and its affiliates

********************************************************************************
   Marvell GPL License Option

   If you received this File from Marvell, you may opt to use, redistribute and/or
   modify this File in accordance with the terms and conditions of the General
   Public License Version 2, June 1991 (the "GPL License"), a copy of which is
   available along with the File in the license.txt file or by writing to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 or
   on the worldwide web at http://www.gnu.org/licenses/gpl.txt.

   THE FILE IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE IMPLIED
   WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY
   DISCLAIMED.  The GPL License provides additional details about this warranty
   disclaimer.
*******************************************************************************/

#ifndef __CONFIG_H
#define __CONFIG_H

#include <config.h>
#include "mv_version.h"
#include <tplink_comboinfo.h>

//#define UBOOT_DEBUG

#define TPLINK_CUSTOM
#define TPLINK_USB_CONSOLE


#define CONFIG_DISABLE_CONSOLE      /* disable console */


/*
 * Plaform
 */

/*
 * Machine
 */

#include "../../board/mv_ebu/a38x/mvSysHwConfig.h"

/* Version number passed to kernel */
#define VER_NUM 0x13010000              /* 2013.01 */

/*
 * General
 */
#ifdef CONFIG_ARMADA_38X
	#define MV88F68XX
#endif
#ifdef CONFIG_ARMADA_39X
	#define MV88F69XX
#endif
#define CONFIG_SWITCHING_SERVICES
#define MV_SEC_64K
#define MV_BOOTSIZE_512K
#define MV_LARGE_PAGE
#define MV_DDR_64BIT
#define MV_BOOTROM

#if defined (CONFIG_CUSTOMER_BOARD_0) || defined (CONFIG_CUSTOMER_BOARD_1) || defined (CONFIG_CLEARFOG_BOARD)
#define CONFIG_CUSTOMER_BOARD_SUPPORT
#endif

#ifdef MV_INCLUDE_SWITCH
/*ARMADA38x switch resgiters are accessed by SMI*/
/*we provide name unified switch register access APIs with different implementations according to the access way*/
#define MV_SWITCH_SMI_ACCESS
#endif

#define CONFIG_FIT


#define MV_USB
#define MV_FS
#define CONFIG_CMD_DATE
#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_PIC_GPIO 		/*  support GPIO signals for PIC (programmable interface circuit) */

#define MV_DDR_TRAINING_CMD_NEW_TIP

/*
 * Debug
 */
//#define MV_RT_DEBUG
#define CONFIG_SYS_INIT_SP_ADDR         0x00FF0000      /* end of 16M scrubbed by training in bootrom */
#define CONFIG_SYS_ATA_BASE_ADDR        0x20000000
#define CONFIG_SYS_ATA_REG_OFFSET       0x0000          /* Offset for normal register accesses*/
#define CONFIG_SYS_ATA_DATA_OFFSET      0x0000          /* Offset for data I/O */

/*
 * Marvell Monitor Extension
 */
#define enaMonExt()                     MV_FALSE

/*
 * Clock
 */
#ifndef __ASSEMBLY__
extern unsigned int mvSysClkGet(void);
extern unsigned int mvTclkGet(void);
extern unsigned int mvBoardSpiBusGet(void);
extern unsigned int mvUartPortGet(void);
	#define UBOOT_CNTR              0               /* counter to use for uboot timer */
	#define MV_TCLK_CNTR            1               /* counter to use for uboot timer */
	#define MV_REF_CLK_DEV_BIT      1000            /* Number of cycle to eanble timer */
	#define MV_REF_CLK_BIT_RATE     100000          /* Ref clock frequency */
	#define MV_REF_CLK_INPUT_GPP    6               /* Ref clock frequency input */

	#define CONFIG_SYS_HZ                   1000
	#define CONFIG_SYS_TCLK                 mvTclkGet()
	#define CONFIG_SYS_BUS_HZ               mvSysClkGet()
	#define CONFIG_SYS_BUS_CLK              CONFIG_SYS_BUS_HZ
	#define CONFIG_SYS_FPGA_DRAM_SIZE       _256M
#endif /* __ASSEMBLY__ */

//#define CONFIG_DISPLAY_CPUINFO

/********************/
/* Page Table settings */
/********************/
#define MV_PT

#ifdef MV_PT
	#define MV_PT_BASE(cpu)  (CONFIG_SYS_MALLOC_BASE - 0x20000 - (cpu * 0x20000))
#endif /* MV_PT */

/*
 * High Level Configuration Options
 */
#define CONFIG_MARVELL
#define CONFIG_API

/*
 * Commands
 */
#define CONFIG_BOOTP_MASK       (CONFIG_BOOTP_DEFAULT | CONFIG_BOOTP_BOOTFILESIZE)
//#define CONFIG_CMD_DHCP
//#define CONFIG_CMD_ELF
#define CONFIG_CMD_I2C
//#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_NET
#define CONFIG_CMD_PING
//#define CONFIG_CMD_LOADS
#define CONFIG_CMD_BSP
#define CONFIG_CMD_MEMORY
//#define CONFIG_CMD_BOOTD
#define CONFIG_CMD_BOOTZ
#define CONFIG_CMD_CONSOLE
#define CONFIG_CMD_RUN
#define CONFIG_CMD_MISC
//#define CONFIG_CMD_IDE
//#define CONFIG_CMD_SCSI
#define CONFIG_CMD_SAR
//#define CONFIG_CMD_STAGE_BOOT
#define CONFIG_CMD_RCVR
//#define CONFIG_CMD_BOOT_MENU
//#define CONFIG_CMD_SYS_RESTORE
#define CONFIG_CMD_TFTPPUT

//#define CONFIG_PHYLIB
//#define CONFIG_PHY_REALTEK
/* Open this define for enabling Secure Boot Mode eFuses modification
#define CONFIG_CMD_EFUSE
*/
#ifdef CONFIG_ARMADA_39X
	#ifndef CONFIG_CUSTOMER_BOARD_SUPPORT
		#define MV_CROSS_FLASH_BOOT
		#define CONFIG_CMD_BOARDCFG
	#endif /* CONFIG_CUSTOMER_BOARD_SUPPORT */
	/* Enable IPv6 for Armada-39x only */
	#define CONFIG_CMD_NET6
#endif /* CONFIG_ARMADA_39X */

#define	CONFIG_ENV_MIN_ENTRIES 128

#if defined(MV_INCLUDE_PEX) || defined(MV_INCLUDE_PCI)
	#define CONFIG_PCI
	#define CONFIG_CMD_PCI
	#define CONFIG_PCIE_IF_MAPPING
#endif

/* Pre eXecution Environment (PXE) support*/
//#define CONFIG_CMD_PXE
//#define CONFIG_BOOTP_PXE
//#define CONFIG_MENU
//#define CONFIG_BOOTP_PXE_CLIENTARCH	0x100
//#ifdef CONFIG_ARMADA_38X
//#define CONFIG_BOOTP_VCI_STRING		"U-boot.armv7.armada_38x"
//#elif defined CONFIG_ARMADA_39X
//#define CONFIG_BOOTP_VCI_STRING         "U-boot.armv7.armada_39x"
//#endif

/* Flattened Device Tree (FDT) support */
#define CONFIG_OF_LIBFDT               1
#define CONFIG_OF_BOARD_SETUP
#undef CONFIG_OF_LIBFDT_IS_DEFAULT   /* dft is the default for bootcmd */

#ifdef MV_FS
/* FS supported */
//#define CONFIG_CMD_EXT2
//#define CONFIG_CMD_EXT4
#define CONFIG_FS_EXT4
//#define CONFIG_CMD_EXT4_WRITE
//#define CONFIG_EXT4_WRITE
#define CONFIG_CMD_JFFS2
//#define CONFIG_CMD_FAT
#define CONFIG_FS_FAT
//#define CONFIG_SUPPORT_VFAT

#define CONFIG_SYS_USE_UBI
#ifdef CONFIG_SYS_USE_UBI
	//#define CONFIG_CMD_UBI
	//#define CONFIG_CMD_UBIFS
	#define CONFIG_MTD_DEVICE
	#define CONFIG_MTD_PARTITIONS
	#define CONFIG_CMD_MTDPARTS
	#define CONFIG_RBTREE
	#define CONFIG_LZO
#endif /* CONFIG_SYS_USE_UBI */

#endif /* MV_FS */
/* this must be included AFTER the definition of CONFIG_COMMANDS (if any) */
#include <config_cmd_default.h>

#define	CONFIG_SYS_MAXARGS	32	/* max number of command args	*/

/*-----------------------------------------------------------------------
 * IDE/ATA/SATA stuff (Supports IDE harddisk on PCMCIA Adapter)
 *-----------------------------------------------------------------------
 */

#undef	CONFIG_IDE_8xx_PCCARD		/* Use IDE with PC Card	Adapter	*/

#undef	CONFIG_IDE_8xx_DIRECT		/* Direct IDE    not supported	*/
#undef	CONFIG_IDE_LED			/* LED   for ide not supported	*/
#undef	CONFIG_IDE_RESET		/* reset for ide not supported	*/

#define CONFIG_SYS_IDE_MAXBUS		4				/* max. 1 IDE bus		*/
#define CONFIG_SYS_IDE_MAXDEVICE	CONFIG_SYS_IDE_MAXBUS * 8	/* max. 1 drive per IDE bus	*/

#define CONFIG_SYS_ATA_IDE0_OFFSET	0x0000

#undef CONFIG_MAC_PARTITION
#define CONFIG_DOS_PARTITION
#define CONFIG_EFI_PARTITION


#define CONFIG_SYS_64BIT_LBA			/*    Support disk over 2TB        */
#define CONFIG_LBA48

//#define CONFIG_SCSI_MV92XX
//#define CONFIG_SCSI_6820

#if defined(CONFIG_SCSI_MV92XX) || defined(CONFIG_SCSI_6820)
#define CONFIG_LIBATA
#define CONFIG_SCSI_AHCI
#define CONFIG_SCSI_MAX_CONTROLLERS	6 /* based on MV_PEX_MAX_UNIT */
#define CONFIG_SYS_SCSI_MAX_SCSI_ID	(4 * CONFIG_SCSI_MAX_CONTROLLERS)
#define CONFIG_SYS_SCSI_MAX_LUN		1
#define CONFIG_SYS_SCSI_MAX_DEVICE	(CONFIG_SYS_SCSI_MAX_SCSI_ID * CONFIG_SYS_SCSI_MAX_LUN)
#define CONFIG_SCSI_DEV_LIST		{ 0x1B4B, 0x9215 }, { 0x1B4B, 0x9235 }, { 0, 0 }
#endif /* CONFIG_SCSI_MV92XX  CONFIG_SCSI_6820 */

#ifdef  CONFIG_SCSI_6820
#define CONFIG_SCSI_AHCI_PLAT
#define ENV_SATA_ACTIVE          "0"	/* active port */
#endif /* CONFIG_SCSI_6820 */


/* #define CONFIG_SCSI_MV94XX */
#ifdef  CONFIG_SCSI_MV94XX
	#define CONFIG_SYS_SCSI_MAX_SCSI_ID	40 /*8 PM * 5 sata port*/
	#define CONFIG_SYS_SCSI_MAX_LUN	1
	#define CONFIG_SYS_SCSI_MAX_DEVICE 	(CONFIG_SYS_SCSI_MAX_SCSI_ID * CONFIG_SYS_SCSI_MAX_LUN)
#endif /* CONFIG_SCSI_AHCI */

/*
 * U-Boot
 */
#define CONFIG_SYS_MAXARGS      32      /* max number of command argg */

/* SPI Flash configuration   */
/*****************************/
#if defined(MV_INCLUDE_SPI)
	#define CONFIG_CMD_SPI
	#define CONFIG_CMD_SF
	#define CONFIG_SPI_FLASH
	#define CONFIG_SPI_FLASH_STMICRO
	#define CONFIG_SPI_FLASH_MACRONIX
	#define CONFIG_SPI_FLASH_WINBOND
	//#define CONFIG_ENV_SPI_MAX_HZ           50000000
	#define CONFIG_ENV_SPI_MAX_HZ           10000000
	#define CONFIG_ENV_SPI_CS               0
	#define CONFIG_ENV_SPI_BUS              1 /*mvBoardSpiBusGet()*/
	#define CONFIG_SPI_FLASH_WINBOND
	#define CONFIG_SPI_FLASH_GIGADEVICE

#if defined(MV_SEC_64K)
	#define CONFIG_ENV_SECT_SIZE_SPI		0x10000
#elif defined(MV_SEC_128K)
	#define CONFIG_ENV_SECT_SIZE_SPI		0x20000
#elif defined(MV_SEC_256K)
	#define CONFIG_ENV_SECT_SIZE_SPI		0x40000
#endif

#define CONFIG_ENV_SIZE_SPI		CONFIG_ENV_SECT_SIZE_SPI	/* environment takes one sector */
#define CONFIG_ENV_OFFSET_SPI		0xE0000			/* (1MB For Image) environment starts here  */
//#define CONFIG_ENV_OFFSET_SPI		0x100000

#define SPI_FLASH_BYTE_MODE 3

#ifndef CONFIG_SF_DEFAULT_SPEED
# define CONFIG_SF_DEFAULT_SPEED        CONFIG_ENV_SPI_MAX_HZ
#endif
#ifndef CONFIG_SF_DEFAULT_MODE
# define CONFIG_SF_DEFAULT_MODE         SPI_MODE_3
#endif
#ifndef CONFIG_SF_DEFAULT_CS
# define CONFIG_SF_DEFAULT_CS		CONFIG_ENV_SPI_CS
#endif
#ifndef CONFIG_SF_DEFAULT_BUS
#define CONFIG_SF_DEFAULT_BUS		CONFIG_ENV_SPI_BUS
#endif

/* Boot from SPI settings */
	#if defined(MV_SPI_BOOT)
		#define CONFIG_ENV_IS_IN_SPI_FLASH

		#define CONFIG_ENV_SECT_SIZE           		CONFIG_ENV_SECT_SIZE_SPI

		#define CONFIG_ENV_SIZE                         CONFIG_ENV_SECT_SIZE    /* environment takes one sector */
		#define CONFIG_ENV_OFFSET                       CONFIG_ENV_OFFSET_SPI
		#define CONFIG_ENV_ADDR                         CONFIG_ENV_OFFSET
		#define MONITOR_HEADER_LEN                      0x200
		#define CONFIG_SYS_MONITOR_BASE                 0
		#define CONFIG_SYS_MONITOR_LEN                  0x80000                 /*(512 << 10) Reserve 512 kB for Monitor */

		#ifndef MV_INCLUDE_NOR
			#ifdef MV_BOOTROM
				#define CONFIG_SYS_FLASH_BASE           DEVICE_SPI_BASE
				#define CONFIG_SYS_FLASH_SIZE           _16M
			#else
				#define CONFIG_SYS_FLASH_BASE           BOOTDEV_CS_BASE
				#define CONFIG_SYS_FLASH_SIZE           BOOTDEV_CS_SIZE
			#endif  /* ifdef MV_BOOTROM */
		#endif
	#endif                  //#if defined(MV_SPI_BOOT)
#endif                          //#if defined(MV_SPI)

#define CONFIG_SYS_NAND_MAX_CHIPS 1     /* pass compilation for non NAND board configuration */

/* NAND-FLASH stuff     */
/************************/
#ifdef MV_NAND
	#ifndef __ASSEMBLY__
extern int nand_get_env_offs(void);
	#endif /* __ASSEMBLY__ */

	#define MV_NAND_PIO_MODE
	#define MV_NAND_1CS_MODE
	/* The following defines are masked for a38x:
	   If the system is booted from NAND, the ECC mode is being detected
	   by mvBoardNandECCModeGet from Sample at Reset boot device selection.
	   To statically override such ECC mode, unmask one of the following ECC modes:
		#define MV_NAND_4BIT_MODE
		#define MV_NAND_8BIT_MODE
		#define MV_NAND_12BIT_MODE
		#define MV_NAND_16BIT_MODE
	*/
	/* For cases when NAND is not a boot device,
	   the pre-defined ECC mode is always required
	 */
	#ifndef MV_NAND_BOOT
		#define MV_NAND_8BIT_MODE
	#endif
	#define MTD_NAND_NFC_INIT_RESET

	#define CONFIG_SYS_MAX_NAND_DEVICE 1
	#define CONFIG_CMD_NAND
	#define CONFIG_CMD_NAND_TRIMFFS
	#define CONFIG_MV_MTD_GANG_SUPPORT
	#define CONFIG_MV_MTD_MLC_NAND_SUPPORT
	#define CONFIG_SYS_64BIT_VSPRINTF
	#define CONFIG_SKIP_BAD_BLOCK
	#undef MV_NFC_DBG
	#define CONFIG_JFFS2_NAND


	#define CONFIG_ENV_SIZE_NAND			0x80000
	#define CONFIG_ENV_OFFSET_NAND			nand_get_env_offs()
	#define CONFIG_ENV_RANGE_NAND			CONFIG_ENV_SIZE_NAND * 8

/* Boot from NAND settings */
	#if defined(MV_NAND_BOOT)
		#define CONFIG_ENV_IS_IN_NAND

		#define CONFIG_ENV_SIZE                 CONFIG_ENV_SIZE_NAND                 /* environment takes one erase block */
		#define CONFIG_ENV_OFFSET               nand_get_env_offs()     /* environment starts here  */
		#define CONFIG_ENV_ADDR                 CONFIG_ENV_OFFSET
		#define MONITOR_HEADER_LEN              0x200
		#define CONFIG_SYS_MONITOR_BASE         0
		#define CONFIG_SYS_MONITOR_LEN          0x80000           /* Reserve 512 kB for Monitor */
		#define CONFIG_ENV_RANGE                CONFIG_ENV_RANGE_NAND

		#define MV_NBOOT_BASE                   0
		#define MV_NBOOT_LEN                    (4 << 10)       /* Reserved 4KB for boot strap */
	#endif /* MV_NAND_BOOT */
#endif /* MV_NAND */
/*
 * Board init
 */
/* which initialization functions to call for this board */
#define CONFIG_MISC_INIT_R              /* after relloc initialization*/
#define CONFIG_ENV_OVERWRITE            /* allow to change env parameters */
#undef  CONFIG_WATCHDOG                 /* watchdog disabled */

/*
 * Cache
 */
#define CONFIG_SYS_DCACHE_OFF
#define CONFIG_SYS_CACHELINE_SIZE       32

/*
 * Global definitions
 */
#define CONFIG_SYS_TEXT_BASE            0x00000000
#define CONFIG_SYS_SDRAM_BASE           0x00000000
#define CONFIG_SYS_RESET_ADDRESS        0xffff0000
#define CONFIG_SYS_MALLOC_BASE          (CONFIG_SYS_TEXT_BASE + (3 << 20))      /* TEXT_BASE + 3M */

#define CONFIG_SYS_MALLOC_LEN           (5 << 20)                               /* Reserve 5MB for malloc*/
#define CONFIG_SYS_GBL_DATA_SIZE        128                                     /* size in bytes reserved for init data */

/*
 * DRAM
 */
#define CONFIG_SYS_DRAM_BANKS           2
#define CONFIG_NR_DRAM_BANKS            2

#define CONFIG_SYS_MEMTEST_START        0x00400000
#define CONFIG_SYS_MEMTEST_END          0x007fffff

/*
 * RTC
 */
#if defined(CONFIG_CMD_DATE)
	#define CONFIG_SYS_NVRAM_SIZE  0x00                     /* dummy */
	#define CONFIG_SYS_NVRAM_BASE_ADDR DEVICE_CS1_BASE      /* dummy */
#endif

/*
 * Serial + Parser
 */
#define CONFIG_BAUDRATE				38400
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600 }
#define CONFIG_SYS_DUART_CHAN		0

#define CONFIG_LOADS_ECHO               0       /* echo off for serial download */
#define CONFIG_SYS_LOADS_BAUD_CHANGE            /* allow baudrate changes       */

#define CONFIG_SYS_CONSOLE_INFO_QUIET           /* don't print In/Out/Err console assignment. */

/*
 * Parser
 */
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_AUTO_COMPLETE

#define CONFIG_SYS_PROMPT_HUSH_PS2      "> "

#define CONFIG_SYS_LONGHELP                                                                     /* undef to save memory		*/
#define CONFIG_SYS_PROMPT               "Marvell>> "                                            /* Monitor Command Prompt	*/
#define CONFIG_SYS_CBSIZE               1024                                                    /* Console I/O Buffer Size	*/
#define CONFIG_SYS_PBSIZE               (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)    /* Print Buffer Size */

/*
 * Ethernet
 */
#define MV_ETH_NETA
#define CONFIG_MV_ETH_NETA
#ifdef CONFIG_ARMADA_39X
#define CONFIG_NET_COMPLEX
#define CONFIG_MV_XSMI
#define CONFIG_MV_ETH_10G
#define CONFIG_MV_ETH_FW_DOWNLOAD
#endif
/* to change the default ethernet port, use this define (options: 0, 1, 2) */
#define CONFIG_NET_MULTI
#define ENV_ETH_PRIME		"egiga1"


#define CONFIG_IPADDR		192.168.0.30
#define CONFIG_SERVERIP		192.168.0.146
#define CONFIG_NETMASK		255.255.255.0
#define ETHADDR			"00:0A:EB:00:13:01"
#define ETH1ADDR		"00:0A:EB:00:13:01"

/*
 * PCI and PCIe
 */

/*
 * USB
 */
#ifdef MV_USB
	#define CONFIG_USB_EHCI
	#define CONFIG_USB_XHCI
	#define CONFIG_SYS_USB_XHCI_MAX_ROOT_PORTS  1
	#define MV_INCLUDE_USB
	#define MV_INCLUDE_USB_DEVICE
	#define CONFIG_CMD_USB
	#define CONFIG_USB_STORAGE
	#define CONFIG_EHCI_IS_TDI
	#define CONFIG_DOS_PARTITION
	#define CONFIG_ISO_PARTITION
	#define ENV_USB0_MODE   "host"
#ifdef CONFIG_CLEARFOG_BOARD
	#define ENV_USB_ACTIVE        "1"
	#define ENV_USB_MODE          "3"	/* 3 = USB3.0 | 2 = USB2.0 */
#else
	#define ENV_USB_ACTIVE        "0"
	#define ENV_USB_MODE          "2"	/* 3 = USB3.0 | 2 = USB2.0 */
#endif

	#define CONFIG_USB_HOST_ETHER
	#define CONFIG_USB_ETHER_ASIX
	/* Marvell encapsulate it's USB usage with usbActive internal index,
	 * the usb stack uses 1 controller simultaneously */
	#define CONFIG_USB_MAX_CONTROLLER_COUNT		1
	/* xHCI code relies on index receiving from that usbActive,
	 * which could go up to 2. this requires xHCI arrays to be as big as
	 * the actual USB host count */
	#define CONFIG_USB_MAX_CONTROLLER_HOST_COUNT	2

	#define MV_USB_VBUS_CYCLE

#if defined(CONFIG_USB_XHCI) || defined(CONFIG_USB_EHCI)
	#define CONFIG_USB_XHCI_HCD /* set kernel define - for mv_hal/usb usage */
#endif /* CONFIG_USB_XHCI */
#else
	#undef MV_INCLUDE_USB
	#undef CONFIG_CMD_USB
	#undef CONFIG_USB_STORAGE
#endif /* MV_USB */

/************/
/* SDIO/MMC */
/************/
#define CONFIG_MMC
#define CONFIG_CMD_MMC
#define CONFIG_GENERIC_MMC		1
#undef	CONFIG_MRVL_MMC
#define CONFIG_MV_SDHCI			1
#define CONFIG_SDHCI			1
#define CONFIG_MMC_SDMA			1
#define CONFIG_MMC_SDHCI_IO_ACCESSORS	1
#define CONFIG_SYS_MMC_MAX_DEVICE	1
#define CONFIG_SYS_MMC_MAX_BLK_COUNT	0x100
#define CONFIG_SYS_MMC_NUM		1

#ifndef MV_SDMMC_REGS_OFFSET
#define MV_SDMMC_REGS_OFFSET			(0xD8000)
#endif
#define CONFIG_SYS_MMC_BASE			(INTER_REGS_BASE + MV_SDMMC_REGS_OFFSET)

/* MMC configuration   */
/*****************************/
//#define CONFIG_MMC_TRACE
/* Boot from MMC settings */
#if defined(MV_MMC_BOOT)
/* the following commands are supported only with SPI/NAND interfaces */
#if (!defined(MV_INCLUDE_SPI) && !defined(MV_NAND))
	#undef CONFIG_CMD_SOURCE	/* cmd_mvsource.c supports script burning to SPI/NAND only */
	#undef CONFIG_CMD_STAGE_BOOT
	#undef CONFIG_CMD_RCVR
	#undef CONFIG_CMD_BOOT_MENU
	#undef CONFIG_CMD_SYS_RESTORE
#endif
	#define CONFIG_ENV_IS_IN_MMC	/* Environment is at absolute location (RAW) */
//	#define CONFIG_ENV_IS_IN_FAT	/* Environment is in file on FAT partition */
//	#define CONFIG_FAT_WRITE
//	#define FAT_ENV_INTERFACE		"mmc"
//	#define FAT_ENV_DEVICE			0
//	#define FAT_ENV_PART			1
//	#define FAT_ENV_FILE			"u-boot.env"

//	#define CONFIG_SYS_MMC_ENV_PART			1 /* Valid for MMC/eMMC for separating boot image and env */
	#define CONFIG_SYS_MMC_ENV_DEV			0
	#define CONFIG_ENV_SECT_SIZE			0x200
	#define CONFIG_ENV_SIZE					0x80000
	/* For SD - reserve 1 LBA for MBR + 1M for u-boot image. The MMC/eMMC boot image starts @ LBA-0.
	   As result in MMC/eMMC case it will be a 1 sector gap between u-boot image and environment */
	#define CONFIG_ENV_OFFSET				(_1M + CONFIG_ENV_SECT_SIZE)
	#define CONFIG_ENV_ADDR					CONFIG_ENV_OFFSET
	#define MONITOR_HEADER_LEN				0x200
	#define CONFIG_SYS_MONITOR_BASE			0
	#define CONFIG_SYS_MONITOR_LEN			0x80000					/*(512 << 10) Reserve 512 kB for Monitor */

#endif /* #if defined(MV_MMC_BOOT) */


/*
 * Linux boot and other
 */
/* this define is to support different nand node name in Linux mainline
   currently in Linux 3.14/3.10 same name used "nand@"*/
#define MV_NFC_FDT_NODE_NAME    "nand@"
#define MV_MMC_FDT_NODE_NAME	"sdhci"

#ifdef CONFIG_ARMADA_38X
#define MV_BOOTARGS_END         ":192.168.0.254:255.255.255.0:Armada38x:eth1:none"
#define MV_DDR_L2_ALIGNMENT
#elif defined CONFIG_ARMADA_39X
#define MV_BOOTARGS_END         ":192.168.0.254:255.255.255.0:Armada39x:eth1:none"
#endif
#define RCVR_IP_ADDR            "169.254.100.100"
#define RCVR_LOAD_ADDR          "0x02000000"

#define CONFIG_ZERO_BOOTDELAY_CHECK

#define CONFIG_SYS_LOAD_ADDR    0x02000000      /* default load address	*/
#define CONFIG_SYS_MIN_HDR_DEL_SIZE 0x100

#undef  CONFIG_BOOTARGS

/*
 * Auto boot
 */
#define CONFIG_BOOTDELAY                3
#define CONFIG_ROOTPATH                 "/srv/nfs/"             /* Default Dir for NFS */
#define CONFIG_SYS_BARGSIZE             CONFIG_SYS_CBSIZE       /* Boot Argument Buffer Size */

/*
 * For booting Linux, the board info and command line data
 * have to be in the first 8 MB of memory, since this is
 * the maximum mapped by the Linux kernel during initialization.
 */
#define CONFIG_SYS_BOOTMAPSZ    (16 << 20)      /* Initial Memory map for Linux */

#define BRIDGE_REG_BASE_BOOTM   0xfbe00000      /* this paramaters are used when booting the linux kernel */

#define CONFIG_CMDLINE_TAG              1       /* enable passing of ATAGs  */
#define CONFIG_CMDLINE_EDITING          1
#define CONFIG_INITRD_TAG               1       /* enable INITRD tag for ramdisk data */
#define CONFIG_SETUP_MEMORY_TAGS        1
#define CONFIG_MARVELL_TAG
#define ATAG_MARVELL                    0x41000403

/*
 * I2C
 */
#if defined(CONFIG_CMD_I2C)
	#define CONFIG_I2C_MULTI_BUS
	#define CONFIG_SYS_MAX_I2C_BUS          2
	#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN  1
	#define CONFIG_SYS_I2C_MULTI_EEPROMS
	#define CONFIG_SYS_I2C_SPEED            100000  /* I2C speed default */
#endif

/*
 * PCI
 */
#ifdef CONFIG_PCI
	#define CONFIG_PCI_HOST PCI_HOST_FORCE  /* select pci host function     */
	#define CONFIG_PCI_PNP                  /* do pci plug-and-play         */

/* PnP PCI Network cards */
	#define CONFIG_EEPRO100 /* Support for Intel 82557/82559/82559ER chips */
	#define CONFIG_E1000
	#define YUK_ETHADDR                     "00:00:00:EE:51:81"
#endif

#define PCI_HOST_ADAPTER 0              /* configure ar pci adapter     */
#define PCI_HOST_FORCE   1              /* configure as pci host        */
#define PCI_HOST_AUTO    2              /* detected via arbiter enable  */

#define CONFIG_UBOOT_SIZE                       0x100000
#define CONFIG_SPARE_AREA			0x400000

/* NOR-FLASH stuff	*/
/************************/
#define CONFIG_SYS_MAX_FLASH_BANKS 1
#define CONFIG_ENV_SIZE_NOR			0x20000
#define CONFIG_ENV_SECT_SIZE_NOR	0x20000
#define CONFIG_ENV_OFFSET_NOR		0x100000	/* environment starts here  */
#define CONFIG_ENV_RANGE_NOR 		CONFIG_ENV_SIZE_NOR * 8
#define CONFIG_ENV_ADDR_NOR			(NOR_CS_BASE + CONFIG_ENV_OFFSET_NOR)

#if defined(MV_INCLUDE_NOR)

	#define CONFIG_NOR_FLASH_AUTODETECT
	#define CONFIG_NOR_FLASH
	#define CONFIG_SYS_FLASH_CFI
	#define CONFIG_SYS_FLASH_PROTECTION
	#define CONFIG_FLASH_CFI_DRIVER
	#define CONFIG_SYS_MAX_FLASH_SECT	128
	#define CONFIG_SYS_FLASH_BASE		NOR_CS_BASE

	#define CONFIG_SYS_FLASH_CFI_WIDTH	FLASH_CFI_8BIT

	#define CONFIG_FLASH_SHOW_PROGRESS 1
	#define CONFIG_SYS_FLASH_EMPTY_INFO
	#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE

	#define CONFIG_CMD_FLASH
	#undef CONFIG_CMD_IMLS

	/* Boot from NOR settings */
	#if defined(MV_NOR_BOOT)
		#define CONFIG_ENV_IS_IN_FLASH

		#define CONFIG_ENV_SIZE			CONFIG_ENV_SIZE_NOR
		#define CONFIG_ENV_SECT_SIZE		CONFIG_ENV_SECT_SIZE_NOR
		#define CONFIG_ENV_OFFSET		CONFIG_ENV_OFFSET_NOR   /* environment starts here  */
		#define CONFIG_ENV_RANGE 		CONFIG_ENV_RANGE_NOR
		#define CONFIG_ENV_ADDR			CONFIG_ENV_ADDR_NOR
		#define MONITOR_HEADER_LEN		0x200
		#define CONFIG_SYS_MONITOR_BASE		0
		#define CONFIG_SYS_MONITOR_LEN		0xC0000		/* Reserve 768 kB for Monitor */

	#endif /* MV_NOR_BOOT */
#else
	#define CONFIG_SYS_NO_FLASH
	#define CONFIG_SYS_NO_FLASH_NO_HANG	/* disable hung when NOR flash disconnected */
	#undef CONFIG_CMD_FLASH
	#undef CONFIG_CMD_IMLS
#endif /* MV_INCLUDE_NOR */

/*
 * Other
 */
#define MV_DFL_REGS             0xf1000000      /* boot time MV_REGS */
#define MV_REGS                 INTER_REGS_BASE /* MV Registers will be mapped here */
#define BOARD_LATE_INIT
#define CONFIG_BOARD_LATE_INIT
#undef  CONFIG_USE_IRQ
#define CONFIG_BZIP2

#define CONFIG_STACKSIZE        (1 << 20)       /* regular stack - up to 4M (in case of exception)*/

/*
 * ERRATA
 */
#define ERRATA_FE_3124064

#define ENV_SPI_MAIN_CHANNEL	1
#define ENV_SPI_MAIN_INDEX		0


#endif /* __CONFIG_H */
