/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2009, 2010, 2011, 2012 Cavium Inc.
 */

#include <common.h>
#include <malloc.h>
#include <phy.h>
#include <miiphy.h>
#include <asm/arch/cvmx.h>
#include <asm/arch/cvmx-mdio.h>
#include <asm/arch/octeon_mdio.h>
#include <fdt.h>
#include <fdt_support.h>
#include <i2c.h>
#include <asm/gpio.h>

#ifndef MII_ADDR_C45
#define MII_ADDR_C45 (1 << 30)
#endif

#define OCT_REMOTE_BUS_FLAG	0x10000

#define MAX_GPIOS		2

DECLARE_GLOBAL_DATA_PTR;

enum phy_mux_type {
	SN74CBTLV3253,
	OTHER
};

enum phy_gpio_type {
	GPIO_OCTEON,
	GPIO_PCA8574
};


struct octeon_mdiobus {
	struct mii_dev *mii_dev;
	/**
	 * The local bus is in the lower 8 bits, followed by the remote bus in
	 * the top 8 bits.  Bit 16 will be set if the bus is non-local.
	 */
	uint32_t bus_id;

	/* The following is to work on some insane boards that use a mux
	 * to access a MDIO bus.
	 */
	int local;			/** 1 if local MDIO bus */
	int num_gpios;			/** Number of GPIO pins used for MUX */
	int gpio[MAX_GPIOS];		/** GPIO pins used to control the mux */
	enum phy_gpio_type gpio_type[MAX_GPIOS];	/** type of each GPIO line */
	int gpio_i2c[MAX_GPIOS];	/** twsi address of each GPIO line */
	int gpio_value;			/** value to put on the GPIO lines to select */
	int gpio_parent_mux_i2c;	/** -1 if not used, parent i2c mux for ebb6600 */
	int gpio_parent_mux_select;	/** Selector to use on the parent i2c mux */
	enum phy_mux_type mux_type;	/** Type of mux */
	int mux_twsi_addr;		/** Address of TWSI mux */
};

static int current_muxed_bus = -1;

static int __set_i2c_mux(int i2c_addr, uint8_t value)
{
	uint8_t old_val;
	int rc;

	debug("%s(0x%x, 0x%x)\n", __func__, i2c_addr, value);
	/* Assume I2C bus number 0 for now */
	i2c_set_bus_num(0);

	rc = i2c_read(i2c_addr, 0, 1, &old_val, 1);
	if (rc < 0) {
		debug("%s: Error reading i2c addr 0x%x\n", __func__, i2c_addr);
		return -1;
	}

	if (i2c_write(i2c_addr, 0, 1, &value, 1) < 0) {
		debug("%s: Error writing to i2c address 0x%x\n",
		      __func__, i2c_addr);
		return -1;
	}
	debug("%s: old value: 0x%x\n", __func__, old_val);
	return old_val;
}

static void __set_gpio(const int gpio_pin[], int num_bits,
		       enum phy_gpio_type type, int i2c_addr, int value)
{
	int i;
	uint8_t new_value;

	switch (type) {
	case GPIO_OCTEON:
		debug("%s(0x%p, %d, GPIO_OCTEON, 0x%x, 0x%x\n",
		      __func__, gpio_pin, num_bits, i2c_addr, value);
		for (i = 0; i < num_bits; i++) {
			debug("%s: gpio pin %d set to %d\n", __func__,
			      gpio_pin[i], (value >> i) & 1);
			gpio_direction_output(gpio_pin[i], (value >> i) & 1);
		}
		break;
	case GPIO_PCA8574:
		debug("%s(0x%p, %d, GPIO_PCA8574, 0x%x, 0x%x\n",
		      __func__, gpio_pin, num_bits, i2c_addr, value);
		new_value = 0xff;
		for (i = 0; i < num_bits; i++) {
			debug("gpio_pin[%d] = %d]\n", i, gpio_pin[i]);
			if (((value >> i) & 1) == 0)
				new_value &= ~(1 << gpio_pin[i]);
		}
		debug("%s: Writing 0x%x to I2C address 0x%x\n",
		      __func__, new_value, i2c_addr);
		i2c_write(i2c_addr, 0, 1, &new_value, 1);
		break;
	default:
		printf("%s: Unknown GPIO type\n", __func__);
		break;
	}
}

static int switch_mdio_mux(struct octeon_mdiobus *bus)
{
	int num_bits = bus->num_gpios;
	int old_mux = -1;

	if (num_bits == 0)
		return -1;

	if ((bus->bus_id & 0xFFFF0000) == (current_muxed_bus & 0xFFFF0000)) {
		debug("%s: bus id 0x%x matches current bus 0x%x\n", __func__,
		      bus->bus_id, current_muxed_bus);
		return 0;
	}

	/* For now we assume all of the GPIO lines are contiguous and the
	 * same type.
	 */

	/* If the I2C bus is also muxed, set that up first */
	if (bus->gpio_parent_mux_i2c > 0) {
		debug("%s: Setting parent i2c mux at 0x%x to 0x%x\n",
		      __func__, bus->gpio_parent_mux_i2c,
		      1 << bus->gpio_parent_mux_select);
		old_mux = __set_i2c_mux(bus->gpio_parent_mux_i2c,
					1 << bus->gpio_parent_mux_select);
		if (old_mux < 0) {
			printf("%s: Error: could not read old MUX value\n",
			       __func__);
			return -1;
		}
	} else {
		debug("%s: No parent i2c mux\n", __func__);
	}


	__set_gpio(bus->gpio, num_bits, bus->gpio_type[0],
		   bus->gpio_i2c[0], bus->gpio_value);

	current_muxed_bus = bus->bus_id;
	return 0;
}

#ifdef CONFIG_SWITCH_RTL8367X

static int octeon_phy_read(struct mii_dev *dev, int phy_addr, int dev_addr,
			   int reg_addr)
{
	struct octeon_mdiobus *p = dev->priv;
	int value;

	debug("%s(0x%p(%s), %d, 0x%x, 0x%x)\n", __func__, dev, dev->name, phy_addr,
	      dev_addr, reg_addr);
	debug("bus id: 0x%x\n", p->bus_id);
	if (!p->local)
		switch_mdio_mux(p);
#ifdef CONFIG_PHYLIB_10G
	if (dev_addr != MDIO_DEVAD_NONE ||
	    is_10g_interface(dev->phymap[phy_addr]->interface)) {
		debug("clause 45 mode\n");
		value = cvmx_mdio_45_read(p->bus_id & 0xff, phy_addr, dev_addr,
					  reg_addr);
	} else
#endif
	{
        int ret = 0;
        uint32_t reg_val = 0;

		debug("RTL8367S : clause 22 mode\n");

        ret = rtl8367c_getAsicPHYReg(phy_addr, reg_addr, &reg_val);
        if (0 != ret) {
            debug("rtl8367c_getAsicPHYReg(%d,%d) failed, return %d\n", phy_addr, reg_addr, ret);
            return 0;
        }

        value = reg_val;
	}
	debug("Return value: 0x%x\n", value);
	return value;
}

static int octeon_phy_write(struct mii_dev *dev, int phy_addr, int dev_addr,
			    int reg_addr, u16 value)
{
	struct octeon_mdiobus *p = dev->priv;

	debug("%s(0x%p(%s), %d, 0x%x, 0x%x, 0x%x)\n", __func__, dev, dev->name,
	      phy_addr, dev_addr, reg_addr, value);
	debug("bus id: 0x%x\n", p->bus_id);
	if (!p->local)
		switch_mdio_mux(p);

#ifdef CONFIG_PHYLIB_10G
	if (dev_addr != MDIO_DEVAD_NONE ||
	    is_10g_interface(dev->phymap[phy_addr]->interface)) {
		debug("clause 45 mode\n");
		return cvmx_mdio_45_write(p->bus_id & 0xff, phy_addr, dev_addr,
					  reg_addr, value);
	} else
#endif
	{
		int ret = 0;
        uint32_t reg_val = 0;

		debug("RTL8367S : clause 22 mode\n");

        ret = rtl8367c_setAsicPHYReg(phy_addr, reg_addr, value);
        if (0 != ret) {
            debug("rtl8367c_setAsicPHYReg(%d,%d,%d) failed, return %d\n", phy_addr, reg_addr, value, ret);
            return 0;
        }
	}
}

static int octeon_phy_reset(struct mii_dev *bus)
{
	return 0;
}

#else /* CONFIG_SWITCH_RTL8367X */

static int octeon_phy_read(struct mii_dev *dev, int phy_addr, int dev_addr,
			   int reg_addr)
{
	struct octeon_mdiobus *p = dev->priv;
	int value;

	debug("%s(0x%p(%s), %d, 0x%x, 0x%x)\n", __func__, dev, dev->name, phy_addr,
	      dev_addr, reg_addr);
	debug("bus id: 0x%x\n", p->bus_id);
	if (!p->local)
		switch_mdio_mux(p);
#ifdef CONFIG_PHYLIB_10G
	if (dev_addr != MDIO_DEVAD_NONE ||
	    is_10g_interface(dev->phymap[phy_addr]->interface)) {
		debug("clause 45 mode\n");
		value = cvmx_mdio_45_read(p->bus_id & 0xff, phy_addr, dev_addr,
					  reg_addr);
	} else
#endif
	{
		debug("clause 22 mode\n");
		value =  cvmx_mdio_read(p->bus_id & 0xff, phy_addr, reg_addr);
	}
	debug("Return value: 0x%x\n", value);
	return value;
}

static int octeon_phy_write(struct mii_dev *dev, int phy_addr, int dev_addr,
			    int reg_addr, u16 value)
{
	struct octeon_mdiobus *p = dev->priv;

	debug("%s(0x%p(%s), %d, 0x%x, 0x%x, 0x%x)\n", __func__, dev, dev->name,
	      phy_addr, dev_addr, reg_addr, value);
	debug("bus id: 0x%x\n", p->bus_id);
	if (!p->local)
		switch_mdio_mux(p);

#ifdef CONFIG_PHYLIB_10G
	if (dev_addr != MDIO_DEVAD_NONE ||
	    is_10g_interface(dev->phymap[phy_addr]->interface)) {
		debug("clause 45 mode\n");
		return cvmx_mdio_45_write(p->bus_id & 0xff, phy_addr, dev_addr,
					  reg_addr, value);
	} else
#endif
	{
		debug("clause 22 mode\n");
		return cvmx_mdio_write(p->bus_id & 0xff, phy_addr,
				       reg_addr, value);
	}
}

static int octeon_phy_reset(struct mii_dev *bus)
{
	return 0;
}

#endif /* CONFIG_SWITCH_RTL8367X */


/**
 * Gets the mux information from the DT.
 *
 * @param[in,out] oct_bus - mdio bus
 * @param mux - offset in device tree of /mdio-mux
 * @param mdio_offset - offset of muxed MDIO bus in device tree
 *
 * @return 0 on success, -1 on error
 */
static int octeon_mdio_get_mux_info(struct octeon_mdiobus *oct_bus,
				    int mux_offset, int mdio_offset)
{
	uint32_t *prop_val;
	int phandle;
 	uint32_t *psmi_handle;
	int smi_offset;
	uint64_t smi_addr;
	uint64_t *smi_addrp;
	int len;
	int smi_bus_num;
	uint32_t *pgpio_handle;
	int gpio_count;
	int gpio_offset;
	int offset;

	if (mux_offset < 0) {
		printf("%s: Invalid mux offset\n", __func__);
		return -1;
	}

	debug("%s(0x%p, %d, %d)\n", __func__, oct_bus, mux_offset, mdio_offset);
	if (fdt_node_check_compatible(gd->fdt_blob, mux_offset,
				      "cavium,mdio-mux")) {
		printf("%s: mdio-mux not compatible\n", __func__);
		return -1;
	}

	psmi_handle = (uint32_t *)fdt_getprop(gd->fdt_blob, mux_offset,
					      "mdio-parent-bus", NULL);
	if (!psmi_handle) {
		printf("%s: No parent handle found!\n", __func__);
		return -1;
	}
	phandle = fdt32_to_cpu(*psmi_handle);
	smi_offset = fdt_node_offset_by_phandle(gd->fdt_blob,
						phandle);
	debug("%s: smi_offset: 0x%x\n", __func__, smi_offset);
	if (smi_offset < 0) {
		printf("%s: Could not get smi parent offset in DT\n",
		       __func__);
		return -1;
	}

	if (fdt_node_check_compatible(gd->fdt_blob, smi_offset,
				      "cavium,octeon-3860-mdio")) {
		printf("%s: Incompatible SMI bus\n", __func__);
		return -1;
	}

	smi_addrp = (uint64_t *)fdt_getprop(gd->fdt_blob,
					    smi_offset, "reg", &len);
	if (smi_addrp != NULL && len > 8) {
		memcpy(&smi_addr, smi_addrp, sizeof(uint64_t));
		smi_addr = fdt64_to_cpu(smi_addr);
		debug("%s: SMI addr: 0x%llx\n", __func__, smi_addr);
	} else {
		printf("%s: Error: unknown SMI address\n", __func__);
		return -1;
	}

	/* Now we need to translate the SMI address to a bus number */
	/* Convert SMI address to a MDIO interface */
	smi_bus_num = octeon_mdio_reg_addr_to_bus(smi_addr);

	debug("%s: smi_bus: %d, old bus id: 0x%x\n", __func__,
	      smi_bus_num, oct_bus->bus_id);
	/* Set the parent BUS number */
	oct_bus->bus_id |= smi_bus_num;

	/* Find the GPIO MUX controller */
	pgpio_handle = (uint32_t *)fdt_getprop(gd->fdt_blob, mux_offset,
					       "gpios", &len);
	if (!pgpio_handle || len < 12 || (len % 12) != 0 ||
	    len > MAX_GPIOS * 12) {
		puts("Invalid GPIO for muxed MDIO controller in DT\n");
		return -1;
	}

	oct_bus->num_gpios = len / 12;
	if (oct_bus->num_gpios > MAX_GPIOS) {
		printf("%s: Error: Found %d GPIOs, max is %d\n", __func__,
		       oct_bus->num_gpios, MAX_GPIOS);
		return -1;
	}
	for (gpio_count = 0; gpio_count < oct_bus->num_gpios; gpio_count++) {
		phandle = fdt32_to_cpu(pgpio_handle[gpio_count * 3]);
		oct_bus->gpio[gpio_count] =
			fdt32_to_cpu(pgpio_handle[gpio_count * 3 + 1]);
			debug("%s: gpio[%d]: %d\n", __func__, gpio_count,
			      oct_bus->gpio[gpio_count]);
		gpio_offset = fdt_node_offset_by_phandle(gd->fdt_blob,
							 phandle);
		if (gpio_offset < 0) {
			puts("Cannot access parent GPIO node in DT\n");
			return -1;
		}

		if (!fdt_node_check_compatible(gd->fdt_blob,
					       gpio_offset,
					       "cavium,octeon-3860-gpio")) {
			oct_bus->gpio_type[gpio_count] = GPIO_OCTEON;
			debug("gpio_type[%d] is OCTEON\n", gpio_count);
		} else if (!fdt_node_check_compatible(gd->fdt_blob,
						      gpio_offset,
						      "nxp,pca8574")) {
			/* GPIO is a TWSI GPIO unit which might sit
			 * behind another MUX
			 */
			oct_bus->gpio_type[gpio_count] = GPIO_PCA8574;
			/* Get the I2C address of the GPIO mux */
			prop_val = (uint32_t *)fdt_getprop(gd->fdt_blob,
							   gpio_offset,
							   "reg", NULL);
			if (!prop_val) {
				puts("Could not find TWSI address of npx"
				     "pca8574 GPIO from DT\n");
				return -1;
			}
			oct_bus->gpio_i2c[gpio_count] = fdt32_to_cpu(*prop_val);
			/* Get the selector on the GPIO mux if present */
			debug("%s: gpio i2c[%d] = 0x%x\n", __func__, gpio_count,
			      oct_bus->gpio_i2c[gpio_count]);
			offset = fdt_parent_offset(gd->fdt_blob,
						   gpio_offset);
			prop_val = (uint32_t *)fdt_getprop(gd->fdt_blob,
							   offset, "reg",
							   NULL);
			if (!prop_val) {
				debug("%s: No parent I2C mux\n", __func__);
				return 0;
			}

			oct_bus->gpio_parent_mux_select = fdt32_to_cpu(*prop_val);
			debug("%s: Set parent mux to 0x%x\n", __func__,
			      oct_bus->gpio_parent_mux_select);
			offset = fdt_parent_offset(gd->fdt_blob, offset);
			if (fdt_node_check_compatible(gd->fdt_blob,
						      offset,
						      "nxp,pca9548")) {
				printf("%s: Unknown MUX type\n", __func__);
				return -1;
			}

			prop_val = (uint32_t *)fdt_getprop(gd->fdt_blob,
							   offset, "reg",
							   NULL);
			if (!prop_val) {
				puts("Could not read MUX TWSI address from DT\n");
				return -1;
			}
			oct_bus->gpio_parent_mux_i2c = fdt32_to_cpu(*prop_val);
			debug("%s: GPIO parent mux I2C addr 0x%x\n", __func__,
			      oct_bus->gpio_parent_mux_i2c);
			oct_bus->gpio_type[gpio_count] = GPIO_PCA8574;
		} else {
			puts("Unknown GPIO MUX type\n");
			return -1;
		}
	}
	return 0;
}

/**
 * Initialize and add all of the MDIO devices
 */
int octeon_mdio_initialize(void)
{
	struct mii_dev *dev;
	struct octeon_mdiobus *oct_bus;
	int num_buses = 0;
	int enable_buses = 0;
	int aliases;
	int mux_offset;
	int i;
	char prop_name[16];
	int mdio_offset;
	uint32_t *pmdio_addr;

	debug("In %s\n", __func__);

	aliases = fdt_path_offset(gd->fdt_blob, "/aliases");
	if (aliases >= 0) {
		for (i = 0; i < 8; i++) {
			snprintf(prop_name, sizeof(prop_name), "smi%d", i);
			debug("Looking for property %s\n", prop_name);
			if (fdt_getprop(gd->fdt_blob, aliases, prop_name,
					NULL)) {
				debug("Found %s\n", prop_name);
				enable_buses |= 1 << i;
				num_buses = i + 1;
			}
		}
	} else {
		if (OCTEON_IS_MODEL(OCTEON_CN68XX))
			num_buses = 4;
		else if (OCTEON_IS_MODEL(OCTEON_CN38XX)
			|| OCTEON_IS_MODEL(OCTEON_CN58XX)
			|| OCTEON_IS_MODEL(OCTEON_CN30XX)
			|| OCTEON_IS_MODEL(OCTEON_CN50XX)
			|| OCTEON_IS_MODEL(OCTEON_CN31XX))
			num_buses = 1;
		else
			num_buses = 2;
	}

	debug("Initializing %d MDIO buses\n", num_buses);
	for (i = 0; i < num_buses; i++) {
		/* Skip buses not enabled */
		if (!(enable_buses & (1 << i)))
			continue;

		dev = mdio_alloc();
		oct_bus = (struct octeon_mdiobus *)calloc(sizeof(*oct_bus), 1);
		if (!dev || !oct_bus) {
			printf("Failed to allocate MDIO bus\n");
			return -1;
		}
		snprintf(dev->name, sizeof(dev->name), "mdio-octeon%d", i);
		dev->read = octeon_phy_read;
		dev->write = octeon_phy_write;
		dev->reset = octeon_phy_reset;

		dev->priv = (void *)oct_bus;
		oct_bus->mii_dev = dev;
		oct_bus->bus_id = i;
		oct_bus->local = 1;
		debug("Registering %s\n", dev->name);
		mdio_register(dev);
		debug("Enabling SMI interface %s\n", dev->name);
		cvmx_write_csr(CVMX_SMIX_EN(i), 1);

#ifdef CONFIG_SWITCH_RTL8367X
		printf("RTL8367S : SMI interface %s *MUST* put bus into clause 22 mode *without* preamble.\n", dev->name);
		cvmx_smix_clk_t smi_clk;
		/* Put bus into clause 22 mode */
		smi_clk.u64 = cvmx_read_csr(CVMX_SMIX_CLK(i));
		smi_clk.s.mode = 0;
		smi_clk.s.preamble = 0;
		cvmx_write_csr(CVMX_SMIX_CLK(i), smi_clk.u64);
#endif

	}

	/* Now deal with muxed MDIO buses */
	mux_offset = fdt_path_offset(gd->fdt_blob, "/mdio-mux");
	if (mux_offset < 0) {
		debug("%s: No muxed MDIO buses\n", __func__);
		return 0;
	}

	debug("%s: Found mdio-mux at offset 0x%x in device tree\n",
	      __func__, mux_offset);

	for (i = 0; i < (1 << MAX_GPIOS); i++) {
		snprintf(prop_name, sizeof(prop_name), "mdio@%d", i);
		mdio_offset = fdt_subnode_offset(gd->fdt_blob,
						 mux_offset, prop_name);
		if (mdio_offset < 0) {
			debug("%s: %s not found, continuing.\n", __func__,
			      prop_name);
			continue;
		}

		debug("%s: Found %s\n", __func__, prop_name);

		pmdio_addr = (uint32_t *)fdt_getprop(gd->fdt_blob,
						     mdio_offset, "reg", NULL);
		if (!pmdio_addr) {
			printf("%s: Could not get register address of %s\n",
			       __func__, prop_name);
		}

		dev = mdio_alloc();
		oct_bus = (struct octeon_mdiobus *)malloc(sizeof(*oct_bus));
		if (!dev || !oct_bus) {
			printf("Failed to allocate MDIO bus\n");
			return -1;
		}

		snprintf(dev->name, sizeof(dev->name), "mdio-mux-octeon%d", i);
		dev->read = octeon_phy_read;
		dev->write = octeon_phy_write;
		dev->reset = octeon_phy_reset;
		dev->priv = (void *)oct_bus;
		oct_bus->mii_dev = dev;
		oct_bus->gpio_value = fdt32_to_cpu(*pmdio_addr);
		debug("%s: GPIO value for %s is 0x%x\n", __func__, prop_name,
		      oct_bus->gpio_value);
		oct_bus->bus_id =
			 (oct_bus->gpio_value << 24) | OCT_REMOTE_BUS_FLAG;
		oct_bus->local = 0;

		/* This will also set the SMI bus number of oct_bus->bus_id. */
		if (octeon_mdio_get_mux_info(oct_bus, mux_offset,
					     mdio_offset)) {
			printf("%s: Error getting muxed MDIO bus information for %s\n",
			       __func__, prop_name);
			return -1;
		}
		debug("Registering %s\n", dev->name);
		mdio_register(dev);
	}
	return 0;
}

int octeon_mdio_reg_addr_to_bus(uint64_t reg_addr)
{
	switch (reg_addr) {
	case 0x1180000001800:
	case 0x1180000003800:	/* 68XX address */
		return 0;
	case 0x1180000001900:
	case 0x1180000003880:
		return 1;
	case 0x1180000003900:
		return 2;
	case 0x1180000003980:
		return 3;
	default:
		printf("%s: Unknown register address 0x%llx\n",
		       __func__, reg_addr);
		return -1;
	}
}
