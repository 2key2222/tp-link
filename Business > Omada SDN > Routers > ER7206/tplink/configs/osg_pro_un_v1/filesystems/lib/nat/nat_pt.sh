#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file      nat_mod_pt.sh
# brief    
# author    Chen chen
# version   1.1.0
# date      20Apr15
# history   arg 1.0.0, 21Apr15, Chen chen, Create the file.
#           arg 1.1.0, 21Dec17, Zhangzhongwei, Rewrite the file.

VALID_PT_IFACES=

nat_config_rule_pt()
{
	nat_config_get_section "$1" rule_pt { \
		string name "" \
		string enable "" \
		string interface "" \
		string ext_interface ""\
		string trigger_port "" \
		string trigger_protocol "" \
		string external_port "" \
		string external_protocol "" \
	} || return
}

nat_load_rule_pt()
{
	local tri_proto="all tcp udp"
	local pub_proto="all tcp udp"
	
	nat_config_rule_pt "$1"
	
	if [[ -z "$rule_pt_interface" ]]; then
		NAT_LOG_PRINT "! interface is not set"
		return 1
	fi

	if [[ -n "$rule_pt_trigger_protocol" ]]; then
		rule_pt_trigger_protocol=$(echo $rule_pt_trigger_protocol |tr '[A-Z]' '[a-z]')
	fi

	if [[ -n "$rule_pt_external_protocol" ]]; then
		rule_pt_external_protocol=$(echo $rule_pt_external_protocol |tr '[A-Z]' '[a-z]')
	fi

	list_contains tri_proto ${rule_pt_trigger_protocol}  || return
	list_contains pub_proto ${rule_pt_external_protocol} || return

	nat__do_pt_rule ()
	{
		local tri_proto=$1
		local pub_proto=$2
		local iface=$3
		
		for tri_port in $rule_pt_trigger_port; do		
			local tri_port_start=${tri_port%-*}
			local tri_port_end=${tri_port#*-}

			for ex_port in $rule_pt_external_port; do			
				local ex_port_start=${ex_port%-*}
				local ex_port_end=${ex_port#*-}
				
				if [[ -n "$tri_port_start" && -n "$tri_port_end" && -n "$ex_port_start" && -n "$ex_port_end" ]]; then
					local ex_ports=${ex_port_start}-${ex_port_end}
					local tri_ports=${tri_port_start}-${tri_port_end}

					if [[ "${ex_port_start}" -gt "${ex_port_end}" ]]; then
						ex_ports=${ex_port_end}-${ex_port_start}
					fi
					if [[ "${tri_port_start}" -gt "${tri_port_end}" ]]; then
						tri_ports=${tri_port_end}-${tri_port_start}
					fi

					# Build Filter Rules
					local list=${tri_proto}
					[[ "$tri_proto" == "all" ]] && list="tcp udp"
					for pro in $list; do
						nat_filter_add lan $MOD_PT "-A" "-m comment --comment $rule_pt_name -p $pro -j TRIGGER \
							--trigger-type out --trigger-proto $pub_proto --trigger-match $tri_ports --trigger-relate $ex_ports"
					done

					##### save the valid iface list for PT-init-bottom half
					list_contains VALID_PT_IFACES $iface || append VALID_PT_IFACES $iface
				fi
			done
		done
	}

	if [[ "$rule_pt_enable" == "on" ]]; then
		# Only for the first connection.
		for zone in $rule_pt_interface; do
			[ -z "$zone" ] && continue
			local iface=$(zone_get_effect_ifaces "${zone}" 2>/dev/null)
			local if_ip=$(uci_get_state nat env "${iface}_ip")
			if [[ -n "$if_ip" ]]; then
				nat__do_pt_rule $rule_pt_trigger_protocol $rule_pt_external_protocol $iface
			fi
		done
	fi
}

nat_post_load_rule_pt()
{
	for iface in $VALID_PT_IFACES; do
		local device=$(uci_get_state nat env ${iface}_dev)
		local if_ip=$(uci_get_state nat env "${iface}_ip")
		if [[ -n "$device" && -n "if_ip" && "$if_ip" != "0.0.0.0" ]]; then
			nat_filter_add $iface $MOD_PT "-A" "-j TRIGGER --trigger-type in"
			nat_prerouting_add $MOD_PT "-A" "-d $if_ip -j TRIGGER --trigger-type dnat"
		fi
	done
	unset VALID_PT_IFACES
}

nat_flush_rule_pt()
{
	nat_prerouting_flush ${MOD_PT}

	local if_list=$(uci_get_state nat env if_list)
	if [[ -n "$if_list" ]]; then
		for iface in $if_list; do
			[[ -n "$iface" ]] && nat_filter_flush ${MOD_PT} $iface
		done
	fi
}

nat_rule_pt_operation()
{
	local operation=$1
	NAT_LOG_PRINT "@ enter Port Triggering"
	case $operation in
		start)
			# NAT_LOG_PRINT "  flusing old Port Triggering rules"
			# nat_flush_rule_pt

			NAT_LOG_PRINT "  building new Port Triggering rules"
			config_foreach nat_load_rule_pt rule_pt
			nat_post_load_rule_pt
		;;
		stop)
			NAT_LOG_PRINT "  flusing old Port Triggering rules"
			nat_flush_rule_pt
		;;
	esac
}
