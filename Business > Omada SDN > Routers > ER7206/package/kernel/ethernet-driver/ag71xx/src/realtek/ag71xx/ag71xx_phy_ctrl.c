#include "ag71xx.h"
#include "ag71xx_ctrl.h"

#define PHY_REG(phy_id, phy_reg) (((phy_id) << 5) + (phy_reg))

int ag71xx_mdio_read(struct mii_bus *bus, int addr, int reg);
int ag71xx_mdio_write(struct mii_bus *bus, int addr, int reg, u16 val);

int ag71xx_phy_ctrl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
    struct ag71xx *ag = netdev_priv(dev);
    struct eth_cfg_params *ethcfg;
    struct mii_bus *mii = ag->mii_bus;
    u32 reg_addr;
	
    ethcfg = (struct eth_cfg_params *) ifr->ifr_data;
    cmd = ethcfg->cmd;

    switch (cmd) {
       case ATHR_PHY_RD:	
			
			ethcfg->val = ag71xx_mdio_read(mii, 0, PHY_REG(ethcfg->portnum, ethcfg->phy_reg));
			break;
			
	case ATHR_PHY_WR:
			ag71xx_mdio_write(mii, 0, PHY_REG(ethcfg->portnum, ethcfg->phy_reg), ethcfg->val);
			break;
			
        default:
             		break;
    }
    if (copy_to_user(ifr->ifr_data, ethcfg, sizeof(struct eth_cfg_params)))
        return -EFAULT;

    return 0;

}
