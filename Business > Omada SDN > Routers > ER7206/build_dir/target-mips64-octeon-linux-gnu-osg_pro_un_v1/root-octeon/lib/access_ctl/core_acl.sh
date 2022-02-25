#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     access_ctl core.sh
# brief    
# author   Chen chen
# version  1.0.0
# date     08June15
# histry   arg 1.0.0, 08June15, Chen chen, Create the file. 
. /lib/access_ctl/time.sh

ACL_LOG()
{
	[ ! -e /tmp/access_ctl ] && mkdir touch /tmp/access_ctl
	[ -f /tmp/access_ctl/access_ctl.log ] && {
		local size="`ls -l /tmp/access_ctl/access_ctl.log | awk '{ print $5 }'`"
		if [ $size -gt 3072000 ]; then
			rm /tmp/access_ctl/access_ctl.log
		fi
	}
	[ ! -f /tmp/access_ctl/access_ctl.log ] && touch /tmp/access_ctl/access_ctl.log
	#echo "$1" >> /tmp/access_ctl/access_ctl.log
}

local known_service="FTP SSH TELNET SMTP DNS HTTP POP3 SNTP H323 TCPUDP"

fw_acl_ipset_check()
{
	#echo "argv1=$1"
	local ret=$(ipset -L -n $1)

	#[ "$ret" == "$1" ] && return 0||return 1
	return 0

}

fw_acl_config_get_rule_acl_inner() {
	fw_config_get_section "$1" rule_acl_inner { \
		string name "" \
		string zone "" \
		string policy "" \
		string service "" \
		string src "" \
		string dest "" \
		string srcIf "" \
		string destIf "" \
		string srcIfName "" \
		string destIfName "" \
		string time "" \
		string flag "" \
	} || return
}

fw_acl_config_get_rule_acl_btw() {
	fw_config_get_section "$1" rule_acl_btw { \
		string name "" \
		string zone "" \
		string policy "" \
		string service "" \
		string src "" \
		string dest "" \
		string time "" \
		string flag "" \
	} || return

}

service_config_get() {
	fw_config_get_section "$1" service { \
		string name "" \
		string proto "" \
		string sport "" \
		string dport "" \
		string type "" \
		string code "" \
		string comment "" \
		string flag "" \
	} || return
}

# need to reverse the rule order
fw_acl_do_acl_inner_rule()
{
	#fw_acl_config_get_rule_acl_inner $1
	local rule_acl_inner_service=""
	local rule_acl_inner_policy=""
	local rule_acl_inner_src=""
	local rule_acl_inner_srcIf=""
	local rule_acl_inner_srcIfName=""
	local rule_acl_inner_time=""
	local rule_acl_inner_dest=""
	local rule_acl_inner_destIf=""
	local rule_acl_inner_destIfName=""
	local rule_acl_inner_zone=""
	local rule_acl_inner_flag=""
	local rule_acl_inner_name=""
	local loop=0
	local destroy_flag=$2
	local vnet_prefix=0
	local result=$(uci get access_ctl.@rule_acl_inner[$loop].name 2>/dev/null)
	while [ x$result != 'x' ];do
		rule_acl_inner_service=$(uci get access_ctl.@rule_acl_inner[$loop].service 2>/dev/null)
		rule_acl_inner_policy=$(uci get access_ctl.@rule_acl_inner[$loop].policy 2>/dev/null)
		rule_acl_inner_src=$(uci get access_ctl.@rule_acl_inner[$loop].src 2>/dev/null)
		rule_acl_inner_srcIf=$(uci get access_ctl.@rule_acl_inner[$loop].srcIf 2>/dev/null)
		rule_acl_inner_srcIfName=$(uci get access_ctl.@rule_acl_inner[$loop].srcIfName 2>/dev/null)
		rule_acl_inner_time=$(uci get access_ctl.@rule_acl_inner[$loop].time 2>/dev/null)
		rule_acl_inner_dest=$(uci get access_ctl.@rule_acl_inner[$loop].dest 2>/dev/null)
		rule_acl_inner_destIf=$(uci get access_ctl.@rule_acl_inner[$loop].destIf 2>/dev/null)
		rule_acl_inner_destIfName=$(uci get access_ctl.@rule_acl_inner[$loop].destIfName 2>/dev/null)
		rule_acl_inner_zone=$(uci get access_ctl.@rule_acl_inner[$loop].zone 2>/dev/null)
		rule_acl_inner_flag=$(uci get access_ctl.@rule_acl_inner[$loop].flag 2>/dev/null)
		rule_acl_inner_name=$(uci get access_ctl.@rule_acl_inner[$loop].name 2>/dev/null)

		#echo "$rule_acl_inner_service,$rule_acl_inner_policy,$rule_acl_inner_src,$rule_acl_inner_time,$rule_acl_inner_dest,$rule_acl_inner_zone,$rule_acl_inner_flag"
		service_config_get $rule_acl_inner_service
		rule_acl_inner_policy=$(echo $rule_acl_inner_policy|tr '[a-z]' '[A-Z]')
		[ "$rule_acl_inner_policy" == "ACCEPT" ] && rule_acl_inner_policy="RETURN"

		[ "$rule_acl_inner_flag" == "1" ] && {
			if [ $destroy_flag == 1 ];then
				ACL_LOG "add rule ${loop}"
				
				if [ $rule_acl_inner_time == "Any" ];then
					if [ $rule_acl_inner_zone != "VNET" ];then
						local set_src_rule=""
						if [ "$rule_acl_inner_src" != "IPGROUP_ANY" ];then
							local ipset_src=${rule_acl_inner_src%_REV}
							if [[ "$ipset_src" == "$rule_acl_inner_src" ]]; then
								set_src_rule="-m set --match-set $ipset_src src"
							else
								set_src_rule="-m set ! --match-set $ipset_src src"
							fi
							set_src_rule="$set_src_rule,src"
						fi
						echo "set_src_rule=$set_src_rule"

						local set_dst_rule=""
						if [ "$rule_acl_inner_dest" != "IPGROUP_ANY" ];then
							local ipset_dst=${rule_acl_inner_dest%_REV}
							if [[ "$ipset_dst" == "$rule_acl_inner_dest" ]]; then
								set_dst_rule="-m set --match-set $ipset_dst dst"
							else
								set_dst_rule="-m set ! --match-set $ipset_dst dst"
							fi
							set_dst_rule="$set_dst_rule,dst"
						fi
						echo "set_dst_rule=$set_dst_rule"
					else
						local set_src_rule=""
						local set_dst_rule_reply=""
						local src_lan_ifname=${rule_acl_inner_srcIfName%_REV}
						if [[ "$src_lan_ifname" == "$rule_acl_inner_srcIfName" ]]; then
							set_src_rule="-i $src_lan_ifname"
							set_dst_rule_reply="-o $src_lan_ifname"
						else
							set_src_rule="! -i $src_lan_ifname"
							set_dst_rule_reply="! -o $src_lan_ifname"
						fi
						echo "set_src_rule=$set_src_rule"
						echo "set_dst_rule_reply=$set_dst_rule_reply"

						local set_dst_rule=""
						local set_src_rule_reply=""
						local dst_lan_ifname=${rule_acl_inner_destIfName%_REV}
						if [ "$dst_lan_ifname" == "$rule_acl_inner_destIfName" ];then
							set_dst_rule="-o $dst_lan_ifname"
							set_src_rule_reply="-i $dst_lan_ifname"
						else
							set_dst_rule="! -o $dst_lan_ifname"
							set_src_rule_reply="! -i $dst_lan_ifname"
						fi
						echo "set_dst_rule=$set_dst_rule"
						echo "set_src_rule_reply=$set_src_rule_reply"
					fi

					local interface=""
					local device=""
					local all_flag=0
					[ "$rule_acl_inner_zone" == "ALL" ] && all_flag=1

					for interface in ${rule_acl_inner_zone};do
						local xyy="eth0"
						local vnet_prefix=""
						[ "$all_flag" != '1' -a "$interface" != "VNET" ] && xyy=$(zone_get_wan_devices $interface)
						[ "$interface" == "VNET" ] && vnet_prefix="vnete" || vnet_prefix=""

						for device in $xyy;do
							[ -z "$device" ] && continue
							local input_dev=""
							[ "$all_flag" != '1' -a "$interface" != "VNET" ] && input_dev="-i $device"

							if [ "$service_name" == "ALL" ]; then #all
								ACL_LOG "position 1: add rule with device ${device} of loop ${loop} to iptables"
								$vnet_prefix iptables -w -A access_ctl $input_dev $set_src_rule $set_dst_rule \
									-m comment --comment ${rule_acl_inner_name}_1acl -j ${rule_acl_inner_policy}
								[ "$interface" == "ALL" ] && vnete iptables -w -A access_ctl $input_dev $set_src_rule $set_dst_rule \
									-m comment --comment ${rule_acl_inner_name}_1acl -j ${rule_acl_inner_policy}
								[ "$interface" == "VNET" ] && $vnet_prefix iptables -w -A access_ctl $set_src_rule_reply $set_dst_rule_reply \
									-m comment --comment ${rule_acl_inner_name}_1acl -j ${rule_acl_inner_policy}
							else
								echo "enter into non-all branch"
								local service_name
								local service_sport
								local service_dport
								local service_proto
								local service_type
								local service_code
								
								#echo "==================================="
								#echo "rule_acl_inner_service: $rule_acl_inner_service"
								
								for i in $rule_acl_inner_service; do
								service_name=$(uci get service.$i.name)
								service_sport=$(uci get service.$i.sport)
								service_dport=$(uci get service.$i.dport)
								service_proto=$(uci get service.$i.proto)
								service_type=$(uci get service.$i.type)
								service_code=$(uci get service.$i.code)
					
								service_name=$(echo $service_name | tr '[a-z]' '[A-Z]')
								service_proto=$(echo $service_proto | tr '[A-Z]' '[a-z]')
								
								#echo "service[$i].name: $service_name"
								#echo "service[$i].proto: $service_proto"
					
								if [ "$service_proto" != "icmp" ]; then
									# for UDP/TCP
									if [ "$service_proto" == "tcp" -o "$service_proto" == "udp" -o "$service_proto" == "tcp-udp" ];then 
										[ "$service_proto" == "tcp-udp" ] && service_proto="tcp udp"
										echo "service_proto=$service_proto"
										service_sport=$(echo $service_sport|tr '-' ':')
										service_dport=$(echo $service_dport|tr '-' ':')
										ACL_LOG "position 2: add rule with device ${device} of loop ${loop} to iptables"
										for proto in $service_proto; do
											$vnet_prefix iptables -w -A access_ctl $input_dev -p $proto -m $proto --sport $service_sport --dport $service_dport \
												$set_src_rule  $set_dst_rule -m comment --comment ${rule_acl_inner_name}_1acl -j ${rule_acl_inner_policy}
											[ "$interface" == "ALL" ] && vnete iptables -w -A access_ctl $input_dev -p $proto -m $proto --sport $service_sport --dport $service_dport \
												$set_src_rule  $set_dst_rule -m comment --comment ${rule_acl_inner_name}_1acl -j ${rule_acl_inner_policy}
											[ "$interface" == "VNET" ] && $vnet_prefix iptables -w -A access_ctl -p $proto -m $proto --dport $service_sport --sport $service_dport \
												$set_src_rule_reply  $set_dst_rule_reply -m comment --comment ${rule_acl_inner_name}_1acl -j ${rule_acl_inner_policy}
										done

									else  # for other
										echo "enter into proto other branch"
										for proto in $service_proto;do
											ACL_LOG "position 3: add rule with device ${device} of loop ${loop} to iptables"
											$vnet_prefix iptables -w -A access_ctl $input_dev -p $proto $set_src_rule $set_dst_rule \
												-m comment --comment ${rule_acl_inner_name}_1acl -j ${rule_acl_inner_policy}
											[ "$interface" == "ALL" ] && vnete iptables -w -A access_ctl $input_dev -p $proto $set_src_rule $set_dst_rule \
												-m comment --comment ${rule_acl_inner_name}_1acl -j ${rule_acl_inner_policy}
											[ "$interface" == "VNET" ] && $vnet_prefix iptables -w -A access_ctl -p $proto $set_src_rule_reply $set_dst_rule_reply \
												-m comment --comment ${rule_acl_inner_name}_1acl -j ${rule_acl_inner_policy}
										done
									fi

								else  # for icmp
									if [ "$service_name" == "ICMP_ALL" ]; then #icmp_all
										ACL_LOG "position 4: add rule with device ${device} of loop ${loop} to iptables"
										$vnet_prefix iptables -w -A access_ctl $input_dev -p $service_proto --icmp-type any \
											$set_src_rule $set_dst_rule -m comment --comment ${rule_acl_inner_name}_1acl -j ${rule_acl_inner_policy}
										[ "$interface" == "ALL" ] && vnete iptables -w -A access_ctl $input_dev -p $service_proto --icmp-type any \
											$set_src_rule $set_dst_rule -m comment --comment ${rule_acl_inner_name}_1acl -j ${rule_acl_inner_policy}
										[ "$interface" == "VNET" ] && $vnet_prefix iptables -w -A access_ctl -p $service_proto --icmp-type any \
											$set_src_rule_reply $set_dst_rule_reply -m comment --comment ${rule_acl_inner_name}_1acl -j ${rule_acl_inner_policy}
									
									else # icmp service_type & service_code
										ACL_LOG "position 5: add rule with device ${device} of loop ${loop} to iptables"
										$vnet_prefix iptables -w -A access_ctl $input_dev -p $service_proto -m $service_proto --icmp-type $service_type/$service_code \
											$set_src_rule $set_dst_rule -m comment --comment ${rule_acl_inner_name}_1acl -j ${rule_acl_inner_policy}
										[ "$interface" == "ALL" ] && vnete iptables -w -A access_ctl $input_dev -p $service_proto -m $service_proto --icmp-type $service_type/$service_code \
											$set_src_rule $set_dst_rule -m comment --comment ${rule_acl_inner_name}_1acl -j ${rule_acl_inner_policy}
										[ "$interface" == "VNET" ] && $vnet_prefix iptables -w -A access_ctl -p $service_proto -m $service_proto --icmp-type $service_type/$service_code \
											$set_src_rule_reply $set_dst_rule_reply -m comment --comment ${rule_acl_inner_name}_1acl -j ${rule_acl_inner_policy}
									fi
								fi
								done
							fi
						done
					done
				#else
				#	ACL_LOG "position 7: add rule to time object"
				#	add_timeobj $rule_acl_inner_time $rule_acl_inner_name
				fi
			else
				echo "this should print out"
				ACL_LOG "delelte rule ${loop}, actually do nothing"
				if [ $destroy_flag != 2 ];then
					ACL_LOG "destroy_flag is not 1 or 2"
					return 1
				fi
				[ $rule_acl_inner_time != "Any" ] && del_timeobj $rule_acl_inner_time $rule_acl_inner_name
			fi
			#conntrack -F
		}
		loop=$(($loop+1))
		result=$(uci get access_ctl.@rule_acl_inner[$loop].name 2>/dev/null)
	done

	if [ $destroy_flag == 1 ]; then
		ACL_LOG "iptables after add all rule"
		# iptables -w -nvL access_ctl >> /tmp/access_ctl/access_ctl.log
		ACL_LOG "end"
	else
		ACL_LOG "iptables after delete all rule"
		# iptables -w -nvL access_ctl >> /tmp/access_ctl/access_ctl.log
		ACL_LOG "end"
	fi
}

fw_acl_do_acl_btw_rule()
{
	fw_acl_config_get_rule_acl_btw $1
	service_config_get $rule_acl_btw_service

	[ "$rule_acl_btw_flag" == "2" ] && {
		src_zone=${rule_acl_btw_zone%-*}
		dst_zone=${rule_acl_btw_zone#*-}
	}
	
	rule_acl_btw_policy=$(echo $rule_acl_btw_policy|tr '[a-z]' '[A-Z]')

	[ "$rule_acl_btw_flag" == "2" ] && {
		src_devices=$(zone_get_wan_devices "${src_zone}")
		dst_devices=$(zone_get_wan_devices "${dst_zone}")

		set_src_rule=""
		if [ $rule_acl_btw_src != "IPGROUP_ANY" ];then
			src_group=$(echo $rule_acl_btw_src |grep "REV")
			
			if [ -n "$src_group" ]; then
				rule_acl_btw_src=${rule_acl_btw_src%_*}
				
				fw_acl_ipset_check $rule_acl_btw_src
				[ x$? == x0 ] && {
					set_src_rule="-m set ! --match-set $rule_acl_btw_src src"
				} || return
				
					
			else
				fw_acl_ipset_check $rule_acl_btw_src
				[ x$? == x0 ] && {
					set_src_rule="-m set --match-set $rule_acl_btw_src src"
				} || return
				
			fi
		else
			set_src_rule=""		# IPGROUP_ANY
		fi
		set_src_rule="$set_src_rule,src"
		#echo "set_src_rule=$set_src_rule"

		set_dst_rule=""
		if [ $rule_acl_btw_dest != "IPGROUP_ANY" ];then
			dst_group=$(echo $rule_acl_btw_dest |grep "REV")
			if [ -n "$dst_group" ]; then
				rule_acl_btw_dest=${rule_acl_btw_dest%_*}
				fw_acl_ipset_check $rule_acl_btw_dest
				[ x$? == x0 ] && {
					set_dst_rule="-m set ! --match-set $rule_acl_btw_dest dst"

				} || return
				
			else
				fw_acl_ipset_check $rule_acl_btw_dest
				[ x$? == x0 ] && {
					set_dst_rule="-m set --match-set $rule_acl_btw_dest dst"
				} || return
				
			fi
				
		else
			set_dst_rule=""
		fi
		set_dst_rule="$set_dst_rule,dst"
		#echo "set_dst_rule=$set_dst_rule"

		for src_device in $src_devices;do
			[ -z $src_device ] && continue
			for dst_device in $dst_devices; do
				[ -z $dst_device ] && continue
				if [ "$service_name" == "ALL" ]; then
					local rule="-i $src_device -o $dst_device ""$set_src_rule"" ""$set_dst_rule"
					fw add 4 f access_ctl ${rule_acl_btw_policy} $ { "$rule" }
			
				else
					if [ "$service_proto" != "icmp" ]; then
				
						service_sport=$(echo $service_sport|tr '-' ':')
						service_dport=$(echo $service_dport|tr '-' ':')

						for proto in $service_proto; do
							
							fw add 4 f access_ctl ${rule_acl_btw_policy} $ \
								{ -i $src_device -o $dst_device -p $proto -m $proto --sport $service_sport \
								--dport $service_dport "$set_src_rule"" ""$set_dst_rule" }
						done
					
					else
						if [ "$service_name" == "ICMP_ALL" ]; then
							fw add 4 f access_ctl ${rule_acl_btw_policy} $ \
								{ -i $src_device -o $dst_device -p $service_proto --icmp-type any \
								"$set_src_rule"" ""$set_dst_rule" }
							
						else
							fw add 4 f access_ctl ${rule_acl_btw_policy} $ \
								{ -i $src_device -o $dst_device -p $service_proto -m $service_proto \
								--icmp-type $service_type/$service_code "$set_src_rule"" ""$set_dst_rule" }
						fi
					fi
				fi
			done
		done
	}
}

#destroy_flag = 1 means 'add rules'
#destroy_flag = 2 means 'del rules'
fw_acl_load_rules()
{
	# original stack
	if ! iptables -w -C forwarding_rule -j access_ctl 2>/dev/null; then
		iptables -w -N access_ctl
		iptables -w -I forwarding_rule 1 -j access_ctl
		iptables -w -I input_rule 1 -j access_ctl
	else
		iptables -w -F access_ctl
	fi
	
	# vnet stack
	if ! vnete iptables -w -C forwarding_rule -j access_ctl_fwd 2>/dev/null; then
		vnete iptables -w -N access_ctl
		vnete iptables -w -N access_ctl_fwd
		vnete iptables -w -I INPUT 1 -j access_ctl
		vnete iptables -w -I forwarding_rule 1 -j access_ctl_fwd
	else
		vnete iptables -w -F access_ctl_fwd
		vnete iptables -w -F access_ctl
	fi
	
	# Make sure access_ctl in vnet only works for packets from LAN to LAN
	vnete iptables -w -I access_ctl_fwd 1 -j RETURN -m multinetdev --out lo,veth1
	vnete iptables -w -I access_ctl_fwd 1 -j RETURN -m multinetdev --in lo,veth1
	vnete iptables -w -A access_ctl_fwd -j access_ctl

	ACL_LOG "start load iptables"
	#config_foreach fw_acl_do_acl_btw_rule rule_acl_btw
	#config_load access_ctl
	fw_acl_do_acl_inner_rule rule_acl_inner 1
	lua /lib/access_ctl/attach_timeobj.lua
	#config_foreach fw_acl_do_acl_inner_rule rule_acl_inner 1
	#config_foreach config_clear
	ACL_LOG "stop"
}

fw_acl_clear()
{
	# original stack
	if iptables -w -C forwarding_rule -j access_ctl 2>/dev/null; then
		iptables -w -F access_ctl
		iptables -w -D forwarding_rule -j access_ctl
		iptables -w -D input_rule -j access_ctl
		iptables -w -X access_ctl
	fi
	
	# vnet stack
	if vnete iptables -w -C forwarding_rule -j access_ctl_fwd 2>/dev/null; then
		vnete iptables -w -F access_ctl
		vnete iptables -w -F access_ctl_fwd
		vnete iptables -w -D INPUT -j access_ctl
		vnete iptables -w -D forwarding_rule -j access_ctl_fwd
		vnete iptables -w -X access_ctl_fwd
		vnete iptables -w -X access_ctl
	fi
	
	ACL_LOG "free access_ctl rule"
	fw_acl_do_acl_inner_rule rule_acl_inner 2
	ACL_LOG "free access_ctl rule stop"
	#config_load access_ctl
	#config_foreach fw_acl_do_acl_inner_rule rule_acl_inner 2
	#config_foreach config_clear
}


fw_acl_event_do_btw_interface()
{
	local iface=$2
	local action=$3
	local flag=""

	devices=$(zone_get_device_byif $iface)
	fw_acl_config_get_rule_acl_btw $1
	service_config_get $rule_acl_btw_service

	[ "$rule_acl_btw_flag" == "2" ] && {
		src_zone=${rule_acl_btw_zone%-*}
		dst_zone=${rule_acl_btw_zone#*-}
	}

	src_ifaces=$(zone_get_wan_ifaces $src_zone)
	for src_iface in $src_ifaces;do
		[ "$iface" == "$src_iface" ] && {
			flag=1
		}
	done
	
	[ "$flag" != "1" ] && {
		dst_ifaces=$(zone_get_wan_ifaces $dst_zone)
		for dst_iface in $dst_ifaces;do
			[ "$iface" == "$dst_iface" ] && {
				flag=1
			}
		done
	}
	
	[ "$flag" == 1 ] && {
		[ "$rule_acl_btw_flag" == "2" ] && {
			src_zone=${rule_acl_btw_zone%-*}
			dst_zone=${rule_acl_btw_zone#*-}
		}
	
		rule_acl_btw_policy=$(echo $rule_acl_btw_policy|tr '[a-z]' '[A-Z]')
		[ "$rule_acl_btw_flag" == "2" ] && {
			src_devices=$(zone_get_wan_devices "${src_zone}")
			dst_devices=$(zone_get_wan_devices "${dst_zone}")
			set_src_rule=""
			if [ $rule_acl_btw_src != "IPGROUP_ANY" ];then
				src_group=$(echo $rule_acl_btw_src |grep "REV")
				
				if [ -n "$src_group" ]; then
					rule_acl_btw_src=${rule_acl_btw_src%_*}
					
					fw_acl_ipset_check $rule_acl_btw_src
					[ x$? == x0 ] && {
						set_src_rule="-m set ! --match-set $rule_acl_btw_src src"
					} || return
				else
					fw_acl_ipset_check $rule_acl_btw_src
					[ x$? == x0 ] && {
						set_src_rule="-m set --match-set $rule_acl_btw_src src"
					} || return
				fi
			else
				set_src_rule=""		# IPGROUP_ANY
			fi
			set_src_rule="$set_src_rule,src"
			#echo "set_src_rule=$set_src_rule"

			set_dst_rule=""
			if [ $rule_acl_btw_dest != "IPGROUP_ANY" ];then
				dst_group=$(echo $rule_acl_btw_dest |grep "REV")
				if [ -n "$dst_group" ]; then
					rule_acl_btw_dest=${rule_acl_btw_dest%_*}
					fw_acl_ipset_check $rule_acl_btw_dest
					[ x$? == x0 ] && {
						set_dst_rule="-m set ! --match-set $rule_acl_btw_dest dst"

					} || return
				else
					fw_acl_ipset_check $rule_acl_btw_dest
					[ x$? == x0 ] && {
						set_dst_rule="-m set --match-set $rule_acl_btw_dest dst"
					} || return
				fi
			else
				set_dst_rule=""
			fi
			set_dst_rule="$set_dst_rule,dst"
			#echo "set_dst_rule=$set_dst_rule"

			for src_device in $src_devices;do
				for dst_device in $dst_devices; do
					if [ "$service_name" == "ALL" ]; then
						local rule="-i $src_device -o $dst_device ""$set_src_rule"" ""$set_dst_rule"
						fw $action 4 f access_ctl ${rule_acl_btw_policy} $ { "$rule" }
					else
						if [ "$service_proto" != "icmp" ]; then
							service_sport=$(echo $service_sport|tr '-' ':')
							service_dport=$(echo $service_dport|tr '-' ':')
							for proto in $service_proto; do
								
								fw $action 4 f access_ctl ${rule_acl_btw_policy} $ \
									{ -i $src_device -o $dst_device -p $proto -m $proto --sport $service_sport \
									--dport $service_dport "$set_src_rule"" ""$set_dst_rule" }
							done
						else
							if [ "$service_name" == "ICMP_ALL" ]; then
								fw $action 4 f access_ctl ${rule_acl_btw_policy} $ \
									{ -i $src_device -o $dst_device -p $service_proto --icmp-type any \
									"$set_src_rule"" ""$set_dst_rule" }
							else
								fw $action 4 f access_ctl ${rule_acl_btw_policy} $ \
									{ -i $src_device -o $dst_device -p $service_proto -m $service_proto \
									--icmp-type $service_type/$service_code "$set_src_rule"" ""$set_dst_rule" }
							fi
						fi
					fi
				done
			done
		}
	}
}


fw_acl_event_interface()
{
	local iface=$1
	local action=$2

	[ -z "$iface" -o -z "$action" ] && {
		return
	}
	
	devices=$(zone_get_device_byif $iface)

	[ "del" == "$action" ] && {
		fw_acl_clear
		fw_acl_load_rules
		#config_foreach fw_acl_event_do_btw_interface rule_acl_btw $iface $action
	}

	[ "add" == "$action" ] && {
		fw_acl_clear
		fw_acl_load_rules
		# also can change fw_acl_event_do_btw_interface
		#config_foreach fw_acl_event_do_btw_interface rule_acl_btw $iface $action
	}
}


fw_acl_event_vpniface()
{
	local iface=$1
	local action=$2

	[ -z "$iface" -o -z "$action" ] && {
		return
	}

	devices=$(zone_get_device_byif $iface)

	[ "del" == "$action" ] && {
	#	config_foreach fw_acl_event_do_btw_interface rule_acl_btw $iface $action
		fw_acl_clear
		fw_acl_load_rules
	}

	[ "add" == "$action" ] && {
		fw_acl_clear
		fw_acl_load_rules
		# also can change fw_acl_event_do_btw_interface
		# config_foreach fw_acl_event_do_btw_interface rule_acl_btw $iface $action
	}
	
}


