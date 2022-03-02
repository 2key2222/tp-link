/*
 * (C) 2012 by Pablo Neira Ayuso <pablo@netfilter.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This code has been sponsored by Vyatta Inc. <http://www.vyatta.com>
 */
#include "internal.h"

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>	/* for htonl */

#include <libmnl/libmnl.h>
#include <linux/netfilter/nfnetlink.h>
#include <linux/netfilter/nfnetlink_cthelper.h>

#include <libnetfilter_cthelper/libnetfilter_cthelper.h>

/**
 * \mainpage
 *
 * libnetfilter_cthelper is the userspace library that provides a programming
 * interface (API) to user-space connection tracking helpers. Basically, you
 * can find here a set of helper functions that you can use together with
 * libmnl.
 *
 * libnetfilter_cthelper homepage is:
 *      http://netfilter.org/projects/libnetfilter_cthelper/
 *
 * \section Dependencies
 * libnetfilter_cthelper requires libmnl >= 1.0.0 and the Linux kernel that
 * includes the nfnetlink_cthelper subsystem (i.e. 3.3.x or any later).
 *
 * \section Main Features
 *  - register new user-space connection tracking helpers.
 *  - unregister user-space connection tracking helpers.
 *  - list existing registered user-space connection tracking helpers.
 *
 * \section Git Tree
 * The current development version of libnetfilter_cthelper can be accessed at
 * https://git.netfilter.org/cgi-bin/gitweb.cgi?p=libnetfilter_cthelper.git
 *
 * \section using Using libnetfilter_cthelper
 * To write your own program using libnetfilter_cthelper, you should start by
 * reading the documentation for libmnl to understand basic operation with
 * Netlink sockets. Moreover, you may want to check the examples available
 * under examples/ in the libnetfilter_cthelper source code. You can compile
 * these examples by invoking `make check'.
 *
 * \section Authors
 * libnetfilter_cthelper has been written by Pablo Neira Ayuso.
 */

/* XXX */
#ifndef NF_CT_HELPER_NAME_MAX
#define NF_CT_HELPER_NAME_MAX 16
#endif

#ifndef NF_CT_HELPER_CLASS_MAX
#define NF_CT_HELPER_CLASS_MAX 4
#endif

struct nfct_helper_policy {
	char		name[NF_CT_HELPER_NAME_MAX];
	uint32_t	expect_timeout;
	uint32_t	expect_max;
	uint32_t	bitset;
};

struct nfct_helper {
	char		name[NF_CT_HELPER_NAME_MAX];
	uint32_t	priv_data_len;
	uint32_t	queue_num;
	uint32_t	status;
	struct {
			uint16_t	l3num;
			uint8_t		l4num;
			uint16_t	port;
	} tuple;
	struct nfct_helper_policy *expect_policy[NF_CT_HELPER_CLASS_MAX];
	uint32_t	policy_num;

	uint32_t	bitset;
};

/**
 * \defgroup nfct_helper Accounting object handling
 * @{
 */

/**
 * nfct_helper_alloc - allocate a new helper object
 *
 * In case of success, this function returns a valid pointer, otherwise NULL
 * s returned and errno is appropriately set.
 */
struct nfct_helper *nfct_helper_alloc(void)
{
	return calloc(1, sizeof(struct nfct_helper));
}
EXPORT_SYMBOL(nfct_helper_alloc);

/**
 * nfct_helper_free - release one helper object
 * \param nfct_helper pointer to the helper object
 */
void nfct_helper_free(struct nfct_helper *h)
{
	int i;

	free(h);
	for (i=0; i<NF_CT_HELPER_CLASS_MAX; i++) {
		if (h->expect_policy[i])
			free(h->expect_policy[i]);
	}
}
EXPORT_SYMBOL(nfct_helper_free);

/**
 * nfct_helper_policy_alloc - allocate a new helper policy object
 *
 * In case of success, this function returns a valid pointer, otherwise NULL
 * s returned and errno is appropriately set.
 */
struct nfct_helper_policy *nfct_helper_policy_alloc(void)
{
	return calloc(1, sizeof(struct nfct_helper_policy));
}
EXPORT_SYMBOL(nfct_helper_policy_alloc);

/**
 * nfct_helper_free - release one helper policy object
 * \param nfct_helper pointer to the helper object
 */
void nfct_helper_policy_free(struct nfct_helper_policy *p)
{
	free(p);
}
EXPORT_SYMBOL(nfct_helper_policy_free);

/**
 * nfct_helper_policy_attr_set - set one attribute of the helper object
 * \param nfct_helper pointer to the helper object
 * \param type attribute type you want to set
 * \param data pointer to data that will be used to set this attribute
 */
void
nfct_helper_policy_attr_set(struct nfct_helper_policy *p,
			    enum nfct_helper_policy_attr_type type,
			    const void *data)
{
	switch(type) {
	case NFCTH_ATTR_POLICY_NAME:
		strncpy(p->name, data, NF_CT_HELPER_NAME_MAX);
		p->name[NF_CT_HELPER_NAME_MAX-1] = '\0';
		p->bitset |= (1 << NFCTH_ATTR_POLICY_NAME);
		break;
	case NFCTH_ATTR_POLICY_TIMEOUT:
		p->expect_timeout = *((uint32_t *) data);
		p->bitset |= (1 << NFCTH_ATTR_POLICY_TIMEOUT);
		break;
	case NFCTH_ATTR_POLICY_MAX:
		p->expect_max = *((uint32_t *) data);
		p->bitset |= (1 << NFCTH_ATTR_POLICY_MAX);
		break;
	}
}
EXPORT_SYMBOL(nfct_helper_policy_attr_set);

/**
 * nfct_helper_attr_set_str - set one attribute the helper object
 * \param nfct_helper pointer to the helper object
 * \param type attribute type you want to set
 * \param name string that will be used to set this attribute
 */
void
nfct_helper_policy_attr_set_str(struct nfct_helper_policy *p,
				enum nfct_helper_policy_attr_type type,
				const char *name)
{
	nfct_helper_policy_attr_set(p, type, name);
}
EXPORT_SYMBOL(nfct_helper_policy_attr_set_str);

void
nfct_helper_policy_attr_set_u32(struct nfct_helper_policy *p,
				enum nfct_helper_policy_attr_type type,
				uint32_t value)
{
	nfct_helper_policy_attr_set(p, type, &value);
}
EXPORT_SYMBOL(nfct_helper_policy_attr_set_u32);

/**
 * nfct_helper_attr_set - set one attribute of the helper object
 * \param nfct_helper pointer to the helper object
 * \param type attribute type you want to set
 * \param data pointer to data that will be used to set this attribute
 */
void
nfct_helper_attr_set(struct nfct_helper *h,
		     enum nfct_helper_attr_type type, const void *data)
{
	switch(type) {
	case NFCTH_ATTR_NAME:
		strncpy(h->name, data, NF_CT_HELPER_NAME_MAX);
		h->name[NF_CT_HELPER_NAME_MAX-1] = '\0';
		h->bitset |= (1 << NFCTH_ATTR_NAME);
		break;
	case NFCTH_ATTR_QUEUE_NUM:
		h->queue_num = *((uint32_t *) data);
		h->bitset |= (1 << NFCTH_ATTR_QUEUE_NUM);
		break;
	case NFCTH_ATTR_PROTO_L3NUM:
		h->tuple.l3num = *((uint16_t *) data);
		h->bitset |= (1 << NFCTH_ATTR_PROTO_L3NUM);
		break;
	case NFCTH_ATTR_PROTO_L4NUM:
		h->tuple.l4num = *((uint8_t *) data);
		h->bitset |= (1 << NFCTH_ATTR_PROTO_L4NUM);
		break;
	case NFCTH_ATTR_PRIV_DATA_LEN:
		h->priv_data_len = *((uint32_t *) data);
		h->bitset |= (1 << NFCTH_ATTR_PRIV_DATA_LEN);
		break;
	case NFCTH_ATTR_POLICY1:
		h->expect_policy[0] = (struct nfct_helper_policy *)data;
		h->bitset |= (1 << NFCTH_ATTR_POLICY1);
		break;
	case NFCTH_ATTR_POLICY2:
		h->expect_policy[1] = (struct nfct_helper_policy *)data;
		h->bitset |= (1 << NFCTH_ATTR_POLICY2);
		break;
	case NFCTH_ATTR_POLICY3:
		h->expect_policy[2] = (struct nfct_helper_policy *)data;
		h->bitset |= (1 << NFCTH_ATTR_POLICY3);
		break;
	case NFCTH_ATTR_POLICY4:
		h->expect_policy[3] = (struct nfct_helper_policy *)data;
		h->bitset |= (1 << NFCTH_ATTR_POLICY4);
		break;
	case NFCTH_ATTR_STATUS:
		h->status = *((uint32_t *) data);
		h->bitset |= (1 << NFCTH_ATTR_STATUS);
		break;
	}
}
EXPORT_SYMBOL(nfct_helper_attr_set);

/**
 * nfct_helper_attr_set_str - set one attribute the helper object
 * \param nfct_helper pointer to the helper object
 * \param type attribute type you want to set
 * \param name string that will be used to set this attribute
 */
void
nfct_helper_attr_set_str(struct nfct_helper *nfct_helper, enum nfct_helper_attr_type type,
		    const char *name)
{
	nfct_helper_attr_set(nfct_helper, type, name);
}
EXPORT_SYMBOL(nfct_helper_attr_set_str);

void
nfct_helper_attr_set_u8(struct nfct_helper *nfct_helper,
			 enum nfct_helper_attr_type type, uint8_t value)
{
	nfct_helper_attr_set(nfct_helper, type, &value);
}
EXPORT_SYMBOL(nfct_helper_attr_set_u8);

void
nfct_helper_attr_set_u16(struct nfct_helper *nfct_helper,
			 enum nfct_helper_attr_type type, uint16_t value)
{
	nfct_helper_attr_set(nfct_helper, type, &value);
}
EXPORT_SYMBOL(nfct_helper_attr_set_u16);

void
nfct_helper_attr_set_u32(struct nfct_helper *nfct_helper,
			 enum nfct_helper_attr_type type, uint32_t value)
{
	nfct_helper_attr_set(nfct_helper, type, &value);
}
EXPORT_SYMBOL(nfct_helper_attr_set_u32);

/**
 * nfct_helper_attr_unset - unset one attribute the helper object
 * \param nfct_helper pointer to the helper object
 * \param type attribute type you want to set
 */
void
nfct_helper_attr_unset(struct nfct_helper *nfct_helper, enum nfct_helper_attr_type type)
{
	switch(type) {
	case NFCTH_ATTR_NAME:
		nfct_helper->bitset &= ~(1 << NFCTH_ATTR_NAME);
		break;
	default:
		/* XXX */
		break;
	}
}
EXPORT_SYMBOL(nfct_helper_attr_unset);

/**
 * nfct_helper_attr_get - get one attribute the helper object
 * \param nfct_helper pointer to the helper object
 * \param type attribute type you want to set
 *
 * This function returns a valid pointer to the attribute data. If a
 * unsupported attribute is used, this returns NULL.
 */
const void *nfct_helper_attr_get(struct nfct_helper *helper,
				 enum nfct_helper_attr_type type)
{
	const void *ret = NULL;

	switch(type) {
	case NFCTH_ATTR_NAME:
		ret = helper->name;
		break;
	case NFCTH_ATTR_QUEUE_NUM:
		ret = &helper->queue_num;
		break;
	case NFCTH_ATTR_PROTO_L3NUM:
		ret = &helper->tuple.l3num;
		break;
	case NFCTH_ATTR_PROTO_L4NUM:
		ret = &helper->tuple.l4num;
		break;
	case NFCTH_ATTR_PRIV_DATA_LEN:
		ret = &helper->priv_data_len;
		break;
	case NFCTH_ATTR_POLICY1:
		ret = helper->expect_policy[0];
		break;
	case NFCTH_ATTR_POLICY2:
		ret = helper->expect_policy[1];
		break;
	case NFCTH_ATTR_POLICY3:
		ret = helper->expect_policy[2];
		break;
	case NFCTH_ATTR_POLICY4:
		ret = helper->expect_policy[3];
		break;
	case NFCTH_ATTR_STATUS:
		ret = &helper->status;
		break;
	default:
		ret = NULL;
	}
	return ret;
}
EXPORT_SYMBOL(nfct_helper_attr_get);

/**
 * nfct_helper_attr_get_str - get one attribute the helper object
 * \param nfct_helper pointer to the helper object
 * \param type attribute type you want to set
 *
 * This function returns a valid pointer to the beginning of the string.
 * If the attribute is unsupported, this returns NULL.
 */
const char *
nfct_helper_attr_get_str(struct nfct_helper *nfct_helper,
			 enum nfct_helper_attr_type type)
{
	return (const char *)nfct_helper_attr_get(nfct_helper, type);
}
EXPORT_SYMBOL(nfct_helper_attr_get_str);

/**
 * nfct_helper_attr_get_u8 - get one attribute the helper object
 * \param nfct_helper pointer to the helper object
 * \param type attribute type you want to set
 *
 * This function returns a unsigned 8-bits integer. If the attribute is
 * unsupported, this returns NULL.
 */
uint8_t nfct_helper_attr_get_u8(struct nfct_helper *nfct_helper,
				  enum nfct_helper_attr_type type)
{
	return *((uint8_t *)nfct_helper_attr_get(nfct_helper, type));
}
EXPORT_SYMBOL(nfct_helper_attr_get_u8);

/**
 * nfct_helper_attr_get_u16 - get one attribute the helper object
 * \param nfct_helper pointer to the helper object
 * \param type attribute type you want to set
 *
 * This function returns a unsigned 16-bits integer. If the attribute is
 * unsupported, this returns NULL.
 */
uint16_t nfct_helper_attr_get_u16(struct nfct_helper *nfct_helper,
				  enum nfct_helper_attr_type type)
{
	return *((uint16_t *)nfct_helper_attr_get(nfct_helper, type));
}
EXPORT_SYMBOL(nfct_helper_attr_get_u16);

/**
 * nfct_helper_attr_get_u32 - get one attribute the helper object
 * \param nfct_helper pointer to the helper object
 * \param type attribute type you want to set
 *
 * This function returns a unsigned 32-bits integer. If the attribute is
 * unsupported, this returns NULL.
 */
uint32_t nfct_helper_attr_get_u32(struct nfct_helper *nfct_helper,
				  enum nfct_helper_attr_type type)
{
	return *((uint32_t *)nfct_helper_attr_get(nfct_helper, type));
}
EXPORT_SYMBOL(nfct_helper_attr_get_u32);

/**
 * nfct_helper_snprintf - print helper object into one buffer
 * \param buf: pointer to buffer that is used to print the object
 * \param size: size of the buffer (or remaining room in it).
 * \param nfct_helper: pointer to a valid helper object.
 * \param flags: output flags (NFCTH_SNPRINTF_F_FULL).
 *
 * This function returns -1 in case that some mandatory attributes are
 * missing. On sucess, it returns 0.
 */
int nfct_helper_snprintf(char *buf, size_t size,
			 struct nfct_helper *helper,
			 unsigned int type, unsigned int flags)
{
	int ret;

	ret = snprintf(buf, size, "{\n"
				  "\t.name = %s,\n"
				  "\t.queuenum = %u,\n"
				  "\t.l3protonum = %u,\n"
				  "\t.l4protonum = %u,\n"
				  "\t.priv_data_len = %u,\n"
				  "\t.status = %s,\n};",
		nfct_helper_attr_get_str(helper, NFCTH_ATTR_NAME),
		nfct_helper_attr_get_u32(helper, NFCTH_ATTR_QUEUE_NUM),
		nfct_helper_attr_get_u16(helper, NFCTH_ATTR_PROTO_L3NUM),
		nfct_helper_attr_get_u8(helper, NFCTH_ATTR_PROTO_L4NUM),
		nfct_helper_attr_get_u32(helper, NFCTH_ATTR_PRIV_DATA_LEN),
		nfct_helper_attr_get_u32(helper, NFCTH_ATTR_STATUS) ?
			"enabled" : "disabled");

	return ret;
}
EXPORT_SYMBOL(nfct_helper_snprintf);

/**
 * @}
 */

/**
 * \defgroup nlmsg Netlink message helper functions
 * @{
 */

/**
 * nfct_helper_nlmsg_build_hdr - build netlink message header for nfct_helper subsystem
 * \param buf: buffer where this function outputs the netlink message.
 * \param cmd: nfct_helper nfnetlink command.
 * \param flags: netlink flags.
 * \param seq: sequence number for this message.
 *
 * Possible commands:
 * - NFNL_MSG_ACCT_NEW: new helper object.
 * - NFNL_MSG_ACCT_GET: get helper object.
 * - NFNL_MSG_ACCT_GET_CTRZERO: get helper object and atomically reset.
 *
 * Examples:
 * - Command NFNL_MSG_ACCT_NEW + flags NLM_F_CREATE | NLM_F_ACK, to create
 *   one new helper object (if it does not already exists). You receive
 *   one acknoledgment in any case with the result of the operation.
 *
 * - Command NFNL_MSG_ACCT_GET + flags NLM_F_DUMP, to obtain all the
 *   existing helper objects.
 *
 * - Command NFNL_MSG_ACCT_DEL, to delete all existing unused objects.
 *
 * - Command NFNL_MSG_ACCT_DEL, to delete one specific nfct_helper object (if
 *   unused, otherwise you hit EBUSY).
 */
struct nlmsghdr *
nfct_helper_nlmsg_build_hdr(char *buf, uint8_t cmd,
			    uint16_t flags, uint32_t seq)
{
	struct nlmsghdr *nlh;
	struct nfgenmsg *nfh;

	nlh = mnl_nlmsg_put_header(buf);
	nlh->nlmsg_type = (NFNL_SUBSYS_CTHELPER << 8) | cmd;
	nlh->nlmsg_flags = NLM_F_REQUEST | flags;
	nlh->nlmsg_seq = seq;

	nfh = mnl_nlmsg_put_extra_header(nlh, sizeof(struct nfgenmsg));
	nfh->nfgen_family = AF_UNSPEC;
	nfh->version = NFNETLINK_V0;
	nfh->res_id = 0;

	return nlh;
}
EXPORT_SYMBOL(nfct_helper_nlmsg_build_hdr);

static void
nfct_helper_nlmsg_build_policy(struct nlmsghdr *nlh,
				struct nfct_helper_policy *p)
{
	struct nlattr *nest;

	nest = mnl_attr_nest_start(nlh, NFCTH_POLICY_SET);
	mnl_attr_put_strz(nlh, NFCTH_POLICY_NAME, p->name);
	mnl_attr_put_u32(nlh, NFCTH_POLICY_EXPECT_MAX, htonl(p->expect_max));
	mnl_attr_put_u32(nlh, NFCTH_POLICY_EXPECT_TIMEOUT,
			htonl(p->expect_timeout));
	mnl_attr_nest_end(nlh, nest);
}

/**
 * nfct_helper_nlmsg_build_payload - build payload from helper object
 * \param nlh: netlink message that you want to use to add the payload.
 * \param nfct_helper: pointer to a helper object
 */
void
nfct_helper_nlmsg_build_payload(struct nlmsghdr *nlh, struct nfct_helper *h)
{
	struct nlattr *nest;


	if (h->bitset & (1 << NFCTH_ATTR_NAME))
		mnl_attr_put_strz(nlh, NFCTH_NAME, h->name);

	if (h->bitset & (1 << NFCTH_ATTR_QUEUE_NUM))
		mnl_attr_put_u32(nlh, NFCTH_QUEUE_NUM, htonl(h->queue_num));

	if (h->bitset & (1 << NFCTH_ATTR_PRIV_DATA_LEN)) {
		mnl_attr_put_u32(nlh, NFCTH_PRIV_DATA_LEN,
					htonl(h->priv_data_len));
	}

	if (h->bitset & (1 << NFCTH_ATTR_PROTO_L3NUM) ||
	    h->bitset & (1 << NFCTH_ATTR_PROTO_L4NUM)) {
		nest = mnl_attr_nest_start(nlh, NFCTH_TUPLE);
		mnl_attr_put_u16(nlh, NFCTH_TUPLE_L3PROTONUM,
					htons(h->tuple.l3num));
		mnl_attr_put_u8(nlh, NFCTH_TUPLE_L4PROTONUM, h->tuple.l4num);
		mnl_attr_nest_end(nlh, nest);
	}

	if (h->bitset & (1 << NFCTH_ATTR_POLICY1) ||
	    h->bitset & (1 << NFCTH_ATTR_POLICY2) ||
	    h->bitset & (1 << NFCTH_ATTR_POLICY3) ||
	    h->bitset & (1 << NFCTH_ATTR_POLICY4)) {
		nest = mnl_attr_nest_start(nlh, NFCTH_POLICY);
		int policy_set_num = 0;

		if (h->bitset & (1 << NFCTH_ATTR_POLICY1)) {
			nfct_helper_nlmsg_build_policy(nlh,
							h->expect_policy[0]);
			policy_set_num++;
		}
		if (h->bitset & (1 << NFCTH_ATTR_POLICY2)) {
			nfct_helper_nlmsg_build_policy(nlh,
							h->expect_policy[1]);
			policy_set_num++;
		}
		if (h->bitset & (1 << NFCTH_ATTR_POLICY3)) {
			nfct_helper_nlmsg_build_policy(nlh,
							h->expect_policy[2]);
			policy_set_num++;
		}
		if (h->bitset & (1 << NFCTH_ATTR_POLICY4)) {
			nfct_helper_nlmsg_build_policy(nlh,
							h->expect_policy[3]);
			policy_set_num++;
		}

		mnl_attr_put_u32(nlh, NFCTH_POLICY_SET_NUM,
					htonl(policy_set_num));

		mnl_attr_nest_end(nlh, nest);
	}

	if (h->bitset & (1 << NFCTH_ATTR_STATUS))
		mnl_attr_put_u32(nlh, NFCTH_STATUS, ntohl(h->status));
}
EXPORT_SYMBOL(nfct_helper_nlmsg_build_payload);

static int
nfct_helper_nlmsg_parse_tuple_cb(const struct nlattr *attr, void *data)
{
	const struct nlattr **tb = data;
	int type = mnl_attr_get_type(attr);

	if (mnl_attr_type_valid(attr, NFCTH_TUPLE_MAX) < 0)
		return MNL_CB_OK;

	switch(type) {
	case NFCTH_TUPLE_L3PROTONUM:
		if (mnl_attr_validate(attr, MNL_TYPE_U16) < 0) {
			perror("mnl_attr_validate");
			return MNL_CB_ERROR;
		}
		break;
	case NFCTH_TUPLE_L4PROTONUM:
		if (mnl_attr_validate(attr, MNL_TYPE_U8) < 0) {
			perror("mnl_attr_validate");
			return MNL_CB_ERROR;
		}
		break;
	default:
		break;
	}
	tb[type] = attr;
	return MNL_CB_OK;
}

static void
nfct_helper_nlmsg_parse_tuple(const struct nlattr *attr,
			      struct nfct_helper *helper)
{
	struct nlattr *tb[NFCTH_TUPLE_MAX+1] = {};

	mnl_attr_parse_nested(attr, nfct_helper_nlmsg_parse_tuple_cb, tb);
	if (tb[NFCTH_TUPLE_L3PROTONUM]) {
		nfct_helper_attr_set_u16(helper, NFCTH_ATTR_PROTO_L3NUM,
			ntohs(mnl_attr_get_u16(tb[NFCTH_TUPLE_L3PROTONUM])));
	}
	if (tb[NFCTH_TUPLE_L4PROTONUM]) {
		nfct_helper_attr_set_u8(helper, NFCTH_ATTR_PROTO_L4NUM,
			mnl_attr_get_u8(tb[NFCTH_TUPLE_L4PROTONUM]));
	}
}

static int
nfct_helper_nlmsg_parse_policy_cb(const struct nlattr *attr, void *data)
{
	const struct nlattr **tb = data;
	int type = mnl_attr_get_type(attr);

	if (mnl_attr_type_valid(attr, NFCTH_POLICY_MAX) < 0)
		return MNL_CB_OK;

	switch(type) {
	case NFCTH_POLICY_NAME:
		if (mnl_attr_validate(attr, MNL_TYPE_STRING) < 0) {
			perror("mnl_attr_validate");
			return MNL_CB_ERROR;
		}
		break;
	case NFCTH_POLICY_EXPECT_MAX:
		if (mnl_attr_validate(attr, MNL_TYPE_U32) < 0) {
			perror("mnl_attr_validate");
			return MNL_CB_ERROR;
		}
		break;
	case NFCTH_POLICY_EXPECT_TIMEOUT:
		if (mnl_attr_validate(attr, MNL_TYPE_U32) < 0) {
			perror("mnl_attr_validate");
			return MNL_CB_ERROR;
		}
		break;
	default:
		break;
	}
	tb[type] = attr;
	return MNL_CB_OK;
}

static int
nfct_helper_nlmsg_parse_policy_set_cb(const struct nlattr *attr, void *data)
{
	const struct nlattr **tb = data;
	int type = mnl_attr_get_type(attr);

	if (mnl_attr_type_valid(attr, NFCTH_POLICY_SET_MAX) < 0)
		return MNL_CB_OK;

	switch(type) {
	case NFCTH_POLICY_SET_NUM:
		if (mnl_attr_validate(attr, MNL_TYPE_U32) < 0) {
			perror("mnl_attr_validate");
			return MNL_CB_ERROR;
		}
		break;
	default:
		/* NFCTH_POLICY_SET1, 2, 3 and 4. */
		break;
	}
	tb[type] = attr;
	return MNL_CB_OK;
}

static void
nfct_helper_nlmsg_parse_policy(const struct nlattr *attr,
			       struct nfct_helper *helper)
{
	struct nlattr *tb[NFCTH_POLICY_MAX+1] = {};
	struct nfct_helper_policy *p;

	p = nfct_helper_policy_alloc();
	if (p == NULL)
		return;

	mnl_attr_parse_nested(attr, nfct_helper_nlmsg_parse_policy_cb, tb);
	if (tb[NFCTH_POLICY_NAME]) {
		nfct_helper_policy_attr_set_str(p, NFCTH_ATTR_POLICY_NAME,
			mnl_attr_get_str(tb[NFCTH_POLICY_NAME]));
	}
	if (tb[NFCTH_POLICY_EXPECT_MAX]) {
		nfct_helper_policy_attr_set_u32(p, NFCTH_ATTR_POLICY_MAX,
			ntohl(mnl_attr_get_u32(tb[NFCTH_POLICY_EXPECT_MAX])));
	}
	if (tb[NFCTH_POLICY_EXPECT_TIMEOUT]) {
		nfct_helper_policy_attr_set_u32(p, NFCTH_ATTR_POLICY_TIMEOUT,
			ntohl(mnl_attr_get_u32(tb[NFCTH_POLICY_EXPECT_TIMEOUT])));
	}

	helper->expect_policy[helper->policy_num++] = p;
}

static void
nfct_helper_nlmsg_parse_policy_set(const struct nlattr *attr,
				   struct nfct_helper *helper)
{
	struct nlattr *tb[NFCTH_POLICY_SET_MAX+1] = {};
	int i;

	mnl_attr_parse_nested(attr, nfct_helper_nlmsg_parse_policy_set_cb, tb);
	if (tb[NFCTH_POLICY_SET_NUM]) {
		helper->policy_num =
			ntohl(mnl_attr_get_u32(tb[NFCTH_POLICY_SET_NUM]));
	}
	for (i=0; i<helper->policy_num; i++) {
		if (tb[NFCTH_POLICY_SET+i]) {
			nfct_helper_nlmsg_parse_policy(tb[NFCTH_POLICY_SET+i],
						       helper);
		}
	}
}

static int
nfct_helper_nlmsg_parse_attr_cb(const struct nlattr *attr, void *data)
{
	const struct nlattr **tb = data;
	int type = mnl_attr_get_type(attr);

	if (mnl_attr_type_valid(attr, NFCTH_MAX) < 0)
		return MNL_CB_OK;

	switch(type) {
	case NFCTH_NAME:
		if (mnl_attr_validate(attr, MNL_TYPE_STRING) < 0) {
			perror("mnl_attr_validate");
			return MNL_CB_ERROR;
		}
		break;
	case NFCTH_QUEUE_NUM:
		if (mnl_attr_validate(attr, MNL_TYPE_U32) < 0) {
			perror("mnl_attr_validate");
			return MNL_CB_ERROR;
		}
		break;
	case NFCTH_TUPLE:
		if (mnl_attr_validate(attr, MNL_TYPE_NESTED) < 0) {
			perror("mnl_attr_validate");
			return MNL_CB_ERROR;
		}
		break;
	case NFCTH_POLICY:
		if (mnl_attr_validate(attr, MNL_TYPE_NESTED) < 0) {
			perror("mnl_attr_validate");
			return MNL_CB_ERROR;
		}
		break;
	}
	tb[type] = attr;
	return MNL_CB_OK;
}

/**
 * nfct_helper_nlmsg_parse_payload - set helper object attributes from message
 * \param nlh: netlink message that you want to use to add the payload.
 * \param nfct_helper: pointer to a helper object
 *
 * This function returns -1 in case that some mandatory attributes are
 * missing. On sucess, it returns 0.
 */
int
nfct_helper_nlmsg_parse_payload(const struct nlmsghdr *nlh,
				struct nfct_helper *h)
{
	struct nlattr *tb[NFCTH_MAX+1] = {};
	struct nfgenmsg *nfg = mnl_nlmsg_get_payload(nlh);

	mnl_attr_parse(nlh, sizeof(*nfg), nfct_helper_nlmsg_parse_attr_cb, tb);
	if (!tb[NFCTH_NAME] || !tb[NFCTH_QUEUE_NUM] ||
	    !tb[NFCTH_TUPLE] || !tb[NFCTH_POLICY] || !tb[NFCTH_STATUS])
		return -1;

	if (tb[NFCTH_NAME]) {
		nfct_helper_attr_set_str(h, NFCTH_ATTR_NAME,
				 mnl_attr_get_str(tb[NFCTH_NAME]));
	}
	if (tb[NFCTH_ATTR_QUEUE_NUM]) {
		nfct_helper_attr_set_u32(h, NFCTH_ATTR_QUEUE_NUM,
				 ntohl(mnl_attr_get_u32(tb[NFCTH_QUEUE_NUM])));
	}
	if (tb[NFCTH_TUPLE])
		nfct_helper_nlmsg_parse_tuple(tb[NFCTH_TUPLE], h);

	if (tb[NFCTH_POLICY])
		nfct_helper_nlmsg_parse_policy_set(tb[NFCTH_POLICY], h);

	if (tb[NFCTH_PRIV_DATA_LEN]) {
		nfct_helper_attr_set_u32(h, NFCTH_ATTR_PRIV_DATA_LEN,
			ntohl(mnl_attr_get_u32(tb[NFCTH_PRIV_DATA_LEN])));
	}

	if (tb[NFCTH_STATUS]) {
		nfct_helper_attr_set_u32(h, NFCTH_ATTR_STATUS,
				 ntohl(mnl_attr_get_u32(tb[NFCTH_STATUS])));
	}
	return 0;
}
EXPORT_SYMBOL(nfct_helper_nlmsg_parse_payload);

/**
 * @}
 */
