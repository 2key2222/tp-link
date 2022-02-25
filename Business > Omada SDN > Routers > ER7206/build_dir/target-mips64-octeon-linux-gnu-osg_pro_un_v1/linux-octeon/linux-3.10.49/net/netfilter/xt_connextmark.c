/*
 *	xt_connextmark - Netfilter module to operate on connection marks
 *
 *	Copyright (C) 2002,2004 MARA Systems AB <http://www.marasystems.com>
 *	by Henrik Nordstrom <hno@marasystems.com>
 *	Copyright © CC Computer Consultants GmbH, 2007 - 2008
 *	Jan Engelhardt <jengelh@medozas.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/module.h>
#include <linux/skbuff.h>
#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_ecache.h>
#include <linux/netfilter/x_tables.h>
#include <linux/netfilter/xt_connextmark.h>

MODULE_AUTHOR("Henrik Nordstrom <hno@marasystems.com>");
MODULE_DESCRIPTION("Xtables: connection extmark operations");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_CONNEXTMARK");
MODULE_ALIAS("ip6t_CONNEXTMARK");
MODULE_ALIAS("ipt_connextmark");
MODULE_ALIAS("ip6t_connextmark");

static unsigned int
connextmark_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_connextmark_tginfo1 *info = par->targinfo;
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct;
	u_int32_t newmark;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct == NULL)
		return XT_CONTINUE;

	switch (info->mode) {
	case XT_CONNEXTMARK_SET:
		newmark = (ct->extmark & ~info->ctmask) ^ info->ctmark;
		if (ct->extmark != newmark) {
			ct->extmark = newmark;
			nf_conntrack_event_cache(IPCT_MARK, ct);
		}
		break;
	case XT_CONNEXTMARK_SAVE:
		newmark = (ct->extmark & ~info->ctmask) ^
		          (skb->extmark & info->nfmask);
		if (ct->extmark != newmark) {
			ct->extmark = newmark;
			nf_conntrack_event_cache(IPCT_MARK, ct);
		}
		break;
	case XT_CONNEXTMARK_RESTORE:
		newmark = (skb->extmark & ~info->nfmask) ^
		          (ct->extmark & info->ctmask);
		skb->extmark = newmark;
		break;
	}

	return XT_CONTINUE;
}

static int connextmark_tg_check(const struct xt_tgchk_param *par)
{
	int ret;

	ret = nf_ct_l3proto_try_module_get(par->family);
	if (ret < 0)
		pr_info("cannot load conntrack support for proto=%u\n",
			par->family);
	return ret;
}

static void connextmark_tg_destroy(const struct xt_tgdtor_param *par)
{
	nf_ct_l3proto_module_put(par->family);
}

static bool
connextmark_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_connextmark_mtinfo1 *info = par->matchinfo;
	enum ip_conntrack_info ctinfo;
	const struct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct == NULL)
		return false;

	return ((ct->extmark & info->mask) == info->mark) ^ info->invert;
}

static int connextmark_mt_check(const struct xt_mtchk_param *par)
{
	int ret;

	ret = nf_ct_l3proto_try_module_get(par->family);
	if (ret < 0)
		pr_info("cannot load conntrack support for proto=%u\n",
			par->family);
	return ret;
}

static void connextmark_mt_destroy(const struct xt_mtdtor_param *par)
{
	nf_ct_l3proto_module_put(par->family);
}

static struct xt_target connextmark_tg_reg __read_mostly = {
	.name           = "CONNEXTMARK",
	.revision       = 1,
	.family         = NFPROTO_UNSPEC,
	.checkentry     = connextmark_tg_check,
	.target         = connextmark_tg,
	.targetsize     = sizeof(struct xt_connextmark_tginfo1),
	.destroy        = connextmark_tg_destroy,
	.me             = THIS_MODULE,
};

static struct xt_match connextmark_mt_reg __read_mostly = {
	.name           = "connextmark",
	.revision       = 1,
	.family         = NFPROTO_UNSPEC,
	.checkentry     = connextmark_mt_check,
	.match          = connextmark_mt,
	.matchsize      = sizeof(struct xt_connextmark_mtinfo1),
	.destroy        = connextmark_mt_destroy,
	.me             = THIS_MODULE,
};

static int __init connextmark_mt_init(void)
{
	int ret;

	printk(" ## netfilter xt_connextmark loaded.\n ");

	ret = xt_register_target(&connextmark_tg_reg);
	if (ret < 0)
		return ret;
	ret = xt_register_match(&connextmark_mt_reg);
	if (ret < 0) {
		xt_unregister_target(&connextmark_tg_reg);
		return ret;
	}
	return 0;
}

static void __exit connextmark_mt_exit(void)
{
	xt_unregister_match(&connextmark_mt_reg);
	xt_unregister_target(&connextmark_tg_reg);
}

module_init(connextmark_mt_init);
module_exit(connextmark_mt_exit);
