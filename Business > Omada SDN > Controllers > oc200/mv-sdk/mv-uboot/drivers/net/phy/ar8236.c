
#include <linux/mii.h>
#include <dm.h>
#include <asm/gpio.h>
#include "ar8236.h"

static struct ar8236_dev data;
static const char *switch_reset_gpio="GPIO20";

static int ar8236_reg_read(struct ar8236_dev *dev, uint32_t reg_addr)
{
	const char *name = miiphy_get_current_dev();
	int reg_word_addr;
	int phy_addr, reg_val;
	unsigned short phy_val;
	unsigned short tmp_val;
	unsigned char  phy_reg;

	if (!name)
		return -ENXIO;

	/* change reg_addr to 16-bit word address, 32-bit aligned */
	reg_word_addr = (reg_addr & 0xfffffffc) >> 1;

	/* configure register high address */
	phy_addr = 0x18;
	phy_reg = 0x0;
	phy_val = (unsigned short) ((reg_word_addr >> 8) & 0x1ff);  /* bit16-8 of reg address */
	miiphy_write(name, phy_addr, phy_reg, phy_val);

	/*
	 * For some registers such as MIBs, since it is read/clear, we should
	 * read the lower 16-bit register then the higher one
	 */

	/* read register in lower address */
	phy_addr = 0x10 | ((reg_word_addr >> 5) & 0x7); /* bit7-5 of reg address */
	phy_reg = (unsigned char) (reg_word_addr & 0x1f);   /* bit4-0 of reg address */
	miiphy_read(name, phy_addr, phy_reg, &phy_val);

	/* read register in higher address */
	reg_word_addr++;
	phy_addr = 0x10 | ((reg_word_addr >> 5) & 0x7); /* bit7-5 of reg address */
	phy_reg = (unsigned char) (reg_word_addr & 0x1f);   /* bit4-0 of reg address */
	miiphy_read(name, phy_addr, phy_reg, &tmp_val);
	reg_val = (tmp_val << 16 | phy_val);

	return reg_val;
}

static int ar8236_reg_write(struct ar8236_dev *dev, uint32_t reg_addr, uint32_t reg_val)
{
	const char *name = miiphy_get_current_dev();
	int reg_word_addr;
	int phy_addr;
	unsigned short phy_val;
	unsigned char phy_reg;

	if (!name)
		return -ENXIO;

	/* change reg_addr to 16-bit word address, 32-bit aligned */
	reg_word_addr = (reg_addr & 0xfffffffc) >> 1;

	/* configure register high address */
	phy_addr = 0x18;
	phy_reg = 0x0;
	phy_val = (unsigned short) ((reg_word_addr >> 8) & 0x1ff);  /* bit16-8 of reg address */
	miiphy_write(name, phy_addr, phy_reg, phy_val);

	/*
	 * For some registers such as ARL and VLAN, since they include BUSY bit
	 * in lower address, we should write the higher 16-bit register then the
	 * lower one
	 */

	/* read register in higher address */
	reg_word_addr++;
	phy_addr = 0x10 | ((reg_word_addr >> 5) & 0x7); /* bit7-5 of reg address */
	phy_reg = (unsigned char) (reg_word_addr & 0x1f);   /* bit4-0 of reg address */
	phy_val = (unsigned short) ((reg_val >> 16) & 0xffff);
	miiphy_write(name, phy_addr, phy_reg, phy_val);

	/* write register in lower address */
	reg_word_addr--;
	phy_addr = 0x10 | ((reg_word_addr >> 5) & 0x7); /* bit7-5 of reg address */
	phy_reg = (unsigned char) (reg_word_addr & 0x1f);   /* bit4-0 of reg address */
	phy_val = (unsigned short) (reg_val & 0xffff);
	miiphy_write(name, phy_addr, phy_reg, phy_val);

	return 0;
}

static int ar8236_mii_phy_read(struct ar8236_dev *dev, int phy, int reg)
{
	int ret;
	unsigned short val;
	const char *name = miiphy_get_current_dev();

	if (!name)
		return -ENXIO;

	if (!dev)
		return -ENODEV;

	ret = miiphy_read(name, phy, reg, &val);
	if (ret < 0)
		return ret;
	else
		return (int)val;
}

static int ar8236_mii_phy_write(struct ar8236_dev *dev, int phy, int reg,
		unsigned short val)
{
	const char *name = miiphy_get_current_dev();

	if (!name)
		return -ENXIO;

	if (!dev)
		return -ENODEV;

	return miiphy_write(name, phy, reg, val);
}

static void ar8236_display_switch_info(struct ar8236_dev *dev)
{
	if (dev->id < 0) {
		printf("No Switch Device Found\n");
		return;
	}

	if (dev->id == PORT_SWITCH_ID_AR8236) {
		printf("Switch    : SOHO\n");
		printf("Series    : AR8236\n");
		printf("Product # : 0x%08x\n", dev->id);
		if (dev->cpu_port != -1)
			printf("Cpu port  : %d\n", dev->cpu_port);
	} else {
		printf("Unknown switch with Device ID: 0x%X\n", dev->id);
	}

	return;
}

static int ar8236_get_switch_id(struct ar8236_dev *dev)
{
	int phy_id;
	int phy_reg;

	phy_reg = ar8236_mii_phy_read(dev, dev->phy_addr, MII_PHYSID1);
	if (phy_reg < 0)
		return -EIO;
	
	phy_id = (phy_reg & 0xffff) << 16;
	
	phy_reg = ar8236_mii_phy_read(dev, dev->phy_addr, MII_PHYSID2);
	if (phy_reg < 0)
		return -EIO;

	phy_id |= (phy_reg & 0xffff);

	printf("Attach switch ID 0x%08x\n", phy_id);
	return phy_id;
}

static int ar8236_leds(struct ar8236_dev *dev)
{
#if 0
	int reg_val = 0;

	/* Step 1: turn on all gpio led (system/switch) */
	/* Step 1.1: switch LED on */
	reg_val = ar8236_reg_read(dev, 0x00b4); 
	ar8236_reg_write(dev, 0x00b4, (reg_val & 0xFFC0FFFF) | 0x002A0000);
	reg_val = ar8236_reg_read(dev, 0x00b0); 
	ar8236_reg_write(dev, 0x00b0, (reg_val & 0x3fff3fff) | 0x80008000);
	/* Step 1.2: turn on system */
	board_sys_led(1);
	
	mdelay(500);

	/* Step 2: turn off all gpio led (system/switch) */
	/* Step 2.1: switch LED off */
	reg_val = ar8236_reg_read(dev, 0x00b4); 
	ar8236_reg_write(dev, 0x00b4, (reg_val & 0xFFC0FFFF));
	reg_val = ar8236_reg_read(dev, 0x00b0); 
	ar8236_reg_write(dev, 0x00b0, (reg_val & 0x3fff3fff));
	/* Step 2.2: turn off system */
	board_sys_led(0);

	mdelay(500);

	/* Step 2: turn on system/switch control by hardware) */
	/* Step 3: switch control by hardware state */
	reg_val = ar8236_reg_read(dev, 0x00b4); 
	ar8236_reg_write(dev, 0x00b4, (reg_val & 0xFFC0FFFF) | 0x003F0000);
	reg_val = ar8236_reg_read(dev, 0x00b0); 
	ar8236_reg_write(dev, 0x00b0, (reg_val & 0x3fff3fff) | 0xC000C000);
	/* Step 3.1: turn on system */
	board_sys_led(1);
#endif

	return 0;
}

static int ar8236_hw_reset(void)
{
	int ret;
	unsigned int gpio;

	ret = gpio_lookup_name(switch_reset_gpio, NULL, NULL, &gpio);
	if (ret) {
		printf("GPIO: '%s' not found\n", switch_reset_gpio);
		return -1;
	}

	ret = gpio_request(gpio, "switch_reset_gpio");
	if (ret && ret != -EBUSY) {
		printf("GPIO: requesting pin %u failed\n", gpio);
		return -1;
	}

	gpio_direction_output(gpio, 0);
	mdelay(50); /* should more than 10 ms */
	gpio_direction_output(gpio, 1);
	mdelay(50);

	if (ret != -EBUSY)
		gpio_free(gpio);

	return 0;
}

static int ar8236_phy_poll_reset(struct ar8236_dev *dev, int phy)
{
	/* Poll until the reset bit clears (50ms per retry == 0.6 sec) */
	unsigned int retries = 12;
	int ret;

	do {
		udelay(50*1000);
		ret = ar8236_mii_phy_read(dev, phy, MII_BMCR);
		if (ret < 0)
			return ret;
	} while (ret & BMCR_RESET && --retries);
	if (ret & BMCR_RESET)
	{
		printf("ar8236_phy_poll_reset error for phy%d\n", phy);
		return -ETIMEDOUT;
	}

	udelay(1*1000);
	return 0;
}


int ar8236_down(void)
{
	int i = 0;

	/* phy down */
	for (i = 0; i < 5; i++) {
		ar8236_mii_phy_write(&data, data.phy_addr+i, MII_BMCR, BMCR_PDOWN);
	}

	return 0;
}

int ar8236_initialize(const void *blob)
{
	int val = 0;
	int node = 0;
	int ret = 0;
	int i = 0;

	/* Read Device Tree */
	node = fdt_node_offset_by_compatible(blob, -1, "atheros,ar8236");
	if (node == -FDT_ERR_NOTFOUND)
		return -ENXIO;

	/* Check whether switch node is enabled */
	ret = fdtdec_get_is_enabled(blob, node);
	if (ret == 0)
		return -EACCES;

	/* Initizalize Switch Device Structure */
	data.phy_addr = fdtdec_get_uint(blob, node, "phy-addr", 0);
	data.port_mask = fdtdec_get_int(blob, node, "port-mask", 0);

	/* should hw reset before use SMI interface of AR8236 */
	ar8236_hw_reset();

	data.id = ar8236_get_switch_id(&data);
	if (data.id != PORT_SWITCH_ID_AR8236)
		return -ENODEV;

	printf("Attach switch driver for AR8236\n");

	data.cpu_port = fdtdec_get_int(blob, node, "cpu-port", -1);
	if (data.cpu_port == -1)
	{
		printf("*ERROR*: cpu-port should not be -1\n");
		return -ENXIO;
	}
	
	/* Reset the switch before initialization */
	ar8236_reg_write(&data, AR8236_REG_CTRL, AR8236_CTRL_RESET);
	do {
		udelay(10);
		val = ar8236_reg_read(&data, AR8236_REG_CTRL);
	} while (val & AR8236_CTRL_RESET);

	/* phy initialize */
	for (i = 0; i < 5; i++) {
		ar8236_mii_phy_write(&data, data.phy_addr+i, MII_ADVERTISE,
			ADVERTISE_ALL | ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM);

		ar8236_mii_phy_write(&data, data.phy_addr+i, MII_BMCR, BMCR_RESET | BMCR_ANENABLE);
		ar8236_phy_poll_reset(&data, data.phy_addr+i);
	}
	
	/* config MII PHY mode */
	ar8236_reg_write(&data, 0x2c, 0x7e3f003f);
	ar8236_reg_write(&data, 0x4, 0x500);
	
	/* Enable MIB counters */
	val = ar8236_reg_read(&data, AR8236_REG_MIB_FUNC);
	val |= AR8236_MIB_EN;
	ar8236_reg_write(&data, AR8236_REG_MIB_FUNC, val);

	for (i = 0; i < 6; i++) {
		/* Enable port learning and tx */
		ar8236_reg_write(&data, AR8236_REG_PORT_CTRL(i),
			AR8236_PORT_CTRL_LEARN |
			(4 << AR8236_PORT_CTRL_STATE_S));
		
		if (i == data.cpu_port)
		{
			/* CPU port is forced link-up, full-duplex and 100MB speed */
			ar8236_reg_write(&data, AR8236_REG_PORT_STATUS(i),
				AR8236_PORT_STATUS_LINK_UP |
				AR8236_PORT_SPEED_100M |
				AR8236_PORT_STATUS_TXMAC |
				AR8236_PORT_STATUS_RXMAC |
				AR8236_PORT_STATUS_DUPLEX);
		}
		else
		{
			ar8236_reg_write(&data, AR8236_REG_PORT_STATUS(i),
				AR8236_PORT_STATUS_LINK_AUTO | AR8236_PORT_STATUS_LINK_FLOW_EN | AR8236_PORT_STATUS_TX_HALF_FLOW);
		}
	}

	ar8236_leds(&data);

	return 0;
}

static int ar8236_sw_options(char *str)
{
	if (strcmp(str, "info") == 0)
		return AR8236_SW_INFO;
	else if (strcmp(str, "read") == 0)
		return AR8236_SW_READ;
	else if (strcmp(str, "write") == 0)
		return AR8236_SW_WRITE;
	else if (strcmp(str, "led") == 0)
		return AR8236_SW_LED;
	else
		return AR8236_SW_NA;
}

static int ar8236_do_sw(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	struct ar8236_dev *dev;
	int reg, val = 0, ret = 0;

	dev = &data;

	if (!dev) {
		printf("Switch Device not found\n");
		return -ENODEV;
	}

	switch (ar8236_sw_options(argv[1])) {
	case AR8236_SW_INFO:
		ar8236_display_switch_info(dev);
		break;

	case AR8236_SW_READ:
		if (argc < 3) {
			printf("Syntax Error: switch read <reg>\n");
			return 1;
		}

		reg = (int)simple_strtoul(argv[2], NULL, 16);
		ret = ar8236_reg_read(dev, reg);
		printf("Read - switch reg: 0x%X, val: 0x%X\n", reg, ret);
		break;

	case AR8236_SW_WRITE:
		if (argc < 4) {
			printf("Syntax Error: switch write <reg> <val>\n");
			return 1;
		}

		reg  = (int)simple_strtoul(argv[2], NULL, 16);
		val  = (int)simple_strtoul(argv[3], NULL, 16);

		ret = ar8236_reg_write(dev, reg, val);

		printf("Write - switch reg: 0x%X, val: 0x%X\n", reg, val);
		break;

	case AR8236_SW_LED:
		ar8236_leds(dev);
		break;

	case AR8236_SW_NA:
		printf("\"switch %s\" - Wrong command. Try \"help switch\"\n",
		       argv[1]);

	default:
		break;
	}
	return 0;
}

/***************************************************/
U_BOOT_CMD(
	switch,	4,	1,	ar8236_do_sw,
	"Switch Access commands",
	"switch info - Display switch information\n"
	"switch read <reg> - read switch register <reg>\n"
	"switch write <reg> <val> - write <val> to switch register <reg>\n"
);
