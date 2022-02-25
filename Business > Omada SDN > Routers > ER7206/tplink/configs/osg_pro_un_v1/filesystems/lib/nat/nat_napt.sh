#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file      nat_mod_napt.sh
# brief    
# author    Chen chen
# version   1.1.0
# date      23Apr15
# history   arg 1.0.0, 23Apr15, Chen chen, Create the file.
#           arg 1.1.0, 21Dec17, Zhangzhongwei, Rewrite the file.

nat_config_rule_napt()
{
	nat_config_get_section "$1" rule_napt { \
		string name "" \
		string enable "" \
		string interface "" \
		string ipaddr "" \
		string mask "" \
		string comment "" \
	} || return
}

nat_load_rule_napt()
{
	nat_config_rule_napt "$1"

	if [[ "$rule_napt_enable" == "on" ]]; then
		for zone in $rule_napt_interface; do
			[ -z "$zone" ] && continue
			local ifaces=$(zone_get_wan_ifaces "${zone}")
			for iface in $ifaces; do
				local device=$(zone_get_device_byif "${iface}")
				if [[ -n "$iface" && -n "$device" ]]; then	
					if $(nat_napt_whole); then
						nat_postrouting_add $MOD_NAPT "-A" "-m comment --comment $rule_napt_name -o $device \
							-m connextmark --mark ${NAPT_DEVICE_MARK}/${NAPT_DEVICE_MARK} -s ${rule_napt_ipaddr}/${rule_napt_mask} -j MASQUERADE"
						nat_postrouting_add $MOD_NAPT "-A" "-m comment --comment $rule_napt_name -o $device \
							-m extmark --extmark ${NAPT_DEVICE_MARK}/${NAPT_DEVICE_MARK} -s ${rule_napt_ipaddr}/${rule_napt_mask} -j MASQUERADE"

						nat_filter_add lan $MOD_NAPT "-I 1" "-m comment --comment $rule_napt_name -o $device \
							-m connextmark --mark ${NAPT_DEVICE_MARK}/${NAPT_DEVICE_MARK} -s ${rule_napt_ipaddr}/${rule_napt_mask} -j ACCEPT"
						nat_filter_add lan $MOD_NAPT "-I 1" "-m comment --comment $rule_napt_name -o $device \
							-m extmark --extmark ${NAPT_DEVICE_MARK}/${NAPT_DEVICE_MARK} -s ${rule_napt_ipaddr}/${rule_napt_mask} -j ACCEPT"

						iptables -w -A zone_vpn_forward -s ${rule_napt_ipaddr}/${rule_napt_mask} -o $device -m connextmark --mark ${NAPT_DEVICE_MARK}/${NAPT_DEVICE_MARK} -j ACCEPT
						iptables -w -A zone_vpn_forward -s ${rule_napt_ipaddr}/${rule_napt_mask} -o $device -m extmark --extmark ${NAPT_DEVICE_MARK}/${NAPT_DEVICE_MARK} -j ACCEPT
					else	
						nat_postrouting_add $MOD_NAPT "-A" "-m comment --comment $rule_napt_name -o $device \
							-s ${rule_napt_ipaddr}/${rule_napt_mask} -j MASQUERADE"

						nat_filter_add lan $MOD_NAPT "-I 1" "-m comment --comment $rule_napt_name -o $device \
							-s ${rule_napt_ipaddr}/${rule_napt_mask} -j ACCEPT"

						iptables -w -A zone_vpn_forward -s ${rule_napt_ipaddr}/${rule_napt_mask} -o $device -j ACCEPT
					fi

				fi
			done
		done
	fi
}

nat_post_load_rule_napt()
{
	local device=$(zone_get_device_byif lan)
	if [[ -n "$device" ]]; then
		nat_filter_add lan $MOD_NAPT "-A" "-o $device -j ACCEPT"
	fi
	nat_filter_add lan $MOD_NAPT "-A" "-j DROP"

	nat_napt_iface_list_create

	env -i CLEAN=on MODULE=NAPT /sbin/hotplug-call nat
	#conntrack -F >/dev/null 2>&1
}

nat_flush_rule_napt()
{
	nat_postrouting_flush ${MOD_NAPT}
	nat_filter_flush ${MOD_NAPT} lan
	fw flush 4 f zone_vpn_forward

	nat_napt_iface_list_clean
}

nat_rule_napt_operation()
{
	local operation=$1
	NAT_LOG_PRINT "@ enter Multi-NAT"
	case $operation in
		start)
			# NAT_LOG_PRINT "  flusing old Multi-NAT rules"
			# nat_flush_rule_napt

			NAT_LOG_PRINT "  building new Multi-NAT rules"
			config_foreach nat_load_rule_napt rule_napt
			nat_post_load_rule_napt
		;;
		stop)
			NAT_LOG_PRINT "  flusing old Multi-NAT rules"
			nat_flush_rule_napt
		;;
	esac
}
