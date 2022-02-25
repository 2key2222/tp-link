#ifndef _AG71XX_GMAC_CTRL_H
#define _AG71XX_GMAC_CTRL_H

#define 	AG71XX_REG_START	0xb8000000
#define	AG71XX_REG_END	0xbf000018
static inline int ag71xx_check_reg(struct ag71xx *ag, unsigned reg)
{	
	return 0; 
}

/*
 * Tx counter registers
 */
#define ATHR_GMAC_TX_PKT_CNTR                0xe4
#define ATHR_GMAC_TX_BYTES_CNTR              0xe0
#define ATHR_GMAC_TX_DROP_CNTR               0x114
#define ATHR_GMAC_TX_MULT_CNTR               0xe8
#define ATHR_GMAC_TX_CRC_ERR_CNTR            0x11c
#define ATHR_GMAC_TX_BRD_CNTR                0xEC
#define ATHR_GMAC_TX_PCTRL_CNTR              0xf0                       /*Tx pause control frame counter */
#define ATHR_GMAC_TX_DFRL_CNTR               0xf4                       /*TX Deferral packet counter */
//#define ATHR_GMAC_TX_TEDF_CNTR               0x1ec                      /*Tx Excessive deferal packet counter */
#define ATHR_GMAC_TX_TSCL_CNTR               0xfc                       /*Tx Single collision pcket counter */
#define ATHR_GMAC_TX_TMCL_CNTR               0x100                      /*TX Multiple collision packet counter */
#define ATHR_GMAC_TX_TLCL_CNTR               0x104                      /*Tx Late collision packet counter */
#define ATHR_GMAC_TX_TXCL_CNTR               0x108                      /*Tx excesive collision packet counter */
#define ATHR_GMAC_TX_TNCL_CNTR               0x10c                      /*Tx total collison counter */
#define ATHR_GMAC_TX_TPFH_CNTR               0x110                      /*Tx pause frames honoured counter */
#define ATHR_GMAC_TX_TJBR_CNTR               0x118                      /*Tx jabber frame counter */
#define ATHR_GMAC_TX_TXCF_CNTR               0x120                      /*Tx Control frame counter */
#define ATHR_GMAC_TX_TOVR_CNTR               0x124                      /*Tx oversize frame counter */
#define ATHR_GMAC_TX_TUND_CNTR               0x128                      /*TX under size frame counter */
#define ATHR_GMAC_TX_TFRG_CNTR               0x12c                      /*TX Fragments frame counter */

/*
 * MIB Registers
 */
#define ATHR_GMAC_RX_BYTES_CNTR              0x9c                      /*Rx Byte counter*/
#define ATHR_GMAC_RX_PKT_CNTR                0xa0                      /*Rx Packet counter*/
#define ATHR_GMAC_RX_CRC_ERR_CNTR            0xa4                      /*Rx rcv FCR error counter */
#define ATHR_GMAC_RX_MULT_CNTR               0xa8                      /*Rx rcv Mcast packet counter*/ 
#define ATHR_GMAC_RX_RBCA_CNTR               0xac                      /*Rx Broadcast packet counter*/
#define ATHR_GMAC_RX_RXCF_CNTR               0xb0                      /*Rx rcv control frame packet counter */
#define ATHR_GMAC_RX_RXPF_CNTR               0xb4                      /*Rx rcv pause frame work packet counter*/
#define ATHR_GMAC_RX_RXUO_CNTR               0xb8                      /*Rx rcv unknown opcode counter*/
#define ATHR_GMAC_RX_FRM_ERR_CNTR            0xbc                      /*Rx rcv alignment error counter*/
#define ATHR_GMAC_RX_LEN_ERR_CNTR            0xc0                      /*Rx Frame length error counter*/
#define ATHR_GMAC_RX_CODE_ERR_CNTR           0xc4                      /*Rx rcv code error counter */  
#define ATHR_GMAC_RX_CRS_ERR_CNTR            0xc8                      /*Rx rcv carrier sense error counter*/
#define ATHR_GMAC_RX_RUND_CNTR               0xcc                      /*Rx rcv undersize packet counter*/
#define ATHR_GMAC_RX_OVL_ERR_CNTR            0xd0                      /*Rx rcv oversize packet counter*/
#define ATHR_GMAC_RX_RFRG_CNTR               0xd4                      /*Rx rcv fragments counter */
#define ATHR_GMAC_RX_RJBR_CNTR               0xd8                      /*Rx rcv jabber counter*/ 
#define ATHR_GMAC_RX_DROP_CNTR               0xdc                      /*Rx rcv drop*/  
#define ATHR_GMAC_TOTAL_COL_CNTR             0x10c

/*END:    Add for ethreg*/

#endif