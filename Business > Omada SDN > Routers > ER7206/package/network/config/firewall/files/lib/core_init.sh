# Copyright (C) 2009-2011 OpenWrt.org
# Copyright (C) 2008 John Crispin <blogic@openwrt.org>

FW_INITIALIZED=
FW_DEFAULTS_APPLIED=

FW_DEFAULT_INPUT_POLICY=REJECT
FW_DEFAULT_OUTPUT_POLICY=REJECT
FW_DEFAULT_FORWARD_POLICY=REJECT

fw_dual_ipt()
{
	iptables $@
	ip6tables $@
}

fw_clear()
{
	local policy=$1

	fw_set_filter_policy $policy

	local tab
	for tab in f r m; do
		fw del i $tab
	done
}

fw_set_filter_policy()
{
	local policy=$1
	local chn tgt
	for chn in INPUT OUTPUT FORWARD; do
		eval "tgt=\${policy:-\${FW_DEFAULT_${chn}_POLICY}}"
		[ $tgt == "REJECT" ] && tgt=reject
		[ $tgt == "ACCEPT" -o $tgt == "DROP" ] || {
			fw_dual_ipt -w -A $chn -j $tgt
			tgt=DROP
		}
		fw_dual_ipt -w -P $chn $tgt
	done
}

fw_build_defaults()
{
	fw_config_get_section "$1" defaults { \
		string input $FW_DEFAULT_INPUT_POLICY \
		string output $FW_DEFAULT_OUTPUT_POLICY \
		string forward $FW_DEFAULT_FORWARD_POLICY \
		boolean drop_invalid 0 \
		boolean syn_flood 0 \
		boolean synflood_protect 0 \
		string synflood_rate 2000 \
		string synflood_burst 3500 \
		boolean tcp_syncookies 1 \
		boolean tcp_ecn 0 \
		boolean tcp_westwood 0 \
		boolean tcp_window_scaling 1 \
		boolean accept_redirects 0 \
		boolean accept_source_route 0 \
		boolean custom_chains 1 \
		boolean disable_ipv6 0 \
	} || return
	if [[ -n "$FW_DEFAULTS_APPLIED" ]]; then
		fw_log error "duplicate defaults section detected, skipping"
		return 1
	fi
	FW_DEFAULTS_APPLIED=1

	# Set sysctl
	{
		sysctl -w net.ipv4.tcp_syncookies=$defaults_tcp_syncookies
		sysctl -w net.ipv4.tcp_ecn=$defaults_tcp_ecn
		sysctl -w net.ipv4.tcp_westwood=$defaults_tcp_westwood
		sysctl -w net.ipv4.tcp_window_scaling=$defaults_tcp_window_scaling
		sysctl -w net.ipv4.conf.all.accept_redirects=$defaults_accept_redirects
		sysctl -w net.ipv6.conf.all.accept_redirects=$defaults_accept_redirects
		sysctl -w net.ipv4.conf.all.accept_source_route=$defaults_accept_source_route
		sysctl -w net.ipv6.conf.all.accept_source_route=$defaults_accept_source_route
	} >/dev/null 2>/dev/null

	fw_dual_ipt -w -A INPUT   -m conntrack --ctstate RELATED,ESTABLISHED -j ACCEPT
	fw_dual_ipt -w -A OUTPUT  -m conntrack --ctstate RELATED,ESTABLISHED -j ACCEPT
	fw_dual_ipt -w -A FORWARD -m conntrack --ctstate RELATED,ESTABLISHED -j ACCEPT

	if [[ "$defaults_drop_invalid" == 1 ]]; then
		fw_dual_ipt -w -A INPUT   -m conntrack --ctstate INVALID -j DROP
		fw_dual_ipt -w -A OUTPUT  -m conntrack --ctstate INVALID -j DROP
		fw_dual_ipt -w -A FORWARD -m conntrack --ctstate INVALID -j DROP
	fi

	fw_dual_ipt -w -A INPUT  -i lo -j ACCEPT
	fw_dual_ipt -w -A OUTPUT -o lo -j ACCEPT

	if [[ "$defaults_syn_flood" == 1 ]]; then
		[ "${defaults_synflood_rate%/*}" == "$defaults_synflood_rate" ] && \
			defaults_synflood_rate="$defaults_synflood_rate/second"

		fw_dual_ipt -w -N syn_flood
		fw_dual_ipt -w -A syn_flood -p tcp --syn \
			-m limit --limit "${defaults_synflood_rate}" --limit-burst "${defaults_synflood_burst}" -j RETURN
		fw_dual_ipt -w -A syn_flood -j DROP
		fw_dual_ipt -w -A INPUT -p tcp --syn -j syn_flood
	fi

	if [[ "$defaults_custom_chains" == 1 ]]; then
		fw_dual_ipt -w -N input_rule
		fw_dual_ipt -w -N output_rule
		fw_dual_ipt -w -N forwarding_rule
		#fw_dual_ipt -w -N forward_auth
		fw_dual_ipt -w -N forward_session_limits
		fw_dual_ipt -w -A INPUT   -j input_rule
		fw_dual_ipt -w -A OUTPUT  -j output_rule
		fw_dual_ipt -w -A FORWARD -j forward_session_limits
		fw_dual_ipt -w -A FORWARD -j forwarding_rule
		#fw_dual_ipt -w -A FORWARD -j forward_auth
	fi

	fw_dual_ipt -w -N input
	fw_dual_ipt -w -N output
	fw_dual_ipt -w -N forward
	fw_dual_ipt -w -A INPUT   -j input
	fw_dual_ipt -w -A OUTPUT  -j output
	fw_dual_ipt -w -A FORWARD -j forward

	fw_dual_ipt -w -N input_default
	fw_dual_ipt -w -N output_default
	fw_dual_ipt -w -N forward_default
	
	fw_dual_ipt -w -A INPUT   -j input_default
	fw_dual_ipt -w -A OUTPUT  -j output_default
	fw_dual_ipt -w -A FORWARD -j forward_default

	fw_dual_ipt -w -I input_default 1 -i br-lan -j RETURN

	fw_dual_ipt -w -N reject
	fw_dual_ipt -w -A reject -p tcp -j REJECT --reject-with tcp-reset
	fw_dual_ipt -w -A reject -j REJECT --reject-with port-unreach

	fw_set_filter_policy ACCEPT
}

fw_set_iface_mss()
{
	local iface=$1
	local device=$2
	local ipv6=$3
	local fam=4
	local cur_mtu=$(uci get network.$iface.mtu)
	local cur_mru=$(uci get network.$iface.mru)
	local cur_mss=1460
	local ipt_app="iptables"

	cur_mtu=${cur_mtu:=$cur_mru}
	cur_mtu=${cur_mtu:=1500}
	if [[ -n "$ipv6" ]]; then
		cur_mss=$(($cur_mtu-60))
		fam=6
		ipt_app="ip6tables"
	else
		cur_mss=$(($cur_mtu-40))
	fi

	if ! $ipt_app -w -t mangle -C zone_MSSFIX -i $device -j zone_${iface}_MSSFIX 2>/dev/null; then
		$ipt_app -w -t mangle -N zone_${iface}_MSSFIX
		$ipt_app -w -t mangle -A zone_${iface}_MSSFIX -p tcp -m tcp --tcp-flags SYN,RST SYN -j TCPMSS --set-mss ${cur_mss}
		$ipt_app -w -t mangle -A zone_${iface}_MSSFIX -o $device -p tcp -m tcp --tcp-flags SYN,RST SYN -j TCPMSS --clamp-mss-to-pmtu
		$ipt_app -w -t mangle -I zone_MSSFIX 1 -o $device -j zone_${iface}_MSSFIX
		$ipt_app -w -t mangle -I zone_MSSFIX 1 -i $device -j zone_${iface}_MSSFIX
	fi
}

fw_build_zone_iface()
{
	local iface=$1
	local device=$2
	local zone=$3

	# to check if the chains had been built
	iptables -w -C forward -i $device -j zone_${iface}_forward 2>/dev/null && return

	# add basic chains
	iptables -w -N zone_${iface}_forward
	iptables -w -N zone_${iface}_input
	iptables -w -N zone_${iface}_output
	iptables -w -I forward 1 -i $device -j zone_${iface}_forward
	iptables -w -A input  -i $device -j zone_${iface}_input
	iptables -w -A output -o $device -j zone_${iface}_output

	# accept icmp pkts
	iptables -w -A zone_${iface}_input -p icmp -m icmp --icmp-type 8 -j ACCEPT

	# for wan, build mss chains
	if [[ "$iface" != "lan" ]]; then
		if [[ "$zone" != "VPN" ]]; then
			fw_set_iface_mss $iface $device
			iptables -w -A zone_${iface}_input -j zone_wan_openvpn

			iptables -w -N zone_wan_lan_protection
			iptables -w -A zone_${iface}_input -j zone_wan_lan_protection
			iptables -w -A zone_${iface}_forward -j ipsecmark --type use
			iptables -w -A zone_${iface}_forward -o br-lan -j DROP
			iptables -w -A zone_${iface}_forward -p udp --sport 67 --dport 68 -j DROP
			iptables -w -A zone_${iface}_forward -p udp --sport 68 --dport 67 -j DROP
		fi
	# for lan, build lan protection chains
	else
		local if_ipaddr=""
		local if_mask=""
		local lan_ip_limit=$(uci get firewall.global.lan_ip_limit)
		local remote_access_lan=$(uci get firewall.global.remote_access_lan)
		network_get_ipaddr if_ipaddr "$iface"
		network_get_netmask if_mask "$iface"

		iptables -w -N zone_lan_ip_limit
		if [[ -n "$if_ipaddr" && -n "$if_mask" ]]; then                  
			if [[ "$remote_access_lan" == "0" ]]; then
				iptables -w -A zone_wan_lan_protection -j ipsecmark --type use
				iptables -w -A zone_wan_lan_protection -d ${if_ipaddr}/32 -j DROP
			fi
			if [[ "$lan_ip_limit" == "1" ]]; then
				iptables -w -A zone_lan_ip_limit ! -s ${if_ipaddr}/${if_mask} -j DROP
				iptables -w -A zone_lan_forward -j zone_lan_ip_limit
			fi
		fi
		# for lan, build service default targets
		fw_dual_ipt -w -I input_default 1 -i $device -j RETURN
	fi
}

fw_flush_zone_iface()
{
	local iface=$1
	local device=$2

	# to check if the chains had been built
	iptables -w -C forward -i $device -j zone_${iface}_forward 2>/dev/null || return

	if [[ "$iface" != "lan" ]]; then
		iptables -w -t mangle -F zone_${iface}_MSSFIX
		iptables -w -t mangle -D zone_MSSFIX -o $device -j zone_${iface}_MSSFIX
		iptables -w -t mangle -D zone_MSSFIX -i $device -j zone_${iface}_MSSFIX
		iptables -w -t mangle -X zone_${iface}_MSSFIX
		iptables -w -D zone_${iface}_input -j zone_wan_openvpn

	else
		iptables -w -F zone_wan_lan_protection
		iptables -w -F zone_lan_ip_limit
		iptables -w -D zone_lan_forward -j zone_lan_ip_limit
		iptables -w -X zone_lan_ip_limit
		fw_dual_ipt -w -D input_default -i $device -j RETURN
	fi

	iptables -w -F zone_${iface}_forward
	iptables -w -F zone_${iface}_input
	iptables -w -F zone_${iface}_output
	iptables -w -D forward -i $device -j zone_${iface}_forward
	iptables -w -D input   -i $device -j zone_${iface}_input
	iptables -w -D output  -o $device -j zone_${iface}_output
	iptables -w -X zone_${iface}_forward
	iptables -w -X zone_${iface}_input
	iptables -w -X zone_${iface}_output
}

fw_build_zones()
{
	iptables -w -t mangle -N zone_MSSFIX
	iptables -w -t mangle -I FORWARD 1 -j zone_MSSFIX
	iptables -w -N zone_wan_lan_protection

	config_load network

	local zone_list=$(zone_get_zonelist)
	for zone in $zone_list; do
		local if_list=""
		local ifaces=$(zone_get_wan_ifaces "${zone}")
		for iface in $ifaces; do
			local if_ipaddr=""
			network_get_ipaddr if_ipaddr "$iface"		
			[[ -z "$if_ipaddr" ]] && continue
			if_list="$iface $if_list"

			local device=$(zone_get_device_byif "$iface")
			uci_set_state firewall core ${iface}_if "$device"
			uci_set_state firewall core ${iface}_ip "$if_ipaddr"
			fw_build_zone_iface $iface $device $zone
		done
		[[ -n "$if_list" ]] && uci_set_state firewall core ${zone}_ifaces "$if_list"
	done
}

fw_build_zones_v6()
{
	ip6tables -w -t mangle -N zone_MSSFIX
	ip6tables -w -t mangle -I FORWARD 1 -j zone_MSSFIX
	# fw entries will be built in function fw_event_interface_v6
}

fw_event_interface()
{
	config_load network

	local iface=$1
	local action=$2
	local device=$3
	local zone=$(zone_get_zone_byif $iface)

	[[ -z "$iface" || -z "$zone" || -z "$action" ]] && return 1

	if [[ "$action" == "del" ]]; then
		local ifaces=$(uci_get_state firewall core ${zone}_ifaces)
		local if_list=""
		for viface in $ifaces; do
			if [ "$viface" != "$iface" ]; then
				if_list=$viface" "$if_list
			fi
		done
		[ -z "$device" ] && device=$(uci_get_state firewall core ${iface}_if)
		fw_flush_zone_iface "$iface" "$device"
		uci_revert_state firewall core ${iface}_if
		uci_revert_state firewall core ${iface}_ip
		uci_revert_state firewall core ${zone}_ifaces
		uci_set_state firewall core ${zone}_ifaces "$if_list"

	elif [[ "$action" == "add" ]]; then
		local ifaces=$(uci_get_state firewall core ${zone}_ifaces)
		local if_list="$iface $ifaces"

		[ -z "$device" ] && device=$(zone_get_device_byif $iface)
		for viface in $ifaces; do
			if [ "$viface" == "$iface" ]; then
				vdevice=$(uci_get_state firewall core ${iface}_if)
				[ -z "$vdevice" ] && vdevice="$device"
				fw_flush_zone_iface "$iface" "$vdevice"
				if_list="$ifaces"
			fi
		done

		network_get_ipaddr if_ipaddr "$iface"
		uci_set_state firewall core ${iface}_if "$device"
		uci_set_state firewall core ${iface}_ip "$if_ipaddr"

		fw_build_zone_iface "$iface" "$device" "$zone"
		if [[ -n "$if_list" ]]; then
			uci_revert_state firewall core ${zone}_ifaces
			uci_set_state firewall core ${zone}_ifaces "$if_list"
		fi
	fi
}

fw_event_interface_v6()
{
	config_load network

	local iface=$1
	local action=$2
	local device=$3

	[[ -z "$iface" || -z "$action" ]] && return 1

	[[ -z "$device" ]] && device=$(zone_get_device_byif $iface)

	if [[ "$action" == "del" ]]; then
		if [[ "$iface" != "lanv6" ]]; then
			if ip6tables -w -t mangle -C zone_MSSFIX -i $device -j zone_${iface}_MSSFIX 2>/dev/null; then
				ip6tables -w -t mangle -F zone_${iface}_MSSFIX
				ip6tables -w -t mangle -D zone_MSSFIX -o $device -j zone_${iface}_MSSFIX
				ip6tables -w -t mangle -D zone_MSSFIX -i $device -j zone_${iface}_MSSFIX
				ip6tables -w -t mangle -X zone_${iface}_MSSFIX
			fi
		fi
	elif [[ "$action" == "add" ]]; then
		if [[ "$iface" != "lanv6" ]]; then
			fw_set_iface_mss $iface $device ipv6
		fi
	fi
}
