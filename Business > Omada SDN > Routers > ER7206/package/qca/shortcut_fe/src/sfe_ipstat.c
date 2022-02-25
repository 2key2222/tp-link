/*! Copyright(c) 2008-2016 Shenzhen TP-LINK Technologies Co.Ltd.
 *
 *\file     ipstat_sfe.c
 *\brief
 *\details
 *
 *\author   Yuan Fengjia
 *\version  0.0.1
 *\date     18May16
 *
 *\warning
 *
 *\history  \arg    0.0.1, 22May15, Yuan Fengjia, Create the file.
 *\history  \arg    0.0.2, 13Oct17, Zhang Zhongwei, Modify the file.
 */

/**************************************************************************************************/
/*                                      CONFIGURATIONS                                            */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      INCLUDE_FILES                                             */
/**************************************************************************************************/
#include <linux/types.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/module.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netfilter_bridge.h>
#include <linux/spinlock.h>
#include <linux/timer.h>
#include <linux/version.h>
#include <linux/proc_fs.h>
#include <net/neighbour.h>
#include <net/arp.h>
#include <linux/list.h>
#include <linux/hash.h>
#include <linux/if_bridge.h>

#include "sfe_cm.h"
#include "sfe_ipstat.h"
/**************************************************************************************************/
/*                                      DEFINES                                                   */
/**************************************************************************************************/
#define ETHER_PAYLOAD_LEN           14
#define LAN_IFNAME                  "br-lan"
#define LAN_IFNAME_LEN              6
#define SFE_IPSTAT_PROC_NAME        "sfe_ipstat"
#define SFE_IPMAC_PROC_NAME         "sfe_ip_mac"
#define SFE_IPSTAT_STEP_PROC_NAME   "sfe_ipstat_step"
#define MAX_IP_STR_LEN              20

#define IPSTAT_HASH_BITNUM     (10)
#define IPSTAT_HASHTBL_MAX     (1UL << IPSTAT_HASH_BITNUM)
#define IPSTAT_ENTRIES_MAX     (IPSTAT_HASHTBL_MAX << 2)
#define ARP_GC_THRESH_TIME     (60)


#define ipstat_debug(fmt, args...)\
        /*printk(KERN_INFO"[LOG]%s,%d:"fmt"\r\n", __FUNCTION__,__LINE__,##args)*/

/**************************************************************************************************/
/*                                      TYPES                                                     */
/**************************************************************************************************/
typedef struct _IP_SUBNET
{
    u_int32_t ip;
    u_int32_t mask;
}IP_SUBNET;

typedef struct _IPSTAT_STATISTIC
{
    u_int32_t src_packets;
    u_int32_t src_bytes;

    u_int32_t dst_packets;
    u_int32_t dst_bytes;
}IPSTAT_STATISTIC;

typedef struct _IPSTAT_IP_ENTRY
{
    u_int32_t ip;
    u_int8_t  mac[ETH_ALEN];
    IPSTAT_STATISTIC cur_stat;
    IPSTAT_STATISTIC cur_stat_update;
    IPSTAT_STATISTIC pre_stat_update;

    unsigned long arp_timer;
    u_int32_t offline;

    struct hlist_node hostHashNode;
    struct _IPSTAT_IP_ENTRY *pNextLruHost;
    struct _IPSTAT_IP_ENTRY *pPrevLruHost;
}IPSTAT_IP_ENTRY;

typedef struct _IPSTAT_IP_MNGR
{
    IPSTAT_IP_ENTRY mem_pool[IPSTAT_ENTRIES_MAX];
    int used;
    IPSTAT_IP_ENTRY hostLstHead;
    IPSTAT_IP_ENTRY *pLastLruHost;
    struct hlist_head hostHashTbl[IPSTAT_HASHTBL_MAX];
}IPSTAT_IP_MNGR;

/**************************************************************************************************/
/*                                      EXTERN_PROTOTYPES                                         */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      LOCAL_PROTOTYPES                                          */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      VARIABLES                                                 */
/**************************************************************************************************/
IP_SUBNET g_ip_subnet;
static struct proc_dir_entry *sfe_ipstat_proc = NULL;
static struct proc_dir_entry *sfe_ipmac_proc = NULL;
static struct proc_dir_entry *sfe_ipstat_step_proc = NULL;
static DEFINE_SPINLOCK(g_stat_lock);
static IPSTAT_IP_MNGR g_ip_entry_table;
static int g_interval_time = 1;
static int g_interval_update_time = 5;
static struct timer_list g_arp_timer;
static struct timer_list g_update_timer;
volatile unsigned long g_cur_timer_cycle = 0;
volatile unsigned long g_cur_update_timer_cycle = 0;
int sfe_ipstat_switch = 1;

/**************************************************************************************************/
/*                                      LOCAL_FUNCTIONS                                           */
/**************************************************************************************************/
static void ipstat_lock(void)
{
    spin_lock_bh(&g_stat_lock);
}

static void ipstat_unlock(void)
{
    spin_unlock_bh(&g_stat_lock);
}

void ip_entry_init(void)
{
    int idx = 0;

    memset(&g_ip_entry_table, 0, sizeof(g_ip_entry_table));

    g_ip_entry_table.pLastLruHost = &g_ip_entry_table.hostLstHead;
    for ( idx = 0; idx < IPSTAT_HASHTBL_MAX; idx++ ) {
        INIT_HLIST_HEAD(&g_ip_entry_table.hostHashTbl[idx]);
    }

    return;
}

static u_int32_t do_hash_key(u_int32_t ipaddr)
{
    u_int32_t hashIn = 0;
    hashIn = ipaddr;
    return hash_32(hashIn, IPSTAT_HASH_BITNUM);
}

IPSTAT_IP_ENTRY *ipstat_get_entry(u_int32_t ipaddr)
{
    ipstat_debug("ipaddr:%x",ipaddr);
    u_int32_t hashKey = do_hash_key(ipaddr);
    struct hlist_head *head = &g_ip_entry_table.hostHashTbl[hashKey];
    ipstat_debug();
    struct hlist_node *_p = NULL;
    IPSTAT_IP_ENTRY *pHost = NULL;

    ipstat_debug();
    if ( ipaddr == 0 || head == NULL) {
        return NULL;
    }

    ipstat_debug();
    hlist_for_each(_p, head) {
        ipstat_debug();
        pHost = hlist_entry(_p, IPSTAT_IP_ENTRY, hostHashNode);
        if ( pHost == NULL ) {
            continue ;
        }
        ipstat_debug("pHost:%x",pHost);
        if ( pHost->ip == ipaddr ) {
            ipstat_debug();
            break;
        }
        ipstat_debug();
    }
    ipstat_debug();
    return ((_p == NULL) ? NULL : pHost);
}

static void init_host(IPSTAT_IP_ENTRY *pHost, u_int32_t ipaddr, const u_int8_t mac[ETH_ALEN])
{
    memset(pHost, 0, sizeof(IPSTAT_IP_ENTRY));
    pHost->ip = ipaddr;
    if (mac[0] != 0 || mac[1] != 0 || mac[2] != 0 || mac[3] != 0 || mac[4] != 0 || mac[5] != 0) {
        memcpy(&pHost->mac, mac, ETH_ALEN);
    }
    pHost->offline = 1;
}

static void add_entry_toLruLst(IPSTAT_IP_ENTRY *pHost)
{
    if (g_ip_entry_table.pLastLruHost == &g_ip_entry_table.hostLstHead) {
        g_ip_entry_table.pLastLruHost = pHost;
    }

    pHost->pPrevLruHost = &g_ip_entry_table.hostLstHead;
    pHost->pNextLruHost = g_ip_entry_table.hostLstHead.pNextLruHost;

    if (pHost->pNextLruHost != NULL) {
        pHost->pNextLruHost->pPrevLruHost = pHost;
    }
    g_ip_entry_table.hostLstHead.pNextLruHost = pHost;

    return;
}

static void add_entry_toHashTbl(IPSTAT_IP_ENTRY *pHost)
{
    u_int32_t hashKey = do_hash_key(pHost->ip);
    struct hlist_head *head = &g_ip_entry_table.hostHashTbl[hashKey];
    hlist_add_head(&pHost->hostHashNode, head);

    return;
}

static void add_entry(IPSTAT_IP_ENTRY *pHost)
{
    add_entry_toLruLst(pHost);
    add_entry_toHashTbl(pHost);
}

static void remove_entry_fromHashTbl(IPSTAT_IP_ENTRY *pHost)
{
    hlist_del_init(&pHost->hostHashNode);
}

static void remove_entry_fromLruLst(IPSTAT_IP_ENTRY *pHost)
{
    pHost->pPrevLruHost->pNextLruHost = pHost->pNextLruHost;

    if (g_ip_entry_table.pLastLruHost == pHost) {
        g_ip_entry_table.pLastLruHost = pHost->pPrevLruHost;
    } else {
        pHost->pNextLruHost->pPrevLruHost = pHost->pPrevLruHost;
    }

    return;
}

static void remove_entry(IPSTAT_IP_ENTRY *pHost)
{
    remove_entry_fromLruLst(pHost);
    remove_entry_fromHashTbl(pHost);
}

static void replace_entry(IPSTAT_IP_ENTRY *pHost, u_int32_t ipaddr, const u_int8_t mac[ETH_ALEN])
{
    remove_entry(pHost);
    init_host(pHost, ipaddr, mac);
    add_entry(pHost);
}

static IPSTAT_IP_ENTRY *replace_exist_entry(u_int32_t ipaddr, const u_int8_t mac[ETH_ALEN])
{
    IPSTAT_IP_ENTRY *pHost = NULL;

    pHost = g_ip_entry_table.pLastLruHost;
    if (pHost == NULL ) {
        return NULL;
    }

    replace_entry(pHost, ipaddr, mac);
    return pHost;
}

static IPSTAT_IP_ENTRY *add_newEntry(u_int32_t ipaddr, const u_int8_t mac[ETH_ALEN])
{
    IPSTAT_IP_ENTRY *pNewHost = NULL;

    if (g_ip_entry_table.used >= IPSTAT_ENTRIES_MAX) {
        return replace_exist_entry(ipaddr, mac);
    }

    pNewHost = &g_ip_entry_table.mem_pool[g_ip_entry_table.used];
    g_ip_entry_table.used ++;
    init_host(pNewHost, ipaddr, mac);

    add_entry(pNewHost);

    return pNewHost;
}

IPSTAT_IP_ENTRY *find_ipentry(u_int32_t ipaddr, const u_int8_t mac[ETH_ALEN])
{
    IPSTAT_IP_ENTRY *pHost = NULL;
    ipstat_debug();
    pHost = ipstat_get_entry(ipaddr);
    if (pHost) {
            return pHost;
    }

    ipstat_debug();
    pHost = add_newEntry(ipaddr, mac);
    return pHost;
}

IPSTAT_IP_ENTRY *get_firstLruHost(void)
{
    return g_ip_entry_table.hostLstHead.pNextLruHost;
}

int format_ip(char *buff, u_int32_t ip)
{
    int len;
	ip = ntohl(ip);
    len = sprintf(buff, "%d.%d.%d.%d", (u_int8_t)(ip >> 24), (u_int8_t)(ip >> 16), (u_int8_t)(ip >> 8), (u_int8_t)(ip));
   // len = sprintf(buff, "%d.%d.%d.%d", (u_int8_t)(ip), (u_int8_t)(ip >> 8), (u_int8_t)(ip >> 16), (u_int8_t)(ip >> 24));
    return len;
}

int format_mac(char *buff, u_int8_t  mac[ETH_ALEN])
{
    int len;
    len = sprintf(buff, ";%02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return len;
}

static int ipstat_proc_show(struct seq_file *seq, void *v)
{
    IPSTAT_IP_ENTRY *pHost = NULL;
    const int MAX_LINE_LEN = 512;
    char line[MAX_LINE_LEN];
    char *cur = &line[0];
    int len;

    spin_lock_bh(&g_stat_lock);
    pHost = get_firstLruHost();
    while(pHost != NULL)
    {
        cur = &line[0];
        len = format_ip(cur, pHost->ip);
        cur += len;
        len = sprintf(cur, ";%u;%u;%u;%u\n",
                      pHost->cur_stat.src_packets,
                      pHost->cur_stat.src_bytes,
                      pHost->cur_stat.dst_packets,
                      pHost->cur_stat.dst_bytes);
        cur += len;
        seq_puts(seq, line);
        pHost = pHost->pNextLruHost;
    }
    spin_unlock_bh(&g_stat_lock);

    return 0;
}

static int ipstat_step_proc_show(struct seq_file *seq, void *v)
{
    IPSTAT_IP_ENTRY *pHost = NULL;
    const int MAX_LINE_LEN = 512;
    char line[MAX_LINE_LEN];
    char *cur = &line[0];
    int len;
    u_int32_t denominator = (g_interval_update_time * 1024); // for KBps unit

    spin_lock_bh(&g_stat_lock);
    pHost = get_firstLruHost();
    while (pHost != NULL) {
        cur = &line[0];
        len = format_ip(cur, pHost->ip);
        cur += len;
        // calc KB/s and Pkt/s
        len = sprintf(cur, ";%u;%u;%u;%u",
                      ((pHost->cur_stat_update.src_packets - pHost->pre_stat_update.src_packets) /g_interval_update_time),
                      ((pHost->cur_stat_update.src_bytes - pHost->pre_stat_update.src_bytes) / denominator),
                      ((pHost->cur_stat_update.dst_packets - pHost->pre_stat_update.dst_packets) / g_interval_update_time),
                      ((pHost->cur_stat_update.dst_bytes - pHost->pre_stat_update.dst_bytes) / denominator)
                     );
        cur += len;
        len = sprintf(cur, ";%u;%u;%u;%u\n",
                      pHost->cur_stat.src_packets,
                      pHost->cur_stat.src_bytes,
                      pHost->cur_stat.dst_packets,
                      pHost->cur_stat.dst_bytes);
        cur += len;
        seq_puts(seq, line);
        pHost = pHost->pNextLruHost;
    }
    spin_unlock_bh(&g_stat_lock);

    return 0;
}

static int ipmac_proc_show(struct seq_file *seq, void *v)
{
    IPSTAT_IP_ENTRY *pHost = NULL;
    const int MAX_LINE_LEN = 512;
    char line[MAX_LINE_LEN];
    char *cur = &line[0];
    int len;

    ipstat_debug();
    spin_lock_bh(&g_stat_lock);
    pHost = get_firstLruHost();
    while (pHost != NULL) {
        cur = &line[0];
        if (pHost->offline) {
            ipstat_debug("%x is offline",pHost->ip);
            pHost = pHost->pNextLruHost;
            continue ;
        }
        len = format_ip(cur, pHost->ip);
        cur += len;
        len = format_mac(cur, pHost->mac);
        cur += len;
        seq_puts(seq, line);
        pHost = pHost->pNextLruHost;
    }
    spin_unlock_bh(&g_stat_lock);
    ipstat_debug();

    return 0;
}

static int ipstat_proc_open(struct inode *inode, struct file *fp)
{
    return single_open(fp, ipstat_proc_show, inode->i_private);
}

static int ipmac_proc_open(struct inode *inode, struct file *fp)
{
    return single_open(fp, ipmac_proc_show, inode->i_private);
}

static int ipstat_step_proc_open(struct inode *inode, struct file *fp)
{
    return single_open(fp, ipstat_step_proc_show, inode->i_private);
}

static int parse_para(const char *input, char lanIp[MAX_IP_STR_LEN + 1], char lanMask[MAX_IP_STR_LEN + 1])
{
    char *space = NULL;
    int lanIpLen;
    int lanMaskLen;

    space = strchr(input, ' ');
    if (NULL == space) {
        printk("input para format error!\n");
        return -1;
    }

    lanIpLen = space - input;
    if (lanIpLen > MAX_IP_STR_LEN) {
        printk("input para too long!\n");
        return -1;
    }
    strncpy(lanIp, input, lanIpLen);
    lanIp[lanIpLen] = '\0';

    lanMaskLen = strlen(space + 1);
    if (lanMaskLen > MAX_IP_STR_LEN) {
            printk("input para too long!\n");
            return -1;
    }
    strncpy(lanMask, (space + 1), lanMaskLen);
    lanMask[lanMaskLen] = '\0';

    return 0;
}

static int parse_ip(char *ipStr, u_int32_t ipData[4])
{
    int scanResult;
    int idx;

    scanResult = sscanf(ipStr, "%u.%u.%u.%u", &ipData[0], &ipData[1], &ipData[2], &ipData[3]);
    if (scanResult != 4) {
        return -1;
    }

    for (idx = 0; idx < 4; idx++) {
        if (ipData[idx] > 255) {
                return -1;
        }
    }

    return 0;
}

static int update_config(u_int32_t addr[4], u_int32_t mask[4])
{
    g_ip_subnet.ip = htonl( (addr[0] << 24) | (addr[1] << 16) | (addr[2] << 8) | (addr[3]));
    g_ip_subnet.mask = htonl( (mask[0] << 24) | (mask[1] << 16) | (mask[2] << 8) | (mask[3]));
    printk(KERN_INFO"Update Subnet-> ip: %08X, mask: %08X\n", g_ip_subnet.ip, g_ip_subnet.mask);
    return 0;
}

static int ipstat_proc_write(struct file *fp, const char __user *buff, size_t len, loff_t *ppos)
{
    char lanIp[MAX_IP_STR_LEN + 1];
    char lanMask[MAX_IP_STR_LEN + 1];
    u_int32_t addr[4];
    u_int32_t mask[4];
    int ret;

    ipstat_debug();
    ret = parse_para(buff, lanIp, lanMask);
    if (ret != 0) {
        return -1;
    }

    ret = parse_ip(lanIp, addr);
    if (ret != 0) {
        printk("[stat]Input ip invalid!\n");
        return -1;
    }

    ret = parse_ip(lanMask, mask);
    if (ret != 0) {
        printk("[stat]Input mask invalid!\n");
        return -1;
    }

    ipstat_debug();
    update_config(addr, mask);

    return len;
}

static const struct file_operations stat_file_op =
{
    .open    = ipstat_proc_open,
    .read    = seq_read,
    .write   = ipstat_proc_write,
    .llseek  = seq_lseek,
    .release = single_release,
};

static const struct file_operations ipmac_file_op =
{
    .open    = ipmac_proc_open,
    .read    = seq_read,
    .write   = seq_write,
    .llseek  = seq_lseek,
    .release = single_release,
};

static const struct file_operations ipstat_step_file_op =
{
    .open    = ipstat_step_proc_open,
    .read    = seq_read,
    .write   = seq_write,
    .llseek  = seq_lseek,
    .release = single_release,
};

static int creat_proc_file (void)
{
    if ( sfe_ipstat_proc != NULL ) {
            return -ENOENT;
    }
    sfe_ipstat_proc = proc_create(SFE_IPSTAT_PROC_NAME, 0644, init_net.proc_net, &stat_file_op);
    if (!sfe_ipstat_proc) {
        printk("Create proc file %s failed!\n", SFE_IPSTAT_PROC_NAME);
        return -ENOENT;
    }

    if ( sfe_ipmac_proc != NULL ) {
        return -ENOENT;
    }
    sfe_ipmac_proc = proc_create(SFE_IPMAC_PROC_NAME, 0644, init_net.proc_net, &ipmac_file_op);
    if (!sfe_ipmac_proc) {
        printk("Create proc file %s failed!\n", SFE_IPMAC_PROC_NAME);
        return -ENOENT;
    }

    if ( sfe_ipstat_step_proc != NULL ) {
        return -ENOENT;
    }
    sfe_ipstat_step_proc = proc_create(SFE_IPSTAT_STEP_PROC_NAME, 0644, init_net.proc_net, &ipstat_step_file_op);
    if (!sfe_ipstat_step_proc) {
        printk("Create proc file %s failed!\n", SFE_IPSTAT_STEP_PROC_NAME);
        return -ENOENT;
    }

    return 0;
}

static void remove_proc_file(void)
{
    if ( sfe_ipstat_proc != NULL ) {
        remove_proc_entry(SFE_IPSTAT_PROC_NAME, init_net.proc_net);
    }

    if ( sfe_ipmac_proc != NULL ) {
        remove_proc_entry(SFE_IPMAC_PROC_NAME, init_net.proc_net);
    }

    if ( sfe_ipstat_step_proc != NULL ) {
        remove_proc_entry(SFE_IPSTAT_STEP_PROC_NAME, init_net.proc_net);
    }
}

void gc_thresh_entry(IPSTAT_IP_ENTRY *pHost)
{
    pHost->arp_timer = g_cur_timer_cycle;
    pHost->offline = 0;
}

void refresh_entry_mac(IPSTAT_IP_ENTRY *pHost, const u_int8_t mac[ETH_ALEN])
{
    if (mac[0] != 0 || mac[1] != 0 || mac[2] != 0 || mac[3] != 0 || mac[4] != 0 || mac[5] != 0) {
        memcpy(&pHost->mac, mac, ETH_ALEN);
    }
}

void ipstat_tx(IPSTAT_IP_ENTRY *pHost, u_int32_t proto, u_int32_t len)
{

    pHost->cur_stat.src_bytes += len;
    pHost->cur_stat.src_packets += 1;

    gc_thresh_entry(pHost);
}

void ipstat_rx(IPSTAT_IP_ENTRY *pHost, u_int32_t proto, u_int32_t len)
{
    pHost->cur_stat.dst_bytes += len;
    pHost->cur_stat.dst_packets += 1;

    gc_thresh_entry(pHost);
}

void check_offline_entry(unsigned long curTime, IPSTAT_IP_ENTRY *pHost)
{
    if (pHost->offline == 1) {
        return;
    }

    if (time_after(curTime, pHost->arp_timer + HZ*ARP_GC_THRESH_TIME)) {
        ipstat_debug("%x is offline",pHost->ip);
        pHost->offline = 1;
    }
}

void entry_timer_proc(unsigned long curTime)
{
    IPSTAT_IP_ENTRY *pHost = NULL;

    ipstat_lock();
    pHost = get_firstLruHost();
    while (pHost != NULL) {
        check_offline_entry(curTime, pHost);
        pHost = pHost->pNextLruHost;
    }
    ipstat_unlock();
}

void arp_timer_proc(unsigned long nul)
{
    entry_timer_proc(g_cur_timer_cycle);
    g_cur_timer_cycle = jiffies + g_interval_time * HZ;
    mod_timer(&g_arp_timer, g_cur_timer_cycle);
}

void arp_timer_init(void)
{
    init_timer(&g_arp_timer);
    g_arp_timer.data     = (unsigned long)0;
    g_arp_timer.function = arp_timer_proc;
    arp_timer_proc(0);
}

void arp_timer_exit(void)
{
    del_timer(&g_arp_timer);
}

void update_timer_proc(unsigned long nul)
{
    IPSTAT_IP_ENTRY *pHost = NULL;

    ipstat_lock();
    pHost = get_firstLruHost();
    while(pHost != NULL)
    {
        memcpy(&(pHost->pre_stat_update), &(pHost->cur_stat_update), sizeof(pHost->cur_stat_update));
        memcpy(&(pHost->cur_stat_update), &(pHost->cur_stat), sizeof(pHost->cur_stat));
        pHost = pHost->pNextLruHost;
    }
    ipstat_unlock();

    g_cur_update_timer_cycle = jiffies + g_interval_update_time * HZ;
    mod_timer(&g_update_timer, g_cur_update_timer_cycle);
}

void update_timer_init(void)
{
    init_timer(&g_update_timer);
    g_update_timer.data     = (unsigned long)0;
    g_update_timer.function = update_timer_proc;

    update_timer_proc(0);
}

void update_timer_exit(void)
{
    del_timer(&g_update_timer);
}
/**************************************************************************************************/
/*                                      PUBLIC_FUNCTIONS                                          */
/**************************************************************************************************/
int sfe_ipstat_init(void)
{
    g_ip_subnet.ip = 0xC0A80001;
    g_ip_subnet.mask = 0xFFFFFF00;

    creat_proc_file();
    ip_entry_init();
    arp_timer_init();
    update_timer_init();

    return 0;
}

int sfe_ipstat_exit(void)
{
    remove_proc_file();
    arp_timer_exit();
    update_timer_exit();

    return 0;
}

int sfe_ipstat_flush(void)
{
    ipstat_lock();
    ip_entry_init();
    ipstat_unlock();
    return 0;
}
/**************************************************************************************************/
/*                                      GLOBAL_FUNCTIONS                                          */
/**************************************************************************************************/
void sfe_ipstat_in(const struct sfe_ipv4_stat_info *sisi, const struct sk_buff *skb)
{
    const struct iphdr *iph = ip_hdr(skb);
    u_int32_t len = ntohs(iph->tot_len) + ETHER_PAYLOAD_LEN;
    void *host = NULL;

    if (1 != sfe_ipstat_switch) {
        return;
    }

    ipstat_debug();
    if (unlikely(0 == g_ip_subnet.ip && 0 == g_ip_subnet.mask)) {
        ipstat_debug("No ip subnet!!!\n");
        goto next;
    }

    ipstat_debug();
    if ((sisi->src_ip & g_ip_subnet.mask) == (g_ip_subnet.ip & g_ip_subnet.mask)) {
        ipstat_debug();
        ipstat_lock();

        if (unlikely((skb_mac_header(skb) < skb->head) || ((skb_mac_header(skb) + ETH_HLEN) > skb->data))) 
		{
            ipstat_unlock();
            ipstat_debug("tx mac is not valid\n");
            goto next;
        }


        host = find_ipentry(sisi->src_ip,eth_hdr(skb)->h_source);
        if (unlikely(NULL == host))
		{
            ipstat_unlock();
            ipstat_debug("host can't match and add.\n");
            goto next;
        }
		refresh_entry_mac(host, eth_hdr(skb)->h_source);
        ipstat_tx(host, sisi->protocol, len);
        ipstat_unlock();
    } 
	else if ((sisi->dst_ip & g_ip_subnet.mask) == (g_ip_subnet.ip & g_ip_subnet.mask)) 
	{
        ipstat_debug();
        ipstat_lock();

        ipstat_debug();
        host = find_ipentry(sisi->dst_ip, sisi->dst_mac);
        if (unlikely(NULL == host))
		{
            ipstat_unlock();
            ipstat_debug("host can't match and add.\n");
            goto next;
        }

        ipstat_debug();
        refresh_entry_mac(host, sisi->dst_mac);
        ipstat_rx(host, sisi->protocol, len);

        ipstat_unlock();
    }
	else 
	{
        ipstat_debug("package doesn't have lan_dev or src/dst_ip != lan_ip\n");
    }

next:
    return;
}

EXPORT_SYMBOL(sfe_ipstat_in);
EXPORT_SYMBOL(sfe_ipstat_flush);
EXPORT_SYMBOL(sfe_ipstat_switch);