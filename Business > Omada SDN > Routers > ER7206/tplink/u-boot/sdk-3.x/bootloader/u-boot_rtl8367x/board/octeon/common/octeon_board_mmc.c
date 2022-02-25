/*
 * (C) Copyright 2012 - 2013 Cavium, Inc.
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
#include <libfdt.h>
#include <fdt_support.h>
#include <fdt.h>
#include <fdtdec.h>
#include <asm/arch/cvmx.h>
#include <asm/arch/octeon_board_mmc.h>
#include <asm/arch/octeon-feature.h>

#ifndef CONFIG_OCTEON_MAX_MMC_SLOT
# define CONFIG_OCTEON_MAX_MMC_SLOT 4
#endif

DECLARE_GLOBAL_DATA_PTR;

int octeon_boot_bus_mmc_get_info(struct octeon_mmc_info *mmc_info)
	__attribute__((weak, alias("__octeon_boot_bus_mmc_get_info")));

int __octeon_boot_bus_mmc_get_info(struct octeon_mmc_info *mmc_info)
{
	int i;
#ifdef CONFIG_OF_LIBFDT
	int nodeoffset;
	uint32_t *pgpio_handle;
	int len;
	int gpio_offset;
	int phandle;
	int default_power_gpio = -1;
	int default_power_active_low = 0;
#endif

	if (!octeon_has_feature(OCTEON_FEATURE_MMC))
		return -1;

	if (mmc_info == NULL)
		return -1;

	memset(mmc_info, 0, sizeof(mmc_info));
#ifdef CONFIG_OF_LIBFDT
	nodeoffset = fdt_path_offset(gd->fdt_blob, "/soc/mmc");

	if (nodeoffset < 0) {
		debug("MMC interface not found\n");
		return -1;
	}

	if (fdt_node_check_compatible(gd->fdt_blob, nodeoffset,
				      "cavium,octeon-6130-mmc")) {
		puts("Incompatible MMC interface type in FDT\n");
		return -1;
	}

	pgpio_handle = (uint32_t *)fdt_getprop(gd->fdt_blob, nodeoffset,
					       "power-gpios", &len);
	if (pgpio_handle && len == 12) {
		phandle = fdt32_to_cpu(pgpio_handle[0]);
		gpio_offset = fdt_node_offset_by_phandle(gd->fdt_blob, phandle);
		if (gpio_offset < 0) {
			printf("%s: Cannot access parent GPIO node in DT\n", __func__);
			return -1;
		}
		if (fdt_node_check_compatible(gd->fdt_blob, gpio_offset,
					      "cavium,octeon-3860-gpio")) {
			printf("%s: ERROR: Only native GPIO pins supported\n", __func__);
			return -1;
		}
		default_power_gpio = fdt32_to_cpu(pgpio_handle[1]);
		default_power_active_low = (fdt32_to_cpu(pgpio_handle[2]) & 1);
		if (fdt_getprop(gd->fdt_blob, nodeoffset, "power-inverted", NULL))
			default_power_active_low ^= 1;

		debug("%s: MMC default power GPIO %d active %s\n",
		      __func__, default_power_gpio,
		      default_power_active_low ? "low" : "high");
	}

#endif
	memset(mmc_info, 0, sizeof(*mmc_info));

	for (i = 0; i < CONFIG_OCTEON_MAX_MMC_SLOT; i++) {
#ifdef CONFIG_OF_LIBFDT
		int slot_offset = 0;
		char name[16];
		int slot;
		const char *slot_name = NULL;
		int found;
		int next_node;
#endif
		mmc_info->slot[i].chip_sel = -1;
#ifdef CONFIG_OF_LIBFDT
		sprintf(name, "mmc-slot@%i", i);
		debug("Searching for %s\n", name);
		found = 0;
		next_node = fdt_subnode_offset(gd->fdt_blob, nodeoffset,
					       "mmc-slot");
		if (next_node < 0) {
			printf("No MMC slot entries found in device tree\n");
			return -1;
		}

		do {
			int depth = 0;

			slot_offset = next_node;

			debug("%s: slot offset: %d\n", name, slot_offset);
			if (slot_offset < 0)
				break;

			/* Find the next node */
			do {
				next_node = fdt_next_node(gd->fdt_blob,
							  next_node, &depth);
			} while (next_node > 0 && depth > 0);
			debug("  next node: %d\n", next_node);
			/* Make sure we're compatible */
			if (fdt_node_check_compatible(gd->fdt_blob, slot_offset,
						      "cavium,octeon-6130-mmc-slot")) {
				debug("Incompatible mmc-slot found\n");
				break;;
			}

			/* Is this the slot we're looking for? */
			slot_name = fdt_get_name(gd->fdt_blob, slot_offset,
						 NULL);
			debug("Comparing device tree slot %s with %s\n",
			      slot_name, name);
			found = !strcmp(slot_name, name);
			if (!found)
				debug("Slot name %s doesn't match %s, continuing\n",
				      slot_name, name);
		} while (!found);

		if (!found || slot_offset < 0) {
			debug("%s not found, trying next\n", name);
			continue;
		}

		debug("%s: Found match %s\n", __func__, slot_name);

		slot = fdtdec_get_int(gd->fdt_blob, slot_offset, "reg", -1);
		if (slot < 0) {
			printf("Chip select for mmc slot %d missing in FDT\n", i);
			return -1;
		}

		debug("Chip select for %s is %d\n", name, slot);
		if (slot != i) {
			printf("Bad register address %d for MMC slot %d (%s)\n",
			       slot, i, name);
			return -1;
		}

		mmc_info->slot[i].chip_sel = i;

		mmc_info->slot[i].max_frequency =
			fdtdec_get_int(gd->fdt_blob, slot_offset,
				       "spi-max-frequency", 50000000);

		mmc_info->slot[i].bus_max_width =
			fdtdec_get_int(gd->fdt_blob, slot_offset,
				       "cavium,max-bus-width", 8);

		mmc_info->slot[i].cmd_clk_skew =
			fdtdec_get_int(gd->fdt_blob, slot_offset,
				       "cavium,cmd-clk-skew", 0);

		mmc_info->slot[i].dat_clk_skew =
			fdtdec_get_int(gd->fdt_blob, slot_offset,
				       "cavium,dat-clk-skew", 0);

		mmc_info->slot[i].power_gpio = default_power_gpio;
		mmc_info->slot[i].power_active_low = default_power_active_low;
		pgpio_handle = (uint32_t *)fdt_getprop(gd->fdt_blob,
						       slot_offset,
						       "power-gpios", &len);
		if (pgpio_handle && len == 12) {
			phandle = fdt32_to_cpu(pgpio_handle[0]);
			gpio_offset = fdt_node_offset_by_phandle(gd->fdt_blob,
							 phandle);
			if (gpio_offset < 0) {
				printf("%s: Cannot access parent GPIO node in DT\n",
				       __func__);
				return -1;
			}
			if (fdt_node_check_compatible(gd->fdt_blob,
						      gpio_offset,
						      "cavium,octeon-3860-gpio")) {
				printf("%s: ERROR: Only native GPIO pins supported\n",
				       __func__);
				return -1;
			}
			mmc_info->slot[i].power_gpio = fdt32_to_cpu(pgpio_handle[1]);
			mmc_info->slot[i].power_active_low = (fdt32_to_cpu(pgpio_handle[2]) & 1);
			if (fdt_getprop(gd->fdt_blob, slot_offset, "power-inverted", NULL))
				mmc_info->slot[i].power_active_low ^= 1;

			debug("%s: MMC slot %d power GPIO %d active %s\n",
			      __func__, i, mmc_info->slot[i].power_gpio,
			      mmc_info->slot[i].power_active_low ? "low" : "high");
		}

		mmc_info->slot[i].cd_gpio = -1;
		pgpio_handle = (uint32_t *)fdt_getprop(gd->fdt_blob,
						       slot_offset,
						       "cd-gpios", &len);
		if (pgpio_handle && len == 12) {
			phandle = fdt32_to_cpu(pgpio_handle[0]);
			gpio_offset = fdt_node_offset_by_phandle(gd->fdt_blob,
							 phandle);
			if (gpio_offset < 0) {
				printf("%s: Cannot access parent GPIO node in DT\n",
				       __func__);
				return -1;
			}
			if (fdt_node_check_compatible(gd->fdt_blob,
						      gpio_offset,
						      "cavium,octeon-3860-gpio")) {
				printf("%s: ERROR: Only native GPIO pins supported\n",
				       __func__);
				return -1;
			}
			mmc_info->slot[i].cd_gpio = fdt32_to_cpu(pgpio_handle[1]);
			mmc_info->slot[i].cd_active_low = (fdt32_to_cpu(pgpio_handle[2]) & 1);
			if (fdt_getprop(gd->fdt_blob, slot_offset, "cd-inverted", NULL))
				mmc_info->slot[i].cd_active_low ^= 1;

			debug("%s: MMC slot %d cd GPIO %d active %s\n",
			      __func__, i, mmc_info->slot[i].cd_gpio,
			      mmc_info->slot[i].cd_active_low ? "low" : "high");
		} else {
			mmc_info->slot[i].cd_gpio = -1;
		}

		mmc_info->slot[i].wp_gpio = -1;
		pgpio_handle = (uint32_t *)fdt_getprop(gd->fdt_blob,
						       slot_offset,
						       "wp-gpios", &len);
		if (pgpio_handle && len == 12) {
			phandle = fdt32_to_cpu(pgpio_handle[0]);
			gpio_offset = fdt_node_offset_by_phandle(gd->fdt_blob,
							 phandle);
			if (gpio_offset < 0) {
				printf("%s: Cannot access parent GPIO node in DT\n",
				       __func__);
				return -1;
			}
			if (fdt_node_check_compatible(gd->fdt_blob,
						      gpio_offset,
						      "cavium,octeon-3860-gpio")) {
				printf("%s: ERROR: Only native GPIO pins supported\n",
				       __func__);
				return -1;
			}
			mmc_info->slot[i].wp_gpio =
					fdt32_to_cpu(pgpio_handle[1]);
			mmc_info->slot[i].wp_active_low =
					(fdt32_to_cpu(pgpio_handle[2]) & 1);
			if (fdt_getprop(gd->fdt_blob, slot_offset,
					"wp-inverted", NULL))
				mmc_info->slot[i].wp_active_low ^= 1;
			debug("%s: MMC slot %d wp GPIO %d active %s\n",
			      __func__, i, mmc_info->slot[i].cd_gpio,
			      mmc_info->slot[i].cd_active_low ? "low" : "high");
		} else {
			mmc_info->slot[i].wp_gpio = -1;
		}

#else
		if (CONFIG_OCTEON_AVAIL_MMC_SLOTS & (1 << i))
			mmc_info->slot[i].chip_sel = i;
		mmc_info->slot[i].max_frequency = CONFIG_OCTEON_MMC_MAX_FREQUENCY;
		mmc_info->slot[i].bus_max_width = CONFIG_OCTEON_MMC_MAX_WIDTH;
# ifdef CONFIG_OCTEON_MMC_WP_GPIO
		mmc_info->slot[i].wp_gpio = CONFIG_OCTEON_MMC_WP_GPIO;
# else
		mmc_info->slot[i].wp_gpio = -1;
# endif
# ifdef CONFIG_OCTEON_MMC_CD_GPIO
		mmc_info->slot[i].cd_gpio = CONFIG_OCTEON_MMC_CD_GPIO;
# else
		mmc_info->slot[i].cd_gpio = -1;
# endif
# ifdef CONFIG_OCTEON_MMC_POWER_GPIO
		mmc_info->slot[i].power_gpio = CONFIG_OCTEON_MMC_POWER_GPIO;
# else
		mmc_info->slot[i].power_gpio = -1;
# endif
#endif
		switch (mmc_info->slot[i].bus_max_width) {
		case 1:
		case 4:
		case 8:
			break;
		default:
			printf("Bad bus-max-width %d for MMC slot %d in FDT\n",
			       mmc_info->slot[i].bus_max_width, i);
			return -1;
		}
	}
	return 0;
}
