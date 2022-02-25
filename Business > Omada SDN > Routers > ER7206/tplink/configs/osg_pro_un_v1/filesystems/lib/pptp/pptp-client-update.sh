#!/bin/sh
#basic task of update is to kill previous pppd if it exists,and start a new pppd if enable is true
. /lib/pppox/pppox-default-variables.sh
. /lib/zone/zone_api.sh
. /lib/pptp/pptp-startup.sh
. /lib/pptp/pptp-ifdevice-info.sh

update_config(){
	local path=$1/config
	local username=$2
	local password=$3
	local pns=$4
	local workmode=$5
	local remotesubnet=$6
	local outif=$7
	local mppe=$8
	local enable=$9
	local local_network=${10}
	
	uci -c $path set ${pppox_configname}.@pnc[-1].username=$username
	uci -c ${path} set ${pppox_configname}.@pnc[-1].password=$password
	uci -c ${path} set ${pppox_configname}.@pnc[-1].pns=$pns
	uci -c ${path} set ${pppox_configname}.@pnc[-1].workmode=$workmode
	uci -c ${path} set ${pppox_configname}.@pnc[-1].remotesubnet="$remotesubnet"
	uci -c ${path} set ${pppox_configname}.@pnc[-1].outif=$outif
	uci -c ${path} set ${pppox_configname}.@pnc[-1].enable=$enable
	uci -c ${path} set ${pppox_configname}.@pnc[-1].local_network="$local_network"
	#when enable is '1',should start the client pppd
	#right now,code is not written
	uci -c ${path} commit ${pppox_configname}
	
	enable_mppe $mppe $path options.pptp
}

start_new_pppd(){
	local username=$1
	local password=$2
	local pns=$3
	local outif=$4
	local zonex=$outif
	local client_path=$5/config
	
	#local devices=$(zone_get_effect_devices $outif)
	outif=$(zone_get_effect_main_wan_ifaces $outif)
	pptp_set_ifdevice_info "${outif}"  "$(basename ${5})"
	local devices=$(zone_get_device_byif $outif)
	for i in $devices;do
		outif=$i
	done
	echo "outif=$outif"
	
	/usr/sbin/pppd nodetach \
	+ipv6 \
	nodefaultroute \
	usepeerdns \
	persist maxfail 0 \
	user $username password $password \
	ip-up-script /lib/netifd/ppp-up \
	ipv6-up-script /lib/netifd/ppp-up \
	ip-down-script /lib/netifd/ppp-down \
	ipv6-down-script /lib/netifd/ppp-down \
	plugin pptp.so \
	pptp_server $pns \
	file ${client_path}/options.pptp \
	zonex $zonex \
	tunnel-proto pptp \
	outif $outif &
}

#parameter follow this order:
#path previous_enable now_enable username password pns workmode remotesubnet outif mppe
client_update(){
	local path=$1
	local previous_enable=$2
	local enable=$3
	local username=$4
	local password=$5
	local pns=$6
	local workmode=$7
	local remotesubnet=$8
	local outif=$9
	local mppe=${10}
	local local_network=${11}
	
	# as client-delete.sh may need to access the old config first,so update_config need invoked only
	# after client-delete.sh
	if [ $previous_enable = 'off' -a $enable = 'off' ];then
		update_config $path $username $password $pns $workmode "$remotesubnet" $outif $mppe $enable "$local_network"
		return 0
	fi
	
	if [ $previous_enable = 'on' -a $enable = 'off' ];then
		/lib/pptp/pptp-client-delete.sh $path '0'
		update_config $path $username $password $pns $workmode "$remotesubnet" $outif $mppe $enable "$local_network"
		return 0
	fi
	
	if [ $previous_enable = 'on' -a $enable = 'on' ];then
		/lib/pptp/pptp-client-delete.sh $path '0'
		sleep 3
		echo "sleep 3" > /dev/console
		update_config $path $username $password $pns $workmode "$remotesubnet" $outif $mppe $enable "$local_network"
		start_new_pppd $username $password $pns $outif $path
		return 0
	fi
	
	if [ $previous_enable = 'off' -a $enable = 'on' ];then
		update_config $path $username $password $pns $workmode "$remotesubnet" $outif $mppe $enable "$local_network"
		start_new_pppd $username $password $pns $outif $path
		return 0
	fi
}

client_update $1 $2 $3 $4 $5 $6 $7 "$8" $9 ${10} "${11}"


