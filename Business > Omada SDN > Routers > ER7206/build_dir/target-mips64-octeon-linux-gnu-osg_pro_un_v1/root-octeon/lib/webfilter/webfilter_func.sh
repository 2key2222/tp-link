#!/bin/sh

. /lib/firewall/fw.sh
. /lib/zone/zone_api.sh

local config_file="webfilter"
local IPT="iptables -w"

local group=""
local rule_type=""
local action=""
local website=""
local redirect=""
local position=0

fw_check() {
  local ret=$(iptables -w -t $1 -C $2 $3 2>&1)
  [ -n "$ret" ] && return 0||return 1
}

get_other_info(){
	local target_name=$1
  	# local loop=0

  	# local result=$(uci get webfilter.@webfilter[$loop].rulename 2>/dev/null)
  	# while [ x$result != 'x' ];do
	  #   local name=$result
	  #   [ $name == $target_name ] && {
	  #      group=$(uci get webfilter.@webfilter[$loop].group 2>/dev/null)
	  #      rule_type=$(uci get webfilter.@webfilter[$loop].rule_type 2>/dev/null)
	  #      action=$(uci get webfilter.@webfilter[$loop].action 2>/dev/null)
	  #      website=$(uci get webfilter.@webfilter[$loop].website 2>/dev/null)
	  #      redirect=$(uci get webfilter.@webfilter[$loop].redirect 2>/dev/null)
	  #      break
	  #   }
	  #   loop=$(($loop+1))
	  #   result=$(uci get webfilter.@webfilter[$loop].rulename 2>/dev/null)
   # done

   # loop=$(($loop+1))
   # result=$(uci get webfilter.@webfilter[$loop].rulename 2>/dev/null)
   # while [ x$result != 'x' ];do
   #     local ret=$(iptables -w -t mangle -n -L webfilter --line-number | grep "\burl_${result}_url\b" | cut -d ' ' -f 1)
   #     if [ x"$ret" != 'x' ];then
   #        ret=${ret//\n/ }     
   #        for i in $ret;do
   #          position=$i  # just get the first if have many
   #          break
   #        done  
   #        break
   #     fi
   #    loop=$(($loop+1))
   #    result=$(uci get webfilter.@webfilter[$loop].rulename 2>/dev/null)
   # done
   lua /lib/webfilter/find_target.lua $target_name
   local line_number=0
   local line=""

   while read line
   do
   	  line_number=$(($line_number+1))
   	  [ $line_number -eq 1 ] && position=$line
   	  [ $line_number -eq 2 ] && group=$line
   	  [ $line_number -eq 3 ] && rule_type=$line
   	  [ $line_number -eq 4 ] && action=$line
   	  [ $line_number -eq 5 ] && website=$line
   	  [ $line_number -eq 6 ] && redirect=$line
   done </tmp/web_rule.tmp
}

{
  flock 5
  local cmd=$1
  local enable=$(uci get webfilter_global.settings.enable)
  [ "$enable" == 'off' ] && return 0
  case $cmd in
  	add)
		local rulename=$2 
		get_other_info $rulename
		echo "rulename=$rulename,group=$group,rule_type=$rule_type,action=$action,website=$website,redirect=$redirect,time=$time,state=$state"
		local targetx=""
		local tourl=""
		local acc="accept"
		local tmp_act="ACCEPT"
		[ $rule_type == "off" ] && acc="drop_reset" && tmp_act="DROP"
		for i in $action;do
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
		local match=""
		local tmp_match=""
		if [ $all_flag == "0" ];then
			match="-m webfiltermatch --setname $matchset --filter keyword"
			tmp_match="-m web_dns_match --setname $matchset --filter keyword --type dns"
		else
			match="-m webfiltermatch --filter special"
			tmp_match="-m web_dns_match --filter special --type dns"
		fi

		local tmp_pos=""
		if [ $position == "0" ];then
			position="-A webfilter"
			tmp_pos="-A webfilter_dns"
		else
			tmp_pos="-I webfilter_dns $position"
			position="-I webfilter $position"
		fi
		local id="11702"
		[ $acc == "accept" ] && id="11811"
		if [ "$group" == "IPGROUP_ANY" ];then
			$IPT -t mangle $position -m conntrack --ctdir ORIGINAL -p tcp $match -m comment --comment url_${rulename}_url -j urlsettarget --type $acc $targetx $tourl --common $id,"Any"
			$IPT -t mangle $tmp_pos -p udp $tmp_match -m comment --comment url_${rulename}_url -j $tmp_act
		else
			$IPT -t mangle $position -m conntrack --ctdir ORIGINAL -p tcp -m set --match-set $group src $match -m comment --comment url_${rulename}_url -j urlsettarget --type $acc $targetx $tourl --common $id,$group
			$IPT -t mangle $tmp_pos -p udp -m set --match-set $group src $tmp_match -m comment --comment url_${rulename}_url -j $tmp_act
		fi
	;;
	del)
		local rulename=$2
		local ret=$(iptables -w -t mangle -n -L webfilter --line-number | grep "\burl_${rulename}_url\b" | cut -d ' ' -f 1)
		if [ x"$ret" != 'x' ];then
          $IPT -t mangle -D webfilter $ret
          rm -f /tmp/webfilter/$rulename
        fi
        ret=$(iptables -w -t mangle -n -L webfilter_dns --line-number | grep "\burl_${rulename}_url\b" | cut -d ' ' -f 1)
        if [ x"$ret" != 'x' ];then
        	$IPT -t mangle -D webfilter_dns $ret
        fi
	;;
   esac
} 5<>/tmp/webfilter_lock