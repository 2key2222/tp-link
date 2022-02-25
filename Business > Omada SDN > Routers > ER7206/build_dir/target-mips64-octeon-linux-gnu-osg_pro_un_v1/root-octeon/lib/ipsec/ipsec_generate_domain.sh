#!/bin/sh 
#/etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file    ipsec_generate_domain.sh 
# brief   generate uci file : /etc/config/ipsec_check_dns from /etc/config/ipsec and /etc/config/ipsec_secrets
#		which be checked by ipsec_check_domain.sh 
# author   Yang xiaoqiang
# version  1.0.0
# date     08June15
# histry   arg 1.0.0, 16July15, Yang xiaoqiang, Create the file. 


. /lib/functions.sh
. /lib/functions/network.sh
. /lib/zone/zone_api.sh
include /lib/network

UCI_DEFAULT_SEARCH_DIR=/etc/config
UCI_IPSEC_SEARCH_DIR=/var/config
UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE=ipsec_check_dns
UCI_IPSEC_CONFIG_FILE=ipsec
UCI_AUTHENTICATION_CONFIG_FILE=ipsec_secrets
IPSEC_SECTION=connection
AUTHENTICATION_SECTION=authentication
#该section名字是ipsec_check_dns文件的config 字段的名字.
CHECKED_DOMAIN_SECTION=domain

generate_from_uci_ipsec(){
	#${0}: shell name
	#${1}: section name 
	#${2}: input file
	#${3}: output file	
	#${4}: the connection name which only generated from.
	let ignore_dns_resovle=0
	config_get name $1 name
	#echo "Checking ${IPSEC_SECTION} section: ${name}."
	test $4
	if [ $? -ne 1 ]
	then
		if [ ${name} != $4 ]
		then 
			#echo "connection name is not equal.\"${name}\" !=  \"$4\""
			return 
		fi 
		let ignore_dns_resovle=1
	#else 
	#	echo "\$4 doesn't exit"
	fi 
	 
	config_get local_binding_type $1 local_binding_type	
	if [ ${local_binding_type} = "domain_name"  -o  ${local_binding_type} = "if_name" ]
	then 
		#echo "Local_binding is a domain name ,add to the file." 		
		config_get local_binding $1 local_binding		
		echo "" >> ${3}
		echo "config domain" >> ${3}		
		echo "	option domain_name '${local_binding}'" >> ${3}		
		echo "	#1: DOMAIN_NORMAL,2: DOMAIN_SPECIAL" >> ${3}	
		
		local old_ipaddr=""
		if [ ${local_binding_type} = "domain_name" ]
		then 
			echo "	option domain_type '1'" >> ${3}	
			
			if [ ${ignore_dns_resovle} -eq 0 ]
			then 
				old_ipaddr=$(dnsq ${local_binding} ${domain_name} )
			else 
				echo "ignore_dns_resovle is ${ignore_dns_resovle},ignore it !"
				old_ipaddr="xx.xx.xx.xx"
			fi 			
			if [ ${old_ipaddr} = "0.0.0.0" ]
			then 
				old_ipaddr=""
			fi 
			
		else
			echo "	option domain_type '2'" >> ${3}			
			local effect_iface=$(zone_get_effect_main_wan_ifaces ${local_binding})
			network_get_ipaddr old_ipaddr ${effect_iface}				
		fi 

		echo "	option binding_file '${2}'" >> ${3}		
		echo "	option binding_section_type '${IPSEC_SECTION}'" >> ${3}
		echo "	option binding_item  '${name}'" >> ${3}
		echo "	option binding_field  'local_binding'" >> ${3}	
		#因为dnsq查询的时候需要指定从那个接口发送出去，即：该域名所属的隧道条目的本地绑定的接口名称，因此需要多加一个参数，其它地方没有用到，一下同�?	
                echo "	option tunnel_local_binding  '${local_binding}'" >> ${3}
		test "${old_ipaddr}" 
		if [ $? -eq 1 ]	
		then 
			echo "	option old_ipaddr	'xx.xx.xx.xx'" >> ${3}	
		else 
			echo "	option old_ipaddr	'${old_ipaddr}'" >> ${3}	
		fi 	
			
	fi 		
	
	config_get remote_peer_type $1 remote_peer_type
	if [ ${remote_peer_type} = "domain_name"  -o  ${remote_peer_type} = "if_name" ]
	then 
		echo "Remote peer is a ${remote_peer_type} ,add to the file." 		
		config_get remote_peer $1 remote_peer
		config_get local_binding $1 local_binding	
		echo "" >> ${3}
		echo "config domain" >> ${3}		
		echo "	option domain_name '${remote_peer}'" >> ${3}		
		echo "	#1: DOMAIN_NORMAL,2: DOMAIN_SPECIAL" >> ${3}
		local old_ipaddr=""
		if [ ${remote_peer_type} = "domain_name" ] 
		then 
			echo "	option domain_type '1'" >> ${3}
			if [ ${ignore_dns_resovle} -eq 0 ]
			then 
				old_ipaddr=$(dnsq ${local_binding} ${remote_peer} )
			else 
				
				old_ipaddr="xx.xx.xx.xx"
			fi 						
			
		else 
			echo "	option domain_type '2'" >> ${3}
			local effect_iface=$(zone_get_effect_main_wan_ifaces ${remote_peer})
			network_get_ipaddr old_ipaddr ${effect_iface}
		fi
		echo "	option binding_file '${2}'" >> ${3}		
		echo "	option binding_section_type '${IPSEC_SECTION}'" >> ${3}
		echo "	option binding_item  '${name}'" >> ${3}
		echo "	option binding_field  'remote_peer'" >> ${3}		
		echo "	option tunnel_local_binding  '${local_binding}'" >> ${3}	
		test "${old_ipaddr}" 
		if [ $? -eq 1 ]	
		then 
			echo "	option old_ipaddr	'xx.xx.xx.xx'" >> ${3}	
		else 
			echo "	option old_ipaddr	'${old_ipaddr}'" >> ${3}	
		fi 	
			
	fi
		
}
generate_from_uci_ipsec_secrets(){
	#${0}: shell name
	#${1}: section name 
	#${2}: input file
	#${3}: output file
	#${4}: the connection name which only generated from.
	
	let ignore_dns_resovle=0
	config_get name $1 name
	test $4
	if [ $? -ne 1 ]
	then
		if [ ${name} != $4 ]
		then 
			#echo "connection name is not equal.\"${name}\" !=  \"$4\""
			return 
		fi 
		let ignore_dns_resovle=1
	#else 
	#	echo "\$4 doesn't exit"
	fi 
	
	#echo "Checking ${AUTHENTICATION_SECTION} section: ${name}."
	config_get local_id_type $1 local_id_type
	if [ ${local_id_type} = "IP_ADDRESS_FROM_DNSNAME" -o ${local_id_type} = "IP_ADDRESS_FROM_IFNAME" ]
	then 
		config_get local_id_value $1 local_id_value
		#echo "local_id  is a domain name ,add to the file." 		
		echo "" >> ${3}
		echo "config domain" >> ${3}		
		echo "	option domain_name '${local_id_value}'" >> ${3}		
		echo "	#1: DOMAIN_NORMAL,2: DOMAIN_SPECIAL" >> ${3}	
		
		local old_ipaddr=""
		if [ ${local_id_type} = "IP_ADDRESS_FROM_DNSNAME" ]
		then 
			echo "	option domain_type '1'" >> ${3}	
			if [ ${ignore_dns_resovle} -eq 0 ]
			then 
				old_ipaddr=$(dnsq ${local_id_value} ${local_id_value} )	
			else
				old_ipaddr="xx.xx.xx.xx"
			fi
		else 
			echo "	option domain_type '2'" >> ${3}	
			local effect_iface=$(zone_get_effect_main_wan_ifaces ${local_id_value})
			network_get_ipaddr old_ipaddr ${effect_iface}	
		fi 
		echo "	option binding_file '${2}'" >> ${3}		
		echo "	option binding_section_type '${AUTHENTICATION_SECTION}'" >> ${3}
		echo "	option binding_item  '${name}'" >> ${3}
		echo "	option binding_field  'local_id_value'" >> ${3}				
		echo "	option tunnel_local_binding  '${local_id_value}'" >> ${3}
		test "${old_ipaddr}" 
		if [ $? -eq 1 ]	
		then 
			echo "	option old_ipaddr	'xx.xx.xx.xx'" >> ${3}	
		else 
			echo "	option old_ipaddr	'${old_ipaddr}'" >> ${3}	
		fi 	
			
	fi 	
	
	config_get remote_id_type $1 remote_id_type
	if [ ${remote_id_type} = "IP_ADDRESS_FROM_DNSNAME"  -o  ${remote_id_type} = "IP_ADDRESS_FROM_IFNAME" ]
	then 	
		echo "remote_id  is a domain name ,add to the file." 	
		config_get remote_id_value $1 remote_id_value
		config_get local_id_value $1 local_id_value
		echo "" >> ${3}
		echo "config domain" >> ${3}		
		echo "	option domain_name '${remote_id_value}'" >> ${3}		
		echo "	#1: DOMAIN_NORMAL,2: DOMAIN_SPECIAL" >> ${3}
	
		
		local old_ipaddr=""		
		if [ ${remote_id_type} = "IP_ADDRESS_FROM_DNSNAME" ]
		then 
			echo "	option domain_type '1'" >> ${3}
			if [ ${ignore_dns_resovle} -eq 0 ]
			then 
				old_ipaddr=$(dnsq ${local_id_value} ${remote_id_value} )
			else
				
				old_ipaddr="xx.xx.xx.xx"
			fi 
		else
			echo "	option domain_type '2'" >> ${3}			
			local effect_iface=$(zone_get_effect_main_wan_ifaces ${remote_id_value})
			network_get_ipaddr old_ipaddr ${effect_iface}				
		fi 
		echo "	option binding_file '${2}'" >> ${3}		
		echo "	option binding_section_type '${AUTHENTICATION_SECTION}'" >> ${3}
		echo "	option binding_item  '${name}'" >> ${3}
		echo "	option binding_field  'remote_id_value'" >> ${3}		
		echo "	option tunnel_local_binding  '${local_id_value}'" >> ${3}		
		
		test "${old_ipaddr}" 
		if [ $? -eq 1 ]	
		then 
			echo "	option old_ipaddr	'xx.xx.xx.xx'" >> ${3}	
		else 
			echo "	option old_ipaddr	'${old_ipaddr}'" >> ${3}	
		fi	
	fi 	

		
}


delete_from_checked_file(){
	#${0}: shell name
	#${1}: section name 
	#${2}: the connection name which will be deleted.
	#${3}: count 
	config_get binding_item $1 binding_item
	
	
	test $2
	if [ $? -eq 1 ]
	then 
		#echo "\"$2\" doesn't exit."
		return 
	elif [ ${binding_item} != $2 ]
	then	
		#echo "\"$2\" vs ${binding_item} let it go ."
		return 
	else 	
		#echo "\"$2\" vs ${binding_item} delete it=$1."
		uci delete ${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}."${1}"	
	fi 
	
}

USAGE(){
	echo "Uage: ipsec_generate_domain.sh <commands> [connection_name]"
	echo ""
	echo "Commands:"
	echo "	renew ---- rebuild all the domain to \"ipsec_check_dns\" from scratch, and it will ignore the [connection_name]."
	echo "	 add  ---- only add the domain of connection [connection_name] to the \"ipsec_check_dns\". "
	echo "	 del  ---- only del the domain of connection [connection_name] from the \"ipsec_check_dns\". "
	echo "	 lock ---- lock the whole \"ipsec_check_dns\" file."
	echo "	 unlock ---- unlock the whole \"ipsec_check_dns\" file."
	echo "For example: "
	echo "	./ipsec_generate_domain.sh renew "
	echo "	./ipsec_generate_domain.sh add u_s_t_c "
	echo "	./ipsec_generate_domain.sh del tunnel_1 "
	
}


if [ $# -le 0 ]
then	
	USAGE
	exit 0
else	
	if [ $1 = "renew" ]
	then	
		test "${2}" 
		if [ $? -ne 1 ]	
		then 
			echo "Invalid command."
			USAGE	
			exit 0
		fi		
			
	elif [ $1 = "add" ]
	then 
		test "${2}" 
		if [ $? -eq 1 ]	
		then 
			echo "Invalid command."
			USAGE	
			exit 0
		fi		
		test "${3}" 
		if [ $? -ne 1 ]	
		then 
			echo "Invalid command."
			USAGE	
			exit 0
		fi	
		
	elif [ $1 = "del" ]
	then 
		test "${2}" 
		if [ $? -eq 1 ]	
		then 
			echo "Invalid command."
			USAGE	
			exit 0
		fi		
		test "${3}" 
		if [ $? -ne 1 ]	
		then 
			echo "Invalid command."
			USAGE	
			exit 0
		fi		
	elif [ $1 = "lock" ]		
	then 
		test "${2}" 
		if [ $? -ne 1 ]	
		then 
			echo "Invalid command."
			USAGE	
			exit 0
		fi	
	elif [ $1 = "unlock" ]
	then 
		test "${2}" 
		if [ $? -ne 1 ]	
		then 
			echo "Invalid command."
			USAGE	
			exit 0
		fi	
	else 
		echo "command \"$1\" not surported."
		USAGE
		exit 0		
	fi	
fi


if [ $1 = "renew" ]
then
	{
		flock -x 30
    	[ $? -eq 1 ] && {  echo "ipsec_generate_domain.sh get lock(/var/lock/ipsec_dnsq) fail.";  exit 1; } 

		echo "#this file record the domain name will be checked by /usr/sbin/tmngtd periodically." > ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}	
		rm -rf ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}	
		
		#generate from /etc/config/ipsec 
		config_load ${UCI_IPSEC_CONFIG_FILE}
		config_foreach generate_from_uci_ipsec ${IPSEC_SECTION} ${UCI_IPSEC_CONFIG_FILE} ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}	
		
		#don't need to add the items from secret to ipsec_check_dns -- chenxing
		#generate from /etc/config/ipsec_secrets  
		#config_load ${UCI_AUTHENTICATION_CONFIG_FILE}
		#config_foreach generate_from_uci_ipsec_secrets ${AUTHENTICATION_SECTION}  ${UCI_AUTHENTICATION_CONFIG_FILE} ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}
		flock -u 30	
} 30>>/var/lock/ipsec_dnsq	
elif [ $1 = "add" ]
then
	{
		flock -x 30
   		[ $? -eq 1 ] && {  echo "ipsec_generate_domain.sh get lock(/var/lock/ipsec_dnsq) fail.";  exit 1; } 

		#generate from /etc/config/ipsec 
		config_load ${UCI_IPSEC_CONFIG_FILE}
		config_foreach generate_from_uci_ipsec ${IPSEC_SECTION} ${UCI_IPSEC_CONFIG_FILE} ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE} $2
		#don't need to add the items from secret to ipsec_check_dns -- chenxing	
		#generate from /etc/config/ipsec_secrets 
		#config_load ${UCI_AUTHENTICATION_CONFIG_FILE}
		#config_foreach generate_from_uci_ipsec_secrets ${AUTHENTICATION_SECTION}  ${UCI_AUTHENTICATION_CONFIG_FILE} ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE} $2	
		flock -u 30			
	} 30>>/var/lock/ipsec_dnsq			
elif [ $1 = "del" ]
then
	{
		flock -x 30
   		[ $? -eq 1 ] && {  echo "ipsec_generate_domain.sh get lock(/var/lock/ipsec_dnsq) fail.";  exit 1; } 

		#delete from ${UCI_DEFAULT_SEARCH_DIR}/${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE} 
		config_load ${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}		
		config_foreach delete_from_checked_file ${CHECKED_DOMAIN_SECTION} $2	
		uci commit ${UCI_IPSEC_DOMAIN_TO_BE_CHECKED_FILE}
		flock -u 30
	} 30>>/var/lock/ipsec_dnsq	
elif [ $1 = "lock" ]
then 
	{
		flock -x 37
		echo "lock" > /tmp/lock/ipsec_web
		flock -u 37
	} 37>>/var/lock/ipsec_web_lock	
elif [ $1 = "unlock" ]
then 
	{
		flock -x 37
		echo "unlock" > /tmp/lock/ipsec_web
		flock -u 37
	} 37>>/var/lock/ipsec_web_lock	
else 
	echo "command \"$1\" not surported."
	USAGE
fi


