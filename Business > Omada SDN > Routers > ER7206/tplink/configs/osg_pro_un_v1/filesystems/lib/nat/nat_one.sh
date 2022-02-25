#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file      nat_mod_one.sh
# brief	
# author    Chen chen
# version   1.1.0
# date      23Apr15
# history   arg 1.0.0, 23Apr15, Chen chen, Create the file.
#           arg 1.1.0, 21Dec17, Zhangzhongwei, Rewrite the file.

nat_config_rule_onenat()
{
	nat_config_get_section "$1" rule_onenat { \
		string name "" \
		string enable "" \
		string interface "" \
		string internal_ip "" \
		string external_ip "" \
		string dmz "" \
		string comment "" \
	} || return
}

nat_load_rule_onenat()
{
	nat_config_rule_onenat "$1"
	
	if [[ "$rule_onenat_enable" == "on" ]]; then
		nat_postrouting_add $MOD_ONE "-A" "-m policy --dir out --pol ipsec --mode tunnel -j RETURN" 
		for zone in $rule_onenat_interface; do
			[ -z "$zone" ] && continue
			local iface=$(zone_get_effect_ifaces "${zone}" 2>/dev/null)
			local device=$(zone_get_device_byif "${iface}")

			if [[ -n "$iface" && -n "$device" ]]; then
				local netmask="255.255.255.255"
				ifconfig $device:$one_nat_id ${rule_onenat_external_ip} netmask $netmask up
				echo "$device:$one_nat_id" >> /tmp/.nat/one_nat_id
				let one_nat_id++

				nat_postrouting_add $MOD_ONE "-A" "-m comment --comment $rule_onenat_name -o $device \
					-s $rule_onenat_internal_ip -j SNAT --to-source $rule_onenat_external_ip"

				if [[ "$rule_onenat_dmz" == "on" ]]; then
					# No need to specify INPUT device, for DMZ loopback. Packets from other INPUT devices would be drop in the filter table.
					nat_prerouting_add $MOD_ONE "-A" "-m comment --comment $rule_onenat_name \
						-d $rule_onenat_external_ip -j DNAT --to-destination $rule_onenat_internal_ip"
						
					# for One-to-one NAT Loopback
					nat_postrouting_add $MOD_ONE "-A" "-m comment --comment $rule_onenat_name -d $rule_onenat_internal_ip \
						-j SNAT --to-source $rule_onenat_external_ip -m extmark --extmark ${NAPT_DEVICE_MARK_LANIN}/${NAPT_DEVICE_MARK_LANIN}"

					nat_filter_add $iface $MOD_ONE "-A" "-m comment --comment $rule_onenat_name \
						-d $rule_onenat_internal_ip -j ACCEPT"
				fi
			fi
		done
	fi
}

nat_flush_rule_onenat()
{
	nat_prerouting_flush ${MOD_ONE}
	nat_postrouting_flush ${MOD_ONE}

	local if_list=$(uci_get_state nat env if_list)
	if [[ -n "$if_list" ]]; then
		for iface in $if_list; do
			if [[ -n "$iface" && "$iface" != "lan" ]]; then
				nat_filter_flush ${MOD_ONE} $iface
			fi
		done
	fi
}

nat_rule_one_nat_operation()
{
	local operation=$1

	NAT_LOG_PRINT "@ enter One-NAT"
	case $operation in
		start)
			# NAT_LOG_PRINT "  flusing old One-NAT rules"
			# nat_flush_rule_onenat

			NAT_LOG_PRINT "  building new One-NAT rules"
			if [[ -f /tmp/.nat/one_nat_id ]]; then
				while read line; do ifconfig $line down; done < /tmp/.nat/one_nat_id
				rm -f /tmp/.nat/one_nat_id >/dev/null 2>&1
			fi
			local one_nat_id=1
			config_foreach nat_load_rule_onenat rule_onenat
		;;
		stop)
			NAT_LOG_PRINT "  flusing old One-NAT rules"
			nat_flush_rule_onenat
		;;
	esac
}
