#include "ag71xx.h"
#include "ag71xx_ctrl.h"
#include "ag71xx_mii_ctrl.h"

#if (defined(CONFIG_ATH79_SOC_QCA9558) || defined(CONFIG_ATH79_SOC_QCA9563))
extern u32 rtl8367s_reg_read(struct mii_bus *mii, u32 reg);
extern u32 rtl8367s_reg_write(struct mii_bus *mii, u32 reg, u32 val);
#define sw_reg_read rtl8367s_reg_read
#define sw_reg_write rtl8367s_reg_write
#define REG_STATS_BASE(_port)	(0x1000 + (_port) * 0x100)
#else
#define sw_reg_read ar7240sw_reg_read
#define sw_reg_write ar7240sw_reg_write
#define REG_STATS_BASE(_port)	(0x20000 + (_port) * 0x100)
#endif

static void athr_mib_stats_get(struct net_device *dev, struct ifreq *ifr)
{
	struct eth_cfg_params *ethcfg = (struct eth_cfg_params *) ifr->ifr_data;
	u16 ret = 0;

	ret = rtk_stat_port_getAll(ethcfg->portnum, &ethcfg->rtk_stat_cntr);

	if (ret)
		printk("fail to get port stat.\n");
}

int ag71xx_mii_ctrl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
    struct ag71xx *ag = netdev_priv(dev);
    struct eth_cfg_params *ethcfg;
    struct mii_bus *mii = ag->mii_bus;

    ethcfg = (struct eth_cfg_params *) ifr->ifr_data;
    cmd = ethcfg->cmd;

    switch (cmd) {
       case ATHR_MII_REG_READ:
				ethcfg->val = sw_reg_read(mii, ethcfg->phy_reg);
				break;
		case ATHR_MII_REG_WRITE:
				sw_reg_write(mii, ethcfg->phy_reg, ethcfg->val);
				break;
      		case ATHR_PHY_STATS:
            	athr_mib_stats_get(dev, ifr);
            	break;
        default:
            break;
    }
    if (copy_to_user(ifr->ifr_data, ethcfg, sizeof(struct eth_cfg_params)))
        return -EFAULT;

    return 0;

}
