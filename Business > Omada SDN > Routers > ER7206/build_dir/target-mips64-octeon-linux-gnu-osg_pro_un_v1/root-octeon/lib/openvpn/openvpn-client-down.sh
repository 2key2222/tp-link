#!/bin/sh
. /lib/functions.sh
. /lib/functions/service.sh
. /lib/openvpn/openvpn-common.sh
. /lib/zone/zone_api.sh
. /lib/functions/network.sh
. /lib/firewall/fw.sh

IFNAME=$1
if [ ! -n "$7" ] ;then
        echo "no config file name"
        CONFIGFILENAME=${IFNAME}
else
        CONFIGFILENAME=$7
fi

openvpn_client_down_hook()
{
	local indexname=
	indexname=$(echo $CONFIGFILENAME | tr -cd "[0-9]")
	echo "openvpn_client_down $IFNAME $indexname" >  /dev/console
	
	# prevent the recurrence of the same interface
	uci set openvpn.client${indexname}.dev=""
	uci set openvpn.client${indexname}.uptime=""
	uci set openvpn.client${indexname}.vlocalip=""
	uci set openvpn.client${indexname}.vremoteip=""
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
	
	nums=$(iptables -w -t nat -nvL openvpn_postrouting_rule --line-numbers | grep "\b${IFNAME}\b" | cut -d ' ' -f 1)
	while [ -n "${nums}" ]; do
		for num in $nums;
		do
			iptables -w -t nat -D openvpn_postrouting_rule ${num}
			break; # just delete the first once.
		done
		nums=$(iptables -w -t nat -nvL openvpn_postrouting_rule --line-numbers | grep "\b${IFNAME}\b" | cut -d ' ' -f 1)
	done
	
	nbptc down ${IFNAME} "ovpn"
}

openvpn_client_down_hook