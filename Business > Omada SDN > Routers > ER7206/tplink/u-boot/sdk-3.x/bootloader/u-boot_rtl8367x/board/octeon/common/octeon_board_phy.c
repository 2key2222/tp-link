/*
 * (C) Copyright 2012-2014 Cavium, Inc. <support@cavium.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <miiphy.h>
#include <phy.h>
#include <net.h>
#include <fdt_support.h>
#include <fdtdec.h>
#include <libfdt.h>
#include <i2c.h>
#include <asm/gpio.h>
#include <asm/arch/octeon_eth.h>
#include <asm/arch/cvmx.h>
#include <asm/arch/cvmx-qlm.h>
#include <asm/arch/octeon_fdt.h>
#include <asm/arch/cvmx-helper-fdt.h>
#ifdef CONFIG_PCA953X
# include <pca953x.h>
#endif
#ifdef CONFIG_PCF857X
# include <pcf857x.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_PHY_VITESSE

/** Maximum number of COMA GPIOs */
#define MAX_COMA_GPIOS		32

/** Describes each COMA pin */
struct gpio_pin {
	enum cvmx_gpio_type type;	/** Type of GPIO bus */
	uint8_t i2c_addr;	/** If an I2C GPIO device the I2C address */
	uint8_t pin:7;		/** GPIO pin on device */
	uint8_t invert:1;	/** If COMA should be inverted or not */
	uint8_t i2c_bus;	/** I2C bus number if I2C GPIO expander */
};

static int num_coma_gpios = 0;	/** Number of COMA GPIOs to activate */

/** Describes each COMA GPIO pin */
static struct gpio_pin coma_gpios[MAX_COMA_GPIOS];

#define COMA_FLAG_ACTIVE_LOW	0x80
#define COMA_GPIO_MASK		0x7f

enum vsc8574_media_mode {
	MM_COPPER,
	MM_1000BX,
	MM_100FX
};
#endif

extern int octeon_i2c_reg_addr_to_bus(uint64_t addr);
extern uint32_t i2c_get_stop_delay(void);
extern int i2c_set_stop_delay(uint32_t delay);

#if defined(CONFIG_PHYLIB_10G) && defined (CONFIG_PHY_MARVELL)
/**
 * Configure generic clause 45 PHY
 *
 * @param ethdev	- ethernet device to configure
 * @param init_seq_str	- init sequence string, i,e. ti,reg-init
 *
 * @return 0 for success, error otherwise
 */
static int octeon_fdt_generic_c45_config(const struct eth_device *ethdev,
					 const char *init_seq_str)
{
	struct octeon_eth_info *oct_eth_info =
		 (struct octeon_eth_info *)ethdev->priv;
	uint8_t dev;
	uint16_t reg;
	uint16_t mask;
	uint16_t value;
	int len;
	uint32_t *init_seq;
	int seq_len;
	int phy_node_offset = oct_eth_info->phy_node_offset;

	debug("%s(%s)\n", __func__, ethdev->name);

	if (fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "marvell,88x3120") &&
	    fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "ti,tlk10232")) {
		printf("%s: Warning: untested Clause 45 PHY for %s\n",
		       __func__, ethdev->name);
	}
	init_seq = (uint32_t *)fdt_getprop(gd->fdt_blob, phy_node_offset,
					   init_seq_str, &len);
	if (!init_seq)
		return 0;

	if (len % 16 != 0) {
		printf("Invalid init sequence in DT for generic Clause 45 PHY for %s\n",
		       ethdev->name);
		return -1;
	}

	seq_len = len / 16;
	while (seq_len--) {
		dev = fdt32_to_cpu(*init_seq++);
		reg = fdt32_to_cpu(*init_seq++);
		mask = fdt32_to_cpu(*init_seq++);
		if (!mask) {
			value = fdt32_to_cpu(*init_seq++);
		} else {
			value = phy_read(oct_eth_info->phydev, dev, reg);
			value &= mask;
			value |= fdt32_to_cpu(*init_seq++);
		}
		debug("Init for %s addr: 0x%x, dev: 0x%x, reg: 0x%x, mask: 0x%x, value: 0x%x\n",
		      ethdev->name, oct_eth_info->phydev->addr, dev, reg, mask,
		      value);
		phy_write(oct_eth_info->phydev, dev, reg, value);
	}
	return 0;
}
#endif

#ifdef CONFIG_PHY_MARVELL
/**
 * @INTERNAL
 * Configures a Marvell PHY based on the device tree
 *
 * @param ethdev - Ethernet device to configure
 *
 * @return 0 for success, error otherwise
 */
static int octeon_fdt_marvell_config(const struct eth_device *ethdev)
{
	struct octeon_eth_info *oct_eth_info =
		 (struct octeon_eth_info *)ethdev->priv;
		uint32_t page, reg, mask, value;
	int last_page = -1;
	int len;
	uint32_t *init_seq;
	int seq_len;
	int phy_node_offset = oct_eth_info->phy_node_offset;

	debug("%s(%s)\n", __func__, ethdev->name);
#ifdef CONFIG_PHYLIB_10G
	if (!fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				       "ethernet-phy-ieee802.3-c45"))
		return octeon_fdt_generic_c45_config(ethdev, "marvell,reg-init");
#endif

	/* Check for at least one compatible Marvell PHY */
	if (fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "marvell,88e1118") &&
	    fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "marvell,88e1149") &&
	    fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "marvell,88e1149r") &&
	    fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "marvell,88e1145") &&
	    fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "marvell,88e1240") &&
	    fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "marvell,88e1680")) {
		printf("%s: Warning: unknown Marvell PHY for %s\n",
		       __func__, ethdev->name);
		return 0;
	}

	init_seq = (uint32_t *)fdt_getprop(gd->fdt_blob, phy_node_offset,
					   "marvell,reg-init", &len);
	if (!init_seq)
		return 0;

	if (len % 16 != 0) {
		printf("Invalid init sequence in DT for Marvell PHY for %s\n",
		       ethdev->name);
		return -1;
	}

	seq_len = len / 16;
	while (seq_len--) {
		page = fdt32_to_cpu(*init_seq++);
		reg = fdt32_to_cpu(*init_seq++);
		mask = fdt32_to_cpu(*init_seq++);
		if (page != last_page) {
			phy_write(oct_eth_info->phydev, MDIO_DEVAD_NONE,
				  0x16, page);
			last_page = page;
		}

		if (mask) {
			value = phy_read(oct_eth_info->phydev, MDIO_DEVAD_NONE,
					 reg);
			value &= mask;
			value |= fdt32_to_cpu(*init_seq++);
		} else {
			value = fdt32_to_cpu(*init_seq++);
		}
		debug("Marvell init for %s addr: %d: page: %d, reg: %d, mask: 0x%x, value: 0x%x\n",
		      ethdev->name, oct_eth_info->phydev->addr, page, reg,
		      mask, value);

		phy_write(oct_eth_info->phydev, MDIO_DEVAD_NONE, reg, value);
	}
	/* Reset to page 0 */
	if (last_page != 0)
		phy_write(oct_eth_info->phydev, MDIO_DEVAD_NONE, 0x16, 0);

	return 0;
}
#endif /* CONFIG_PHY_MARVELL */
#ifdef CONFIG_PHY_BROADCOM
/**
 * @INTERNAL
 * Configures a Broadcom PHY based on the device tree
 *
 * @param ethdev - Ethernet device to configure
 *
 * @return 0 for success, error otherwise
 */
static int octeon_fdt_broadcom_config(const struct eth_device *ethdev)
{
	struct octeon_eth_info *oct_eth_info =
		 (struct octeon_eth_info *)ethdev->priv;
	uint32_t devid = MDIO_DEVAD_NONE;
	uint32_t reg, mask;
	int value;
	int c45 = 0;	/* True if clause-45 mode */
	int len;
	uint32_t *init_seq;
	int seq_len;
	int phy_node_offset = oct_eth_info->phy_node_offset;

	debug("%s(%s)\n", __func__, ethdev->name);

	/* Check for at least one compatible Broadcom PHY */
	if (fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "broadcom,bcm5466") &&
	    fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "broadcom,bcm5482") &&
	    fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "broadcom,bcm5464r") &&
	    fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "broadcom,bcm5464") &&
	    fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "broadcom,bcm5241") &&
	    fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "broadcom,bcm7806") &&
	    fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "broadcom,bcm8706") &&
	    fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "broadcom,bcm8727") ) {

		printf("%s: Unknown broadcom phy for %s\n",
		       __func__, ethdev->name);
		return 0;
	}

	init_seq = (uint32_t *)fdt_getprop(gd->fdt_blob, phy_node_offset,
					   "broadcom,c45-reg-init", &len);
	if (init_seq)
		c45 = 1;
	else
		init_seq = (uint32_t *)fdt_getprop(gd->fdt_blob,
						   phy_node_offset,
						   "broadcom,reg-init", &len);
	if (!init_seq)
		return 0;

	if ((c45 && (len % 16 != 0)) || (!c45 && (len % 12 != 0))) {
		printf("Invalid init sequence in DT for Broadcom PHY for %s (c45: %d, len: %d)\n",
		       ethdev->name, c45, len);
		return -1;
	}

	seq_len = len / (c45 ? 16 : 12);
	while (seq_len--) {
		devid = (c45) ? fdt32_to_cpu(*init_seq++) : MDIO_DEVAD_NONE;
		reg = fdt32_to_cpu(*init_seq++);
		mask = fdt32_to_cpu(*init_seq++);

		if (mask) {
			value = phy_read(oct_eth_info->phydev, devid, reg);
			if (value < 0) {
				printf("%s: Error reading from phy for %s at %d:%d\n",
				       __func__, ethdev->name, devid, reg);
				return -1;
			}
			debug("%s: Read: 0x%x, mask: 0x%x\n", __func__, value, mask);
			value &= mask;
			value |= fdt32_to_cpu(*init_seq++);
		} else {
			value = fdt32_to_cpu(*init_seq++);
		}
		debug("Broadcom init for %s addr: %d: dev: %d, reg: 0x%x, mask: 0x%x, value: 0x%x\n",
		      ethdev->name, oct_eth_info->phydev->addr, devid, reg,
		      mask, value);

		if (phy_write(oct_eth_info->phydev, devid, reg, value) < 0) {
			printf("%s: Error writing 0x%x to phy for %s at %d:%d\n",
			       __func__, value, ethdev->name, devid, reg);
			return -1;
		}
	}

	return 0;
}
#endif /* CONFIG_PHY_BROADCOM */

/**
 * @INTERNAL
 * Configures generic 802.3 C22 PHY
 *
 * @param ethdev - ethernet device to initialize PHY force
 *
 * @return 0 for success, error otherwise
 */
static int octeon_fdt_generic_8023_c22_config(const struct eth_device *ethdev)
{
	struct octeon_eth_info *oct_eth_info = ethdev->priv;
	int phy_node_offset = oct_eth_info->phy_node_offset;
	int len, seq_len;
	uint32_t *init_seq;
	uint8_t dev;
	uint16_t reg, mask, value;

	debug("%s(%s)\n", __func__, ethdev->name);

	/* Check for compatible Micrel PHY */
	if (fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "ethernet-phy-ieee802.3-c22"))
		return 0;

	/* It is possible for some PHYs to require special "clause 45"
	 * initialization sequences instead of the regular clause 22
	 * sequences.
	 */
	init_seq = (uint32_t *)fdt_getprop(gd->fdt_blob, phy_node_offset,
					   "c45-reg-init", &len);
	if (init_seq && len > 0) {
		if (len % 16 != 0) {
			printf("Invalid clause 45 init sequence in DT for generic Clause 22 PHY for %s\n",
			       ethdev->name);
			return -1;
		}
		seq_len = len / 16;
		while (seq_len--) {
			dev = fdt32_to_cpu(*init_seq++);
			reg = fdt32_to_cpu(*init_seq++);
			mask = fdt32_to_cpu(*init_seq++);
			if (!mask) {
				value = fdt32_to_cpu(*init_seq++);
			} else {
				value = phy_read(oct_eth_info->phydev, dev, reg);
				value &= mask;
				value |= fdt32_to_cpu(*init_seq++);
			}
			debug("C45 init for %s addr: 0x%x, dev: 0x%x, reg: 0x%x, mask: 0x%x, value: 0x%x\n",
			     ethdev->name, oct_eth_info->phydev->addr, dev,
			     reg, mask, value);
			phy_write(oct_eth_info->phydev, dev, reg, value);
		}
	}

	/* Look for clause 22 init sequence */
	init_seq = (uint32_t *)fdt_getprop(gd->fdt_blob, phy_node_offset,
					   "reg-init", &len);
	if (!init_seq)
		return 0;

	if (len % 12 != 0) {
		printf("Invalid init sequence in DT for generic 802.3 PHY for %s\n",
		       ethdev->name);
		return -1;
	}

	seq_len = len / 12;
	while (seq_len--) {
		reg = fdt32_to_cpu(*init_seq++);
		mask = fdt32_to_cpu(*init_seq++);
		if (mask) {
			value = phy_read(oct_eth_info->phydev, MDIO_DEVAD_NONE,
					 reg);
			value &= mask;
			value |= fdt32_to_cpu(*init_seq++);
		} else {
			value = fdt32_to_cpu(*init_seq++);
		}
		debug("Generic PHY init for %s addr: %d, reg: %d, mask: 0x%x, value: 0x%x\n",
		      ethdev->name, oct_eth_info->phydev->addr, reg, mask, value);
	}

	return 0;
}

#if defined(CONFIG_PHY_TI) && defined(CONFIG_PHYLIB_10G)
/**
 * @INTERNAL
 * Configures a TI PHY based on the device tree
 *
 * @param ethdev - ethernet device PHY is attached to
 *
 * @return 0 for success, error otherwise
 */
static int octeon_fdt_ti_config(const struct eth_device *ethdev)
{
	uint16_t value;
	struct octeon_eth_info *oct_eth_info = ethdev->priv;
	struct phy_device *phydev = oct_eth_info->phydev;
	int phy_node_offset = oct_eth_info->phy_node_offset;

	debug("%s(%s)\n", __func__, ethdev->name);

	/* Check for at least one compatible TI PHY */
	if (fdt_node_check_compatible(gd->fdt_blob, phy_node_offset,
				      "ti,tlk10232")) {
		printf("%s: Warning: unknown TI PHY for %s\n",
		       __func__, ethdev->name);
		return 0;
	}

#define	CHANNEL_CONTROL_1 0x1e, 0x0001
	value =  phy_read(phydev, CHANNEL_CONTROL_1);
	value |= 1; /* REFCLK_1_P/N as clock */
	phy_write(phydev, CHANNEL_CONTROL_1, value);

#define HS_CH_CONTROL_1 0x1e, 0x001d
	value =  phy_read(phydev, HS_CH_CONTROL_1);
	value |= 0x1000; /* REFCLK = 312.5MHz */
	phy_write(phydev, HS_CH_CONTROL_1, value);

#define AN_CONTROL 0x07, 0x0000
	value =  phy_read(phydev, AN_CONTROL);
	value &= 0xefff; /* disable autonegotiation */
	phy_write(phydev, AN_CONTROL, value);

#define LT_TRAIN_CONTROL 0x01, 0x0096
	value =  phy_read(phydev, LT_TRAIN_CONTROL);
	value &= 0xfffd; /* turn off LT_TRAINING_ENABLE */
	phy_write(phydev, LT_TRAIN_CONTROL, value);

#define TI_RESERVED_20 0x1e, 0x8020
	value = 3; /* Magic */
	phy_write(phydev, TI_RESERVED_20, value);

#define RESET_CONTROL 0x1e, 0x000e
	value =  phy_read(phydev, RESET_CONTROL);
	value |= 8; /* Reset channel */
	phy_write(phydev, RESET_CONTROL, value);

	return 0;
}
#endif

#ifdef CONFIG_PHY_VITESSE
static const uint8_t vitesse_qsgmii_vsc8574_program[] = {
	0x44, 0x83, 0x02, 0x42, 0x12, 0x02, 0x44, 0x93, 0x02, 0x44,
	0xca, 0x02, 0x44, 0x4d, 0x02, 0x43, 0xef, 0xed, 0xff, 0xe5,
	0xfc, 0x54, 0x38, 0x64, 0x20, 0x70, 0x08, 0x65, 0xff, 0x70,
	0x04, 0xed, 0x44, 0x80, 0xff, 0x22, 0x8f, 0x19, 0x7b, 0xbb,
	0x7d, 0x0e, 0x7f, 0x04, 0x12, 0x3d, 0xd7, 0xef, 0x4e, 0x60,
	0x03, 0x02, 0x41, 0xf9, 0xe4, 0xf5, 0x1a, 0x74, 0x01, 0x7e,
	0x00, 0xa8, 0x1a, 0x08, 0x80, 0x05, 0xc3, 0x33, 0xce, 0x33,
	0xce, 0xd8, 0xf9, 0xff, 0xef, 0x55, 0x19, 0x70, 0x03, 0x02,
	0x41, 0xed, 0x85, 0x1a, 0xfb, 0x7b, 0xbb, 0xe4, 0xfd, 0xff,
	0x12, 0x3d, 0xd7, 0xef, 0x4e, 0x60, 0x03, 0x02, 0x41, 0xed,
	0xe5, 0x1a, 0x54, 0x02, 0x75, 0x1d, 0x00, 0x25, 0xe0, 0x25,
	0xe0, 0xf5, 0x1c, 0xe4, 0x78, 0xc5, 0xf6, 0xd2, 0x02, 0x12,
	0x41, 0xfa, 0x7b, 0xff, 0x7d, 0x12, 0x7f, 0x07, 0x12, 0x3d,
	0xd7, 0xef, 0x4e, 0x60, 0x03, 0x02, 0x41, 0xe7, 0xc2, 0x02,
	0x74, 0xc7, 0x25, 0x1a, 0xf9, 0x74, 0xe7, 0x25, 0x1a, 0xf8,
	0xe6, 0x27, 0xf5, 0x1b, 0xe5, 0x1d, 0x24, 0x5b, 0x12, 0x44,
	0x2a, 0x12, 0x3e, 0xda, 0x7b, 0xfc, 0x7d, 0x11, 0x7f, 0x07,
	0x12, 0x3d, 0xd7, 0x78, 0xcc, 0xef, 0xf6, 0x78, 0xc1, 0xe6,
	0xfe, 0xef, 0xd3, 0x9e, 0x40, 0x06, 0x78, 0xcc, 0xe6, 0x78,
	0xc1, 0xf6, 0x12, 0x41, 0xfa, 0x7b, 0xec, 0x7d, 0x12, 0x7f,
	0x07, 0x12, 0x3d, 0xd7, 0x78, 0xcb, 0xef, 0xf6, 0xbf, 0x07,
	0x06, 0x78, 0xc3, 0x76, 0x1a, 0x80, 0x1f, 0x78, 0xc5, 0xe6,
	0xff, 0x60, 0x0f, 0xc3, 0xe5, 0x1b, 0x9f, 0xff, 0x78, 0xcb,
	0xe6, 0x85, 0x1b, 0xf0, 0xa4, 0x2f, 0x80, 0x07, 0x78, 0xcb,
	0xe6, 0x85, 0x1b, 0xf0, 0xa4, 0x78, 0xc3, 0xf6, 0xe4, 0x78,
	0xc2, 0xf6, 0x78, 0xc2, 0xe6, 0xff, 0xc3, 0x08, 0x96, 0x40,
	0x03, 0x02, 0x41, 0xd1, 0xef, 0x54, 0x03, 0x60, 0x33, 0x14,
	0x60, 0x46, 0x24, 0xfe, 0x60, 0x42, 0x04, 0x70, 0x4b, 0xef,
	0x24, 0x02, 0xff, 0xe4, 0x33, 0xfe, 0xef, 0x78, 0x02, 0xce,
	0xa2, 0xe7, 0x13, 0xce, 0x13, 0xd8, 0xf8, 0xff, 0xe5, 0x1d,
	0x24, 0x5c, 0xcd, 0xe5, 0x1c, 0x34, 0xf0, 0xcd, 0x2f, 0xff,
	0xed, 0x3e, 0xfe, 0x12, 0x44, 0x6a, 0x7d, 0x11, 0x80, 0x0b,
	0x78, 0xc2, 0xe6, 0x70, 0x04, 0x7d, 0x11, 0x80, 0x02, 0x7d,
	0x12, 0x7f, 0x07, 0x12, 0x3e, 0x9a, 0x8e, 0x1e, 0x8f, 0x1f,
	0x80, 0x03, 0xe5, 0x1e, 0xff, 0x78, 0xc5, 0xe6, 0x06, 0x24,
	0xcd, 0xf8, 0xa6, 0x07, 0x78, 0xc2, 0x06, 0xe6, 0xb4, 0x1a,
	0x0a, 0xe5, 0x1d, 0x24, 0x5c, 0x12, 0x44, 0x2a, 0x12, 0x3e,
	0xda, 0x78, 0xc5, 0xe6, 0x65, 0x1b, 0x70, 0x82, 0x75, 0xdb,
	0x20, 0x75, 0xdb, 0x28, 0x12, 0x44, 0x42, 0x12, 0x44, 0x42,
	0xe5, 0x1a, 0x12, 0x44, 0x35, 0xe5, 0x1a, 0xc3, 0x13, 0x12,
	0x44, 0x35, 0x78, 0xc5, 0x16, 0xe6, 0x24, 0xcd, 0xf8, 0xe6,
	0xff, 0x7e, 0x08, 0x1e, 0xef, 0xa8, 0x06, 0x08, 0x80, 0x02,
	0xc3, 0x13, 0xd8, 0xfc, 0xfd, 0xc4, 0x33, 0x54, 0xe0, 0xf5,
	0xdb, 0xef, 0xa8, 0x06, 0x08, 0x80, 0x02, 0xc3, 0x13, 0xd8,
	0xfc, 0xfd, 0xc4, 0x33, 0x54, 0xe0, 0x44, 0x08, 0xf5, 0xdb,
	0xee, 0x70, 0xd8, 0x78, 0xc5, 0xe6, 0x70, 0xc8, 0x75, 0xdb,
	0x10, 0x02, 0x40, 0xfd, 0x78, 0xc2, 0xe6, 0xc3, 0x94, 0x17,
	0x50, 0x0e, 0xe5, 0x1d, 0x24, 0x62, 0x12, 0x42, 0x08, 0xe5,
	0x1d, 0x24, 0x5c, 0x12, 0x42, 0x08, 0x20, 0x02, 0x03, 0x02,
	0x40, 0x76, 0x05, 0x1a, 0xe5, 0x1a, 0xc3, 0x94, 0x04, 0x50,
	0x03, 0x02, 0x40, 0x3a, 0x22, 0xe5, 0x1d, 0x24, 0x5c, 0xff,
	0xe5, 0x1c, 0x34, 0xf0, 0xfe, 0x12, 0x44, 0x6a, 0x22, 0xff,
	0xe5, 0x1c, 0x34, 0xf0, 0xfe, 0x12, 0x44, 0x6a, 0x22, 0xd2,
	0x00, 0x75, 0xfb, 0x03, 0xab, 0x7e, 0xaa, 0x7d, 0x7d, 0x19,
	0x7f, 0x03, 0x12, 0x3e, 0xda, 0xe5, 0x7e, 0x54, 0x0f, 0x24,
	0xf3, 0x60, 0x03, 0x02, 0x42, 0xb9, 0x12, 0x44, 0xa3, 0x12,
	0x44, 0xaa, 0xd8, 0xfb, 0xff, 0x20, 0xe2, 0x2a, 0x13, 0x92,
	0x04, 0xef, 0xa2, 0xe1, 0x92, 0x03, 0x30, 0x04, 0x1f, 0xe4,
	0xf5, 0x10, 0xe5, 0x10, 0x24, 0x17, 0xfd, 0x7b, 0x54, 0x7f,
	0x04, 0x12, 0x3d, 0xd7, 0x74, 0x25, 0x25, 0x10, 0xf8, 0xa6,
	0x07, 0x05, 0x10, 0xe5, 0x10, 0xc3, 0x94, 0x02, 0x40, 0xe4,
	0x12, 0x44, 0xa3, 0x12, 0x44, 0xaa, 0xd8, 0xfb, 0x54, 0x05,
	0x64, 0x04, 0x70, 0x27, 0x78, 0xc4, 0xe6, 0x78, 0xc6, 0xf6,
	0xe5, 0x7d, 0xff, 0x33, 0x95, 0xe0, 0xef, 0x54, 0x0f, 0x78,
	0xc4, 0xf6, 0x12, 0x42, 0xcf, 0x20, 0x04, 0x0c, 0x12, 0x44,
	0xa3, 0x12, 0x44, 0xaa, 0xd8, 0xfb, 0x13, 0x92, 0x05, 0x22,
	0xc2, 0x05, 0x22, 0x12, 0x44, 0xa3, 0x12, 0x44, 0xaa, 0xd8,
	0xfb, 0x54, 0x05, 0x64, 0x05, 0x70, 0x1e, 0x78, 0xc4, 0x7d,
	0xb8, 0x12, 0x42, 0xc5, 0x78, 0xc1, 0x7d, 0x74, 0x12, 0x42,
	0xc5, 0xe4, 0x78, 0xc1, 0xf6, 0x22, 0x7b, 0x01, 0x7a, 0x00,
	0x7d, 0xee, 0x7f, 0x92, 0x12, 0x38, 0xbd, 0x22, 0xe6, 0xfb,
	0x7a, 0x00, 0x7f, 0x92, 0x12, 0x38, 0xbd, 0x22, 0x78, 0xc1,
	0xe6, 0xfb, 0x7a, 0x00, 0x7d, 0x74, 0x7f, 0x92, 0x12, 0x38,
	0xbd, 0xe4, 0x78, 0xc1, 0xf6, 0xf5, 0x11, 0x74, 0x01, 0x7e,
	0x00, 0xa8, 0x11, 0x08, 0x80, 0x05, 0xc3, 0x33, 0xce, 0x33,
	0xce, 0xd8, 0xf9, 0xff, 0x78, 0xc4, 0xe6, 0xfd, 0xef, 0x5d,
	0x60, 0x44, 0x85, 0x11, 0xfb, 0xe5, 0x11, 0x54, 0x02, 0x25,
	0xe0, 0x25, 0xe0, 0xfe, 0xe4, 0x24, 0x5b, 0xfb, 0xee, 0x12,
	0x44, 0x2d, 0x12, 0x3e, 0xda, 0x7b, 0x40, 0x7d, 0x11, 0x7f,
	0x07, 0x12, 0x3d, 0xd7, 0x74, 0xc7, 0x25, 0x11, 0xf8, 0xa6,
	0x07, 0x7b, 0x11, 0x7d, 0x12, 0x7f, 0x07, 0x12, 0x3d, 0xd7,
	0xef, 0x4e, 0x60, 0x09, 0x74, 0xe7, 0x25, 0x11, 0xf8, 0x76,
	0x04, 0x80, 0x07, 0x74, 0xe7, 0x25, 0x11, 0xf8, 0x76, 0x0a,
	0x05, 0x11, 0xe5, 0x11, 0xc3, 0x94, 0x04, 0x40, 0x9a, 0x78,
	0xc6, 0xe6, 0x70, 0x15, 0x78, 0xc4, 0xe6, 0x60, 0x10, 0x75,
	0xd9, 0x38, 0x75, 0xdb, 0x10, 0x7d, 0xfe, 0x12, 0x43, 0x7d,
	0x7d, 0x76, 0x12, 0x43, 0x7d, 0x79, 0xc6, 0xe7, 0x78, 0xc4,
	0x66, 0xff, 0x60, 0x03, 0x12, 0x40, 0x25, 0x78, 0xc4, 0xe6,
	0x70, 0x09, 0xfb, 0xfa, 0x7d, 0xfe, 0x7f, 0x8e, 0x12, 0x38,
	0xbd, 0x22, 0x7b, 0x01, 0x7a, 0x00, 0x7f, 0x8e, 0x12, 0x38,
	0xbd, 0x22, 0xe4, 0xf5, 0x19, 0x74, 0x25, 0x25, 0x19, 0xf8,
	0xe6, 0x64, 0x03, 0x60, 0x51, 0xe5, 0x19, 0x24, 0x17, 0xfd,
	0x7b, 0xeb, 0x7f, 0x04, 0x12, 0x3d, 0xd7, 0x8f, 0xfb, 0x7b,
	0x22, 0x7d, 0x18, 0x7f, 0x06, 0x12, 0x3d, 0xd7, 0xef, 0x64,
	0x01, 0x4e, 0x60, 0x1c, 0x7d, 0x1c, 0xe4, 0xff, 0x12, 0x3e,
	0x9a, 0xef, 0x54, 0x1b, 0x64, 0x0a, 0x70, 0x15, 0x7b, 0xcc,
	0x7d, 0x10, 0xff, 0x12, 0x3d, 0xd7, 0xef, 0x64, 0x01, 0x4e,
	0x70, 0x07, 0x12, 0x44, 0xb1, 0x7b, 0x03, 0x80, 0x0a, 0x12,
	0x44, 0xb1, 0x74, 0x25, 0x25, 0x19, 0xf8, 0xe6, 0xfb, 0x7a,
	0x00, 0x7d, 0x54, 0x12, 0x38, 0xbd, 0x05, 0x19, 0xe5, 0x19,
	0xc3, 0x94, 0x02, 0x40, 0x9c, 0x22, 0xe5, 0x7e, 0x30, 0xe5,
	0x35, 0x30, 0xe4, 0x0b, 0x7b, 0x02, 0x7d, 0x33, 0x7f, 0x35,
	0x12, 0x36, 0x29, 0x80, 0x10, 0x7b, 0x01, 0x7d, 0x33, 0x7f,
	0x35, 0x12, 0x36, 0x29, 0x90, 0x47, 0xd2, 0xe0, 0x44, 0x04,
	0xf0, 0x90, 0x47, 0xd2, 0xe0, 0x54, 0xf7, 0xf0, 0x90, 0x47,
	0xd1, 0xe0, 0x44, 0x10, 0xf0, 0x7b, 0x05, 0x7d, 0x84, 0x7f,
	0x86, 0x12, 0x36, 0x29, 0x22, 0xfb, 0xe5, 0x1c, 0x34, 0xf0,
	0xfa, 0x7d, 0x10, 0x7f, 0x07, 0x22, 0x54, 0x01, 0xc4, 0x33,
	0x54, 0xe0, 0xf5, 0xdb, 0x44, 0x08, 0xf5, 0xdb, 0x22, 0xf5,
	0xdb, 0x75, 0xdb, 0x08, 0xf5, 0xdb, 0x75, 0xdb, 0x08, 0x22,
	0xe5, 0x7e, 0x54, 0x0f, 0x64, 0x01, 0x70, 0x0d, 0xe5, 0x7e,
	0x30, 0xe4, 0x08, 0x90, 0x47, 0xd0, 0xe0, 0x44, 0x02, 0xf0,
	0x22, 0x90, 0x47, 0xd0, 0xe0, 0x54, 0xfd, 0xf0, 0x22, 0xab,
	0x07, 0xaa, 0x06, 0x7d, 0x10, 0x7f, 0x07, 0x12, 0x3e, 0xda,
	0x7b, 0xff, 0x7d, 0x10, 0x7f, 0x07, 0x12, 0x3d, 0xd7, 0xef,
	0x4e, 0x60, 0xf3, 0x22, 0x12, 0x44, 0xc5, 0x12, 0x44, 0xbb,
	0x90, 0x47, 0xfa, 0xe0, 0x54, 0xf8, 0x44, 0x02, 0xf0, 0x22,
	0x30, 0x04, 0x03, 0x12, 0x43, 0x87, 0x78, 0xc4, 0xe6, 0xff,
	0x60, 0x03, 0x12, 0x40, 0x25, 0x22, 0xe5, 0x7e, 0xae, 0x7d,
	0x78, 0x04, 0x22, 0xce, 0xa2, 0xe7, 0x13, 0xce, 0x13, 0x22,
	0xe5, 0x19, 0x24, 0x17, 0x54, 0x1f, 0x44, 0x80, 0xff, 0x22,
	0xe4, 0x78, 0xc4, 0xf6, 0xc2, 0x05, 0x78, 0xc1, 0xf6, 0x22,
	0xc2, 0x04, 0xc2, 0x03, 0x22, 0x22
};
static const uint16_t vsc8574_program_crc = 0xb7c2;

/**
 * Maps GPIO lines to the global GPIO config registers.
 *
 * Please see the data sheet since the configuration for each GPIO line is
 * different.
 */
static const struct {
	uint32_t config1_status_reg;
	uint32_t config2_reg;
} vcs848x_gpio_to_reg[12] = {
	{ 0x1e0100, 0x1e0101 },	/* 0 */
	{ 0x1e0102, 0x1e0103 },	/* 1 */
	{ 0x1e0104, 0x1e0105 },	/* 2 */
	{ 0x1e0106, 0x1e0107 },	/* 3 */
	{ 0x1e0108, 0x1e0109 },	/* 4 */
	{ 0x1e010A, 0x1e010B },	/* 5 */
	{ 0x1e0124, 0x1e0125 },	/* 6 */
	{ 0x1e0126, 0x1e0127 },	/* 7 */
	{ 0x1e0128, 0x1e0129 },	/* 8 */
	{ 0x1e012a, 0x1e012b },	/* 9 */
	{ 0x1e012c, 0x1e012d },	/* 10 */
	{ 0x1e012e, 0x1e012f },	/* 11 */
};

static int octeon_vitesse_vsc8574_load_fw(const struct eth_device *ethdev)
{
	struct octeon_eth_info *oct_eth_info = ethdev->priv;
	struct phy_device *phydev = oct_eth_info->phydev;
	u16 val;
	int i;
	ulong start;

	debug("%s(%s): Loading VSC8574 firmware\n", __func__, ethdev->name);
	phy_write(phydev, MDIO_DEVAD_NONE, 31, 0x0010);	/* GPIO space */
	phy_write(phydev, MDIO_DEVAD_NONE, 18, 0x800f);	/* uP command */
	phy_write(phydev, MDIO_DEVAD_NONE, 31, 0x0010);	/* GPIO space */
	start = get_timer(0);
	do {
		val = phy_read(phydev, MDIO_DEVAD_NONE, 18);
		if (!(val & (1 << 15)))
			break;

		mdelay(10);
	} while (get_timer(start) < 1000);		/* Wait for command completion */
	if (val & (1 << 15)) {
		printf("%s: Timeout 1\n", __func__);
		return -1;
	}

	phy_write(phydev, MDIO_DEVAD_NONE, 31, 0);	/* Main register space */
	phy_write(phydev, MDIO_DEVAD_NONE, 31, 0x0010);	/* GPIO space */
	val = phy_read(phydev, MDIO_DEVAD_NONE, 12);
	val &= 0x0800;;
	phy_write(phydev, MDIO_DEVAD_NONE, 12, val);
	phy_write(phydev, MDIO_DEVAD_NONE, 9, 0x005b);
	phy_write(phydev, MDIO_DEVAD_NONE, 10, 0x005b);
	val = phy_read(phydev, MDIO_DEVAD_NONE, 12);
	val &= 0x0800;
	phy_write(phydev, MDIO_DEVAD_NONE, 12, val);
	phy_write(phydev, MDIO_DEVAD_NONE, 18, 0x800f);
	val = phy_read(phydev, MDIO_DEVAD_NONE, 0);
	val &= 0x0800;
	phy_write(phydev, MDIO_DEVAD_NONE, 0, val);
	phy_write(phydev, MDIO_DEVAD_NONE, 18, 0x0);
	val = phy_read(phydev, MDIO_DEVAD_NONE, 12);
	val &= 0x0800;
	phy_write(phydev, MDIO_DEVAD_NONE, 12, val);
	phy_write(phydev, MDIO_DEVAD_NONE, 31, 0x0010);
	phy_write(phydev, MDIO_DEVAD_NONE, 0, 0x7009);
	phy_write(phydev, MDIO_DEVAD_NONE, 12, 0x5002);
	phy_write(phydev, MDIO_DEVAD_NONE, 11, 0x0000);

	for (i = 0; i < sizeof(vitesse_qsgmii_vsc8574_program); i++)
	      phy_write(phydev, MDIO_DEVAD_NONE, 12,
			0x5000 | vitesse_qsgmii_vsc8574_program[i]);

	phy_write(phydev, MDIO_DEVAD_NONE, 12,  0x0000);
	phy_write(phydev, MDIO_DEVAD_NONE, 3, 0x3eb7);
	phy_write(phydev, MDIO_DEVAD_NONE, 4, 0x4012);
	phy_write(phydev, MDIO_DEVAD_NONE, 12, 0x0100);
	phy_write(phydev, MDIO_DEVAD_NONE, 0, 0x4018);
	phy_write(phydev, MDIO_DEVAD_NONE, 0, 0xC018);

	phy_write(phydev, MDIO_DEVAD_NONE, 31, 0x0001);
	phy_write(phydev, MDIO_DEVAD_NONE, 25, 0x4000);
	phy_write(phydev, MDIO_DEVAD_NONE, 26,
		  sizeof(vitesse_qsgmii_vsc8574_program)+1);
	phy_write(phydev, MDIO_DEVAD_NONE, 31, 0x0010);
	phy_write(phydev, MDIO_DEVAD_NONE, 18, 0x8008);

	start = get_timer(0);
	do {
		val = phy_read(phydev, MDIO_DEVAD_NONE, 18);
		if (!(val & (1 << 15)))
			break;
		mdelay(10);
	} while (get_timer(start) < 1000);
	if (val & (1 << 15)) {
		printf("%s: Timeout 2\n", __func__);
		return -1;
	}
	phy_write(phydev, MDIO_DEVAD_NONE, 31, 0x0001);
	val = phy_read(phydev, MDIO_DEVAD_NONE, 25);
	if (val != vsc8574_program_crc) {
		printf("Calculated CRC is 0x%x, expected CRC is 0x%x\n",
		       val, vsc8574_program_crc);
		return -1;
	}
	phy_write(phydev, MDIO_DEVAD_NONE, 31, 0);
	return 0;
}

/**
 * This function is called before and after all of the PHY initialization
 * to control the Vitesse COMA mode.
 */
int __octeon_vitesse_coma(bool start)
{
	int i, gpio, val;
	debug("%s: Entry\n", __func__);
	for (i = 0; i < num_coma_gpios; i++) {
		gpio = coma_gpios[i].pin;
		val = coma_gpios[i].invert ^ !!start;
		debug("%s: Setting GPIO %d to %d\n", __func__, gpio, val);

		switch (coma_gpios[i].type) {
		case CVMX_GPIO_PIN_OCTEON:
			debug("Setting OCTEON GPIO coma pin %d to %d\n",
			      gpio, val);
			gpio_set_value(gpio, val);
			break;
#ifdef CONFIG_PCA953X
		case CVMX_GPIO_PIN_PCA953X:
			debug("Setting PCA953X at 0x%x:0x%x GPIO coma pin %d to %d\n",
			      coma_gpios[i].i2c_bus, coma_gpios[i].i2c_addr,
			      gpio, val);
			pca953x_set_val(coma_gpios[i].i2c_bus,
					coma_gpios[i].i2c_addr,
					1 << gpio,
					val << gpio);
			break;
#endif
#ifdef CONFIG_PCF857X
		case CVMX_GPIO_PIN_PCF857X:
			debug("Setting PCF857X at 0x%x:0x%x GPIO coma pin %d to %d\n",
			      coma_gpios[i].i2c_bus, coma_gpios[i].i2c_addr,
			      gpio, val);
			pcf857x_set_val(coma_gpios[i].i2c_bus,
					coma_gpios[i].i2c_addr,
					1 << gpio,
					val << gpio);
			break;
#endif
		default:
			printf("%s: Unsupported GPIO type for GPIO pin %d\n",
			       __func__, gpio);
			return -1;
		}
	}
	return 0;
}

int octeon_vitesse_coma(bool start)
		__attribute__((weak, alias("__octeon_vitesse_coma")));

static int octeon_fdt_vitesse_vsc8574_config(const struct eth_device *ethdev)
{
	const struct octeon_eth_info *oct_eth_info =
				 (struct octeon_eth_info *)ethdev->priv;
	struct phy_device *phydev = oct_eth_info->phydev;
	int phy_node_offset;
	int rc = 0;
	const uint32_t *pgpio_handle;
	int gpio;
	enum cvmx_gpio_type gpio_type;
	int invert;
	int len;
	int phandle;
	int value;
	const char *media_type;
	ulong start;
	enum vsc8574_media_mode media_mode = MM_COPPER;

	phy_node_offset = oct_eth_info->phy_node_offset;
	if (phy_node_offset < 0) {
		printf("%s: Error: could not find phy info for phy device\n",
		       __func__);
		return -1;
	}

	/* For the first PHY follow the configuration steps outlined in
	 * the data sheet configuration section 2.21.
	 */
	pgpio_handle = fdt_getprop(gd->fdt_blob, phy_node_offset, "coma", &len);
	if (pgpio_handle) {

		if (len != 12) {
			printf("Invalid coma property length for %s\n",
			       ethdev->name);
			return -1;
		}
		phandle = fdt32_to_cpu(pgpio_handle[0]);
		gpio = fdt32_to_cpu(pgpio_handle[1]);
		invert = fdt32_to_cpu(pgpio_handle[2]);

		gpio_type = cvmx_fdt_get_gpio_type(gd->fdt_blob, phandle, NULL);
		if (gpio_type != CVMX_GPIO_PIN_OCTEON) {
			int bus, addr;

			if (cvmx_fdt_get_twsi_gpio_bus_addr(gd->fdt_blob,
							    phandle, &bus,
							    &addr)) {
				printf("%s: Error: could not get i2c bus and address for i2c GPIO COMA for %s\n",
				       __func__, ethdev->name);
			goto no_coma;
		}
			coma_gpios[num_coma_gpios].i2c_addr = addr;
			coma_gpios[num_coma_gpios].i2c_bus = bus;
			debug("%s: I2C coma pin for %s connected to I2C GPIO expander @ 0x%x:0x%x\n",
			      __func__, ethdev->name, bus, addr);
		}
		coma_gpios[num_coma_gpios].type = gpio_type;
		coma_gpios[num_coma_gpios].pin = gpio & COMA_GPIO_MASK;
		coma_gpios[num_coma_gpios].invert = !!invert;
		debug("%s: Added coma GPIO %d to index %d for %s\n", __func__, gpio,
		      num_coma_gpios, ethdev->name);

		num_coma_gpios++;

		if (num_coma_gpios >= MAX_COMA_GPIOS) {
			num_coma_gpios--;
			printf("ERROR: Maximum number of COMA GPIO lines (%d) exceeded\n",
			       MAX_COMA_GPIOS);
			rc = -1;
		}

		/* 1. COMA_MODE active, drive high (hopefully this is done
		 * earlier
		 */
		debug("Setting GPIO %d to %d for %s\n", gpio, !invert,
		      ethdev->name);
		gpio_set_value(gpio, !invert);
	}
no_coma:
	/* 2. Apply Power (hopefully done elsewhere)
	 * 3. Apply RefClk
	 * 4. Release reset, drive high. Power and clock must be stable before
	 *    releasing reset.
	 * 5. Wait 120ms minimum.
	 *
	 * 6. Apply patch from PHY_API (required for production released (sic)
	 *    optional for board testing).
	 */
	if ((phydev->addr & 3) == 0) {
		debug("%s(%s): Loading firmware\n", __func__,
		      ethdev->name);
		/* 6. Apply patch from PHY_API (required for production) */
		rc = octeon_vitesse_vsc8574_load_fw(ethdev);
		if (rc) {
			printf("%s: Error loading firmware for %s\n",
			       __func__, ethdev->name);
			return -1;
		}

		/* 7. Configure register 19G for MAC mode (to access register
		 *    19G, register 31 must be 0x10).  Read register 19G.  Set
		 *    bits 15:14, MAC configuration as follows:
		 *    00: SGMII
		 *    01: QSGMII
		 *    10: Reserved
		 *    11: Reserved
		 *    Write new register 19G.
		 */
		/* Access CPU/GPIO registers */
		if ((rc = phy_write(phydev, MDIO_DEVAD_NONE, 0x1f, 0x10)))
			goto phy_err;
		value = phy_read(phydev, MDIO_DEVAD_NONE, 19);
		if (value < 0) {
			rc = value;
			goto phy_err;
		}

		value = value & 0x3fff;
		if (phydev->interface == PHY_INTERFACE_MODE_QSGMII)
			value |= 0x4000;
		/* else SGMII */
		if ((rc = phy_write(phydev, MDIO_DEVAD_NONE, 19, value)))
			goto phy_err;

		/* 8. Configure register 18G for MAC on all 4 PHYs write:
		 *    SGMII: 0x80F0
		 *    QSGMII: 0x80e0
		 *    Read register 18G until bit 15 equals 0
		 */
		value = (phydev->interface == PHY_INTERFACE_MODE_QSGMII) ?
			0x80E0 : 0x80F0;
		if ((rc = phy_write(phydev, MDIO_DEVAD_NONE, 18, value)))
			goto phy_err;

		start = get_timer(0);
		do {
			value = phy_read(phydev, MDIO_DEVAD_NONE, 18);
			if (value < 0)
				goto phy_err;
		} while ((value & 0x8000) && get_timer(start) < 1000);
		if (value & 0x8000) {
			printf("Timed out waiting for MAC mode configuration for %s\n",
			       ethdev->name);
			goto phy_err;
		}
		/* 9. If Fiber Media on all 4 PHYs configure register 18G by
		 *    writing:
		 *    Media 1000BX: 0x8FC1
		 *    Media 100FX: 0x8FD1
		 */
		media_type = fdt_getprop(gd->fdt_blob, phy_node_offset,
					 "optical-media-type", NULL);
		if (media_type) {
			/* Optical media attached */
			if (!strcmp(media_type, "1000bx")) {
				media_mode = MM_1000BX;
				value = 0x8fc1;
			} else if (!strcmp(media_type, "100fx")) {
				media_mode = MM_100FX;
				value = 0x8fd1;
			} else {
				printf("Unknown optical media type %s for phy %s\n",
				       media_type, ethdev->name);
				goto phy_err;
			}
			if ((rc = phy_write(phydev, MDIO_DEVAD_NONE, 18, value)))
				goto phy_err;

			/* 10. If Fiber Media read register 18G till (SIC) bit 15
			 * equals 0.
			 */
			start = get_timer(0);
			do {
				value = phy_read(phydev, MDIO_DEVAD_NONE, 18);
				if (value < 0)
					goto phy_err;
			} while ((value & 0x8000) && get_timer(start) < 1000);
			if (value & 0x8000) {
				printf("Timed out waiting for PHY optical configuration for %s\n",
				       ethdev->name);
				goto phy_err;
			}
		}

		/* 11. Configure register 23 for MAC and Media mode (to access
		 *     register 23, register 31 must be 0). Read register 23.
		 *     Set bits 10:8 as follows:
		 *     000: Copper
		 *     010: 1000BX
		 *     011: 100FX
		 *     Write new register 23.
		 */
		if ((rc = phy_write(phydev, MDIO_DEVAD_NONE, 31, 0)))
			goto phy_err;

		value = phy_read(phydev, MDIO_DEVAD_NONE, 23);
		if (value < 0)
			goto phy_err;
		value &= 0xf8ff;
		if (media_mode == MM_1000BX)
			value |= 0x0200;
		else if (media_mode == MM_100FX)
			value |= 0x0300;
		if ((rc = phy_write(phydev, MDIO_DEVAD_NONE, 23, value)))
			goto phy_err;
	}

	/* 12. Software reset. Read register 0 (to access register 0,
	 *     register 31 must be 0). Set bit 15 to 1.
	 *     Write new register 0.
	 */
	if ((rc = phy_write(phydev, MDIO_DEVAD_NONE, 31, 0)))
		goto phy_err;

	value = phy_read(phydev, MDIO_DEVAD_NONE, 0);
	if (value < 0)
		goto phy_err;
	value |= 0x8000;
	if ((rc = phy_write(phydev, MDIO_DEVAD_NONE, 0, value)))
		goto phy_err;

	start = get_timer(0);
	do {
		value = phy_read(phydev, MDIO_DEVAD_NONE, 0);
		if (value < 0)
			goto phy_err;
	} while ((value & 0x8000) && get_timer(start) < 1000);

phy_err:
	if (rc) {
		printf("%s: PHY I/O error accessing PHY for %s\n",
		       __func__, ethdev->name);
	}

	return rc;
}

/**
 * This performs initialization for the Vitesse VSC866x PHY using a number
 * of fields in the device tree.  The default values are chosen to work
 * with the NIC401NVG board.
 *
 * @param[in]	phydev	PHY device
 * @param	offset	Offset of node in device tree
 *
 * @return 0 for success, -1 for error
 */
static int octeon_vitesse_vsc866x_init(const struct eth_device *ethdev,
				       int offset)
{
	const struct octeon_eth_info *oct_eth_info =
				 (struct octeon_eth_info *)ethdev->priv;
	struct phy_device *phydev = oct_eth_info->phydev;
	int cmode_mac_an;
	int cmode_mode;
	int cmode_sigdet_polarity;
	int cmode_mac_mode;
	int serdes_mac_loopback_mode;
	int serdes_media_loopback_mode;
	int led_mode = 0x403;
	int led_behavior = 0x8002;
	int tx_en_gpio;
	const void *fdt = gd->fdt_blob;
	int rc;
	int val;

	debug("%s(%s) ENTRY\n", __func__, ethdev->name);

	cmode_mode = fdtdec_get_int(fdt, offset, "cmode-mode", 2);
	debug("%s(%s) cmode mode: %d\n", __func__, ethdev->name,
	      cmode_mode);

	cmode_sigdet_polarity = fdtdec_get_int(fdt, offset,
					       "cmode-sigdet-polarity", 1);
	debug("%s(%s) cmode sigdet polarity: %d\n", __func__, ethdev->name,
	      cmode_sigdet_polarity);

	cmode_mac_mode = fdtdec_get_int(fdt, offset, "cmode-mac-mode", 1);
	debug("%s(%s) cmode mac mode: %d\n", __func__, ethdev->name,
	      cmode_mac_mode);

	cmode_mac_an = fdtdec_get_int(fdt, offset, "cmode-mac-an", 0);
	debug("%s(%s) cmode mac autonegotiation: %d\n",
	      __func__, ethdev->name, cmode_mac_an);

	serdes_mac_loopback_mode = fdtdec_get_int(fdt, offset,
						  "serdes-mac-loopback-mode", 3);
	debug("%s(%s) serdes mac loopback mode: %d\n", __func__, ethdev->name,
	      serdes_mac_loopback_mode);

	serdes_media_loopback_mode = fdtdec_get_int(fdt, offset,
						    "serdes-media-loopback-mode",
						    3);
	debug("%s(%s) serdes media loopback mode: %d\n", __func__, ethdev->name,
	      serdes_media_loopback_mode);

	led_mode = fdtdec_get_int(fdt, offset, "led-mode", 0x403);
	debug("%s(%s) LED mode: 0x%x\n", __func__, ethdev->name, led_mode);

	led_behavior = fdtdec_get_int(fdt, offset, "led-behavior", 0x8002);
	debug("%s(%s) LED behavior: 0x%x\n", __func__, ethdev->name,
	      led_behavior);

	tx_en_gpio = fdtdec_get_int(fdt, offset, "tx-enable-gpio", -1);
	debug("%s(%s) TX enable GPIO: %d\n", __func__, ethdev->name,
	      tx_en_gpio);

	/* Configure the LEDs */
	rc = phy_write(phydev, MDIO_DEVAD_NONE, 0x1f, 0);
	if (rc < 0)
		goto error;

	rc = phy_write(phydev, MDIO_DEVAD_NONE, 0x1e, led_mode);
	if (rc < 0)
		goto error;
	debug(" 0x001e = 0x%x\n", phy_read(phydev, MDIO_DEVAD_NONE, 0x1e));

	rc = phy_write(phydev, MDIO_DEVAD_NONE, 0x1d, led_behavior);
	if (rc < 0)
		goto error;
	debug(" 0x001d = 0x%x\n", phy_read(phydev, MDIO_DEVAD_NONE, 0x1d));

	/* Enable TX */
	if (tx_en_gpio >= 0) {
		debug("  Clearing tx enable GPIO %d\n", tx_en_gpio);
		rc = phy_write(phydev, MDIO_DEVAD_NONE, 0x1f, 0x10);
		if (rc < 0)
			goto error;

		val = phy_read(phydev, MDIO_DEVAD_NONE, 0x11);
		if (val < 0)
			goto error;
		val |= 1 << tx_en_gpio;
		debug("Setting gpio %d to output, reg: 0x%x\n", tx_en_gpio,
		      val);
		rc = phy_write(phydev, MDIO_DEVAD_NONE, 0x11, val);
		if (rc < 0)
			goto error;
		debug(" 0x0011 = 0x%x\n", phy_read(phydev, MDIO_DEVAD_NONE, 0x11));

		val = phy_read(phydev, MDIO_DEVAD_NONE, 0x10);
		if (val < 0)
			goto error;
		val &= ~(1 << tx_en_gpio);
		rc = phy_write(phydev, MDIO_DEVAD_NONE, 0x10, val);
		if (rc < 0)
			goto error;
		debug(" 0x0010 = 0x%x\n", phy_read(phydev, MDIO_DEVAD_NONE, 0x10));
		/* Reset registers back to normal */
		rc = phy_write(phydev, MDIO_DEVAD_NONE, 0x1f, 0x00);
		if (rc < 0)
			goto error;
	}

	/* Update cmode pins */
	val = phy_read(phydev, MDIO_DEVAD_NONE, 0x17);
	if (val < 0)
		goto error;
	if (cmode_mac_an)
		val |= 1 << 13;
	else
		val &= ~(1 << 13);

	val &= ~(0x700);
	val |= (cmode_mode << 8);

	if (cmode_mac_mode)
		val |= (1 << 12);
	else
		val &= ~(1 << 12);

	rc = phy_write(phydev, MDIO_DEVAD_NONE, 0x17, val);
	if (rc < 0)
		goto error;
	debug(" 0x0017 = 0x%x\n", phy_read(phydev, MDIO_DEVAD_NONE, 0x17));

	/* Standard registers */
	rc = phy_write(phydev, MDIO_DEVAD_NONE, 0x1f, 0);
	if (rc < 0)
		goto error;

	/* Do soft reset */
	val = phy_read(phydev, MDIO_DEVAD_NONE, 0);
	if (val < 0)
		goto error;
	val |= 0x8000;
	rc = phy_write(phydev, MDIO_DEVAD_NONE, 0, val);
	if (rc < 0)
		goto error;
	mdelay(1);

	/* Extended registers */
	rc = phy_write(phydev, MDIO_DEVAD_NONE, 0x1f, 1);
	if (rc < 0)
		goto error;

	/* SigDet polarity */
	val = phy_read(phydev, MDIO_DEVAD_NONE, 0x13);
	if (val < 0)
		goto error;

	/* Set MAC and Media modes */
	val &= ~0x361;

	if (cmode_sigdet_polarity)
		val |= 1;

	val |= (serdes_mac_loopback_mode & 3) << 5;
	val |= (serdes_media_loopback_mode & 3) << 8;
	rc = phy_write(phydev, MDIO_DEVAD_NONE, 0x13, val);
	if (rc < 0)
		goto error;
	debug(" 0x0013 = 0x%x\n", phy_read(phydev, MDIO_DEVAD_NONE, 0x13));

	/* Standard registers */
	rc = phy_write(phydev, MDIO_DEVAD_NONE, 0x1f, 0);
	if (rc < 0)
		goto error;

	/* Do soft reset */
	val = phy_read(phydev, MDIO_DEVAD_NONE, 0);
	if (val < 0)
		goto error;
	val |= 0x8000;
	rc = phy_write(phydev, MDIO_DEVAD_NONE, 0, val);
	if (rc < 0)
		goto error;
	mdelay(1);

	debug("%s(%s) done\n", __func__, ethdev->name);
	return 0;

error:
	printf("MDIO error communicating with phy %s\n", ethdev->name);
	return -1;
}

/**
 * @INTERNAL
 * Configures the Vitesse VCS8488 for use on boards like the SNIC10xxx based
 * boards using the values in the flat device tree.
 *
 * @param ethdev - ethernet device to initialize PHY for
 *
 * @returns 0 for success, error otherwise
 */
static int octeon_fdt_vitesse_config(const struct eth_device *ethdev)
{
	const void *fdt = gd->fdt_blob;
	struct phy_device *phydev;
	int phy_node_offset;
	uint32_t txon_gpio;
	enum cvmx_gpio_type gpio_type;
	uint32_t rx_eq;
	uint32_t tx_preemph;
	uint32_t tx_out_driver_ctl1;
	uint32_t tx_out_driver_ctl2;
	const uint32_t *nodep;
	uint32_t devid = MDIO_DEVAD_NONE;
	uint32_t reg, mask;
	int value;
	int c45 = 0;	/* True if clause-45 mode */
	int len;
	uint32_t *init_seq;
	int seq_len;
	int vsc8488 = 0;
	int rc;
	int phandle;
	const struct octeon_eth_info *oct_eth_info =
				 (struct octeon_eth_info *)ethdev->priv;
	debug("%s(%s)\n", __func__, ethdev->name);

	phydev = oct_eth_info->phydev;

	if (!phydev) {
		printf("%s: Error: could not get phy device for %s\n",
		       __func__, ethdev->name);
		return -1;
	}

	phy_node_offset = oct_eth_info->phy_node_offset;
	if (phy_node_offset < 0) {
		printf("%s: Error: could not find phy info for phy device\n",
		       __func__);
		return -1;
	}
	if (!fdt_node_check_compatible(fdt, phy_node_offset,
				       "vitesse,vsc8488") ||
	    !fdt_node_check_compatible(fdt, phy_node_offset,
				       "vitesse,vsc8488-15") ||
	    !fdt_node_check_compatible(fdt, phy_node_offset,
				       "vitesse,vsc8487") ||
	    !fdt_node_check_compatible(fdt, phy_node_offset,
				       "vitesse,vsc8486") ||
	    !fdt_node_check_compatible(fdt, phy_node_offset,
				       "vitesse,vsc8486-15") ||
	    !fdt_node_check_compatible(fdt, phy_node_offset,
				       "vitesse,vsc8484") ) {
		vsc8488 = 1;
		c45 = 1;
	} else if (!fdt_node_check_compatible(fdt, phy_node_offset,
					      "vitesse,vsc8572") ||
		   !fdt_node_check_compatible(fdt, phy_node_offset,
					      "vitesse,vsc8574") ||
		   !fdt_node_check_compatible(fdt, phy_node_offset,
					      "vitesse,vsc857x")) {
		rc = octeon_fdt_vitesse_vsc8574_config(ethdev);
		if (rc) {
			printf("%s: Error configuring vsc8574 for %s\n",
			       __func__, ethdev->name);
		return rc;
	}
	} else if (!fdt_node_check_compatible(fdt, phy_node_offset,
					      "vitesse,vsc8662") ||
		   !fdt_node_check_compatible(fdt, phy_node_offset,
					      "vitesse,vsc8664") ||
		   !fdt_node_check_compatible(fdt, phy_node_offset,
					      "vitesse,vsc866x")) {
		rc = octeon_vitesse_vsc866x_init(ethdev, phy_node_offset);
		if (rc) {
			printf("%s: Error configuring vsc866x for %s\n",
			       __func__, ethdev->name);
			return rc;
		}
	}


	init_seq = (uint32_t *)fdt_getprop(gd->fdt_blob, phy_node_offset,
					   "vitesse,c45-reg-init", &len);
	if (init_seq)
		c45 = 1;
	else
		init_seq = (uint32_t *)fdt_getprop(gd->fdt_blob,
						   phy_node_offset,
						   "vitesse,reg-init", &len);

	if (init_seq) {
		if ((c45 && (len % 16 != 0)) || (!c45 && (len % 12 != 0))) {
			printf("Invalid init sequence in DT for Vitesse PHY for %s\n",
			       ethdev->name);
			return -1;
		}

		seq_len = len / (c45 ? 16 : 12);
		while (seq_len--) {
			devid = (c45) ?
				fdt32_to_cpu(*init_seq++) : MDIO_DEVAD_NONE;
			reg = fdt32_to_cpu(*init_seq++);
			mask = fdt32_to_cpu(*init_seq++);

			if (mask) {
				value = phy_read(oct_eth_info->phydev, devid, reg);
				if (value < 0) {
					printf("%s: Error reading from phy for %s at %d:%d\n",
					       __func__, ethdev->name, devid, reg);
					return -1;
				}
				debug("%s: Read: 0x%x, mask: 0x%x\n", __func__,
				      value, mask);
				value &= mask;
				value |= fdt32_to_cpu(*init_seq++);
			} else {
				value = fdt32_to_cpu(*init_seq++);
			}
			debug("Vitesse init for %s addr: %d: dev: %d, reg: 0x%x, mask: 0x%x, value: 0x%x\n",
			      ethdev->name, oct_eth_info->phydev->addr, devid,
			      reg, mask, value);

			if (phy_write(oct_eth_info->phydev, devid,
				      reg, value) < 0) {
				printf("%s: Error writing 0x%x to phy for %s at %d:%d\n",
				       __func__, value, ethdev->name, devid, reg);
				return -1;
			}
		}
	}

	if (!vsc8488)
		return 0;

	/* The following are only supported on the VCS8488 for now */
	tx_preemph = getenv_ulong("vcs8488_preemph", 16, 0xffffffff);
	if (tx_preemph != 0xffffffff) {
		printf("Overriding PHY XS XAUI TX Pre-emphasis Control register to 0x%x\n",
		       tx_preemph);
		/* PHYXS_TYPE_CTRL: PHY XS XAUI Tx Pre-emphasis Control
		 *  14-13: LANE0_PE
		 *	00: 0 dB
		 *	01: ~2.5dB
		 *	10: ~6dB (default)
		 *	11: ~12dB
		 *
		 *  11-10: LANE1_PE
		 *  8-7: LANE2_PE
		 *  5-4: LANE3_PE
		 *  3-2: LOS_THRES
		 *	11: 80mV to 205mV differential peak-peak
		 *	10: 70mV to 195mV differential peak-peak
		 *	01: 60mV to 185mV differential peak-peak
		 *	00: 50mV to 175mV differential peak-peak (default)
		 *  1: HS_ENA Enable XAUI output high swing mode
		 *	0: disable (default), 1: enable
		 */
		phy_write(phydev, 4, 0x8011, tx_preemph);
	} else {
		nodep = fdt_getprop(fdt, phy_node_offset,
				    "vitesse,tx_preemphasis",
				    NULL);
		if (nodep) {
			tx_preemph = fdt32_to_cpu(*nodep);
			debug("%s: Writing 0x%x to TX pre-emphasis\n",
			      __func__, tx_preemph);
			phy_write(phydev, 4, 0x8011, tx_preemph);
		}
	}

	rx_eq = getenv_ulong("vcs8488_rxeq", 16, 0xffffffff);
	if (rx_eq != 0xffffffff) {
		printf("Overriding PHY XS XAUI Rx Equalization Control with 0x%x\n",
		       rx_eq);
		/* PHYXS_RXEQ_CTL: PHY XS Rx Equalization Control
		 *  15-12: LANE0_EQ
		 *	0000: 0 dB
		 *	0001: 1.41 dB
		 *	0010: 2.24 dB
		 *	0011: 2.83 dB
		 *	0101: 4.48 dB
		 *	0110: 5.39 dB
		 *	0111: 6.07 dB
		 *	1001: 6.18 dB
		 *	1010: 7.08 dB (default)
		 *	1011: 7.79 dB
		 *	1101: 9.96 dB
		 *	1110: 10.84 dB
		 *	1111: 11.55 dB
		 *  11-8: LANE1_EQ
		 *  7-4: LANE2_EQ
		 *  3-0: LANE3_EQ
		 */
		phy_write(phydev, 4, 0x8010, rx_eq);
	} else {
		nodep = fdt_getprop(fdt, phy_node_offset,
				    "vitesse,rx_equalization", NULL);
		if (nodep) {
			rx_eq = fdt32_to_cpu(*nodep);
			debug("%s: Writing 0x%x to RX equalization\n",
			      __func__, rx_eq);
			phy_write(phydev, 4, 0x8010, rx_eq);
		}
	}

	tx_out_driver_ctl1 = getenv_ulong("vcs8488_txdrvctrl1", 16, 0xffffffff);
	if (tx_out_driver_ctl1 != 0xffffffff) {
		printf("Overriding TX Output Driver Control 1 with 0x%x\n",
		       tx_out_driver_ctl1);
		phy_write(phydev, 1, 0x8014, tx_out_driver_ctl1);
	} else {
		nodep = fdt_getprop(fdt, phy_node_offset,
				    "vitesse,txout_driver_ctrl1", NULL);
		if (nodep) {
			tx_out_driver_ctl1 = fdt32_to_cpu(*nodep);
			debug("%s: Writing 0x%x to TX Output driver control 1\n",
			      __func__, tx_out_driver_ctl1);
			phy_write(phydev, 1, 0x8013, tx_out_driver_ctl1);
		}
	}

	tx_out_driver_ctl2 = getenv_ulong("vcs8488_txdrvctrl2", 16, 0xffffffff);
	if (tx_out_driver_ctl2 != 0xffffffff) {
		printf("Overriding TX Output Driver Control 2 with 0x%x\n",
		       tx_out_driver_ctl2);
		phy_write(phydev, 1, 0x8014, tx_out_driver_ctl2);
	} else {
		nodep = fdt_getprop(fdt, phy_node_offset,
				    "vitesse,txout_driver_ctrl2", NULL);
		if (nodep) {
			tx_out_driver_ctl2 = fdt32_to_cpu(*nodep);
			debug("%s: Writing 0x%x to TX Output driver control 2\n",
			      __func__, tx_out_driver_ctl2);
			phy_write(phydev, 1, 0x8014, tx_out_driver_ctl2);
		}
	}


	txon_gpio = fdtdec_get_int(fdt, phy_node_offset, "txon", -1);
	if (txon_gpio >= 0) {
		debug("%s: Turning on transmit with GPIO %d for %s\n",
		      __func__, txon_gpio, ethdev->name);
		gpio_type = CVMX_GPIO_PIN_OTHER;	/* Assume PHY */
		nodep = fdt_getprop(fdt, phy_node_offset, "txon-parent", NULL);
		if (nodep) {
			phandle = fdt32_to_cpu(*nodep);
			gpio_type = cvmx_fdt_get_gpio_type(fdt, phandle, NULL);
		}
		switch (gpio_type) {
		case CVMX_GPIO_PIN_OTHER:
			if (txon_gpio >= ARRAY_SIZE(vcs848x_gpio_to_reg)) {
			printf("Error: txon gpio %d is out of range on %s\n",
			       txon_gpio, ethdev->name);
			return -1;
		}
		value = vcs848x_gpio_to_reg[txon_gpio].config1_status_reg;

			debug("  Using Vitesse GPIO %d\n", txon_gpio);
		phy_write(phydev, value >> 16, value & 0xffff, 0);
			break;
		case CVMX_GPIO_PIN_OCTEON:
			debug("  Using OCTEON GPIO pin %d\n", txon_gpio);
			gpio_direction_output(txon_gpio, 0);
			break;
		default:
			printf("Unsupported GPIO type for TXON for %s\n",
			       ethdev->name);
			return -1;
		}
	} else {
		printf("Could not find txon GPIO for %s\n", ethdev->name);
	}
	return 0;
}

#ifdef CONFIG_PHYLIB_10G

#define VITESSE_FUNC_MODE_LIMITING	2	/* Optical */
#define VITESSE_FUNC_MODE_COPPER	3	/* Copper */
#define VITESSE_FUNC_MODE_LINEAR	4
#define VITESSE_FUNC_MODE_KR		5
#define VITESSE_FUNC_MODE_ZR		7
#define VITESSE_FUNC_MODE_1G		8

#ifdef DEBUG
/**
 * This reads a global variable as described in the VSC848X EDC Firmware
 * Configuration Application Note.
 *
 * @param phydev[in] - phy device to read from
 * @param channel - channel to read
 * @param addr - global variable address
 *
 * @returns 0 for success, -1 on error.
 */
static int vitesse_read_global_var(struct phy_device *phydev, uint8_t channel,
				   uint8_t addr)
{
	int timeout = 10000;
	uint16_t val;
	do {
		val = phy_read(phydev, 0x1e, 0x7fe3);
		if (val == 0)
			break;
		udelay(1);
	} while (timeout-- > 0);
	if (timeout <= 0) {
		printf("%s: Timeout waiting to read global\n", __func__);
		return -1;
	}
	phy_write(phydev, 0x1e, 0x7fe3, 0x4000 | ((channel & 3) << 8) | addr);
	timeout = 10000;
	do {
		val = phy_read(phydev, 0x1e, 0x7fe3);
		if (val == 0)
			break;
		udelay(1);
	} while (timeout-- > 0);
	if (timeout <= 0) {
		printf("%s: Timeout waiting to read global\n", __func__);
		return -1;
	}
	val = phy_read(phydev, 0x1e, 0x7fe4);
	debug("%s: Read 0x%04x from channel %d, address 0x%x\n", __func__, val,
	      channel, addr);
	return val;
}
#endif

/**
 * This writes a global variable as described in the VSC848X EDC Firmware
 * Configuration Application Note.
 *
 * @param phydev[in] - phy device to write to
 * @param channel - channel to write
 * @param addr - global variable address
 * @param value - value to write
 *
 * @returns 0 for success, -1 on error.
 */
static int vitesse_write_global_var(struct phy_device *phydev, uint8_t channel,
				    uint8_t addr, uint16_t value)
{
	int timeout = 100000;
	uint16_t val;

	/* 1. Read control register until 0 */
	do {
		val = phy_read(phydev, 0x1e, 0x7fe3);
		if (val == 0)
			break;
		udelay(100);
	} while (timeout-- > 0);
	if (timeout <= 0) {
		printf("%s: Timeout waiting to read global 1, val=0x%x\n",
		       __func__, val);
		return -1;
	}
	/* 2. Write data register */
	phy_write(phydev, 0x1e, 0x7fe4, value);
	/* 3. Write control register */
	phy_write(phydev, 0x1e, 0x7fe3,
		  0x8000 | ((channel & 3) << 8) | addr);
	debug("%s: Wrote 0x%04x to channel %d, address 0x%x\n", __func__, value,
	      channel, addr);
	/* 4. Wait until control reg cleared */
	timeout = 100000;
	do {
		val = phy_read(phydev, 0x1e, 0x7fe3);
		if (val == 0)
			break;
		udelay(100);
	} while (timeout-- > 0);
	if (timeout <= 0) {
		printf("%s: Timeout waiting to read global 2, val=0x%x\n",
		       __func__, val);
		return -1;
	}
	return 0;
}

/**
 * This function configures the Vitesse PHY based on information read from the
 * SFP+ module SFF EEPROM
 *
 * @param ethdev - ethernet device to configure
 *
 * @returns 0 for success, error otherwise
 */
int octeon_vitesse_sfp_config(struct eth_device *ethdev)
{
	struct octeon_eth_info *oct_eth_info;
	uint32_t *sfp_handle;
	uint32_t phandle;
	const uint32_t *value;
	int phy_offset;
	int sfp_offset;
	uint8_t sfp_buffer[256];
	int i2c_bus, i2c_addr;
	int offset;
	int len;
	int mode = VITESSE_FUNC_MODE_LIMITING;	/* Default for optical */
	uint64_t tx_id;
	uint8_t csum;
	int i;
	const char *mode_str = "Unknown";
	struct phy_device *phydev;
	int timeout;
	uint16_t val;
 	uint8_t addr_mask = 0;
        uint32_t old_stop_delay;

	oct_eth_info = (struct octeon_eth_info *)ethdev->priv;

	phydev = oct_eth_info->phydev;

	if (!is_10g_interface(oct_eth_info->phydev->interface))
		return 0;

	/* This is a lengthy process to parse and validate the device tree.
	 * The SPD EEPROM address is linked from the PHY.  We must obtain both
	 * the TWSI bus number and the address (which should be 0x50) from the
	 * device tree before we can actually read it.
	 */
	phy_offset = oct_eth_info->phy_fdt_offset;

	sfp_handle = (uint32_t *)fdt_getprop(gd->fdt_blob, phy_offset,
					     "sfp-eeprom", NULL);
	if (!sfp_handle) {
		printf("Error: cannot find SFP for PHY on %s\n", ethdev->name);
		return -1;
	}

	phandle = fdt32_to_cpu(*sfp_handle);
	sfp_offset = fdt_node_offset_by_phandle(gd->fdt_blob, phandle);
	if (sfp_offset < 0) {
		printf("Error: cannot find SFP for PHY on %s\n", ethdev->name);
		return -1;
	}

	if (fdt_node_check_compatible(gd->fdt_blob, sfp_offset, "atmel,24c01")) {
		printf("Error: Unknown SFP EEPROM type for %s\n", ethdev->name);
		return -1;
	}

	value = (uint32_t *)fdt_getprop(gd->fdt_blob, sfp_offset, "reg", NULL);
	if (!value) {
		printf("Error: could not get SFP EEPROM address for %s\n",
		       ethdev->name);
		return -1;
	}
	i2c_addr = fdt32_to_cpu(*value);

	offset = fdt_parent_offset(gd->fdt_blob, sfp_offset);
	if (fdt_node_check_compatible(gd->fdt_blob, offset,
				      "cavium,octeon-3860-twsi")) {
		printf("Error: incompatible TWSI bus type for %s\n",
		       ethdev->name);
		return -1;
	}

	value = (uint32_t *)fdt_getprop(gd->fdt_blob, offset, "reg", &len);

	if (len != 16)  {
		printf("Error: invalid register length for TWSI bus for SFP for %s\n",
		       ethdev->name);
		return -1;
	}
	if (!value) {
		printf("Error: could not obtain TWSI bus information for SFP for %s\n",
		       ethdev->name);
		return -1;
	}
	i2c_bus = octeon_i2c_reg_addr_to_bus(((uint64_t)fdt32_to_cpu(value[0]) << 32)
					   | fdt32_to_cpu(value[1]));

	if (i2c_bus < 0) {
		printf("Error: Unknown register address for TWSI bus for SPD for %s\n",
		       ethdev->name);
		return -1;
	}

	i2c_set_bus_num(i2c_bus);
	/* We need to increase the delay between transactions for the SFP+
	 * module to 26usec minimum.
	 */
        old_stop_delay = i2c_get_stop_delay();
        i2c_set_stop_delay(26);

	if (i2c_read(i2c_addr, 0, 1, sfp_buffer, 64)) {
		/* The SPD might not be present, i.e. if nothing is plugged in */
		debug("Error reading from spd on I2C bus %d, address 0x%x for %s\n",
		      i2c_bus, i2c_addr, ethdev->name);
		return 0;
	}

	i2c_set_stop_delay(old_stop_delay);

	/* Validate the checksum */
	csum = 0;
	for (i = 0; i < 63; i++)
		csum += sfp_buffer[i];
	if (csum != sfp_buffer[63]) {
		printf("Warning: SFP checksum information is incorrect for %s.\n"
		       "Checksum is 0x%x, expected 0x%x\n",
		       ethdev->name, sfp_buffer[63], csum);
	}

	/* Check transceiver type.  See the SFF-8472 standard. */
	if (sfp_buffer[0] != 3) {	/* SFP or SFP+ */
		printf("Error: Unknown SFP transceiver type 0x%x for %s\n",
		       sfp_buffer[0], ethdev->name);
		return -1;
	}

	if (sfp_buffer[1] < 1 || sfp_buffer[1] > 7) {	/* Extended ID */
		printf("Error: Unknown SFP extended identifier 0x%x for %s\n",
		       sfp_buffer[1], ethdev->name);
		return -1;
	}

	switch (sfp_buffer[2]) {
	case 0x01:
		mode = VITESSE_FUNC_MODE_LIMITING;
		mode_str = "SC";
		break;
	case 0x07:
		mode = VITESSE_FUNC_MODE_LIMITING;
		mode_str = "LC";
		break;
	case 0x0B:
		mode = VITESSE_FUNC_MODE_LIMITING;
		mode_str = "Optical Pigtail";
		break;
	case 0x21:
		mode = VITESSE_FUNC_MODE_COPPER;
		mode_str = "Copper Pigtail";
		break;
	default:
		printf("Error: Unknown SFP module type 0x%x.  Please see SFF-8472 table 3.4 for definition\n",
		       sfp_buffer[2]);
		return -1;
	}
	memcpy(&tx_id, &sfp_buffer[3], sizeof(tx_id));
	if (mode == VITESSE_FUNC_MODE_LIMITING) {
		if (sfp_buffer[3] & 0x80)
			debug("%s SFP cap 10G Base-ER\n", ethdev->name);
		if (sfp_buffer[3] & 0x40)
			debug("%s SFP cap 10G Base-LRM\n", ethdev->name);
		if (sfp_buffer[3] & 0x20)
			debug("%s SFP cap 10G Base-LR\n", ethdev->name);
		if (sfp_buffer[3] & 0x10)
			debug("%s SFP cap 10G Base-SR\n", ethdev->name);
		if (!(sfp_buffer[3] & 0xF0)) {
			printf("Error: unknown SFP ID 0x%016llx for %s\n",
			       tx_id, ethdev->name);
			puts("SFP+ does not support Ethernet.\n");
			return -1;
		}
	} else if (mode == VITESSE_FUNC_MODE_COPPER) {
		if (sfp_buffer[8] & 0x4) {
			debug("%s SFP is passive copper\n", ethdev->name);
			if (sfp_buffer[6] & 0x4) {
				debug("%s SFP+ supports Twinax\n", ethdev->name);
			} else if (sfp_buffer[6] & 0x8) {
				debug("%s SFP+ supports 1000Base-T", ethdev->name);
			}
		} else if(sfp_buffer[8] & 0x8) {
			debug("%s SFP is active copper\n", ethdev->name);
			mode = 2;	/* Active copper uses optical mode */
		} else {
			printf("Error: Cannot detect if copper SFP+ is active or passive for %s\n",
			       ethdev->name);
			printf("SFP+ id is 0x%016llx\n", tx_id);
			return -1;
		}
	} else {
		printf("Unknown mode %d for %s\n", mode, ethdev->name);
		printf("SFP+ id is 0x%016llx\n", tx_id);
		return -1;
	}

	debug("%s: Setting PHY to mode %d (%s) on %s\n",
	      __func__, mode, mode_str, ethdev->name);

	/* Wait for firmware download to complete */
	timeout = 100000;
	do {
		/* Check the checksum result register */
		val = phy_read(phydev, 0x1e, 0x7fe0);
		if (val == 3)
			break;
		udelay(100);
	} while (timeout-- > 0);
	if (timeout <= 0) {
		printf("Error waiting for PHY firmware download to complete on %s, reg: 0x%04x\n",
		       ethdev->name, val);
		return -1;
	}

	/* Program the mode into the PHY */
	if (!fdt_node_check_compatible(gd->fdt_blob, phy_offset,
	    "vitesse,vsc8488"))
		addr_mask = 1;
	if (!fdt_node_check_compatible(gd->fdt_blob, phy_offset,
	    "vitesse,vsc8484"))
		addr_mask = 3;

	if (mode == VITESSE_FUNC_MODE_COPPER) {
		/* DC_AGC_LOS_CONFIG1:
		 *   15: Suppress_Coarse_Adj_on_LOS_Clear
		 *	0: DC offset correction performed using coarse
		 *	   resolution mode (default)
		 *	1: DC offset correction performed using fine resolution
		 *	   mode when correction resumes after LOPC/LOS alarms
		 *	   clear.  This guarantees there will be no big jumps in
		 *	   the offset at the expense of taking longer to reach
		 *	   optimal setting.
		 *   14: Force_DC2_Fine_Adj:
		 *	Forces the DC offset correction to operate in fine
		 *	resolution adjustment mode at times when the algorithm.
		 *	0: DC offset correction makes coarse adjustments when
		 *	   correction mode is first enabled (default)
		 *	1: DC offset correction performed using fine resolution
		 *	   at all times.  This is slower.
		 *   13: Force_DC1_Fine_Adj:
		 *	Forces the DC offset correction to operate in fine
		 *	resolution adjustment mode at times when the algorithm.
		 *	0: DC offset correction makes coarse adjustments when
		 *	   correction mode is first enabled (default)
		 *	1: DC offset correction performed using fine resolution
		 *	   at all times.  This is slower.
		 *   12: Force_DC0_Fine_Adj:
		 *	Forces the DC offset correction to operate in fine
		 *	resolution adjustment mode at times when the algorithm.
		 *	0: DC offset correction makes coarse adjustments when
		 *	   correction mode is first enabled (default)
		 *	1: DC offset correction performed using fine resolution
		 *	   at all times.  This is slower.
		 *   10: Skip_DC2_Adj, 1 = skip DC2 offset correction
		 *   9:  Skip_DC1_Adj, 1 = skip DC1 offset correction
		 *   8:  Skip_DC0_Adj, 1 = skip DC0 offset correction
		 *
		 *   6-4: DC_Offset_Alarm_Mode (default 1)
		 *	Selects the alarm condition that will halt the DC offset
		 *	correction logic when the alarm(s) are set.
		 *	111: reserved
		 *	110: reserved
		 *	101: LOPC and software LOS detection
		 *	100: LOPC and hardware LOS detection
		 *	011: Software LOS detection
		 *	010: Hardware LOS detection
		 *	001: LOPC
		 *	000: Never.  DC offset correction will continue to make
		 *	     fine resolution adjustments to the offsets even
		 *	     when LOPC and LOS alarms are present.
		 *
		 *  3: AGC_Enable
		 *	Selects when hardware AGC adjustment logic and LOS
		 *	detection logic is enabled (default 1)
		 *	0: disabled
		 *	1: enabled
		 *  2: AGC_Suspend
		 *	Suspends the LOS detection logic and AGC logic
		 *	from making adjustments to the gain.  Bit valid only
		 *	if AGC_Enable=1
		 *	0: AGC adjustment enabled (default)
		 *	1: AGC adjustment suspended
		 *  1: DC_Offset_Adj_Enable
		 *	Select when the hardware DC offset correction logic is
		 *	enabled.
		 *	0: disable
		 *	1: enable (default)
		 *  0: DC_Offset_Adj_Suspend
		 *	Suspends the DC offset correction logic from making
		 *	adjustments to all offset settings.  Bit valid only if
		 *	DC_Offset_Adj_Enable=1
		 *	0: DC offset correction enabled (default)
		 *	1: DC offset correction suspended
		 */
		value = fdt_getprop(gd->fdt_blob, phy_offset,
				    "vitesse,copper_dc_agc_los_config1", NULL);
		if (value) {
			debug("%s: Writing 0x%x to DC_AGC_LOS CONFIG1\n",
			      __func__, fdt32_to_cpu(*value));
			phy_write(phydev, 1, 0xB0C0, fdt32_to_cpu(*value));
		}

		value = fdt_getprop(gd->fdt_blob, phy_offset,
				    "vitesse,copper_agg_track_phase", NULL);
		if (value && !(*value)) {
			/* This setting disables the aggressive track phase for
			 * firmware convergence.  The aggressive track phase
			 * takes place in state 4 after selecting the best tap
			 * (which takes 5 seconds).  This state normally remains
			 * active for 60 seconds.
			 */
			vitesse_write_global_var(phydev,
						 phydev->addr & addr_mask,
						 0xAF, 0xFFFF);
		}

		/* This global variable is not documented */
		vitesse_write_global_var(phydev, phydev->addr & addr_mask,
					 0x83, 0x0A);
		/* AGC_Config4
		 *
		 * 13-8: Ampl_Tolerance
		 *	This defines the hysterisis built in to the AGC
		 *	adjustment circuit.  The VGA gain will not be adjusted
		 *	as long as the measured input amplitude is
		 *	Inp_Ampl_Target +/- Amnpl_Tolerance.  Default is 4.
		 * 7-0: Inp_Ampl_Target
		 *	This is the target amplitude desired to be measured at
		 *	the peak detector when measuring input amplitude.  The
		 *	VGA gain is adjusted to achieve this target setting.
		 *	Default is 0x6E.
		 */
		value = fdt_getprop(gd->fdt_blob, phy_offset,
				    "vitesse,copper_agc_config4", NULL);
		if (value) {
			debug("%s: Writing 0x%x to AGC_Config4\n",
			      __func__, fdt32_to_cpu(*value));
			phy_write(phydev, 1, 0xb0c5, fdt32_to_cpu(*value));
		}
	}
	vitesse_write_global_var(phydev, phydev->addr & addr_mask, 0x94, mode);

	/* Adjust PMA_TXOUTCTRL2 based on cable length for copper */
	if (mode == VITESSE_FUNC_MODE_COPPER) {
		if (sfp_buffer[18] >= 5) {
			/* Optimize for 5M and longer cables */
			/* PMA_TXOUTCTRL2
			 *	PMA Tx Output Driver Control 2
			 *  12-8: C(0) Tap Control
			 *	Tx Output Driver C(0) Coefficient Control
			 *	00000: Minimum (0mA)
			 *	11111: Maximum (+16mA)
			 *	10011: default
			 *  5-0: C(+1) Tap Control
			 *	000000: Minimum (-0.25mA) (default)
			 *	111111: Maximum (-16mA)
			 */
			phy_write(phydev, 1, 0x8014, 0x1606);
		}
		if (0) {/* Disable for now, causes link flapping */
			/* Limit the EDC taps */
			vitesse_write_global_var(phydev,
						 phydev->addr & addr_mask,
						 0x52, 0x7a0);
			vitesse_write_global_var(phydev,
						 phydev->addr & addr_mask,
						 0x54, 0x600);
		}
	}

	/* Reset the state machine */
	phy_write(phydev, 1, 0x8036, 0x11);


#ifdef DEBUG
	for (i = 0; i < 4; i++)
		vitesse_read_global_var(phydev, i, 0x94);
#endif

	return 0;
}
#endif
/**
 * Configures all Vitesse VCS8488 devices found.
 *
 * @return 0 for success, error otherwise.
 */
int octeon_vcs8488_config(void)
{
	struct eth_device *start = eth_get_dev();
	struct eth_device *ethdev = start;
	struct octeon_eth_info *oct_eth_info;

	if (!start) {
		debug("%s: No Ethernet devices found\n", __func__);
		return 0;
	}
	do {
		oct_eth_info = (struct octeon_eth_info *)ethdev->priv;
		if (!fdt_node_check_compatible(gd->fdt_blob,
					       oct_eth_info->phy_fdt_offset,
					       "vitesse")) {
			if (octeon_fdt_vitesse_config(ethdev)) {
				printf("%s: Error configuring Ethernet device %s\n",
				       __func__, ethdev->name);
				return -1;
			}
		}
		ethdev = ethdev->next;
	} while (ethdev && ethdev != start);
	return 0;
}

/**
 * This function tunes the QLM for use by the Vitesse VCS8488 PHY.
 *
 * @param qlm - qlm number to tune
 */
void octeon_board_vcs8488_qlm_tune(int qlm)
{
	if (!OCTEON_IS_MODEL(OCTEON_CN66XX) &&
	    !OCTEON_IS_MODEL(OCTEON_CN61XX)) {
		printf("%s: Not supported on this OCTEON model yet\n", __func__);
		return;
	}
	cvmx_qlm_jtag_set(qlm, -1, "tcoeff_hf_ls_byp", 0);
	cvmx_qlm_jtag_set(qlm, -1, "tcoeff_hf_byp", 0);
	cvmx_qlm_jtag_set(qlm, -1, "tcoeff_lf_ls_byp", 0);
	cvmx_qlm_jtag_set(qlm, -1, "tcoeff_lf_byp", 0);
	cvmx_qlm_jtag_set(qlm, -1, "rx_eq_gen1", 0);
	cvmx_qlm_jtag_set(qlm, -1, "rx_eq_gen2", 0);
	cvmx_qlm_jtag_set(qlm, -1, "rx_cap_gen1", 0);
	cvmx_qlm_jtag_set(qlm, -1, "rx_cap_gen2", 0);
	cvmx_qlm_jtag_set(qlm, -1, "biasdrv_hs_ls_byp", 31);
	cvmx_qlm_jtag_set(qlm, -1, "biasdrv_hf_byp", 31);
	cvmx_qlm_jtag_set(qlm, -1, "biasdrv_lf_ls_byp", 31);
	cvmx_qlm_jtag_set(qlm, -1, "biasdrv_lf_byp", 31);
	/* Assert serdes_tx_byp to force the new settings to override the
	   QLM default. */
	cvmx_qlm_jtag_set(qlm, -1, "serdes_tx_byp", 1);
}
#endif /* CONFIG_PHY_VITESSE */

int octeon_board_post_phy_init(void)
{
	return 0;
}

int octeon_board_post_phy_init(void) __attribute__((weak));

/**
 * Initializes all of the PHYs on a board using the device tree information.
 *
 * @return 0 for success, error otherwise
 */
int octeon_board_phy_init(void)
{
	struct eth_device *ethdev, *start;
	struct octeon_eth_info *oct_eth_info;

	int err = 0;
	int rc = 0;
	int phy_off;
#ifdef CONFIG_PHY_VITESSE
	int need_coma = 0;
#endif

	debug("%s()\n", __func__);
	start = eth_get_dev();
	if (!start) {
		debug("%s: No starting eth device found\n", __func__);
		return 0;
	}

	ethdev = start;
	do {
		oct_eth_info = (struct octeon_eth_info *)ethdev->priv;
		if (!oct_eth_info) {
			printf("%s: ERROR: ethernet private information not set\n",
			       __func__);
		}
		phy_off = oct_eth_info->phy_fdt_offset;

		debug("%s: Initializing %s\n", __func__, ethdev->name);
		if (!oct_eth_info->phydev) {
			ethdev = ethdev->next;
			continue;
		}
#ifdef DEBUG
			switch (oct_eth_info->phy_device_type) {
		case BROADCOM:	debug("  Broadcom PHY\n");	break;
		case MARVELL:	debug("  Marvell PHY\n");	break;
		case CORTINA:	debug("  Cortina PHY\n");	break;
		case GENERIC_8023_C22:
			debug("  Generic 802.3 C22 PHY\n");
			break;
		case GENERIC_8023_C45:
			debug("  Generic 802.3 C45 PHY\n");
			break;
		case INBAND:
			debug("  Inband PHY\n");
			break;
		default:
			debug("  Unknown PHY type %d\n",
			      oct_eth_info->phy_device_type);
			break;
		}
		debug("Compatible: %s\n", (char *)fdt_getprop(gd->fdt_blob,
							      phy_off,
							      "compatible",
							      NULL));
#endif /* DEBUG */
#ifdef CONFIG_PHY_MARVELL
		if (!octeon_fdt_compat_vendor(gd->fdt_blob, phy_off,
					      "marvell")) {
			debug("Configuring Marvell PHY\n");
				if ((rc = octeon_fdt_marvell_config(ethdev)))
					printf("Error configuring Marvell PHY for %s\n",
					       ethdev->name);
		} else
#endif
#ifdef CONFIG_PHY_BROADCOM
		if (!octeon_fdt_compat_vendor(gd->fdt_blob, phy_off,
					      "broadcom")) {
			debug("Configuring Broadcom PHY\n");
				if ((rc = octeon_fdt_broadcom_config(ethdev)))
					printf("Error configuring Broadcom PHY for %s\n",
					       ethdev->name);
		} else
#endif
#ifdef CONFIG_PHY_VITESSE
		if (!octeon_fdt_compat_vendor(gd->fdt_blob, phy_off,
					      "vitesse")) {
			debug("Configuring Vitesse PHY\n");
			need_coma = 1;
			octeon_vitesse_coma(true);
				rc = octeon_fdt_vitesse_config(ethdev);
#ifdef CONFIG_PHYLIB_10G
			/* Only read SFP+ for 10G parts */
			if (!fdt_node_check_compatible(gd->fdt_blob, phy_off,
						       "ethernet-phy-ieee802.3-c45"))
				rc |= octeon_vitesse_sfp_config(ethdev);
#endif
				if (rc)
					printf("Error configuring Vitesse PHY for %s\n",
					       ethdev->name);
		} else
#endif
#ifdef CONFIG_PHY_TI
		if (!octeon_fdt_compat_vendor(gd->fdt_blob, phy_off, "ti")) {
			debug("Configuring TI PHY\n");
			rc = octeon_fdt_ti_config(ethdev);
			if (rc)
				printf("Error configuring TI PHY for %s\n",
				       ethdev->name);
		} else
#endif
		if (!fdt_node_check_compatible(gd->fdt_blob, phy_off,
					       "ethernet-phy-ieee802.3-c22")) {
			debug("Configuring generic 802.3 C22 PHY\n");
				rc = octeon_fdt_generic_8023_c22_config(ethdev);
				if (rc)
					printf("Error configuring generic 802.3 C22 PHY for %s\n",
					       ethdev->name);
		} else if (!fdt_node_check_compatible(gd->fdt_blob, phy_off,
						      "ethernet-phy-ieee802.3-c45")) {
			printf("Generic 802.3 c45 init function needed for %s\n",
			       ethdev->name);
		} else if (!fdt_node_check_compatible(gd->fdt_blob, phy_off,
						      "cortina,cs4318")) {
			debug("Don't do anything here.\n");
		} else {
			printf("%s: Unknown PHY type for %s\n",
			       __func__, ethdev->name);
			err |= 1;
			}
			err |= rc;

		ethdev = ethdev->next;
	} while (ethdev != start);

#if defined(CONFIG_PHY_VITESSE)
	if (need_coma)
		octeon_vitesse_coma(false);
#endif
	if (!err)
		err = octeon_board_post_phy_init();

	return err;
}
