/*
 * Vitesse PHY drivers
 *
 * Copyright 2010-2012 Freescale Semiconductor, Inc.
 * Author: Andy Fleming
 * Add vsc8662 phy support - Priyanka Jain
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <miiphy.h>

/* Cicada Auxiliary Control/Status Register */
#define MIIM_CIS82xx_AUX_CONSTAT	0x1c
#define MIIM_CIS82xx_AUXCONSTAT_INIT	0x0004
#define MIIM_CIS82xx_AUXCONSTAT_DUPLEX	0x0020
#define MIIM_CIS82xx_AUXCONSTAT_SPEED	0x0018
#define MIIM_CIS82xx_AUXCONSTAT_GBIT	0x0010
#define MIIM_CIS82xx_AUXCONSTAT_100	0x0008

/* Cicada Extended Control Register 1 */
#define MIIM_CIS82xx_EXT_CON1		0x17
#define MIIM_CIS8201_EXTCON1_INIT	0x0000

/* Cicada 8204 Extended PHY Control Register 1 */
#define MIIM_CIS8204_EPHY_CON		0x17
#define MIIM_CIS8204_EPHYCON_INIT	0x0006
#define MIIM_CIS8204_EPHYCON_RGMII	0x1100

/* Cicada 8204 Serial LED Control Register */
#define MIIM_CIS8204_SLED_CON		0x1b
#define MIIM_CIS8204_SLEDCON_INIT	0x1115

/* Vitesse VSC8601 Extended PHY Control Register 1 */
#define MIIM_VSC8601_EPHY_CON		0x17
#define MIIM_VSC8601_EPHY_CON_INIT_SKEW	0x1120
#define MIIM_VSC8601_SKEW_CTRL		0x1c

#define PHY_EXT_PAGE_ACCESS    0x1f
#define PHY_EXT_PAGE_ACCESS_GENERAL	0x10
#define PHY_EXT_PAGE_ACCESS_EXTENDED3	0x3

/* Vitesse VSC8574 control register */
#define MIIM_VSC8574_MAC_SERDES_CON	0x10
#define MIIM_VSC8574_MAC_SERDES_ANEG	0x80
#define MIIM_VSC8574_GENERAL18		0x12
#define MIIM_VSC8574_GENERAL19		0x13

/* Vitesse VSC8574 gerenal purpose register 18 */
#define MIIM_VSC8574_18G_SGMII		0x80f0
#define MIIM_VSC8574_18G_QSGMII		0x80e0
#define MIIM_VSC8574_18G_CMDERR		0x4000
#define MIIM_VSC8574_18G_CMDSTAT	0x8000

/* CIS8201 */
static int vitesse_config(struct phy_device *phydev)
{
	/* Override PHY config settings */
	phy_write(phydev, MDIO_DEVAD_NONE, MIIM_CIS82xx_AUX_CONSTAT,
			MIIM_CIS82xx_AUXCONSTAT_INIT);
	/* Set up the interface mode */
	phy_write(phydev, MDIO_DEVAD_NONE, MIIM_CIS82xx_EXT_CON1,
			MIIM_CIS8201_EXTCON1_INIT);

	genphy_config_aneg(phydev);

	return 0;
}

static int vitesse_parse_status(struct phy_device *phydev)
{
	int speed;
	int mii_reg;

	mii_reg = phy_read(phydev, MDIO_DEVAD_NONE, MIIM_CIS82xx_AUX_CONSTAT);

	if (mii_reg & MIIM_CIS82xx_AUXCONSTAT_DUPLEX)
		phydev->duplex = DUPLEX_FULL;
	else
		phydev->duplex = DUPLEX_HALF;

	speed = mii_reg & MIIM_CIS82xx_AUXCONSTAT_SPEED;
	switch (speed) {
	case MIIM_CIS82xx_AUXCONSTAT_GBIT:
		phydev->speed = SPEED_1000;
		break;
	case MIIM_CIS82xx_AUXCONSTAT_100:
		phydev->speed = SPEED_100;
		break;
	default:
		phydev->speed = SPEED_10;
		break;
	}

	return 0;
}

static int vitesse_startup(struct phy_device *phydev)
{
	genphy_update_link(phydev);
	vitesse_parse_status(phydev);

	return 0;
}

static int cis8204_config(struct phy_device *phydev)
{
	/* Override PHY config settings */
	phy_write(phydev, MDIO_DEVAD_NONE, MIIM_CIS82xx_AUX_CONSTAT,
			MIIM_CIS82xx_AUXCONSTAT_INIT);

	genphy_config_aneg(phydev);

	if ((phydev->interface == PHY_INTERFACE_MODE_RGMII) ||
			(phydev->interface == PHY_INTERFACE_MODE_RGMII) ||
			(phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID) ||
			(phydev->interface == PHY_INTERFACE_MODE_RGMII_RXID))
		phy_write(phydev, MDIO_DEVAD_NONE, MIIM_CIS8204_EPHY_CON,
				MIIM_CIS8204_EPHYCON_INIT |
				MIIM_CIS8204_EPHYCON_RGMII);
	else
		phy_write(phydev, MDIO_DEVAD_NONE, MIIM_CIS8204_EPHY_CON,
				MIIM_CIS8204_EPHYCON_INIT);

	return 0;
}

/* Vitesse VSC8601 */
static int vsc8601_config(struct phy_device *phydev)
{
	/* Configure some basic stuff */
#ifdef CONFIG_SYS_VSC8601_SKEWFIX
	phy_write(phydev, MDIO_DEVAD_NONE, MIIM_VSC8601_EPHY_CON,
			MIIM_VSC8601_EPHY_CON_INIT_SKEW);
#if defined(CONFIG_SYS_VSC8601_SKEW_TX) && defined(CONFIG_SYS_VSC8601_SKEW_RX)
	phy_write(phydev, MDIO_DEVAD_NONE, PHY_EXT_PAGE_ACCESS, 1);
#define VSC8101_SKEW \
	((CONFIG_SYS_VSC8601_SKEW_TX << 14) \
	| (CONFIG_SYS_VSC8601_SKEW_RX << 12))
	phy_write(phydev, MDIO_DEVAD_NONE, MIIM_VSC8601_SKEW_CTRL,
			VSC8101_SKEW);
	phy_write(phydev, MDIO_DEVAD_NONE, PHY_EXT_PAGE_ACCESS, 0);
#endif
#endif

	genphy_config_aneg(phydev);

	return 0;
}

static int vsc8574_config(struct phy_device *phydev)
{
	u32 val;
	int wait;
	debug("%s(%s)\n", __func__, phydev->drv->name);
	/* configure regiser 19G for MAC */
	phy_write(phydev, MDIO_DEVAD_NONE, PHY_EXT_PAGE_ACCESS,
		  PHY_EXT_PAGE_ACCESS_GENERAL);

	val = phy_read(phydev, MDIO_DEVAD_NONE, MIIM_VSC8574_GENERAL19);
	if (phydev->interface == PHY_INTERFACE_MODE_QSGMII) {
		debug("  QSGMII mode\n");
		/* set bit 15:14 to '01' for QSGMII mode */
		val = (val & 0x3fff) | (1 << 14);
		phy_write(phydev, MDIO_DEVAD_NONE,
			  MIIM_VSC8574_GENERAL19, val);
		/* Enable 4 ports MAC QSGMII */
		phy_write(phydev, MDIO_DEVAD_NONE, MIIM_VSC8574_GENERAL18,
			  MIIM_VSC8574_18G_QSGMII);
	} else {
		debug("  SGMII mode\n");
		/* set bit 15:14 to '00' for SGMII mode */
		val = val & 0x3fff;
		phy_write(phydev, MDIO_DEVAD_NONE, MIIM_VSC8574_GENERAL19, val);
		/* Enable 4 ports MAC SGMII */
		phy_write(phydev, MDIO_DEVAD_NONE, MIIM_VSC8574_GENERAL18,
			  MIIM_VSC8574_18G_SGMII);
	}
	/* When bit 15 is cleared the command has completed */
	debug("%s(%s) 1\n", __func__, phydev->drv->name);
	wait = 300;
	do {
		val = phy_read(phydev, MDIO_DEVAD_NONE, MIIM_VSC8574_GENERAL18);
		debug("  cmd status: 0x%x\n", val);
		mdelay(1);
	} while ((val & (MIIM_VSC8574_18G_CMDSTAT | MIIM_VSC8574_18G_CMDERR))
		 && --wait);

	if (val & MIIM_VSC8574_18G_CMDERR) {
		printf("Error resetting PHY %s\n", phydev->dev->name);
		return -1;
	}
	if (!wait) {
		printf("Reset of phy %s timed out\n", phydev->dev->name);
		return -1;
	}
	debug("%s(%s) 2\n", __func__, phydev->drv->name);
	/* Enable Serdes Auto-negotiation */
	phy_write(phydev, MDIO_DEVAD_NONE, PHY_EXT_PAGE_ACCESS,
		  PHY_EXT_PAGE_ACCESS_EXTENDED3);
	val = phy_read(phydev, MDIO_DEVAD_NONE, MIIM_VSC8574_MAC_SERDES_CON);
	val = val | MIIM_VSC8574_MAC_SERDES_ANEG;
	phy_write(phydev, MDIO_DEVAD_NONE, MIIM_VSC8574_MAC_SERDES_CON, val);

	phy_write(phydev, MDIO_DEVAD_NONE, PHY_EXT_PAGE_ACCESS, 0);

	genphy_config_aneg(phydev);
	debug("%s(%s) 3\n", __func__, phydev->drv->name);

	return 0;
}

static struct phy_driver VSC8211_driver = {
	.name	= "Vitesse VSC8211",
	.uid	= 0xfc4b0,
	.mask	= 0xffff0,
	.features = PHY_GBIT_FEATURES,
	.config = &vitesse_config,
	.startup = &vitesse_startup,
	.shutdown = &genphy_shutdown,
};

static struct phy_driver VSC8221_driver = {
	.name = "Vitesse VSC8221",
	.uid = 0xfc550,
	.mask = 0xffff0,
	.features = PHY_GBIT_FEATURES,
	.config = &genphy_config_aneg,
	.startup = &vitesse_startup,
	.shutdown = &genphy_shutdown,
};

static struct phy_driver VSC8244_driver = {
	.name = "Vitesse VSC8244",
	.uid = 0xfc6c0,
	.mask = 0xffff0,
	.features = PHY_GBIT_FEATURES,
	.config = &genphy_config_aneg,
	.startup = &vitesse_startup,
	.shutdown = &genphy_shutdown,
};

static struct phy_driver VSC8234_driver = {
	.name = "Vitesse VSC8234",
	.uid = 0xfc620,
	.mask = 0xffff0,
	.features = PHY_GBIT_FEATURES,
	.config = &genphy_config_aneg,
	.startup = &vitesse_startup,
	.shutdown = &genphy_shutdown,
};

static struct phy_driver VSC8574_driver = {
	.name = "Vitesse VSC8574",
	.uid = 0x704a0,
	.mask = 0xffff0,
	.features = PHY_GBIT_FEATURES,
	.config = &vsc8574_config,
	.startup = &vitesse_startup,
	.shutdown = &genphy_shutdown,
};

static struct phy_driver VSC8601_driver = {
	.name = "Vitesse VSC8601",
	.uid = 0x70420,
	.mask = 0xffff0,
	.features = PHY_GBIT_FEATURES,
	.config = &vsc8601_config,
	.startup = &vitesse_startup,
	.shutdown = &genphy_shutdown,
};

static struct phy_driver VSC8641_driver = {
	.name = "Vitesse VSC8641",
	.uid = 0x70430,
	.mask = 0xffff0,
	.features = PHY_GBIT_FEATURES,
	.config = &genphy_config_aneg,
	.startup = &vitesse_startup,
	.shutdown = &genphy_shutdown,
};

static struct phy_driver VSC8662_driver = {
	.name = "Vitesse VSC8662",
	.uid = 0x70660,
	.mask = 0xffff0,
	.features = PHY_GBIT_FEATURES,
	.config = &genphy_config_aneg,
	.startup = &vitesse_startup,
	.shutdown = &genphy_shutdown,
};

/* Vitesse bought Cicada, so we'll put these here */
static struct phy_driver cis8201_driver = {
	.name = "CIS8201",
	.uid = 0xfc410,
	.mask = 0xffff0,
	.features = PHY_GBIT_FEATURES,
	.config = &vitesse_config,
	.startup = &vitesse_startup,
	.shutdown = &genphy_shutdown,
};

static struct phy_driver cis8204_driver = {
	.name = "Cicada Cis8204",
	.uid = 0xfc440,
	.mask = 0xffff0,
	.features = PHY_GBIT_FEATURES,
	.config = &cis8204_config,
	.startup = &vitesse_startup,
	.shutdown = &genphy_shutdown,
};

int phy_vitesse_init(void)
{
	phy_register(&VSC8641_driver);
	phy_register(&VSC8601_driver);
	phy_register(&VSC8234_driver);
	phy_register(&VSC8244_driver);
	phy_register(&VSC8211_driver);
	phy_register(&VSC8221_driver);
	phy_register(&VSC8574_driver);
	phy_register(&VSC8662_driver);
	phy_register(&cis8201_driver);
	phy_register(&cis8204_driver);

	return 0;
}
