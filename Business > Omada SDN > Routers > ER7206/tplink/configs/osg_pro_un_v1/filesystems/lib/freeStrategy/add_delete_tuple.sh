#!/bin/sh
. /lib/zone/zone_api.sh
. /lib/functions/network.sh
# kill_backup(){
# 	ps | grep freeStrategy_backup.sh | grep -v grep | awk '{print $1}' | xargs kill -s USR1
#     ps | grep 'sleep 600' | grep -v 'grep' | awk '{print $1}' | xargs kill
# }

# start_backup(){

# 	/lib/freeStrategy/freeStrategy_backup.sh &
# }


_load_rule(){
	local name
	local strategy_type
	local url
	local src_ipset
	local dst_ipset
	local sport
	local dport
	local service_type
	local zone
	local mac
	#local comment
	local enable
	local flag=$2

	config_get name $1 name
	config_get strategy_type $1 strategy_type
	[ $strategy_type == 'url' ] && config_get url $1 url
	config_get src_ipset $1 src_ipset
	config_get dst_ipset $1 dst_ipset
	config_get sport $1 sport
	config_get dport $1 dport
	config_get mac $1 mac
	config_get service_type $1 service_type
	config_get zone $1 zone
	config_get enable $1 enable

	[ $enable == 'on' ] && {
		echo "name=$name,strategy_type=$strategy_type,url=$url,src_ipset=$src_ipset,dst_ipset=$dst_ipset,sport=$sport,dport=$dport,mac=$mac,service_type=$service_type,zone=$zone,enable=$enable"
		local mac_rule=""
		[ x$mac != 'x' ] && mac=${mac//-/:} && echo "mac=$mac" && mac_rule="-m mac --mac-source $mac"
		local src=""
		[ x$src_ipset != 'x' -a x$src_ipset != x"IPGROUP_ANY" ] && src="-s $src_ipset"
		local src_port=""
		[ x$sport != "x" ] && sport=$(echo $sport | tr '-' ':') && src_port="--sport $sport"
		
		if [ $strategy_type == "five_tuple" ];then	
			if [ $flag == "1" ];then
				local dst=""
				[ x$dst_ipset != 'x' -a x$dst_ipset != x"IPGROUP_ANY" ] && dst="-d $dst_ipset"
				
				local dst_port=""
				
				[ x$dport != "x" ] && dport=$(echo $dport | tr '-' ':') && dst_port="--dport $dport"
				service_type=$(echo $service_type | tr '[A-Z]' '[a-z]')
				local proto=""
				if [ $service_type != "all" ];then
					proto="-p $service_type"
				else
					src_port=""
					dst_port=""
				fi
				local interface=""
				for interface in $zone;do
					interface=$(zone_get_effect_ifaces $interface)
					local device=$(zone_get_device_byif $interface)
					vnete iptables -w -t nat -A freeStrategy $proto $src $dst $mac_rule $src_port $dst_port -i $device -j ACCEPT -m comment --comment xx_${name}_xx
					vnete iptables -w -A freeStrategy $proto $src $dst $mac_rule $src_port $dst_port -i $device -j forward -m comment --comment xx_${name}_xx
				done
			fi
		else # url
	
			#urlset create ${name}_free weburl 3 1
			#urlset add $url ${name}_free
			#urlset add '#end#' ${name}_free
			if [ $flag == "2" ];then
				local result=$(echo $url | awk -F . '{if(NF==4){i=0;while(i<NF){if($i<0 || $i>255) break;i++}if(i==NF){print "good"}else{print "bad"}}else{print "bad"}}')
				if [ "$result" == "bad" ];then
					local iparray=$( dnsq -t 1000 -a $url -d 127.0.0.1 | awk '{print $0}')
					[ -z "$iparray" ] && return 1
					for ip in ${iparray}; do {
						local interface=""
						for interface in $zone;do
							interface=$(zone_get_effect_ifaces $interface)
							local device=$(zone_get_device_byif $interface)
							vnete iptables -w -t nat -A freeStrategy_url -p tcp --dport 80 $src $mac_rule $src_port -d $ip -i $device -j ACCEPT -m comment --comment xx_${name}_xx
							vnete iptables -w -A freeStrategy_url -p tcp --dport 80 $src $mac_rule $src_port -d $ip -i $device -j forward -m comment --comment xx_${name}_xx
						done
					}
					done
				else
					vnete iptables -w -t nat -A freeStrategy_url -p tcp --dport 80 $src $mac_rule $src_port -d $url -i $device -j ACCEPT -m comment --comment xx_${name}_xx
					vnete iptables -w -A freeStrategy_url -p tcp --dport 80 $src $mac_rule $src_port -d $url -i $device -j forward -m comment --comment xx_${name}_xx
				fi
				# echo "$iparray" >/tmp/freeStrategy_dir/$name
			fi
		fi
	}
}

load_free_rules(){
	config_load freeStrategy
	config_foreach _load_rule rule $1
	#urlset add "#end#" freestrategy1
	#if [ $count -gt $MAX_ELEMENT_PER_SET ];then
	#	urlset add "#end" freestrategy2
	#fi
}

{
	flock 8
	local action=$1
	# kill_backup
	case $action in
		tuple)
			vnete iptables -w -F freeStrategy
			vnete iptables -w -t nat -F freeStrategy
			load_free_rules 1
		;;
		*)
			# start_backup
			return 1
		;;
	esac
	# cp /etc/config/freeStrategy /tmp
	# start_backup
} 8<>/tmp/freeStrategy_tuple_lock