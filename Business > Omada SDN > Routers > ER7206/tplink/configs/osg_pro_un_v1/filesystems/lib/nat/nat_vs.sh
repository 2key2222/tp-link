#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file      nat_mod_vs.sh
# brief    
# author    Chen chen
# version   1.1.0
# date      23Apr15
# history   arg 1.0.0, 23Apr15, Chen chen, Create the file.
#           arg 1.1.0, 21Dec17, Zhangzhongwei, Rewrite the file.

. /lib/net_share.sh

nat_config_rule_vs()
{
	nat_config_get_section "$1" rule_vs { \
		string name "" \
		string enable "" \
		string interface "" \
		string external_port "" \
		string internal_port "" \
		string protocol "" \
		string ipaddr "" \
		string fromAddr "" \
		string natIndex "" \
	} || return
}

nat_load_rule_vs()
{
	local proto="all tcp udp"
	local lan_mask="$2"
	local lan_subnet="$3"

	#echo "###  nat_load_rule_vs_in"
	nat_config_rule_vs "$1"

	#echo "rule_vs_interface=$rule_vs_interface"
	if [[ -z "$rule_vs_interface" ]]; then
		NAT_LOG_PRINT "! interface is not set"
		return 1
	fi

	if [[ -z "$rule_vs_ipaddr" || "$rule_vs_ipaddr" == "0.0.0.0" ]]; then
		NAT_LOG_PRINT "! host ipaddr is not set"
		return 1
	fi

	if [[ -z "$rule_vs_external_port" || -z "$rule_vs_internal_port" ]]; then
		NAT_LOG_PRINT "! port is not set"
		return 1
	fi

	if [[ -n "$rule_vs_protocol" ]]; then
		rule_vs_protocol=$(echo $rule_vs_protocol|tr '[A-Z]' '[a-z]')
	fi

	nat__do_vs_rule() {
		local protos=$1
		local device=$2
		local iface=$3
		local ip=$4
		local ex_port_start=${rule_vs_external_port%-*}
		local ex_port_end=${rule_vs_external_port#*-}
		local in_port_start=${rule_vs_internal_port%-*}
		local in_port_end=${rule_vs_internal_port#*-}
		local ipgroup_src=$rule_vs_fromAddr
		local index=$rule_vs_natIndex

		if nat_port $ex_port_start && nat_port $ex_port_end && nat_port $in_port_start && nat_port $in_port_end; then
			local ex_ports=${ex_port_start}
			local in_ports=${in_port_start}

			if [[ "$ex_port_start" -gt "$ex_port_end" ]]; then
				ex_ports=${ex_port_end}:${ex_port_start}
			elif [[ "$ex_port_start" -lt "$ex_port_end" ]]; then
				ex_ports=${ex_port_start}:${ex_port_end}
			fi

			if [[ "$in_port_start" -gt "$in_port_end" ]]; then
				in_ports=${in_port_end}:${in_port_start}
			elif [[ "$in_port_start" -lt "$in_port_end" ]]; then
				in_ports=${in_port_start}:${in_port_end}
			fi

			if [[ "$ipgroup_src" != "" ]]; then
				for proto in $protos; do
					# Build prerouting Rules, for DNAT
					nat_prerouting_add $MOD_VS "-A" "-m comment --comment ${rule_vs_name} -m set --match-set ${ipgroup_src} src \
						-d ${ip} -p ${proto} --dport ${ex_ports} -j DNAT --to-destination ${rule_vs_ipaddr}:${in_ports/:/-} ${index:+--nat-index $index}"

					# Build postrouting Rules, for Loopback
					nat_postrouting_add $MOD_VS "-A" "-m comment --comment ${rule_vs_name} -m set --match-set ${ipgroup_src} src \
						-d ${rule_vs_ipaddr}/32 -p ${proto} -m ${proto} --dport ${in_ports} -j SNAT --to ${ip} -m extmark --extmark ${NAPT_DEVICE_MARK_LANIN}/${NAPT_DEVICE_MARK_LANIN} ${index:+--nat-index $index}"

					# Build Filter Rules
					nat_filter_add $iface $MOD_VS "-A" "-m comment --comment ${rule_vs_name} -m set --match-set ${ipgroup_src} src \
						-d ${rule_vs_ipaddr} -p ${proto} --dport ${in_ports} -j ACCEPT"
				done
			else
				for proto in $protos; do
					# Build prerouting Rules, for DNAT
					nat_prerouting_add $MOD_VS "-A" "-m comment --comment ${rule_vs_name} -d ${ip} -p ${proto} \
						--dport ${ex_ports} -j DNAT --to-destination ${rule_vs_ipaddr}:${in_ports/:/-} ${index:+--nat-index $index}"

					# Build postrouting Rules, for Loopback
					nat_postrouting_add $MOD_VS "-A" "-m comment --comment ${rule_vs_name} \
						-d ${rule_vs_ipaddr}/32 -p ${proto} -m ${proto} --dport ${in_ports} -j SNAT --to ${ip} -m extmark --extmark ${NAPT_DEVICE_MARK_LANIN}/${NAPT_DEVICE_MARK_LANIN} ${index:+--nat-index $index}"

					# Build Filter Rules
					nat_filter_add $iface $MOD_VS "-A" "-m comment --comment ${rule_vs_name} -d ${rule_vs_ipaddr} \
						-p ${proto} --dport ${in_ports} -j ACCEPT"
				done
			fi
		fi
	}

	if [[ "$rule_vs_enable" == "on" ]]; then
		# Only for the first connection.
		for zone in $rule_vs_interface; do
			[ -z "$zone" ] && continue
			local iface=$(zone_get_effect_ifaces "${zone}" 2>/dev/null) 
			local device=$(zone_get_device_byif "${iface}")
			if [[ -n "$iface" && -n "$device" ]]; then
				local if_ip=$(uci_get_state nat env "${iface}_ip")
				if [[ -n "$if_ip" ]]; then
					case $rule_vs_protocol in
						tcp|udp)
							nat__do_vs_rule $rule_vs_protocol "$device" "$iface" "$if_ip"
						;;
						all)
							nat__do_vs_rule "tcp udp" "$device" "$iface" "$if_ip"
						;;
					esac
				fi
			fi
		done
	fi
}

nat_flush_rule_vs()
{
	nat_prerouting_flush ${MOD_VS}
	nat_postrouting_flush ${MOD_VS}

	local if_list=$(uci_get_state nat env if_list)
	if [[ -n "$if_list" ]]; then
		for iface in $if_list; do
			if [[ -n "$iface" && "$iface" != "lan" ]]; then
				nat_filter_flush ${MOD_VS} $iface
			fi
		done
	fi
}

nat_rule_vs_operation()
{
	local operation=$1
	NAT_LOG_PRINT "@ enter Virtual Server"
	case $operation in
		start)
			# NAT_LOG_PRINT "  flusing old Virtual Server rules"
			# nat_flush_rule_vs
			local lan_ip=$(uci_get_state nat env lan_ip)
			local lan_mask=$(uci_get_state nat env lan_mask)
			local lan_subnet=$(ipcalc -n $lan_ip/$lan_mask)
			lan_subnet=${lan_subnet#*=}
			[ -z "$lan_mask" -o -z "$lan_subnet" ] && return 1

			NAT_LOG_PRINT "  building new Virtual Server rules"
			config_foreach nat_load_rule_vs rule_vs "$lan_mask" "$lan_subnet"
		;;
		stop)
			NAT_LOG_PRINT "  flusing old Virtual Server rules"
			nat_flush_rule_vs
		;;
	esac
}
