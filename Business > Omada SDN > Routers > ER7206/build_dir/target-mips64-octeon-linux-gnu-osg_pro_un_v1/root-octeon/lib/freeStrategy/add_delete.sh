#!/bin/sh
. /lib/zone/zone_api.sh
. /lib/functions/network.sh
. /lib/firewall/fw.sh
# kill_backup(){
# 	ps | grep freeStrategy_backup.sh | grep -v grep | awk '{print $1}' | xargs kill -s USR1
#     ps | grep 'sleep 600' | grep -v 'grep' | awk '{print $1}' | xargs kill
# }

# start_backup(){

# 	/lib/freeStrategy/freeStrategy_backup.sh &
# }
fw_check()
{
	local ret=$(vnete iptables -w -t $1 -C $2 $3 2>&1)
	[ -n "$ret" ] && return 0||return 1
}

cron_modify(){
	local period="$1"
	[ -z "$period" ] && return 1
	[ -z "$(echo $period | sed -n "/^[0-9]\+$/p")" ] && return 1

	# start cron to update ip of url
	[ ! -f /etc/crontabs/root ] && touch /etc/crontabs/root
	echo "*/$period * * * * /bin/sh /lib/freeStrategy/add_delete.sh url" > /tmp/freeStrategy_save
	crontab -l | grep -v "freeStrategy" | cat - /tmp/freeStrategy_save | crontab -
	/etc/init.d/cron start
	rm -f /tmp/freeStrategy_save
}

cron_check() {
	local value="$1"
	[ -z "$value" ] && return 1
	[ -z "$(echo $value | sed -n "/^[0-9]\+$/p")" ] && return 1

	crontab -l | grep "freeStrategy" | awk '{print $1}' | grep -q -w "*/$value" && return 0 || return 1
}

item_add()
{
	local name_union=$1
	local name=${name_union%%##*}
	local strategy_type=${name_union##*##}
	local url=$2
	local src_ipset=$3
	local dst_ipset=$4
	local sport=$5
	local dport=$6
	local mac=$7
	local service_type=$8
	local zone=$9

	local mac_rule=""
	[ "$mac" != "default" ] && mac=${mac//-/:} && echo "mac=$mac" && mac_rule="-m mac --mac-source $mac"
	local src=""
	[ "$src_ipset" != "default" ] && src="-s $src_ipset"
	local src_port=""
	[ "$sport" != "default" ] && sport=$(echo $sport | tr '-' ':') && src_port="--sport $sport"

	if [ "$strategy_type" == "five_tuple" ];then
		local dst=""
		[ "$dst_ipset" != "default" ] && dst="-d $dst_ipset"

		local dst_port=""
		[ "$dport" != "default" ] && dport=$(echo $dport | tr '-' ':') && dst_port="--dport $dport"
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
	else #url
		local result=$(echo $url | awk -F . '{if(NF==4){i=0;while(i<NF){if($i<0 || $i>255) break;i++}if(i==NF){print "good"}else{print "bad"}}else{print "bad"}}')
		if [ $result == "bad" ];then
			local iparray=$url
			[ "$service_type" != "1" ] && {
				iparray=$( dnsq -t 1000 -a $url -d 127.0.0.1 | awk '{print $0}')
				[ -z "$iparray" ] && return 1
			}
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
			 # echo "$iparray" >/tmp/freeStrategy_dir/$name
		else
			for interface in $zone;do
				interface=$(zone_get_effect_ifaces $interface)
				local device=$(zone_get_device_byif $interface)
				vnete iptables -w -t nat -A freeStrategy_url -p tcp --dport 80 $src $mac_rule $src_port -d $url -i $device -j ACCEPT -m comment --comment xx_${name}_xx
				vnete iptables -w -A freeStrategy_url -p tcp --dport 80 $src $mac_rule $src_port -d $url -i $device -j forward -m comment --comment xx_${name}_xx
			done
		fi

	fi

}

item_delete()
{
	# first kill the backup process?
	local name_set=$1
	local strategy_type=""
	local num=0
	for name_union in $name_set;do
		# name##strategy
		local name=${name_union%%##*}
		strategy_type=${name_union##*##}
		if [ $strategy_type == "five_tuple" ];then
			num=$(vnete iptables -w -t nat -nvL freeStrategy --line-number | grep "\bxx_${name}_xx\b" | wc -l)
			if [ $num != "0" ];then
				local rule_num=$(vnete iptables -w -t nat -nvL freeStrategy --line-number | grep "\bxx_${name}_xx\b" | head -n 1 | awk '{print $1}')
				for i in $(seq 1 ${num});do
					vnete iptables -w -t nat -D freeStrategy $rule_num
				done
				num=$(vnete iptables -w  -nvL freeStrategy --line-number | grep "\bxx_${name}_xx\b" | wc -l)
				[ $num == "0" ] && return 0
				rule_num=$(vnete iptables -w -nvL freeStrategy --line-number | grep "\bxx_${name}_xx\b" | head -n 1 | awk '{print $1}')
				for i in $(seq 1 ${num});do
					vnete iptables -w -D freeStrategy $rule_num
				done
			fi
		else #url
			num=$(vnete iptables -w -t nat -nvL freeStrategy_url --line-number | grep "\bxx_${name}_xx\b" | wc -l)
			if [ $num != "0" ];then
				local rule_num=$(vnete iptables -w -t nat -nvL freeStrategy_url --line-number | grep "\bxx_${name}_xx\b" | head -n 1 | awk '{print $1}')
				for i in $(seq 1 ${num});do
					vnete iptables -w -t nat -D freeStrategy_url $rule_num
				done
				num=$(vnete iptables -w  -nvL freeStrategy_url --line-number | grep "\bxx_${name}_xx\b" | wc -l)
				[ $num == "0" ] && return 0
				rule_num=$(vnete iptables -w -nvL freeStrategy_url --line-number | grep "\bxx_${name}_xx\b" | head -n 1 | awk '{print $1}')
				for i in $(seq 1 ${num});do
					vnete iptables -w -D freeStrategy_url $rule_num
				done
				# rm -f /tmp/freeStrategy_dir/$name
			fi
		fi
	done
	#then start it again?
}


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
		#echo "name=$name,strategy_type=$strategy_type,url=$url,src_ipset=$src_ipset,dst_ipset=$dst_ipset,sport=$sport,dport=$dport,mac=$mac,service_type=$service_type,zone=$zone,enable=$enable"
		local mac_rule=""
		[ x$mac != 'x' ] && mac=${mac//-/:} && echo "mac=$mac" && mac_rule="-m mac --mac-source $mac"
		local src=""
		[ x$src_ipset != 'x' -a x$src_ipset != x"IPGROUP_ANY" ] && src="-s $src_ipset"
		local src_port=""
		[ x$sport != "x" ] && sport=$(echo $sport | tr '-' ':') && src_port="--sport $sport"
		
		if [ $strategy_type == "five_tuple" ];then	
			if [ $flag == "1" -o $flag == "3" ];then
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
			if [ $flag == "2" -o $flag == "3" ];then
				local result=$(echo $url | awk -F . '{if(NF==4){i=0;while(i<NF){if($i<0 || $i>255) break;i++}if(i==NF){print "good"}else{print "bad"}}else{print "bad"}}')
				if [ "$result" == "bad" ];then
					local iparray=$( dnsq -t 1000 -a $url -d 127.0.0.1 | awk '{print $0}')
					[ -z "$iparray" ] && {
						cron_check 1 || cron_modify 1
						return 1
					}
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
					cron_check 5 || cron_modify 5
				else
					local interface=""
						for interface in $zone;do
							interface=$(zone_get_effect_ifaces $interface)
							local device=$(zone_get_device_byif $interface)
							vnete iptables -w -t nat -A freeStrategy_url -p tcp --dport 80 $src $mac_rule $src_port -d $url -i $device -j ACCEPT -m comment --comment xx_${name}_xx
							vnete iptables -w -A freeStrategy_url -p tcp --dport 80 $src $mac_rule $src_port -d $url -i $device -j forward -m comment --comment xx_${name}_xx
						done
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
	flock 9
	local action=$1
	# kill_backup
	case $action in
		add)
			item_add "$2" "$3" "$4" "$5" "$6" "$7" "$8" "$9" "${10}" 
			
		;;
		delete)
			item_delete "$2"
		;;
		update)
			item_delete "$2"
			local enable=$11
			if [ "$enable" == "on" ];then
				item_add "$3" "$4" "$5" "$6" "$7" "$8" "$9" "${10}" "${12}" 
			fi
		;;
		nat)
			#echo "nat =============================" >>/tmp/free.log
			#vnete iptables -w -nL freeStrategy_url >>/tmp/free.log
			
			vnete iptables -w -t nat -N freeStrategy 2>&1
			vnete iptables -w -t nat -N freeStrategy_url 2>&1
			local num_s=$(vnete iptables -w  -t nat -nL PREROUTING --line-number | grep service_redirect | awk '{print $1}')
			fw_check "nat" "PREROUTING" "-j freeStrategy"
			[ x$? == x0 ] && {
				# need to get rule number of wifidog chain
				# vnete iptables -w  -t nat -I PREROUTING -j freeStrategy
				if [ "x$num_s" == 'x' ];then
					vnete iptables -w  -t nat -I PREROUTING -j freeStrategy
				else
					vnete iptables -w  -t nat -I PREROUTING $((num_s+1)) -j freeStrategy
				fi
			}

			fw_check "nat" "PREROUTING" "-j freeStrategy_url"
			[ x$? == x0 ] && {
				# need to get rule number of wifidog chain
				# vnete iptables -w -t nat -I PREROUTING -j freeStrategy_url
				if [ "x$num_s" == 'x' ];then
					vnete iptables -w  -t nat -I PREROUTING -j freeStrategy_url
				else
					vnete iptables -w  -t nat -I PREROUTING $((num_s+1)) -j freeStrategy_url
				fi
			}
			vnete iptables -w -N freeStrategy_url 2>&1
			fw_check "filter" "forward_auth" "-j freeStrategy_url"
			[ x$? == x0 ] && {
				# need to get rule number of wifidog chain
				vnete iptables -w  -I forward_auth -j freeStrategy_url
			}
			
			fw_check "filter" "forward_auth" "-d 169.254.11.21 -j ACCEPT"
			[ x$? == x0 ] && {
				vnete iptables -w -I forward_auth -d "169.254.11.21" -j ACCEPT
			}	
			vnete iptables -w -F freeStrategy
			vnete iptables -w -F freeStrategy_url
			vnete iptables -w -t nat -F freeStrategy
			vnete iptables -w -t nat -F freeStrategy_url
			load_free_rules 3
			#vnete iptables -w -nL freeStrategy_url >>/tmp/free.log
		;;
		url)
			#echo "url===================" >>/tmp/free.log
			vnete iptables -w -N freeStrategy_url 2>&1
			fw_check "filter" "forward_auth" "-j freeStrategy_url"
			[ x$? == x0 ] && {
				# need to get rule number of wifidog chain
				vnete iptables -w  -I forward_auth -j freeStrategy_url
			}
			
			fw_check "filter" "forward_auth" "-d 169.254.11.21 -j ACCEPT"
			[ x$? == x0 ] && {
				vnete iptables -w -I forward_auth -d "169.254.11.21" -j ACCEPT
			}
			vnete iptables -w -F freeStrategy_url
			vnete iptables -w -t nat -F freeStrategy_url
			#vnete iptables -w -nL freeStrategy_url >>/tmp/free.log
			load_free_rules 2
			#echo "" >>/tmp/free.log
			#vnete iptables -w -nL freeStrategy_url >>/tmp/free.log
		;;
		*)
			# start_backup
			return 1
		;;
	esac
	# cp /etc/config/freeStrategy /tmp
	# start_backup
} 9<>/tmp/freeStrategy_lock
