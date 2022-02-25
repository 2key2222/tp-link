#!/bin/sh

. /lib/pppox/pppox-default-variables.sh
. /lib/functions.sh
. /lib/pppox/pppox-functions.sh
. /lib/firewall/fw.sh
. /lib/zone/zone_api.sh
. /lib/pptp/pptp-option.sh
. /lib/pppox/pppox-header.sh
. /lib/pptp/pptp-ifdevice-info.sh
. /lib/pppox/pppox-remote-management.sh

path=""

client_path=""

fw_check() {
	local ret=$(iptables -w -t $1 -C $2 $3 2>&1)
	[ -n "$ret" ] && return 0||return 1
}

#$1:client=1 or server=0; $2:pptp-new value; $3 lcp-new value
update_global(){
	local pptppath=""
	local lcppath=""
	local option=""
	if [ $1 = '0' ];then
		pptppath=${pppox_pptp_server_path}/server-global
		lcppath=${pppox_pptp_server_path}
		option="options.pptpd"
	else
		pptppath=${pppox_pptp_client_path}/client-global
		lcppath=${pppox_pptp_client_path}
		option="options.pptp"
	fi
	echo $2 >$pptppath
	for dir in $(ls ${lcppath});do
		[ -d ${lcppath}/$dir ] && {
			local file=${lcppath}/${dir}/config/${option}
			echo $file
			sed -r -i "/lcp-echo-interval/s/[[:digit:]]+/$3/" $file
		}
	done
}

config_global(){  #read global
	local pptpinterval
	local lcpinterval
	
	config_get pptpinterval $1 pptphellointerval
	config_get lcpinterval  $1 lcpechointerval
	
	[ ! -e ${pppox_pptp_server_path} ] && mkdir -p ${pppox_pptp_server_path}
	echo $pptpinterval >${pppox_pptp_server_path}/server-global
	echo $lcpinterval
	
	sed -r -i "/lcp-echo-interval/s/[[:digit:]]+/$lcpinterval/" $path/options.pptpd
	
}

#s1 enable_mppe  $2:path  $3 file
enable_mppe(){
	if [ "$1" == "0" ];then
		sed -i 's/^#noccp/noccp/' $2/$3
		sed -i 's/^mppe required,stateless/#&/' $2/$3
	else
		sed -i 's/^noccp/#noccp/' $2/$3
		sed -i 's/^#mppe/mppe/' $2/$3
	fi
}


#s1 zone  $2:path  $3 file
zone_change(){
	sed -i '/^zonex*/d' $2/$3
	sed -i '$azonex '$1'' $2/$3
}

#$1 (1|0)
#$2 (interface or device)
enable_packet(){
	local local_service_chain=local_service_rule
	if [ "$1" == "0" -o $1 == "off" ];then
		#block the packet from $2
		echo "block"
		#interface=$(zone_get_effect_devices $2)
		local inter=$(zone_get_effect_main_wan_ifaces $2)
		interface=$(zone_get_device_byif $inter)
		for iface in $interface;do
			[ -n "$iface" -a "$iface" != "loopback" ] && {
				local rule="-i ${iface} -p tcp --dport 1723"
				fw_check "filter" "$local_service_chain" "$rule -j ACCEPT"
				[ x$? == x1 ] && fw del 4 f $local_service_chain ACCEPT $ { -i ${iface} -p tcp --dport 1723 }
			}
		done
		refresh_vpn_remote_management
	else
		echo "allow"
		#interface=$(zone_get_effect_devices $2)
		local inter=$(zone_get_effect_main_wan_ifaces $2)
		interface=$(zone_get_device_byif $inter)
		for iface in $interface;do
			[ -n "$iface" -a "$iface" != "loopback" ] && {
				local rule="-i ${iface} -p tcp --dport 1723"
				fw_check "filter" "$local_service_chain" "$rule -j ACCEPT"
				[ x$? == x0 ] && fw add 4 f $local_service_chain ACCEPT $ { "$rule" }
			}
		done
		refresh_vpn_remote_management
	fi
}

config_pns(){
	local server
	local bindif
	local enable
	local mppe
	local authtype
	
	config_get server $1 server
	config_get bindif $1 bindif
	config_get_bool enable $1 enable # if [ "$eanble" == '0' ];
	config_get_bool mppe  $1 mppeencryption
	config_get authtype $1 authtype
	
	echo $server,$bindif,$enable,$mppe,$authtype
	
	path=${pppox_pptp_server_path}/$server/config
	mkdir -p $path  #path
	touch $path/${pppox_pptptype}.type #type
	touch $path/${pppox_configname} 
	
	uci -c ${path} add ${pppox_configname} pns
	uci -c ${path} set ${pppox_configname}.@pns[-1].bindif=$bindif
	uci -c ${path} set ${pppox_configname}.@pns[-1].authtype=$authtype
	uci -c ${path} set ${pppox_configname}.@pns[-1].enable=$enable
	uci -c ${path} commit ${pppox_configname}
	
	#local devices=$(zone_get_effect_devices $bindif)
	local if=$(zone_get_effect_main_wan_ifaces $bindif)
	pptp_set_ifdevice_info "${bindif}"  "${server}"
	local devices=$(zone_get_device_byif $if)
	#wan file is like 'service_name#effective_devices'
	echo "$server#$devices" >>$pppox_pptp_server_path/wan 
	# for pppd started by pptpd,add a file called options.pptpd
	echo -e $options >$path/options.pptpd
	enable_mppe $mppe $path options.pptpd
	enable_packet $enable $bindif
	echo "path ${pppox_pptp_server_path}/$server" >>$path/options.pptpd
	echo "zonex ${bindif}" >> $path/options.pptpd
	echo "tunnel-proto pptp" >> $path/options.pptpd
	local lcp_echo=$(uci get pptp-server-global.@global[-1].lcpechointerval)
	sed -r -i "/lcp-echo-interval/s/[[:digit:]]+/$lcp_echo/" $path/options.pptpd
	pppox_load_user ${pppox_pptptype} $server
}

config_client_global(){
	local pptpinterval
	local lcpinterval
	
	config_get pptpinterval $1 pptphellointerval
	config_get lcpinterval $1 lcpechointerval
	
	[ ! -e $pppox_pptp_client_path ] && mkdir -p $pppox_pptp_client_path
	echo "$pptpinterval" >$pppox_pptp_client_path/client-global
	sed -r -i "/lcp-echo-interval/s/[[:digit:]]+/$lcpinterval/" $client_path/options.pptp
	#echo "${pptpinterval}#${lcpinterval}"
}

config_pnc(){
	local confname
	local outif
	local enable
	local username 
	local password 
	local pns 
	local workmode 
	local remotesubnet
	local mppe
	local ifname
	local local_network
	
	config_get confname $1 confname
	config_get username $1 username
	config_get password $1 password
	config_get pns  $1 pns
	config_get workmode $1 workmode
	config_get remotesubnet $1 remotesubnet
	config_get local_network $1 local_network
	
	config_get outif $1 outif
	config_get_bool enable $1 enable
	config_get_bool mppe $1 mppeencryption
	config_get ifname $1 tunnelname
	
	client_path=${pppox_pptp_client_path}/${confname}/config
	mkdir -p ${client_path}
	touch ${client_path}/${pppox_configname}
	uci -c ${client_path} add ${pppox_configname} pnc
	uci -c ${client_path} set ${pppox_configname}.@pnc[-1].username=$username
	uci -c ${client_path} set ${pppox_configname}.@pnc[-1].password=$password
	uci -c ${client_path} set ${pppox_configname}.@pnc[-1].pns=$pns
	uci -c ${client_path} set ${pppox_configname}.@pnc[-1].workmode=$workmode
	uci -c ${client_path} set ${pppox_configname}.@pnc[-1].remotesubnet="$remotesubnet"
	uci -c ${client_path} set ${pppox_configname}.@pnc[-1].local_network="$local_network"
	uci -c ${client_path} set ${pppox_configname}.@pnc[-1].outif=$outif
	uci -c ${client_path} set ${pppox_configname}.@pnc[-1].enable=$enable
	uci -c ${client_path} set ${pppox_configname}.@pnc[-1].tunnelname=$ifname
	#when enable is '1',should start the client pppd
	#right now,code is not written
	uci -c ${client_path} commit ${pppox_configname}
	touch ${client_path}/${pppox_pptptype}.type
	touch ${client_path}/options.pptp
	echo -e $client_options >>${client_path}/options.pptp
	enable_mppe $mppe $client_path options.pptp
	echo "path $(dirname $client_path)" >>${client_path}/options.pptp
	echo "ifname ${pptp_header}$ifname" >>${client_path}/options.pptp
	local lcp_echo=$(uci get pptp-client-global.@global[-1].lcpechointerval)
	sed -r -i "/lcp-echo-interval/s/[[:digit:]]+/$lcp_echo/" ${client_path}/options.pptp
	
	#local devices=$(zone_get_effect_devices $outif)
	#for i in $devices;do
	#	outif=$i
	#done
	#echo "outif=$outif"
#	outif=$(zone_get_device_byif $outif)
#	[ $enable = '1' -o $enable = 'on' ] && client_start_pppd $username $password $pns $outif $client_path
}

load_server_config(){
	config_load pptp-server
	config_foreach config_pns	pns
	
	config_load pptp-server-global
	config_foreach config_global global

	#load user
	
}

start_pptp_client() {
	for dir in `ls ${pppox_pptp_client_path} 2>/dev/null`; do
		[ ! -d "${pppox_pptp_client_path}/${dir}" ] && continue
		local path=${pppox_pptp_client_path}/${dir}/config
		local username=`uci -c ${path} get ${pppox_configname}.@pnc[-1].username 2>/dev/null`
		local password=`uci -c ${path} get ${pppox_configname}.@pnc[-1].password 2>/dev/null`
		local outif=`uci -c ${path} get ${pppox_configname}.@pnc[-1].outif 2>/dev/null`
		local pns=`uci -c ${path} get ${pppox_configname}.@pnc[-1].pns 2>/dev/null`
		local enable=`uci -c ${path} get ${pppox_configname}.@pnc[-1].enable 2>/dev/null`
		outif=$(zone_get_effect_main_wan_ifaces $outif)
		pptp_set_ifdevice_info "${outif}"  "${dir}"
		outif=$(zone_get_device_byif $outif)
		local client_path=${path}
		[ $enable = '1' -o $enable = 'on' ] && client_start_pppd $username $password $pns $outif $client_path
	done
}

load_client_config(){
	config_load pptp-client
	config_foreach config_pnc pnc
	
	config_load pptp-client-global
	config_foreach config_client_global global

	start_pptp_client
}
