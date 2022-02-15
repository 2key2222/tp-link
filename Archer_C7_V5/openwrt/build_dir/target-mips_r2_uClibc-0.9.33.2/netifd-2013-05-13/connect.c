/*! Copyright(c) 2008-2014 Shenzhen TP-LINK Technologies Co.Ltd.
 *
 *\file     connect.c
 *\brief        
 *\details  
 *
 *\author   Zhu Xianfeng<zhuxianfeng@tp-link.net>
 *\version  1.0.0
 *\date     29May14
 *
 *\warning  
 *
 *\history \arg 29May14, Zhu Xianfeng, create the file.
 */
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "netifd.h"
#include "interface.h"
#include "proto.h"
#include "system.h"
#include "connect.h"
#include "backup_config.h"

#define IPT_STAT_BASE_CTL         (128)
#define IPT_STAT_SET_NET          (IPT_STAT_BASE_CTL)
#define IPT_STAT_DEL_ALL          (IPT_STAT_BASE_CTL + 5)
#define IPT_STAT_GET_WAN_STAT     (IPT_STAT_BASE_CTL + 1)
#define IPT_STAT_GET_WANS_TX_STAT (IPT_STAT_BASE_CTL + 2)

#define MAX_CONNECT_IFACE_NUM     10

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)             (sizeof(x)/sizeof(x[0]))
#endif
#define CONNECT_IFACE_WAN         "wan"
#define CONNECT_IFACE_WANV6       "wanv6"
#define CONNECT_IFACE_LAN         "lan"
#define CONNECT_IFACE_INTERNET    "internet"
#define CONNECT_IFACE_INTERNETV6  "internetv6"
#define CONNECT_IFNAME_LAN        "br-lan"
#define CONNECT_IFACE_MOBILE      "mobile"
#define CONNECT_MACADDR_LEN       (6)
#define CONNECT_TIMEOUT           (1000)
#define dprintf(fmt, args...)     D(CONNCTL, fmt, ##args)

enum iface_proto
{
	IFP_INVALID,
	IFP_STATIC,
	IFP_DHCP,
	IFP_DHCPV6,
	IFP_PPPOE,
	IFP_PPPOEV6,
	IFP_L2TP,
	IFP_PPTP,
	IFP_BIGPOND,
	IFP_6TO4,
	IFP_6RD,
	IFP_DSLITE,
	IFP_PASSTHROUGH,
};

struct ipt_net
{
	uint32_t ip;
	uint32_t mask;
};

struct ipt_tx_stat{
	char tx_devname[IFNAMSIZ + 1];
	uint32_t snd_pkt;
	uint32_t snd_byte;
};

struct {
	struct ipt_tx_stat stats[MAX_CONNECT_IFACE_NUM];
	int num;
}wans_tx_data;

struct iface_stat
{
	char ifname[IFNAMSIZ + 1];
	struct ipt_tx_stat last_stats[2];
};

struct conn_handler
{
	enum interface_conn_mode mode;
	void (*process)(struct interface *iface);
};

static int connect_ipt_outgone(struct interface *iface);
static void connect_auto(struct interface *iface);
static void connect_manual(struct interface *iface);
static void connect_demand(struct interface *iface);
static void connect_timebased(struct interface *iface);
static void connect_dft_route(int add);
static int get_uci_ifname(char *ifname);

static int initialized;
static int tmp_ip_set;
static char tmp_ip_str[16];
static struct iface_stat ifaces_stat[MAX_CONNECT_IFACE_NUM];
static int ifaces_stat_len = 0;
static bool get_tx_info = false;
static struct uloop_timeout timeout;
static struct conn_handler conn_handlers[] =
{
	{
		.mode = IFCM_AUTO,
		.process = connect_auto,
	},
	{
		.mode = IFCM_MANUAL,
		.process = connect_manual,
	},
	{
		.mode = IFCM_DEMAND,
		.process = connect_demand,
	},
	{
		.mode = IFCM_TIMEBASED,
		.process = connect_timebased,
	},
};
static char *valid_ifaces[] =
{
	CONNECT_IFACE_WAN,
	CONNECT_IFACE_WANV6,
	CONNECT_IFACE_INTERNET,
	CONNECT_IFACE_INTERNETV6,
	CONNECT_IFACE_MOBILE,
	NULL,
};

static bool 
connect_ifvalid(struct interface *iface)
{
	char **ptr;

	for (ptr = valid_ifaces; *ptr != NULL; ptr++)
	{
		if (strcmp(iface->name, *ptr) == 0)
		{
			return true;
		}
	}

	return false;
}

static int find_wan_tx_data_index(char *tx_devname)
{
	int i = 0;
	for (i = 0; i < wans_tx_data.num; i++)
	{
		if (strcmp(wans_tx_data.stats[i].tx_devname, tx_devname) == 0)
		{
			return i;
		}
	}

	return -1;
}

static int find_ifaces_stats_index(char *ifname)
{
	int i = 0;
	for (i = 0; i < ifaces_stat_len; i++)
	{
		if (strcmp(ifaces_stat[i].ifname, ifname) == 0)
		{
			return i;
		}
	}

	return -1;
}

static struct device * get_dev_by_iface(struct interface *iface, bool real_dev)
{
	struct interface *phy_if = NULL;
	struct device * ret_dev = NULL;

	if (real_dev)
	{
		if ((!strcmp(iface->name, CONNECT_IFACE_INTERNET) ||
		!strcmp(iface->name, CONNECT_IFACE_INTERNETV6)) &&
		!iface->main_dev.dev)
		{
			phy_if = vlist_find(&interfaces, CONNECT_IFACE_WAN, iface, node);
		}
	}

	if (!phy_if)
	{
		phy_if = iface;
	}

	if ((strcmp(iface->name, CONNECT_IFACE_MOBILE) == 0 || !real_dev) && iface->l3_dev.dev)
	{
		ret_dev = iface->l3_dev.dev;
	}
	else if (phy_if->main_dev.dev)
	{
		ret_dev = phy_if->main_dev.dev;
	}

	return ret_dev;
}

static bool has_two_connections(struct interface *iface)
{
	bool ret = false;
	if (strcmp(iface->name, CONNECT_IFACE_INTERNET) == 0)
	{
		if (iface->proto_handler && (strcmp(iface->proto_handler->name, "l2tp") == 0 ||
			strcmp(iface->proto_handler->name, "pptp") == 0 || 
			strcmp(iface->proto_handler->name, "pppoe") == 0))
		{
			ret = true;
		}
	}

	return ret;
}

static int wan_tx_stat_increase(struct interface *iface)
{
	int ret = 0;
	int tx_data_index = 0;
	int iface_id = 0;
	int count = 0;
	bool real_dev = true;
	static struct device * dev = NULL;
	iface_id = find_ifaces_stats_index(iface->name);
	if (iface_id < 0)
	{
		return ret;
	}

cmp:
	dev = get_dev_by_iface(iface, real_dev);
	if (!dev)
	{
		ret |= 0;
		goto nxt_conn;
	}
	tx_data_index = find_wan_tx_data_index(dev->ifname);
	if (tx_data_index < 0)
	{
		ret |= 0;
		goto nxt_conn;
	}

	if (wans_tx_data.stats[tx_data_index].snd_pkt != 0 &&
		wans_tx_data.stats[tx_data_index].snd_pkt > ifaces_stat[iface_id].last_stats[count].snd_pkt)
	{
		ret |= 1;
	}

	memcpy(&(ifaces_stat[iface_id].last_stats[count]), &(wans_tx_data.stats[tx_data_index]), sizeof(struct ipt_tx_stat));

nxt_conn:
	if (has_two_connections(iface) && count < 1)
	{
		count++;
		real_dev = false;
		goto cmp;
	}

	return ret;
}

static bool all_wans_down()
{
	struct interface *iface = NULL;
	struct interface *tmp_iface = NULL;
	vlist_for_each_element(&interfaces, iface, node)
	{
		if (!connect_ifvalid(iface))
		{
			continue;
		}

		if (iface->state != IFS_DOWN)
		{
			/* Fixed me? when pppoe disconnect, the wan interface do not disconnect... */
			if (strcmp(iface->name, CONNECT_IFACE_WAN) == 0 &&
				(tmp_iface = vlist_find(&interfaces, CONNECT_IFACE_INTERNET, tmp_iface, node)))
			{
				if (tmp_iface->proto_handler && strcmp(tmp_iface->proto_handler->name, "pppoe") == 0)
				{
					continue;
				}
			}

			return false;
		}
	}
	return true;
}

static bool all_wans_not_ondemand()
{
	struct interface *iface = NULL;
	vlist_for_each_element(&interfaces, iface, node)
	{
		if (!connect_ifvalid(iface))
		{
			continue;
		}

		if (iface->conn_mode == IFCM_DEMAND)
		{
			return false;
		}
	}
	return true;
}

static void
connect_ifup(struct interface *iface)
{
	struct interface *parent = NULL;

	if (strcmp(iface->name, CONNECT_IFACE_INTERNET) == 0)
	{
		parent = vlist_find(&interfaces, CONNECT_IFACE_WAN, iface, node);
	}
	else if (strcmp(iface->name, CONNECT_IFACE_INTERNETV6) == 0)
	{
		parent = vlist_find(&interfaces, CONNECT_IFACE_WANV6, iface, node);
	}
#if 0
	else if (strcmp(iface->name, CONNECT_IFACE_WAN) == 0)
	{
		/* If connect down the WAN_VIF, the VIF device will be removed. */
		/* While connect up the WAN_VIF, The VIF device should be added again. */
		/* Added by xlw, 2015-04-15 */
		struct device_user *main_dev = &iface->main_dev;
		if(main_dev){
			struct device *dev = main_dev->dev;
			if(dev){
				dev->set_state(dev, true);
			}
		}
	}
#endif
	if (parent && parent->state == IFS_DOWN)
	{
#if 0
		dprintf("interface(%p): %s, available: %d, connectable: %d, state: %d, conn_mode: %d\n",
			    iface, iface->name, iface->available, 
				iface->connectable, iface->state, iface->conn_mode);
#endif
		(void)interface_set_up(parent);
	}

	if (iface->state == IFS_DOWN) 
	{
		dprintf("interface(%s) set up\n", iface->name);
		(void)interface_set_up(iface);
	}
}

static void
connect_ifdown(struct interface *iface)
{
	struct interface *parent = NULL;
	bool pppoe = false;

	if (strcmp(iface->name, CONNECT_IFACE_INTERNET) == 0)
	{
		parent = vlist_find(&interfaces, CONNECT_IFACE_WAN, iface, node);
	}
	else if (strcmp(iface->name, CONNECT_IFACE_INTERNETV6) == 0)
	{
		parent = vlist_find(&interfaces, CONNECT_IFACE_WANV6, iface, node);
	}

	/* Sequential action: 
	 *   1. Down L2TP/PPTP/PPPoE;
	 *   2. Down DHCP;
	 * Make sure both PPP Termination and DHCP Release frame was transmitted.
	 */

	if (iface->state != IFS_DOWN)
	{
		dprintf("interface_set_down %s\n", iface->name);
		(void)interface_set_down(iface);
	}

	if (iface->proto_handler && strcmp(iface->proto_handler->name, "pppoe") == 0)
	{
		pppoe = true;
	}

	if (iface->state == IFS_DOWN && parent && !pppoe)
	{
        if (parent->state != IFS_DOWN)
        {
		dprintf("interface_set_down %s\n", parent->name);
		(void)interface_set_down(parent);
	}
}
}

/* Return iface's proto */
#if 0
static enum iface_proto
connect_ifproto(struct interface *iface)
{
	const struct proto_handler *handler = iface->proto_handler;

	if (handler)
	{
		if (strcmp(handler->name, "static") == 0)
		{
			return IFP_STATIC;
		}
		else if (strcmp(handler->name, "dhcp") == 0)
		{
			return IFP_DHCP;
		}
		else if (strcmp(handler->name, "pppoe") == 0)
		{
			return IFP_PPPOE;
		}
		else if (strcmp(handler->name, "l2tp") == 0)
		{
			return IFP_L2TP;
		}
		else if (strcmp(handler->name, "pptp") == 0)
		{
			return IFP_PPTP;
		}
		else if (strcmp(handler->name, "bigpond") == 0)
		{
			return IFP_BIGPOND;
		}
	}

	return IFP_INVALID;
}
#endif

static void 
connect_auto(struct interface *iface)
{
	struct interface *internet = NULL;
	struct interface *internetv6 = NULL;
	bool dhcp = false;
	bool dhcpv6 = false;
	unsigned int flags = 0;
	int ret = 0;

	internet = vlist_find(&interfaces, CONNECT_IFACE_INTERNET, internet, node);
	if (!internet && strcmp(iface->name, CONNECT_IFACE_WAN) == 0 &&
		iface->proto_handler && strcmp(iface->proto_handler->name, "dhcp") == 0)
	{
		dhcp = true;
	}

	internetv6 = vlist_find(&interfaces, CONNECT_IFACE_INTERNETV6, internetv6, node);
	if (!internetv6 && strcmp(iface->name, CONNECT_IFACE_WANV6) == 0 &&
		iface->proto_handler && strcmp(iface->proto_handler->name, "dhcp6c") == 0)
	{
		dhcpv6 = true;
	}
	
	/* device unplugged handler for DHCP */
	if (dhcp || dhcpv6)
	{
		if (iface->ifname)
		{
			ret = system_if_get_flags(iface->ifname, &flags);
			if (!ret)
			{
				iface->link_state = !!(flags & IFF_RUNNING);
			}
		}

		if (!iface->link_state)
		{
			if (iface->state == IFS_UP)
			{
				(void)interface_set_down(iface);
			}

			/* link down handled completely */
			return;
		}
	}

	if (iface->state != IFS_UP && backup_auto_dial(iface->name))
	{
		connect_ifup(iface);
	}
}

static void 
connect_manual(struct interface *iface)
{
	time_t now = 0;
	int valid = 0;
	int ret = 0;

	dprintf("interface: %s, state: %d, idle: %ld\n", 
		iface->name, iface->state, iface->conn_time.idle);

	if (iface->conn_time.idle == 0)
	{
		return;
	}

	ret = connect_ipt_outgone(iface);
	dprintf("lan -> wan had outgoing pkts: %s\n", ret ? "yes" : "no");
	now = time(NULL);
	if (!iface->conn_time.last)
	{
		iface->conn_time.last = now;
	}
	if (ret)
	{
		/* lan -> wan had outgoing pkts */
		iface->conn_time.last = now;
		valid = 1;
	}
	else if ((now - iface->conn_time.last) >= iface->conn_time.idle)
	{
		dprintf("connectable timeout\n");
		valid = 0;
	}
	else
	{
		valid = 1;
	}

	if (!valid)
	{
		connect_ifdown(iface);
	}

	return; 
}

static void 
connect_demand(struct interface *iface)
{
	struct interface *tmp_iface = NULL;
	time_t now;
	int valid = 0;
	int ret = 0;

	dprintf("interface: %s, state: %d, idle: %ld\n", 
		iface->name, iface->state, iface->conn_time.idle);

	if (all_wans_down())
	{
		tmp_iface = vlist_find(&interfaces, CONNECT_IFACE_WAN, tmp_iface, node);
	    if (tmp_iface == NULL)
	    {
	        return;
	    }
		ret = connect_ipt_outgone(tmp_iface);
		tmp_iface = NULL;
	}
	else
	{
		ret = connect_ipt_outgone(iface);
	}
	dprintf("lan -> wan had outgoing pkts: %s\n", ret ? "yes" : "no");
	now = time(NULL);
	if (ret)
	{
		/* lan -> wan had outgoing pkts */
		iface->conn_time.last = now;
		valid = 1;
	}
	else if (!iface->conn_time.idle)
	{
		dprintf("ignore connect handle\n");
		valid = -1;
	}
	else if ((now - iface->conn_time.last) >= iface->conn_time.idle)
	{
		dprintf("connectable timeout\n");
		valid = 0;
	}
	else
	{
		dprintf("connectable valid\n");
		valid = 1;
	}

	if (valid > 0)
	{
		if (all_wans_down())
		{
			vlist_for_each_element(&interfaces, tmp_iface, node)
	        {
	            if (!connect_ifvalid(tmp_iface))
	            {
	                continue;
	            }

	            if (tmp_iface->conn_mode != IFCM_DEMAND)
	            {
	                continue;
	            }

	            connect_ifup(tmp_iface);

	            tmp_iface->conn_time.last = now;
	        }
		}
	}
	else if (valid < 0)
	{
		/* ignore */
	}
	else 
	{
		connect_ifdown(iface);
		tmp_iface = NULL;
		tmp_iface = vlist_find(&interfaces, CONNECT_IFACE_WAN, tmp_iface, node);
		if (tmp_iface)
		{
			connect_ipt_outgone(tmp_iface);	/* just syn wan stats to avoid auto dial beaucause error data */
		}
	}

    if (all_wans_down())
	{
        connect_dft_route(1);
	}
    else
    {
        connect_dft_route(0);
    }

	return;
}

/* Time based connection: PPPoE */
static void 
connect_timebased(struct interface *iface)
{
	struct tm cur;
	time_t cur_sec;
	int valid = 0;
	int ret = 0;

	ret = system_get_localtime(&cur);
	if (ret != 0)
	{
		return;
	}

	cur_sec = cur.tm_hour * 60 * 60 + cur.tm_min * 60 + cur.tm_sec;
	if (cur_sec > iface->conn_time.start && cur_sec < iface->conn_time.end)
	{
		valid = 1;
	}

	if (valid)
	{
		connect_ifup(iface);
	}
	else
	{
		connect_ifdown(iface);
	}
}

char wan_ifname[20] = {0};
static int get_uci_ifname(char * ifname)
{
	FILE *fp = NULL;
	char status[32] = {0};
	char * p = NULL;
	fp = popen("uci get network.wan.ifname", "r");
	if(fp != NULL)
	{
		fgets(status, sizeof(status), fp);
		pclose(fp);
		if( (p = strchr(status, '\n')) != NULL) 
		{
			strncpy(ifname, status, p - status); /* ifname do not include "\n" */
		}
		else
		{
			strncpy(ifname, status, strlen(status));
		}
		return 0;
	}
	return -1;
}


static int 
connect_process()
{
	struct interface *iface, *phy_if = NULL;
	struct device *dev = NULL;
	int i = 0;
	bool link = true;

	if (all_wans_not_ondemand())
	{
		connect_dft_route(0);
	}

	vlist_for_each_element(&interfaces, iface, node) 
	{
		phy_if = NULL;
		if (!connect_ifvalid(iface))
		{
			continue;
		}

		/* dprintf("interface(%p): %s, available: %d, connectable: %d, state: %d, conn_mode: %d\n",
			    iface, iface->name, iface->available, 
				iface->connectable, iface->state, iface->conn_mode); */

		if ((i = find_ifaces_stats_index(iface->name)) < 0)
		{
			i = ifaces_stat_len;
			strcpy(ifaces_stat[i].ifname, iface->name);
			ifaces_stat_len++;
		}

		 if ((!strcmp(iface->name, CONNECT_IFACE_INTERNET) ||
			!strcmp(iface->name, CONNECT_IFACE_INTERNETV6)) &&
			!iface->main_dev.dev)
		 {
			phy_if = vlist_find(&interfaces, CONNECT_IFACE_WAN, iface, node);
		 }
		 if (!phy_if)
		 {
			phy_if = iface;
		 }
		if (phy_if->main_dev.dev)
		{
			/* if wan interface is "br-wan", refer network.wan.ifname(eth0.4094) to indicate wan linkstate */
			if(!strncmp(phy_if->main_dev.dev->ifname, "br-wan", 6)) 
			{
				if((dev = device_get(wan_ifname, false)) )
				{
					link = !!dev->link_active;
				}
				else
				{
					link = !!phy_if->main_dev.dev->link_active;
				}
			}
			else
			{
				link = !!phy_if->main_dev.dev->link_active;
			}
			device_set_link(phy_if->main_dev.dev, link);
		}
		
		if ((!iface->connectable || !link) && (iface->proto_handler && strcmp(iface->proto_handler->name, "static")))
		{
			if ((iface->state == IFS_SETUP || iface->state == IFS_UP) && strcmp(iface->name, CONNECT_IFACE_MOBILE) != 0)
					connect_ifdown(iface);

			iface->conn_time.last = 0;
			continue;
		}

		for (i = 0; i < ARRAY_SIZE(conn_handlers); i++)
		{
			if (iface->conn_mode == conn_handlers[i].mode)
			{
				conn_handlers[i].process(iface);
				break;
			}

			/* Invalid connect mode, ignore */
		}
	}

	return 0;
}

static void 
connect_timeout(struct uloop_timeout *timeout)
{
	get_tx_info = false;
	(void)connect_process();
	(void)uloop_timeout_set(timeout, CONNECT_TIMEOUT);
}

#if 0
static int
connect_dev_hasip(const char *ifname)
{
	uint32_t ip = 0;
	int ret = 0;

	ret = system_if_get_addr(ifname, &ip);
	if (ret != 0 || ip == 0)
	{
		return 0;
	}

	return 1;
}
#endif

static void
connect_dft_route(int add)
{
	const char *dftgw = "1.0.0.1";
	const char *wan_ifname;
	const char *lan_ifname;
	const char *lan_ipaddr;
	uint8_t macaddr[CONNECT_MACADDR_LEN];
	int ret = 0;
	char rlan_ifname[IFNAMSIZ];
	int tmp_pos = 0;

	wan_ifname = config_option_str(CONNECT_IFACE_WAN, "ifname");
	if (!wan_ifname) 
	{
		dprintf("interface %s: invalid option ifname\n", CONNECT_IFACE_WAN);
		return;
	}

	if (add)
	{
#if 0
		if (tmp_ip_set || connect_dev_hasip(wan_ifname))
		{
			/* tmp ip addr for wan's device is set already, or it has ip */
			return;
		}
#endif

		lan_ifname = config_option_str(CONNECT_IFACE_LAN, "ifname");
		if (!lan_ifname)
		{
			dprintf("interface %s: invalid option ifname\n", CONNECT_IFACE_LAN);
			return;
		}
		else
		{
			/* lan_ifname will be "eth1.1 eth1.2 eth1.3 eth1.4", in this case, we get mac addr of eth1 only. */
			memset(rlan_ifname, 0, sizeof(rlan_ifname));
			strncpy(rlan_ifname, lan_ifname, sizeof(rlan_ifname));
			tmp_pos = 0;
			while(tmp_pos < sizeof(rlan_ifname))
			{
				if (rlan_ifname[tmp_pos] == '.' || rlan_ifname[tmp_pos] == ' ')
				{
					rlan_ifname[tmp_pos] = '\0';
					break;
				}
				tmp_pos++;
			}
			if (tmp_pos == 0 || strlen(rlan_ifname) >= sizeof(rlan_ifname))
			{
				dprintf("interface %s: invalid option ifname\n", CONNECT_IFACE_LAN);
				return;
			}
		}

		lan_ipaddr = config_option_str(CONNECT_IFACE_LAN, "ipaddr");
		if (!lan_ipaddr)
		{
			dprintf("interface %s: invalid option ipaddr\n", CONNECT_IFNAME_LAN);
			return;
		}

		ret = system_if_get_macaddr(rlan_ifname, macaddr);
		if (ret != 0)
		{
			dprintf("ifname %s: can't get macaddr\n", rlan_ifname);
			return;
		}

		/* system_exec_fmt("ifconfig %s 0.0.0.0", wan_ifname); */
		memset(tmp_ip_str, 0, sizeof(tmp_ip_str));
		if ((macaddr[CONNECT_MACADDR_LEN - 1] != 0x01) &&
			(macaddr[CONNECT_MACADDR_LEN - 1] != 0xFF))
		{
			snprintf(tmp_ip_str, sizeof(tmp_ip_str), "1.0.%d.%d", 
				macaddr[CONNECT_MACADDR_LEN - 2], 
				macaddr[CONNECT_MACADDR_LEN - 1]);
		}
		else
		{
			snprintf(tmp_ip_str, sizeof(tmp_ip_str), "1.0.%d.10", 
				macaddr[CONNECT_MACADDR_LEN - 2]);
		}

		/* system_exec_fmt("ifconfig %s %s", wan_ifname, tmp_ip_str); */
		system_exec_fmt("ip addr add %s/8 dev %s", tmp_ip_str, wan_ifname);
		system_exec_fmt("ip route replace default via %s dev %s", dftgw, wan_ifname);
		system_exec_fmt("ifconfig %s up", wan_ifname);
		system_exec_fmt("nat del dns && nat add dns { %s %s }", lan_ipaddr, dftgw);
		tmp_ip_set = 1;
	}
	else 
	{
		if (tmp_ip_set)
		{
			/* delete tmp ip and default route */
			system_exec_fmt("ip addr del %s/8 dev %s", tmp_ip_str, wan_ifname);
			/* dnsproxy will execute nat del dns */
			/* system_exec_cmd("nat del dns"); */
			tmp_ip_set = 0;
		}
	}
}

static int 
connect_ipt_stat()
{
	socklen_t len = sizeof(wans_tx_data);
	int sock = -1;
	int ret = 0;

	sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if (sock < 0)
	{
		dprintf("create socket failed\n");
		ret = -1;
		goto out;
	}

	memset(&wans_tx_data, 0, len);
	ret = getsockopt(sock, IPPROTO_IP, IPT_STAT_GET_WANS_TX_STAT, &wans_tx_data, &len);
	if (ret != 0)
	{
		dprintf("setsockopt failed to get stats\n");
		goto out;
	}
	else if (len != sizeof(wans_tx_data))
	{
		dprintf("len %d != %d\n", len, sizeof(wans_tx_data));
		ret = -1;
		goto out;
	}

	ret = 0;

out:
	if (sock > -1)
	{
		close(sock);
	}
	return ret;
}

static int
connect_ipt_outgone(struct interface *iface)
{
	int ret = 0;

    if (!get_tx_info)
    {
        ret = connect_ipt_stat();
        if (ret != 0)
        {
            return 0;
        }
        get_tx_info = true;
    }

    ret = wan_tx_stat_increase(iface);

    return ret;
}

static int
connect_cfg_ip4addr(const char *secname, const char *name, uint32_t *ip4addr)
{
	const char *val = NULL;
	struct in_addr addr;
	int ret = 0;

	val = config_option_str(secname, name);
	if (!val) 
	{
		dprintf("interface lan doesn't exist ipaddr\n");
		ret = -1;
		goto out;
	}

	ret = inet_aton(val, &addr);
	if (ret == 0)
	{
		ret = -1;
		dprintf("Invalid lan ipaddr\n");
		goto out;
	}

	*ip4addr = ntohl(addr.s_addr);
	ret = 0;

out:
	return ret;
}

static int 
connect_ipt_init()
{
	struct ipt_net ipnet;
	int sock = -1;
	int ret = 0;

#if 0
	ret = system_if_get_addr(CONNECT_IFNAME_LAN, &ipnet.ip);
	if (ret != 0)
	{
		dprintf("system_if_get_addr(lan) failed\n");
		goto out;
	}

	ret = system_if_get_mask(CONNECT_IFNAME_LAN, &ipnet.mask);
	if (ret != 0)
	{
		dprintf("system_if_get_mask(lan) failed\n");
		goto out;
	}

#else
	ret = connect_cfg_ip4addr(CONNECT_IFACE_LAN, "ipaddr", &ipnet.ip);
	if (ret != 0)
	{
		goto out;
	}

	ret = connect_cfg_ip4addr(CONNECT_IFACE_LAN, "netmask", &ipnet.mask);
	if (ret != 0)
	{
		goto out;
	}
#endif

	sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if (sock < 0) 
	{
		dprintf("create socket failed\n");
		ret = -1;
		goto out;
	}

	ret = setsockopt(sock, IPPROTO_IP, IPT_STAT_DEL_ALL, NULL, 0);
	if (ret != 0)
	{
		dprintf("setsockopt stats del all failed");
		goto out;
	}

	ret = setsockopt(sock, IPPROTO_IP, IPT_STAT_SET_NET, &ipnet, sizeof(ipnet));
	if (ret != 0)
	{
		dprintf("setsockopt stats set net failed");
		goto out;
	}

	ret = 0;

out:
	if (sock > -1)
	{
		close(sock);
	}
	return ret;
}

void 
connect_dump_info(struct blob_buf *b)
{
	blobmsg_add_u32(b, "timeout remaining", uloop_timeout_remaining(&timeout));
}

int 
connect_init()
{
	int ret = 0;

	if (initialized)
	{
		return ret;
	}

	memset(ifaces_stat, 0, sizeof(struct iface_stat) * MAX_CONNECT_IFACE_NUM);
	ifaces_stat_len = 0;
	ret = connect_ipt_init();
	if (ret != 0)
	{
		dprintf("connect_ipt_init failed\n");
		return ret;
	}

	(void)connect_ipt_stat();

	timeout.cb = connect_timeout;
	ret = uloop_timeout_set(&timeout, CONNECT_TIMEOUT);

	detect_init_exit(true);
	ret = get_uci_ifname(wan_ifname);
	if (ret != 0)
	{
		dprintf("get_uci_ifname failed\n");
		return ret;
	}

	initialized = 1;
	return ret;
}

void 
connect_exit()
{
	if (initialized)
	{
		detect_init_exit(false);
		uloop_timeout_cancel(&timeout);
		/* delete default route */
		connect_dft_route(0);
		memset(wan_ifname, 0, 20);
		initialized = 0;
	}
}

