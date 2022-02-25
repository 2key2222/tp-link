/***********************license start************************************
 * Copyright (c) 2004-2013 Cavium Inc. (support@cavium.com). All rights
 * reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *
 *     * Neither the name of Cavium Inc. nor the names of
 *       its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS
 * OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
 * RESPECT TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
 * REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
 * DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
 * OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
 * PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET
 * POSSESSION OR CORRESPONDENCE TO DESCRIPTION.  THE ENTIRE RISK ARISING OUT
 * OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
 *
 *
 * For any questions regarding licensing please contact
 * support@cavium.com
 ***********************license end**************************************/
#ifndef __ASM_GBL_DATA_H
#define __ASM_GBL_DATA_H

#ifndef __U_BOOT__
# define k0 $26
# include "asm/u-boot.h"
#endif

#ifdef __U_BOOT__
# include <asm/arch/octeon_eeprom_types.h>
#else
# include <asm/arch-octeon/octeon_eeprom_types.h>
# define u32 uint32_t
# define u64 uint64_t
#endif

#define SERIAL_LEN              20
#define GD_TMP_STR_SIZE         30

/**
 * These values are used in the bd->bi_bootflags parameter
 */
#define OCTEON_BD_FLAG_BOOT_RAM		1
#define OCTEON_BD_FLAG_BOOT_CACHE	2
#define OCTEON_BD_FLAG_BOOT_FLASH	4

/** This holds I2C information required in the OCTEON gd_t arch data */
struct octeon_i2c_bus {
	uint64_t	regs;		/** Address of I2C registers */
	int		node;		/** Device tree node */
	int16_t		bus_num;	/** I2C bus number */
	int16_t		id;		/** I2C bus id */
};

struct arch_global_data {
       /* EEPROM data structures as read from EEPROM or populated by other
        * means on boards without an EEPROM.
        */
        octeon_eeprom_board_desc_t board_desc;
        octeon_eeprom_clock_desc_t clock_desc;
        octeon_eeprom_mac_addr_t   mac_desc;

        uint32_t	console_uart;	/* Console UART number */
        uint32_t	ddr_ref_hertz;  /* DDR reference clock in hz */
        uint64_t	dfm_ram_size;   /* DFM ram size */
        char		*err_msg;       /* Save error msg until console up */
        /* Temporary string used in ddr init code before DRAM is up */
	ulong		uboot_flash_address;    /* Address of normal
                                                 * bootloader in flash
                                                 */
	ulong		uboot_flash_size;   /* Size of normal bootloader */
        char		tmp_str[GD_TMP_STR_SIZE];
	uint32_t	flash_base_address;	/* Base address of flash */
	uint32_t	flash_size;		/* Size of flash */
	/* These really belong in gd->bd though unfortunately it isn't
	 * initialized until later.
	 */
	uint8_t		tlv_addr;		/* TWSI address of TLV EEPROM */
	uint8_t		node_mask;		/* Mask of available nodes */
	uint8_t		mcu_rev_maj;
	uint8_t		mcu_rev_min;
# ifdef CONFIG_OCTEON_ENABLE_PAL
	uint32_t	pal_addr;		/* Address of PAL on boot bus */
# endif
# ifdef CONFIG_OCTEON_ENABLE_LED_DISPLAY
	uint32_t	led_addr;		/* LED display address */
# endif
#ifdef CONFIG_OF_CONTROL
	/** I2C device-tree busses */
	struct octeon_i2c_bus	i2c_busses[CONFIG_MAX_I2C_NUM];
#endif
	uint8_t		current_i2c_mux_bus;	/** Current I2C mux setting */
	int8_t		num_i2c_busses;		/** Number of I2C busses */
	uint8_t		i2c_initialized;	/** Bitmask of I2C buses initialized */
};

/*
 * This is used for compatibility and is passed to the Linux kernel and Octeon
 * simple executive applications since the definition of gd_t has changed with
 * more recent versions of U-Boot.
 */
typedef struct octeon_boot_gd_s {
	bd_t                *bd;
	unsigned long       flags;
	unsigned long       baudrate;
	unsigned long       have_console;   /* serial_init() was called */
	uint64_t            ram_size;       /* RAM size */
	uint64_t            reloc_off;      /* Relocation Offset */
	unsigned long       env_addr;       /* Address  of Environment struct */
	unsigned long       env_valid;      /* Checksum of Environment valid? */
	unsigned long       cpu_clock_mhz;  /* CPU clock speed in Mhz */
	unsigned long       ddr_clock_mhz;  /* DDR clock (not data rate!) in Mhz */
	unsigned long       ddr_ref_hertz;   /* DDR Ref clock Hertz */
	int                 mcu_rev_maj;
	int                 mcu_rev_min;
	int                 console_uart;

	/* EEPROM data structures as read from EEPROM or populated by other
	 * means on boards without an EEPROM
	 */
	octeon_eeprom_board_desc_t board_desc;
	octeon_eeprom_clock_desc_t clock_desc;
	octeon_eeprom_mac_addr_t   mac_desc;

	void                **jt;               /* jump table */
	char                *err_msg;           /* pointer to error message to
                                                 * save until console is up
                                                 */
	char                tmp_str[GD_TMP_STR_SIZE];  /* Temporary string used
                                                        * in ddr init code
                                                        * before DRAM is up
                                                        */
	unsigned long       uboot_flash_address;    /* Address of normal
                                                     * bootloader in flash
                                                     */
	unsigned long       uboot_flash_size;   /* Size of normal bootloader */
	uint64_t            dfm_ram_size;       /* DFM RAM size */
} octeon_boot_gd_t;

#ifdef CONFIG_OCTEON
# define GD_FLG_FAILSAFE_MODE    	0x01000 /* Failsafe mode */
/* Note that the DDR clock initialized flags must be contiguous */
# define GD_FLG_DDR0_CLK_INITIALIZED	0x02000 /* Clock for DDR 0 initialized */
# define GD_FLG_DDR1_CLK_INITIALIZED	0x04000 /* Clock for DDR 1 initialized */
# define GD_FLG_DDR2_CLK_INITIALIZED	0x08000 /* Clock for DDR 2 initialized */
# define GD_FLG_DDR3_CLK_INITIALIZED	0x10000 /* Clock for DDR 3 initialized */
# define GD_FLG_RAM_RESIDENT		0x20000 /* Loaded into RAM externally */
# define GD_FLG_DDR_VERBOSE		0x40000 /* Verbose DDR information */
# define GD_FLG_DDR_DEBUG		0x80000 /* Check env. for DDR variables */
# define GD_FLG_DDR_TRACE_INIT		0x100000
# define GD_FLG_MEMORY_PRESERVED		0x200000
# define GD_FLG_DFM_VERBOSE		0x400000
# define GD_FLG_DFM_TRACE_INIT		0x800000
# define GD_FLG_DFM_CLK_INITIALIZED	0x1000000 /* DFM memory clock initialized */
# define GD_FLG_CLOCK_DESC_MISSING	0x2000000 /* EEPROM clock descr. missing */
# define GD_FLG_BOARD_DESC_MISSING	0x4000000 /* EEPROM board descr. missing */
# define GD_FLG_DDR_PROMPT		0x8000000
#endif /* CONFIG_OCTEON */

#include <asm-generic/global_data.h>

#define DECLARE_GLOBAL_DATA_PTR     register volatile gd_t *gd asm ("k0")

#endif /* __ASM_GBL_DATA_H */
