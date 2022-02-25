#!/bin/sh
. /lib/webfilter/time.sh
. /lib/functions/network.sh
. /lib/zone/zone_api.sh

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
	iptables -w -t mangle -N webfilter 2>&1
	iptables -w -t mangle -N webfilter_dns 2>&1
	fw_check "mangle" "FORWARD" "-p tcp -j webfilter"
	[ x$? == x0 ] && {
		fw_check "mangle" "FORWARD" "-p tcp -j websec"
		if [ x$? == x1 ];then
			pos=$(iptables -w -t mangle -n -L FORWARD --line-number | grep websec | cut -d ' ' -f 1)
			pos=$(($pos+1))
		else
			fw_check "mangle" "FORWARD" "-p tcp -j url_filter"
			[ x$? == x1 ] && pos=$(iptables -w -t mangle -n -L FORWARD --line-number | grep '\burl_filter\b' | cut -d ' ' -f 1)
			pos=$(($pos+1))
		fi
		iptables -w -t mangle -I FORWARD $pos -p tcp -j webfilter
	}

	fw_check "mangle" "FORWARD" "-p udp --dport 53 -j webfilter_dns"
	[ x$? == x0 ] && {
		fw_check "mangle" "FORWARD" "-p udp --dport 53 -j url_filter_dns"
		if [ x$? == x0 ];then
			iptables -w -t mangle -A FORWARD -p udp --dport 53 -j webfilter_dns
		else
			local pos=$(iptables -w -t mangle -n -L FORWARD --line-number | grep '\burl_filter_dns\b' | cut -d ' ' -f 1)
			pos=$(($pos+1))
			iptables -w -t mangle -I FORWARD $pos -p udp --dport 53 -j webfilter_dns
		fi
	}

	fw_check "mangle" "INPUT" "-p udp --dport 53 -j webfilter_dns"
	[ x$? == x0 ] && {
		fw_check "mangle" "INPUT" "-p udp --dport 53 -j url_filter_dns"
		if [ x$? == x0 ];then
			iptables -w -t mangle -A INPUT -p udp --dport 53 -j webfilter_dns
		else
			local pos=$(iptables -w -t mangle -n -L INPUT --line-number | grep '\burl_filter_dns\b' | cut -d ' ' -f 1)
			pos=$(($pos+1))
			iptables -w -t mangle -I INPUT $pos -p udp --dport 53 -j webfilter_dns
		fi
	}
}

_load_rule(){
	local rulename
	local group
	local rule_type
	local action
	local website
	local redirect
	local time
	local state
	local tmp_act="ACCEPT"

	config_get rulename $1 rulename
	config_get group $1 group
	config_get rule_type $1 rule_type
	config_get action $1 action
	config_get website $1 website
	config_get redirect $1 redirect
	config_get time $1 time
	config_get state $1 state

	echo "rulename=$rulename,group=$group,rule_type=$rule_type,action=$action,website=$website,redirect=$redirect,time=$time,state=$state"
	[ "$state" != "on" ] && return 1
	local targetx=""
	local tourl=""
	local acc="accept"
	[ $rule_type == "off" ] && acc="drop_reset" && tmp_act="DROP"
	for i in $action;do
		[ ${i##*_} == "off" ] && continue  # end with 'off',
		case $i in
			log)
				if [ x"$targetx" == "x" ];then
					targetx="log"
				else
					targetx="$targetx,log"
				fi
			;;
			warn)
				if [ x"$targetx" == "x" ];then
					targetx="warn"
				else
					targetx="$targetx,warn"
				fi
			;;
			redirect)
				if [ x"$targetx" == "x" ];then
					targetx="redirect"
				else
					targetx="$targetx,redirect"
				fi
				if [ x"$redirect" != 'x' ];then
					echo "$redirect" | grep "^http" || redirect="http://$redirect"
					tourl="--tourl $redirect"
				else
					echo "error happens,should leave"
					return
				fi  
			;;
		esac
	done
	[ x"$targetx" != "x" ] && targetx="--target $targetx"
    # target module	
    echo "targetx=$targetx"
    echo "tourl=$tourl"
	local matchset=""
	local all_flag=0
	for i in $website;do
		[ $i == "ALL" ] && all_flag=1 && break
		local set=$(uci get websort.$i.name)
		[ x"$set" == 'x' ] && echo "error happens" && return
		if [ x"$matchset" == 'x' ];then
			matchset=$set
		else
			matchset="$matchset,$set"
		fi
	done
	echo "matchset=$matchset"
	#match module
	local tmp_match=""
	if [ $time == "Any" ];then
		#add rule here
		local match=""
		if [ $all_flag == '0' ];then
		 	match="-m webfiltermatch --setname $matchset --filter keyword"
		 	tmp_match="-m web_dns_match --setname $matchset --filter keyword --type dns"
		else
			match="-m webfiltermatch --filter special"
			tmp_match="-m web_dns_match --filter special --type dns"
		fi
		local id="11702"
		[ $acc == "accept" ] && id="11811"
		if [ "$group" == "IPGROUP_ANY" ];then
			iptables -w -t mangle -A webfilter -m conntrack --ctdir ORIGINAL -p tcp $match -m comment --comment url_${rulename}_url -j urlsettarget --type $acc $targetx $tourl --common $id,"Any"
			iptables -w -t mangle -A webfilter_dns -p udp $tmp_match -m comment --comment url_${rulename}_url -j $tmp_act
		else
			iptables -w -t mangle -A webfilter -m conntrack --ctdir ORIGINAL -p tcp -m set --match-set $group src $match -m comment --comment url_${rulename}_url -j urlsettarget --type $acc $targetx $tourl --common $id,$group
			iptables -w -t mangle -A webfilter_dns -p udp -m set --match-set $group src $tmp_match -m comment --comment url_${rulename}_url -j $tmp_act
		fi
	#else
	#	add_timeobj $time $rulename
	fi  
}

load_filter_rules(){
	config_load $1
	config_foreach _load_rule webfilter
}

webfilter_start(){
	fw_is_loaded || {
        #syslog $ACCESS_CONTROL_LOG_WNG_FIREWALL_NOT_LOADED
        exit 1
    }
    echo "begin loading web filter rules"
	local enable=$(uci get webfilter_global.settings.enable)
	[ $enable != 'on' ] && echo "webfilter global setting is off" && return 1
	add_subchain
	load_filter_rules webfilter
	lua /lib/webfilter/attach_timeobj.lua
}

webfilter_stop(){
	fw_is_loaded || {
        #syslog $ACCESS_CONTROL_LOG_WNG_FIREWALL_NOT_LOADED
        exit 1
    }
    echo "begin to exit rule"
    #remove iptables & chains,detach rule from time-obj
    iptables -w -t mangle -F webfilter
    lua /lib/webfilter/detach_timeobj.lua
    fw_check "mangle" "FORWARD" "-p tcp  -j webfilter" #complete condition check here
    while [ x$? == x1 ]; do
		fw del 4 m FORWARD webfilter $ { -p tcp }
		fw_check "mangle" "FORWARD" "-p tcp -j webfilter"
	done
	iptables -w -t mangle -X webfilter

	iptables -w -t mangle -F webfilter_dns
	fw_check "mangle" "FORWARD" "-p udp --dport 53 -j webfilter_dns"
	while [ x$? == x1 ];do
		fw del 4 m FORWARD webfilter_dns $ { -p udp --dport 53 }
		fw_check "mangle" "FORWARD" "-p udp --dport 53 -j webfilter_dns"
	done

	fw_check "mangle" "INPUT" "-p udp --dport 53 -j webfilter_dns"
	while [ x$? == x1 ];do
		fw del 4 m INPUT webfilter_dns $ { -p udp --dport 53 }
		fw_check "mangle" "INPUT" "-p udp --dport 53 -j webfilter_dns"
	done
	iptables -w -t mangle -X webfilter_dns
}

webfilter_restart(){
	webfilter_stop
	webfilter_start
}

webfilter_reload(){
	webfilter_restart
}