#!/bin/sh 
#/etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file    ipsec_convert_uciconfig 
# brief   convert uci config(/etc/config/ipsec ) to which charon can read. 
# author   Yang xiaoqiang
# version  1.0.0
# date     08June15
# histry   arg 1.0.0, 08June15, Yang xiaoqiang, Create the file. 


. /lib/functions.sh


UCI_SESSION_LIMITS_CONFIG_FILE=/etc/config/session_limits
SESSION_LIMITS_ITEM_SECTION=session_limits
SESSION_LIMITS_GLOBAL_SECTION=global

USAGE(){
	echo "Uage: session_limits.sh start | stop | restart | reload"
	echo ""
	echo "For example: "
	echo "	session_limits.sh restart"
}

local session_limits_enabled_rule_num=0
get_enabled_rule_num(){
	config_get status $1 status
	if [  "${status}" == "on" ];then
		let session_limits_enabled_rule_num++
	fi
}
get_session_limits_num()
{
	config_load session_limits
	config_foreach  get_enabled_rule_num session_limits
}

get_global_status(){
	config_get global_status $1 status
	echo "in get_global_status global_status=${global_status}"
}
do_start(){
	echo "Entering do_start ....."
	echo "section = ${1} "		
	config_get status $1 status
	config_get max_conn $1 max_conn
	config_get name $1 name
	config_get ipgroup $1 ipgroup	
	#echo "name = ${name} "
	#echo "ipgroup = ${ipgroup} "	
	#echo "max_conn = ${max_conn} "
	#echo "status = ${status} "	
	
	if [ "on" = ${status} ]
	then 
		if [ "IPGROUP_ANY" = ${ipgroup} ]
		then 
			iptables -w -A forward_session_limits -s 0.0.0.0/0 -m tpconnlimit --tpconnlimit-above ${max_conn} -j REJECT		
		else 
			iptables -w -A forward_session_limits -m set --match-set ${ipgroup} src -m tpconnlimit --tpconnlimit-above ${max_conn} -j REJECT
		fi 		
		
	else
		echo "rule status is \"off\" Nothing to do."
	fi 
	
}


do_stop(){
	echo "Entering do_stop ....."
	#echo "section = ${1} "		
	config_get status $1 status
	config_get max_conn $1 max_conn
	config_get name $1 name
	config_get ipgroup $1 ipgroup	
	#echo "name = ${name} "
	#echo "ipgroup = ${ipgroup} "	
	#echo "max_conn = ${max_conn} "
	#echo "status = ${status} "	
	
	if [ "on" = ${status} ]
	then 
		if [ "IPGROUP_ANY" = ${ipgroup} ]
		then 
			iptables -w -D forward_session_limits -s 0.0.0.0/0 -m tpconnlimit --tpconnlimit-above ${max_conn} -j REJECT
		else 
			iptables -w -D forward_session_limits -m set --match-set ${ipgroup} src -m tpconnlimit --tpconnlimit-above ${max_conn} -j REJECT
		fi 
	else
		echo "rule status is \"off\" Nothing to do."
	fi 
	
}


if [ $# -eq 1  ]
then	
	
	global_status="off"
	
	config_load ${UCI_SESSION_LIMITS_CONFIG_FILE}	

	config_foreach get_global_status ${SESSION_LIMITS_GLOBAL_SECTION}
	
	get_session_limits_num
	if [ ${global_status} = "on" -a ${session_limits_enabled_rule_num} -gt 0 ];then
	{
		echo "session_limits_enabled_rule_num = ${session_limits_enabled_rule_num},insmod xt_tpconnlimit" > /dev/console
		insmod xt_tpconnlimit
	}
	else 
	{                 
		echo "session_limits_enabled_rule_num = ${session_limits_enabled_rule_num},rmmod xt_tpconnlimit" > /dev/console
		[ -d /sys/module/xt_tpconnlimit ] && rmmod xt_tpconnlimit
	}
	fi
	
	case $1 in 
	"start" )
		
		if [ "on" = ${global_status} ]
		then 
			#ipset create ippool1 bitmap:ip range 192.168.0.0/24
			#ipset add ippool1 192.168.0.100/32
			config_foreach do_start ${SESSION_LIMITS_ITEM_SECTION}
		else 
			echo "global status is \"off\" Nothing to do."
		fi 	
		;;
	"stop" )	
		
		if [ "on" = ${global_status} ]
		then 
			config_foreach do_stop ${SESSION_LIMITS_ITEM_SECTION}
		else 
			echo "global status is \"off\" Nothing to do."
		fi 			
		;;
		
	"restart" )

		if [ "on" = ${global_status} ]
		then 
			config_foreach do_stop ${SESSION_LIMITS_ITEM_SECTION}
		else 
			echo "global status is \"off\" Nothing to do."
		fi 	
	
		if [ "on" = ${global_status} ]
		then 
			config_foreach do_start ${SESSION_LIMITS_ITEM_SECTION}
		else 
			echo "global status is \"off\" Nothing to do."
		fi 		
		;;
	"reload" )

		if [ "on" = ${global_status} ]
		then 
			config_foreach do_stop ${SESSION_LIMITS_ITEM_SECTION}
		else 
			echo "global status is \"off\" Nothing to do."
		fi 	

		if [ "on" = ${global_status} ]
		then 
			config_foreach do_start ${SESSION_LIMITS_ITEM_SECTION}
		else 
			echo "global status is \"off\" Nothing to do."
		fi 		
		;;
	*)
		echo "Nothing to do."
		exit 0
		;;
	esac	
else	
	USAGE
	exit 0
fi





