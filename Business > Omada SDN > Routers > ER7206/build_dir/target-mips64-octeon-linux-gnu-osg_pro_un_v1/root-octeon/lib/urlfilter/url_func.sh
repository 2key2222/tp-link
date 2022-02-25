#!/bin/sh

#
# Copyright (C) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# 
# brief      dynamically add or delete rules of urlfilter
# author     Luo pei
# version    1.0.0 
# date         29Dec2015
# history     29Dec2015    Luo pei    Create the file

URL_LIBDIR=${URL_LIBFIR:-/lib/urlfilter}

local usergrp=""
local action=""
local filter_way=""
local filter_content=""
local action1=""
local position=0
local redirect=""

fw_check()
{
	local ret=$(iptables -w -t $1 -C $2 $3 2>&1)
	[ -n "$ret" ] && return 0||return 1
}

get_other_info(){
	local target_name=$1
  	# local loop=0

  	# local result=$(uci get url_filter.@url[$loop].urlgroupname 2>/dev/null)
  	# while [ x$result != 'x' ];do
	  #   local name=$result
	  #   [ $name == $target_name ] && {
	  #      usergrp=$(uci get url_filter.@url[$loop].usergroupname 2>/dev/null)
	  #      filter_way=$(uci get url_filter.@url[$loop].filter_way 2>/dev/null)
	  #      action=$(uci get url_filter.@url[$loop].action 2>/dev/null)
	  #      filter_content=$(uci get url_filter.@url[$loop].filter_content 2>/dev/null)
	  #      action1=$(uci get url_filter.@url[$loop].action1 2>/dev/null)
	  #      redirect=$(uci get url_filter.@url[$loop].redirect 2>/dev/null)
	  #      break
	  #   }
	  #   loop=$(($loop+1))
	  #   result=$(uci get url_filter.@url[$loop].urlgroupname 2>/dev/null)
   # done

   # loop=$(($loop+1))
   # result=$(uci get url_filter.@url[$loop].urlgroupname 2>/dev/null)
   # while [ x$result != 'x' ];do
   # 		local tmpx="url_${result}_url"
   #     local ret=$(iptables -w -t mangle -n -L url_filter --line-number | grep "\b$tmpx\b" | cut -d ' ' -f 1)
   #     if [ x"$ret" != 'x' ];then
   #        ret=${ret//\n/ }     
   #        for i in $ret;do
   #          position=$i  # just get the first if have many
   #          break
   #        done  
   #        break
   #     fi
   #    loop=$(($loop+1))
   #    result=$(uci get url_filter.@url[$loop].urlgroupname 2>/dev/null)
   # done
   lua /lib/urlfilter/find_target.lua $target_name
   local line_number=0
   local line=""
   while read line
   do
   		line_number=$(($line_number+1))
   		[ $line_number -eq 1 ] && position=$line
   		[ $line_number -eq 2 ] && filter_way=$line
   		[ $line_number -eq 3 ] && action=$line
   		[ $line_number -eq 4 ] && usergrp=$line
   		[ $line_number -eq 5 ] && filter_content=$line
   		[ $line_number -eq 6 ] && action1=$line
   		[ $line_number -eq 7 ] && redirect=$line
   done </tmp/url_rule.tmp
}

{
	flock 9
	local type=$1
	local enable=$(uci get filter_global.@filter_global[0].enable)
	[ "$enable" != '1' -a "$enable" != 'on' ] && return 0
	case $type in 
		add)
			local urlgrp=$2
			local special=""
			local tmp_act="ACCEPT"
			get_other_info $urlgrp
			#echo "pos=$position,urlgrp=$2,usergrp=$usergrp,action=$action,filter_way=$filter_way,filter_content=$filter_content,action1=$action1" >>/tmp/url_log
			local filter_mode="keyword"
			[ $action == "drop" ] && action="drop_reset" && tmp_act="DROP"
			[ x"$filter_way" = "xurl" ] && filter_mode="url"
			[ x"$filter_way" = "xcontroller_url" ] && filter_mode="controller_url"
			local targetx=""
			local tourl=""
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
			#echo "action=$action"
			#echo "targetx=$targetx"
			#echo "tourl=$tourl"
			echo "time=$time,usergroup=$usergroup,urlgroup=$urlgroup"
			if [ ${targetx}x == 'x' ];then
				targetx=""
			else
				targetx="--target $targetx"
			fi
			echo "targetx=$targetx"
			[ "$filter_content" == "." ] && {
				local id="11702"
				[ $action == "accept" ] && id="11811"

				if [ x"$usergrp" == "xIPGROUP_ANY" ];then
					iptables -w -t mangle -A url_filter -m conntrack --ctdir ORIGINAL -p tcp -m urlsetmatch --filter special -m comment --comment url_${urlgrp}_url -j urlsettarget --type $action $targetx $tourl --common $id,"Any"
					iptables -w -t mangle -A url_filter_dns -p udp -m url_dns_match --filter special --type dns -m comment --comment url_${urlgrp}_url -j $tmp_act
				else
					iptables -w -t mangle -A url_filter -m conntrack --ctdir ORIGINAL -p tcp -m set --match-set $usergrp src -m urlsetmatch --filter special -m comment --comment url_${urlgrp}_url -j urlsettarget --type $action $targetx $tourl --common $id,$usergrp
					iptables -w -t mangle -A url_filter_dns -p udp -m set --match-set $usergrp src -m url_dns_match --filter special --type dns -m comment --comment url_${urlgrp}_url -j $tmp_act
				fi	
				return 
			}
			urlset create $urlgrp ac url
			for i in $filter_content;do
				urlset add "$i" $urlgrp
				[ "x${i%%/}" = "x${i}" ] && {
					urlset add "$i/" $urlgrp
				}
			done
			urlset add '#end#' $urlgrp
			echo "begin to add rule" 
			local dns_pos=""
			if [ $position == "0" ];then
				position="-A url_filter"
				dns_pos="-A url_filter_dns"
			else
				dns_pos="-I url_filter_dns $position"
				position="-I url_filter $position"
			fi
			
			local id="11702"
			[ $action == "accept" ] && id="11811"

			if [ x"$usergrp" == "xIPGROUP_ANY" ];then
				iptables -w -t mangle $position -m conntrack --ctdir ORIGINAL -p tcp -m urlsetmatch --setname $urlgrp --filter $filter_mode -m comment --comment url_${urlgrp}_url -j urlsettarget --type $action $targetx $tourl --common $id,"Any"
				iptables -w -t mangle $dns_pos -p udp  -m url_dns_match --setname $urlgrp --filter $filter_mode --type dns -m comment --comment url_${urlgrp}_url -j $tmp_act
			else
				iptables -w -t mangle $position -m conntrack --ctdir ORIGINAL -p tcp -m set --match-set $usergrp src -m urlsetmatch --setname $urlgrp --filter $filter_mode -m comment --comment url_${urlgrp}_url -j urlsettarget --type $action $targetx $tourl --common $id,$usergrp
				iptables -w -t mangle $dns_pos -p udp -m set --match-set $usergrp src -m url_dns_match --setname $urlgrp --filter $filter_mode --type dns -m comment --comment url_${urlgrp}_url -j $tmp_act
			fi

		;;
		del)
			local key=url_$2_url
			local ret=$(iptables -w -t mangle -n -L url_filter --line-number | grep "\b$key\b" | cut -d ' ' -f 1)
			[ "$ret" != "" ] && {
				iptables -w -t mangle -D url_filter $ret
			}
			ret=$(iptables -w -t mangle -n -L url_filter_dns --line-number | grep "\b$key\b" | cut -d ' ' -f 1)
			[ "$ret" != "" ] && {
				iptables -w -t mangle -D url_filter_dns $ret
			}
			urlset destroy $2
		;;
		*)
			return
		;;
	esac
} 9<>/tmp/urlfilter
