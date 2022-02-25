#include "ag71xx.h"
#include "ag71xx_ctrl.h"
#include "ag71xx_phy_ctrl.h"

#if (defined(CONFIG_ATH79_SOC_QCA9558) || defined(CONFIG_ATH79_SOC_QCA9563))
extern u16 ar8337sw_phy_read(struct mii_bus *mii, unsigned phy_addr,
		      unsigned reg_addr);
extern int ar8337sw_phy_write(struct mii_bus *mii, unsigned phy_addr,
		       unsigned reg_addr, u16 reg_val);
#define phy_read ar8337sw_phy_read
#define phy_write ar8337sw_phy_write
#else
#define phy_read ar7240sw_phy_read
#define phy_write ar7240sw_phy_write
#endif

int ag71xx_phy_ctrl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
    struct ag71xx *ag = netdev_priv(dev);
    struct eth_cfg_params *ethcfg;
#if (defined(CONFIG_ATH79_SOC_QCA9558) || defined(CONFIG_ATH79_SOC_QCA9563))
    struct mii_bus *mii = ag->phy_dev->bus;
#else
    struct mii_bus *mii = ag->mii_bus;
#endif
    u32 reg_addr;
	
    ethcfg = (struct eth_cfg_params *) ifr->ifr_data;
    cmd = ethcfg->cmd;

    switch (cmd) {
       case ATHR_PHY_RD:	
			if (ethcfg->portnum == 0x3f)
			{
				printk("No this phy, please check!\n");
				return -1;
			}
			ethcfg->val = phy_read(mii, ethcfg->portnum, ethcfg->phy_reg);
			break;
			
	case ATHR_PHY_WR:
			if (ethcfg->portnum == 0x3f)
			{
				printk("No this phy, please check!\n");
				return -1;
			}
			phy_write(mii, ethcfg->portnum, ethcfg->phy_reg, ethcfg->val);
			break;
			
        default:
             		break;
    }
    if (copy_to_user(ifr->ifr_data, ethcfg, sizeof(struct eth_cfg_params)))
        return -EFAULT;

    return 0;

}
