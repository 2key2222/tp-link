#!/bin/sh 
#/etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file    radius_check_result.sh 
# brief   read the result from /etc/config/radius_query_result file 
# author   Yang xiaoqiang
# version  1.0.0
# date     17Sep15
# histry   arg 1.0.0, 17Sep15, Yang xiaoqiang, Create the file. 

. /lib/functions.sh
	USAGE(){
		echo "Uage: radius_check_result.sh <user_name>"
		echo ""	
		echo "For example: "
		echo "	./radius_check_result.sh fildwork"
	}

	if [ $# -ne 1 ]
	then	
		#USAGE
		exit 0
	fi 

	#UCI_RADIUS_QUERY_RESULT=/etc/config/radius_query_result
	UCI_RADIUS_QUERY_RESULT=radius_query_result	

	#查询是否存在该记录
	local status=$(uci get ${UCI_RADIUS_QUERY_RESULT}.${1}.status)	
	test "${status}" 
	
	if [ $? -eq 1 ] 
	then 		
		echo ""
	else 
		if [ ${status} == "success" ]
		then 
			local timeout=$(uci get ${UCI_RADIUS_QUERY_RESULT}.${1}.timeout)
			if [ $? -eq 1 ]
			then 
				echo "{status=\"${status}\",timeout=600}"
			else 
				if echo ${timeout} | egrep -q '^[0-9]+$'; then
					echo "{status=\"${status}\",timeout=${timeout}}"
				else
					echo "{status=\"${status}\",timeout=600}"
				fi
			fi 
		else
			echo "{status=\"${status}\"}"
		fi 
			#只要是确定了状态的，都顺手删除掉。
		if [ ${status} == "success" -o ${status} == "fail" ]
		then 
			uci delete ${UCI_RADIUS_QUERY_RESULT}.${1}
			uci commit ${UCI_RADIUS_QUERY_RESULT}
		fi 		
	fi 	
