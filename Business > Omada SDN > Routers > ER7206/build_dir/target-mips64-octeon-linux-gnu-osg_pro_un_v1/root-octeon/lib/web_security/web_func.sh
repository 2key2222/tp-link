#!/bin/sh

. /lib/firewall/fw.sh

local IPT="iptables -w"

local name=""
local addr=""
local websubmit=""
local fileext=""
local position=0

get_other_info_old(){
	local target_name=$1
  	local loop=0

  	local result=$(uci get web_security.@rule[$loop].name 2>/dev/null)
  	while [ x$result != 'x' ];do
	    local name=$result
	    [ $name == $target_name ] && {
	       addr=$(uci get web_security.@rule[$loop].addr 2>/dev/null)
	       websubmit=$(uci get web_security.@rule[$loop].websubmit 2>/dev/null)
	       fileext=$(uci get web_security.@rule[$loop].fileext 2>/dev/null)
	       break
	    }
	    loop=$(($loop+1))
	    result=$(uci get web_security.@rule[$loop].name 2>/dev/null)
   done

   loop=$(($loop+1))
   result=$(uci get web_security.@rule[$loop].name 2>/dev/null)
   while [ x$result != 'x' ];do
   	   local tmp="sec_${result}_sec"
       local ret=$(iptables -w -t mangle -n -L websec --line-number | grep "\b$tmp\b" | cut -d ' ' -f 1)
       if [ x"$ret" != 'x' ];then
          ret=${ret//\n/ }     
          for i in $ret;do
            position=$i  # just get the first if have many
            break
          done  
          break
       fi
      loop=$(($loop+1))
      result=$(uci get web_security.@rule[$loop].name 2>/dev/null)
   done
}

get_other_info(){
	local target_name=$1
	lua /lib/web_security/websec_timeobj.lua $target_name
	local line_number=0
	while read line 
	do
	  line_number=$(($line_number+1))
	  [ $line_number -eq 1 ] && fileext=${line}
	  [ $line_number -eq 2 ] && websubmit=${line}
	  [ $line_number -eq 3 ] && addr=${line} 
	  [ $line_number -eq 4 ] && position=${line} 
	done < /tmp/websec_rule.tmp
}

{
	flock 6
	local cmd=$1
	local enable=$(uci get web_security.default.state)
	[ "$enable" == "off" ] && return 0
	case $cmd in
		add)
			local name=$2
			local post_filter=""
			get_other_info $name
			urlset create $name weburl websec 100
			for i in $fileext;do
				urlset add $i $name
			done
			#echo "name=$name,addr=$addr,websubmit=$websubmit,fileext=$fileext" >>/tmp/test.txt
			#urlset add '#end#' $name
			#match module

			[ "$websubmit" == "on" ] && post_filter="--filter submit"
			
			if [ $position == "0" ];then
				position="-A websec"
			else
				position="-I websec $position"
			fi

			if [ "$addr" == "IPGROUP_ANY" ];then
				iptables -w -t mangle $position -p tcp -m websecmatch $post_filter --setname $name -m comment --comment  sec_${name}_sec -j urlsettarget --type drop #--target log 
			else
				iptables -w -t mangle $position -p tcp -m set --match-set $addr src -m websecmatch $post_filter --setname $name -m comment --comment sec_${name}_sec -j urlsettarget --type drop #--target log 
			fi
		;;
		del) 
		   local rulename=$2
		   local ret=$(iptables -w -t mangle -n -L websec --line-number | grep "\bsec_${rulename}_sec\b" | cut -d ' ' -f 1)
		   if [ x"$ret" != 'x' ];then
	          $IPT -t mangle -D websec $ret
	          rm /tmp/web_security/$rulename
	       fi
	       urlset destroy $rulename
		;;
	esac
} 6<>/tmp/websec_lock