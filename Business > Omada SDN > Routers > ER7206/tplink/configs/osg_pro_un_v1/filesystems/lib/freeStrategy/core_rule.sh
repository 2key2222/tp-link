#
# Copyright (C) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# 
# brief      implement the core function of freeStrategy
# author     Luo pei
# version    1.0.0 
# date         16Sep2015
# history     16Sep2015    Luo pei    Create the file
. /lib/firewall/fw.sh

 
RULE_LIBDIR=${RULE_LIBDIR:-/lib/freeStrategy}

local count=0
local MAX_ELEMENT_PER_SET=200
local RULE_NUMBERS_AT_MOST=400

fw_is_loaded() {
    local bool=$(uci_get_state firewall.core.loaded)
    return $((! ${bool:-0}))
}

fw_check()
{
	local ret=$(vnete iptables -w -t $1 -C $2 $3 2>&1)
	[ -n "$ret" ] && return 0||return 1
}

add_subchain(){
	vnete iptables -w -t nat -N freeStrategy 2>&1
	vnete iptables -w -t nat -N freeStrategy_url 2>&1
	local num=$(vnete iptables -w -nL forward_auth --line-number | grep '\bWiFiDog_Internet\b' | awk '{print $1}')
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
	# WiFiDog_Internet
	vnete iptables -w -N freeStrategy 2>&1
	vnete iptables -w -N freeStrategy_url 2>&1
	fw_check "filter" "forward_auth" "-j freeStrategy"
	[ x$? == x0 ] && {
		if [ "x$num" == 'x' ];then
			vnete iptables -w -A forward_auth -j freeStrategy
		else
			vnete iptables -w -I forward_auth $num -j freeStrategy
		fi
	}

	fw_check "filter" "forward_auth" "-j freeStrategy_url"
	[ x$? == x0 ] && {
		if [ "x$num" == 'x' ];then
			vnete iptables -w -A forward_auth -j freeStrategy_url
		else
			vnete iptables -w -I forward_auth $num -j freeStrategy_url
		fi
	}		
	
	
	fw_check "filter" "forward_auth" "-d 169.254.11.21 -j ACCEPT"
	[ x$? == x0 ] && {
		vnete iptables -w -I forward_auth -d "169.254.11.21" -j ACCEPT
	}	
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
			local dst=""
			[ x$dst_ipset != 'x' -a x$dst_ipset != x"IPGROUP_ANY" ] && dst="-d $dst_ipset"
			
			local dst_port=""
			
			[ x$dport != "x" ] && dport=$(echo $dport | tr '-' ':') && dst_port="--dport $dport"
			service_type=$(echo $service_type | tr '[A-Z]' '[a-z]')
			local proto=""
			if [ "$service_type" != "all" ];then
				proto="-p $service_type"
			else
				src_port=""
				dst_port=""
			fi
			local interface=""
			for interface in $zone;do
				interface=$(zone_get_effect_ifaces $interface)
				local device=$(zone_get_device_byif $interface)
				vnete iptables -w -t nat -A freeStrategy $proto $src $dst $mac_rule $src_port $dst_port -i $device -j ACCEPT
				vnete iptables -w -A freeStrategy $proto $src $dst $mac_rule $src_port $dst_port -i $device -j forward
			done
		else # url
	
			#urlset create ${name}_free weburl 3 1
			#urlset add $url ${name}_free
			#urlset add '#end#' ${name}_free
			local iparray=$( dnsq -a $url -d 127.0.0.1 | awk '{print $0}')
			for ip in ${iparray}; do {
			local interface=""
			for interface in $zone;do
				interface=$(zone_get_effect_ifaces $interface)
				local device=$(zone_get_device_byif $interface)
				vnete iptables -w -t nat -A freeStrategy_url -p tcp --dport 80 $src $mac_rule $src_port -d $ip -i $device -j ACCEPT
				vnete iptables -w -A freeStrategy_url -p tcp --dport 80 $src $mac_rule $src_port -d $ip -i $device -j forward
			done
			}
			done
			
		fi
	}
}

load_free_rules(){
	config_load $1
	config_foreach _load_rule rule
	#urlset add "#end#" freestrategy1
	#if [ $count -gt $MAX_ELEMENT_PER_SET ];then
	#	urlset add "#end" freestrategy2
	#fi
}

fw_init() {
    [ -z "$RULE_INITIALIZED" ] || return 0
	
	. /lib/zone/zone_api.sh
	. /lib/functions/network.sh
    
    RULE_INITIALIZED=1
    return 0
}

rule_start(){
	fw_init
	fw_is_loaded || {
        #syslog $ACCESS_CONTROL_LOG_WNG_FIREWALL_NOT_LOADED
        echo "firewall hasnt start up yet"
        exit 1
    }
    #cp /etc/config/freeStrategy /tmp/freeStrategy
    echo "begin loading rules in freeStrategy"
    # add own rule here!!
    # create two urlset instances,each is a set of 200 number,so that means,support at most 400 rules whoes type is url
   # urlset create freestrategy1 ac 3
   # urlset create freestrategy2 ac 3
    add_subchain
    /lib/freeStrategy/add_delete.sh nat
    #/lib/freeStrategy/freeStrategy_backup.sh &
    #then a single rule is needed with urlsetmatch
}

rule_stop(){
	fw_init
	fw_is_loaded || {
        #syslog $ACCESS_CONTROL_LOG_WNG_FIREWALL_NOT_LOADED
        echo "firewall hasnt start up yet,in rule_stop"
        exit 1
    }
    ## try to destroy all the rules
    # first empty the rules that reference the 

    # killall freeStrategy_backup.sh
    # ps | grep 'sleep 600' | grep -v 'grep' | awk '{print $1}' | xargs kill
    
    #clean the freeStrategy of nat
    vnete iptables -w -t nat -F freeStrategy
    vnete iptables -w -t nat -F freeStrategy_url
    fw_check "nat" "PREROUTING" "-j freeStrategy"
    while [ x$? == 'x1' ];do
    	#fw del 4 n PREROUTING freeStrategy
		vnete iptables -w -t nat -D PREROUTING -j freeStrategy
    	fw_check "nat" "PREROUTING" "-j freeStrategy"
    done
    #fw del 4 n freeStrategy
	vnete iptables -w -t nat -X freeStrategy

    fw_check "nat" "PREROUTING" "-j freeStrategy_url"
    while [ x$? == 'x1' ];do
    	#fw del 4 n PREROUTING freeStrategy_url
		vnete iptables -w -t nat -D PREROUTING -j freeStrategy_url
    	fw_check "nat" "PREROUTING" "-j freeStrategy_url"
    done
    #fw del 4 n freeStrategy_url
	vnete iptables -w -t nat -X freeStrategy_url

    # clean the freeStrategy of filter
    vnete iptables -w -t filter -F freeStrategy
    vnete iptables -w -t filter -F freeStrategy_url
    fw_check "filter" "forward_auth" "-j freeStrategy"
    while [ x$? == 'x1' ];
    do
    	#fw del 4 f forward_auth freeStrategy
		vnete iptables -w -t filter -D forward_auth -j freeStrategy
    	fw_check "filter" "forward_auth" "-j freeStrategy"
    done
    #fw del 4 f freeStrategy
	vnete iptables -w -t filter -X freeStrategy

    fw_check "filter" "forward_auth" "-j freeStrategy_url"
    while [ x$? == 'x1' ];
    do
    	#fw del 4 f forward_auth freeStrategy_url
		vnete iptables -w -t filter -D forward_auth -j freeStrategy_url
    	fw_check "filter" "forward_auth" "-j freeStrategy_url"
    done
    #fw del 4 f freeStrategy_url
	vnete iptables -w -t filter -X freeStrategy_url

    #urlset destroy 3  # destroy the set
}

rule_restart(){
	rule_stop
	rule_start
}

rule_reload(){
	rule_restart
}
