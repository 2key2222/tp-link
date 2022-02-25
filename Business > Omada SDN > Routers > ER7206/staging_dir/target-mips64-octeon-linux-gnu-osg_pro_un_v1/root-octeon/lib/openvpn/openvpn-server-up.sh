#!/bin/sh
. /lib/functions.sh
. /lib/functions/service.sh
. /lib/openvpn/openvpn-common.sh
. /lib/zone/zone_api.sh
. /lib/functions/network.sh
. /lib/firewall/fw.sh

IFNAME=$1
VLOCALIP=$4

openvpn_server_up_hook()
{
	local indexname=
    local proto=
    local port=
	local local_network=
	#local wans=
	
	indexname=$(echo $IFNAME | tr -cd "[0-9]")
	echo "openvpn_server_up $IFNAME $indexname" >  /dev/console

	uci set openvpn.server${indexname}.vlocalip=${VLOCALIP}
	uci commit openvpn
	
	config_load 'openvpn'	
	config_get port "server$indexname" port
	config_get proto "server$indexname" proto
	config_get local_network "server$indexname" local_network
	
	#FORWORDING
	fw add 4 n openvpn_prerouting_rule ACCEPT { "-p $proto -m $proto --dport $port -m comment --comment $IFNAME" }	
    fw add 4 f openvpn_forwarding_rule ACCEPT { "-o $IFNAME -m conntrack --ctstate RELATED,ESTABLISHED" }
	for local in ${local_network} 
	do 
		fw add 4 f openvpn_forwarding_rule ACCEPT { "-i br-lan -o $IFNAME -s $local" }
		fw add 4 f openvpn_forwarding_rule ACCEPT { "-i $IFNAME -o br-lan -d $local" }
	done
	
	nbptc up ${IFNAME} "ovpn"
}

openvpn_server_up_hook