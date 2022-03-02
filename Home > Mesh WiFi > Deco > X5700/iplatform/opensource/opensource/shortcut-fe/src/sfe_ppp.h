/*  Copyright(c) 2009-2018 Shenzhen TP-LINK Technologies Co.Ltd.
 *
 * file		sfe_ppp.h
 * brief		
 * details	
 *
 * author	Wang Hao
 * version	
 * date		19Jun18
 *
 * history 	\arg	
 */


#ifndef _SFE_PPP_H
#define _SFE_PPP_H

#include <linux/skbuff.h>
#include "sfe_cm.h"

#define SFE_VID_UNUSED 0xFFFF

extern int32_t addVlanToLan(struct sk_buff * skb);
extern int32_t sfe_ppp_getDestRealDev(struct sfe_connection_create *sic, struct net_device *src_dev, struct net_device *dest_dev);

extern int32_t sfe_ppp_pppoeToWanAddHeader(struct sk_buff * skb, int len, struct net_device *dev, __be16 vid);
extern int32_t sfe_ppp_pptpToWanAddHeader(struct sk_buff * skb, struct net_device *dev, __be16 vid);
extern int32_t sfe_ppp_L2tpToWanAddHeader(struct sk_buff * skb, struct net_device *dev, __be16 vid);
extern int32_t sfe_ppp_pppoeToLanRemoveHeader(struct sk_buff * skb);
extern int32_t sfe_ppp_pptpToLanRemoveHeader(struct sk_buff * skb);
extern int32_t sfe_ppp_L2tpToLanRemoveHeader(struct sk_buff * skb);

extern void sfe_ppp_init(void);
extern void sfe_ppp_exit(void);

#endif
