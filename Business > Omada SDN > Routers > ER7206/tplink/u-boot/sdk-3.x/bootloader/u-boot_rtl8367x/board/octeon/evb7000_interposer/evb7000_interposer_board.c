/*
 * (C) Copyright 2013 Cavium, Inc. <support@cavium.com>
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
#define DEBUG
#include <common.h>
#include <asm/mipsregs.h>
#include <asm/arch/octeon_boot.h>
#include <asm/arch/octeon_board_common.h>
#include <asm/arch/octeon_fdt.h>
#include <asm/arch/lib_octeon_shared.h>
#include <asm/arch/lib_octeon.h>
#include <asm/arch/cvmx-helper-jtag.h>
#include <asm/gpio.h>
#include <asm/arch/cvmx-qlm.h>

DECLARE_GLOBAL_DATA_PTR;

void board_net_preinit(void)
{
	mdelay(120);
}
/**
 * Modify the device tree to remove all unused interface types.
 */
int board_fixup_fdt(void)
{
	const char *fdt_key;
	u8 dlm_sel;

	dlm_sel = 7 ^ ((gpio_get_value(1) << 2) | (gpio_get_value(2) << 1) |
		       gpio_get_value(3));

	if (OCTEON_IS_OCTEON2()) {
		octeon_fdt_patch(working_fdt, "9,octeon2", NULL);
		fdt_key = "2,sgmii";
	} else {
		octeon_fdt_patch(working_fdt, "9,octeon3", NULL);
		switch (dlm_sel >> 1) {
		case 0:
			octeon_fdt_patch(working_fdt, "0,sata", NULL);
			break;
		case 1:
		case 2:
		case 3:
			octeon_fdt_patch(working_fdt, "0,pci", NULL);
			break;
		}
		fdt_key = "2,qsgmii";	/* Actually on DLM0 */
	}

	debug("Patching FDT with key %s\n", fdt_key);
	octeon_fdt_patch(working_fdt, fdt_key, NULL);

	if (OCTEON_IS_OCTEON2())
		fdt_key = "4,mix";
	else
		fdt_key = "4,agl";

	debug("Patching FDT with key %s\n", fdt_key);
	octeon_fdt_patch(working_fdt, fdt_key, NULL);

	return 0;
}

int checkboard(void)
{
	u8 dlm_sel;

	dlm_sel = 7 ^ ((gpio_get_value(1) << 2) | (gpio_get_value(2) << 1) |
		       gpio_get_value(3));

#ifdef CONFIG_OCTEON_QLM
	if (OCTEON_IS_OCTEON2()) {
		/* Hard-code to PCIe 2x1 mode for now */
		octeon_configure_qlm(0, 5000, 0, 1, 3, 0, 0);
		octeon_configure_qlm(1, 5000, 0, 1, 0, 0, 0);

		/* Hard code to SGMII for now */
		octeon_configure_qlm(2, 1250, 2, 0, 0, 0, 0);
	} else {
		debug("Configuring DLM0 for QSGMII\n");
		octeon_configure_qlm(0, 2500, CVMX_QLM_MODE_QSGMII_QSGMII,
				     0, 0, 0, 0);
		debug("Done.\n");
	}
	if (OCTEON_IS_OCTEON2()) {
		if (dlm_sel & 4) {
			puts("SW4-1 off: 2x Mini-PCIe slots active (only slot 0 works)\n");
			octeon_configure_qlm(0, 5000, 0, 1, 3, 0, 0);
		} else {
			puts("SW4-1 on: PCIe x4 Slot (x2 mode on CN61XX)\n");
			octeon_configure_qlm(0, 5000, 0, 1, 3, 0, 0);
		}

		switch (dlm_sel & 3) {
		case 0:
			puts("SW4-2 off, SW4-3 off: PCIe x4 slot (invalid with CN6XXX)\n");
			octeon_configure_qlm(1, 0, 0, 1, 3, 0, 0);
			break;
		case 1:
			puts("SW4-2 off, SW4-3 on: SATA 2.0 mode\n");
			break;
			octeon_configure_qlm(1, 5000, 0, 1, 3, 0, 0);
		case 2:
			puts("SW4-2 on, SW4-3 off: SATA 3.0 mode (invalid with CN6XXX)\n");
			octeon_configure_qlm(1, 0, 0, 1, 3, 0, 0);
			break;
		case 3:
			puts("SW4-2 on, SW4-3 on: Invalid\n");
			octeon_configure_qlm(1, 0, 2, 1, 3, 0, 0);
			break;
		}
	} else if (OCTEON_IS_MODEL(OCTEON_CN70XX)) {
		if (dlm_sel & 4) {
			puts("SW4-1 on: 2x Mini-PCIe Slots Active\n");
			octeon_configure_qlm(1, 5000, CVMX_QLM_MODE_PCIE_2X1, 1, 1, 0, 0);
		} else {
			puts("SW4-1 off: 4x PCIe slot active\n");
			octeon_configure_qlm(1, 5000, CVMX_QLM_MODE_PCIE_2X1, 1, 1, 0, 0);
		}

		switch (dlm_sel >> 1) {
		case 0:
			puts("SW4-2 off, SW4-3 off: SATA 3.0\n");
			octeon_configure_qlm(2, 3125, CVMX_QLM_MODE_SATA_2X1, 1, 0, 0, 0);
			break;
		case 1:
			puts("SW4-2 off, SW4-3 on: SATA 2.0\n");
			octeon_configure_qlm(2, 5000, CVMX_QLM_MODE_PCIE_1X2, 1, 0, 0, 0);
			break;
		case 2:
			puts("SW4-2 on, SW4-3 off: PCIe X4 slot in 4x mode\n");
			puts("FIX THIS!!\n");
#warning need to fix this, QLM2 is upper 2 lanes!
			octeon_configure_qlm(2, 5000, CVMX_QLM_MODE_PCIE_1X2, 1, 0, 0, 0);
			break;
		case 3:
			puts("SW4-2 on, SW4-3 on:\n");
			break;
		}
	} else {
		puts("Unsupported OCTEON model!\n");
		return -1;
	}
#endif

	debug("Powering up Vitesse PHYs\n");
	gpio_direction_output(9, 0);	/* COMA mode */

	return 0;
}

int early_board_init(void)
{
	int cpu_ref = DEFAULT_CPU_REF_FREQUENCY_MHZ;
	union cvmx_gpio_clk_qlmx clk_qlmx;

	/* Enable USB power */
	gpio_direction_output(18, 0);
	gpio_direction_output(19, 0);

	gpio_direction_input(1);	/* DLM1_SEL */
	gpio_direction_input(2);	/* DLM2A_SEL */
	gpio_direction_input(3);	/* DLM2B_SEL */
	gpio_direction_output(9, 1);	/* Vitesse COMA mode */

	gpio_direction_input(14);	/* SD/MMC Write Protect */
	gpio_direction_input(15);	/* SD/MMC Card Detect */
	mdelay(10);
	/* Take SYS_RESET_L out of reset */
	gpio_set_value(1, 1);

	/* Populate global data from eeprom */
	octeon_board_get_clock_info(EVB7000_INTERPOSER_DEF_DRAM_FREQ);

	octeon_board_get_descriptor(CVMX_BOARD_TYPE_EVB7000_INTERPOSER, 1, 0);

	/* CN63XX has a fixed 50 MHz reference clock */
	gd->arch.ddr_ref_hertz = 50000000;

	octeon_board_get_mac_addr();

	return 0;
}
