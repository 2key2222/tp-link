#
# Copyright (C) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# 
# brief        arp defense module core_global shell scripts
# author     Huang Zhenwei
# version    1.0.0 
# date         15May2015
# history     15May2015    Huang Zhenwei    Create the file

#
# use "-C" to check if the rule exists
# return: 1 rule exists;
#            0 rule not exists;
#
. /lib/zone/zone_api.sh
. /lib/net_share.sh

fw_check() {
	local ret=$(iptables -w -t $1 -C $2 $3 2>&1)
	[ -n "$ret" ] && return 0||return 1
}

fw_check_vnet() {
	local ret=$(vnete iptables -w -t $1 -C $2 $3 2>&1)
	[ -n "$ret" ] && return 0||return 1
}

fw_config_get_global() {
	fw_config_get_section "$1" global { \
		string imb_pass "off" \
		string garp "off" \
		string time "100" \
		string interface "" \
		string log_enable "0" \
		string enable "on" \
	} || return
}

fw_load_all() {
	fw_config_once fw_load_global global
}

fw_exit_all() {
	anete fw flush 4 f ip_mac_binding
	fw_check "filter" "forwarding_rule" "-j ip_mac_binding"
	while [ x$? == x1 ]; do
		anete fw del 4 f forwarding_rule ip_mac_binding
		fw_check "filter" "forwarding_rule" "-j ip_mac_binding"
	done
	
	# fw_check "filter" "input_rule" "-j ip_mac_binding"
	# while [ x$? == x1 ]; do
	# 	fw del 4 f INPUT ip_mac_binding
	# 	fw_check "filter" "input_rule" "-j ip_mac_binding"
	# done
	anete fw del 4 f ip_mac_binding

	#fw flush 4 f ip_mac_binding_output
	#fw_check "filter" "OUTPUT" "-j ip_mac_binding_output"
	#while [ x$? == x1 ]; do
	#	fw del 4 f OUTPUT ip_mac_binding_output
	#	fw_check "filter" "OUTPUT" "-j ip_mac_binding_output"
	#done	
	#fw del 4 f ip_mac_binding_output
	
}

fw_load_global() {
	fw_config_get_global $1
	#local enable=$(uci get imb.settings.enable)
	#global_enable is off,then return
	[ $global_enable == "off" ] && return 1
	case $global_imb_pass in
		on )
		
		[ -f /tmp/state/imb ]
		if [ $? -eq 0 ]; then
			
			anete fw add 4 f ip_mac_binding
			fw_check "filter" "forwarding_rule" "-j ip_mac_binding"
			[ x$? == x0 ] && anete fw add 4 f forwarding_rule ip_mac_binding 1
			
			# fw_check "filter" "input_rule" "-j ip_mac_binding"
			# [ x$? == x0 ] && fw add 4 f input_rule ip_mac_binding 1

			#fw add 4 f ip_mac_binding_output
			#fw_check "filter" "OUTPUT" "-j ip_mac_binding_output"
			#[ x$? == x0 ] && iptables -I OUTPUT -j ip_mac_binding_output		
			local interfaces=$(zone_get_zonelist)
			for i in $interfaces;do
				# [ "$i" == "VPN" ] && continue
				[ "${i:0:3}" != "LAN" ] && continue		# Now only support LAN
				local existflag=0
				local devices=$(zone_get_wan_devices $i)
				[ -z "$devices" ] && continue
				for device in $devices; do
					echo $device | grep -q '_poe$' && continue
					while read LINE
					do
						local IFACE=$(echo $LINE | awk '{ print $1 }')
						if [ $device == $IFACE ];then
							local SETNAME=$(echo $LINE | awk '{ print $2 }')
							local rule="-i ${IFACE} -m set ! --match-set ${SETNAME} src,src"

							if multilan_on && vnet_on ; then
								fw_check "filter" "ip_mac_binding" "-m extmark --extmark 0x1/0x1 -j DROP"
								[ "$i" != "LAN" -a x$? == x0 ] && {
									fw add 4 f ip_mac_binding DROP { -m extmark --extmark 0x1/0x1 }
								}
								fw_check_vnet "filter" "ip_mac_binding" "$rule -j EXTMARK --or-mark 0x1"
								[ "$i" != "LAN" -a x$? == x0 ] && {
									vnete fw add 4 f ip_mac_binding 'EXTMARK --or-mark 0x1' { "$rule" }
									vnete fw add 4 f ip_mac_binding 'CONNEXTMARK --or-mark 0x1' { "$rule" }
								}
							else
								fw_check "filter" "ip_mac_binding" "$rule -j DROP"
								[ x$? == x0 ] && {
										fw add 4 f ip_mac_binding DROP { "$rule" }
								}
							fi

							#rule="-o ${IFACE} -m set ! --match-set ${SETNAME} dst,dst"
							#fw_check "filter" "ip_mac_binding_output" "$rule -j DROP"
							#[ x$? == x0 ] && fw add 4 f ip_mac_binding_output DROP { "$rule" }						
							existflag=1
							break
						fi
					done < /tmp/state/imb
					
					[ $existflag = 0 ] && {
						local rule="-i ${device} -m set ! --match-set imb_ipmac_${device} src,src"

						if multilan_on && vnet_on ; then
							fw_check "filter" "ip_mac_binding" "-m extmark --extmark 0x1/0x1 -j DROP"
							[ "$i" != "LAN" -a x$? == x0 ] && {
									fw add 4 f ip_mac_binding DROP { -m extmark --extmark 0x1/0x1 }
							}
							fw_check_vnet "filter" "ip_mac_binding" "$rule -j EXTMARK --or-mark 0x1"
							[ "$i" != "LAN" -a x$? == x0 ] && {
									vnete fw add 4 f ip_mac_binding 'EXTMARK --or-mark 0x1' { "$rule" }
									vnete fw add 4 f ip_mac_binding 'CONNEXTMARK --or-mark 0x1' { "$rule" }
							}
						else
							fw_check "filter" "ip_mac_binding" "$rule -j DROP"
							[ x$? == x0 ] && {
									fw add 4 f ip_mac_binding DROP { "$rule" }
							}
						fi
					}
				done
			done
			# fw_check "filter" "ip_mac_binding" "-j RETURN"
			# [ x$? == x0 ] && fw add 4 f ip_mac_binding RETURN
			
		#	conntrack -F
		# else
		# 	fw add 4 f ip_mac_binding
			
		# 	fw_check "filter" "forwarding_rule" "-j ip_mac_binding"
		# 	[ x$? == x0 ] && fw add 4 f forwarding_rule ip_mac_binding 2
			
		# 	fw_check "filter" "INPUT" "-j ip_mac_binding"
		# 	[ x$? == x0 ] && iptables -w  -I INPUT  -j ip_mac_binding

		# 	#fw add 4 f ip_mac_binding_output
		# 	#fw_check "filter" "OUTPUT" "-j ip_mac_binding_output"
		# 	#[ x$? == x0 ] && iptables -I OUTPUT -j ip_mac_binding_output
			
		# 	for i in $global_interface;do
		# 		local device=$(zone_get_effect_devices $i)
		# 		local rule="-i ${device}"
		# 		fw_check "filter" "ip_mac_binding" "$rule -j DROP"
		# 		[ x$? == x0 ] && fw add 4 f ip_mac_binding DROP { "$rule" }

		# 		#rule="-o ${device}"
		# 		#fw_check "filter" "ip_mac_binding_output" "$rule -j DROP"
		# 		#[ x$? == x0 ] && fw add 4 f ip_mac_binding_output DROP { "$rule" }
		# 	done
		#	conntrack -F
		fi
			;;
		off )
		#syslog $LOG_INF_FUNCTION_DISABLE
			;;
	esac
	
}
