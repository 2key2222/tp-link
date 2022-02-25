#include "ag71xx.h"
#include "ag71xx_ctrl.h"
#include "ag71xx_mii_ctrl.h"


#if (defined(CONFIG_ATH79_SOC_QCA9558) || defined(CONFIG_ATH79_SOC_QCA9563))
extern u32 ar8216_reg_read(struct mii_bus *mii, u32 reg);
extern u32 ar8327_reg_write(struct mii_bus *mii, u32 reg, u32 val);
#define sw_reg_read ar8216_reg_read
#define sw_reg_write ar8327_reg_write
#define REG_STATS_BASE(_port)	(0x1000 + (_port) * 0x100)
#else
#define sw_reg_read ar7240sw_reg_read
#define sw_reg_write ar7240sw_reg_write
#define REG_STATS_BASE(_port)	(0x20000 + (_port) * 0x100)
#endif

int  athr_mib_tx_stats(struct net_device *dev, struct ifreq *ifr, int phyBase)
{           
    struct ag71xx *ag = netdev_priv(dev);
    struct eth_cfg_params *ethcfg;
    struct mii_bus *mii = ag->mii_bus;
    unsigned int base;
	
    ethcfg = (struct eth_cfg_params *) ifr->ifr_data;
    base = (unsigned int)REG_STATS_BASE(ethcfg->portnum);
	
    ethcfg->txcntr.tx_broad	=  sw_reg_read(mii, base + ATHR_PHY_TX_BROAD_REG);
    ethcfg->txcntr.tx_pause	=  sw_reg_read(mii, base + ATHR_PHY_TX_PAUSE_REG);
    ethcfg->txcntr.tx_multi	=  sw_reg_read(mii, base + ATHR_PHY_TX_MULTI_REG);
    ethcfg->txcntr.tx_underrun	=  sw_reg_read(mii, base + ATHR_PHY_TX_MULTI_REG);
    ethcfg->txcntr.tx_64b	=  sw_reg_read(mii, base + ATHR_PHY_TX_64B_REG);
    ethcfg->txcntr.tx_128b	=  sw_reg_read(mii, base + ATHR_PHY_TX_128B_REG);
    ethcfg->txcntr.tx_256b	=  sw_reg_read(mii, base + ATHR_PHY_TX_256B_REG);
    ethcfg->txcntr.tx_512b	=  sw_reg_read(mii, base + ATHR_PHY_TX_512B_REG);
    ethcfg->txcntr.tx_1024b     =  sw_reg_read(mii, base + ATHR_PHY_TX_1024B_REG);
    ethcfg->txcntr.tx_1518b     =  sw_reg_read(mii, base + ATHR_PHY_TX_1518B_REG);
    ethcfg->txcntr.tx_maxb	=  sw_reg_read(mii, base + ATHR_PHY_TX_MAXB_REG);
    ethcfg->txcntr.tx_oversiz	=  sw_reg_read(mii, base + ATHR_PHY_TX_OVSIZE_REG);
    ethcfg->txcntr.tx_bytel   	=  sw_reg_read(mii, base + ATHR_PHY_TX_TXBYTEL_REG);
    ethcfg->txcntr.tx_byteh  	=  sw_reg_read(mii, base + ATHR_PHY_TX_TXBYTEU_REG);
    ethcfg->txcntr.tx_collision	=  sw_reg_read(mii, base + ATHR_PHY_TX_COLL_REG);
    ethcfg->txcntr.tx_abortcol 	=  sw_reg_read(mii, base + ATHR_PHY_TX_ABTCOLL_REG);
    ethcfg->txcntr.tx_multicol 	=  sw_reg_read(mii, base + ATHR_PHY_TX_MLTCOL_REG);
    ethcfg->txcntr.tx_singalcol	=  sw_reg_read(mii, base + ATHR_PHY_TX_SINGCOL_REG); 
    ethcfg->txcntr.tx_execdefer	=  sw_reg_read(mii, base + ATHR_PHY_TX_EXDF_REG);
    ethcfg->txcntr.tx_defer	=  sw_reg_read(mii, base + ATHR_PHY_TX_DEF_REG);
    ethcfg->txcntr.tx_latecol	=  sw_reg_read(mii, base + ATHR_PHY_TX_LATECOL_REG);

    return 0;	
}

int athr_mib_rx_stats(struct net_device *dev, struct ifreq *ifr, int phyBase)
{
    struct ag71xx *ag = netdev_priv(dev);
    struct eth_cfg_params *ethcfg;
    struct mii_bus *mii = ag->mii_bus;
    unsigned int base;
    ethcfg = (struct eth_cfg_params *) ifr->ifr_data;
    base = (unsigned int)REG_STATS_BASE(ethcfg->portnum);
	
     ethcfg->rxcntr.rx_broad        = sw_reg_read(mii, base + ATHR_PHY_RX_BROAD_REG);
     ethcfg->rxcntr.rx_pause        = sw_reg_read(mii, base + ATHR_PHY_RX_PAUSE_REG);
     ethcfg->rxcntr.rx_multi        = sw_reg_read(mii, base + ATHR_PHY_RX_MULTI_REG);
     ethcfg->rxcntr.rx_fcserr       = sw_reg_read(mii, base + ATHR_PHY_RX_FCSERR_REG);
     ethcfg->rxcntr.rx_allignerr    = sw_reg_read(mii, base + ATHR_PHY_RX_ALIGNERR_REG);
     ethcfg->rxcntr.rx_runt         = sw_reg_read(mii, base + ATHR_PHY_RX_RUNT_REG);
     ethcfg->rxcntr.rx_frag         = sw_reg_read(mii, base + ATHR_PHY_RX_FRAGMENT_REG);
     ethcfg->rxcntr.rx_64b          = sw_reg_read(mii, base + ATHR_PHY_RX_RUNT_REG);
     ethcfg->rxcntr.rx_128b         = sw_reg_read(mii, base + ATHR_PHY_RX_128B_REG);
     ethcfg->rxcntr.rx_256b         = sw_reg_read(mii, base + ATHR_phy_RX_256B_REG);
     ethcfg->rxcntr.rx_512b         = sw_reg_read(mii, base + ATHR_PHY_RX_512B_REG);
     ethcfg->rxcntr.rx_1024b        = sw_reg_read(mii, base + ATHR_PHY_RX_1024B_REG);
     ethcfg->rxcntr.rx_1518b        = sw_reg_read(mii, base + ATHR_PHY_RX_1518B_REG);
     ethcfg->rxcntr.rx_maxb         = sw_reg_read(mii, base + ATHR_PHY_RX_MAXB_REG);
     ethcfg->rxcntr.rx_tool         = sw_reg_read(mii, base + ATHR_PHY_RX_TOLO_REG);
     ethcfg->rxcntr.rx_goodbl       = sw_reg_read(mii, base + ATHR_PHY_RX_GOODBL_REG);
     ethcfg->rxcntr.rx_goodbh       = sw_reg_read(mii, base + ATHR_PHY_RX_GOODBU_REG);
     ethcfg->rxcntr.rx_overflow     = sw_reg_read(mii, base + ATHR_PHY_RX_OVERFLW_REG);
     ethcfg->rxcntr.rx_badbl        = sw_reg_read(mii, base + ATHR_PHY_RX_BADBL_REG);
     ethcfg->rxcntr.rx_badbu        = sw_reg_read(mii, base + ATHR_PHY_RX_BADBU_REG);
           
     return 0;
}

int ag71xx_mii_ctrl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
    struct ag71xx *ag = netdev_priv(dev);
    struct eth_cfg_params *ethcfg;
    struct mii_bus *mii = ag->mii_bus;
    u32 reg_addr;
	
    ethcfg = (struct eth_cfg_params *) ifr->ifr_data;
    cmd = ethcfg->cmd;
	
    switch (cmd) {
       case ATHR_MII_REG_READ:	
			if (ethcfg->portnum == 0x3f)
			{
				ethcfg->val = sw_reg_read(mii, ethcfg->phy_reg);	
				break;
			}
			else if ((ethcfg->portnum >= 0)&&(ethcfg->portnum <= 6))
			{
				ethcfg->val = sw_reg_read(mii, ethcfg->phy_reg + 0x100*(ethcfg->portnum+1));
				break;
			}
			else
			{
				printk("No this port, please check!\n");
				break;
			}
			
		case ATHR_MII_REG_WRITE:
			if (ethcfg->portnum == 0x3f)
			{
				sw_reg_write(mii, ethcfg->phy_reg, ethcfg->val);
				break;
			}
			else if ((ethcfg->portnum >= 0)&&(ethcfg->portnum <= 6))
			{
				sw_reg_write(mii, ethcfg->phy_reg + 0x100*(ethcfg->portnum+1), ethcfg->val);
				break;
			}
			else
			{
				printk("No this port, please check!\n");
				break;				
			}
      		case ATHR_PHY_STATS:
            		athr_mib_tx_stats(dev, ifr, 0); 
            		athr_mib_rx_stats(dev, ifr, 0); 
            		break;
        default:
            break;
    }
    if (copy_to_user(ifr->ifr_data, ethcfg, sizeof(struct eth_cfg_params)))
        return -EFAULT;

    return 0;

}
