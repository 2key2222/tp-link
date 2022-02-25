#!/bin/sh 
#/etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file    ipsec_monitor_tunnel.sh 
# brief   called by /usr/sbin/tmngtd periodically, to check if should call 'ipsec reload' for every tunnel.
# 		  周期性执行的脚本，用于判断每个隧道是否处于预定状态，如果不处于，需要手动启动。目前的功能是：
#			1.判断一个auto=start的条目是否处于建立连接状态，需要永远保持发包，即使尽管对端不响应。
# author   Yang xiaoqiang
# version  1.0.0
# date     08June15
# histry   arg 1.0.0, 14July15, Yang xiaoqiang, Create the file. 
#		   arg 1.0.1, 14Dec30,Yang xiaoqiang ,let lua do the job ,and change the Algorithm.
IPSEC_WEB_LOCK=/tmp/lock/ipsec_web

INITIAL_STAGE_TIMEOUT=10
STABLE_STAGE_TIMEOUT=30

count_down=5


waiting_next()
{
	local timeout=$STABLE_STAGE_TIMEOUT
	if [[ "$count_down" -gt 0 ]]; then
		count_down=$((count_down-1))
		timeout=$INITIAL_STAGE_TIMEOUT
	fi
	for i in `seq $timeout`;do
		sleep 1
	done
}


{
	flock -x -w 5 30
	[ $? -eq 1 ] && {  exit 1;}

	while [ 1 ]
	do
		waiting_next
		{	
			flock -x -n 30	
			ipsec_web_lock=$(cat ${IPSEC_WEB_LOCK})
			if [ "${ipsec_web_lock}" = "unlock" ]
			then			
				lua /usr/lib/lua/ipsec/ipsec_monitor_tunnel.lua
			fi 
			flock -u 30
		} 30>>/var/lock/ipsec_dnsq
	done	
	flock -u 30
} 30>>/var/lock/ipsec_monitor
	
