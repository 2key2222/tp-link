#!/bin/sh 
#/etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file   radius_query 
# brief  
# author   Yang xiaoqiang
# version  1.0.0
# date     17Sep15
# histry   arg 1.0.0, 17Sep15, Yang xiaoqiang, Create the file. 

. /lib/functions.sh
# PAP认证方式：
#	命令		用户名		密码	PAP方式
#	radius_query fieldwork utcauto 	8
#CPAP认证方式
	#UCI_RADIUS_QUERY_RESULT=/etc/config/radius_query_result
	UCI_RADIUS_QUERY_RESULT=radius_query_result
	
	USAGE(){
		echo "Uage: radius_query.sh <User-Name> <Password> <Authentication-method> <binding_inf> <key>"		
		echo ""
		echo "Authentication-method: \"PAP\" or \"CHAP\""
		echo "For example: "
		echo "	./radius_query.sh fildwork ustc PAP eth0 12345678"
	}

	if [ $# -ne 5 ]
	then	
		USAGE
		exit 0
	fi 

	local radius_query_cmd
	if [ ${3} == "PAP" ]
	then 
		radius_query_cmd="NAS-Identifier=TP-LINK_7520_NAS"
	elif [ ${3} == "CHAP" ]
	then 
		radius_query_cmd="Framed-Protocol=1 Service-Type=2 NAS-Identifier=TP-LINK_7520_NAS"
	else 
		USAGE
		exit 0
	fi 
	
	
	#首先要确保/etc/config/${UCI_RADIUS_QUERY_RESULT}文件存在，否则uci不工作.
	if [ ! -e /etc/config/${UCI_RADIUS_QUERY_RESULT} ]
	then 
		#echo "/etc/config/${UCI_RADIUS_QUERY_RESULT} doesn't exist , create it."
		touch /etc/config/${UCI_RADIUS_QUERY_RESULT}	
	#else 
		#echo "/etc/config/${UCI_RADIUS_QUERY_RESULT} exist,pass."
	fi 
	
	if [ $? -eq 1 ] 
	then 
		#如果创建文件失败，直接返回.
		return 
	fi 
	
	#由于不同的binding_inf会使用相同的用户名来认证，因此为了区分，引入binding_inf变量
	# omada的binding_inf为eth0.1，带.号，不符合uci规范
	local key=${5}
	#先查询是否存在该记录
	local status=$(uci get ${UCI_RADIUS_QUERY_RESULT}.${key}.status)	
	test "${status}" 
	
	if [ $? -eq 1 ] 
	then 			
		#创建一个新的类型为RADIUS_QUERY的section,名字叫做${key},它有一个option，名字叫做status,值为"waiting",另外一个option是timeout,默认值为空，该值无意义，仅仅是占位。
		uci set ${UCI_RADIUS_QUERY_RESULT}.${key}="RADIUS_QUERY" 
		uci set ${UCI_RADIUS_QUERY_RESULT}.${key}."status"="waiting"
		uci set ${UCI_RADIUS_QUERY_RESULT}.${key}."timeout"=""
		uci commit ${UCI_RADIUS_QUERY_RESULT} 
	#else 
		#echo "\"${key}\" has an status"	
	fi 		 
	
	# 新增2>&1
	local ret=$(radiusclient -f /etc/radiusclient-ng/radiusclient_${4}.conf User-Name=${1} Password=${2} ${radius_query_cmd} 2>&1)
	#echo "radiusclient -f /etc/radiusclient-ng/radiusclient_${4}.conf User-Name=${1} Password=${2} ${radius_query_cmd}  ${ret}" > /dev/console
	test "${ret}" 
	if [ $? -eq 1 ] 
	then 
		echo "Authentication failure"
		uci set ${UCI_RADIUS_QUERY_RESULT}.${key}."status"="fail" 	
	else 		
		#uci set ${UCI_RADIUS_QUERY_RESULT}.${key}."status"="success"		
		local cmd_Session_Timeout_start="'BEGIN {match(\"${ret}\",\"Session-Timeout                  =\");print RSTART}'"	
		local ret_Session_Timeout_start=$(eval awk ${cmd_Session_Timeout_start})
		
		local cmd_Session_Timeout_length="'BEGIN {match(\"${ret}\",\"Session-Timeout                  =\");print RLENGTH}'"	
		local ret_Session_Timeout_length=$(eval awk ${cmd_Session_Timeout_length})
		#echo "${ret}"
		#echo "${ret_Session_Timeout_start}"
		#echo "${ret_Session_Timeout_length}"
		
		test "${ret_Session_Timeout_start}" 
		if [ $? -ne 1 -a ${ret_Session_Timeout_length} -ne -1 ]
		then 
			#如果返回值有该值
			local Session_Timeout_val_pos_start=${ret_Session_Timeout_start}+${ret_Session_Timeout_length}+1
			#echo ${Session_Timeout_val_pos_start}
			
			local cmd_Session_Timeout_remain="'BEGIN {print substr(\"${ret}\",${Session_Timeout_val_pos_start});}'"
			local ret_Session_Timeout_remain=$(eval awk ${cmd_Session_Timeout_remain})	
			#echo "remain=${ret_Session_Timeout_remain}"
			
			local cmd_Session_Timeout_end="'BEGIN {match(\"${ret_Session_Timeout_remain}\",\" \");print RSTART}'"
			local ret_Session_Timeout_end=$(eval awk ${cmd_Session_Timeout_end})	
		
			local cmd_Session_Timeout_val
			local ret_Session_Timeout_val
			
			#ret_Session_Timeout_end的值表示了是否是最后一项，如果是最后一项，则返回0(表示没有找到),否则返回至少1表示开始的位置.
			if [ ${ret_Session_Timeout_end} -ne 0 ]
			then 
				#echo "Not last entry"				
				cmd_Session_Timeout_val="'BEGIN {print substr(\"${ret_Session_Timeout_remain}\",1,${ret_Session_Timeout_end}-1);}'"	
			else 
				#表示Session-Timeout是最后一项.
				cmd_Session_Timeout_val="'BEGIN {print substr(\"${ret_Session_Timeout_remain}\",1);}'"	
				#echo "last entry"
			fi 
			ret_Session_Timeout_val=$(eval awk ${cmd_Session_Timeout_val})	

	
			uci set ${UCI_RADIUS_QUERY_RESULT}.${key}."timeout"="${ret_Session_Timeout_val}"	
			echo "Authentication success with Session-Timeout=${ret_Session_Timeout_val}."			
		else 
			echo "Authentication success without Session-Timeout."
		fi 
		uci set ${UCI_RADIUS_QUERY_RESULT}.${key}."status"="success"
	fi
	
	uci commit ${UCI_RADIUS_QUERY_RESULT}
	








