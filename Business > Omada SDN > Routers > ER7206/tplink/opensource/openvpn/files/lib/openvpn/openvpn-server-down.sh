#!/bin/sh
. /lib/functions.sh
. /lib/functions/service.sh
. /lib/openvpn/openvpn-common.sh
. /lib/zone/zone_api.sh
. /lib/functions/network.sh
. /lib/firewall/fw.sh

IFNAME=$1

openvpn_server_down_hook()
{
	local indexname=
	indexname=$(echo $IFNAME | tr -cd "[0-9]")
	echo "openvpn_server_down $IFNAME" >  /dev/console

	uci set openvpn.server${indexname}.vlocalip=""
	uci commit openvpn
	
	nums=$(iptables -w -nvL openvpn_forwarding_rule --line-numbers | grep "\b${IFNAME}\b" | cut -d ' ' -f 1)
	while [ -n "${nums}" ]; do
		for num in $nums;
		do
			iptables -w -D openvpn_forwarding_rule ${num}
			break; # just delete the first once.
		done
		nums=$(iptables -w -nvL openvpn_forwarding_rule --line-numbers | grep "\b${IFNAME}\b" | cut -d ' ' -f 1)
	done
	
	nums=$(iptables -w -t nat -nvL openvpn_prerouting_rule --line-numbers | grep "\b${IFNAME}\b" | cut -d ' ' -f 1)
	while [ -n "${nums}" ]; do
		for num in $nums;
		do
			iptables -w -t nat -D openvpn_prerouting_rule ${num}
			break; # just delete the first once.
		done
		nums=$(iptables -w -t nat -nvL openvpn_prerouting_rule --line-numbers | grep "\b${IFNAME}\b" | cut -d ' ' -f 1)
	done
	
	nbptc down ${IFNAME} "ovpn"
}

openvpn_server_down_hook