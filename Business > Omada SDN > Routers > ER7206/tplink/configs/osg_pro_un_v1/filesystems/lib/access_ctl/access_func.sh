#!/bin/sh
. /lib/firewall/fw.sh
. /lib/zone/zone_api.sh

local config_file="access_ctl"
# options of access_ctl
local zone=""
local service=""
local src=""
local dest=""
local srcIf=""
local destIf=""
local srcIfName=""
local destIfName=""
local name=""
local policy=""
local position=0

ACL_LOG()
{
  t="`date +"%Y-%M-%d %H:%m:%S"`"
  #echo "$t ---> $1" >> /tmp/acl_rule.log
}

fw_acl_ipset_check()
{
  #echo "argv1=$1"
  local ret=$(ipset -L|grep $1 | awk '{print $2}')

  #[ "$ret" == "$1" ] && return 0||return 1
  return 0

}

fw_check() {
  local vnet_prefix=$4
  local ret=$(${vnet_prefix} iptables -w -t $1 -C $2 $3 2>&1)
  [ -n "$ret" ] && return 0||return 1
}

# reversed-order,have to find the rule before the given rulename,then insert it 
get_other_info(){
  local target_name=$1
  #local loop=0
  #local result=$(uci get access_ctl.@rule_acl_inner[$loop].name 2>/dev/null)
  #while [ x$result != 'x' ];do
  #  local name=$result
  #  [ $name == $target_name ] && {
  #     zone=$(uci get access_ctl.@rule_acl_inner[$loop].zone 2>/dev/null)
  #     service=$(uci get access_ctl.@rule_acl_inner[$loop].service 2>/dev/null)
  #     src=$(uci get access_ctl.@rule_acl_inner[$loop].src 2>/dev/null)
  #     dest=$(uci get access_ctl.@rule_acl_inner[$loop].dest 2>/dev/null)
  #     policy=$(uci get access_ctl.@rule_acl_inner[$loop].policy 2>/dev/null)
  #     break
  #  }
  #  loop=$(($loop+1))
  #  result=$(uci get access_ctl.@rule_acl_inner[$loop].name 2>/dev/null)
  #done
   # as config file stores the item in a reversed order,so,we need to keep on going
  # loop=$(($loop+1))
  # result=$(uci get access_ctl.@rule_acl_inner[$loop].name 2>/dev/null)
  # while [ x$result != 'x' ];do
  #     local ret=$(iptables -w -n -L access_ctl --line-number | grep "\b${result}_1acl\b" | cut -d ' ' -f 1)
  #     if [ x"$ret" != 'x' ];then
  #        ret=${ret//\n/ }     
  #        for i in $ret;do
  #          position=$i  # just get the first if have many
  #          break
  #        done  
  #        break
  #     fi
  #    loop=$(($loop+1))
  #    result=$(uci get access_ctl.@rule_acl_inner[$loop].name 2>/dev/null)
  # done

   #local tmpx=0
   #while [ $tmpx -lt $loop ];do
   #  result=$(uci get access_ctl.@rule_acl_inner[$tmpx].name 2>/dev/null)
   #  local ret=$(iptables -n -L access_ctl --line-number | grep $result | cut -d ' ' -f 1)
   #  if [ x"$ret" != 'x' ];then
   #     ret=${ret//\n/ }
        #local OLDIFS=$IFS
        #IFS='\n'
   #     for i in $ret;do
   #       position=$i  # just get the first one if have many
   #       break
   #     done
        #IFS=$OLDIFS
   #  fi
   # tmpx=$(($tmpx+1))
   #done

   ACL_LOG "start get other info for rule $target_name"
   lua /lib/access_ctl/acl_timeobj.lua $target_name
   local line_number=0
   while read line 
   do
      line_number=$(($line_number+1))
      [ $line_number -eq 1 ] && zone=${line}
      [ $line_number -eq 2 ] && service=${line}
      [ $line_number -eq 3 ] && src=${line}
      [ $line_number -eq 4 ] && dest=${line}
      [ $line_number -eq 5 ] && srcIf=${line}
      [ $line_number -eq 6 ] && destIf=${line}
      [ $line_number -eq 7 ] && srcIfName=${line}
      [ $line_number -eq 8 ] && destIfName=${line}
      [ $line_number -eq 9 ] && policy=${line}
      [ $line_number -eq 10 ] && position=${line} 
  done < /tmp/acl_rule.tmp
  [ "$policy" == "ACCEPT" ] && policy="RETURN"
   ACL_LOG "stop get other info for rule $target_name"
}

delete_rule()
{
  local rulename=$1
  local vnet_prefix=$2
  local rulenumber=$(${vnet_prefix} iptables -w -nvL access_ctl --line-numbers | grep "\<${rulename}_1acl\>" | wc -l)
  if [ "x${rulenumber}" == "x0" ]; then
    # no rule exist in iptables
    ACL_LOG "no rule in iptables for $rulename"
    return 
  fi
  local firstposition=$(${vnet_prefix} iptables -w -nvL access_ctl --line-numbers | grep "\<${rulename}_1acl\>" | head -1 | awk '{print $1}')
  ACL_LOG "position in iptables for $rulename is $firstposition"
  for i in `seq 1 ${rulenumber}`; do
    ${vnet_prefix} iptables -w -D access_ctl ${firstposition}
  done
}

add_rule(){
	local rulename=$1
    local is_delete=$2
    echo "before get_other_info"
    # according to rulename,get the item of 
    # if [ x$is_delete == 'x' -o x$is_delete == 'x0' ];then
    if [ x$is_delete == 'x' ];then
		ACL_LOG "action for rule $rulename to add"
	else
		delete_rule ${rulename}
		delete_rule ${rulename} "vnete"
		ACL_LOG "action for rule $rulename to delete"
		return
	fi
	get_other_info $rulename
	# local service_name=$1
	# local service_proto=$2
	# local service_sport=$3
	# local service_dport=$4
	# local service_type=$5
	# local service_code=$6
	
	local vnet_prefix=""
	if [ $zone == "VNET" ];then
		vnet_prefix="vnete"
	else
		vnet_prefix=
	fi

	echo "only after log"
	#new added
	# local rulename=$7
    #end add
	#  local is_delete=$8
    local set_src_rule=""
    local set_dst_rule=""
    local set_src_rule_reply=""
    local set_dst_rule_reply=""
	
	if [ $zone == "VNET" ];then
		local src_ifname=$(echo $srcIfName | grep "_REV$")
		if [ -n "$src_ifname" ]; then
			srcIfName=${srcIfName%_*}
			set_src_rule="! -i $srcIfName"
			set_dst_rule_reply="! -o $srcIfName"
		else
			set_src_rule="-i $srcIfName"
			set_dst_rule_reply="-o $srcIfName"
		fi
		
		local dst_ifname=$(echo $destIfName | grep "_REV$")
		if [ -n "$dst_ifname" ]; then
			destIfName=${destIfName%_*}
			set_dst_rule="! -o $destIfName"
			set_src_rule_reply="! -i $destIfName"
		else
			set_dst_rule="-o $destIfName"
			set_src_rule_reply="-i $destIfName"
		fi	
	else	
		if [ $src != "IPGROUP_ANY" ];then
			local src_group=$(echo $src |grep "_REV$")
			if [ -n "$src_group" ]; then
				local rule_acl_inner_src=${src%_*}
				fw_acl_ipset_check $rule_acl_inner_src
				[ x$? == x0 ] && {
					set_src_rule="-m set ! --match-set $rule_acl_inner_src src,src"
				} || return
			else
				fw_acl_ipset_check $src
				[ x$? == x0 ] && {
					set_src_rule="-m set --match-set $src src,src"
				} || return
			fi
		else
			set_src_rule=""   # IPGROUP_ANY
		fi

		if [ $dest != "IPGROUP_ANY" ];then
			local dst_group=$(echo $dest |grep "_REV$")
			if [ -n "$dst_group" ]; then
				local rule_acl_inner_dest=${dest%_*}
				fw_acl_ipset_check $rule_acl_inner_dest
				[ x$? == x0 ] && {
					set_dst_rule="-m set ! --match-set $rule_acl_inner_dest dst,dst"
				} || return
			else
				fw_acl_ipset_check $dest
				[ x$? == x0 ] && {
					set_dst_rule="-m set --match-set $dest dst,dst"
				} || return
			fi  
		else
			set_dst_rule=""
		fi
	fi
	
    echo "set_src_rule=$set_src_rule"
    echo "set_dst_rule=$set_dst_rule"
	echo "set_src_rule_reply=$set_src_rule_reply"
    echo "set_dst_rule_reply=$set_dst_rule_reply"
        
	local interface=""
    local device=""
    local zone_flag=0	# [zone_flag] 1: ALL or VNET, no need to set interface, 0: Others, need to set interface
    if [ $zone == "ALL" -o $zone == "VNET" ];then
		zone_flag=1
	else
		zone_flag=0
	fi
    for interface in ${zone};do
		local xyy=""
        if [ $zone_flag == '1' ];then
			xyy="eth0"
		else
			xyy=$(zone_get_wan_devices $interface)
		fi
		
		for device in $xyy;do
			[ -z $device ] && continue
			
			if [ "$service" == "ALL" ]; then
				local tmpa=""
				[ $zone_flag != '1' ] && tmpa="-i $device"
				local rule="$tmpa"" ""$set_src_rule"" ""$set_dst_rule"" ""-m comment --comment ${rulename}_1acl"
				local rule_reply="$tmpa"" ""$set_src_rule_reply"" ""$set_dst_rule_reply"" ""-m comment --comment ${rulename}_1acl"
				
				if [ x$is_delete == "x" ];then
					fw_check "filter" "access_ctl" "$rule -j $policy" ${vnet_prefix}
					[ x$? == x0 ] && {
						if [ $position == 0 ];then
							${vnet_prefix} iptables -w -A access_ctl $rule -j ${policy}
							[ $zone == "ALL" ] && vnete iptables -w -A access_ctl $rule -j ${policy}
							[ $zone == "VNET" ] && vnete iptables -w -A access_ctl $rule_reply -j ${policy}
						else
							${vnet_prefix} iptables -w -I access_ctl $position $rule -j ${policy}
							[ $zone == "ALL" ] && vnete iptables -w -I access_ctl $position $rule -j ${policy}
							[ $zone == "VNET" ] && vnete iptables -w -I access_ctl $position $rule_reply -j ${policy}
						fi
                    }
				else
					fw_check "filter" "access_ctl" "$rule -j ${policy}" ${vnet_prefix}
					if [ x$? == x1 ];then
						fw del 4 f access_ctl ${policy} $ $vnet_prefix { $rule }
						[ $zone == "ALL" ] && fw del 4 f access_ctl ${policy} $ vnete { $rule }
						[ $zone == "VNET" ] && fw del 4 f access_ctl ${policy} $ $vnet_prefix { $rule_reply }
					fi
				fi
            else
				echo "enter into non-all branch"
				local service_name
				local service_sport
				local service_dport
				local service_proto
				local service_type
				local service_code
				echo "=================="
				echo "service: $service"
				for i in $service; do
					service_name=$(uci get service.$i.name)
					service_sport=$(uci get service.$i.sport)
					service_dport=$(uci get service.$i.dport)
					service_proto=$(uci get service.$i.proto)
					service_type=$(uci get service.$i.type)
					service_code=$(uci get service.$i.code)
					
					echo "service[$i].name: $service_name"
					echo "service[$i].proto: $service_proto"
					
					service_name=$(echo $service_name | tr '[a-z]' '[A-Z]')
					if [ "$service_proto" != "icmp" ]; then
						service_proto=$(echo $service_proto | tr '[a-z]' '[A-Z]')
						if [ $service_proto == "TCP" -o $service_proto == "UDP" ];then
							service_sport=$(echo $service_sport|tr '-' ':')
							service_dport=$(echo $service_dport|tr '-' ':')
							echo "service_proto=$service_proto"
							#for proto in $service_proto; do
							local tmpb=""
							[ $zone_flag != '1' ] && tmpb="-i $device"
							local proto=$(echo $service_proto | tr '[A-Z]' '[a-z]') 
							local rule="$tmpb -p $proto -m $proto --sport $service_sport --dport $service_dport \
								$set_src_rule  $set_dst_rule -m comment --comment ${rulename}_1acl"
							local rule_reply="$tmpb -p $proto -m $proto --dport $service_sport --sport $service_dport \
								$set_src_rule_reply $set_dst_rule_reply -m comment --comment ${rulename}_1acl"
							if [ x$is_delete == "x" ];then
								fw_check "filter" "access_ctl" "$rule -j ${policy}" ${vnet_prefix}
								[ x$? == x0 ] && {
									local tmpc=""
									[ $zone_flag != '1' ] && tmpc="-i $device"
									if [ $position == 0 ];then
										${vnet_prefix} iptables -w -A access_ctl $rule -j ${policy}
										[ $zone == "ALL" ] && vnete iptables -w -A access_ctl $rule -j ${policy}
										[ $zone == "VNET" ] && vnete iptables -w -A access_ctl $rule_reply -j ${policy}
									else
										${vnet_prefix} iptables -w -I access_ctl $position $rule -j ${policy}
										[ $zone == "ALL" ] && vnete iptables -w -I access_ctl $position $rule -j ${policy}
										[ $zone == "VNET" ] && vnete iptables -w -I access_ctl $position $rule_reply -j ${policy}
									fi
								}
							else
								fw_check "filter" "access_ctl" "$rule -j ${policy}" ${vnet_prefix}
								if [ x$? == x1 ];then
									fw del 4 f access_ctl ${policy} $ $vnet_prefix { $rule }
									[ $zone == "ALL" ] && fw del 4 f access_ctl ${policy} $ vnete { $rule }
									[ $zone == "VNET" ] && fw del 4 f access_ctl ${policy} $ $vnet_prefix { $rule_reply }
								fi
							fi
                        #done
                        else  # proto other
							echo "enter into proto other branch"
							if [ $service_proto == "TCP-UDP" ];then #TCP/UDP
								service_sport=$(echo $service_sport|tr '-' ':')
								service_dport=$(echo $service_dport|tr '-' ':')
								echo "service_proto=$service_proto"
								for proto in $service_proto; do
									local tmpd=""
									[ $zone_flag != '1' ] && tmpd="-i $device"
									local tcp_rule="$tmpd -p tcp -m tcp --sport $service_sport --dport $service_dport \
										$set_src_rule  $set_dst_rule -m comment --comment ${rulename}_1acl"
									local udp_rule="$tmpd -p udp -m udp --sport $service_sport --dport $service_dport \
										$set_src_rule  $set_dst_rule -m comment --comment ${rulename}_1acl"
									local tcp_rule_reply="$tmpd -p tcp -m tcp --dport $service_sport --sport $service_dport \
										$set_src_rule_reply  $set_dst_rule_reply -m comment --comment ${rulename}_1acl"
									local udp_rule_reply="$tmpd -p udp -m udp --dport $service_sport --sport $service_dport \
										$set_src_rule_reply  $set_dst_rule_reply -m comment --comment ${rulename}_1acl"
									
									if [ x$is_delete == "x" ];then
										fw_check "filter" "access_ctl" "$tcp_rule -j $policy" ${vnet_prefix}
										[ x$? == x0 ] && {
											local tmpe=""
											[ $zone_flag != '1' ] && tmpe="-i $device"
											if [ $position == 0 ];then
												${vnet_prefix} iptables -w -A access_ctl $tcp_rule -j ${policy}
												[ $zone == "ALL" ] && vnete iptables -w -A access_ctl $tcp_rule -j ${policy}
												[ $zone == "VNET" ] && vnete iptables -w -A access_ctl $tcp_rule_reply -j ${policy}
											else
												${vnet_prefix} iptables -w -I access_ctl $position $tcp_rule -j ${policy}
												[ $zone == "ALL" ] && vnete iptables -w -I access_ctl $position $tcp_rule -j ${policy}
												[ $zone == "VNET" ] && vnete iptables -w -I access_ctl $position $tcp_rule_reply -j ${policy}
											fi
										}
										fw_check "filter" "access_ctl" "$udp_rule -j $policy" ${vnet_prefix}
										[ x$? == x0 ] && {
											local tmpf=""
											[ $zone_flag != '1' ] && tmpf="-i $device"
											if [ $position == 0 ];then
												${vnet_prefix} iptables -w -A access_ctl $udp_rule -j ${policy}
												[ $zone == "ALL" ] && vnete iptables -w -A access_ctl $udp_rule -j ${policy}
												[ $zone == "VNET" ] && vnete iptables -w -A access_ctl $udp_rule_reply -j ${policy}
											else
												${vnet_prefix} iptables -w -I access_ctl $position $udp_rule -j ${policy}
												[ $zone == "ALL" ] && vnete iptables -w -I access_ctl $position $udp_rule -j ${policy}
												[ $zone == "VNET" ] && vnete iptables -w -I access_ctl $position $udp_rule_reply -j ${policy}
											fi
										}
									else
										fw_check "filter" "access_ctl" "$tcp_rule -j $policy" ${vnet_prefix}
										if [ x$? == x1 ];then
											fw del 4 f access_ctl $policy $ $vnet_prefix { $tcp_rule }
											[ $zone == "ALL" ] && fw del 4 f access_ctl $policy $ vnete { $tcp_rule } 
											[ $zone == "VNET" ] && fw del 4 f access_ctl $policy $ $vnet_prefix { $tcp_rule_reply }
										fi
										fw_check "filter" "access_ctl" "$udp_rule -j $policy" ${vnet_prefix}
										if [ x$? == x1 ];then
											fw del 4 f access_ctl $policy $ $vnet_prefix { $udp_rule }
											[ $zone == "ALL" ] && fw del 4 f access_ctl $policy $ vnete { $udp_rule }
											[ $zone == "VNET" ] && fw del 4 f access_ctl $policy $ $vnet_prefix { $udp_rule_reply }
										fi
									fi
								done
							else  #other
								echo ">>> Enter \"Other\" branch"
								for proto in $service_proto;do
									local tmpg=""
                                    [ $zone_flag != '1' ] && tmpg="-i $device"
                                    local rule="$tmpg -p $proto $set_src_rule $set_dst_rule -m comment --comment ${rulename}_1acl"
									local rule_reply="$tmpg -p $proto $set_src_rule_reply $set_dst_rule_reply -m comment --comment ${rulename}_1acl"
                                    if [ x$is_delete == "x" ];then
										fw_check "filter" "access_ctl" "$rule -j $policy" ${vnet_prefix}
										[ x$? == x0 ] && {
											if [ $position == 0 ];then
												${vnet_prefix} iptables -w -A access_ctl $rule -j ${policy}
												[ $zone == "ALL" ] && vnete iptables -w -A access_ctl $rule -j ${policy}
												[ $zone == "VNET" ] && vnete iptables -w -A access_ctl $rule_reply -j ${policy}
											else
												${vnet_prefix} iptables -w -I access_ctl $position $rule -j ${policy}
												[ $zone == "ALL" ] && vnete iptables -w -I access_ctl $position $rule -j ${policy}
												[ $zone == "VNET" ] && vnete iptables -w -I access_ctl $position $rule_reply -j ${policy}
											fi
										}
                                    else
										fw_check "filter" "access_ctl" "$rule -j $policy" ${vnet_prefix}
										if [ x$? == x1 ];then
											fw del 4 f access_ctl $policy $ $vnet_prefix { $rule }
											[ $zone == "ALL" ] && fw del 4 f access_ctl $policy $ vnete { $rule }
											[ $zone == "VNET" ] && fw del 4 f access_ctl $policy $ $vnet_prefix { $rule_reply }
										fi
                                    fi
								done
							fi
						fi
					else
                        if [ "$service_name" == "ICMP_ALL" ]; then
                            local tmph=""
                            [ $zone_flag != '1' ] && tmph="-i $device"
                            local rule="$tmph -p $service_proto --icmp-type any $set_src_rule $set_dst_rule -m comment --comment ${rulename}_1acl"
                            local rule_reply="$tmph -p $service_proto --icmp-type any $set_src_rule_reply $set_dst_rule_reply -m comment --comment ${rulename}_1acl"
                            if [ x$is_delete == "x" ]; then
								fw_check "filter" "access_ctl" "$rule -j $policy" ${vnet_prefix}
								[ x$? == x0 ] && {
									if [ $position == 0 ];then
										${vnet_prefix} iptables -w -A access_ctl $rule -j ${policy}
										[ $zone == "ALL" ] && vnete iptables -w -A access_ctl $rule -j ${policy}
										[ $zone == "VNET" ] && vnete iptables -w -A access_ctl $rule_reply -j ${policy}
									else
										${vnet_prefix} iptables -w -I access_ctl $position $rule -j ${policy}
										[ $zone == "ALL" ] && vnete iptables -w -I access_ctl $position $rule -j ${policy}
										[ $zone == "VNET" ] && vnete iptables -w -I access_ctl $position $rule_reply -j ${policy}
									fi
                    			}
                            else
                                fw_check "filter" "access_ctl" "$rule -j $policy" ${vnet_prefix}
                                if [ x$? == x1 ];then
									fw del 4 f access_ctl $policy $ $vnet_prefix { $rule }
									[ $zone == "ALL" ] && fw del 4 f access_ctl $policy $ vnete { $rule }
									[ $zone == "VNET" ] && fw del 4 f access_ctl $policy $ $vnet_prefix { $rule_reply }
								fi
                            fi
                        else
							local tmpi=""
							[ $zone_flag != '1' ] && tmpi="-i $device"
							local rule="$tmpi -p $service_proto -m $service_proto --icmp-type $service_type/$service_code \
								$set_src_rule $set_dst_rule -m comment --comment ${rulename}_1acl"
							local rule_reply="$tmpi -p $service_proto -m $service_proto --icmp-type $service_type/$service_code \
								$set_src_rule_reply $set_dst_rule_reply -m comment --comment ${rulename}_1acl"
							if [ x$is_delete == "x" ]; then
								fw_check "filter" "access_ctl" "$rule -j $policy" ${vnet_prefix}
								[ x$? == x0 ] && {
									if [ $position == 0 ];then
										${vnet_prefix} iptables -w -A access_ctl $rule -j ${policy}
										[ $zone == "ALL" ] && vnete iptables -w -A access_ctl $rule -j ${policy}
										[ $zone == "VNET" ] && vnete iptables -w -A access_ctl $rule_reply -j ${policy}
									else
										${vnet_prefix} iptables -w -I access_ctl $position $rule -j ${policy}
										[ $zone == "ALL" ] && vnete iptables -w -I access_ctl $position $rule -j ${policy}
										[ $zone == "VNET" ] && vnete iptables -w -I access_ctl $position $rule_reply -j ${policy}
									fi
								}
							else
								fw_check "filter" "access_ctl" "$rule -j $policy" ${vnet_prefix}
                                if [ x$? == x1 ];then
									fw del 4 f access_ctl $policy $ $vnet_prefix { $rule }
									[ $zone == "ALL" ] && fw del 4 f access_ctl $policy $ vnete { $rule }
									[ $zone == "VNET" ] && fw del 4 f access_ctl $policy $ $vnet_prefix { $rule_reply }
								fi
							fi
                        fi
					fi
				done
			fi
		done
	done
	ACL_LOG "action for rule $rulename stop "
}

# $1=rulename  $2=is_delete $3==>zone $4==>service_name $5==>src_group $6==>dest_group $7==>policy
# if $2 is empty,means 'add'.
{
  flock 4
  ACL_LOG "start add_rule $1"
  add_rule $1 $2 $3 $4 $5 $6 $7
  ACL_LOG "stop add_rule $1"
} 4<>/tmp/access_ctl_lock