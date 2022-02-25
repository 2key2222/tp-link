#
# Copyright (C) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# 
# brief        mac filter module core_global shell scripts
# author     Huang Zhenwei
# version    1.0.0 
# date         29Apr2015
# history     29Apr2015    Huang Zhenwei    Create the file

#
# use "-C" to check if the rule exists
# return: 1 rule exists;
#            0 rule not exists;
#
. /lib/zone/zone_api.sh

fw_check() {
	local ret=$(iptables -w -t $1 -C $2 $3 2>&1)
	[ -n "$ret" ] && return 0||return 1
}

fw_config_get_global() {
	fw_config_get_section "$1" global { \
		string enable "off" \
		string filter_mode "black" \
		string interfaces "" \
	} || return
}

fw_config_get_white_list() {
	fw_config_get_section "$1" white_list { \
		string name "" \
		string mac "" \
	} || return
}

fw_config_get_black_list() {
	fw_config_get_section "$1" black_list { \
		string name "" \
		string mac "" \
	} || return
}

fw_config_get_mac_list() {
	fw_config_get_section "$1" mac_list { \
		string name "" \
		string mac "" \
	} || return
}

fw_load_all() {
	fw_config_once fw_load_global global
}

fw_exit_all() {
	fw flush 4 f mac_filtering
	fw_check "filter" "forwarding_rule" "-j mac_filtering"
	while [ x$? == x1 ]; do
		fw del 4 f forwarding_rule mac_filtering
		fw_check "filter" "forwarding_rule" "-j mac_filtering"
	done
	fw del 4 f mac_filtering
	
	ipset destroy mac_set
}

fw_load_global() {
	fw_config_get_global $1
	case $global_enable in
		on )
		ipset create mac_set hash:mac -exist
		
		fw add 4 f mac_filtering
		fw_check "filter" "forwarding_rule" "-j mac_filtering"
		[ x$? == x0 ] && {
			fw_check "filter" "forwarding_rule" "-j mac_drop"
			if [ x$? == x0 ];then 
				fw add 4 f forwarding_rule mac_filtering 1
			else
				#fw add 4 f forwarding_rule mac_filtering 3
				local num=$(iptables -w -nL forwarding_rule --line-number | grep "\bmac_drop\b" | awk '{print $1}')
				num=$(($num+1))
				fw add 4 f forwarding_rule mac_filtering $num
			fi
		} 
		

		case $global_filter_mode in
		 	black )
			ipset flush mac_set
			#config_foreach fw_load_black_list black_list
			config_foreach fw_load_mac_list mac_list
			local tmp_interface=""
			if [ x"$global_interfaces" == 'x' ];then  #interface is empty
				#local rule="-m set --match-set mac_set src"
				#fw_check "filter" "mac_filtering" "$rule -j DROP"
				#[ x$? == x0 ] && fw add 4 f mac_filtering DROP { "$rule" }
				return
			else
				
				for tmp_interface in $global_interfaces;do
					local dev=$(zone_get_effect_ifaces $tmp_interface)
					dev=$(zone_get_device_byif $dev)
					local rule="-m set --match-set mac_set src -i $dev"
					fw_check "filter" "mac_filtering" "$rule -j DROP"
					[ x$? == x0 ] && fw add 4 f mac_filtering DROP { "$rule" }
				done
			fi
			for tmp_interface in $global_interfaces;do
				local dev=$(zone_get_effect_ifaces $tmp_interface)
				dev=$(zone_get_device_byif $dev)
				local rule="-i $dev"
				fw_check "filter" "mac_filtering" "$rule -j RETURN"
				[ x$? == x0 ] && fw add 4 f mac_filtering RETURN { "$rule" }
			done
		 		;;
		 	white )
			ipset flush mac_set
			#config_foreach fw_load_white_list white_list
			config_foreach fw_load_mac_list mac_list

			local tmp_interface
			if [ x"$global_interfaces" == 'x' ];then
				#local rule="-m set --match-set mac_set src"
				#fw_check "filter" "mac_filtering" "$rule -j RETURN"
				#[ x$? == x0 ] && fw add 4 f mac_filtering RETURN { "$rule" }
				return
			else
				
				for tmp_interface in $global_interfaces;do
					local dev=$(zone_get_effect_ifaces $tmp_interface)
					dev=$(zone_get_device_byif $dev)
					local rule="-m set --match-set mac_set src -i $dev"
					fw_check "filter" "mac_filtering" "$rule -j RETURN"
					[ x$? == x0 ] && fw add 4 f mac_filtering RETURN { "$rule" }
				done
			fi

			for tmp_interface in $global_interfaces;do
				local dev=$(zone_get_effect_ifaces $tmp_interface)
				dev=$(zone_get_device_byif $dev)
				local rule="-i $dev"
				fw_check "filter" "mac_filtering" "$rule -j DROP"
				[ x$? == x0 ] && fw add 4 f mac_filtering DROP { "$rule" }
			done
		 		;;
		esac 

		#conntrack -F
		#syslog $LOG_INF_FUNCTION_ENABLE
		#syslog $LOG_NTC_FLUSH_CT_SUCCESS
			;;
		off )
		#syslog $LOG_INF_FUNCTION_DISABLE
			;;
	esac
	
}

fw_load_white_list() {
	fw_config_get_white_list $1
	local mac=$(echo $white_list_mac | tr [a-z] [A-Z])
	ipset add mac_set "${mac//-/:}"
	#syslog $ACCESS_CONTROL_LOG_DBG_WHITE_LIST_ADD "${mac//-/:}"
}

fw_load_black_list() {
	fw_config_get_black_list $1
	local mac=$(echo $black_list_mac | tr [a-z] [A-Z])
	ipset add mac_set "${mac//-/:}"
	#syslog $ACCESS_CONTROL_LOG_DBG_BLACK_LIST_ADD "${mac//-/:}"
}

fw_load_mac_list() {
	fw_config_get_mac_list $1
	local mac=$(echo $mac_list_mac | tr [a-z] [A-Z])
	ipset add mac_set "${mac//-/:}" -exist
	#syslog $ACCESS_CONTROL_LOG_DBG_BLACK_LIST_ADD "${mac//-/:}"
}