#!/bin/sh
. /lib/zone/zone_api.sh

fw_check()
{
	local ret=$(vnete iptables -w -t $1 -C $2 $3 2>&1)
	[ -n "$ret" ] && return 0||return 1
}

add_subchain(){
	vnete iptables -w -t nat -N freeStrategy_url_backup >/dev/null 2>&1
	vnete iptables -w -t nat -F freeStrategy_url_backup
	#fw_check "nat" "PREROUTING" "-j freeStrategy_url_backup"
	#[ x$? == x0 ] && {
		# need to get rule number of wifidog chain
	#	vnete iptables -t nat -I PREROUTING -j freeStrategy_url_backup
	#}

	vnete iptables -w -N freeStrategy_url_backup >/dev/null 2>&1
	vnete iptables -w -F freeStrategy_url_backup
	#fw_check "filter" "FORWARD" "-j freeStrategy_url_backup"
	#[ x$? == x0 ] && {
	#	vnete iptables -I FORWARD -j freeStrategy_url_backup
	#}		
}

#flush freeStrategy_url chain and make freeStrategy_url_backup become freeStrategy_url
reset_subchain(){
	vnete iptables -w -t nat -F freeStrategy_url
	fw_check "nat" "PREROUTING" "-j freeStrategy_url"
    while [ x$? == 'x1' ];do
    	#fw del 4 n PREROUTING freeStrategy_url
		vnete iptables -w -t nat -D PREROUTING -j freeStrategy_url
    	fw_check "nat" "PREROUTING" "-j freeStrategy_url"
    done
    #fw del 4 n freeStrategy_url
	vnete iptables -w -t nat -X freeStrategy_url

    vnete iptables -w -t filter -F freeStrategy_url
    fw_check "filter" "forward_auth" "-j freeStrategy_url"
    while [ x$? == 'x1' ];
    do
    	#fw del 4 f forward_auth freeStrategy_url
		vnete iptables -w -t filter -D forward_auth -j freeStrategy_url
    	fw_check "filter" "forward_auth" "-j freeStrategy_url"
    done
    #fw del 4 f freeStrategy_url
	vnete iptables -w -t filter -X freeStrategy_url

    vnete iptables -w -t nat -E freeStrategy_url_backup freeStrategy_url
    vnete iptables -w -t filter -E freeStrategy_url_backup freeStrategy_url

    fw_check "nat" "PREROUTING" "-j freeStrategy_url"
	[ x$? == x0 ] && {
		# need to get rule number of wifidog chain
		vnete iptables -w -t nat -A PREROUTING -j freeStrategy_url
	}

	fw_check "filter" "forward_auth" "-j freeStrategy_url"
	[ x$? == x0 ] && {
		vnete iptables -w -A forward_auth -j freeStrategy_url
	}		
}

while [ 1 ];do

	sleep 600   #check if dns ip has changed every 10 mins
	add_subchain
	local loop=0
	local result=$(uci -c /tmp get freeStrategy.@rule[$loop].strategy_type 2>/dev/null)
	while [ x$result != 'x' ];do
		[ $result == 'url' ] && {
			local enable=$(uci -c /tmp get freeStrategy.@rule[$loop].enable 2>/dev/null)
			local sport=$(uci -c /tmp get freeStrategy.@rule[$loop].sport 2>/dev/null)
			local zone=$(uci -c /tmp get freeStrategy.@rule[$loop].zone 2>/dev/null)
			local mac=$(uci -c /tmp get freeStrategy.@rule[$loop].mac 2>/dev/null)
			local src_ipset=$(uci -c /tmp get freeStrategy.@rule[$loop].src_ipset 2>/dev/null)
			local url=$(uci -c /tmp get freeStrategy.@rule[$loop].url 2>/dev/null)
			[ $enable == 'on' ] && {
				local mac_rule=""
				[ x$mac != 'x' ] && mac=${mac//-/:} && echo "mac=$mac" && mac_rule="-m mac --mac-source $mac"
				local src=""
				[ x$src_ipset != 'x' -a x$src_ipset != x"IPGROUP_ANY" ] && src="-s $src_ipset"
				local src_port=""
				[ x$sport != "x" ] && sport=$(echo $sport | tr '-' ':') && src_port="--sport $sport"
				local iparray=$( dnsq -a $url -d 127.0.0.1 | awk '{print $0}')
				for ip in ${iparray}; do {
					local interface=""
					for interface in $zone;do
						interface=$(zone_get_effect_ifaces $interface)
						local device=$(zone_get_device_byif $interface)
						vnete iptables -w -t nat -A freeStrategy_url_backup -p tcp --dport 80 $src $mac_rule $src_port -d $ip -i $device -j ACCEPT
						vnete iptables -w -A freeStrategy_url_backup -p tcp --dport 80 $src $mac_rule $src_port -d $ip -i $device -j ACCEPT
					done
				}
				done

			}
		} 
		loop=$(($loop+1))
		result=$(uci -c /tmp get freeStrategy.@rule[$loop].strategy_type 2>/dev/null)
	done
	reset_subchain
done