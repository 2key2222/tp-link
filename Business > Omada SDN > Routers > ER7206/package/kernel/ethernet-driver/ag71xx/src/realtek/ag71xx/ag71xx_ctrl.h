#ifndef _AG71XX_CTRL_H
#define _AG71XX_CTRL_H

#include "phys/rtl8367s_api.h"

#define ATHR_GMAC_FLOW_CTRL               ((ATHR_GMAC_CTRL_IOC << 16) | 0x9)                   /* GMAC FLOW CTRL*/

/* Ioctl subroutines */
#define ATHR_GMAC_QOS_CTRL_IOC      (SIOCDEVPRIVATE | 0x01)
#define ATHR_GMAC_CTRL_IOC          (SIOCDEVPRIVATE | 0x02)
#define ATHR_PHY_CTRL_IOC           (SIOCDEVPRIVATE | 0x03)
#define ATHR_VLAN_IGMP_IOC          (SIOCDEVPRIVATE | 0x04)
#define ATHR_HW_ACL_IOC             (SIOCDEVPRIVATE | 0x05)
#define ATHR_MII_CTRL_IOC		(SIOCDEVPRIVATE | 0x06)

/*
 *GMAC_CTRL_IOC_COMMANDS
 */
#define ATHR_GMAC_TX_FLOW_CTRL            ((ATHR_GMAC_CTRL_IOC << 16) | 0x1)
#define ATHR_GMAC_RX_FLOW_CTRL            ((ATHR_GMAC_CTRL_IOC << 16) | 0x2)
#define ATHR_GMAC_DMA_CHECK               ((ATHR_GMAC_CTRL_IOC << 16) | 0x3)
#define ATHR_GMAC_SOFT_LED_BLINK          ((ATHR_GMAC_CTRL_IOC << 16) | 0x4)
#define ATHR_GMAC_SW_ONLY_MODE            ((ATHR_GMAC_CTRL_IOC << 16) | 0x5)
#define ATHR_GMAC_STATS                   ((ATHR_GMAC_CTRL_IOC << 16) | 0x6)
#define ATHR_JUMBO_FRAME                  ((ATHR_GMAC_CTRL_IOC << 16) | 0x7)
#define ATHR_FRAME_SIZE_CTL               ((ATHR_GMAC_CTRL_IOC << 16) | 0x8)
#define ATHR_GMAC_REG_READ				  ((ATHR_GMAC_CTRL_IOC << 16) | 0xa)                   /* read gmac register */
#define ATHR_GMAC_REG_WRITE				  ((ATHR_GMAC_CTRL_IOC << 16) | 0xb)
/*
 *PHY_CTRL_COMMANDS
 */
#define ATHR_PHY_FORCE           ((ATHR_PHY_CTRL_IOC << 16) | 0x1)
#define ATHR_PHY_RD              ((ATHR_PHY_CTRL_IOC << 16) | 0x2)
#define ATHR_PHY_WR              ((ATHR_PHY_CTRL_IOC << 16) | 0x3)
#define ATHR_PHY_MIB             ((ATHR_PHY_CTRL_IOC << 16) | 0X4)
#define ATHR_PHY_STATS           ((ATHR_PHY_CTRL_IOC << 16) | 0X5)
#define ATHR_PORT_STATS          ((ATHR_PHY_CTRL_IOC << 16) | 0X6)
#define ATHR_PORT_LINK           ((ATHR_PHY_CTRL_IOC << 16) | 0x7)
#define ATHR_FLOW_LINK_EN        ((ATHR_PHY_CTRL_IOC << 16) | 0x8)
#define ATHR_PHY_RXFCTL          ((ATHR_PHY_CTRL_IOC << 16) | 0x9)
#define ATHR_PHY_TXFCTL          ((ATHR_PHY_CTRL_IOC << 16) | 0x10)


#define ATHR_PACKET_FLAG         ((ATHR_VLAN_IGMP_IOC << 16) | 0x1)
#define ATHR_VLAN_ADDPORTS       ((ATHR_VLAN_IGMP_IOC << 16) | 0x2)
#define ATHR_VLAN_DELPORTS       ((ATHR_VLAN_IGMP_IOC << 16) | 0x3)
#define ATHR_VLAN_SETTAGMODE     ((ATHR_VLAN_IGMP_IOC << 16) | 0x4)
#define ATHR_VLAN_SETDEFAULTID   ((ATHR_VLAN_IGMP_IOC << 16) | 0x5)
#define ATHR_VLAN_ENABLE         ((ATHR_VLAN_IGMP_IOC << 16) | 0x6)
#define ATHR_VLAN_DISABLE        ((ATHR_VLAN_IGMP_IOC << 16) | 0x7)
#define ATHR_IGMP_ON_OFF         ((ATHR_VLAN_IGMP_IOC << 16) | 0x8)
#define ATHR_LINK_GETSTAT        ((ATHR_VLAN_IGMP_IOC << 16) | 0x9)
#define ATHR_ARL_ADD             ((ATHR_VLAN_IGMP_IOC << 16) | 0xa)
#define ATHR_ARL_DEL             ((ATHR_VLAN_IGMP_IOC << 16) | 0xb)
#define ATHR_MCAST_CLR           ((ATHR_VLAN_IGMP_IOC << 16) | 0xc)
/*
 * GMC_QOS_COMMANDS
 */
#define ATHR_QOS_ETH_SOFT_CLASS   ((ATHR_GMAC_QOS_CTRL_IOC << 16) | 0x1)
#define ATHR_QOS_ETH_PORT         ((ATHR_GMAC_QOS_CTRL_IOC << 16) | 0x2)
#define ATHR_QOS_ETH_VLAN         ((ATHR_GMAC_QOS_CTRL_IOC << 16) | 0x3)
#define ATHR_QOS_ETH_DA           ((ATHR_GMAC_QOS_CTRL_IOC << 16) | 0x4)
#define ATHR_QOS_ETH_IP           ((ATHR_GMAC_QOS_CTRL_IOC << 16) | 0x5)
#define ATHR_QOS_PORT_ILIMIT      ((ATHR_GMAC_QOS_CTRL_IOC << 16) | 0x6)
#define ATHR_QOS_PORT_ELIMIT      ((ATHR_GMAC_QOS_CTRL_IOC << 16) | 0x7)
#define ATHR_QOS_PORT_EQLIMIT     ((ATHR_GMAC_QOS_CTRL_IOC << 16) | 0x8)
#define MAX_QOS_COMMAND           ((ATHR_GMAC_QOS_CTRL_IOC << 16) | 0x9)

/*
 * ACL COMMANDS
 */
#define ATHR_ACL_COMMIT ((ATHR_HW_ACL_IOC << 16) | 0x1)
#define ATHR_ACL_FLUSH  ((ATHR_HW_ACL_IOC << 16) | 0x2)

/*
*MII_CTRL_COMMANDS
*/
#define ATHR_MII_REG_READ   ((ATHR_MII_CTRL_IOC << 16) | 0x1)
#define ATHR_MII_REG_WRITE         ((ATHR_MII_CTRL_IOC << 16) | 0x2)

/* Ethernet speeds in Mbps */
#define ETHSPEED_10MBPS     (0)
#define ETHSPEED_100MBPS    (1)
#define ETHSPEED_1000MBPS   (2)


struct tx_mac_stats {

	int pkt_cntr;
	int byte_cntr;
	int mcast_cntr;
	int bcast_cntr;
	int pctrlframe_cntr;
	int deferal_cntr;
	int excess_deferal_cntr;
	int single_col_cntr;
        int multi_col_cntr;
	int late_col_cntr;
	int excess_col_cntr;
	int total_col_cntr;
	int honored_cntr;
	int dropframe_cntr;
	int jabberframe_cntr;
	int fcserr_cntr;
	int ctrlframe_cntr;
	int oz_frame_cntr;
	int us_frame_cntr;
	int frag_frame_cntr;

};
struct rx_mac_stats {

	int byte_cntr;
	int pkt_cntr;
	int fcserr_cntr;
	int mcast_cntr;
	int bcast_cntr;
	int ctrlframe_cntr;
	int pausefr_cntr;
	int unknownop_cntr;
	int allignerr_cntr;
	int framelerr_cntr;
	int codeerr_cntr;
	int carriersenseerr_cntr;
	int underszpkt_cntr;
	int ozpkt_cntr;
	int fragment_cntr;
	int jabber_cntr;
	int rcvdrop_cntr;
	u_int32_t rxoverfl;
};

typedef struct {
        unsigned int link       :1;
        unsigned int speed      :2;
        unsigned int duplex     :1;
        unsigned int rxflctrl   :1;
        unsigned int txflctrl   :1;
}phystats;

struct eth_cfg_params {
    int cmd;
    char ad_name[IFNAMSIZ]; /* if name, e.g. "eth0" */
    uint16_t vlanid;
    uint16_t portnum;   /* pack to fit, yech */
    uint32_t phy_reg;
    uint32_t tos;
    uint32_t val;
    uint8_t duplex;
    uint8_t mac_addr[6];
    rtk_stat_port_cntr_t rtk_stat_cntr;
    struct tx_mac_stats txmac;
    struct rx_mac_stats rxmac;
    phystats phy_st;
};

#endif
