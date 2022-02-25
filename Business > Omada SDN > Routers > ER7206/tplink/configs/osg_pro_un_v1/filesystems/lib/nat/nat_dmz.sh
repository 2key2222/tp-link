#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file      nat_mod_dmz.sh
# brief    
# author    Chen chen
# version   1.1.0
# date      23Apr15
# history   arg 1.0.0, 23Apr15, Chen chen, Create the file.
#           arg 1.1.0, 21Dec17, Zhangzhongwei, Rewrite the file.

DMZ_ENABLE=0

TCP_SERVICE_LIST="http https pptp ssh"
UDP_SERVICE_LIST="ike l2tp sae"

nat_service_to_port()
{ #$service
	local port http_list https_list ssh_list
	case "$1" in
	http|HTTP|Http)
		#port="$(uci get uhttpd.main.listen_http |cut -d : -f 5)"
		port="$(uci_get_state uhttpd main listen_http |cut -d : -f 5)"
		[ -z "$port" ] && port=80
		;;
	https|HTTPS|Https)
		#port="$(uci get uhttpd.main.listen_https |cut -d : -f 5)"
		port="$(uci_get_state uhttpd main listen_https |cut -d : -f 5)"
		[ -z "$port" ] && port=443
		;;
	pptp|Pptp|PPTP)
		port=1723  #default port
		;;
	l2tp|L2TP|L2tp)
		port=1701  #default port
		;;
	IKE|ike|Ike)
		port=500  #default port
		;;
	ssh|SSH|Ssh)
		port=$(uci_get administration port SSH)
		[ -z "$port" ] && port=22
		;;
	sae|SAE|Sae)
		port=4500  #default port
		;;
	*) 
		return 1
		;;
	esac

	echo "$port"
	return 0
}

nat_dmz_service_ports()
{
	local service_list=$@
	local ports port
	for ser in $service_list;do
		port=$(nat_service_to_port $ser)
		ports=${ports:+$ports,}${port:+$port}
	done
	echo $ports
	return 0
}

nat_config_dmz()
{
	nat_config_get_section "$1" rule_dmz { \
		string name "" \
		string enable "" \
		string ipaddr "" \
		string interface "" \
		string fromAddr "" \
		string natIndex "" \
	}
}

nat_post_load_rule_dmz()
{
	if [[ "$DMZ_ENABLE" -eq 1 ]]; then
		# local tcp_ports=$(nat_dmz_service_ports $TCP_SERVICE_LIST)
		# local udp_ports=$(nat_dmz_service_ports $UDP_SERVICE_LIST)
		# nat_prerouting_add $MOD_DMZ "-I 1" "-p udp -m multiport --dport $udp_ports -j RETURN"
		# nat_prerouting_add $MOD_DMZ "-I 1" "-p tcp -m multiport --dport $tcp_ports -j RETURN"
		# nat_prerouting_add $MOD_DMZ "-I 1" "-p 47 -j RETURN"
		# nat_prerouting_add $MOD_DMZ "-I 1" "-p 50 -j RETURN"
		# nat_prerouting_add $MOD_DMZ "-I 1" "-p 51 -j RETURN"
		nat_prerouting_add $MOD_DMZ "-I 1" "-p icmp -j RETURN"
	fi
	unset DMZ_ENABLE
}

nat_load_rule_dmz()
{
	nat_config_dmz "$1"

	if [[ "$rule_dmz_enable" == "on" ]]; then
		for zone in $rule_dmz_interface; do
			[ -z "$zone" ] && continue
			local iface=$(zone_get_effect_ifaces "${zone}" 2>/dev/null)
			local device=$(zone_get_device_byif "${iface}")
			local if_ip=$(uci_get_state nat env ${iface}_ip)
			local ipgroup_src=$rule_dmz_fromAddr
			local index=$rule_dmz_natIndex

			if [[ "$ipgroup_src" != "" ]]; then
				if [[ -n "$iface" && -n "$device" && -n "$if_ip" && "$if_ip" != "0.0.0.0" ]]; then
					# Build Filter Rules
					nat_filter_add $iface $MOD_DMZ "-A" "-m comment --comment $rule_dmz_name -m set --match-set $ipgroup_src src \
						-d $rule_dmz_ipaddr -m conntrack --ctstate DNAT -j ACCEPT"

					# No need to specify INPUT device, for DMZ loopback. Packets from other INPUT devices would be drop in the filter table.

					# Build prerouting Rules, for DNAT
					nat_prerouting_add $MOD_DMZ "-A" "-m comment --comment $rule_dmz_name -d $if_ip -m set --match-set $ipgroup_src src \
						-m socket --nowildcard -j RETURN ${index:+--nat-index $index}"
					nat_prerouting_add $MOD_DMZ "-A" "-d $if_ip -i $device -p 50 -m esp --espspi 0:0 -m set --match-set $ipgroup_src src -j RETURN"
					nat_prerouting_add $MOD_DMZ "-A" "-m comment --comment $rule_dmz_name -d $if_ip -i $device -m set --match-set $ipgroup_src src \
						-j DNAT --to-destination $rule_dmz_ipaddr ${index:+--nat-index $index}"
					nat_prerouting_add $MOD_DMZ "-A" "-m comment --comment $rule_dmz_name -d $if_ip -m set --match-set $ipgroup_src src \
						-j DNAT --to-destination $rule_dmz_ipaddr -m extmark --extmark ${NAPT_DEVICE_MARK_LANIN}/${NAPT_DEVICE_MARK_LANIN} ${index:+--nat-index $index}"
						
					# Build postrouting Rules, for Loopback
					nat_postrouting_add $MOD_DMZ "-A" "-m comment --comment $rule_dmz_name -d ${rule_dmz_ipaddr}/32 -m set --match-set $ipgroup_src src \
						-j SNAT --to ${if_ip} -m extmark --extmark ${NAPT_DEVICE_MARK_LANIN}/${NAPT_DEVICE_MARK_LANIN} -m conntrack --ctstate DNAT ${index:+--nat-index $index}"

					DMZ_ENABLE=1
				fi
			else
				if [[ -n "$iface" && -n "$device" && -n "$if_ip" && "$if_ip" != "0.0.0.0" ]]; then
					# Build Filter Rules
					nat_filter_add $iface $MOD_DMZ "-A" "-m comment --comment $rule_dmz_name -d $rule_dmz_ipaddr \
						-m conntrack --ctstate DNAT -j ACCEPT"

					# No need to specify INPUT device, for DMZ loopback. Packets from other INPUT devices would be drop in the filter table.
					
					# Build prerouting Rules, for DNAT
					nat_prerouting_add $MOD_DMZ "-A" "-m comment --comment $rule_dmz_name -d $if_ip \
						-m socket --nowildcard -j RETURN ${index:+--nat-index $index}"
					nat_prerouting_add $MOD_DMZ "-A" "-d $if_ip -i $device -p 50 -m esp --espspi 0:0 -j RETURN"
					nat_prerouting_add $MOD_DMZ "-A" "-m comment --comment $rule_dmz_name -d $if_ip -i $device \
						-j DNAT --to-destination $rule_dmz_ipaddr ${index:+--nat-index $index}"
					nat_prerouting_add $MOD_DMZ "-A" "-m comment --comment $rule_dmz_name -d $if_ip -j DNAT --to-destination $rule_dmz_ipaddr \
						-m extmark --extmark ${NAPT_DEVICE_MARK_LANIN}/${NAPT_DEVICE_MARK_LANIN} ${index:+--nat-index $index}"
						
					# Build postrouting Rules, for Loopback
					nat_postrouting_add $MOD_DMZ "-A" "-m comment --comment $rule_dmz_name -d ${rule_dmz_ipaddr}/32 -j SNAT --to ${if_ip} \
						-m extmark --extmark ${NAPT_DEVICE_MARK_LANIN}/${NAPT_DEVICE_MARK_LANIN} -m conntrack --ctstate DNAT ${index:+--nat-index $index}"

					DMZ_ENABLE=1
				fi
			fi
		done
	fi
}

nat_flush_rule_dmz()
{
	nat_prerouting_flush ${MOD_DMZ}
	nat_postrouting_flush ${MOD_DMZ}

	local if_list=$(uci_get_state nat env if_list)
	if [[ -n "$if_list" ]]; then
		for iface in $if_list; do
			if [[ -n "$iface" && "$iface" != "lan" ]]; then
				nat_filter_flush ${MOD_DMZ} $iface
			fi
		done
	fi
}

nat_rule_dmz_operation()
{
	local operation=$1
	NAT_LOG_PRINT "@ enter DMZ"
	case $operation in
		start)
			# NAT_LOG_PRINT "  flusing old DMZ rules"
			# nat_flush_rule_napt

			NAT_LOG_PRINT "  building new DMZ rules"
			config_foreach nat_load_rule_dmz rule_dmz
			nat_post_load_rule_dmz
		;;
		stop)
			NAT_LOG_PRINT "  flusing old DMZ rules"
			nat_flush_rule_dmz
		;;
	esac
}

