#!/bin/sh 
#/etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file   radius_query 
# brief  
# author   Yang xiaoqiang
# version  1.0.0
# date     17Sep15
# histry   arg 1.0.0, 17Sep15, Yang xiaoqiang, Create the file. 

#radius_generate_config_file.sh server1 server2 dst_port psk radius_retries radius_timeout 
#		0 	shell name
#		1 	server1 ip
#		1.1 server1 id
#		2 	server2 ip
#		2.1 server2 id
#		3 	server binding port
#		4 	psk
#		5	radius_retries
#		6 	radius_timeout
USAGE(){
	echo "Uage: radius_generate_config_file.sh <bind_inf> <server1>  <server2>  <dst_port> <psk> <radius_retries> <radius_timeout>"
	echo ""	
	echo "For example: "
	echo "	./radius_generate_config_file.sh eth0 192.168.1.100 192.168.1.27 1812 tplink 3 10"
}

if [ $# -ne 7 ]
then	
	USAGE
	exit 0
fi 
	
local TARGET=/etc/radiusclient-ng/radiusclient_${1}.conf
	rm -rf ${TARGET}
	echo "# General settings" >${TARGET}
	echo "" >>${TARGET}
	echo "# specify which authentication comes first respectively which" >>${TARGET}
	echo "# authentication is used. possible values are: \"radius\" and \"local\"." >>${TARGET}
	echo "# if you specify \"radius,local\" then the RADIUS server is asked" >>${TARGET}
	echo "# first then the local one. if only one keyword is specified only" >>${TARGET}
	echo "# this server is asked." >>${TARGET}
	echo "auth_order	radius,local" >>${TARGET}
	echo "" >>${TARGET}
	echo "# maximum login tries a user has" >>${TARGET}
	echo "login_tries	4" >>${TARGET}
	echo "" >>${TARGET}
	echo "# timeout for all login tries" >>${TARGET}
	echo "# if this time is exceeded the user is kicked out" >>${TARGET}
	echo "login_timeout	60" >>${TARGET}
	echo "" >>${TARGET}
	echo "# name of the nologin file which when it exists disables logins." >>${TARGET}
	echo "# it may be extended by the ttyname which will result in" >>${TARGET}
	echo "# a terminal specific lock (e.g. /etc/nologin.ttyS2 will disable" >>${TARGET}
	echo "# logins on /dev/ttyS2)" >>${TARGET}
	echo "nologin /etc/nologin" >>${TARGET}
	echo "" >>${TARGET}
	echo "# name of the issue file. it's only display when no username is passed" >>${TARGET}	
	echo "# on the radlogin command line" >>${TARGET}
	echo "issue	/etc/radiusclient-ng/issue" >>${TARGET}
	echo "" >>${TARGET}
	echo "# RADIUS settings" >>${TARGET}
	echo "" >>${TARGET}
	echo "# RADIUS server to use for authentication requests. this config" >>${TARGET}
	echo "# item can appear more then one time. if multiple servers are" >>${TARGET}
	echo "# defined they are tried in a round robin fashion if one" >>${TARGET}
	echo "# server is not answering." >>${TARGET}
	echo "# optionally you can specify a the port number on which is remote" >>${TARGET}
	echo "# RADIUS listens separated by a colon from the hostname. if" >>${TARGET}
	echo "# no port is specified /etc/services is consulted of the radius" >>${TARGET}
	echo "# service. if this fails also a compiled in default is used." >>${TARGET}
	echo "authserver 	${2}:${4}" >>${TARGET}
	echo "authserver 	${3}:${4}" >>${TARGET}
	echo "" >>${TARGET}
	echo "# RADIUS server to use for accouting requests. All that I" >>${TARGET}
	echo "# said for authserver applies, too. " >>${TARGET}
	echo "#" >>${TARGET}
	echo "acctserver 	localhost" >>${TARGET}
	echo "" >>${TARGET}
	echo "# file holding shared secrets used for the communication" >>${TARGET}
	echo "# between the RADIUS client and server" >>${TARGET}
	echo "servers		/etc/radiusclient-ng/servers" >>${TARGET}
	echo "" >>${TARGET}
	echo "# dictionary of allowed attributes and values" >>${TARGET}
	echo "# just like in the normal RADIUS distributions" >>${TARGET}
	echo "dictionary 	/etc/radiusclient-ng/dictionary" >>${TARGET}
	echo "" >>${TARGET}
	echo "# program to call for a RADIUS authenticated login" >>${TARGET}
	echo "login_radius	/usr/sbin/login.radius" >>${TARGET}
	echo "" >>${TARGET}
	echo "# file which holds sequence number for communication with the" >>${TARGET}
	echo "# RADIUS server" >>${TARGET}
	echo "seqfile		/var/run/radius.seq" >>${TARGET}
	echo "" >>${TARGET}
	echo "# file which specifies mapping between ttyname and NAS-Port attribute" >>${TARGET}
	echo "mapfile		/etc/radiusclient-ng/port-id-map" >>${TARGET}
	echo "" >>${TARGET}
	echo "# default authentication realm to append to all usernames if no" >>${TARGET}
	echo "# realm was explicitly specified by the user" >>${TARGET}
	echo "# the radiusd directly form Livingston doesnt use any realms, so leave" >>${TARGET}
	echo "# it blank then" >>${TARGET}
	echo "default_realm" >>${TARGET}
	echo "" >>${TARGET}
	echo "# time to wait for a reply from the RADIUS server" >>${TARGET}
	echo "radius_timeout	${7}" >>${TARGET}
	echo "" >>${TARGET}
	echo "# resend request this many times before trying the next server" >>${TARGET}
	echo "radius_retries	${6}" >>${TARGET}
	echo "" >>${TARGET}
	echo "# local address from which radius packets have to be sent" >>${TARGET}
	echo "bindaddr *" >>${TARGET}
	echo "" >>${TARGET}
	echo "# LOCAL settings" >>${TARGET}
	echo "" >>${TARGET}
	echo "# program to execute for local login" >>${TARGET}
	echo "# it must support the -f flag for preauthenticated login" >>${TARGET}
	echo "login_local	/bin/login" >>${TARGET}
	
	
TARGET=/etc/radiusclient-ng/servers	
	#判断文件是否存在，如果不存在，则创建一个。
	[ -e ${TARGET} ]
	if [ $? -ne 0 ]
	then 
		touch ${TARGET}	
		echo "${TARGET} don's exist"
	fi 
	#替换掉已经存在的server的psk,
	#先保留非server1,server2的条目，然后通过在末尾增加新条目，目的是为了防止已经存在了该条目，但是后面又增加了，使得文件越来越长。
	local cmd="'!(match(\$1,\"${2}\") || match(\$1,\"${3}\")) {print \$0 ;}' ${TARGET}"
	local remains=$(eval awk ${cmd})	
	rm -rf ${TARGET}_tmp
	touch ${TARGET}_tmp
	echo "${remains}" > ${TARGET}_tmp
	echo "${2}		${5}" >>${TARGET}_tmp
	echo "${3}		${5}" >>${TARGET}_tmp
	rm -rf  ${TARGET}
	mv  ${TARGET}_tmp  ${TARGET}



