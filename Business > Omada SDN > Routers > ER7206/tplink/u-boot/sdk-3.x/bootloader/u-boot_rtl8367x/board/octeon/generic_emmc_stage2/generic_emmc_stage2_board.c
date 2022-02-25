/*
 * (C) Copyright 2004-2012 Cavium, Inc. <support@cavium.com>
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

#include <common.h>
#include <asm/arch/octeon_boot.h>
#include <asm/arch/octeon_board_common.h>
#include <asm/arch/lib_octeon_shared.h>
#include <asm/arch/lib_octeon.h>
#include <asm/arch/cvmx.h>
#include <asm/arch/cvmx-mio-defs.h>
#include <asm/arch/lib_octeon.h>

DECLARE_GLOBAL_DATA_PTR;

int checkboard(void)
{
	return 0;
}

int early_board_init(void)
{
	int i;
	static const uint8_t tuple_addresses[] = {
		OCTEON_EBB6100_BOARD_EEPROM_TWSI_ADDR, 0x54
	};

	/* NOTE: this is early in the init process, so the serial port is not
	 * yet configured
	 */
	for (i = 0; i < ARRAY_SIZE(tuple_addresses); i++) {
		gd->arch.tlv_addr = tuple_addresses[i];
		octeon_board_get_descriptor(CVMX_BOARD_TYPE_GENERIC, 1, 0);
		if (gd->board_type != CVMX_BOARD_TYPE_GENERIC) {
			debug("%s: found TLV EEPROM at address 0x%x\n",
			      __func__, gd->arch.tlv_addr);
			break;
		}
	}
	if (i == ARRAY_SIZE(tuple_addresses)) {
		puts("ERROR: Board TLV descriptor not found!  Cannot continue!\n");
		return -1;
	}

	octeon_board_get_clock_info(GENERIC_EMMC_DEF_DRAM_FREQ);

	/* CN63XX has a fixed 50 MHz reference clock */
	gd->arch.ddr_ref_hertz = 50000000;

	if (gd->mem_clk < 100 || gd->mem_clk > 2000)
		gd->mem_clk = GENERIC_EMMC_DEF_DRAM_FREQ;

	octeon_board_get_mac_addr();

	return 0;
}

void late_board_init(void)
{
	char buf[256];
	char *board_name;
	board_name = getenv("boardname");
	if (board_name) {
		sprintf(buf, "u-boot-octeon_%s.bin", board_name);
		setenv("octeon_stage3_bootloader", buf);
	}
}
