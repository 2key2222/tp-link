/*
 * (C) Copyright 2004 - 2013
 * Cavium Inc.
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

#include <common.h>
#include <asm/mipsregs.h>
#include <asm/arch/octeon_boot.h>
#include <asm/arch/cvmx-sim-magic.h>
#include <asm/arch/cvmx-qlm.h>

DECLARE_GLOBAL_DATA_PTR;

/* Device tree */
extern char __dtb_begin;
extern char __dtb_end;
extern char __dtb_68xx_begin;
extern char __dtb_68xx_end;
extern char __dtb_78xx_begin;
extern char __dtb_78xx_end;

int checkboard(void)
{
	if (OCTEON_IS_MODEL(OCTEON_CN31XX)
	    || OCTEON_IS_MODEL(OCTEON_CN30XX)
	    || OCTEON_IS_MODEL(OCTEON_CN50XX)) {
		/* Enable RGMII/GMII interface block */
		cvmx_gmxx_inf_mode_t mode;
		mode.u64 = cvmx_read_csr(CVMX_GMXX_INF_MODE(0));
		mode.s.en = 1;
		cvmx_write_csr(CVMX_GMXX_INF_MODE(0), mode.u64);
	}
	/* See if we need to adjust DRAM width for CN3020 simulation */
	if (OCTEON_IS_MODEL(OCTEON_CN3020)) {
		/* We are a 3020, so make the DDR interface 32 bits */
		cvmx_lmc_ctl_t lmc_ctl;
		lmc_ctl.u64 = cvmx_read_csr(CVMX_LMC_CTL);
		lmc_ctl.cn31xx.mode32b = 1;
		cvmx_write_csr(CVMX_LMC_CTL, lmc_ctl.u64);
	}
#ifdef CONFIG_OCTEON_QLM
	if (OCTEON_IS_MODEL(OCTEON_CN70XX)) {
		/* DLM0 to SGMII */
		octeon_configure_qlm(0, 1250, CVMX_QLM_MODE_SGMII_DISABLED, 0, 0, 0, 0);
	}
#endif
	return 0;
}

void octeon_led_str_write(const char *str)
{
	/* Not implemented on simulator */
	return;
}

int board_fdt_init_f(void)
{
	if (OCTEON_IS_MODEL(OCTEON_CN78XX))
		gd->fdt_blob = &__dtb_78xx_begin;
	else if (OCTEON_IS_MODEL(OCTEON_CN68XX))
		gd->fdt_blob = &__dtb_68xx_begin;
	else
		gd->fdt_blob = &__dtb_begin;

	return fdt_check_header(gd->fdt_blob);
}
void board_fdt_get_limits(char **begin, char **end)
{
	if (OCTEON_IS_MODEL(OCTEON_CN78XX)) {
		*begin = &__dtb_78xx_begin;
		*end = &__dtb_78xx_end;
	} else if (OCTEON_IS_MODEL(OCTEON_CN68XX)) {
		*begin = &__dtb_68xx_begin;
		*end = &__dtb_68xx_end;
	} else {
		*begin = &__dtb_begin;
		*end = &__dtb_end;
	}
}

/**
 * Modify the device tree to remove all unused interface types.
 */
int board_fixup_fdt(void)
{
	const char *alias_prop;
	int aliases;
	int i;

	aliases = fdt_path_offset(working_fdt, "/aliases");

	for (i = 0; i < 2; i++) {
		char fdt_key[20];
		sprintf(fdt_key, "mix%d", i);
		/* Some models do not have mgmt port and some have only one. */
		alias_prop = fdt_getprop(working_fdt, aliases, fdt_key, NULL);

		if (alias_prop) {
			int mix = fdt_path_offset(working_fdt, alias_prop);
			int del = 0;
			if (i == 0 && mix >= 0
			    && (OCTEON_IS_MODEL(OCTEON_CN3XXX)
				|| OCTEON_IS_MODEL(OCTEON_CN58XX)
				|| OCTEON_IS_MODEL(OCTEON_CN70XX)))
				del = 1;
			else if (i == 1 && mix >= 0
				 && (OCTEON_IS_MODEL(OCTEON_CN3XXX)
				     || OCTEON_IS_MODEL(OCTEON_CN58XX)
				     || OCTEON_IS_MODEL(OCTEON_CN56XX)
				     || OCTEON_IS_MODEL(OCTEON_CN70XX)))
				del = 1;
			if (del) {
				debug("Deleting %s\n", fdt_key);
				fdt_nop_node(working_fdt, mix);
				fdt_nop_property(working_fdt, aliases, fdt_key);
			}
		}
	}
	return 0;
}


int early_board_init(void)
{
	gd->arch.board_desc.board_type = CVMX_BOARD_TYPE_SIM;
	gd->board_type = gd->arch.board_desc.board_type;
	gd->arch.board_desc.rev_major = 1;
	gd->arch.board_desc.rev_minor = 0;

	gd->cpu_clk = cvmx_sim_magic_get_cpufreq() * 1000000;

	/* Make up some MAC addresses */
	gd->arch.mac_desc.count = 255;
	gd->arch.mac_desc.mac_addr_base[0] = 0x00;
	gd->arch.mac_desc.mac_addr_base[1] = 0xDE;
	gd->arch.mac_desc.mac_addr_base[2] = 0xAD;
	gd->arch.mac_desc.mac_addr_base[3] = 0xbe;
	gd->arch.mac_desc.mac_addr_base[4] = 0xef;
	gd->arch.mac_desc.mac_addr_base[5] = 0x00;

	return 0;
}
