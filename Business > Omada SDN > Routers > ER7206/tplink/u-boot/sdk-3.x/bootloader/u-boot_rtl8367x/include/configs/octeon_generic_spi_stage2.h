/*
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * Copyright (C) 2004 - 2014 Cavium, Inc. <support@cavium.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

/*
 * This file contains the configuration parameters for
 * Octeon EBB6300 board.
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#define CONFIG_OCTEON_SPI_BOOT
/*
 * Define CONFIG_OCTEON_PCI_HOST = 1 to map the pci devices on the
 * bus.  Define CONFIG_OCTEON_PCI_HOST = 0 for target mode when the
 * host system performs the pci bus mapping instead.  Note that pci
 * commands are enabled to allow access to configuration space for
 * both modes.
 */
#ifndef CONFIG_OCTEON_PCI_HOST
# define CONFIG_OCTEON_PCI_HOST     0
#endif

#define CONFIG_OCTEON_NO_FAILSAFE
#define CONFIG_OCTEON_DISABLE_UBI
#define CONFIG_OCTEON_DISABLE_JFFS2
#define CONFIG_ENV_IS_NOWHERE
#define CONFIG_OCTEON_DISABLE_NETWORKING
#define CONFIG_OCTEON_DISABLE_QLM

#include "octeon_common_spi_stage2.h"

/* CONFIG_OCTEON_GENERIC_NAND set by Makefile in include/config.h */
#define SPI_STAGE2_BOARD_TYPE           CVMX_BOARD_TYPE_GENERIC

/**
 * Add command to boot stage 3 bootloader out of NAND
 */
#define CONFIG_CMD_OCTEON_SPI_BOOT_STAGE3


/**
 * Start of where the SPI bootloader images are placed.  Must be on an erase
 * block boundary/
 */
#define CONFIG_OCTEON_SPI_BOOT_START        0x1000

/**
 * End of the NAND boot partition which is searched for a bootloader.  Must be
 * on an erase block boundary.  It should be large enough to be able to handle
 * at least one bad block.
 */
#define CONFIG_OCTEON_SPI_BOOT_END      0x600000

/**
 * Address to load the stage 3 bootloader for booting
 */
#define CONFIG_OCTEON_STAGE3_LOAD_ADDR  0x81000000

/**
 * If more than one NAND chip is present, define which one contains the
 * bootloader.
 */
#define DEFAULT_DDR3_CLOCK_FREQ_MHZ     667

#define DEFAULT_CPU_REF_FREQUENCY_MHZ       50
#define DEFAULT_DDR_REF_FREQUENCY_MHZ       50

/** Address of board EEPROM on TWSI bus */
#define CONFIG_SYS_I2C_EEPROM_ADDR  (gd->arch.tlv_addr)

/** Default EEPROM address */
#define CONFIG_SYS_DEF_EEPROM_ADDR  CONFIG_SYS_I2C_EEPROM_ADDR
/* These speed up writes to the serial EEPROM by enabling page writes.
 * Please see the datasheet for details.
 */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS   5   /* 32 bytes */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS   5

/* Set bootdelay to 0 for immediate boot */
#define CONFIG_BOOTDELAY    1   /* autoboot after X seconds */
#define CONFIG_BOOTCOMMAND  "bootstage3"

#undef  CONFIG_BOOTARGS

/*
 * The EBB6300 does not use the internal arbiter in Octeon.
 * Enable this for boards that do.
 */
/* #define USE_OCTEON_INTERNAL_ARBITER */

#include "octeon_cmd_conf.h"

#define CONFIG_SYS_LONGHELP

#undef CONFIG_BZIP2
#undef CONFIG_ZIP
#undef CONFIG_GZIP
#undef CONFIG_LZMA
#undef CONFIG_CMD_UNZIP
#undef CONFIG_REGEX
#undef CONFIG_FIT
#undef CONFIG_CMD_MEMINFO
#undef CONFIG_CMD_ASKENV
#undef CONFIG_CMD_EDITENV
#undef CONFIG_CMD_BDI
#undef CONFIG_CMD_XIMG
#undef CONFIG_CMD_GPIO
#undef CONFIG_CMD_CRAMFS
#undef CONFIG_CMD_OCTEON_REGINFO
#undef CONFIG_CMD_I2C
#undef CONFIG_CMD_GREPENV
#undef CONFIG_CMD_OCTEON_LINUX
#undef CONFIG_CMD_OCTEON_ELF
#undef CONFIG_CMD_OCTEON
#undef CONFIG_CMD_OCTEON_MEM
#undef CONFIG_CMD_TIME
#undef CONFIG_CMD_STRINGS
#undef CONFIG_CMD_SOURCE
#undef CONFIG_CMD_NMI
#undef CONFIG_CMD_ITEST
#undef CONFIG_CMD_CONSOLE
#undef CONFIG_CMD_SAVEENV
#undef CONFIG_CMD_SETEXPR
#undef CONFIG_CMD_ENV
#undef CONFIG_CMD_FDT
#undef CONFIG_CMD_I2C
#undef CONFIG_CMD_BOOTM
#undef CONFIG_CMD_MEMORY

#undef CONFIG_ENV_IS_IN_FLASH
#undef CONFIG_CMD_OCTNAND

/* "tlv_eeprom" command */
#define CONFIG_CMD_OCTEON_TLVEEPROM

#undef CONFIG_HW_WATCHDOG

#define CONFIG_OCTEON_DISABLE_DDR2

#undef CONFIG_SYS_CBSIZE
#define CONFIG_SYS_CBSIZE       256

#undef CONFIG_OCTEON_QLM

/*
 * Miscellaneous configurable options
 */

/* Environment variables that will be set by default */
#define CONFIG_EXTRA_ENV_SETTINGS                   \
        "autoload=n\0"                          \
        "bootcmd=bootstage3\0"                      \
        "bootdelay=1\0"                         \
        "\0"
#define CONFIG_ENV_SIZE         4096

/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CONFIG_SYS_DCACHE_SIZE      (32 * 1024)
#define CONFIG_SYS_ICACHE_SIZE      (78 * 1024)


/* Include shared board configuration, consisting mainly of DRAM details. */
#include "octeon_generic_spi_stage2_shared.h"
#include "octeon_evb7000_shared.h"


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
