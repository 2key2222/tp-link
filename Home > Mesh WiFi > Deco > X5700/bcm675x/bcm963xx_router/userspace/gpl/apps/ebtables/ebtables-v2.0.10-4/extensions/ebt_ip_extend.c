/* ebt_ip
 * 
 * Authors:
 * Bart De Schuymer <bdschuym@pandora.be>
 *
 * Changes:
 *    added ip-sport and ip-dport; parsing of port arguments is
 *    based on code from iptables-1.2.7a
 *    Innominate Security Technologies AG <mhopf@innominate.com>
 *    September, 2002
 *
 *  Extend by Broadcom at Jan 31, 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <netdb.h>
#include "../include/ebtables_u.h"
#include "../include/linux/netfilter_bridge/ebt_ip_extend.h"


#define IP_TOS_EXTEND  '1' /* include/bits/in.h seems to already define IP_TOS */


static struct option opts[] =
{
	{ "ip-tos-extend"              , required_argument, 0, IP_TOS_EXTEND  },
	{ 0 }
};

static uint8_t parse_tos(const char *tosstr)
{
	char *end;
	int tos;

	tos = strtol(tosstr, &end, 16);
	if ((*end == '\0') || (*end == ':') || (*end == '/')) {
		if (tos >= 0 && tos <= 0xFF) {
			return tos;
		}
	}

	ebt_print_error("Problem with specified tos '%s'", tosstr);
	return 0;
}

static int parse_tos_mask(char *mask, unsigned char *mask2)
{
	char *end;

	*mask2 = (unsigned char)strtol(mask, &end, 16);

	if (*end != '\0')
		ebt_print_error("Problem with specified tos mask 0x%x", mask2);

	return 0;
}

static void
parse_tos_range_mask(const char *tosstring, uint8_t *tos, uint8_t *mask)
{
	char *buffer;
	char *cp;
	char *p;

	buffer = strdup(tosstring);
	p = strrchr(buffer, '/');
	cp = strchr(buffer, ':');

	if (cp == NULL) {
		tos[0] = tos[1] = parse_tos(buffer);
	} else {
		*cp = '\0';
		cp++;
		tos[0] = buffer[0] ? parse_tos(buffer) : 0;
        if (ebt_errormsg[0] != '\0')
			return;
		tos[1] = cp[0] ? parse_tos(cp) : 0xFF;
		if (ebt_errormsg[0] != '\0')
			return;
		
		if (tos[0] > tos[1])
			ebt_print_error("Invalid tosrange (min > max)");
	}

	if (p != NULL) {
		parse_tos_mask(p + 1, (unsigned char *)mask);
	} else {
		*mask = 0xFF;
	} 

	free(buffer);
}

static void print_tos_range_mask(uint8_t *tos, uint8_t mask)
{
	char str[128];
	int i;
	char * p = str;

	memset(str, 0, sizeof(str));
	if (tos[0] == tos[1])
		i = snprintf(str, sizeof(str), "0x%02X", tos[0]);
	else
		i = snprintf(str, sizeof(str),"0x%02X:0x%02X", tos[0], tos[1]);

	if (mask != 0xFF)
		snprintf(p + i, sizeof(str) - i, "/0x%02X ", mask);
	else
		snprintf(p + i, sizeof(str) - i, " ");

	printf("%s", str);
}

static void print_help()
{
	printf(
"ip options:\n"
"--ip-tos-extend    [!] tos[:tos][/mask]   : ip tos specification\n");
}

static void init(struct ebt_entry_match *match)
{
	struct ebt_ip_extend_info *ipinfo = (struct ebt_ip_extend_info *)match->data;

	ipinfo->invflags = 0;
	ipinfo->bitmask = 0;
}

#define OPT_TOS_EXTEND    0x01

static int parse(int c, char **argv, int argc, const struct ebt_u_entry *entry,
   unsigned int *flags, struct ebt_entry_match **match)
{
	struct ebt_ip_extend_info *ipinfo = (struct ebt_ip_extend_info *)(*match)->data;

	switch (c) {
	case IP_TOS_EXTEND:
		ebt_check_option2(flags, OPT_TOS_EXTEND);
		if (ebt_check_inverse2(optarg))
			ipinfo->invflags |= EBT_IP_TOS_EXTEND;
        parse_tos_range_mask(optarg, ipinfo->tos, &ipinfo->tosmask);
		ipinfo->bitmask |= EBT_IP_TOS_EXTEND;
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
	if (entry->ethproto != ETH_P_IP) {
		ebt_print_error("For IP filtering the protocol must be "
					"specified as IPv4");
	}
}

static void print(const struct ebt_u_entry *entry,
   const struct ebt_entry_match *match)
{
	struct ebt_ip_extend_info *ipinfo = (struct ebt_ip_extend_info *)match->data;

	if (ipinfo->bitmask & EBT_IP_TOS_EXTEND) {
		printf("--ip-tos-extend ");
		if (ipinfo->invflags & EBT_IP_TOS_EXTEND)
			printf("! ");
		print_tos_range_mask(ipinfo->tos, ipinfo->tosmask);
	}
}

static int compare(const struct ebt_entry_match *m1,
   const struct ebt_entry_match *m2)
{
	struct ebt_ip_extend_info *ipinfo1 = (struct ebt_ip_extend_info *)m1->data;
	struct ebt_ip_extend_info *ipinfo2 = (struct ebt_ip_extend_info *)m2->data;

	if (ipinfo1->bitmask != ipinfo2->bitmask)
		return 0;
	if (ipinfo1->invflags != ipinfo2->invflags)
		return 0;
	if (ipinfo1->bitmask & EBT_IP_TOS_EXTEND) {
		if (ipinfo1->tos[0] != ipinfo2->tos[0] ||
            ipinfo1->tos[1] != ipinfo2->tos[1] ||
            ipinfo1->tosmask != ipinfo2->tosmask) 
			return 0;
	}
	return 1;
}

static struct ebt_u_match ip_extend_match =
{
	.name		= EBT_IP_MATCH_EXTEND,
	.size		= sizeof(struct ebt_ip_extend_info),
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
	ebt_register_match(&ip_extend_match);
}
