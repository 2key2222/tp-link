/* ebt_ip6
 * 
 * Authors:
 * Kuo-Lang Tseng <kuo-lang.tseng@intel.com>
 * Manohar Castelino <manohar.castelino@intel.com>
 *
 * Summary:
 * This is just a modification of the IPv4 code written by 
 * Bart De Schuymer <bdschuym@pandora.be>
 * with the changes required to support IPv6
 *
 *  Extend by Broadcom at Jan 31, 2019
 */

#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <netdb.h>
#include "../include/ebtables_u.h"
#include "../include/linux/netfilter_bridge/ebt_ip6_extend.h"



#define IP_TCLASS_EXTEND '1'
#define IP_FLOWLABEL_EXTEND '2'

static const struct option opts[] =
{
	{ "ip6-traffic-class-extend"    , required_argument, 0, IP_TCLASS_EXTEND },
	{ "ip6-tclass-extend"           , required_argument, 0, IP_TCLASS_EXTEND},
	{ "ip6-flow-label-extend"       , required_argument, 0,  IP_FLOWLABEL_EXTEND},
	{ 0 }
};

static uint8_t parse_tclass(const char *tclassstr)
{
	char *end;
	int tclass;

	tclass = strtol(tclassstr, &end, 16);
	if ((*end == '\0') || (*end == ':') || (*end == '/')) {
		if (tclass >= 0 && tclass <= 0xFF) {
            return tclass;
		}
	}

	ebt_print_error("Problem with specified tclass '%s'", tclassstr);
	return 0;
}

static int parse_tclass_mask(char *mask, unsigned char *mask2)
{
	char *end;

	*mask2 = (unsigned char)strtol(mask, &end, 16);

	if (*end != '\0')
		ebt_print_error("Problem with specified tlcass mask 0x%x", mask2);

	return 0;
}

static void
parse_tclass_range_mask(const char *tclassstring, uint8_t *tclass, uint8_t *mask)
{
	char *buffer;
	char *cp;
	char *p;

	buffer = strdup(tclassstring);
	p = strrchr(buffer, '/');
	cp = strchr(buffer, ':');

	if (cp == NULL) {
		tclass[0] = tclass[1] = parse_tclass(buffer);
	} else {
		*cp = '\0';
		cp++;
		tclass[0] = buffer[0] ? parse_tclass(buffer) : 0;
        if (ebt_errormsg[0] != '\0')
			return;
		tclass[1] = cp[0] ? parse_tclass(cp) : 0xFF;
		if (ebt_errormsg[0] != '\0')
			return;
		
		if (tclass[0] > tclass[1])
			ebt_print_error("Invalid tclass range (min > max)");
	}

	if (p != NULL) {
		parse_tclass_mask(p + 1, (unsigned char *)mask);
	} else {
		*mask = 0xFF;
	} 
   
	free(buffer);
}

static void
parse_flow_label(uint32_t input, uint8_t * flow_lbl)
{
	char szFlowLabel[10] = {0};
	char szTemp[3] = {0};
	int i;
	char *end;

	sprintf(szFlowLabel, "%06X", input);

	for (i = 0; i < 3; i++)
	{
		szTemp[0] = szFlowLabel[2*i];
		szTemp[1] = szFlowLabel[2*i+1];
		*(flow_lbl + i) = strtoul(szTemp, &end, 16);
	}
}

static void print_tclass_range_mask(uint8_t *tclass, uint8_t mask)
{
	char str[128];
	int i;
	char * p = str;

	memset(str, 0, sizeof(str));
	if (tclass[0] == tclass[1])
		i = snprintf(str, sizeof(str), "0x%02X", tclass[0]);
	else
		i = snprintf(str, sizeof(str),"0x%02X:0x%02X", tclass[0], tclass[1]);

	if (mask != 0xFF)
		snprintf(p + i, sizeof(str) - i, "/0x%02X ", mask);
	else
		snprintf(p + i, sizeof(str) - i, " ");

	printf("%s", str);
}

static void print_help()
{
	printf(
"ip6 options:\n"
"--ip6-tclass-extend [!] tclass[:tclass][/mask]        : ipv6 traffic class specification\n"
"--ip6-flow-label-extend [!] flowlabel : ipv6 flow label specification\n");
}

static void init(struct ebt_entry_match *match)
{
	struct ebt_ip6_extend_info *ipinfo = (struct ebt_ip6_extend_info *)match->data;

	ipinfo->invflags = 0;
	ipinfo->bitmask = 0;
}

#define OPT_TCLASS_EXTEND 0x01
#define OPT_FLOWLABEL_EXTEND 0x02
static int parse(int c, char **argv, int argc, const struct ebt_u_entry *entry,
   unsigned int *flags, struct ebt_entry_match **match)
{
	struct ebt_ip6_extend_info *ipinfo = (struct ebt_ip6_extend_info *)(*match)->data;
	char *end;
	long int i;

	switch (c) {
	case IP_TCLASS_EXTEND:
		ebt_check_option2(flags, OPT_TCLASS_EXTEND);
		if (ebt_check_inverse2(optarg))
			ipinfo->invflags |= EBT_IP6_TCLASS_EXTEND;
        parse_tclass_range_mask(optarg, ipinfo->tclass, &ipinfo->tclassmsk);
		ipinfo->bitmask |= EBT_IP6_TCLASS_EXTEND;
		break;

	case IP_FLOWLABEL_EXTEND:
		ebt_check_option2(flags, OPT_FLOWLABEL_EXTEND);
		if (ebt_check_inverse2(optarg))
			ipinfo->invflags |= EBT_IP6_FLOWLABEL_EXTEND;
		i = strtoul(optarg, &end, 16);
		if (*end != '\0') {
			ebt_print_error2("Problem with specified IPv6 flow label");
		} else {
			parse_flow_label((i & 0xFFFFF), ipinfo->flow_lbl);
		}
		ipinfo->bitmask |= EBT_IP6_FLOWLABEL_EXTEND;
		break;
		
	default:
		return 0;
	}
	return 1;
}

static void final_check(const struct ebt_u_entry *entry,
   const struct ebt_entry_match *match, const char *name,
   unsigned int hookmask, unsigned int time)
{
	if (entry->ethproto != ETH_P_IPV6) {
		ebt_print_error("For IPv6 filtering the protocol must be "
		            "specified as IPv6");
	} 
}

static void print(const struct ebt_u_entry *entry,
   const struct ebt_entry_match *match)
{
	struct ebt_ip6_extend_info *ipinfo = (struct ebt_ip6_extend_info *)match->data;

	if (ipinfo->bitmask & EBT_IP6_TCLASS_EXTEND) {
		printf("--ip6-tclass-extend ");
		if (ipinfo->invflags & EBT_IP6_TCLASS_EXTEND)
			printf("! ");
        print_tclass_range_mask(ipinfo->tclass, ipinfo->tclassmsk);
	}
	if (ipinfo->bitmask & EBT_IP6_FLOWLABEL_EXTEND) {
		printf("--ip6-flow-label-extend ");
		if (ipinfo->invflags & EBT_IP6_FLOWLABEL_EXTEND)
			printf("! ");
		printf("0x%02X%02X%02X ", ipinfo->flow_lbl[0], ipinfo->flow_lbl[1], ipinfo->flow_lbl[2]);
	}
}

static int compare(const struct ebt_entry_match *m1,
   const struct ebt_entry_match *m2)
{
	struct ebt_ip6_extend_info *ipinfo1 = (struct ebt_ip6_extend_info *)m1->data;
	struct ebt_ip6_extend_info *ipinfo2 = (struct ebt_ip6_extend_info *)m2->data;

	if (ipinfo1->bitmask != ipinfo2->bitmask)
		return 0;
	if (ipinfo1->invflags != ipinfo2->invflags)
		return 0;
	if (ipinfo1->bitmask & EBT_IP6_TCLASS_EXTEND) {
		if (ipinfo1->tclass[0] != ipinfo2->tclass[0] ||
            ipinfo1->tclass[1] != ipinfo2->tclass[1] ||
            ipinfo1->tclassmsk != ipinfo2->tclassmsk)
			return 0;
	}
	if (ipinfo1->bitmask & EBT_IP6_FLOWLABEL_EXTEND) {
		if (ipinfo1->flow_lbl[0] != ipinfo2->flow_lbl[0] ||
			ipinfo1->flow_lbl[1] != ipinfo2->flow_lbl[1] ||
			ipinfo1->flow_lbl[2] != ipinfo2->flow_lbl[2])
			return 0;
	}
	return 1;
}

static struct ebt_u_match ip6_extend_match =
{
	.name		= EBT_IP6_MATCH_EXTEND,
	.size		= sizeof(struct ebt_ip6_extend_info),
	.help		= print_help,
	.init		= init,
	.parse		= parse,
	.final_check	= final_check,
	.print		= print,
	.compare	= compare,
	.extra_ops	= opts,
};

void _init(void)
{
	ebt_register_match(&ip6_extend_match);
}
