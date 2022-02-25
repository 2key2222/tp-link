#
# Copyright (C) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# 
# brief        ip mac binding module core_global shell scripts
# author     Huang Zhenwei
# version    1.0.0 
# date         06May2015
# history     06May2015    Huang Zhenwei    Create the file
#                22May2015    Huang Zhenwei    Modify 'zone' and 'interface'
#				4August2015  luopei   zone becomes the list of interfaces
. /lib/zone/zone_api.sh
	
IMB_PREFIX="imb_ipmac_"
IP_PREFIX="imb_ip_"
IMB_ARP_FILE="/tmp/.imb_arp"
IMB_IPSET_FILE="/tmp/.imb_ipset"
local imb_device=""

fw_config_get_global() {
	fw_config_get_section "$1" global { \
		string enable "off" \
	} || return
}

fw_config_get_imb_rule() {
	fw_config_get_section "$1" imb_rule { \
		string ipaddr "" \
		string mac "" \
		string zone "" \
		string enable "" \
		string description "" \
	} || return
}


fw_load_all() {
	fw_config_once fw_load_global global
}

fw_exit_all() {
	#fw_flush_arp
	
	/etc/init.d/arp_defense stop  #stop arp_defense firewall
	# local ZONES=$(zone_get_zonelist)	
	# for i in $ZONES; do
		# local EFF_DE=$(zone_get_effect_devices $i)
		# for j in $EFF_DE; do
			# ipset destroy "${IMB_PREFIX}${j}"
			# ipset destroy "${IP_PREFIX}${j}"
		# done
	# done
	while read LINE
	do
		local devname=$(echo $LINE | awk '{print $1}')
		local setname=$(echo $LINE | awk '{print $2}')
		local ipname=$(echo $LINE | awk '{print $3}')
		ipset list $ipname | sed -n '/^Members/,$p' | grep -v 'Members' >/tmp/.debind
		anete ipmac -d /tmp/.debind $devname
		anete ipset destroy $setname
		anete ipset destroy $ipname
	done < /tmp/state/imb
	
	rm /tmp/state/imb
	imb_device=""
}

create_ipset_default()
{
	[ -f /tmp/state/imb ] && rm /tmp/state/imb
	local zone_list=$(zone_get_zonelist)
	local zone=""
	for zone in $zone_list;do
		[ "$zone" == "VPN" ] && continue
		local iface=$(zone_get_wan_ifaces $zone)  # If it is PPPoE/L2TP/PPTP, we choose eth0.XX instead of pppoe/l2tp/pptp-wanX_poe to build the ipset rule.
		if [ -z $iface ];then
			continue
		fi
		local eth_dev=$(zone_get_eth_device $iface)
		echo "${eth_dev} ${IMB_PREFIX}${eth_dev} ${IP_PREFIX}${eth_dev}" >>/tmp/state/imb
		anete ipset create "${IMB_PREFIX}${eth_dev}" hash:ip,mac  -exist
		anete ipset create "${IP_PREFIX}${eth_dev}"  hash:ip  -exist
		if [ x"$imb_device" == "x" ];then
			imb_device=$eth_dev
		else
			imb_device="$imb_device,$eth_dev"
		fi
		local effect_device=$eth_dev
		local device_ip=$(anete ifconfig $effect_device | grep 'inet addr' | awk -F : '{print $2}' | awk '{print $1}')
		[ x"$device_ip" != "x" ] && {
				local device_mac=$(anete ifconfig $effect_device | grep 'HWaddr' | awk '{print $5}')
				if [ x"$device_mac" != "x" ];then
					anete arp -s -i $effect_device $device_ip $device_mac
					local inter=$(zone_get_effect_ifaces $zone)
					echo "$effect_device $device_ip $device_mac" >/tmp/state/$inter
					anete ipset add "${IMB_PREFIX}${effect_device}" "${device_ip},${device_mac}" -exist
					anete ipset add "${IP_PREFIX}${effect_device}" "${device_ip}" -exist
				fi
			}
	done
}

create_ipset_interface(){
	local ZONES=$(zone_get_zonelist)
	create_ipset_default
	for i in $ZONES; do
		#local EFF_IF=$(zone_get_effect_devices $i)
		[ $i == "VPN" ] && continue
		local EFF_IF=$(zone_get_wan_devices $i)
		for j in $EFF_IF; do
			#local EFF_IF=$(zone_get_effect_ifaces NORMAL)
			#local effect_device=$(zone_get_device_byif $j)
			echo $j | grep -q '_poe$' && continue
			local effect_device=${j}
			anete ipset create "${IMB_PREFIX}${effect_device}" hash:ip,mac  -exist
			anete ipset create "${IP_PREFIX}${effect_device}"  hash:ip  -exist
			#echo "${effect_device} ${IMB_PREFIX}${effect_device} ${IP_PREFIX}${effect_device}" >>/tmp/state/imb
			if [ x"$imb_device" == 'x' ];then
				imb_device=$effect_device
			else
				imb_device="$imb_device $effect_device"
			fi
			local device_ip=$(anete ifconfig $effect_device | grep 'inet addr' | awk -F : '{print $2}' | awk '{print $1}')
			[ x"$device_ip" != "x" ] && {
				local device_mac=$(anete ifconfig $effect_device | grep 'HWaddr' | awk '{print $5}')
				if [ x"$device_mac" != "x" ];then
					anete arp -s -i $effect_device $device_ip $device_mac
					local inter=$(zone_get_effect_ifaces $i)
					echo "$effect_device $device_ip $device_mac" >/tmp/state/$inter
					anete ipset add "${IMB_PREFIX}${effect_device}" "${device_ip},${device_mac}" -exist
					anete ipset add "${IP_PREFIX}${effect_device}" "${device_ip}" -exist
				fi
			}
		done
	done
}

fw_load_global() {
	#fw_config_get_global $1
	local global_enable=$(uci get arp_defense.settings.enable)
	local imb_pass=$(uci get arp_defense.settings.imb_pass)
	local garp=$(uci get arp_defense.settings.garp)
	local time=$(uci get arp_defense.settings.time)
	#local accept_only_flag=0
	#[ x"$imb_pass" == "xon" ] && accept_only_flag=1
	create_ipset_default
	
	#config_foreach fw_load_imb_rule imb_rule
	cd /usr/lib/lua && lua ./imb/imb_reload.lua

	[ $global_enable = "on" -a $imb_pass = "on" ] && /etc/init.d/arp_defense start
	[ x$time == 'x' ] && time=1000
	rmmod arp_garp
	if [ $global_enable = 'on' ];then
		local devices=""
		local interfaces=$(uci get arp_defense.settings.interface)
		local inter=""
		for inter in $interfaces;do
			local dev=$(zone_get_effect_devices $inter)
			if [ x"$devices" == 'x' ];then
				devices=$dev
			else
				devices="$devices,$dev"
			fi
		done
		#[ x"$imb_device" == 'x' ] && imb_device="br-lan"
		#imb_device=${imb_device// /,}
		#imb_device="br-lan,eth0.10,eth0.20,eth0.30,eth0.40"
		#echo "$imb_device" >/dev/console
		if [ x$garp != 'xon' ];then
			insmod /lib/modules/$(uname -r)/arp_garp.ko sendflag=0 interval_time=$time  name=$devices
		else
			insmod /lib/modules/$(uname -r)/arp_garp.ko sendflag=1 interval_time=$time  name=$devices
		fi
    fi
}

#$1: interface
#$2: ipaddr
#$3: mac
lua_load_imb_rule()
{
	local global_enable=$(uci get arp_defense.settings.enable)
	if [[ $global_enable = 'on' ]]; then
		anete ipmac -b $IMB_ARP_FILE
	fi
	#rm $IMB_ARP_FILE -f 2>/dev/null
	#rm $IMB_IPSET_FILE -f 2>/dev/null
}

fw_load_imb_rule() {
	fw_config_get_imb_rule $1
	
	case $imb_rule_enable in
		on )
		# need small changes to...
		local interface=$imb_rule_zone  
		#echo "imb_zone:$R_ZONE" >>/tmp/imb_log
		local R_IPADDR=$imb_rule_ipaddr
		local R_MAC=$(echo $imb_rule_mac | tr [a-z] [A-Z])
		
		local IF_IP
		
		local effect_devices=$(zone_get_wan_devices $interface)
		for effect_device in $effect_devices; do
			echo $effect_device | grep -q '_poe$' && continue

			ipset list ${IMB_PREFIX}$effect_device >/dev/null 2>&1 && {
				anete ipset add "${IMB_PREFIX}${effect_device}" "${R_IPADDR},${R_MAC//-/:}" -exist
				anete ipset add "${IP_PREFIX}${effect_device}" "${R_IPADDR}" -exist
				anete arp -s -i $effect_device $R_IPADDR ${R_MAC//-/:}
			}
		done

			;;
		off )		
			;;
	esac
}

fw_flush_arp() {
	local IFS_old=$IFS
	IFS=$'\n'
	local LINE=""
	for LINE in $(anete arp -n | sed '/Address/d' | awk '{ print }');
	do
		if [ $(echo $LINE | awk '{ print $2 }') != "(incomplete)" ]; then
			local IPADDR=$(echo $LINE | awk '{ print $1 }')
			local IFACE=$(echo $LINE | awk '{ print $5 }')
			anete arp -d -i $IFACE $IPADDR
		fi
	done
	IFS=$IFS_old
}



fw_imb_event_do_interface()
{
	local iface=$2
	local $action=$3
	#add ip & mac of the device itself to ipset
	local devices=$(zone_get_wan_devices $iface)
	for device in $devices; do
		echo $device | grep -q '_poe$' && continue

		# [ x"$device" == "x" ] && return 1
		anete ipset create "${IMB_PREFIX}$device" hash:ip,mac -exist
		anete ipset create "${IP_PREFIX}$device" hash:ip -exist

		local device_ip=$(anete ifconfig $device | grep 'inet addr' | awk -F : '{print $2}' | awk '{print $1}')
		[ x"$device_ip" != "x" ] && {
			local device_mac=$(anete ifconfig $device | grep 'HWaddr' | awk '{print $5}')
			if [ x"$device_mac" != "x" ];then
				anete ipset add "${IMB_PREFIX}${device}" "${device_ip},${device_mac}" -exist
				anete ipset add "${IP_PREFIX}$device" "${device_ip}" -exist
			fi
		}
	done

	fw_config_get_imb_rule $1

	case $imb_rule_enable in
		on )
		local R_ZONE=$imb_rule_zone  #interface
		local R_IPADDR=$imb_rule_ipaddr
		local R_MAC=$(echo $imb_rule_mac | tr [a-z] [A-Z])
		local IF_IP

		#local EFF_IF=$(zone_get_effect_ifaces $R_ZONE)

		#for i in $EFF_IF; do
		for i in $R_ZONE; do
			[ "$i" == "$iface" ] && {
				#network_get_subnet IF_IP $i
				#if [ $(ipcalc -n $R_IPADDR/${IF_IP#*/}) == $(ipcalc -n $IF_IP) ]; then
					local devices=$(zone_get_wan_devices $i)
					for EFF_DE in $devices; do
						echo $EFF_DE | grep -q '_poe$' && continue
						anete ipset add "${IMB_PREFIX}${EFF_DE}" "${R_IPADDR},${R_MAC//-/:}" -exist
						anete ipset add "${IP_PREFIX}${EFF_DE}" "${R_IPADDR}" -exist
						anete arp -s -i $EFF_DE $R_IPADDR ${R_MAC//-/:}
						break
					done
				#fi
			}	
		done
			;;
		off )		
			;;
	esac

}


fw_imb_event_interface()
{
	local iface=$1
	local action=$2

	[ -z "$iface" -o -z "$action" ] && {
		return
	}

	[ "add" == "$action" ] && {
		config_foreach fw_imb_event_do_interface imb_rule $iface $action
	}

	[ "del" == "$action" ] && {
		local LINE=""
		for LINE in $(anete arp -n | sed '/Address/d' | awk '{ print }');
		do
			if [ $(echo $LINE | awk '{ print $2 }') != "(incomplete)" ]; then
				local IPADDR=$(echo $LINE | awk '{ print $1 }')
				local IFACE=$(echo $LINE | awk '{ print $5 }')
				local FLAGS=$(echo $LINE | awk '{ print $4 }')
				devices=$(zone_get_wan_devices $iface)
				for device in $devices; do
					[ "$IFACE" == "$device" -a "$FLAGS" == "CM" ] && {
						anete arp -d -i $IFACE $IPADDR
					}	
				done
				
			fi
		done
		local devices=$(zone_get_wan_devices $iface)
		for device in $devices; do
			echo $device | grep -q '_poe$' && continue
			[ x"$device" != 'x' ] && {
				anete ipset destroy "${IMB_PREFIX}$device"
				anete ipset destroy "${IP_PREFIX}$device"
			}
		done
	}

}
