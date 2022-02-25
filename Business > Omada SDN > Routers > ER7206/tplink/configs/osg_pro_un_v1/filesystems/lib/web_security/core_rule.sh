#!/bin/sh
. /lib/web_security/time.sh
. /lib/functions/network.sh
. /lib/web_security/config.sh
. /lib/firewall/fw.sh

fw_is_loaded() {
    local bool=$(uci_get_state firewall.core.loaded)
    return $((! ${bool:-0}))
}

fw_check()
{
	local ret=$(iptables -w -t $1 -C $2 $3 2>&1)
	[ -n "$ret" ] && return 0||return 1
}


add_subchain(){
	local pos=0
	iptables -w -t mangle -N websec 2>&1
	fw_check "mangle" "FORWARD" "-p tcp -j websec"
	[ x$? == x1 ] && return 1
	fw_check "mangle" "FORWARD" "-p tcp --dport 80 -j url_filter"
	[ x$? == x1 ] && pos=$(iptables -w -t mangle -n -L FORWARD --line-number | grep url_filter | cut -d ' ' -f 1)
	[ x"pos" != 'x' ] && pos=$(($pos+1)) || pos=1
	iptables -w -t mangle -I FORWARD $pos -p tcp -j websec
}

_load_rule(){
	local name
	local addr
	local websubmit
	local fileext
	local timeobj
	local state
	local post_filter=""

	config_get name $1 name
	config_get addr $1 addr
	config_get websubmit $1 websubmit
	config_get fileext $1 fileext
	config_get timeobj $1 timeobj
	config_get state $1 state

	echo "rulename=$name,group=$addr,websubmit=$websubmit,fileext=$fileext,timeobj=$timeobj,state=$state"
	[ "$state" != "on" ] && return 1

	[ "$timeobj" != "Any" ] && return 1
	
	urlset create $name weburl websec 100
	for i in $fileext;do
		urlset add $i $name
	done
	#urlset add '#end#' $name
	#match module

	if [ $timeobj == "Any" ];then
		#add rule here
		[ "$websubmit" == "on" ] && post_filter="--filter submit"
		if [ "$addr" == "IPGROUP_ANY" ];then
			iptables -w -t mangle -A websec -p tcp -m websecmatch $post_filter --setname $name -m comment --comment  sec_${name}_sec -j urlsettarget --type drop #--target log 
		else
			iptables -w -t mangle -A websec -p tcp -m set --match-set $addr src -m websecmatch $post_filter --setname $name -m comment --comment sec_${name}_sec -j urlsettarget --type drop #--target log 
		fi
	#else
	#	add_timeobj $timeobj $name
	fi  
}

load_security_rules(){
	config_load $1
	config_foreach _load_rule rule
}

websecurity_start(){
	fw_is_loaded || {
        #syslog $ACCESS_CONTROL_LOG_WNG_FIREWALL_NOT_LOADED
        exit 1
    }
    echo "begin loading web security rules"
	local enable=$(uci get web_security.default.state)
	[ $enable != 'on' ] && echo "webfilter global setting is off" && return 1
	add_subchain
	load_security_rules web_security
	lua /lib/web_security/attach_timeobj.lua
}

websecurity_stop(){
	fw_is_loaded || {
        #syslog $ACCESS_CONTROL_LOG_WNG_FIREWALL_NOT_LOADED
        exit 1
    }
    echo "begin to exit rule"
    #remove iptables & chains,detach rule from time-obj
    iptables -w -t mangle -F websec
    lua /lib/web_security/detach_timeobj.lua
    fw_check "mangle" "FORWARD" "-p tcp  -j websec" #complete condition check here
    while [ x$? == x1 ]; do
		fw del 4 m FORWARD websec $ { -p tcp }
		fw_check "mangle" "FORWARD" "-p tcp -j websec"
	done
	fw del 4 m websec
	urlset destroy websec
}

websecurity_restart(){
	websecurity_stop
	websecurity_start
}

websecurity_reload(){
	websecurity_restart
}