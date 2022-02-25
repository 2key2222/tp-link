#!/bin/sh
. /lib/functions.sh
. /lib/functions/service.sh
. /lib/openvpn/openvpn-common.sh
. /lib/zone/zone_api.sh
. /lib/functions/network.sh
. /lib/firewall/fw.sh

action=$1
SECTIONNAME=$2
#rebuild or not
flag=$3

openvpn_server_access(){
    local proto=
    local port=
	local device=
	local wans=

	
	config_get port $SECTIONNAME port
	config_get proto $SECTIONNAME proto
	config_get wans $SECTIONNAME wan

	
	for wan in ${wans} 
	do 
		device=$(zone_get_wan_devices $wan)
		echo "$wan $device" > /dev/console
		fw add 4 f zone_wan_openvpn ACCEPT { "-i $device -p $proto -m $proto --dport $port" }
	done
	 	
	
}

openvpn_client_access(){

	local device=
	local wans=
	local proto=
    local port=
	
	config_get wans $SECTIONNAME wan
	config_get port $SECTIONNAME port
	config_get proto $SECTIONNAME proto
	
	for wan in ${wans} 
	do 
		device=$(zone_get_wan_devices $wan)
		#echo "$wan $device" > /dev/console
		fw add 4 f zone_wan_openvpn ACCEPT { "-i $device -p $proto -m $proto --dport $port" }
	done
}

openvpn_server_block(){

    local proto=
    local port=
	local device=
	local wans=

	
	config_get port $SECTIONNAME port
	config_get proto $SECTIONNAME proto
	config_get wans $SECTIONNAME wan

	for wan in ${wans}  
	do 
		device=$(zone_get_wan_devices $wan)
		echo "$wan $device" > /dev/console
		fw del 4 f zone_wan_openvpn ACCEPT { "-i $device -p $proto -m $proto --dport $port" }
	done
   
}

openvpn_client_block(){
	local device=
	local wans=
	local proto=
    local port=
	
	config_get wans $SECTIONNAME wan
	config_get port $SECTIONNAME port
	config_get proto $SECTIONNAME proto
	for wan in ${wans}  
	do 
		device=$(zone_get_wan_devices $wan)
		#echo "$wan $device" > /dev/console
		fw del 4 f zone_wan_openvpn ACCEPT { "-i $device -p $proto -m $proto --dport $port" }
	done
}

{
	case $action in
		addserver)
			/usr/sbin/build-ovpn-crt $SECTIONNAME $flag		
			/lib/cfg_save/config.sh save
			config_load 'openvpn'
			openvpn_server_access
			start_instance "$SECTIONNAME"
		;;
		addclient)
			config_load 'openvpn'
			openvpn_client_access
			start_client_instance "$SECTIONNAME"
		;;
		delserver)
			config_load 'openvpn'
			stop_instance "$SECTIONNAME"
			openvpn_server_block
		;;
		delclient)
			config_load 'openvpn'
			stop_instance "$SECTIONNAME"
			openvpn_client_block
		;;
		update)
			config_load 'openvpn'
			reload_instance "$SECTIONNAME"
		;;
		generate)
			/usr/sbin/build-ovpn-crt $SECTIONNAME $flag
		;;
	esac
}
