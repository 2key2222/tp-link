#include "ag71xx.h"
#include "ag71xx_ctrl.h"
#include "ag71xx_gmac_ctrl.h"
athr_gmac_rx_stats(struct ag71xx *mac, struct ifreq *ifr)
{
    struct eth_cfg_params *ethcfg;
    ethcfg = (struct eth_cfg_params *) ifr->ifr_data;

    ethcfg->rxmac.byte_cntr 		= ag71xx_rr(mac,ATHR_GMAC_RX_BYTES_CNTR);

    ethcfg->rxmac.pkt_cntr		= ag71xx_rr(mac,ATHR_GMAC_RX_PKT_CNTR);  

    ethcfg->rxmac.fcserr_cntr		= ag71xx_rr(mac,ATHR_GMAC_RX_CRC_ERR_CNTR);  

    ethcfg->rxmac.mcast_cntr		= ag71xx_rr(mac,ATHR_GMAC_RX_MULT_CNTR);  

    ethcfg->rxmac.bcast_cntr		= ag71xx_rr(mac,ATHR_GMAC_RX_RBCA_CNTR);  

    ethcfg->rxmac.ctrlframe_cntr	= ag71xx_rr(mac,ATHR_GMAC_RX_RXCF_CNTR);  

    ethcfg->rxmac.pausefr_cntr		= ag71xx_rr(mac,ATHR_GMAC_RX_RXPF_CNTR);  
 
    ethcfg->rxmac.unknownop_cntr	= ag71xx_rr(mac,ATHR_GMAC_RX_RXUO_CNTR);  
 
    ethcfg->rxmac.allignerr_cntr	= ag71xx_rr(mac,ATHR_GMAC_RX_FRM_ERR_CNTR);  

    ethcfg->rxmac.framelerr_cntr	= ag71xx_rr(mac,ATHR_GMAC_RX_LEN_ERR_CNTR);  

    ethcfg->rxmac.codeerr_cntr		= ag71xx_rr(mac,ATHR_GMAC_RX_CODE_ERR_CNTR);  

    ethcfg->rxmac.carriersenseerr_cntr	= ag71xx_rr(mac,ATHR_GMAC_RX_CRS_ERR_CNTR);  

    ethcfg->rxmac.underszpkt_cntr 	= ag71xx_rr(mac,ATHR_GMAC_RX_RUND_CNTR);  

    ethcfg->rxmac.ozpkt_cntr		= ag71xx_rr(mac,ATHR_GMAC_RX_OVL_ERR_CNTR);  

    ethcfg->rxmac.fragment_cntr		= ag71xx_rr(mac,ATHR_GMAC_RX_RFRG_CNTR);  

    ethcfg->rxmac.jabber_cntr		= ag71xx_rr(mac,ATHR_GMAC_RX_RJBR_CNTR);  

    ethcfg->rxmac.rcvdrop_cntr		= ag71xx_rr(mac,ATHR_GMAC_RX_DROP_CNTR);  
	
	ethcfg->rxmac.rxoverfl		= ag71xx_rr(mac,ATHR_GMAC_RX_DROP_CNTR);  
}

static void 
athr_gmac_tx_stats(struct ag71xx *mac, struct ifreq *ifr) 
{
    struct eth_cfg_params *ethcfg;
    ethcfg = (struct eth_cfg_params *) ifr->ifr_data;

    ethcfg->txmac.pkt_cntr	 	= ag71xx_rr(mac, ATHR_GMAC_TX_PKT_CNTR);

    ethcfg->txmac.byte_cntr	 	= ag71xx_rr(mac, ATHR_GMAC_TX_BYTES_CNTR);

    ethcfg->txmac.mcast_cntr		= ag71xx_rr(mac, ATHR_GMAC_TX_MULT_CNTR);

    ethcfg->txmac.bcast_cntr		= ag71xx_rr(mac, ATHR_GMAC_TX_BRD_CNTR);

    ethcfg->txmac.pctrlframe_cntr	= ag71xx_rr(mac, ATHR_GMAC_TX_PCTRL_CNTR);

    ethcfg->txmac.deferal_cntr		= ag71xx_rr(mac, ATHR_GMAC_TX_DFRL_CNTR);			

    ethcfg->txmac.single_col_cntr	= ag71xx_rr(mac, ATHR_GMAC_TX_TSCL_CNTR);		

    ethcfg->txmac.multi_col_cntr	= ag71xx_rr(mac, ATHR_GMAC_TX_TMCL_CNTR);		

    ethcfg->txmac.late_col_cntr		= ag71xx_rr(mac, ATHR_GMAC_TX_TLCL_CNTR);		

    ethcfg->txmac.excess_col_cntr	= ag71xx_rr(mac, ATHR_GMAC_TX_TXCL_CNTR);		

    ethcfg->txmac.total_col_cntr	= ag71xx_rr(mac, ATHR_GMAC_TX_TNCL_CNTR);		

    ethcfg->txmac.honored_cntr		= ag71xx_rr(mac, ATHR_GMAC_TX_TPFH_CNTR);		

    ethcfg->txmac.dropframe_cntr 	= ag71xx_rr(mac, ATHR_GMAC_TX_DROP_CNTR);

    ethcfg->txmac.jabberframe_cntr	= ag71xx_rr(mac, ATHR_GMAC_TX_TJBR_CNTR);		

    ethcfg->txmac.fcserr_cntr		= ag71xx_rr(mac, ATHR_GMAC_TX_CRC_ERR_CNTR);

    ethcfg->txmac.ctrlframe_cntr	= ag71xx_rr(mac, ATHR_GMAC_TX_TXCF_CNTR);		

    ethcfg->txmac.oz_frame_cntr		= ag71xx_rr(mac, ATHR_GMAC_TX_TOVR_CNTR);		

    ethcfg->txmac.us_frame_cntr		= ag71xx_rr(mac, ATHR_GMAC_TX_TUND_CNTR);		

    ethcfg->txmac.frag_frame_cntr	= ag71xx_rr(mac, ATHR_GMAC_TX_TFRG_CNTR);
}

int ag71xx_gmac_ctrl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
    struct ag71xx *ag = netdev_priv(dev);
    struct eth_cfg_params *ethcfg;
    ethcfg = (struct eth_cfg_params *) ifr->ifr_data;
    cmd = ethcfg->cmd;

    switch (cmd) {
        case ATHR_GMAC_REG_READ:
			if(ag71xx_check_reg(ag, ethcfg->phy_reg))
			{
				printk("Reg Adress not corrcet!\n");
				return -1;
			}
			ethcfg->val = ag71xx_rr_fast(ethcfg->phy_reg);
			break;
			
	 case ATHR_GMAC_REG_WRITE:
			if(ag71xx_check_reg(ag, ethcfg->phy_reg))
			{
				printk("Reg Adress not corrcet!\n");
				return -1;
			}
			ag71xx_wr_fast(ethcfg->phy_reg, ethcfg->val);
			break;
			
        case ATHR_GMAC_STATS:
         		athr_gmac_tx_stats (ag, ifr);
            		athr_gmac_rx_stats (ag, ifr);
			break;

        default:
             break;
    }
    if (copy_to_user(ifr->ifr_data, ethcfg, sizeof(struct eth_cfg_params)))
        return -EFAULT;

    return 0;

}
