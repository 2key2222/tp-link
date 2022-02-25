#!/bin/sh 
#/etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file    ipsec_check_domain.sh 
# brief   called by /usr/sbin/tmngtd periodically, and check if domain lists in ipsec_check_dns renew.
# 		   
# author   Yang xiaoqiang
# version  1.0.0
# date     08June15
# histry   arg 1.0.0, 14July15, Yang xiaoqiang, Create the file. 


. /lib/functions.sh
. /lib/functions/network.sh
. /lib/zone/zone_api.sh

include /lib/network

UCI_IPSEC_SEARCH_DIR=/var/config
UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE=ipsec_check_dns_tmp
UCI_IPSEC_DOMAIN_MAIN_FILE=ipsec_check_dns
UCI_DEFAULT_SEARCH_DIR=/etc/config
IPSEC_WEB_LOCK=/tmp/lock/ipsec_web
IPSEC_DOMAIN=/tmp/ipsec_domain_checklist
IPSEC_DOMAIN_TO_BE_CHECK_SECTION=domain
UCI_IPSEC_DNS_CHECKED_FILE=${UCI_IPSEC_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}
IPSEC_DNSQ_COUNT=/tmp/lock/ipsec_dnsq_count

local debug="off"
local re_transfer="false"

local main_file
local backup

MY_ECHO(){
	if [ ${debug} = "on" ]
	then 
		date=$(date)
		echo  "$date ${1}" >> /var/log/ipsec_check_domain.log
	fi 	
}


#本脚本主要是解析与域名有关的三个地方：config connection的local_binding和remote_peer以及config authentication的local/remote_id_value
#在做任何修改之后，都会调用ipsec stroke down connection[*]来断开所有的已建立的连接。
#本脚本起作用的前提是：/etc/config目录中存在一个ipsec_check_dns文件，该uci文件的格式如下：
#config domain
#    option domain_name    'www.qq.com'
	#1: DOMAIN_NORMAL,2: DOMAIN_SPECIAL
#	option domain_type 		'1'
#	ipsec 或者ipsec_secrets分别对应/etc/config/ipsec 以及/etc/config/ipsec_secrets文件
#	option binding_file 	'ipsec'
#	connection 或者authentication
#	option binding_section_type   'connection'
#	option binding_item	  'ipsec_policy'
#	local_binding 或者remote_peer或者local_id_value或者remote_id_value
#   option binding_field  'remote_peer'
#   option old_ipaddr		  '9.9.9.9'
	

check_domain(){
	
	config_get domain_name ${1}		domain_name
	config_get binding_file 		${1} 		binding_file
	config_get binding_section_type ${1} binding_section_type
	config_get binding_item  ${1} binding_item
	config_get binding_field ${1} binding_field
	config_get old_ipaddr  ${1} old_ipaddr
	config_get domain_type  ${1} domain_type
	config_get tunnel_local_binding  ${1} tunnel_local_binding	
	

	local ipaddr=""
	if [ ${domain_type} -eq 1 ]
	then
		#MY_ECHO "${domain_name} is a normal domain , let 'dnsq' program do it. "
		if [  ${old_ipaddr} = "xx.xx.xx.xx" ]
		then
			#echo "this is the first time to check the domain, must do it!" > /dev/console
			ipaddr=$(dnsq ${tunnel_local_binding} ${domain_name} )
		elif [ -n "${domain_checklist}" ]
		then
			if [ "${domain_checklist}" == "no_domain_need_check" ]
			then
				#echo "no domain need check" > /dev/console
				return
			fi
			local check_domain_name="{${domain_name}}"		
			local exist=`echo ${domain_checklist} | grep ${check_domain_name}`

			if [ -n "${exist}" ]
			then
				#echo "check ${domain_name}, because the tunnel is not OK" > /dev/console
				ipaddr=$(dnsq ${tunnel_local_binding} ${domain_name} )
			else 
				#echo "the tunnel is ok, don't need to check it!" > /dev/console
				return
			fi				
		fi
	elif [ ${domain_type} -eq 2 ]
	then 		
		local effect_iface=$(zone_get_effect_main_wan_ifaces ${domain_name})
		network_get_ipaddr ipaddr ${effect_iface}
	fi 
	
	test "${ipaddr}" 
	if [ $? -eq 1 ]
	then
		#MY_ECHO "${domain_name} resolved ip fail,let ${1} pass."
		ipaddr="xx.xx.xx.xx" 
	fi
	
	if [ ${ipaddr} = ${old_ipaddr} -o ${ipaddr} = "0.0.0.0" ]
	then 
		#echo "the ip address with ${domain_name} has no changed ,let ${1} go." > /dev/console
		return 
	fi 

	#echo "now find the IP of ${domain_name} changde, will down the connection and reload" > /dev/console
	#注意：config_set不生效，原因未知.2015.7.15

	#普通接口，一旦检测出地址有变立刻修改old_addr,并重新转换

	MY_ECHO "OK, let's record the new value in the file ${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}"
	uci_set ${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE} ${1} old_ipaddr ${ipaddr}
	#MY_ECHO "re_transfer=${re_transfer}"
	re_transfer="true"
	#uci_commit ${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}

	#uci -c ${UCI_DEFAULT_SEARCH_DIR}
	#config_load ${binding_file}
	MY_ECHO "the binding information of ${domain_name} is as follows:"
	MY_ECHO "	binding_file=${binding_file}"
	MY_ECHO "	binding_section_type=${binding_section_type} "	
	MY_ECHO "	binding_item=${binding_item} "		
	MY_ECHO "	binding_field=${binding_field} "
	MY_ECHO "	tunnel_local_binding=${tunnel_local_binding} "
	MY_ECHO "	old value=${old_ipaddr} "
	MY_ECHO "	new value=${ipaddr} "
	#由于/etc/config/ipsec和/etc/config/ipsec_secrets文件是最原始的文件，不能被修改，否则会出现信息丢失
	#config_foreach modify_field ${binding_section_type}	${binding_item} "${binding_field}" ${ipaddr} ${binding_file}
	#binding_item实际上就是某条隧道的名称，无论是/etc/config/ipsec还是/etc/config/ipsec_secrets的修改，都必须断掉该隧道的所有连接。
	if [ "${binding_section_type}" = "connection" ]
	then 
		#MY_ECHO  "Carrying out \"ipsec stroke down-nb ${binding_item}{*}\"  "
		#ipsec stroke down ${binding_item}
		ipsec stroke down-nb ${binding_item}
		ipsec stroke down-nb ${binding_item}[*]
		ipsec stroke down-nb ${binding_item}{*}
		#ipsec stroke purgeike
	fi
	return 
}



    test ${1}
	if [ $? -eq 0 ]
	then 
		debug=${1}
	fi 

			
{
    flock -x -n 30
    [ $? -eq 1 ] && { MY_ECHO "ipsec_dnsq.sh get lock fail."; exit 1;}        
   
	
	if [ -e ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE} ]
	then 
		#MY_ECHO "${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE} exist"
		MY_ECHO ""
	else
		#MY_ECHO "${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE} doesn't exist"
		touch ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}
	fi 
 
	#MY_ECHO "ipsec_check_domain get lock successfully."
	main_file=$(cat ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_MAIN_FILE})
	backup=$(cat ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE})
	
	if [ "${main_file}" != "${backup}" ]
	then
		#MY_ECHO "main_file and backup is not equal!"
		rm -rf ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}
		cp ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_MAIN_FILE}  ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}
	#else 
		#MY_ECHO "main_file and backup is equal!"
		
	fi 
	
	flock -u 30
	#MY_ECHO "ipsec_check_domain release lock successfully."
} 30>>/var/lock/ipsec_dnsq

	
#获取域名的检查列表
domain_checklist=$(cat ${IPSEC_DOMAIN})
#echo " cat: ${domain_checklist}" > /dev/console
#uci -c ${UCI_IPSEC_SEARCH_DIR}	show ${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}
config_load ${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}
config_foreach check_domain ${IPSEC_DOMAIN_TO_BE_CHECK_SECTION}


if [ "${re_transfer}" = "true" ] 
#需要转换，表示/etc/config/ipsec或者/etc/config/ipsec_secrets的某些域名已经得到了更新，因此需要重新生成
#/etc/ipsec.config 和/etc/ipsec.secrets.
then 
	uci_commit ${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}
	uci_commit ${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}
	#之所以需要再遍历一次，是因为如果n条条目有相同的dommain_name,但是如果第一次循环的时候，直到末尾才发现ip变化了，此时前面也有
	#类似的section需要转换，如果不重新遍历一次，下次发现前面的section需要转换，则会白做许多无用功。
	#对于200条条目引用了同样的local_binding和remote_peer这种类型，可以节约许多工作。		
	config_load ${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}
	config_foreach check_domain ${IPSEC_DOMAIN_TO_BE_CHECK_SECTION}
	#MY_ECHO "Update the ipsec_check_dns file.!"
	
	uci_commit ${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}
	uci_commit ${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}
	MY_ECHO "have committed the change , re-transfer the uci config "
	{	
		flock -x -n 30
		[ $? -eq 1 ] && { MY_ECHO "ipsec_dnsq.sh get lock fail."; exit 1;}        
		
		if [ -e ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE} ]
		then 
			#MY_ECHO "${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE} exist"
			MY_ECHO ""
		else
			#MY_ECHO "${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE} doesn't exist"
			touch ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}
		fi 
	 
		#MY_ECHO "ipsec_check_domain get lock successfully."
		#backup =$(cat ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_MAIN_FILE})
		backup=$(cat ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_MAIN_FILE})
		ipsec_web_lock=$(cat ${IPSEC_WEB_LOCK})
		#此处main_file已经存储有第一次读入的文件内容，相当于UCI_IPSEC_DOMAIN_MAIN_FILE的原始内容
		#再次读取UCI_IPSEC_DOMAIN_MAIN_FILE文件，确认在定时器查询期间没有进程改变了UCI_IPSEC_DOMAIN_MAIN_FILE的内容
		
		if [ "${main_file}" != "${backup}" -o "${ipsec_web_lock}" = "lock" ]
		then
			#主文件有改变或者有web操作在锁定lock,为了不冲突，此时不需要做任何事情，放弃本次查询结果.
			MY_ECHO "${UCI_IPSEC_DOMAIN_MAIN_FILE} has changed,quit!"				
		else 
			#MY_ECHO "${UCI_IPSEC_DOMAIN_MAIN_FILE} has not changed."
			rm -rf ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_MAIN_FILE}
			cp ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}  ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_MAIN_FILE}											
			lua  /usr/lib/lua/ipsec/ipsec_reload.lua
			#sleep 1
			MY_ECHO "Going to update strongswan!"
			ipsec rereadsecrets
			{
				sleep 1;ipsec update;
			}&					
		fi 						
		flock -u 30
		#MY_ECHO "ipsec_check_domain release lock successfully."
	} 30>>/var/lock/ipsec_dnsq	
	
fi 

	
