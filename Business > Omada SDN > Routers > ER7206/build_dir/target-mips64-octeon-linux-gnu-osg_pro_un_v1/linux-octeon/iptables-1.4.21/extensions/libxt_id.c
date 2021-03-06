/* Shared library add-on to iptables to add id match support. */

#include <stdio.h>
#include <xtables.h>
#include <linux/netfilter/xt_id.h>

enum {
	O_ID = 0,
};

static const struct xt_option_entry id_opts[] = {
	{
		.name  = "id",
		.id    = O_ID,
		.type  = XTTYPE_UINT32,
		.flags = XTOPT_MAND | XTOPT_PUT,
		XTOPT_POINTER(struct xt_id_info, id)
	},
	XTOPT_TABLEEND,
};

/* Saves the union ipt_matchinfo in parsable form to stdout. */
static void
id_save(const void *ip, const struct xt_entry_match *match)
{
	struct xt_id_info *idinfo = (void *)match->data;

	printf(" --id %lu", idinfo->id);
}

static struct xtables_match id_match = {
	.family		= NFPROTO_UNSPEC,
	.name		= "id",
	.version	= XTABLES_VERSION,
	.size		= XT_ALIGN(sizeof(struct xt_id_info)),
	.userspacesize	= XT_ALIGN(sizeof(struct xt_id_info)),
	.save 		= id_save,
	.x6_parse	= xtables_option_parse,
	.x6_options	= id_opts,
};

void _init(void)
{
	xtables_register_match(&id_match);
}
