#ifndef _XTABLES_COMPAT_H
#define _XTABLES_COMPAT_H 1

#include <linux/kernel.h>
#include <linux/version.h>
#include "compat_skbuff.h"
#include "compat_xtnu.h"

#define DEBUGP Use__pr_debug__instead

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 7, 0)
#	warning Kernels below 3.7 not supported.
#endif

#if defined(CONFIG_NF_CONNTRACK) || defined(CONFIG_NF_CONNTRACK_MODULE)
#	if !defined(CONFIG_NF_CONNTRACK_MARK)
#		warning You have CONFIG_NF_CONNTRACK enabled, but CONFIG_NF_CONNTRACK_MARK is not (please enable).
#	endif
#	include <net/netfilter/nf_conntrack.h>
#else
#	warning You need CONFIG_NF_CONNTRACK.
#endif

#define ipt_unregister_table(tbl) ipt_unregister_table(&init_net, (tbl))
#define ip6t_unregister_table(tbl) ip6t_unregister_table(&init_net, (tbl))

#if !defined(NIP6) && !defined(NIP6_FMT)
#	define NIP6(addr) \
		ntohs((addr).s6_addr16[0]), \
		ntohs((addr).s6_addr16[1]), \
		ntohs((addr).s6_addr16[2]), \
		ntohs((addr).s6_addr16[3]), \
		ntohs((addr).s6_addr16[4]), \
		ntohs((addr).s6_addr16[5]), \
		ntohs((addr).s6_addr16[6]), \
		ntohs((addr).s6_addr16[7])
#	define NIP6_FMT "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x"
#endif
#if !defined(NIPQUAD) && !defined(NIPQUAD_FMT)
#	define NIPQUAD(addr) \
		((const unsigned char *)&addr)[0], \
		((const unsigned char *)&addr)[1], \
		((const unsigned char *)&addr)[2], \
		((const unsigned char *)&addr)[3]
#	define NIPQUAD_FMT "%u.%u.%u.%u"
#endif

#define ip_route_me_harder    xtnu_ip_route_me_harder
#define skb_make_writable     xtnu_skb_make_writable
#define xt_target             xtnu_target
#define xt_register_target    xtnu_register_target
#define xt_unregister_target  xtnu_unregister_target
#define xt_register_targets   xtnu_register_targets
#define xt_unregister_targets xtnu_unregister_targets

#define xt_request_find_match xtnu_request_find_match

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 9, 0)
static inline struct inode *file_inode(struct file *f)
{
	return f->f_path.dentry->d_inode;
}
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0)
static inline void
proc_set_user(struct proc_dir_entry *de, kuid_t uid, kgid_t gid)
{
	de->uid = uid;
	de->gid = gid;
}

static inline void *PDE_DATA(struct inode *inode)
{
	return PDE(inode)->data;
}

static inline void proc_remove(struct proc_dir_entry *de)
{
	if (de != NULL)
		remove_proc_entry(de->name, de->parent);
}
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 9, 0)
static inline void proc_net_remove(struct net *net, const char *name)
{
       remove_proc_entry(name, net->proc_net);
}
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 14, 0)
static inline u32 net_random(void)
{
	return prandom_u32();
}
#endif

#endif /* _XTABLES_COMPAT_H */
