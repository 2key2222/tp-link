/*  Copyright(c) 2009-2018 Shenzhen TP-LINK Technologies Co.Ltd.
 *
 * file		sfe_ppp.c
 * brief		support encapsulate/decapsulate PPPoE/PPTP/L2TP header.
 * details	
 *
 * author	Wang Hao
 * version	
 * date		15Jun18
 *
 * history 	\arg	
 */

#include <linux/module.h>
#include <linux/if_vlan.h>
#include <linux/ppp_defs.h>
#include <linux/if_pppox.h>
#include <net/tcp.h>
#include <net/udp.h>
#include <linux/if_bridge.h>
#include <linux/l2tp.h>
#include <linux/../../net/l2tp/l2tp_core.h>

#include "sfe_ppp.h"
#include "sfe.h"

/*********************************** DEFINE ***********************************/
#define PPP_ADDRESS_CONTROL		0xff03
#define VLAN_LEN					4

/* port from ppp/pptp.c, make sure these structures are same */
#define PPTP_GRE_PROTO				0x880B
#define PPTP_GRE_VER				0x1
#define PPTP_GRE_FLAG_K				0x20
#define PPTP_GRE_FLAG_S				0x10
#define PPTP_GRE_FLAG_A				0x80

#define PPTP_GRE_IS_S(f)				((f)&PPTP_GRE_FLAG_S)
#define PPTP_GRE_IS_A(f)				((f)&PPTP_GRE_FLAG_A)

#define NUM_NP	6		/* Number of NPs. */

/* Per tunnel, session hash table size */
#define L2TP_HASH_BITS	4
#define L2TP_HASH_SIZE	(1 << L2TP_HASH_BITS)

/*********************************** PROTOTYPE ***********************************/
struct pppoe_header
{
	uint8_t ver:4;
	uint8_t type:4;
	uint8_t code;
	uint16_t sid;
	uint16_t length;
	uint16_t protocol;
};

struct sfe_pppoe_info
{
	uint16_t sid;
	uint8_t eth_header[ETH_HLEN];
};

struct pptp_gre_header
{
	u8  flags; 	  	/* bitfield */
	u8  ver;			 /* should be PPTP_GRE_VER (enhanced GRE) */
	u16 protocol;	 /* should be PPTP_GRE_PROTO (ppp-encaps) */
	u16 payload_len;	 /* size of ppp payload, not inc. gre header */
	u16 call_id;		 /* peer's call_id for this session */
	u32 seq;			  /* sequence number.  Present if S==1 */
	u32 ack;			 /* seq number of highest packet recieved by */
} __packed;
 
struct sfe_pptp_info
{
	uint32_t tx_seqno;
	uint32_t rx_seqno;
	uint32_t saddr;
	uint32_t daddr;
	uint16_t call_id;
	uint16_t tx_ip_id;
	uint8_t eth_header[ETH_HLEN];
};

struct sfe_l2tp_info
{
	uint32_t daddr;				/* DIP */
	uint32_t saddr;			 	/* SIP */
	uint16_t tid;					/* Tunnel ID */
	uint16_t sid;					/* Session ID */
	uint16_t source;				/* UDP source port */
	uint16_t dest; 				/* UDP dest port */
	uint8_t eth_header[ETH_HLEN];
};

struct sfe_l2tp_parse
{
	uint16_t ver;					 /* Packets Type */
	uint16_t length;				 /* Length (Optional)*/
	uint16_t tid;					 /* Tunnel ID */
	uint16_t sid;					 /* Session ID */
};

struct l2tp_add_hdr
{
	uint16_t source; /* UDP */
	uint16_t dest;
	uint16_t len;
	uint16_t checksum;
	uint16_t type; /* L2TP */
	uint16_t tid;
	uint16_t sid;
};

 struct ppp_hdr
{
	uint16_t addr_ctrl;
	uint16_t protocol;
};

struct ppp_file {
	enum {
		INTERFACE=1, CHANNEL
	}		kind;
	struct sk_buff_head xq;		/* pppd transmit queue */
	struct sk_buff_head rq;		/* receive queue for pppd */
	wait_queue_head_t rwait;	/* for poll on reading /dev/ppp */
	atomic_t	refcnt;		/* # refs (incl /dev/ppp attached) */
	int		hdrlen;		/* space to leave for headers */
	int		index;		/* interface unit / channel number */
	int		dead;		/* unit/channel has been shut down */
};

struct ppp {
	struct ppp_file	file;		/* stuff for read/write/poll 0 */
	struct file	*owner;		/* file that owns this unit 48 */
	struct list_head channels;	/* list of attached channels 4c */
	int		n_channels;	/* how many channels are attached 54 */
	spinlock_t	rlock;		/* lock for receive side 58 */
	spinlock_t	wlock;		/* lock for transmit side 5c */
	int		mru;		/* max receive unit 60 */
	unsigned int	flags;		/* control bits 64 */
	unsigned int	xstate;		/* transmit state bits 68 */
	unsigned int	rstate;		/* receive state bits 6c */
	int		debug;		/* debug flags 70 */
	struct slcompress *vj;		/* state for VJ header compression */
	enum NPmode	npmode[NUM_NP];	/* what to do with each net proto 78 */
	struct sk_buff	*xmit_pending;	/* a packet ready to go out 88 */
	struct compressor *xcomp;	/* transmit packet compressor 8c */
	void		*xc_state;	/* its internal state 90 */
	struct compressor *rcomp;	/* receive decompressor 94 */
	void		*rc_state;	/* its internal state 98 */
	unsigned long	last_xmit;	/* jiffies when last pkt sent 9c */
	unsigned long	last_recv;	/* jiffies when last pkt rcvd a0 */
	struct net_device *dev;		/* network interface device a4 */
	int		closing;	/* is device closing down? a8 */
#ifdef CONFIG_PPP_MULTILINK
	int		nxchan;		/* next channel to send something on */
	u32		nxseq;		/* next sequence number to send */
	int		mrru;		/* MP: max reconst. receive unit */
	u32		nextseq;	/* MP: seq no of next packet */
	u32		minseq;		/* MP: min of most recent seqnos */
	struct sk_buff_head mrq;	/* MP: receive reconstruction queue */
#endif /* CONFIG_PPP_MULTILINK */
#ifdef CONFIG_PPP_FILTER
	struct sock_filter *pass_filter;	/* filter for packets to pass */
	struct sock_filter *active_filter;/* filter for pkts to reset idle */
	unsigned pass_len, active_len;
#endif /* CONFIG_PPP_FILTER */
	struct net	*ppp_net;	/* the net we belong to */
};

struct channel {
	struct ppp_file	file;		/* stuff for read/write/poll */
	struct list_head list;		/* link in all/new_channels list */
	struct ppp_channel *chan;	/* public channel data structure */
	struct rw_semaphore chan_sem;	/* protects `chan' during chan ioctl */
	spinlock_t	downl;		/* protects `chan', file.xq dequeue */
	struct ppp	*ppp;		/* ppp unit we're connected to */
	struct net	*chan_net;	/* the net channel belongs to */
	struct list_head clist;		/* link in list of channels per unit */
	rwlock_t	upl;		/* protects `ppp' */
#ifdef CONFIG_PPP_MULTILINK
	u8		avail;		/* flag used in multilink stuff */
	u8		had_frag;	/* >= 1 fragments have been sent */
	u32		lastseq;	/* MP: last sequence # received */
	int		speed;		/* speed of the corresponding ppp channel*/
#endif /* CONFIG_PPP_MULTILINK */
};

/*********************************** VARIABLE ***********************************/
struct net_device *WanInf = NULL;

static struct sfe_pppoe_info pppoe_log;
static struct sfe_pptp_info pptp_log;
static struct sfe_l2tp_info l2tp_log;


extern uint32_t sync_tx_sequence;

/* extern int32_t (*sfe_PppoeToWanParsePtr)(struct sk_buff * skb); */
/* extern int32_t (*sfe_PptpToWanParsePtr)(struct sk_buff * skb); */
/* extern int32_t (*sfe_L2tpToWanParsePtr)(struct sk_buff * skb); */

/*********************************** LOCAL FUNCTION ***********************************/
static void skb_debugFy(const struct sk_buff *skb)
{
#define NUM2PRINT (90+ETH_HLEN)
	char buf[NUM2PRINT * 3 + 1];	/* 3 chars per byte */
	int i = 0;
	for (i = 0; i < skb->len && i < NUM2PRINT; i++) {
		/* sprintf(buf + i * 3, "%2.2x ", 0xff & (skb->data[i - ETH_HLEN])); */
		sprintf(buf + i * 3, "%2.2x ", 0xff & (skb->data[i]));
	}
	printWar("skb[%p] data[%p] hdr[%p]: %s\n", skb->head, skb->data, eth_hdr(skb), buf);
}

static uint8_t GetPppLength(uint8_t *data, uint8_t *protocol)
{
	uint8_t ppp_length = 0;

	/* parse PPP length and get protocol field*/
	if (*data == 0x0  && *(data+1) == PPP_IP)
	{
		ppp_length = 2;
		*protocol = PPP_IP;
	}
	else if (*data == PPP_ALLSTATIONS && *(data + 1) == PPP_UI)
	{
		ppp_length = 2;
		data += 2;
		if (*data == 0x0 && *(data+1) == PPP_IP)
		{
			ppp_length += 2;
			*protocol = PPP_IP;
		}
	}
	else if (*data == PPP_IP)
	{
		ppp_length = 1;
		*protocol = PPP_IP;
	}

	return ppp_length ;
}

//this function is temporarily used, remove it after merge the VLAN entry.
//for debug now.
#if 0
int32_t addVlanToLan(struct sk_buff * skb)
{
	struct vlan_ethhdr	*vethLan = NULL;
	
	if (directionFlag == 1)//(strncmp(skb->dev->name, "br-lan", 4) == 0)
	{
		if (!WanInf)
		{
			WanInf = dev_get_by_name(&init_net, "eth0");
		}
		skb->dev = WanInf;

		/* add lan vid*/
		skb_push(skb, 4);
		memcpy(skb->data, skb->data + 4, 12);
		vethLan = (struct vlan_ethhdr *)(skb->data);
		vethLan->h_vlan_proto = htons(ETH_P_8021Q);
		vethLan->h_vlan_TCI = htons(1);
		vethLan->h_vlan_encapsulated_proto = htons(ETH_P_IP);
		skb->vlan_tci = 0;
		//printErr("3333 dev=%s ", skb->dev->name);
		//skb_debugFy(skb);
		directionFlag = -1;
	}

	return 0;
}
#endif

/*********************************** GLOBAL FUNCTION ***********************************/
int32_t sfe_ppp_getDestRealDev(struct sfe_connection_create *sic, struct net_device *src_dev, struct net_device *dest_dev)
{
#ifdef SFE_FAST_PATH
	struct net_device *real_out_dev = NULL;
	struct net_device *real_in_dev = NULL;
	unsigned short in_vid, out_vid;
	struct net_device *in_vlan_dev = NULL;
	struct net_device *br_eth_dev = NULL;
#endif
	struct net_device *ppp_eth_dev = NULL;

#ifdef SFE_FAST_PATH
	in_vlan_dev = src_dev;
	
	if ((real_in_dev = vlan_dev_real_dev(in_vlan_dev)) != NULL)
	{
		in_vid = vlan_dev_vlan_id(in_vlan_dev);
		printWar("real_in_dev = %s, in_vid = %d\n",real_in_dev->name, in_vid);
	}
	else
	{
		in_vid = 0;	
	}
#endif

	if (dest_dev->flags & IFF_POINTOPOINT)
	{
		struct ppp *ppp = netdev_priv(dest_dev);
		if(IS_ERR(ppp))
		{
			//printErr("ppp is invalid, return\n");
			return -1;
			
		}
		struct list_head *list = &ppp->channels;
		list = list->next;
		struct channel *pch = list_entry(list, struct channel, clist);
		if(IS_ERR(pch) )
		{
			//printErr("pch is invalid, return\n");
			return -1;

		}
		if(IS_ERR(pch->chan) )
		{
			//printErr("pch->chan is invalid, return\n");
			return -1;

		}
		struct sock *sk = (struct sock *)pch->chan->private;
		
		struct pppox_sock *po = pppox_sk(sk);
		if (strncmp(dest_dev->name, "pppoe-internet", 14) == 0 || strncmp(dest_dev->name, "share-internet", 14) == 0)
		{
			ppp_eth_dev = po->pppoe_dev;
			sic->flags |= SFE_IPV4_CREATE_FLAG_PPPOE;
			/* printWar("dev is %s\n", po->pppoe_dev->name); */
		}
		else if (strncmp(dest_dev->name, "pptp-internet", 13) == 0)
		{
			struct pptp_opt *opt = &po->proto.pptp;
			struct flowi4 fl4;
			struct rtable *rt;

            pptp_log.call_id = htons(opt->dst_addr.call_id);
			
			rt = ip_route_output_ports(&init_net, &fl4, NULL,
						   opt->dst_addr.sin_addr.s_addr,
						   opt->src_addr.sin_addr.s_addr,
						   0, 0, IPPROTO_GRE,
						   RT_TOS(0), sk->sk_bound_dev_if);
			if(IS_ERR(rt))
			{
				printErr("fast-classifier pptp rt ERR\n");
				return -1;
			}
			ppp_eth_dev = rt->dst.dev;
			sic->flags |= SFE_IPV4_CREATE_FLAG_PPTP;
			/* printWar("dev is %s\n", rt->dst.dev->name); */
		}
		else if (strncmp(dest_dev->name, "l2tp-internet", 13) == 0)
		{
			struct l2tp_session *session = NULL;
			struct sock *skb_sk = NULL;
			struct inet_sock *inet = NULL;//inet_sk(sk);
			struct ip_options_rcu *inet_opt;
			struct flowi4 fl4;
			struct rtable *rt = NULL;
			__be32 daddr;

			sock_hold(sk);
			session = (struct l2tp_session *)(sk->sk_user_data);
			skb_sk = session->tunnel->sock;
			inet = inet_sk(skb_sk);
			sock_put(sk);

            l2tp_log.tid = ntohs(session->tunnel->peer_tunnel_id);
            l2tp_log.sid = ntohs(session->peer_session_id);

			/* Use correct destination address if we have options. */
			inet_opt = inet->inet_opt;
			daddr = inet->inet_daddr;
			if (inet_opt && inet_opt->opt.srr)
				daddr = inet_opt->opt.faddr;

			rt = ip_route_output_ports(sock_net(skb_sk), &fl4, skb_sk,
					   daddr, inet->inet_saddr,
					   inet->inet_dport,
					   inet->inet_sport,
					   skb_sk->sk_protocol,
					   RT_CONN_FLAGS(skb_sk),
					   skb_sk->sk_bound_dev_if);
			if(IS_ERR(rt))
			{
				printErr("fast-classifier l2tp rt ERR\n");
				return -1;
			}
			ppp_eth_dev = rt->dst.dev;
			sic->flags |= SFE_IPV4_CREATE_FLAG_L2TP;
			/* printWar("dev is %s\n", rt->dst.dev->name); */
		}
		else
		{
			printErr("unknown dest_dev is %s\n", dest_dev->name);
			return -1;
		}
	}

#ifdef SFE_FAST_PATH
	if (ppp_eth_dev != NULL && ppp_eth_dev->priv_flags & IFF_EBRIDGE)
	{
		br_eth_dev = br_port_dev_get(ppp_eth_dev, ppp_eth_dev->dev_addr);
		if (!br_eth_dev)
		{
			printErr("no port found on wan bridge...\n");
			return -1;
		}
	}

	if (ppp_eth_dev != NULL && (real_out_dev = vlan_dev_real_dev(ppp_eth_dev)) != NULL)
	{
		out_vid = vlan_dev_vlan_id(ppp_eth_dev);
		printWar("real_out_dev = %s, outvid = %d\n",real_out_dev->name, out_vid);
	}
	else if (dest_dev != NULL && (real_out_dev = vlan_dev_real_dev(dest_dev)) != NULL)
	{
		out_vid = vlan_dev_vlan_id(dest_dev);
		printWar("real_out_dev = %s, outvid = %d\n",real_out_dev->name, out_vid);
	}
	else if (br_eth_dev != NULL && (real_out_dev = vlan_dev_real_dev(br_eth_dev)) != NULL)
	{
		out_vid = vlan_dev_vlan_id(br_eth_dev);
		printWar("real_out_dev = %s, outvid = %d\n",real_out_dev->name, out_vid);
	}
	else
	{
		out_vid = 0;
	}

	sic->vid = in_vid;
	sic->vid_xlate = out_vid;

	if (real_out_dev)
	{
		sic->dest_real_dev = real_out_dev;
	}
	else if (br_eth_dev)
	{
		sic->dest_real_dev = br_eth_dev;
		dev_put(br_eth_dev);
	}
	else 
#endif
	if (ppp_eth_dev)
	{
		sic->dest_real_dev = ppp_eth_dev;
	}
	else
	{
		sic->dest_real_dev = dest_dev;
	}

	sic->src_dev = src_dev;
	sic->dest_dev = dest_dev;

	return 0;
}
EXPORT_SYMBOL(sfe_ppp_getDestRealDev);

int sfe_ppp_pppoeToWanParseLayerInfo(struct sk_buff * skb)
{
	struct vlan_hdr *vh = NULL;
	struct ethhdr *eth = NULL;
	struct pppoe_header *pppoe_hdr = NULL;

	uint8_t *ppp_format = NULL;
	int32_t offset = 6;	//pppoe header length
	int32_t ppp_length = 0;
	uint8_t ppp_protocol = 0;
	uint16_t eth_type;

	eth = eth_hdr(skb);
	pppoe_hdr = (struct pppoe_header *)(skb->data);
	eth_type = eth->h_proto; 
    
	if (eth_type == htons(ETH_P_8021Q))
	{
		vh = (struct vlan_hdr *)((u8 *)eth + ETH_HLEN);
		pppoe_hdr = (struct pppoe_header *)((u8 *)eth + ETH_HLEN + VLAN_LEN);
		eth_type = vh->h_vlan_encapsulated_proto;
	}

	if (eth_type != htons(ETH_P_PPP_SES))
	{
		return 1;
	}

    if(pppoe_log.sid != pppoe_hdr->sid) {
        memcpy(pppoe_log.eth_header, eth->h_source, ETH_ALEN);
        memcpy(&pppoe_log.eth_header[6], eth->h_dest, ETH_ALEN);


        ppp_format = ((char *)pppoe_hdr) + offset;

        /* parse PPP length */
        ppp_length = GetPppLength(ppp_format, &ppp_protocol);

        if (ppp_length == 0) 
        {
            return 1;
        }

        pppoe_log.sid = pppoe_hdr->sid;
    }

    /* sfe_ppp_pppoeToLanRemoveHeader(skb); */

	return 0;/*0 means OK here*/
}

EXPORT_SYMBOL(sfe_ppp_pppoeToWanParseLayerInfo);

int32_t sfe_ppp_pptpToWanParseLayerInfo(struct sk_buff * skb)
{
	struct vlan_hdr *vh = NULL;
	struct ethhdr *eth = NULL;
	struct iphdr *iph = NULL;
	struct iphdr *iph_ppp0 = NULL;
	struct tcphdr *th = NULL;
	struct udphdr *uh = NULL;

	struct pptp_gre_header *greh = NULL;
	uint8_t *ppp_format = NULL;
	int32_t offset = sizeof(*greh) - 8; // delete seq and ack no
	int32_t ppp_length = 0;
	uint16_t eth_type;

	eth = eth_hdr(skb);
	iph_ppp0 = (struct iphdr *)(skb->data);

	if (iph_ppp0->protocol != IPPROTO_GRE)
	{
		return 1;
	}

	greh = (struct pptp_gre_header *)(skb->data + (iph_ppp0->ihl*4));

	/*log pptp info*/
	pptp_log.saddr = iph_ppp0->saddr;
	pptp_log.daddr = iph_ppp0->daddr;
	memcpy(pptp_log.eth_header, eth->h_source, ETH_ALEN);
	memcpy(&pptp_log.eth_header[6], eth->h_dest, ETH_ALEN);

	eth_type = eth->h_proto;

	if (PPTP_GRE_IS_S(greh->flags))
	{
		pptp_log.tx_seqno = ntohl(greh->seq);
		pptp_log.tx_ip_id = ntohs(iph_ppp0->id);
		offset += 4;
	}

	if (PPTP_GRE_IS_A(greh->ver))
	{
		pptp_log.rx_seqno = ntohl(greh->ack);
		offset += 4;
	}
	
	ppp_format = ((char *)greh) + offset;

	if (greh->payload_len > 0)
	{
		uint8_t ppp_protocol = 0;
		/* parse PPP length */
		ppp_length = GetPppLength(ppp_format, &ppp_protocol);
	}	

	if (ppp_length == 0) 
	{
		return 1;
	}
	
	/* set IP offset*/
	offset = iph_ppp0->ihl*4 + offset + ppp_length;

	if (eth_type == htons(ETH_P_8021Q))
	{
		vh = (struct vlan_hdr *)(skb->data + ETH_HLEN);
		/* eth_type = vh->h_vlan_encapsulated_proto; */
	}

	if (skb->dev->priv_flags & IFF_EBRIDGE){
        sfe_ppp_pptpToLanRemoveHeader(skb);
    }

	return 0;/*0 means OK here*/
}

EXPORT_SYMBOL(sfe_ppp_pptpToWanParseLayerInfo);

int32_t sfe_ppp_L2tpToWanParseLayerInfo(struct sk_buff * skb)
{
	struct ethhdr *eth = NULL;
	struct iphdr *iph_ppp0 = NULL;
	struct udphdr *uh = NULL;

	struct sfe_l2tp_parse  *l2tph = NULL;
	uint16_t *tunnel_id = NULL;	
	uint16_t *session_id = NULL;
	uint8_t *ppp_format;	

	int32_t offset = 6;//l2tp header from 6 
	int32_t ppp_length = 0;
	uint8_t ppp_protocol = 0;

	/*let dst to cpu mac*/
	eth = eth_hdr(skb);
	iph_ppp0 = (struct iphdr *)(skb->data);

	if (iph_ppp0->protocol != IPPROTO_UDP)
	{
		return 1;
	}

	uh = (struct udphdr *)(skb->data + (iph_ppp0->ihl*4));
	l2tph = (struct sfe_l2tp_parse *)(skb->data + (iph_ppp0->ihl*4) + 8);

	if(ntohs(uh->dest) !=1701) /*l2f port:1701*/
	{
		return 1;
	}

	if(ntohs(l2tph->ver) & 0x8000)//control frame
	{
		return 1;
	}

	if(ntohs(l2tph->ver) & 0x4000)
	{
		offset += 2;
	}

	if(ntohs(l2tph->ver) & 0x0200)
	{
		offset += 2;
	}

	/* log l2tp info */
	l2tp_log.saddr = iph_ppp0->daddr;
	l2tp_log.daddr = iph_ppp0->saddr;
	l2tp_log.source = uh->dest;
	l2tp_log.dest = uh->source;
	memcpy(l2tp_log.eth_header, eth->h_source, ETH_ALEN);
	memcpy(&l2tp_log.eth_header[6], eth->h_dest, ETH_ALEN);

	ppp_format = ((char *)l2tph) + offset;				

	/* parse PPP length and check inside IP protocol */
	ppp_length = GetPppLength(ppp_format, &ppp_protocol);

	if (ppp_length == 0) 
	{
		return 1;
	}

	offset = iph_ppp0->ihl*4+ 8 + offset + ppp_length;// tunnel IP offset + udp

	if (ppp_protocol != PPP_IP)
	{
		printWar("3.1 ppp_protocol != IP, return, line %d!!\n", __LINE__);
		return 1;				
	}

    if (skb->dev->priv_flags & IFF_EBRIDGE){
        sfe_ppp_L2tpToLanRemoveHeader(skb);
    }

	return 0;
}
EXPORT_SYMBOL(sfe_ppp_L2tpToWanParseLayerInfo);

int32_t sfe_ppp_pppoeToWanAddHeader(struct sk_buff * skb, int len, struct net_device *dev, __be16 vid)
{
	uint32_t add_len = 0;
	struct pppoe_header *pppoe_hdr = NULL;
#ifdef SFE_FAST_PATH
	struct vlan_ethhdr *veth = NULL;
	uint8_t data_offset = VLAN_LEN + ETH_HLEN;
#else
	struct ethhdr *eth_h = NULL;
	uint8_t data_offset = ETH_HLEN;
#endif
	/*  mac+vlan+pppoe+ppp(no address control) */
	add_len = data_offset  + sizeof(struct pppoe_header); 	
	if (skb_headroom(skb) < add_len || skb_shared(skb) ||
		(skb_cloned(skb) && !skb_clone_writable(skb,0)))
	{
		struct sk_buff *new_skb = skb_realloc_headroom(skb, add_len);
		if (!new_skb)
		{
			printErr("realloc headroom failed!\n");	
			return 1;
		}
		kfree_skb(skb);
		skb = new_skb;
	}

	/* skb_debugFy(skb); */

	/* add L2	*/					
	memcpy(skb_push(skb, add_len), pppoe_log.eth_header, ETH_HLEN);
#ifdef SFE_FAST_PATH
	/* add wan vid */
	veth = (struct vlan_ethhdr *)(skb->data);
	veth->h_vlan_proto = htons(ETH_P_8021Q);
	veth->h_vlan_TCI = htons(vid);
	veth->h_vlan_encapsulated_proto = htons(ETH_P_PPP_SES);
#else
	eth_h = (struct ethhdr *)(skb->data);
	eth_h->h_proto = htons(ETH_P_PPP_SES);
#endif

	/* add pppoe+ppp */
	pppoe_hdr = (struct pppoe_header *)(skb->data + data_offset);    
	memset(pppoe_hdr, 0, sizeof(struct pppoe_header));
	pppoe_hdr->ver = 1;
	pppoe_hdr->type = 1;
	pppoe_hdr->code = 0;
	pppoe_hdr->sid = pppoe_log.sid;
	pppoe_hdr->length = htons(len + 2);// 2: ppp header length
	pppoe_hdr->protocol = htons(PPP_IP);

	skb->vlan_tci = 0;
	skb->dev=dev;

	/* skb_debugFy(skb); */

	return 0;
}

int32_t sfe_ppp_pptpToWanAddHeader(struct sk_buff * skb, struct net_device *dev, __be16 vid)
{
	struct iphdr *iph = NULL;
	uint32_t add_len = 0;
	struct iphdr *iph_new = NULL;
	struct pptp_gre_header *greh_new = NULL;	
	struct ppp_hdr *ppph = NULL;
#ifdef SFE_FAST_PATH
	struct vlan_ethhdr *veth = NULL;
	uint8_t data_offset = ETH_HLEN + VLAN_LEN;
#else
	struct ethhdr *eth_h = NULL;
	uint8_t data_offset = ETH_HLEN;
#endif
	
	//printErr("1111");
	//skb_debugFy(skb);

	/* skb_debugFy(skb); */
	/*  mac+ip+gre+ppp-4(ack) */
	add_len = data_offset + sizeof(struct iphdr) + sizeof(struct pptp_gre_header) -4 + sizeof(struct ppp_hdr); 	
	if (skb_headroom(skb) < add_len || skb_shared(skb) ||
		(skb_cloned(skb) && !skb_clone_writable(skb,0)))
	{
		struct sk_buff *new_skb = skb_realloc_headroom(skb, add_len);
		if (!new_skb)
		{
			printErr("realloc headroom failed!\n");	
			return 1;
		}
		kfree_skb(skb);
		skb = new_skb;
	}
	
	/* add L2 */					
	memcpy(skb_push(skb, add_len), pptp_log.eth_header, ETH_HLEN);
#ifdef SFE_FAST_PATH
	/* add wan vid */
	veth = (struct vlan_ethhdr *)(skb->data);
	veth->h_vlan_proto = htons(ETH_P_8021Q);
	veth->h_vlan_TCI = htons(vid);
	veth->h_vlan_encapsulated_proto = htons(ETH_P_IP);
#else
	eth_h = (struct ethhdr *)(skb->data);
	eth_h->h_proto = htons(ETH_P_IP);
#endif

	/* add L3 */
	iph_new = (struct iphdr *)(skb->data + data_offset);    
	memset(iph_new, 0, sizeof(struct iphdr));
	iph_new->version	= IPVERSION;
	iph_new->ihl	= 5;
	iph_new->ttl 	= IPDEFTTL;   
	iph_new->protocol = IPPROTO_GRE;
	iph_new->saddr = pptp_log.daddr;
	iph_new->daddr = pptp_log.saddr;
	/* TODO: To enable checksum offload in the furure */		
	iph_new->tot_len = htons(skb->len - data_offset);		
	skb->ip_summed = CHECKSUM_NONE;			
	iph_new->id = htons(++pptp_log.tx_ip_id);
	iph_new->check = ip_fast_csum((uint8_t *)iph_new, 5);	

	/* add gre header */
	add_len = data_offset + sizeof(struct iphdr) + sizeof(struct pptp_gre_header) -4;
	greh_new = (struct pptp_gre_header *)(skb->data + data_offset + sizeof(struct iphdr));
	greh_new->flags = PPTP_GRE_FLAG_K | PPTP_GRE_FLAG_S;
	greh_new->ver = PPTP_GRE_VER;
	greh_new->protocol = htons(PPTP_GRE_PROTO); /*ppp type = 0x880b*/
	greh_new->payload_len = htons(skb->len - add_len);    	
	greh_new->call_id = pptp_log.call_id;			
	greh_new->seq = htonl(++sync_tx_sequence);		
	/* do not ack, -4 bytes*/

	/* add PPP */
	ppph = (struct ppp_hdr *)(skb->data + data_offset + sizeof(struct iphdr) + sizeof(struct pptp_gre_header) - 4);
	ppph->addr_ctrl = htons(PPP_ADDRESS_CONTROL);
	ppph->protocol = htons(PPP_IP);

	skb->dev=dev;
	//printErr("2222");
	/* skb_debugFy(skb); */

	return 0;
}

int32_t sfe_ppp_L2tpToWanAddHeader(struct sk_buff * skb, struct net_device *dev, __be16 vid)
{
	uint32_t add_len = 0;
	struct iphdr *iph_new = NULL;
	struct l2tp_add_hdr *l2tph_new = NULL;
	struct ppp_hdr *ppph = NULL;
#ifdef SFE_FAST_PATH
	struct vlan_ethhdr *veth = NULL;
	uint8_t data_offset = ETH_HLEN + VLAN_LEN;
#else
	struct ethhdr *eth_h = NULL;
	uint8_t data_offset = ETH_HLEN;
#endif

    /* if(skb->data[16] != 192 || skb->data[17] != 168 || skb->data[18] != 13 || skb->data[19] != 15){ */
    /*     return 0; */
    /* } */
		
	//printErr("1111");
	/* skb_debugFy(skb); */

	add_len = data_offset + sizeof(struct iphdr) + 8 + 6 + 4;/* UDP(8)+L2TP(6)+PPP(4) */
	if (skb_headroom(skb) < add_len || skb_shared(skb) ||
		(skb_cloned(skb) && !skb_clone_writable(skb,0)))
	{
		struct sk_buff *new_skb = skb_realloc_headroom(skb, add_len);
		if (!new_skb)
		{
			printErr("realloc headroom failed!\n");	
			return 1;
		}
		kfree_skb(skb);
		skb = new_skb;
	}
	
	/* add L2 */
	memcpy(skb_push(skb, add_len), l2tp_log.eth_header, ETH_HLEN);
#ifdef SFE_FAST_PATH
	/* add wan vid*/
	veth = (struct vlan_ethhdr *)(skb->data);
	veth->h_vlan_proto = htons(ETH_P_8021Q);
	veth->h_vlan_TCI = htons(vid);
	veth->h_vlan_encapsulated_proto = htons(ETH_P_IP);
#else
	eth_h = (struct ethhdr *)(skb->data);
	eth_h->h_proto = htons(ETH_P_IP);
#endif

	/* add L3 */
	iph_new = (struct iphdr *)(skb->data + data_offset);
	memset(iph_new, 0, sizeof(struct iphdr));
	iph_new->version	= IPVERSION;
	iph_new->ihl = 5;
	iph_new->ttl = IPDEFTTL;
	iph_new->protocol = IPPROTO_UDP;
	iph_new->saddr = l2tp_log.saddr;
	iph_new->daddr = l2tp_log.daddr;
	iph_new->tot_len = htons(skb->len - data_offset);
	skb->ip_summed = CHECKSUM_NONE;
	iph_new->check = ip_fast_csum((uint8_t *)iph_new, 5);	

	/* add UDP + L2TP */
	l2tph_new = (struct l2tp_add_hdr *)(skb->data + data_offset + sizeof(struct iphdr));
	l2tph_new->source = l2tp_log.source;
	l2tph_new->dest = l2tp_log.dest;
	l2tph_new->checksum = 0;
	l2tph_new->len = htons(skb->len - data_offset - sizeof(struct iphdr));/* UDP Length */
	l2tph_new->type = htons(0x0002); /* V2 */
	l2tph_new->tid = l2tp_log.tid;
	l2tph_new->sid = l2tp_log.sid;
	/* printWar("l2tph_new->tid=%0x l2tph_new->sid=%0x\n", l2tph_new->tid, l2tph_new->sid); */

	/* add PPP */
	ppph = (struct ppp_hdr *)(skb->data + data_offset + sizeof(struct iphdr) + sizeof(struct l2tp_add_hdr));
	ppph->addr_ctrl = htons(PPP_ADDRESS_CONTROL);
	ppph->protocol  = htons(PPP_IP);
	
	skb->dev = dev;
	//printErr("2222");
	/* skb_debugFy(skb); */

	return 0;
}

int32_t sfe_ppp_pppoeToLanRemoveHeader(struct sk_buff * skb)
{
	struct iphdr *iph_ppp0 = NULL;
	struct pppoe_header *pppoe_hdr = NULL;
	struct tcphdr *th = NULL;
	struct udphdr *uh = NULL;
	struct ethhdr *eth = NULL;
	uint32_t offset = 6;//pppoe header length
	uint32_t ppp_length = 0;
	uint8_t *ppp_format;	
	uint8_t ppp_protocol = 0;
	__be16 src_port = 0;
	__be16 dst_port = 0;
	uint8_t ip_protocol =0;
	uint16_t *eth_type = NULL;
    struct net_device *pppInf = NULL;

	eth = eth_hdr(skb);
	pppoe_hdr = (struct pppoe_header *)(skb->data);

	if (eth->h_proto != htons(ETH_P_PPP_SES) || skb->len < 48)
	{
		return 1;
	}

	
	ppp_format = ((u8 *)pppoe_hdr) + offset;				
	ppp_length = GetPppLength(ppp_format, &ppp_protocol);

	if (ppp_length == 0)
	{
		return 1;
	}

	/*calculate remove length*/
	offset = offset + ppp_length;	/* add IP offset */ 
	iph_ppp0 = (struct iphdr *)((u8 *)pppoe_hdr + offset);

	if (iph_ppp0->protocol == IPPROTO_TCP)
	{
		th = (struct tcphdr *)(skb->data + offset + 20);
		src_port = th->source;
		dst_port = th->dest;
		ip_protocol = IPPROTO_TCP;
		/* printWar("TCP src port=%d, dst port=%d\n", ntohs(th->source), ntohs(th->dest)); */
	}
	else if (iph_ppp0->protocol == IPPROTO_UDP)
	{
		uh = (struct udphdr *)(skb->data + offset + 20);
		src_port = uh->source;
		dst_port = uh->dest;
		ip_protocol = IPPROTO_UDP;
		/* printWar("UDP src port=%d, dst port=%d\n", ntohs(uh->source), ntohs(uh->dest)); */
	}
	else
	{
		/* printWar("PppoeToLan, Non TCP/UDP to lan, return\n"); */
		return 1;
	}

	/* not IP packet Inside,return */
	if (ppp_protocol != PPP_IP)
	{
        printWar("ppp_protocol invalid %x %x\n", ppp_protocol, PPP_IP);
		return 1;
	}
	else
	{
		/* header removal section */
        pppInf = __dev_get_by_name(&init_net, "pppoe-internet");
        if (!pppInf)
        {
            pppInf = __dev_get_by_name(&init_net, "share-internet");
            if(pppInf == NULL)
            {
                printErr("pppInf = NULL\n");
                return 1;
            }
        }

		if (sfe_ipv4_find_match(pppInf, ip_protocol, iph_ppp0->saddr, src_port, iph_ppp0->daddr, dst_port) != NULL)
		{
			/* skb_debugFy(skb); */
			/*memory remove from head*/    
			skb_pull(skb, offset);
			skb->dev = pppInf;
			eth_type = (uint16_t *)(skb->data - 2);
			*eth_type = htons(ETH_P_IP);//replace with IP before NAT.
			skb->protocol = *eth_type;
			/* skb_debugFy(skb); */
			/* directionFlag = 1; */
		}
		pppInf = NULL;
	}

	return 0;
}
EXPORT_SYMBOL(sfe_ppp_pppoeToLanRemoveHeader);

int32_t sfe_ppp_pptpToLanRemoveHeader(struct sk_buff * skb)
{
	struct iphdr *iph_ppp0 = NULL;
	struct pptp_gre_header *greh;
	struct iphdr *iph = NULL;
	struct tcphdr *th = NULL;
	struct udphdr *uh = NULL;
	uint32_t offset = 8;// gre 8 bytes, wothout seq and ack
	uint32_t ppp_length = 0;
	uint8_t *ppp_format;	
	uint8_t ppp_protocol = 0;
	__be16 src_port = 0;
	__be16 dst_port = 0;
	uint8_t ip_protocol =0;
    struct net_device *pppInf = NULL;

	iph = (struct iphdr *)(skb->data);
	if (iph->protocol != IPPROTO_GRE || skb->len < 60)
	{
		return 1;
	}

	greh = (struct pptp_gre_header *)(skb->data + (iph->ihl*4));

	/* handle PPTP packet */
	if ((greh->ver&7) == PPTP_GRE_VER && ntohs(greh->protocol) == PPTP_GRE_PROTO)
	{
		/* check optional length */
		if (PPTP_GRE_IS_S(greh->flags))
		{
			offset += 4;
		}	

		if (PPTP_GRE_IS_A(greh->ver))
		{
			offset += 4;
		}

		ppp_format = ((char *)greh) + offset;
		if (greh->payload_len > 0)
		{
			ppp_length = GetPppLength(ppp_format, &ppp_protocol);
		}

		if (ppp_length == 0)
		{
			return 1;
		}

		/*calculate remove length*/
		offset = iph->ihl*4 + offset + ppp_length;	/* add IP offset */	
		iph_ppp0 = (struct iphdr *)(skb->data + offset);
		
		if (iph_ppp0->protocol == IPPROTO_TCP)
		{
			th = (struct tcphdr *)(skb->data + offset + 20);
			src_port = th->source;
			dst_port = th->dest;
			ip_protocol = IPPROTO_TCP;
			/* printWar("TCP src port=%d, dst port=%d\n", ntohs(th->source), ntohs(th->dest)); */
		}
		else if (iph_ppp0->protocol == IPPROTO_UDP)
		{
			uh = (struct udphdr *)(skb->data + offset + 20);
			src_port = uh->source;
			dst_port = uh->dest;
			ip_protocol = IPPROTO_UDP;
			/* printWar("UDP src port=%d, dst port=%d\n", ntohs(uh->source), ntohs(uh->dest)); */
		}
		else
		{
			//printWar("PptpToLan, Non TCP/UDP to lan, return\n");
			return 1;
		}

		/* not IP packet Inside,return */
		if (ppp_protocol != PPP_IP)
		{
			return 1;
		}
		else
		{
			/* header removal section */
			if (!pppInf)
			{
				pppInf = __dev_get_by_name(&init_net, "pptp-internet");
				if (!pppInf)
				{
					printErr("pppInf = NULL\n");
					return 1;
				}
			}

			if (sfe_ipv4_find_match(pppInf, ip_protocol, iph_ppp0->saddr, src_port, iph_ppp0->daddr, dst_port) != NULL)
			{
				memcpy(skb->data, skb->data - offset, offset);
				/*memory remove from head*/    
				skb_pull(skb, offset);
				skb->dev = pppInf;
				directionFlag = 1;
			}
			pppInf = NULL;
		}
	}

	return 0;
}
EXPORT_SYMBOL(sfe_ppp_pptpToLanRemoveHeader);

int32_t sfe_ppp_L2tpToLanRemoveHeader(struct sk_buff * skb)
{
	struct iphdr *iph_ppp0 = NULL;
	struct sfe_l2tp_parse  *l2tpremove;
	uint8_t ppp_protocol = 0;
	struct iphdr *iph = NULL;
	struct tcphdr *th = NULL;
	struct udphdr *uh = NULL;	
	uint8_t *ppp_format;	
	int32_t offset = 6; //l2tp header from 6 
	int32_t ppp_length = 0;
	__be16 src_port = 0;
	__be16 dst_port = 0;
	uint8_t ip_protocol =0;
    struct net_device *pppInf = NULL;

	iph = (struct iphdr *)(skb->data);
	if (iph->protocol != IPPROTO_UDP || skb->len < 60)
	{
		return 1;
	}

	uh = (struct udphdr *)(skb->data + (iph->ihl*4));
	l2tpremove = (struct sfe_l2tp_parse *)(skb->data + (iph->ihl*4) + 8);

	if (ntohs(uh->source)!=1701) /*udp source port 1701*/
	{
		return 1;
	}

	if (l2tpremove->ver & 0x4000)	
	{
		offset += 2;
	}

	if (l2tpremove->ver & 0x0200)
	{
		offset += 2;
	}

	ppp_format = ((char *)l2tpremove) + offset; 			
	/* parse PPP length and check inside IP protocol */
	ppp_length = GetPppLength(ppp_format, &ppp_protocol);
	
	if (ppp_length == 0)
	{
		return 1;
	}

	offset = iph->ihl*4 + 8/*UDP*/ + offset + ppp_length;	// tunnel IP offset 
	iph_ppp0 = (struct iphdr *)(skb->data + offset);/*inner IP, 8:UDP in offset*/

	/* get source&dest port to check if binded */
	if (iph_ppp0->protocol == IPPROTO_TCP)
	{
		th = (struct tcphdr *)(skb->data + offset + 20);
		src_port = th->source;
		dst_port = th->dest;
		ip_protocol = IPPROTO_TCP;
		//printWar("TCP src port=%d, dst port=%d", ntohs(th->source), ntohs(th->dest));
	}
	else if (iph_ppp0->protocol == IPPROTO_UDP)
	{
		uh = (struct udphdr *)(skb->data + offset + 20);
		src_port = uh->source;
		dst_port = uh->dest;
		ip_protocol = IPPROTO_UDP;
	}
	else
	{
		//printWar("L2tpToLan, Non TCP/UDP to lan skb->len=%d\n", skb->len);
		return 1;
	}
	/* not IP packet in PPP */
	if (ppp_protocol != PPP_IP)
	{
		return 1;
	}
	else
	{
		/* header removal section */
        pppInf = __dev_get_by_name(&init_net, "l2tp-internet");
        if (!pppInf)
        {
            printErr("pppInf = NULL\n");
            return 1;
        }

		if (sfe_ipv4_find_match(pppInf, ip_protocol, iph_ppp0->saddr, src_port, iph_ppp0->daddr, dst_port) !=NULL)
		{
			/* printWar("l2tp remove header!!!\n"); */
			//printErr("1111dev=%s", skb->dev->name);
			//skb_debugFy(skb);
			/* memory remove from head */  
            memcpy(skb->data, skb->data - offset, offset);
			skb_pull(skb, offset);
			skb->dev = pppInf;
			/* //printErr("2222"); */
			/* //skb_debugFy(skb); */
			/* directionFlag = 1; */
		}
		pppInf = NULL;
	}

	return 0;
}
EXPORT_SYMBOL(sfe_ppp_L2tpToLanRemoveHeader);

void sfe_ppp_init(void)
{
	/* sfe_PppoeToWanParsePtr = sfe_ppp_pppoeToWanParseLayerInfo; */
	/* sfe_PptpToWanParsePtr = sfe_ppp_pptpToWanParseLayerInfo; */
	/* sfe_L2tpToWanParsePtr = sfe_ppp_L2tpToWanParseLayerInfo; */
}

void sfe_ppp_exit(void)
{
	/* sfe_PppoeToWanParsePtr = NULL; */
	/* sfe_PptpToWanParsePtr = NULL; */
	/* sfe_L2tpToWanParsePtr = NULL; */

	if (WanInf != NULL)
	{
		dev_put(WanInf);
		WanInf = NULL;
	}
	
	/* if (pppInf != NULL) */
	/* { */
	/* 	dev_put(pppInf); */
	/* 	pppInf = NULL; */
	/* } */
}

