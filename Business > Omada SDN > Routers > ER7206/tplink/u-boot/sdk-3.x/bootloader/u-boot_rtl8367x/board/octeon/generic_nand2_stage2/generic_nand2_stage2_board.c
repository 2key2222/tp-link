/*
 * (C) Copyright 2004-2011
 * Cavium Inc.
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
#include <i2c.h>

DECLARE_GLOBAL_DATA_PTR;

static const uint8_t tuple_addresses[] = {
	OCTEON_EVB7000_BOARD_EEPROM_TWSI_ADDR,
	OCTEON_SFF7000_BOARD_EEPROM_TWSI_ADDR,
};

int checkboard(void)
{
	return 0;
}

int early_board_init(void)
{
	const int cpu_ref = DEFAULT_CPU_REF_FREQUENCY_MHZ;
	int i;

	gd->arch.ddr_ref_hertz = 50000000;

	i2c_set_bus_num(0);

	for (i = 0; i < ARRAY_SIZE(tuple_addresses); i++) {
		gd->arch.tlv_addr = tuple_addresses[i];
		octeon_board_get_descriptor(CVMX_BOARD_TYPE_GENERIC, 1, 0);
		debug("Board descriptor type at i2c address 0x%x is %d, i2c bus: %d\n",
		      gd->arch.tlv_addr, gd->board_type, i2c_get_bus_num());
		if (gd->board_type != CVMX_BOARD_TYPE_GENERIC)
			break;
	}
	if (i == ARRAY_SIZE(tuple_addresses)) {
		puts("ERROR: Board TLV descriptor not found!  Cannot continue!\n"
		     "Use the tlv_eeprom command to program the board type.\n");
		return -1;
	}

	/* NOTE: this is early in the init process, so the serial port is not
	 * yet configured
	 */
	octeon_board_get_clock_info(DEFAULT_DDR3_CLOCK_FREQ_MHZ);


	printf("%s: Board type: %s\n", __func__,
	       cvmx_board_type_to_string(gd->board_type));

	/* Read CPU clock multiplier */
	gd->cpu_clk = octeon_get_cpu_multiplier() * cpu_ref * 1000000;

	if (gd->mem_clk < 100 || gd->mem_clk > 2000)
		gd->mem_clk = DEFAULT_DDR3_CLOCK_FREQ_MHZ;

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
