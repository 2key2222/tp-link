/*
 * m_connmark.c		Connection tracking marking import
 *
 * Copyright (c) 2011 Felix Fietkau <nbd@openwrt.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place - Suite 330, Boston, MA 02111-1307 USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"
#include "tc_util.h"

static void
explain(void)
{
	fprintf(stderr, "Usage: ... connmark\n");
}

static void
usage(void)
{
	explain();
	exit(-1);
}

static int
parse_connmark(struct action_util *a, int *argc_p, char ***argv_p, int tca_id,
	      struct nlmsghdr *n)
{
	int argc = *argc_p;
	char **argv = *argv_p;

	if (matches(*argv, "connmark") != 0)
		return -1;

	NEXT_ARG();

	*argc_p = argc;
	*argv_p = argv;
	return 0;
}

static int print_connmark(struct action_util *au, FILE *f, struct rtattr *arg)
{
	if (arg == NULL)
		return -1;

	fprintf(f, " connmark");

	return 0;
}

struct action_util connmark_action_util = {
	.id = "connmark",
	.parse_aopt = parse_connmark,
	.print_aopt = print_connmark,
};
