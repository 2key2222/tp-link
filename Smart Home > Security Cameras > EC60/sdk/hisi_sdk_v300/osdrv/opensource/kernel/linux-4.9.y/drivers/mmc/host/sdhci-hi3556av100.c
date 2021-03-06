/*
 * Copyright (c) 2017-2018 HiSilicon Technologies Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#define REG_EMMC_DRV_DLL_CTRL		0x1b0
#define REG_SDIO0_DRV_DLL_CTRL		0x1d4
#define REG_SDIO1_DRV_DLL_CTRL		0x1fc
#define REG_SDIO2_DRV_DLL_CTRL          /* no sdio2 */
#define SDIO_DRV_PHASE_SEL_MASK		(0x1f << 24)
#define sdio_drv_sel(phase)		((phase) << 24)

#define REG_EMMC_DRV_DLL_STATUS		0x1c4
#define REG_SDIO0_DRV_DLL_STATUS	0x1e8
#define REG_SDIO1_DRV_DLL_STATUS	0x210
#define REG_SDIO2_DRV_DLL_STATUS        /* no sdio2 */
#define SDIO_DRV_DLL_LOCK		BIT(15)

#define REG_EMMC_SAMPL_DLL_STATUS	0x1bc
#define REG_SDIO0_SAMPL_DLL_STATUS	0x1e0
#define REG_SDIO1_SAMPL_DLL_STATUS	0x208
#define REG_SDIO2_SAMPL_DLL_STATUS      /* no sdio2 */
#define SDIO_SAMPL_DLL_SLAVE_READY	BIT(14)

#define REG_EMMC_SAMPL_DLL_CTRL		0x1a8
#define REG_SDIO0_SAMPL_DLL_CTRL	0x1ec
#define REG_SDIO1_SAMPL_DLL_CTRL	0x214
#define REG_SDIO2_SAMPL_DLL_CTRL        /* no sdio2 */
#define SDIO_SAMPL_DLL_SLAVE_EN		BIT(16)

#define REG_EMMC_SAMPLB_DLL_CTRL	0x1ac
#define REG_SDIO0_SAMPLB_DLL_CTRL	0x1d0
#define REG_SDIO1_SAMPLB_DLL_CTRL	0x1f8
#define REG_SDIO2_SAMPLB_DLL_CTRL       /* no sdio2 */
#define SDIO_SAMPLB_DLL_CLK_MASK	(0x1f << 24)
#define sdio_samplb_sel(phase)		((phase) << 24)

#define REG_EMMC_DS_DLL_CTRL		0x1b4
#define EMMC_DS_DLL_MODE_SSEL		BIT(13)
#define EMMC_DS_DLL_SSEL_MASK		0x1fff
#define REG_EMMC_DS180_DLL_CTRL		0x1b8
#define EMMC_DS180_DLL_BYPASS		BIT(15)
#define REG_EMMC_DS_DLL_STATUS		0x1c8
#define EMMC_DS_DLL_LOCK		BIT(15)
#define EMMC_DS_DLL_MDLY_TAP_MASK	0x1fff

#define REG_MISC_CTRL1          0x4
#define SDIO1_PD_MUX_BYPASS     BIT(9)
#define SDIO0_PD_MUX_BYPASS     BIT(8)

#define REG_MISC_CTRL18			0x48
#define SDIO0_PWRSW_SEL_1V8		BIT(5)
#define SDIO0_PWR_EN			BIT(4)
#define SDIO0_IO_MODE_SEL_1V8	BIT(1)
#define SDIO0_PWR_CTRL_BY_MISC	BIT(0)

#define REG_IOCTL_RONSEL_1_0		0x264
#define REG_IOCTL_OD_RONSEL_2		0x268

#define REG_CTRL_SDIO0_CLK		0x006c
#define REG_CTRL_SDIO0_CMD		0x0070
#define REG_CTRL_SDIO0_DATA0	0x0074
#define REG_CTRL_SDIO0_DATA1	0x0078
#define REG_CTRL_SDIO0_DATA2	0x007c
#define REG_CTRL_SDIO0_DATA3	0x0080
#define REG_CTRL_SDIO1_CLK		0x0084
#define REG_CTRL_SDIO1_CMD		0x0088
#define REG_CTRL_SDIO1_DATA0	0x008c
#define REG_CTRL_SDIO1_DATA1	0x0090
#define REG_CTRL_SDIO1_DATA2	0x0094
#define REG_CTRL_SDIO1_DATA3	0x0098


/* SD drive capability */
static unsigned int sd_sdr104_drv[]   = {0x60, 0x20, 0x20, 0x20, 0x20, 0x20};
static unsigned int sd_sdr50_drv[]    = {0x60, 0x20, 0x20, 0x20, 0x20, 0x20};
static unsigned int sd_sdr25_hs_drv[] = {0x60, 0x20, 0x20, 0x20, 0x20, 0x20};
static unsigned int sd_other_drv[]    = {0x60, 0x20, 0x20, 0x20, 0x20, 0x20};

/* SDIO drive capability */
#ifndef CONFIG_HISI_MC /* hi3519av100 SMP */
static unsigned int sdio_sdr104_drv[]   = {0x60, 0x20, 0x20, 0x20, 0x20, 0x20};
#else /*  hi3519av100 hi3556av100 AMP */
static unsigned int sdio_sdr104_drv[]   = {0xc0, 0x90, 0x90, 0x90, 0x90, 0x90};
#endif
static unsigned int sdio_sdr50_drv[]    = {0x60, 0x20, 0x20, 0x20, 0x20, 0x20};
static unsigned int sdio_sdr25_hs_drv[] = {0x60, 0x20, 0x20, 0x20, 0x20, 0x20};
static unsigned int sdio_other_drv[]    = {0x60, 0x20, 0x20, 0x20, 0x20, 0x20};


struct sdhci_hisi_priv {
	struct reset_control *crg_rst;
	struct reset_control *dll_rst;
	struct reset_control *sampl_rst;
	struct regmap *crg_regmap;
	struct regmap *misc_regmap;
	struct regmap *iocfg_regmap;
	void __iomem *phy_addr;
	unsigned int f_max;
	unsigned int devid;
	unsigned int drv_phase;
	unsigned int sampl_phase;
	unsigned int tuning_phase;
};

static void hisi_set_pd_pin_status(struct regmap *misc)
{
	unsigned int ctrl = 0;

	if (misc == NULL)
		return;

	regmap_read(misc, REG_MISC_CTRL1, &ctrl);
	ctrl &= ~(SDIO1_PD_MUX_BYPASS | SDIO0_PD_MUX_BYPASS);
	regmap_write(misc, REG_MISC_CTRL1, ctrl);
}

static int hisi_set_signal_voltage_3v3(struct sdhci_host *host)
{
	struct sdhci_hisi_priv *hisi_priv = sdhci_get_pltfm_priv(host);
	struct regmap *misc = hisi_priv->misc_regmap;
	unsigned int ctrl = 0;

	pr_debug("%s: set voltage to 330\n", mmc_hostname(host->mmc));

	if (hisi_priv->devid == 1) {
		regmap_read(misc, REG_MISC_CTRL18, &ctrl);
		ctrl |= SDIO0_PWR_CTRL_BY_MISC | SDIO0_PWR_EN;
		ctrl &= ~SDIO0_IO_MODE_SEL_1V8;
		regmap_write(misc, REG_MISC_CTRL18, ctrl);

		usleep_range(1000, 2000); /* Sleep between 1000 and 2000us */
		ctrl &= ~SDIO0_PWRSW_SEL_1V8;
		regmap_write(misc, REG_MISC_CTRL18, ctrl);

		regmap_read(misc, REG_MISC_CTRL18, &ctrl);
		if ((ctrl & SDIO0_PWR_CTRL_BY_MISC)
				&& (ctrl & SDIO0_PWR_EN)
				&& !(ctrl & SDIO0_IO_MODE_SEL_1V8) &&
				!(ctrl & SDIO0_PWRSW_SEL_1V8))
			return 0;
	}

	pr_warn("%s: 3.3V output did not became stable\n",
			mmc_hostname(host->mmc));

	return -EAGAIN;
}

static int hisi_set_signal_voltage_1v8(struct sdhci_host *host)
{
	struct sdhci_hisi_priv *hisi_priv = sdhci_get_pltfm_priv(host);
	struct regmap *misc = hisi_priv->misc_regmap;
	unsigned int ctrl = 0;

	pr_debug("%s: set voltage to 180\n", mmc_hostname(host->mmc));

	if (hisi_priv->devid == 0)
		return 0;

	if (hisi_priv->devid == 1) {
		regmap_read(misc, REG_MISC_CTRL18, &ctrl);
		ctrl |= SDIO0_PWRSW_SEL_1V8;
		regmap_write(misc, REG_MISC_CTRL18, ctrl);

		usleep_range(1000, 2000); /* Sleep between 1000 and 2000us */

		ctrl |= SDIO0_IO_MODE_SEL_1V8;
		regmap_write(misc, REG_MISC_CTRL18, ctrl);

		regmap_read(misc, REG_MISC_CTRL18, &ctrl);
		if ((ctrl & SDIO0_PWRSW_SEL_1V8) &&
		    (ctrl & SDIO0_IO_MODE_SEL_1V8))
			return 0;
	}

	if (hisi_priv->devid == 2) /* for device id 2 */
		return 0;

	pr_warn("%s: 1.8V output did not became stable\n",
			mmc_hostname(host->mmc));

	return -EAGAIN;
}

static void sdhci_hisi_hs400_enhanced_strobe(struct mmc_host *mmc, struct mmc_ios *ios)
{
	u32 ctrl;
	struct sdhci_host *host = mmc_priv(mmc);

	ctrl = sdhci_readl(host, SDHCI_EMMC_CTRL);
	if (ios->enhanced_strobe)
		ctrl |= SDHCI_ENH_STROBE_EN;
	else
		ctrl &= ~SDHCI_ENH_STROBE_EN;

	sdhci_writel(host, ctrl, SDHCI_EMMC_CTRL);
}

static int sdhci_hisi_pltfm_init(struct platform_device *pdev, struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_hisi_priv *hisi_priv = sdhci_pltfm_priv(pltfm_host);
	struct device_node *np = pdev->dev.of_node;
	struct clk *clk = NULL;
	int ret;

	hisi_priv->crg_rst = devm_reset_control_get(&pdev->dev, "crg_reset");
	if (IS_ERR_OR_NULL(hisi_priv->crg_rst)) {
		dev_err(&pdev->dev, "get crg_rst failed.\n");
		return PTR_ERR(hisi_priv->crg_rst);
	}

	hisi_priv->dll_rst = devm_reset_control_get(&pdev->dev, "dll_reset");
	if (IS_ERR_OR_NULL(hisi_priv->dll_rst)) {
		dev_err(&pdev->dev, "get dll_rst failed.\n");
		return PTR_ERR(hisi_priv->dll_rst);
	}

	hisi_priv->sampl_rst = devm_reset_control_get(&pdev->dev, "sampl_reset");
	if (IS_ERR_OR_NULL(hisi_priv->sampl_rst)) {
		dev_err(&pdev->dev, "get sampl_rst failed.\n");
		return PTR_ERR(hisi_priv->sampl_rst);
	}

	hisi_priv->crg_regmap = syscon_regmap_lookup_by_phandle(np, "crg_regmap");
	if (IS_ERR(hisi_priv->crg_regmap)) {
		dev_err(&pdev->dev, "get crg regmap failed.\n");
		return PTR_ERR(hisi_priv->crg_regmap);
	}

	if (of_property_read_u32(np, "devid", &hisi_priv->devid))
		return -EINVAL;

	if (hisi_priv->devid == 0) {
		struct resource *res;

		res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
		if (!res)
			return -ENOMEM;

		hisi_priv->phy_addr = devm_ioremap_resource(&pdev->dev, res);
		if (IS_ERR(hisi_priv->phy_addr))
			return PTR_ERR(hisi_priv->phy_addr);
	} else {
		hisi_priv->iocfg_regmap = syscon_regmap_lookup_by_phandle(np,
				"iocfg_regmap");
		if (IS_ERR(hisi_priv->iocfg_regmap))
			return PTR_ERR(hisi_priv->iocfg_regmap);

		hisi_priv->misc_regmap = syscon_regmap_lookup_by_phandle(np,
				"misc_regmap");
		if (IS_ERR(hisi_priv->misc_regmap))
			return PTR_ERR(hisi_priv->misc_regmap);

		hisi_set_pd_pin_status(hisi_priv->misc_regmap);
	}

	clk = devm_clk_get(mmc_dev(host->mmc), "mmc_clk");
	if (IS_ERR_OR_NULL(clk)) {
		dev_err(mmc_dev(host->mmc), "get clk err\n");
		return -EINVAL;
	}

	pltfm_host->clk = clk;

	hisi_mmc_crg_init(host);
	ret = sdhci_hisi_parse_dt(host);
	if (ret)
		return ret;
	/*
	 * only eMMC has a hw reset, and now eMMC signaling
	 * is fixed to 180
	 */
	if (host->mmc->caps & MMC_CAP_HW_RESET) {
		host->flags &= ~SDHCI_SIGNALING_330;
		host->flags |= SDHCI_SIGNALING_180;
	}

	/*
	 * we parse the support timings from dts, so we read the
	 * host capabilities early and clear the timing capabilities,
	 * SDHCI_QUIRK_MISSING_CAPS is set so that sdhci driver would
	 * not read it again
	 */
	host->caps = sdhci_readl(host, SDHCI_CAPABILITIES);
	host->caps &= ~(SDHCI_CAN_DO_HISPD);
	host->caps1 = sdhci_readl(host, SDHCI_CAPABILITIES_1);
	host->caps1 &= ~(SDHCI_SUPPORT_SDR50 | SDHCI_SUPPORT_SDR104 |
				SDHCI_SUPPORT_DDR50 | SDHCI_CAN_DO_ADMA3);
	host->quirks |= SDHCI_QUIRK_MISSING_CAPS |
			SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC |
			SDHCI_QUIRK_SINGLE_POWER_WRITE;

	host->caps1 |= SDHCI_USE_SDR50_TUNING;
	host->mmc_host_ops.hs400_enhanced_strobe =
				sdhci_hisi_hs400_enhanced_strobe;

	mci_host[slot_index++] = host->mmc;

	return 0;
}

static void hisi_wait_ds_dll_lock(struct sdhci_host *host)
{
	struct sdhci_hisi_priv *hisi_priv = sdhci_get_pltfm_priv(host);
	unsigned int reg;
	unsigned int timeout = 20; /* default timeout 20ms */

	do {
		reg = 0;
		regmap_read(hisi_priv->crg_regmap, REG_EMMC_DS_DLL_STATUS, &reg);
		if (reg & EMMC_DS_DLL_LOCK)
			return;

		mdelay(1);
		timeout--;
	} while (timeout > 0);

	pr_err("%s: DS DLL master not locked.\n", mmc_hostname(host->mmc));
}

static void hisi_wait_ds_180_dll_ready(struct sdhci_host *host)
{
	/* Do nothing */
}

static void hisi_set_ds_dll_delay(struct sdhci_host *host)
{
	/* Do nothing */
}

static int sdhci_hisi_start_signal_voltage_switch(struct sdhci_host *host, struct mmc_ios *ios)
{
	switch (ios->signal_voltage) {
	case MMC_SIGNAL_VOLTAGE_330:
		if (!(host->flags & SDHCI_SIGNALING_330))
			return -EINVAL;
		return hisi_set_signal_voltage_3v3(host);
	case MMC_SIGNAL_VOLTAGE_180:
		if (!(host->flags & SDHCI_SIGNALING_180))
			return -EINVAL;
		return hisi_set_signal_voltage_1v8(host);
	default:
		/* No signal voltage switch required */
		return 0;
	}
}

static void hisi_host_extra_init(struct sdhci_host *host)
{
	unsigned short ctrl;
	unsigned int mbiiu_ctrl, val;

	ctrl = sdhci_readw(host, SDHCI_MSHC_CTRL);
	ctrl &= ~SDHCI_CMD_CONFLIT_CHECK;
	sdhci_writew(host, ctrl, SDHCI_MSHC_CTRL);

	mbiiu_ctrl = sdhci_readl(host, SDHCI_AXI_MBIIU_CTRL);
	mbiiu_ctrl &= ~(SDHCI_GM_WR_OSRC_LMT_MASK | SDHCI_GM_RD_OSRC_LMT_MASK);
	mbiiu_ctrl |= (SDHCI_GM_WR_OSRC_LMT_SEL(0x7)
			| SDHCI_GM_RD_OSRC_LMT_SEL(0x7));
	sdhci_writel(host, mbiiu_ctrl, SDHCI_AXI_MBIIU_CTRL);

	val = sdhci_readl(host, SDHCI_MULTI_CYCLE);
	val |= SDHCI_EDGE_DETECT_EN | SDHCI_DOUT_EN_F_EDGE;

	sdhci_writel(host, val, SDHCI_MULTI_CYCLE);
	host->error_count = 0;
}

static void hisi_set_sd_iocfg(struct sdhci_host *host)
{
	struct sdhci_hisi_priv *hisi_priv = sdhci_get_pltfm_priv(host);
	void *iocfg_regmap = hisi_priv->iocfg_regmap;
	unsigned int reg_addr;
	unsigned int *pin_drv_cap = NULL;

	if (host->timing == MMC_TIMING_UHS_SDR104)
		pin_drv_cap = sd_sdr104_drv;
	else if (host->timing == MMC_TIMING_UHS_SDR50)
		pin_drv_cap = sd_sdr50_drv;
	else if (host->timing == MMC_TIMING_UHS_SDR25 ||
		 host->timing == MMC_TIMING_SD_HS)
		pin_drv_cap = sd_sdr25_hs_drv;
	else
		pin_drv_cap = sd_other_drv;

	for (reg_addr = REG_CTRL_SDIO0_CLK;
		reg_addr <= REG_CTRL_SDIO0_DATA3; reg_addr += 0x4) {
		regmap_write_bits(iocfg_regmap, reg_addr, 0xf0, *pin_drv_cap);
		pin_drv_cap++;
	}
}

static void hisi_set_sdio_iocfg(struct sdhci_host *host)
{
	struct sdhci_hisi_priv *hisi_priv = sdhci_get_pltfm_priv(host);
	void *iocfg_regmap = hisi_priv->iocfg_regmap;
	unsigned int reg_addr;
	unsigned int *pin_drv_cap = NULL;

	if (host->timing == MMC_TIMING_UHS_SDR104)
		pin_drv_cap = sdio_sdr104_drv;
	else if (host->timing == MMC_TIMING_UHS_SDR50)
		pin_drv_cap = sdio_sdr50_drv;
	else if (host->timing == MMC_TIMING_UHS_SDR25 ||
		 host->timing == MMC_TIMING_SD_HS)
		pin_drv_cap = sdio_sdr25_hs_drv;
	else
		pin_drv_cap = sdio_other_drv;

	for (reg_addr = REG_CTRL_SDIO1_CLK;
		reg_addr <= REG_CTRL_SDIO1_DATA3; reg_addr += 0x4) {
		regmap_write_bits(iocfg_regmap, reg_addr, 0xf0, *pin_drv_cap);
		pin_drv_cap++;
	}
}

static void hisi_set_io_config(struct sdhci_host *host)
{
	struct sdhci_hisi_priv *hisi_priv = sdhci_get_pltfm_priv(host);
	unsigned int devid = hisi_priv->devid;
	void *phy_addr = hisi_priv->phy_addr;
	unsigned short reg;

	if (devid == 0) {
		if (host->timing == MMC_TIMING_MMC_HS200 ||
		    host->timing == MMC_TIMING_MMC_HS400 ||
		    host->timing == MMC_TIMING_MMC_HS) {
			reg = sdhci_readw(host, SDHCI_EMMC_CTRL);
			reg |= SDHCI_CARD_IS_EMMC;
			sdhci_writew(host, reg, SDHCI_EMMC_CTRL);

			/* set drv strength to 50ohm */
			writel(0x6ff, phy_addr + REG_IOCTL_RONSEL_1_0);
			writel(0x6ff, phy_addr + REG_IOCTL_OD_RONSEL_2);
		}
	} else if (devid == 1) {
		hisi_set_sd_iocfg(host);
	} else {
		hisi_set_sdio_iocfg(host);
	}
}

static void hisi_get_phase(struct sdhci_host *host)
{
	struct sdhci_hisi_priv *hisi_priv = sdhci_get_pltfm_priv(host);

	if (host->mmc->ios.timing == MMC_TIMING_MMC_DDR52 ||
	    host->mmc->ios.timing == MMC_TIMING_UHS_DDR50)
		hisi_priv->drv_phase = 8;       /* 8 for 90 degree */
	else if (host->mmc->ios.timing == MMC_TIMING_MMC_HS200 ||
		 host->mmc->ios.timing == MMC_TIMING_UHS_SDR104)
		hisi_priv->drv_phase = 20;      /* 20 for 225 degree */
	else if (host->mmc->ios.timing == MMC_TIMING_MMC_HS400)
		hisi_priv->drv_phase = 9;       /* 9 for 101.25 degree */
	else
		hisi_priv->drv_phase = 16;      /* 16 for 180 degree */

	if (host->mmc->ios.timing == MMC_TIMING_MMC_HS400 ||
	    host->mmc->ios.timing == MMC_TIMING_MMC_HS200)
		hisi_priv->sampl_phase = hisi_priv->tuning_phase;
	else if (host->mmc->ios.timing == MMC_TIMING_MMC_DDR52)
		hisi_priv->sampl_phase = 20; /* 20 for 225 degree */
	else if (host->mmc->ios.timing == MMC_TIMING_UHS_DDR50 ||
		 host->mmc->ios.timing == MMC_TIMING_UHS_SDR25 ||
		 host->mmc->ios.timing == MMC_TIMING_SD_HS ||
		 host->mmc->ios.timing == MMC_TIMING_MMC_HS)
		hisi_priv->sampl_phase = 4; /* 4 for 45 degree */
	else
		hisi_priv->sampl_phase = 0;
}

static int hisi_support_runtime_pm(struct sdhci_host *host)
{
	/* This feature is disabled by default at Hi3556AV100 */
	return 0;
}
