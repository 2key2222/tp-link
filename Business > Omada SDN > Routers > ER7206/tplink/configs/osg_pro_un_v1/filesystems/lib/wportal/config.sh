#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     config.sh
# brief    
# author   Qian uujun
# version  1.0.0
# date     19Sep15
# histry   arg 1.0.0, 19Sep15, Qian xujun, Create the file.

. /lib/wportal/core_wportal.sh

wportal_start() 
{
	wportal_init

	set_wifidog_conf    

    auth_server_start
}

wportal_init()
{
	[ -z "$WPORTAL_INITIALIZED" ] || return 0

	wportal_config_append wportal #uci config name
}

wportal_stop()
{
	echo ""
}

wportal_restart()
{
	wportal_stop
	wportal_start
}

wportal_reload()
{
	wportal_restart
}