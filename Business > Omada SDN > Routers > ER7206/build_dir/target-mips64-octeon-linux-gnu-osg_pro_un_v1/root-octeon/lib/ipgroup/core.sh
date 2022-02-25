#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     ipgroup core.sh
# brief    
# author   Chen chen
# version  1.0.0
# date     11June15
# histry   arg 1.0.0, 08June15, Chen chen, Create the file.

IPGRP_LIBDIR=${IPGRP_LIBDIR:-/lib/ipgroup}
. $IPGRP_LIBDIR/config.sh

ipgroup_start() 
{
	ipgroup_init

	
	echo "load ipgroup "
	ipgroup_load
	ipgoup_check_modify

	echo "load Me Set"
	ipgroup_load_default_ifaces_set
	
	[ -x /usr/sbin/conntrack ] && conntrack -D -m 0x10000
}

ipgroup_init()
{
	[ -z "$IPGROUP_INITIALIZED" ] || return 0

	for file in $IPGRP_LIBDIR/core_*.sh; do
		. $file
	done
	IPGROUP_INITIALIZED=1
	return 0
}

ipgroup_stop()
{
	echo ""
}

ipgroup_restart()
{
	ipgroup_stop
	ipgroup_start
}

ipgroup_reload()
{
	ipgroup_restart
}

ipgroup_interface_event()
{
	ipgroup_load_default_ifaces_set
}