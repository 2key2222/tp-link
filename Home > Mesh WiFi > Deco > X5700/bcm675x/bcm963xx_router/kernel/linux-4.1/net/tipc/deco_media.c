/*
 * net/tipc/deco_media.c: deco Ethernet bearer support for TIPC
 *
 * Copyright (c) 2001-2007, 2013, Ericsson AB
 * Copyright (c) 2005-2008, 2011-2013, Wind River Systems
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "core.h"
#include "bearer.h"

#define ETH_ADDR_OFFSET	4	/* message header offset of MAC address */

#define MASTER_ROLE 1
#define SLAVE_ROLE 0

static int is_master = SLAVE_ROLE;

/* convert deco Ethernet address to string */
static int tipc_deco_addr2str(struct tipc_media_addr *a, char *str_buf,
			     int str_size)
{
	if (str_size < 18)	/* 18 = strlen("aa:bb:cc:dd:ee:ff\0") */
		return 1;

	sprintf(str_buf, "%pM", a->value);
	return 0;
}

/* convert deco Ethernet address format to message header format */
static int tipc_deco_addr2msg(char *msg_area, struct tipc_media_addr *a)
{
	memset(msg_area, 0, TIPC_MEDIA_ADDR_SIZE);
	msg_area[TIPC_MEDIA_TYPE_OFFSET] = TIPC_MEDIA_TYPE_DECO;
	memcpy(msg_area + ETH_ADDR_OFFSET, a->value, ETH_ALEN);
    msg_area[ETH_ADDR_OFFSET + ETH_ALEN + 2] = is_master;
	return 0;
}

/* tipc_deco_addr_set - initialize Ethernet media address structure
 *
 * Media-dependent "value" field stores MAC address in first 6 bytes
 * and zeroes out the remaining bytes.
 */
static int tipc_deco_addr_set(struct tipc_bearer *b,
	struct tipc_media_addr *a, char *mac)
{
	int len = b->media->hwaddr_len;

	if (unlikely(sizeof(a->value) < len)) {
		WARN_ONCE(1, "Media length invalid\n");
		return 1;
	}

	memcpy(a->value, mac, len);
	memset(a->value + len, 0, sizeof(a->value) - len);
	a->media_id = b->media->type_id;
	a->broadcast = !memcmp(mac, b->bcast_addr.value, len);
	return 0;
}

/* convert message header address format to Ethernet format */
static int tipc_deco_msg2addr(struct tipc_bearer *tb_ptr,
			     struct tipc_media_addr *a, char *msg_area)
{
	if (msg_area[TIPC_MEDIA_TYPE_OFFSET] != TIPC_MEDIA_TYPE_DECO)
		return 1;

	tipc_deco_addr_set(tb_ptr, a, msg_area + ETH_ADDR_OFFSET);
    if(is_master != MASTER_ROLE && msg_area[ETH_ADDR_OFFSET + ETH_ALEN + 2] != MASTER_ROLE)
    {
        a->broadcast = 1;
    }
	return 0;
}

static int tipc_deco_enable_l2_media(struct net *net, struct tipc_bearer *b,
	struct nlattr *attr[])
{
    char *role_name;
    char *driver_name = strchr((const char *)b->name, ':') + 1;
    if (!driver_name)
        return -ENODEV;
    role_name = strchr((const char *)driver_name, ':');
    if (!role_name)
        return -ENODEV;
    if(role_name[1] == '1')
    {
        is_master = 1;
    }
    else
    {
        is_master = 0;
    }
    memset(role_name,0, strlen(role_name));
    return tipc_enable_l2_media(&init_net, b, NULL);
}

#define TIPC_DECO_DEF_LINK_TOL 4000

/* Ethernet media registration info */
struct tipc_media deco_media_info = {
	.send_msg	= tipc_l2_send_msg,
	.enable_media	= tipc_deco_enable_l2_media,
	.disable_media	= tipc_disable_l2_media,
	.addr2str	= tipc_deco_addr2str,
	.addr2msg	= tipc_deco_addr2msg,
	.msg2addr	= tipc_deco_msg2addr,
	.raw2addr	= tipc_deco_addr_set,
	.priority	= TIPC_DEF_LINK_PRI,
	.tolerance	= TIPC_DECO_DEF_LINK_TOL,
	.window		= TIPC_DEF_LINK_WIN,
	.type_id	= TIPC_MEDIA_TYPE_DECO,
	.hwaddr_len	= ETH_ALEN,
	.name		= "deco"
};

