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
#include <i2c.h>
#include <asm/gpio.h>
#include <miiphy.h>
#include <asm/arch/octeon_boot.h>
#include <asm/arch/octeon_board_common.h>
#include <asm/arch/lib_octeon_shared.h>
#include <asm/arch/lib_octeon.h>
#include <asm/arch/octeon_fdt.h>
#include <asm/arch/octeon_board_phy.h>

DECLARE_GLOBAL_DATA_PTR;

int checkboard(void)
{
	uchar temp;
	/* Note that the SA56004 will be programmed again later with DTT */
	/* Internal SA56004 temp, approximates ambient/board temp. */
	temp = 80;
	i2c_write(CONFIG_SYS_I2C_DTT_ADDR, 0x20, 1, &temp, 1);
	/* Internal Octeon temp, approximates junction temp. */
	temp = 100;
	i2c_write(CONFIG_SYS_I2C_DTT_ADDR, 0x19, 1, &temp, 1);

	/* Take PHY out of reset */
	gpio_direction_output(4, 1);
	return 0;
}


int early_board_init(void)
{
	/* configure clk_out pin */
	cvmx_mio_fus_pll_t fus_pll;

	fus_pll.u64 = cvmx_read_csr(CVMX_MIO_FUS_PLL);
	fus_pll.cn63xx.c_cout_rst = 1;
	cvmx_write_csr(CVMX_MIO_FUS_PLL, fus_pll.u64);

	/* Sel::  0:rclk, 1:pllout 2:psout 3:gnd */
	fus_pll.cn63xx.c_cout_sel = 0;
	cvmx_write_csr(CVMX_MIO_FUS_PLL, fus_pll.u64);
	fus_pll.cn63xx.c_cout_rst = 0;
	cvmx_write_csr(CVMX_MIO_FUS_PLL, fus_pll.u64);

	/* Enable PSRAM (take out of low power mode) */
	gpio_direction_output(0, 1);

	/* Reset Vitesse PHY */
	gpio_direction_output(4, 0);

	/* Set fan sense to input */
	gpio_direction_input(7);

	/* Set MOD pins as inputs */
	gpio_direction_input(1);
	gpio_direction_input(6);
	gpio_direction_input(8);
	gpio_direction_input(17);
	/* temp alert */
	gpio_direction_input(15);

	/* Vitesse interrupts */
	gpio_direction_input(9);
	gpio_direction_input(10);
	gpio_direction_input(11);
	gpio_direction_input(12);


	/* NOTE: this is early in the init process, so the serial port is not
	 * yet configured
	 */

	/* Populate global data from eeprom */
	octeon_board_get_clock_info(NIC401NVG_DEF_DRAM_FREQ);

	octeon_board_get_descriptor(CVMX_BOARD_TYPE_NIC401NVG, 3, 0);

	/* CN63XX has a fixed 50 MHz reference clock */
	gd->arch.ddr_ref_hertz = 50000000;

	octeon_board_get_mac_addr();

	return 0;
}
