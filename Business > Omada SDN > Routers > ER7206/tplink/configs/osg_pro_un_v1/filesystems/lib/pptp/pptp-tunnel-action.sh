#!/bin/sh
. /lib/pppox/pppox-default-variables.sh
. /lib/functions.sh
. /lib/zone/zone_api.sh

#brief: server need to kill the pppd & client need to restart pppd in 5s
filepath=${pppox_ppppath}/pid

terminate_server(){
	local pid=$1
	local config=$(uci -c $filepath get $pid.@info[0].configpath)  #no conifg
	local username=$(uci -c $filepath get $pid.@info[0].username)
	local dev=$(uci -c $filepath get $pid.@info[0].ifname)
	local IPREMOTE=$(uci -c $filepath get $pid.@info[0].remoteip)
	
	local if_file=$config/config/${pppox_if_config}
	config_load $if_file
	config_get netmode $username "netmode"
	config_get remotesubnet $username "remotesubnet"
	config_get workmode $username "workmode"
	
	if [ ${netmode} = "client2lan" -o ${netmode} = "pc2lan" ]; then
				route del -host ${IPREMOTE} dev ${dev}
	else
				#route del -net ${remotesubnet} dev ${dev}
				for subnet in ${remotesubnet}; do
					route del -net ${subnet} dev ${dev}
				done
	fi
	#just kill pppd,then pptpctrl will catch SIG_CHILD then quit itself
	kill -TERM $pid
	rm -f $filepath/$pid
}

terminate_client(){
	local pid=$1
	local config=$(uci -c $filepath get $pid.@info[0].configpath)  #path is like /tmp/pptp/client/client0
	local dev=$(uci -c $filepath get $pid.@info[0].ifname)
	local username=$(uci -c $config/config get ${pppox_configname}.@pnc[0].username)
	local password=$(uci -c $config/config get ${pppox_configname}.@pnc[0].password)
	local pns=$(uci -c $config/config get ${pppox_configname}.@pnc[0].pns)
	local outif=$(uci -c $config/config get ${pppox_configname}.@pnc[0].outif)
	local remotesubnet=$(uci -c $config/config get ${pppox_configname}.@pnc[0].remotesubnet)
	local workmode=$(uci -c $config/config get ${pppox_configname}.@pnc[0].workmode)
	
	local if_file=$config/config
	
	#echo "username:$username"
	#echo "password:$password"
	#route del -net ${remotesubnet} dev ${dev};
	#[ ${workmode} = "nat" ] && fw del 4 nat POSTROUTING MASQUERADE  $ { -o ${dev} }
	#kill & start in 5s
	kill -9 $(cat $config/config/mgrfather)
	if_file=$config/config/mgr
	kill -9 $(cat $if_file)
	kill -TERM $pid
	rm -f $config/config/mgrfather
	rm -f $config/config/mgr
	rm -f $config/config/ppp
	rm -f $filepath/$pid
	sleep  3
	
	#local devices=$(zone_get_effect_devices $outif)
	local zonex=$outif
	outif=$(zone_get_effect_ifaces $outif)
	local devices=$(zone_get_device_byif $outif)
	for i in $devices;do
		outif=$i
	done
	echo "outif=$outif"
	#start pppd
	/usr/sbin/pppd nodetach  \
	+ipv6 \
	nodefaultroute \
	usepeerdns \
	persist maxfail 0 \
	user $username password $password \
	ip-up-script /lib/netifd/ppp-up \
	ipv6-up-script /lib/netifd/ppp-up \
	ip-down-script /lib/netifd/ppp-down \
	ipv6-down-script /lib/netifd/ppp-down \
	plugin pptp.so	\
	pptp_server $pns \
	file ${config}/config/options.pptp \
	zonex $zonex \
	tunnel-proto pptp \
	outif $outif &
}

#usage,$1 indicate server(1) or client(0),$2 indicates the pid of pppd
terminate(){
	[ $# -ne 2 ] && return 1
	if [ $1 = '1' ];then
		echo 'server'
		terminate_server $2
	elif [ $1 = '0' ];then
		echo 'client'
		terminate_client $2
	else
		echo 'error'
		return 1
	fi
}

terminate $1 $2
