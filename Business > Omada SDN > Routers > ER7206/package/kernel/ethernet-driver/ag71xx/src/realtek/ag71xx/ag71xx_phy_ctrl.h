#ifndef _AG71XX_PHY_CTRL_H
#define _AG71XX_PHY_CTRL_H
/*
 * Rx Mib counter offset 
 */
#define ATHR_PHY_RX_BROAD_REG		      0x00   /* No of good broad cast frames rcvd*/
#define ATHR_PHY_RX_PAUSE_REG		      0x04   /* No of pause frames recieved */
#define ATHR_PHY_RX_MULTI_REG                 0x08   /* No of good multi cast frames rcvd*/
#define ATHR_PHY_RX_FCSERR_REG                0x0c   /* invalid FCS and an integral no of octets*/
#define ATHR_PHY_RX_ALIGNERR_REG              0x10   /* No of frames rcvd with valid lngth and do 
							not have integral no of octets and invalid FCS*/  	 
#define ATHR_PHY_RX_RUNT_REG		      0x14   /* No of frames rcvd with less than 64B long and have good FCS*/
#define ATHR_PHY_RX_FRAGMENT_REG              0x18   /* No of frames rcvd with less than 64B long and have
                                                        bad FCS*/
#define ATHR_PHY_RX_64B_REG                   0x1c   /* No of frames rcvd that are exactly 64B long with err*/
#define ATHR_PHY_RX_128B_REG                  0x20   /* No of frames rcvd with length 65 and 127  including err*/
#define ATHR_phy_RX_256B_REG		      0x24   /* No of frames rcvd with length 128 and 255 including err */
#define ATHR_PHY_RX_512B_REG		      0x28   /* No of frames rcvd with length 255 and 512 includingg err*/
#define ATHR_PHY_RX_1024B_REG		      0x2c   /* No of frames rcvd with lengeth 512 and 1023 including errs*/
#define ATHR_PHY_RX_1518B_REG		      0x30   /* No of frames rcvd with lengeth 1024 and 1518 including err*/
#define ATHR_PHY_RX_MAXB_REG		      0x34   /* No of frames rcvd with length b/w 1519 and amx length incl of err*/
#define ATHR_PHY_RX_TOLO_REG		      0x38   /* No of frames rcvd whose length exceeds the max length with FCS err*/
#define ATHR_PHY_RX_GOODBL_REG	              0x40   
#define ATHR_PHY_RX_GOODBU_REG	              0x3c
#define ATHR_PHY_RX_BADBL_REG		      0x48   
#define ATHR_PHY_RX_BADBU_REG		      0x44   
#define ATHR_PHY_RX_OVERFLW_REG               0x4c
#define ATHR_PHY_RX_FILTERD_REG               0x50    /*port disabled and unknown VID*/


/*
 * Tx Mib counter off 
 */ 	 

#define ATHR_PHY_TX_BROAD_REG                 0x54
#define ATHR_PHY_TX_PAUSE_REG                 0x58
#define ATHR_PHY_TX_MULTI_REG                 0x5c
#define ATHR_PHY_TX_UNDERRN_REG               0x60
#define ATHR_PHY_TX_64B_REG		      0x64
#define ATHR_PHY_TX_128B_REG                  0x68
#define ATHR_PHY_TX_256B_REG                  0x6c
#define ATHR_PHY_TX_512B_REG                  0x70
#define ATHR_PHY_TX_1024B_REG                 0x74
#define ATHR_PHY_TX_1518B_REG                 0x78
#define ATHR_PHY_TX_MAXB_REG                  0x7c
#define ATHR_PHY_TX_OVSIZE_REG                0x80
#define ATHR_PHY_TX_TXBYTEL_REG               0x88
#define ATHR_PHY_TX_TXBYTEU_REG               0x84
#define ATHR_PHY_TX_COLL_REG                  0x8c
#define ATHR_PHY_TX_ABTCOLL_REG               0x90
#define ATHR_PHY_TX_MLTCOL_REG                0x94
#define ATHR_PHY_TX_SINGCOL_REG               0x98
#define ATHR_PHY_TX_EXDF_REG                  0x9c
#define ATHR_PHY_TX_DEF_REG                   0xA0
#define ATHR_PHY_TX_LATECOL_REG               0xA4


#define ATHR_PHY_FUNC_CONTROL                   16
#define ATHR_PHY_MAX				5
#define ATHR_PHY_CONTROL			0

#endif
