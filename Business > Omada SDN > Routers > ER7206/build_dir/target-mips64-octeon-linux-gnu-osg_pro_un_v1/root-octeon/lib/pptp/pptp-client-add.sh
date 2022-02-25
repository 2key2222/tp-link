#!/bin/sh
#author luopei
. /lib/pppox/pppox-default-variables.sh
. /lib/zone/zone_api.sh
. /lib/pptp/pptp-option.sh
. /lib/pppox/pppox-header.sh
. /lib/pptp/pptp-ifdevice-info.sh

#usage client_add confname username password pns workmode remotesubnet outif enable mppe
#strictly follow this order ,total 9 parameters
client_add(){
	local confname=$1
	local username=$2
	local password=$3
	local pns=$4
	local workmode=$5
	local remotesubnet=$6
	local outif=$7
	local enable=$8
	local mppe=$9
	local ifname=${10}
	local local_network=${11}
	
	local path=${pppox_pptp_client_path}/${confname}/config
	mkdir -p $path
	touch ${path}/${pppox_configname}
	uci -c ${path} add ${pppox_configname} pnc
	uci -c ${path} set ${pppox_configname}.@pnc[-1].username=$username
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
	touch ${path}/${pppox_pptptype}.type
	touch ${path}/options.pptp

	echo -e $client_options >>${path}/options.pptp
	# add client, read lcp_echo from global settings
	local lcp_echo=$(uci get pptp-client-global.@global[-1].lcpechointerval)
	sed -r -i "/lcp-echo-interval/s/[[:digit:]]+/$lcp_echo/" $path/options.pptp
	if [ $mppe = '1' ];then
		sed -i 's/^noccp/#&/' ${path}/options.pptp
		sed -i 's/^#mppe/mppe/' ${path}/options.pptp
	else
		sed -i 's/^#noccp/noccp/' ${path}/options.pptp
		sed -i 's/^mppe required,stateless/#&/' ${path}/options.pptp
	fi
	echo "path $(dirname $path)" >>${path}/options.pptp
	echo "ifname ${pptp_header}${ifname}" >>${path}/options.pptp
	
	#local devices=$(zone_get_effect_devices $outif)
	outif=$(zone_get_effect_main_wan_ifaces $outif)
	local devices=$(zone_get_device_byif $outif)
	for i in $devices;do
		outif=$i
	done
	echo "outif=$outif"
	[ $enable = '1' -o $enable = "on" ] && client_start_pppd $username $password $pns $outif $path
}

client_add $1 $2 $3 $4 $5 "$6" $7 $8 $9 ${10} "${11}"
