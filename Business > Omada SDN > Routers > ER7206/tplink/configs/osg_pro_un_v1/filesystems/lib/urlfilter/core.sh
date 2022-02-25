#
# Copyright (C) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# 
# brief      implement the core function of urlfilter
# author     Luo pei
# version    1.0.0 
# date         23July2015
# history     23July2015    Luo pei    Create the file
. /lib/urlfilter/time.sh

URL_LIBDIR=${URL_LIBFIR:-/lib/urlfilter}

local special=0
local filter_action=""
local s_time=""
local s_urlgrp=""
local s_usergroup=""
local s_action1=""
local s_redirect=""
local s_tmp_act=""

fw_is_loaded() {
    local bool=$(uci_get_state firewall.core.loaded)
    return $((! ${bool:-0}))
}

fw_check()
{
	local ret=$(iptables -w -t $1 -C $2 $3 2>&1)
	[ -n "$ret" ] && return 0||return 1
}

# http packet jump to url_filter chain
add_subchain(){
	iptables -w -t mangle -N url_filter 2>&1
	iptables -w -t mangle -N url_filter_dns 2>&1
	fw_check "mangle" "FORWARD" "-p tcp -j url_filter"
	[ x$? == x0 ] && {
		iptables -w -t mangle -I FORWARD -p tcp -j url_filter
	}

	fw_check "mangle" "FORWARD" "-p udp --dport 53 -j url_filter_dns"
	[ x$? == x0 ] && {
		fw_check "mangle" "FORWARD" "-p udp --dport 53 -j webfilter_dns"
		if [ x$? == x0 ];then
			iptables -w -t mangle -A FORWARD -p udp --dport 53 -j url_filter_dns
		else
			local pos=$(iptables -w -t mangle -nL FORWARD --line-numbers | grep '\bwebfilter_dns\b' | cut -d ' ' -f 1)
			iptables -w -t mangle -I FORWARD $pos -p udp --dport 53 -j url_filter_dns
		fi
	}

	fw_check "mangle" "INPUT" "-p udp --dport 53 -j url_filter_dns"
	[ x$? == x0 ] && {
		fw_check "mangle" "INPUT" "-p udp --dport 53 -j webfilter_dns"
		if [ x$? == x0 ];then
			iptables -w -t mangle -A INPUT -p udp --dport 53 -j url_filter_dns
		else
			local pos=$(iptables -w -t mangle -nL INPUT --line-numbers | grep '\bwebfilter_dns\b' | cut -d ' ' -f 1)
			iptables -w -t mangle -I INPUT $pos -p udp --dport 53 -j url_filter_dns
		fi
	}
}

_load_rule(){
	local urlgroup
	local usergroup
	local action
	local filter_way
	local filter_content
	local target
	local time
	local enable
	local redirect
	local action1
	local filter_mode="keyword"
	local tmp_act="ACCEPT"
	
	config_get urlgroup $1 urlgroupname
	config_get usergroup $1 usergroupname
	config_get action $1 action
	config_get filter_way $1 filter_way
	config_get filter_content $1 filter_content
	config_get target $1 target
	config_get time $1 time
	config_get enable $1 enable
	config_get redirect $1 redirect
	config_get action1 $1 action1
	
	[ $enable != '1' -a $enable != 'on' ] && return

	[ $action == "drop" ] && action="drop_reset" && tmp_act="DROP"
	[ "$filter_content" == "." ] && {
		special=1
		filter_action=$action
		s_time=$time
		s_urlgrp=$urlgroup
		s_usergroup=$usergroup
		s_action1=$action1
		s_redirect=$redirect
		s_tmp_act=$tmp_act
		return
	}

	urlset create $urlgroup ac url
	for i in $filter_content;do
		urlset add $i $urlgroup
		[ "x${i%%/}" = "x${i}" ] && {
			urlset add "$i/" $urlgrp
		}
	done
	urlset add '#end#' $urlgroup
	[ x$filter_way = "xurl" ] && filter_mode="url"
	local targetx=""
	local url=""
	local tourl

		for i in $action1;do
			[ x"${i##*_}" == "xoff" ] && continue  # end with 'off',
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
	echo "action=$action"
	#echo "targetx=$targetx"
	#echo "tourl=$tourl"
	echo "time=$time,usergroup=$usergroup,urlgroup=$urlgroup"
	if [ ${targetx}x == 'x' ];then
		targetx=""
	else
		targetx="--target $targetx"
	fi
	echo "targetx=$targetx"
	echo "tourl=$tourl"
	if [ $time == "Any" ];then
		local id="11702"
		[ $action == "accept" ] && id="11811"
		if [ $usergroup == "IPGROUP_ANY" ]; then
			#add common here
			iptables -w -t mangle -A url_filter -m conntrack --ctdir ORIGINAL -p tcp -m urlsetmatch --setname $urlgroup --filter $filter_mode -m comment --comment url_${urlgroup}_url -j urlsettarget --type $action $targetx $tourl --common $id,"Any"
			iptables -w -t mangle -A url_filter_dns -p udp -m url_dns_match --setname $urlgroup --filter $filter_mode --type dns -m comment --comment url_${urlgroup}_url -j $tmp_act
		else
			iptables -w -t mangle -A url_filter -m conntrack --ctdir ORIGINAL -p tcp -m set --match-set $usergroup src -m urlsetmatch --setname $urlgroup --filter $filter_mode -m comment --comment url_${urlgroup}_url -j urlsettarget --type $action $targetx $tourl --common $id,$usergroup
			iptables -w -t mangle -A url_filter_dns -p udp -m set --match-set $usergroup src -m url_dns_match --setname $urlgroup --filter $filter_mode --type dns -m comment --comment url_${urlgroup}_url -j $tmp_act
		fi
	#else
		#echo "why error happens here?"
	#	add_timeobj $time $urlgroup
	fi
}

load_filter_rules(){
	config_load $1
	config_foreach _load_rule url
	[ $special == 1 ] && {
		local targetx=""
		local tourl=""
		for i in $s_action1;do
			[ x"${i##*_}" == "xoff" ] && continue  # end with 'off',
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
					if [ x"$s_redirect" != 'x' ];then
						echo "$s_redirect" | grep "^http" || s_redirect="http://$s_redirect"
						tourl="--tourl $s_redirect"
					else
						echo "error happens,should leave"
						return
					fi  
				;;
			esac
		done
	#echo "action=$action"
	#echo "targetx=$targetx"
	#echo "tourl=$tourl"
	echo "time=$time,usergroup=$usergroup,urlgroup=$urlgroup"
	if [ ${targetx}x == 'x' ];then
		targetx=""
	else
		targetx="--target $targetx"
	fi
		if [ "$s_time" == "Any" ];then
		#iptables -t mangle -A url_filter -p tcp -j $filter_action
			local id="11702"
			[ $action == "accept" ] && id="11811"
			if [ "$s_usergroup" == "IPGROUP_ANY" ];then
				iptables -w -t mangle -A url_filter -m conntrack --ctdir ORIGINAL -p tcp -m urlsetmatch --filter special -m comment --comment url_${s_urlgrp}_url -j urlsettarget --type $filter_action $targetx $tourl --common $id,"Any"
				iptables -w -t mangle -A url_filter_dns -p udp -m url_dns_match --filter special --type dns -m comment --comment url_${s_urlgrp}_url -j $s_tmp_act
			else
				iptables -w -t mangle -A url_filter -m conntrack --ctdir ORIGINAL -p tcp -m set --match-set $s_usergroup src -m urlsetmatch --filter special -m comment --comment url_${s_urlgrp}_url -j urlsettarget --type $filter_action $targetx $tourl --common $id,$s_usergroup
				iptables -w -t mangle -A url_filter_dns -p udp -m set --match-set $s_usergroup src -m url_dns_match --filter special --type dns -m comment --comment url_${s_urlgrp}_url -j $s_tmp_act
			fi
		#else
		#	add_timeobj $s_time $s_urlgrp
		fi
	}
}

fw_init() {
    [ -z "$URL_INITIALIZED" ] || return 0
    #. $URL_LIBDIR/config.sh
    #fw_config_append url_filter

    #for file in $IMB_LIBDIR/core_*.sh; do
    #    . $file
    #done
	
	. /lib/zone/zone_api.sh
	. /lib/functions/network.sh
    
    URL_INITIALIZED=1
    return 0
}

url_start(){
	fw_init
	fw_is_loaded || {
        #syslog $ACCESS_CONTROL_LOG_WNG_FIREWALL_NOT_LOADED
        exit 1
    }
	
	echo "begin loading url filter rules"
	local enable=$(uci get filter_global.@filter_global[0].enable)
	[ $enable != '1' ] && echo "url global setting is off" && return 1
	add_subchain
	load_filter_rules url_filter
	lua /lib/urlfilter/attach_timeobj.lua
}

url_stop(){
	fw_is_loaded || {
		exit 1
	}
	iptables -w -t mangle -F url_filter
	lua /lib/urlfilter/detach_timeobj.lua
	fw_check "mangle" "FORWARD" "-p tcp -j url_filter" #complete condition check here
	#get rule number,fix me,how to simplify this?
	#local i=$(iptables -t mangle -nvL --line-numbers | grep url_filter | cut -d ' ' -f 1 | sed -r -n '/[[:digit:]]/p')
	#iptables -t mangle -D FORWARD $i
	#iptables -t mangle -X url_filter
	while [ x$? == x1 ]; do
		fw del 4 m FORWARD url_filter $ { -p tcp }
		fw_check "mangle" "FORWARD" "-p tcp -j url_filter"
	done
	fw del 4 m url_filter

	iptables -w -t mangle -F url_filter_dns
	fw_check "mangle" "FORWARD" "-p udp --dport 53 -j url_filter_dns"
	while [ x$? == x1 ];do
		fw del 4 m FORWARD url_filter_dns $ { -p udp --dport 53 }
		fw_check "mangle" "FORWARD" "-p udp --dport 53 -j url_filter_dns"
	done
	
	fw_check "mangle" "INPUT" "-p udp --dport 53 -j url_filter_dns"
	while [ x$? == x1 ];do
		fw del 4 m INPUT url_filter_dns $ { -p udp --dport 53 }
		fw_check "mangle" "INPUT" "-p udp --dport 53 -j url_filter_dns"
	done

	iptables -w -t mangle -X url_filter_dns

	urlset destroy url #need to add another flag to indicate the type(url_filter | website | websec)
	special=0
	filter_action=""
}

url_restart(){
	url_stop
	url_start
}

url_reload(){
	url_restart
}
