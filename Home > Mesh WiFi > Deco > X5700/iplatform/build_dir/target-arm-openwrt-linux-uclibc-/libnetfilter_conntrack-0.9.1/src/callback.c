/*
 * (C) 2006-2010 by Pablo Neira Ayuso <pablo@netfilter.org>
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 */

#include "internal/internal.h"

static int __parse_message(const struct nlmsghdr *nlh)
{
	u_int16_t type = NFNL_MSG_TYPE(nlh->nlmsg_type);
	u_int16_t flags = nlh->nlmsg_flags;
	int ret = NFCT_T_UNKNOWN;

	switch(type) {
	case IPCTNL_MSG_CT_NEW: /* same value for IPCTNL_MSG_EXP_NEW. */
		if (flags & (NLM_F_CREATE|NLM_F_EXCL))
			ret = NFCT_T_NEW;
		else
			ret = NFCT_T_UPDATE;
		break;
	case IPCTNL_MSG_CT_DELETE: /* same value for IPCTNL_MSG_EXP_DELETE. */
		ret = NFCT_T_DESTROY;
		break;
	}
	return ret;
}

int __callback(struct nlmsghdr *nlh, struct nfattr *nfa[], void *data)
{
	int ret = NFNL_CB_STOP;
	unsigned int type;
	struct nf_conntrack *ct = NULL;
	struct nf_expect *exp = NULL;
	struct __data_container *container = data;
	u_int8_t subsys = NFNL_SUBSYS_ID(nlh->nlmsg_type);

	if (nlh->nlmsg_len < NLMSG_LENGTH(sizeof(struct nfgenmsg))) {
		errno = EINVAL;
		return NFNL_CB_FAILURE;
	}
	type = __parse_message(nlh);
	if (!(type & container->type))
		return NFNL_CB_CONTINUE;

	switch(subsys) {
	case NFNL_SUBSYS_CTNETLINK:
		ct = nfct_new();
		if (ct == NULL)
			return NFNL_CB_FAILURE;

		__parse_conntrack(nlh, nfa, ct);

		if (container->h->cb) {
			ret = container->h->cb(type, ct, container->data);
		} else if (container->h->cb2) {
			ret = container->h->cb2(nlh, type, ct,
						container->data);
		}
		break;
	case NFNL_SUBSYS_CTNETLINK_EXP:
		exp = nfexp_new();
		if (exp == NULL)
			return NFNL_CB_FAILURE;

		__parse_expect(nlh, nfa, exp);

		if (container->h->expect_cb) {
			ret = container->h->expect_cb(type, exp,
						      container->data);
		} else if (container->h->expect_cb2) {
			ret = container->h->expect_cb2(nlh, type, exp,
						       container->data);
		}
		break;
	default:
		errno = ENOTSUP;
		ret = NFNL_CB_FAILURE;
		break;
	}

	switch(ret) {
	case NFCT_CB_FAILURE:
		if (ct)
			free(ct);
		if (exp)
			free(exp);
		ret = NFNL_CB_FAILURE;
		break;
	case NFCT_CB_STOP:
		if (ct)
			free(ct);
		if (exp)
			free(exp);
		ret = NFNL_CB_STOP;
		break;
	case NFCT_CB_CONTINUE:
		if (ct)
			free(ct);
		if (exp)
			free(exp);
		ret = NFNL_CB_CONTINUE;
		break;
	case NFCT_CB_STOLEN:
		ret = NFNL_CB_CONTINUE;
		break;
	}
	return ret;
}
