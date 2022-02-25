/*
 * route cache
 */

#define pr_fmt(fmt) KBUILD_MODNAME": "fmt

#include <linux/types.h>
#include <linux/netfilter.h>
#include <linux/skbuff.h>
#include <linux/stddef.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/export.h>
#include <linux/module.h>
#include <linux/version.h>
#include <net/dst.h>
#include <net/route.h>
#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_core.h>
#include <net/netfilter/nf_conntrack_extend.h>
#include <net/netfilter/nf_conntrack_rtcache.h>

#if IS_ENABLED(CONFIG_NF_CONNTRACK_IPV6)
#include <net/ip6_fib.h>
#endif /* IS_ENABLED(CONFIG_NF_CONNTRACK_IPV6) */

unsigned int
seq_print_rtcache(struct seq_file *s, const struct nf_conn *ct, int dir)
{
#ifdef CONFIG_NF_CONNTRACK_RTCACHE
	struct nf_conn_rtcache *rtc = NULL;

	rtc = nf_ct_rtcache_find(ct);
	if (!rtc)
		return 0;

	return seq_printf(s, "dst_entry=%p iif=%d ", rtc->cached_dst[dir].dst, rtc->cached_dst[dir].iif);
#else
    return 0;
#endif
};
EXPORT_SYMBOL(seq_print_rtcache);

static void
__nf_conn_rtcache_destroy(struct nf_conn_rtcache *rtc, enum ip_conntrack_dir dir)
{
    struct dst_entry *dst = rtc->cached_dst[dir].dst;

    dst_release(dst);
}

static void
nf_conn_rtcache_destroy(struct nf_conn *ct)
{
    struct nf_conn_rtcache *rtc = nf_ct_rtcache_find(ct);

    if (!rtc)
        return;

    __nf_conn_rtcache_destroy(rtc, IP_CT_DIR_ORIGINAL);
    __nf_conn_rtcache_destroy(rtc, IP_CT_DIR_REPLY);
}

static void
nf_ct_rtcache_ext_add(struct nf_conn *ct)
{
    struct nf_conn_rtcache *rtc = NULL;

    rtc = nf_ct_ext_add(ct, NF_CT_EXT_RTCACHE, GFP_ATOMIC);
    if (rtc) {
        rtc->cached_dst[IP_CT_DIR_ORIGINAL].iif = -1;
        rtc->cached_dst[IP_CT_DIR_ORIGINAL].dst = NULL;
        rtc->cached_dst[IP_CT_DIR_REPLY].iif = -1;
        rtc->cached_dst[IP_CT_DIR_REPLY].dst = NULL;
    }
}

struct nf_conn_rtcache *
nf_ct_rtcache_find_usable(struct nf_conn *ct)
{
    if (nf_ct_is_untracked(ct))
        return NULL;
    return (struct nf_conn_rtcache *)nf_ct_rtcache_find(ct);
}
EXPORT_SYMBOL(nf_ct_rtcache_find_usable);

static struct dst_entry *
nf_conn_rtcache_dst_get(const struct nf_conn_rtcache *rtc, enum ip_conntrack_dir dir)
{
    return rtc->cached_dst[dir].dst;
}

static u32 nf_rtcache_get_cookie(int pf, const struct dst_entry *dst)
{
#if IS_ENABLED(CONFIG_NF_CONNTRACK_IPV6)
    if (NFPROTO_IPV6 == pf) {
        const struct rt6_info *rt = (const struct rt6_info *)dst;

        if (rt->rt6i_node)
            return (u32)rt->rt6i_node->fn_sernum;
    }
#endif /* IS_ENABLED(CONFIG_NF_CONNTRACK_IPV6) */
    return 0;
}

static void nf_conn_rtcache_dst_set(int pf,
                                    struct nf_conn_rtcache *rtc,
                                    struct dst_entry *dst,
                                    enum ip_conntrack_dir dir,
                                    int iif)
{
    if (rtc->cached_dst[dir].iif != iif)
        rtc->cached_dst[dir].iif = iif;

    if (rtc->cached_dst[dir].dst != dst) {
        struct dst_entry *old;

        dst_hold(dst);

        old = xchg(&rtc->cached_dst[dir].dst, dst);
        dst_release(old);

#if IS_ENABLED(CONFIG_NF_CONNTRACK_IPV6)
        if (NFPROTO_IPV6 == pf)
            rtc->cached_dst[dir].cookie = nf_rtcache_get_cookie(pf, dst);
#endif /* IS_ENABLED(CONFIG_NF_CONNTRACK_IPV6) */
    }
}

static void
nf_conn_rtcache_dst_obsolete(struct nf_conn_rtcache *rtc, enum ip_conntrack_dir dir)
{
    struct dst_entry *old;

    pr_debug("Invalidate iif %d for dir %d on cache %p\n",
             rtc->cached_dst[dir].iif, dir, rtc);

    old = xchg(&rtc->cached_dst[dir].dst, NULL);
    dst_release(old);
    rtc->cached_dst[dir].iif = -1;
}

static unsigned int
nf_ipv4_rtcache_in(unsigned hooknum,
                   struct sk_buff *skb,
                   const struct net_device *in,
                   const struct net_device *out,
                   int (*okfn)(struct sk_buff *))
{
    struct nf_conn_rtcache *rtc;
    enum ip_conntrack_info ctinfo;
    enum ip_conntrack_dir dir;
    struct dst_entry *dst;
    struct nf_conn *ct;
    int iif;
    u32 cookie;

    if (skb_dst(skb) || skb->sk)
        return NF_ACCEPT;

    ct = nf_ct_get(skb, &ctinfo);
    if (!ct)
        return NF_ACCEPT;

    rtc = nf_ct_rtcache_find_usable(ct);
    if (!rtc)
        return NF_ACCEPT;

    /* If iif changes, don't use cache and let ip stack do route lookup.
     *
     * If rp_filter is enabled it might toss skb, so we don't want to avoid
     * these checks.
     */
    dir = CTINFO2DIR(ctinfo);
    iif = nf_conn_rtcache_iif_get(rtc, dir);
    if (in->ifindex != iif) {
        pr_debug("ct %p, iif %d, cached iif %d, skip cached entry\n",
                 ct, iif, in->ifindex);
        return NF_ACCEPT;
    }

    dst = nf_conn_rtcache_dst_get(rtc, dir);
    if (NULL == dst)
        return NF_ACCEPT;

    cookie = nf_rtcache_get_cookie(NFPROTO_IPV4, dst);

    dst = dst_check(dst, cookie);
    pr_debug("obtained dst %p for skb %p, cookie %d\n", dst, skb, cookie);
    if (likely(dst))
        skb_dst_set_noref_force(skb, dst);
    else
        nf_conn_rtcache_dst_obsolete(rtc, dir);

    return NF_ACCEPT;
}

static unsigned int
nf_ipv6_rtcache_in(unsigned hooknum,
                   struct sk_buff *skb,
                   const struct net_device *in,
                   const struct net_device *out,
                   int (*okfn)(struct sk_buff *))
{
    struct nf_conn_rtcache *rtc;
    enum ip_conntrack_info ctinfo;
    enum ip_conntrack_dir dir;
    struct dst_entry *dst;
    struct nf_conn *ct;
    int iif;
    u32 cookie;

    if (skb_dst(skb) || skb->sk)
        return NF_ACCEPT;

    ct = nf_ct_get(skb, &ctinfo);
    if (!ct)
        return NF_ACCEPT;

    rtc = nf_ct_rtcache_find_usable(ct);
    if (!rtc)
        return NF_ACCEPT;

    /* If iif changes, don't use cache and let ip stack do route lookup.
     *
     * If rp_filter is enabled it might toss skb, so we don't want to avoid
     * these checks.
     */
    dir = CTINFO2DIR(ctinfo);
    iif = nf_conn_rtcache_iif_get(rtc, dir);
    if (in->ifindex != iif) {
        pr_debug("ct %p, iif %d, cached iif %d, skip cached entry\n",
                 ct, iif, in->ifindex);
        return NF_ACCEPT;
    }

    dst = nf_conn_rtcache_dst_get(rtc, dir);
    if (NULL == dst)
        return NF_ACCEPT;

    cookie = nf_rtcache_get_cookie(NFPROTO_IPV6, dst);

    dst = dst_check(dst, cookie);
    pr_debug("obtained dst %p for skb %p, cookie %d\n", dst, skb, cookie);
    if (likely(dst))
        skb_dst_set_noref_force(skb, dst);
    else
        nf_conn_rtcache_dst_obsolete(rtc, dir);

    return NF_ACCEPT;
}

static unsigned int
nf_ipv4_rtcache_forward(unsigned int hooknum,
                        struct sk_buff *skb,
                        const struct net_device *in,
                        const struct net_device *out,
                        int (*okfn)(struct sk_buff *))
{
    struct nf_conn_rtcache *rtc;
    enum ip_conntrack_info ctinfo;
    enum ip_conntrack_dir dir;
    enum ip_conntrack_dir redir;
    struct nf_conn *ct;
    struct dst_entry *dst = skb_dst(skb);
    int iif;
    int oif;

    ct = nf_ct_get(skb, &ctinfo);
    if (!ct)
        return NF_ACCEPT;

    if (dst && dst_xfrm(dst))
        return NF_ACCEPT;

    dir = CTINFO2DIR(ctinfo);
    redir = IP_CT_DIR_ORIGINAL == dir ? IP_CT_DIR_REPLY : IP_CT_DIR_ORIGINAL;

    if (!nf_ct_is_confirmed(ct)) {
        if (WARN_ON(nf_ct_rtcache_find(ct)))
            return NF_ACCEPT;

        nf_ct_rtcache_ext_add(ct);

        /* no need to confirm indev of ORIGINAL, directly save it */
        if (WARN_ON(IP_CT_DIR_ORIGINAL != dir))
            return NF_ACCEPT;

        rtc = nf_ct_rtcache_find_usable(ct);
        if (!rtc)
            return NF_ACCEPT;

        nf_conn_rtcache_dst_set(NFPROTO_IPV4, rtc, NULL, dir, in->ifindex);
        return NF_ACCEPT;
    }

    rtc = nf_ct_rtcache_find_usable(ct);
    if (!rtc)
        return NF_ACCEPT;

    iif = nf_conn_rtcache_iif_get(rtc, dir);
    oif = nf_conn_rtcache_iif_get(rtc, redir);
    pr_debug("ct %p, skb %p, dir %d, iif %d, cached iif %d\n",
             ct, skb, dir, iif, in->ifindex);
#if 0
    printk(KERN_ERR"\r\nct %p, skb %p : \r\n\t\t%s, iif %d(%s), cached iif %d; \r\n\t\t%s, oif %d(%s), cached oif %d\n",
             ct, skb, IP_CT_DIR_ORIGINAL == dir ? "ORIG" : "RPLY", in->ifindex, in->name, iif, IP_CT_DIR_ORIGINAL == redir ? "ORIG" : "RPLY", out ? out->ifindex : -1, out ? out->name : "null", oif);

    /* revise output if */
    if (IP_CT_DIR_REPLY == dir && out && out->ifindex != oif) {
        struct rtable *rt;
        struct iphdr *iph = ip_hdr(skb);

        rt = ip_route_output(dev_net(in), iph->daddr, 0, RT_TOS(iph->tos), oif);
        if (!IS_ERR(rt)) {
            skb_dst_set_noref_force(skb, &rt->dst);
        }
    }

    if (likely(in->ifindex == iif))
        return NF_ACCEPT;
#endif /* 0 */

    nf_conn_rtcache_dst_set(NFPROTO_IPV4, rtc, skb_dst(skb), dir, in->ifindex);
    return NF_ACCEPT;
}

static unsigned int
nf_ipv6_rtcache_forward(unsigned int hooknum,
                        struct sk_buff *skb,
                        const struct net_device *in,
                        const struct net_device *out,
                        int (*okfn)(struct sk_buff *))
{
    struct nf_conn_rtcache *rtc;
    enum ip_conntrack_info ctinfo;
    enum ip_conntrack_dir dir;
    struct nf_conn *ct;
    struct dst_entry *dst = skb_dst(skb);
    int iif;

    ct = nf_ct_get(skb, &ctinfo);
    if (!ct)
        return NF_ACCEPT;

    if (dst && dst_xfrm(dst))
        return NF_ACCEPT;

    if (!nf_ct_is_confirmed(ct)) {
        if (WARN_ON(nf_ct_rtcache_find(ct)))
            return NF_ACCEPT;

        nf_ct_rtcache_ext_add(ct);
        return NF_ACCEPT;
    }

    rtc = nf_ct_rtcache_find_usable(ct);
    if (!rtc)
        return NF_ACCEPT;

    dir = CTINFO2DIR(ctinfo);
    iif = nf_conn_rtcache_iif_get(rtc, dir);
    pr_debug("ct %p, skb %p, dir %d, iif %d, cached iif %d\n",
             ct, skb, dir, iif, in->ifindex);

    if (likely(in->ifindex == iif))
        return NF_ACCEPT;

    nf_conn_rtcache_dst_set(NFPROTO_IPV6, rtc, skb_dst(skb), dir, in->ifindex);
    return NF_ACCEPT;
}

static int
nf_rtcache_dst_remove(struct nf_conn *ct, void *data)
{
    struct nf_conn_rtcache *rtc = nf_ct_rtcache_find(ct);
    struct net_device *dev = data;

    if (!rtc)
        return 0;

    if (dev->ifindex == rtc->cached_dst[IP_CT_DIR_ORIGINAL].iif ||
        dev->ifindex == rtc->cached_dst[IP_CT_DIR_REPLY].iif) {
        nf_conn_rtcache_dst_obsolete(rtc, IP_CT_DIR_ORIGINAL);
        nf_conn_rtcache_dst_obsolete(rtc, IP_CT_DIR_REPLY);
    }

    return 0;
}

static int
nf_rtcache_netdev_event(struct notifier_block *this,
                        unsigned long event, void *ptr)
{
    struct net_device *dev = ptr;
    struct net *net = dev_net(dev);

    if (NETDEV_DOWN == event)
        nf_ct_iterate_cleanup(net, nf_rtcache_dst_remove, dev);

    return NOTIFY_DONE;
}

static struct notifier_block nf_rtcache_notifier = {
    .notifier_call = nf_rtcache_netdev_event,
};

static struct nf_hook_ops rtcache_ops[] = {
    {
        .hook       = nf_ipv4_rtcache_in,
        .owner      = THIS_MODULE,
        .pf         = NFPROTO_IPV4,
        .hooknum    = NF_INET_PRE_ROUTING,
        .priority   = NF_IP_PRI_LAST,
    },
    {
        .hook       = nf_ipv4_rtcache_forward,
        .owner      = THIS_MODULE,
        .pf         = NFPROTO_IPV4,
        .hooknum    = NF_INET_FORWARD,
        .priority   = NF_IP_PRI_LAST,
    },
#if IS_ENABLED(CONFIG_NF_CONNTRACK_IPV6)
    {
        .hook       = nf_ipv6_rtcache_in,
        .owner      = THIS_MODULE,
        .pf         = NFPROTO_IPV6,
        .hooknum    = NF_INET_PRE_ROUTING,
        .priority   = NF_IP_PRI_LAST,
    },
    {
        .hook       = nf_ipv6_rtcache_forward,
        .owner      = THIS_MODULE,
        .pf         = NFPROTO_IPV6,
        .hooknum    = NF_INET_FORWARD,
        .priority   = NF_IP_PRI_LAST,
    },
#endif /* IS_ENABLED(CONFIG_NF_CONNTRACK_IPV6) */
};

static struct nf_ct_ext_type rtcache_ext __read_mostly = {
    .len        = sizeof(struct nf_conn_rtcache),
    .align      = __alignof__(struct nf_conn_rtcache),
    .id         = NF_CT_EXT_RTCACHE,
    .destroy    = nf_conn_rtcache_destroy,
};

static int __init
nf_conntrack_rtcache_init(void)
{
    int ret = nf_ct_extend_register(&rtcache_ext);

    if (ret < 0) {
        pr_err("nf_conntrack_rtcache: unable to register extension\n");
        return ret;
    }

    ret = nf_register_hooks(rtcache_ops, ARRAY_SIZE(rtcache_ops));
    if (ret < 0) {
        nf_ct_extend_unregister(&rtcache_ext);
        return ret;
    }

    ret = register_netdevice_notifier(&nf_rtcache_notifier);
    if (ret) {
        nf_unregister_hooks(rtcache_ops, ARRAY_SIZE(rtcache_ops));
        nf_ct_extend_unregister(&rtcache_ext);
        return ret;
    }

    return ret;
}

static int
nf_rtcache_ext_remove(struct nf_conn *ct, void *data)
{
    struct nf_conn_rtcache *rtc = nf_ct_rtcache_find(ct);

    return rtc != NULL;
}

static bool __exit
nf_conntrack_rtcache_wait_for_dying(struct net *net)
{
    bool wait = false;

	struct nf_conntrack_tuple_hash *h;
	struct nf_conn *ct;
	struct hlist_nulls_node *n;

	spin_lock_bh(&nf_conntrack_lock);
	hlist_nulls_for_each_entry(h, n, &net->ct.dying, hnnode) {
		ct = nf_ct_tuplehash_to_ctrack(h);
        if (nf_ct_rtcache_find(ct) != NULL) {
            wait = true;
            break;
        }
	}
	spin_unlock_bh(&nf_conntrack_lock);

    return wait;
}

static void __exit
nf_conntrack_rtcache_fini(void)
{
    struct net *net;
    int count = 0;

    /* remove hooks so no new connections get rtcache extension */
    nf_unregister_hooks(rtcache_ops, ARRAY_SIZE(rtcache_ops));

    synchronize_net();

    unregister_netdevice_notifier(&nf_rtcache_notifier);

    rtnl_lock();

    /* zap all conntracks with rtcache extension */
    for_each_net(net) {
        nf_ct_iterate_cleanup(net, nf_rtcache_ext_remove, NULL);
    }

    for_each_net(net) {
        /* .. and make sure they're gone from dying list, too */
        while (nf_conntrack_rtcache_wait_for_dying(net)) {
            msleep(200);
            WARN_ONCE(++count > 25, "Waiting for all rtcache conntracks to go away\n");
        }
    }

    rtnl_unlock();
    synchronize_net();
    nf_ct_extend_unregister(&rtcache_ext);
}

module_init(nf_conntrack_rtcache_init);
module_exit(nf_conntrack_rtcache_fini);

