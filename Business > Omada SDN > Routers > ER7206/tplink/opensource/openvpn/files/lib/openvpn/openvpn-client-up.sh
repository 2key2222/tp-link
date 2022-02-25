#!/bin/sh
. /lib/functions.sh
. /lib/functions/service.sh
. /lib/openvpn/openvpn-common.sh
. /lib/zone/zone_api.sh
. /lib/functions/network.sh
. /lib/firewall/fw.sh

IFNAME=$1
VLOCALIP=$4
VREMOTEIP=$5
if [ ! -n "$7" ] ;then
        echo "no config file name"
        CONFIGFILENAME=${IFNAME}
else
        CONFIGFILENAME=$7
fi

openvpn_client_up_hook()
{
	local indexname=
    local proto=
    local port=
	local local_network=
	#local wans=
	
	indexname=$(echo $CONFIGFILENAME | tr -cd "[0-9]")
	echo "openvpn_client_up $IFNAME $indexname" >  /dev/console

	uci set openvpn.client${indexname}.dev=${IFNAME}
	uci set openvpn.client${indexname}.uptime=$(date +%s)
	uci set openvpn.client${indexname}.vlocalip=${VLOCALIP}
	uci set openvpn.client${indexname}.vremoteip=${VREMOTEIP}
	uci commit openvpn
	
	config_load 'openvpn'	
	config_get port "client$indexname" port
	config_get proto "client$indexname" proto
	config_get local_network "client$indexname" local_network
	config_get wans "client$indexname" wan
	
	#INPUT
	#for wan in ${wans} 
	#do 
	#	device=$(zone_get_wan_devices $wan)
	#	fw add 4 f zone_wan_openvpn ACCEPT { "-i $device -p $proto -m $proto --dport $port" }
	#done
	
	#FORWORDING
    fw add 4 f openvpn_forwarding_rule ACCEPT { "-o $IFNAME -m conntrack --ctstate RELATED,ESTABLISHED" }
	for local in ${local_network} 
	do 
		fw add 4 f openvpn_forwarding_rule ACCEPT { "-i br-lan -o $IFNAME -s $local" }
		fw add 4 f openvpn_forwarding_rule ACCEPT { "-i $IFNAME -o br-lan -d $local" }
		fw add 4 n openvpn_postrouting_rule MASQUERADE { "-s $local -o $IFNAME" }
	done
	
	nbptc up ${IFNAME} "ovpn"
}

openvpn_client_up_hook