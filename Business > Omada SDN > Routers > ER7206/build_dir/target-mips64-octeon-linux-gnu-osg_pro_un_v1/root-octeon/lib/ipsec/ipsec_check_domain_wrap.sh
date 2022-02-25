#!/bin/sh 
#/etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file    ipsec_monitor_tunnel_wrap.sh 
# brief  ipsec模块启动的时候调用的脚本，目的是每个20s检测一下dns和接口变化情况。
# author   Yang xiaoqiang
# version  1.0.0
# date     08June15
# histry   arg 1.0.0, 15Jan16, Yang xiaoqiang, Create the file. 

INITIAL_STAGE_TIMEOUT=10
STABLE_STAGE_TIMEOUT=20

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
	
	#the first time to check domain maybe cost more time
	while [ 1 ]
	do
		waiting_next
		/lib/ipsec/ipsec_check_domain.sh
	done	
	flock -u 30
} 30>>/var/lock/ipsec_check_domain_wrap
	