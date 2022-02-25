/*
 * Copyright (c) 2012, The Linux Foundation. All rights reserved.
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all copies.
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


#ifdef KVER32
#include <linux/kconfig.h>  
#include <generated/autoconf.h>
#else
#include <linux/autoconf.h>
#endif
#include <linux/kthread.h>
#include <linux/udp.h>
#include <linux/rculist_nulls.h>
#ifdef KVER32
#include <linux/rcupdate.h>
#endif
#include <net/netfilter/nf_conntrack_acct.h>
#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_helper.h>
#include <net/route.h>
#include <net/netevent.h>
#include <net/ip_fib.h>
#include "nat_helper.h"
#include "napt_acl.h"

#include "lib/nat_helper_hsl.h"

extern struct net init_net;
static struct task_struct *ct_task = NULL;

/*#undef HNAT_PRINTK
#define HNAT_PRINTK(x...) aos_printk(x)*/

#ifdef KVER32
extern void __rcu_read_lock(void);
extern void __rcu_read_unlock(void);
extern unsigned int nf_conntrack_htable_size;
#endif

void
napt_ct_aging_disable(uint32_t ct_addr)
{
    if(!ct_addr)
    {
        return;
    }

    struct nf_conn *ct = (struct nf_conn *)ct_addr;

    if (timer_pending(&ct->timeout))
    {
        del_timer(&ct->timeout);
    }
}

int
napt_ct_aging_is_enable(uint32_t ct_addr)
{
    if(!ct_addr)
    {
        return 0;
    }

    struct nf_conn *ct = (struct nf_conn *)ct_addr;

    return timer_pending(&(((struct nf_conn *)ct)->timeout));
}

void
napt_ct_aging_enable(uint32_t ct_addr)
{
    if(!ct_addr)
    {
        return;
    }

    if(napt_ct_aging_is_enable(ct_addr))
    {
        return;
    }

    struct nf_conn *ct = (struct nf_conn *)ct_addr;
    uint16_t l3num = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.l3num;
    uint8_t protonum = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum;

    ct->timeout.expires = jiffies+10*HZ;

    if ((l3num == AF_INET) && (protonum == IPPROTO_TCP))
    {
        if (ct->proto.tcp.state == TCP_CONNTRACK_ESTABLISHED)
        {
            ct->timeout.expires = jiffies+(5*24*60*60*HZ);
        }
    }
    ct->in_hnat = 0; /* once timmer is enabled, contrack not in HNAT anymore. */
    HNAT_PRINTK("<aging> ct:[%x] add timeout again\n",  ct_addr);
    add_timer(&ct->timeout);
}

void
napt_ct_to_hw_entry(uint32_t ct_addr, napt_entry_t *napt)
{
    if(!ct_addr)
    {
        return;
    }

#define NAPT_AGE   0xe

    struct nf_conn *ct = (struct nf_conn *)ct_addr;
    struct nf_conntrack_tuple *org_tuple, *rep_tuple;

    if ((ct->status & IPS_NAT_MASK) == IPS_SRC_NAT)     //snat
    {
        org_tuple = &(ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple);
        rep_tuple = &(ct->tuplehash[IP_CT_DIR_REPLY].tuple);

    }
    else                                                //dnat
    {
        org_tuple = &(ct->tuplehash[IP_CT_DIR_REPLY].tuple);
        rep_tuple = &(ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple);
    }

    uint8_t protonum = org_tuple->dst.protonum;

    if(org_tuple->src.l3num == AF_INET)
    {
        if(protonum == IPPROTO_TCP)
        {
            napt->flags = FAL_NAT_ENTRY_PROTOCOL_TCP;

        }
        else if(protonum == IPPROTO_UDP)
        {
            napt->flags = FAL_NAT_ENTRY_PROTOCOL_UDP;

        }
    }

    napt->src_addr = ntohl(org_tuple->src.u3.ip);
    napt->src_port = ntohs(org_tuple->src.u.all);
    napt->dst_addr = ntohl(org_tuple->dst.u3.ip);
    napt->dst_port = ntohs(org_tuple->dst.u.all);
    napt->trans_addr = ntohl(rep_tuple->dst.u3.ip);
    napt->trans_port = ntohs(rep_tuple->dst.u.all);
    napt->status = NAPT_AGE;

    return;
}

uint64_t
napt_ct_pkts_get(uint32_t ct_addr)
{
    if(!ct_addr)
    {
        return 0;
    }

    struct nf_conn *ct = (struct nf_conn *)ct_addr;
    struct nf_conn_counter *cct = nf_conn_acct_find(ct);

    if(cct)
    {
        return (atomic64_read(&cct[IP_CT_DIR_ORIGINAL].packets) +
                atomic64_read(&cct[IP_CT_DIR_REPLY].packets));
    }
    else
    {
        return 0;
    }
}

int
napt_ct_type_is_nat(uint32_t ct_addr)
{
    if(!ct_addr)
    {
        return 0;
    }

    struct nf_conn *ct = (struct nf_conn *)ct_addr;

    // HNAT couldn't handle both SNAT and DNAT for one ct
    if ((IPS_NAT_MASK & ct->status) == IPS_NAT_MASK)
	return 0;	

    return ((IPS_NAT_MASK & (ct)->status)?1:0);
}

int
napt_ct_status_is_estab(uint32_t ct_addr)
{
    if(!ct_addr)
    {
        return 0;
    }

    struct nf_conn *ct = (struct nf_conn *)ct_addr;
    uint16_t l3num = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.l3num;
    uint8_t protonum = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum;

    if ((l3num == AF_INET) && (protonum == IPPROTO_TCP))
    {
        if (ct->proto.tcp.state == TCP_CONNTRACK_ESTABLISHED)
        {
            return 1;
        }
    }
    else if ((l3num == AF_INET) && (protonum == IPPROTO_UDP))
    {
        return 1;
    }

    return 0;
}

uint32_t
napt_ct_priv_ip_get(uint32_t ct_addr)
{
    if(!ct_addr)
    {
        return 0;
    }

    struct nf_conn *ct = (struct nf_conn *)ct_addr;
    uint32_t usaddr;

    if ((ct->status & IPS_NAT_MASK) == IPS_SRC_NAT)     //snat
    {
        usaddr = ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip;
    }
    else
    {
        usaddr = ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip;
    }

    usaddr = ntohl(usaddr);

    return usaddr;
}

/*
 * check conntrack is need to alg
 */
int napt_ct_is_alg(uint32_t ct_addr)
{
	if(!ct_addr)
	{
		return 1;
	}
	
	struct nf_conn_help *help = NULL;
	struct nf_conn *ct = (struct nf_conn *)ct_addr;

	help = nfct_help(ct);
	
	if (help && help->helper)
	{
		return 1;
	}

	return 0;
}

uint32_t
napt_ct_next_hop_ip_get(uint32_t prv_addr, uint32_t pub_addr)
{
	uint32_t next_hop;
	struct fib_result res;
#ifdef KVER32
	struct flowi4 fl;
#else
	struct flowi fl;
#endif

	if (!prv_addr || !pub_addr)
	{
		printk("error pubaddr: %x, prv_addr: %x.\n", pub_addr, prv_addr);
		return 0;
	}

#ifdef KVER32
	memset(&fl, 0, sizeof(struct flowi4));
	fl.flowi4_scope = RT_SCOPE_UNIVERSE;
	fl.daddr = pub_addr;
	fl.saddr = prv_addr;
#else
	memset(&fl, 0, sizeof(struct flowi));
	fl.nl_u.ip4_u.scope = RT_SCOPE_UNIVERSE;
	fl.nl_u.ip4_u.daddr = pub_addr;
	fl.nl_u.ip4_u.saddr = prv_addr;
#endif	

	if (fib_lookup(&init_net, &fl, &res) != 0)
	{
		return 0;
	}
	next_hop = FIB_RES_GW(res);
#ifndef KVER32
	fib_res_put(&res);
#endif
	return next_hop ? next_hop : pub_addr;
}

void
napt_ct_list_lock(void)
{
    rcu_read_lock();
}

void
napt_ct_list_unlock(void)
{
    rcu_read_unlock();
}

uint32_t
napt_ct_list_iterate(uint32_t *hash, uint32_t *iterate)
{
    struct net *net = &init_net;
    struct nf_conntrack_tuple_hash *h = NULL;
    struct nf_conn *ct = NULL;
    struct hlist_nulls_node *pos = (struct hlist_nulls_node *) (*iterate);

    while(*hash < nf_conntrack_htable_size)
    {
        if(pos == 0)
        {
            /*get head for list*/
            pos = rcu_dereference((&net->ct.hash[*hash])->first);
        }

        hlist_nulls_for_each_entry_from(h, pos, hnnode)
        {
            (*iterate) = (uint32_t)(pos->next);
            ct = nf_ct_tuplehash_to_ctrack(h);
            	return (uint32_t) ct;
        }

        ++(*hash);
        pos = 0;
    }

    return 0;
}

int
napt_ct_task_should_stop(void)
{
    return kthread_should_stop();
}

void
napt_ct_task_start(int (*task)(void*), const char *task_name)
{
    ct_task = kthread_create(task, NULL, task_name);

    if(IS_ERR(ct_task))
    {
        aos_printk("thread: %s create fail\n", task_name);
        return;
    }

    wake_up_process(ct_task);

    HNAT_PRINTK("thread: %s create success pid:%d\n",
                task_name, ct_task->pid);
}

void
napt_ct_task_stop(void)
{
    if(ct_task)
    {
        kthread_stop(ct_task);
	ct_task = NULL;
    }
}
int napt_ct_task_exit(void)
{
	return (ct_task == NULL);
}

void
napt_ct_task_sleep(int secs)
{
    msleep_interruptible(secs*1000);
}
