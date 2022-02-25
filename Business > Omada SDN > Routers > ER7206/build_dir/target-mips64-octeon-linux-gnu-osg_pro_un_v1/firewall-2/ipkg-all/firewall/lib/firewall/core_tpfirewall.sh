#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     nat.init
# brief
# author   Chen chen
# version  1.0.0
# date     05June15
# histry   arg 1.0.0, 05June15, Chen chen, Create the file.

. /lib/zone/zone_api.sh
. /lib/functions/network.sh

fw_load_vpn()
{
	# load ipsec and l2tp
	iptables -w -N ipsec_forward_rule
	iptables -w -A forwarding_rule -j ipsec_forward_rule

	# used for l2tp and pptp vpn
	iptables -w -N ppp_forward_rule
	iptables -w -A forwarding_rule -j ppp_forward_rule

	iptables -w -N local_service_rule
	iptables -w -A local_service_rule -p esp -j ACCEPT
	iptables -w -A input_rule -j local_service_rule

	iptables -w -t mangle -A INPUT -m policy --dir in --pol ipsec --proto ah  -j ipsecmark
	iptables -w -t mangle -A INPUT -m policy --dir in --pol ipsec --proto esp -j ipsecmark

	iptables -w -N zone_vpn_forward
	iptables -w -A forward -j zone_vpn_forward
	
	#used for openvpn
	#bind when wan create
	iptables -w -N zone_wan_openvpn

	iptables -w -N openvpn_forwarding_rule
	iptables -w -A forwarding_rule -j openvpn_forwarding_rule

	iptables -w -t nat -N openvpn_prerouting_rule
	iptables -w -t nat -A PREROUTING -j openvpn_prerouting_rule

	iptables -w -t nat -N openvpn_postrouting_rule
	iptables -w -t nat -I POSTROUTING -j openvpn_postrouting_rule
	
	#set forwarding mark for vpn/ip rule: 0x20000
	iptables -w -t mangle -N VPN_FORWARD_RULE
	iptables -w -t mangle -A PREROUTING -j VPN_FORWARD_RULE
	iptables -w -t mangle -N VPN_FORWARD_MARK
	iptables -w -t mangle -N VPN_ROUTING_MARK
	iptables -w -t mangle -A VPN_FORWARD_RULE -j VPN_FORWARD_MARK
	iptables -w -t mangle -A FORWARD -j VPN_ROUTING_MARK
	iptables -w -t mangle -A VPN_FORWARD_RULE -m mark --mark 0x20000/0x20000 -j RETURN
}

fw_load_manage_vlan()
{
	local mvlan=$(uci get network.lan.manage_vid)

	config_load remote_mngt
	set_mngt_vlan() {
		local iface=$(uci get remote_mngt.$1.iface)
		[ "$iface" = "lan" ] && {
			local vlan=$(uci get remote_mngt.$1.mvlan)
			[ "$vlan" != "$2" ] && {
				uci set remote_mngt.$1.mvlan=$2
				uci commit
			}
		}
	}

	[ -n "$mvlan" -a "$(vlanctrl vlan_dump ${mvlan})" = "{}" ]  && mvlan=""

	config_foreach set_mngt_vlan mngt_iface "$mvlan"

	/etc/init.d/remote_mngt restart
}

fw_load_sfe()
{
	if ! iptables -w -t mangle -C sfe_mark -j CONNEXTMARK --set-mark 0x8/0x8 2>/dev/null; then
		iptables -w -t mangle -N sfe_mark
		iptables -w -t mangle -A sfe_mark -j EXTMARK --or-mark 0x8
		iptables -w -t mangle -A sfe_mark -m connextmark --mark 0x8/0x8 -j RETURN
		iptables -w -t mangle -A sfe_mark -j CONNEXTMARK --set-mark 0x8/0x8 
	fi
	if ! iptables -w -t mangle -C hwnat_mark -j CONNEXTMARK --set-mark 0x4/0x4 2>/dev/null; then
		iptables -w -t mangle -N hwnat_mark
		iptables -w -t mangle -A hwnat_mark -j EXTMARK --or-mark 0x4
		iptables -w -t mangle -A hwnat_mark -m connextmark --mark 0x4/0x4 -j RETURN
		iptables -w -t mangle -A hwnat_mark -j CONNEXTMARK --set-mark 0x4/0x4 
		iptables -w -t mangle -I sfe_mark 1 -j hwnat_mark
	fi
	iptables -w -t mangle -I FORWARD 1 -j CONNEXTMARK --set-mark 0x0/0xc
}

fw_add_passthrough_manage_devs()
{
	local manage_devs_chain="manage_devs"
	iptables -w -I ${manage_devs_chain} 1 $@ -j RETURN
}

fw_del_passthrough_manage_devs()
{
	local manage_devs_chain="manage_devs"
	iptables -w -D ${manage_devs_chain} $@ -j RETURN
}

fw_del_passthrough_manage_devs_by_label()
{
	local manage_devs_chain="manage_devs"
	local label1="$1"
	local label2="$2"
	local nums=$(iptables -w -vnL ${manage_devs_chain} --line-numbers | grep "\b${label1}\b" | grep "\b${label2}\b" | cut -d ' ' -f 1)
	while [ -n "${nums}" ]; do
		for num in $nums;
		do
			iptables -w -D ${manage_devs_chain} ${num}
			break; # just delete the first once.
		done
		nums=$(iptables -w -vnL ${manage_devs_chain} --line-numbers | grep "\b${label1}\b" | grep "\b${label2}\b" | cut -d ' ' -f 1)
	done
}

fw_install_passthrough_icmp()
{
	local action="$1"
	local ifname="$2"
        local srcitf="$3"

	network_get_ipaddr srcip ${srcitf}
	case "${action}" in
		"add" )
			fw_add_passthrough_manage_devs -o ${ifname} -s ${srcip} -p icmp
		;;
		"del" )
			fw_del_passthrough_manage_devs_by_label ${ifname} "icmp"
		;;
	esac
}

fw_install_passthrough_dns()
{
	local action="$1"
	local ifname="$2"
	local srcitf="$3"

	network_get_ipaddr srcip ${srcitf}
	case "${action}" in
		"add" )
			fw_add_passthrough_manage_devs -o ${ifname} -s ${srcip} -p udp --dport 53
		;;
		"del" )
			fw_del_passthrough_manage_devs_by_label ${ifname} "dpt:53"
		;;
	esac

	# online check
	fw_install_passthrough_icmp "$@"
}

fw_event_manage_dev()
{
	local manage_devs_chain="manage_devs"
	local manage_devs="${1%%:*}"
	local updown="${1##*:}"

	if ! iptables -w -C ${manage_devs_chain} -j DROP 2>/dev/null; then
		iptables -w -N ${manage_devs_chain}
		iptables -w -A output -j ${manage_devs_chain}
		iptables -w -A ${manage_devs_chain} -p tcp --dport 1723 -j RETURN
		iptables -w -A ${manage_devs_chain} -p udp -m multiport --dports 1701,67,20001 -j RETURN
		iptables -w -A ${manage_devs_chain} -j DROP
	fi

	case "${updown}" in
		"up")
			# setup new rule
			if ! iptables -w -C ${manage_devs_chain} -o ${manage_devs} -j RETURN 2>/dev/null; then
				iptables -w -I ${manage_devs_chain} 1 -o ${manage_devs} -j RETURN
			fi
			;;
		"down")
			# clean up old rule
			iptables -w -D ${manage_devs_chain} -o ${manage_devs} -j RETURN 2>/dev/null
			;;
		*)
			;;
	esac
	true ;
}

fw_load_manage_devs()
{
	network_flush_cache
	for zone in $(zone_get_zonelist) ; do
		local ifaces=$(zone_get_wan_ifaces $zone)

		for iface in ${ifaces} ; do
			if network_is_up ${iface}; then
				local device=$(zone_get_device_byif $iface)
				fw_event_manage_dev "${device}:up"
			fi
		done
	done

	if network_is_up "loopback"; then
		fw_event_manage_dev "lo:up"
	fi
}

fw_dual_ipt()
{
	iptables $@
	ip6tables $@
}

fw_load_service_default()
{
	fw_dual_ipt -w -N service_default
	fw_dual_ipt -w -A service_default -j reject
	fw_dual_ipt -w -A input_default -p tcp -m multiport --dports 22,23,53,80,443,1723,1900,2026,8080,20002 -j service_default
	fw_dual_ipt -w -A input_default -p udp -m multiport --dports 53,67,137,138,161,500,1701,1900,4500,20002 -j service_default
}

#0x10000
fw_load_forwarding_mark()
{
	forwarding_mark=$((1<<16))
	fw_dual_ipt -t mangle -w -I FORWARD 1 -j CONNMARK --or-mark ${forwarding_mark}
	fw_dual_ipt -t mangle -w -I FORWARD 1 -j MARK --or-mark ${forwarding_mark}
}
