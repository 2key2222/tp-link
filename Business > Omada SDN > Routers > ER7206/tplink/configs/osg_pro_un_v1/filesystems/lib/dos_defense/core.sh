#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     dos_defense core.sh
# brief    
# author   Chen chen
# version  1.0.0
# date     18June15
# histry   arg 1.0.0, 18June15, Chen chen, Create the file.

FD_LIBDIR=${FD_LIBDIR:-/lib/dos_defense}
FW_LIBDIR=${FW_LIBDIR:-/lib/firewall}

. $FW_LIBDIR/fw.sh
. $FW_LIBDIR/config.sh
. /lib/functions.sh

fw_is_loaded()
{
	local bool=$(uci_get_state firewall.core.loaded)
	return $((! ${bool:-0}))
}

fw_init()
{
	[ -z "$FD_INITIALIZED" ] || return 0
	
	
	fw_config_append dos_defense
	
	

	for file in $FD_LIBDIR/core_*.sh; do
		. $file
	done
	FD_INITIALIZED=1
	return 0
}



fd_start()
{
	fw_init
	fw_is_loaded || {
		#syslog
		exit 1
	}

	echo "loading dos defense"
	fw_load_dos_defense
	# syslog



}


fd_stop()
{
	fw_init

	fw_is_loaded || {
		# syslog
		exit 1
	}

	echo "exiting dos defense"
	fw_exit_all dos_defense
	# syslog
}

fd_restart()
{
	fd_stop
	fd_start
}

fd_reload()
{
	fd_restart
}