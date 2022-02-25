#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     access_ctl core.sh
# brief    
# author   Chen chen
# version  1.0.0
# date     08June15
# histry   arg 1.0.0, 08June15, Chen chen, Create the file. 

FW_LIBDIR=${FW_LIBDIR:-/lib/firewall}
FW_ACL_LIBDIR=${FW_ACL_LIBDIR:-/lib/access_ctl}

. $FW_LIBDIR/fw.sh
. $FW_LIBDIR/config.sh
. /lib/zone/zone_api.sh
. /lib/functions.sh

fw_is_loaded() {
	local bool=$(uci_get_state firewall.core.loaded)
}


fw_acl_init()
{
	[ -z "$FW_ACL_INITIALIZED" ] || return 0

	fw_config_append access_ctl
	fw_config_append service

	for file in $FW_ACL_LIBDIR/core_*.sh; do
		. $file
	done
	FW_ACL_INITIALIZED=1
	return 0

}

fw_acl_start() {
	
	fw_acl_init

	fw_is_loaded || {
		#syslog 
		exit 1
	}

	echo "load acl rules"
	fw_acl_load_rules


}

fw_acl_stop() {
	fw_acl_init

	fw_is_loaded || {
		#syslog
		exit 1
	}
	fw_acl_clear
}

fw_acl_restart() {
	fw_acl_stop
	fw_acl_start
}

fw_acl_reload() {
	fw_acl_restart
}