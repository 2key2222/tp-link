/*
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * Copyright (C) 2004 - 2013 Cavium, Inc. <support@cavium.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
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

/*
 * This file contains the configuration parameters for
 * Octeon EVB7000-SFF board.
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__
#define OCTEON_EVB7000_SFF
/*
 * Define CONFIG_OCTEON_PCI_HOST = 1 to map the pci devices on the
 * bus.  Define CONFIG_OCTEON_PCI_HOST = 0 for target mode when the
 * host system performs the pci bus mapping instead.  Note that pci
 * commands are enabled to allow access to configuration space for
 * both modes.
 */
//#ifndef CONFIG_OCTEON_PCI_HOST
//# define CONFIG_OCTEON_PCI_HOST       1
//#endif

#define CONFIG_SPI_FLASH_BAR    /* Enable higher 16MiB accessible. */

#undef CONFIG_OCTEON_USB_OCTEON3   /** Enable USB support on OCTEON III */

#include "octeon_common.h"

/* CONFIG_OCTEON_EVB7000_SFF set by Makefile in include/config.h */

/* Default DDR clock if tuple doesn't exist in EEPROM */
#define EVB7000_SFF_DEF_DRAM_FREQ   533

#define CONFIG_LBA48            /* 48-bit mode */
#define CONFIG_SYS_64BIT_LBA        /* 64-bit LBA support */
#define CONFIG_SYS_ATA_BASE_ADDR    0 /* Make compile happy */
/* Base address of Common memory for Compact flash */

#if 0
/* eMMC support */
#define CONFIG_OCTEON_MMC       /* Enable MMC support */
#define CONFIG_MMC_MBLOCK       /* Multi-block support */
#define CONFIG_CMD_MMC          /* Enable mmc command */
#define CONFIG_SYS_MMC_SET_DEV      /* Enable multiple MMC devices */
#define CONFIG_MMC
#define CONFIG_OCTEON_MIN_BUS_SPEED_HZ  100000
#endif

/** Address of board EEPROM on TWSI bus */
#define CONFIG_SYS_I2C_EEPROM_ADDR  OCTEON_EVB7000_SFF_BOARD_EEPROM_TWSI_ADDR

/** Default EEPROM address */
#define CONFIG_SYS_DEF_EEPROM_ADDR  CONFIG_SYS_I2C_EEPROM_ADDR

/* These speed up writes to the serial EEPROM by enabling page writes.
 * Please see the datasheet for details.
 */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS   5   /* 32 bytes */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS   5

/* Set bootdelay to 0 for immediate boot */
#define CONFIG_BOOTDELAY    2   /* autoboot after X seconds */

#undef  CONFIG_BOOTARGS

/** Enable octbootbus command */
#define CONFIG_CMD_OCTEON_BOOTBUS

/* The 'mtdids' environment variable is used in conjunction with the 'mtdparts'
 * variable to define the MTD partitions for u-boot.
 */
#define MTDPARTS_DEFAULT                \
    "octeon_nor0:2560k(bootloader)ro,"          \
    "2m(kernel),"                   \
    "3520k(cramfs),"                \
    "64k(environment)ro\0"

#define MTDIDS_DEFAULT  "nor0=octeon_nor0\0"


/* Define this to enable built-in octeon ethernet support */
#define CONFIG_OCTEON_SGMII_ENET
#define CONFIG_OCTEON_QSGMII_ENET
//#define CONFIG_OCTEON_XAUI_ENET
//#define CONFIG_OCTEON_MGMT_ENET

/* Enable Octeon built-in networking if RGMII support is enabled */
#if defined(CONFIG_OCTEON_RGMII_ENET) || defined(CONFIG_OCTEON_SGMII_ENET) || \
    defined(CONFIG_OCTEON_XAUI_ENET) || defined(CONFIG_OCTEON_QSGMII_ENET)
# define CONFIG_OCTEON_INTERNAL_ENET
#endif

/* PCI console is supported since oct-remote-boot is supported.
 * Enable MUX and oct-remote-bootcmd support as well
 */
#define CONFIG_SYS_PCI_CONSOLE
#define CONFIG_CONSOLE_MUX
#define CONFIG_OCTEON_BOOTCMD

#include "octeon_cmd_conf.h"

#ifdef  CONFIG_CMD_NET
/**
 * Define available PHYs
 */
# define CONFIG_PHY_GIGE
# define CONFIG_PHY_REALTEK
//# define CONFIG_PHY_MARVELL
//# define CONFIG_PHY_VITESSE
//# define CONFIG_PHYLIB_10G
# include "octeon_network.h"
#endif


/* "tlv_eeprom" command */
#define CONFIG_CMD_OCTEON_TLVEEPROM
/* "qlm" command */
#define CONFIG_CMD_QLM

/* Enable MTD partitioning support */
#define CONFIG_CMD_MTDPARTS

/* Enable JFFS2 support */
//#define CONFIG_CMD_JFFS2

/* Enable "date" command to set and get date from RTC */
#undef CONFIG_CMD_DATE
#define CONFIG_CMD_FLASH        /** flinfo, erase, protect  */
#undef CONFIG_CMD_EXT2         /** EXT2/3 filesystem support   */
#undef CONFIG_CMD_EXT4         /** EXT4 filesystem support */
#undef CONFIG_CMD_FAT          /** FAT support         */
#undef CONFIG_FAT_WRITE        /** FAT write support       */

/* SPI NOR flash support */
#define CONFIG_SF_DEFAULT_BUS       0
#define CONFIG_SF_DEFAULT_CS        0
#define CONFIG_SF_DEFAULT_SPEED     16000000

#define CONFIG_SPI_CONFIG_BAR          //add by zhufeng

#define CONFIG_OCTEON_SPI       /* Enable OCTEON SPI driver */
#define CONFIG_SPI_FLASH        /* Enable SPI flash driver  */
#define CONFIG_SPI_FLASH_STMICRO  /* Enable ST Micro SPI flash    */
#define CONFIG_SPI_FLASH_SPANSION       /*Enable SPANSION SPI flash    */
#define CONFIG_SPI_FLASH_WINBOND
#define CONFIG_SPI_FLASH_GIGADEVICE
#define CONFIG_CMD_SPI          /* Enable SPI command       */
#define CONFIG_CMD_SF           /* Enable SPI flash command */
#define CONFIG_CMD_NAND	/*enable nand command   */
/*
 * Miscellaneous configurable options
 */

/* Environment variables that will be set by default */

/** 
 *          model      cpu              ddr3    flash   flash2   
 * ------------------------------------------------------------ 
 * ER5110G CN7010 [1 cores @ 800MHz]    256MB   32MB    NC  
 * ER5510G CN7020 [2 cores @   1GHz]    256MB   32MB    32MB 
 * ER6110G CN7010 [1 cores @ 800MHz]    512MB   32MB    NC 
 * ER6510G CN7020 [2 cores @   1GHz]      1GB   32MB    32MB 
 *  
 */

#ifdef CONFIG_TP_MODEL_ER5110G
#define CONFIG_EXTRA_ENV_SETTINGS       \
        "autoload=n\0"                  \
        "bootli=bootoctlinux $loadaddr coremask=0xffff numcores=1 rootfstype=squashfs,jffs2 noinitrd console=ttyS0,115200 board=TL-ER7520G mtdparts=spi32766.0:2M(bootloader),8M(kernel),15M(rootfs),768K(default_config),128K(tddp),128K(log),5M(rootfs_data),32M@0x000000(firmware)\0" \
        "bootcmd=run diphy;sf probe;sf read $(loadaddr) 0x200000 0x800000;run bootli\0" \
        "diphy=mii device mdio-octeon0;mii wirte 0 0 0x1940;mii wirte 1 0 0x1940;mii wirte 2 0 0x1940;mii wirte 3 0 0x1940;mii wirte 4 0 0x1940;\0" \
        "enphy=mii device mdio-octeon0;mii wirte 0 0 0x1140;mii wirte 1 0 0x1140;mii wirte 2 0 0x1140;mii wirte 3 0 0x1140;mii wirte 4 0 0x1140;\0" \
        "bootdelay=1\0" \
        "resetenv=sf probe;sf erase 0x1f0000 0x10000\0" \
        "loadaddr=0x8a00000\0" \

#endif

#ifdef CONFIG_TP_MODEL_ER5510G
#define CONFIG_EXTRA_ENV_SETTINGS       \
        "autoload=n\0"                  \
        "bootli=bootoctlinux $loadaddr coremask=0xffff numcores=2 rootfstype=squashfs,jffs2 noinitrd console=ttyS0,115200 board=TL-ER7520G mtdparts=spi32766.0:2M(bootloader),8M(kernel),15M(rootfs),768K(default_config),128K(tddp),128K(log),5M(rootfs_data),32M@0x000000(firmware)\\\\;spi32766.1:-(backup)\0" \
        "bootcmd=run diphy;sf probe;sf read $(loadaddr) 0x200000 0x800000;run bootli\0" \
        "diphy=mii device mdio-octeon0;mii wirte 0 0 0x1940;mii wirte 1 0 0x1940;mii wirte 2 0 0x1940;mii wirte 3 0 0x1940;mii wirte 4 0 0x1940;\0" \
        "enphy=mii device mdio-octeon0;mii wirte 0 0 0x1140;mii wirte 1 0 0x1140;mii wirte 2 0 0x1140;mii wirte 3 0 0x1140;mii wirte 4 0 0x1140;\0" \
        "bootdelay=1\0" \
        "resetenv=sf probe;sf erase 0x1f0000 0x10000\0" \
        "loadaddr=0x8a00000\0" \

#endif

#ifdef CONFIG_TP_MODEL_AC500
#define CONFIG_EXTRA_ENV_SETTINGS       \
        "autoload=n\0"                  \
        "bootli=bootoctlinux $loadaddr coremask=0xffff numcores=2 rootfstype=squashfs,jffs2 noinitrd console=ttyS0,115200 board=AC500 mtdparts=spi32766.0:2M(bootloader),8M(kernel),10M(rootfs),5M(resource),128K(device-info),64K(support-list),576K(firmware-info),128K(tddp),128K(log),5M(rootfs_data),32M@0x000000(firmware)\\\\;spi32766.1:-(backup)\0" \
        "bootcmd=run diphy;sf probe;sf read $(loadaddr) 0x200000 0x800000;run bootli\0" \
        "diphy=mii device mdio-octeon0;mii wirte 0 0 0x1940;mii wirte 1 0 0x1940;mii wirte 2 0 0x1940;mii wirte 3 0 0x1940;mii wirte 4 0 0x1940;\0" \
        "enphy=mii device mdio-octeon0;mii wirte 0 0 0x1140;mii wirte 1 0 0x1140;mii wirte 2 0 0x1140;mii wirte 3 0 0x1140;mii wirte 4 0 0x1140;\0" \
        "bootdelay=1\0" \
        "resetenv=sf probe;sf erase 0x1f0000 0x10000\0" \
        "loadaddr=0x8a00000\0" \

#endif

#ifdef CONFIG_TP_MODEL_ER6120
#ifdef CONFIG_TP_MODEL_ER6120v3
#define CONFIG_EXTRA_ENV_SETTINGS       \
        "autoload=n\0"                  \
        "bootli=bootoctlinux $loadaddr coremask=0xffff numcores=2 rootfstype=squashfs,jffs2 noinitrd console=ttyS0,115200 board=TL-ER6120 mtdparts=spi32766.0:2M(bootloader),8M(kernel),15M(rootfs),128K(device-info),64K(support-list),576K(firmware-info),128K(tddp),128K(log),5M(rootfs_data),32M@0x000000(firmware)\0" \
        "bootcmd=run diphy;sf probe;sf read 0x21000000 0x200000 0x200000;unlzma 0x21000000 $(loadaddr);run bootli\0" \
        "diphy=mii device mdio-octeon0;mii wirte 0 0 0x1940;mii wirte 1 0 0x1940;mii wirte 2 0 0x1940;mii wirte 3 0 0x1940;mii wirte 4 0 0x1940;\0" \
        "enphy=mii device mdio-octeon0;mii wirte 0 0 0x1140;mii wirte 1 0 0x1140;mii wirte 2 0 0x1140;mii wirte 3 0 0x1140;mii wirte 4 0 0x1140;\0" \
        "bootdelay=1\0" \
        "resetenv=sf probe;sf erase 0x1f0000 0x10000\0" \
        "loadaddr=0x8a00000\0" \
        "ipaddr=192.168.0.10\0"\
        "serverip=192.168.0.146\0"\

#else
#define CONFIG_EXTRA_ENV_SETTINGS       \
        "autoload=n\0"                  \
        "bootli=bootoctlinux $loadaddr coremask=0xffff numcores=1 rootfstype=squashfs,jffs2 noinitrd console=ttyS0,115200 board=TL-ER6120 mtdparts=octeon_nand0:2M(bootloader),2M(bootloader-fs),6M(kernel),15M(rootfs),128K(device-info),64K(support-list),576K(firmware-info),128K(tddp),128K(log),5M(rootfs_data),32M@0x000000(firmware)\0" \
        "bootcmd=run diphy;nand read 0x21000000 0x400000 0x200000;unlzma 0x21000000 $(loadaddr);run bootli\0" \
        "diphy=mii device mdio-octeon0;mii wirte 0 0 0x1940;mii wirte 1 0 0x1940;mii wirte 2 0 0x1940;mii wirte 3 0 0x1940;mii wirte 4 0 0x1940;\0" \
        "enphy=mii device mdio-octeon0;mii wirte 0 0 0x1140;mii wirte 1 0 0x1140;mii wirte 2 0 0x1140;mii wirte 3 0 0x1140;mii wirte 4 0 0x1140;\0" \
        "bootdelay=1\0" \
        "resetenv=sf probe;sf erase 0x1f0000 0x10000\0" \
        "loadaddr=0x8a00000\0" \
        "ipaddr=192.168.0.10\0"\
        "serverip=192.168.0.150\0"\

#endif
#endif

#ifdef CONFIG_TP_MODEL_OSG_PRO
#ifdef CONFIG_FS_UBOOT
#define CONFIG_EXTRA_ENV_SETTINGS       \
								"autoload=n\0"					\
								"bootli=bootoctlinux $loadaddr coremask=0xffff numcores=2 rootfstype=squashfs,jffs2 noinitrd console=ttyS0,115200 board=OSG-PRO mtdparts=octeon_nand0:2M(bootloader),8M(kernel),15M(rootfs),128K(partition-table),128K(device-info),128K(support-list),128K(firmware-info),128K(extra-para),5504K(rootfs_data),32M@0x000000(firmware);spi32766.0:2M(bootloader-factory),128K(tddp),128K(log)\0" \
								"bootcmd=run diphy;nand read 0x21000000 0x200000 0x200000;unlzma 0x21000000 $(loadaddr);run bootli\0" \
								"diphy=mii device mdio-octeon0;mii wirte 0 0 0x1940;mii wirte 1 0 0x1940;mii wirte 2 0 0x1940;mii wirte 3 0 0x1940;mii wirte 4 0 0x1940;\0" \
								"enphy=mii device mdio-octeon0;mii wirte 0 0 0x1140;mii wirte 1 0 0x1140;mii wirte 2 0 0x1140;mii wirte 3 0 0x1140;mii wirte 4 0 0x1140;\0" \
								"bootdelay=1\0" \
								"resetenv=sf probe;sf erase 0x1f0000 0x10000\0" \
								"loadaddr=0x8a00000\0" \
								"ipaddr=192.168.0.10\0"\
								"serverip=192.168.0.146\0"\
						
#endif /* CONFIG_OSG_PRO  */
#endif /* CONFIG_FS_UBOOT  */
				
#ifdef CONFIG_TP_MODEL_OSG_PRO
#ifdef CONFIG_FACTORY_UBOOT
#define CONFIG_EXTRA_ENV_SETTINGS       \
								"autoload=n\0"					\
								"bootli=bootoctlinux $loadaddr coremask=0xffff numcores=2 rootfstype=squashfs,jffs2 noinitrd console=ttyS0,115200 board=OSG-PRO mtdparts=spi32766.0:2M(bootloader),8M(kernel),15M(rootfs),128K(device-info),64K(support-list),576K(firmware-info),128K(tddp),128K(log),5M(rootfs_data),32M@0x000000(firmware)\0" \
								"bootcmd=octbootfs;cleancache\0" \
								"diphy=mii device mdio-octeon0;mii wirte 0 0 0x1940;mii wirte 1 0 0x1940;mii wirte 2 0 0x1940;mii wirte 3 0 0x1940;mii wirte 4 0 0x1940;\0" \
								"enphy=mii device mdio-octeon0;mii wirte 0 0 0x1140;mii wirte 1 0 0x1140;mii wirte 2 0 0x1140;mii wirte 3 0 0x1140;mii wirte 4 0 0x1140;\0" \
								"bootdelay=1\0" \
								"resetenv=sf probe;sf erase 0x1f0000 0x10000\0" \
								"loadaddr=0x8a00000\0" \
								"ipaddr=192.168.0.10\0"\
								"serverip=192.168.0.146\0"\
				
#endif	/* CONFIG_OSG_PRO  */
#endif /* CONFIG_FACTORY_UBOOT  */



#ifdef CONFIG_TP_MODEL_ER5120
#ifdef CONFIG_TP_MODEL_ER5120v4
#define CONFIG_EXTRA_ENV_SETTINGS       \
        "autoload=n\0"                  \
        "bootli=bootoctlinux $loadaddr coremask=0xffff numcores=2 rootfstype=squashfs,jffs2 noinitrd console=ttyS0,115200 board=TL-ER5120 mtdparts=spi32766.0:2M(bootloader),8M(kernel),15M(rootfs),128K(device-info),64K(support-list),576K(firmware-info),128K(tddp),128K(log),5M(rootfs_data),32M@0x000000(firmware)\0" \
		"bootcmd=loadfs;cleancache\0" \
		"diphy=mii device mdio-octeon0;mii wirte 0 0 0x1940;mii wirte 1 0 0x1940;mii wirte 2 0 0x1940;mii wirte 3 0 0x1940;mii wirte 4 0 0x1940;\0" \
        "enphy=mii device mdio-octeon0;mii wirte 0 0 0x1140;mii wirte 1 0 0x1140;mii wirte 2 0 0x1140;mii wirte 3 0 0x1140;mii wirte 4 0 0x1140;\0" \
        "bootdelay=1\0" \
        "resetenv=sf probe;sf erase 0x1f0000 0x10000\0" \
        "loadaddr=0x8a00000\0" \

#else
#define CONFIG_EXTRA_ENV_SETTINGS       \
        "autoload=n\0"                  \
        "bootli=bootoctlinux $loadaddr coremask=0xffff numcores=1 rootfstype=squashfs,jffs2 noinitrd console=ttyS0,115200 board=TL-ER5120 mtdparts=spi32766.0:2M(bootloader),8M(kernel),15M(rootfs),128K(device-info),64K(support-list),576K(firmware-info),128K(tddp),128K(log),5M(rootfs_data),32M@0x000000(firmware)\0" \
        "bootcmd=run diphy;sf probe;sf read 0x8200000 0x200000 0x200000;unlzma 0x8200000 $(loadaddr);run bootli\0" \
        "diphy=mii device mdio-octeon0;mii wirte 0 0 0x1940;mii wirte 1 0 0x1940;mii wirte 2 0 0x1940;mii wirte 3 0 0x1940;mii wirte 4 0 0x1940;\0" \
        "enphy=mii device mdio-octeon0;mii wirte 0 0 0x1140;mii wirte 1 0 0x1140;mii wirte 2 0 0x1140;mii wirte 3 0 0x1140;mii wirte 4 0 0x1140;\0" \
        "bootdelay=1\0" \
        "resetenv=sf probe;sf erase 0x1f0000 0x10000\0" \
        "loadaddr=0x8a00000\0" \

#endif
#endif

#ifdef CONFIG_TP_MODEL_ER6110G
#define CONFIG_EXTRA_ENV_SETTINGS       \
        "autoload=n\0"                  \
        "bootli=bootoctlinux $loadaddr coremask=0xffff numcores=1 rootfstype=squashfs,jffs2 noinitrd console=ttyS0,115200 board=TL-ER7520G mtdparts=spi32766.0:2M(bootloader),8M(kernel),15M(rootfs),768K(default_config),128K(tddp),128K(log),5M(rootfs_data),32M@0x000000(firmware)\0" \
        "bootcmd=run diphy;sf probe;sf read $(loadaddr) 0x200000 0x800000;run bootli\0" \
        "diphy=mii device mdio-octeon0;mii wirte 0 0 0x1940;mii wirte 1 0 0x1940;mii wirte 2 0 0x1940;mii wirte 3 0 0x1940;mii wirte 4 0 0x1940;\0" \
        "enphy=mii device mdio-octeon0;mii wirte 0 0 0x1140;mii wirte 1 0 0x1140;mii wirte 2 0 0x1140;mii wirte 3 0 0x1140;mii wirte 4 0 0x1140;\0" \
        "bootdelay=1\0" \
        "resetenv=sf probe;sf erase 0x1f0000 0x10000\0" \
        "loadaddr=0x8a00000\0" \

#endif

#ifdef CONFIG_TP_MODEL_ER6510G
#define CONFIG_EXTRA_ENV_SETTINGS       \
        "autoload=n\0"                  \
        "bootli=bootoctlinux $loadaddr coremask=0xffff numcores=2 rootfstype=squashfs,jffs2 noinitrd console=ttyS0,115200 board=TL-ER7520G mtdparts=spi32766.0:2M(bootloader),8M(kernel),15M(rootfs),768K(default_config),128K(tddp),128K(log),5M(rootfs_data),32M@0x000000(firmware)\\\\;spi32766.1:-(backup)\0" \
        "bootcmd=run diphy;sf probe;sf read $(loadaddr) 0x200000 0x800000;run bootli\0" \
        "diphy=mii device mdio-octeon0;mii wirte 0 0 0x1940;mii wirte 1 0 0x1940;mii wirte 2 0 0x1940;mii wirte 3 0 0x1940;mii wirte 4 0 0x1940;\0" \
        "enphy=mii device mdio-octeon0;mii wirte 0 0 0x1140;mii wirte 1 0 0x1140;mii wirte 2 0 0x1140;mii wirte 3 0 0x1140;mii wirte 4 0 0x1140;\0" \
        "bootdelay=1\0" \
        "resetenv=sf probe;sf erase 0x1f0000 0x10000\0" \
        "loadaddr=0x8a00000\0" \

#endif

#ifndef CONFIG_EXTRA_ENV_SETTINGS
#error missing TP_MODEL_XXX
/* Environment variables that will be set by default */
#define CONFIG_EXTRA_ENV_SETTINGS       \
        "autoload=n\0"                  \
        "bootli=bootoctlinux $loadaddr coremask=0xffff numcores=1 rootfstype=squashfs,jffs2 noinitrd console=ttyS0,115200 board=TL-ER7520G mtdparts=spi32766.0:2M(bootloader),8M(kernel),15M(rootfs),768K(default_config),128K(tddp),128K(log),5M(rootfs_data),32M@0x000000(firmware)\\\\;spi32766.1:-(backup)\0" \
        "bootcmd=run diphy;sf probe;sf read $(loadaddr) 0x200000 0x800000;run bootli\0" \
        "diphy=mii device mdio-octeon0;mii wirte 0 0 0x1940;mii wirte 1 0 0x1940;mii wirte 2 0 0x1940;mii wirte 3 0 0x1940;mii wirte 4 0 0x1940;\0" \
        "enphy=mii device mdio-octeon0;mii wirte 0 0 0x1140;mii wirte 1 0 0x1140;mii wirte 2 0 0x1140;mii wirte 3 0 0x1140;mii wirte 4 0 0x1140;\0" \
        "bootdelay=1\0" \
        "resetenv=sf probe;sf erase 0x1f0000 0x10000\0" \
        "loadaddr=0x8a00000\0" \
        ""
#endif
/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define CONFIG_SYS_FLASH_SIZE           (32*1024*1024)  /* Flash size (bytes) */
#define CONFIG_SYS_MAX_FLASH_BANKS  1   /* max number of memory banks */
#define CONFIG_SYS_MAX_FLASH_SECT   (512)   /* max number of sectors on one chip */

/* Width of CFI bus to start scanning */
#define CONFIG_SYS_FLASH_CFI_WIDTH  FLASH_CFI_8BIT
/* Enable extra elements in CFI driver for storing flash geometry */
#define CONFIG_SYS_FLASH_CFI        1
/* Enable CFI flash driver */
#define CONFIG_FLASH_CFI_DRIVER     1
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE

/* We're not RAM_RESIDENT so CONFIG_ENV_IS_IN_FLASH will be set. */
#if CONFIG_RAM_RESIDENT
# define    CONFIG_ENV_IS_NOWHERE   1
#else
//# define  CONFIG_ENV_IS_IN_FLASH  1

# define    CONFIG_ENV_IS_IN_SPI_FLASH  1
#undef CONFIG_ENV_IS_IN_FLASH
#endif

#define CONFIG_BOOTLOADER_SIZE   (2*1024*1024)     /* layout=stage1+stage2+stage3+ENV */

/* Address and size of Primary Environment Sector   */
#define CONFIG_ENV_SIZE     (64*1024)
#define CONFIG_ENV_ADDR     (CONFIG_SYS_FLASH_BASE + CONFIG_BOOTLOADER_SIZE - CONFIG_ENV_SIZE)
//#define CONFIG_ENV_SECT_SIZE  (64*1024)
//#define CONFIG_ENV_OFFSET (CONFIG_ENV_ADDR - CONFIG_SYS_FLASH_BASE)

/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CONFIG_SYS_DCACHE_SIZE      (32 * 1024)
#define CONFIG_SYS_ICACHE_SIZE      (37 * 1024)

#if CONFIG_OCTEON_PCI_HOST
/* Right now only the Intel E1000 driver has been ported */
# define CONFIG_E1000
# define CONFIG_LIBATA
#if 0
# define CONFIG_CMD_SATA            /* Enable the sata command */
# define CONFIG_SYS_SATA_MAX_DEVICE 8   /* Support up to 8 devices */
# define CONFIG_SATA_AHCI
/*# define CONFIG_SATA_AHCI_PLAT*/
/*# define CONFIG_SATA_AHCI_OCTEON*/
# define CONFIG_SATA_PMP
# define CONFIG_AHCI_SETFEATURES_XFER
# define CONFIG_SYS_SATA_MAX_LUN    16
#endif
#endif

/* The CN70XX has two TWSI buses and the EVB7000 sff board uses both
 * of them
 */
#define CONFIG_SYS_MAX_I2C_BUS      1

#define CONFIG_RTC_DS1337
#define CONFIG_SYS_I2C_RTC_ADDR     0x68
#define CONFIG_SYS_RTC_BUS_NUM      0

/* Enable watchdog support */
#define CONFIG_HW_WATCHDOG

/* Configure QLM */
#define CONFIG_OCTEON_QLM

#if 0
/* DTT sensor */
/* TWSI address of temperature sensor */
#define CONFIG_SYS_I2C_DTT_ADDR     0x2c
#define CONFIG_SYS_DTT_BUS_NUM      0
#define CONFIG_SYS_SPD_BUS_NUM      0

/* TI TMP42X temperature sensor driver support */
#define CONFIG_DTT_ADM1021
/* Default settings for the ADM1031 driver */
#define CONFIG_SYS_DTT_ADM1021              \
    { { .i2c_addr = CONFIG_SYS_I2C_DTT_ADDR,    \
        .conv_rate = 8,             \
        .enable_alert = 1,          \
        .enable_local = 1,          \
        .max_local = 75,            \
        .min_local = 0,             \
        .enable_remote = 1,         \
        .max_remote = 85,           \
        .min_remote = 0,            \
    } }

/* Sensors used */
#define CONFIG_DTT_SENSORS  { 0, 1 }
/* Enable "dtt" command */
#define CONFIG_CMD_DTT
#endif

#define CONFIG_CMD_MEMTEST

#define CONFIG_CMD_DRAMTEST
#define CONFIG_MALLOC_BASE  (((uint32_t)(&uboot_end) + 0xFFFF) & ~0xFFFF)
#define CONFIG_SDRAM_LOWER_RANGE_BASE   0x0C000000
#define CONFIG_SDRAM_UPPER_RANGE_BASE   0x0C100000
#define CONFIG_SDRAM_TOTAL_SIZE         0x02000000        /* 32MiB */
#define CONFIG_SDRAM_DATABUS_WIDTH      32

/* Include shared board configuration, consisting mainly of DRAM details. */
#include "octeon_evb7000_sff_shared.h"

/** Disable DDR2 support */
#define CONFIG_OCTEON_DISABLE_DDR2

#ifdef CONFIG_SWITCH_RTL8367X

/* Force use RTL8367C for RTL8367S-CG */
#define FORCE_PROBE_RTL8367C

/* We user SMI(MDC/MDIO) to managle RTL8367S */
#define MDC_MDIO_OPERATION
#endif #ifdef CONFIG_SWITCH_RTL8367X

/*
 * Web Failsafe configuration
 */
//#define WEBFAILSAFE_UPLOAD_RAM_ADDRESS			CFG_LOAD_ADDR
#define WEBFAILSAFE_UPLOAD_RAM_ADDRESS			0x83000000

// U-Boot partition size and offset
#define WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS		CFG_FLASH_BASE

#define WEBFAILSAFE_UPLOAD_UBOOT_SIZE_IN_BYTES		( 128 * 1024 )
#define UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES		"0x20000"

// Firmware partition offset
#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS		CFG_KERN_ADDR

// ART partition size and offset
#define WEBFAILSAFE_UPLOAD_ART_ADDRESS			CFG_FACTORY_ADDR

#define WEBFAILSAFE_UPLOAD_ART_SIZE_IN_BYTES		( 64 * 1024 )

// max. firmware size <= (FLASH_SIZE -  WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES)
#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	( 320 * 1024 )

// progress state info
#define WEBFAILSAFE_PROGRESS_START			0
#define WEBFAILSAFE_PROGRESS_TIMEOUT			1
#define WEBFAILSAFE_PROGRESS_UPLOAD_READY		2
#define WEBFAILSAFE_PROGRESS_UPGRADE_READY		3
#define WEBFAILSAFE_PROGRESS_UPGRADE_FAILED		4

// update type
#define WEBFAILSAFE_UPGRADE_TYPE_FIRMWARE		0
#define WEBFAILSAFE_UPGRADE_TYPE_UBOOT			1
#define WEBFAILSAFE_UPGRADE_TYPE_ART			2
#endif  /* __CONFIG_H__ */
