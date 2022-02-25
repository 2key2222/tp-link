#!/bin/sh

NAME="policy_route"

del_l2tp_inface_ref()
{
	[ "$flag" -eq 1 ] && return

	config_get tunnelname $1 tunnelname

	if [ "$inface" == "$tunnelname" ];then
		config_get t_reference $1 t_reference
		t_reference=$(($t_reference-1))
		uci set l2tp-client.$1.t_reference=$t_reference
		flag=1
	fi
}

del_pptp_inface_ref()
{
	[ "$flag" -eq 1 ] && return

	config_get tunnelname $1 tunnelname

	if [ "$inface" == "$tunnelname" ];then
		config_get t_reference $1 t_reference
		t_reference=$(($t_reference-1))
		uci set pptp-client.$1.t_reference=$t_reference
		flag=1
	fi
}

# dec the interfaces' reference
# $1: interfaces
iface_ref_del()
{
	[ -n "$1" ] || return

	. /lib/functions.sh

	local flag=0

	for inface in $1;do
		ref=`uci get network.$inface.t_reference 2>/dev/null`
		if [ -n "$ref" ]; then
			ref=$(($ref-1))
			uci set network.$inface.t_reference=$ref
		else			
			config_load l2tp-client
			config_foreach del_l2tp_inface_ref lac

			# flag=1 got it 
			[ "$flag" -eq 1 ] && flag=0 && continue
			
			config_load pptp-client
			config_foreach del_pptp_inface_ref pnc
		fi
		flag=0
	done
	uci commit
}

# dec the policy interfaces' reference
# $1: policy interfaces
policyIface_ref_del()
{
	[ -n "$1" ] || return

	. /lib/functions.sh

	local flag=0
	local use_policy
	local used_infaces
	for use_policy in $1;do
		used_infaces=`uci get policy_route.$use_policy.use_iface`	
		[ -n "$used_infaces" ] || return
		#echo "used_infaces=$used_infaces" > /dev/console
		for inface in $used_infaces;do
			ref=`uci get network.$inface.t_reference 2>/dev/null`
			if [ -n "$ref" ]; then
				ref=$(($ref-1))
				uci set network.$inface.t_reference=$ref
			else			
				config_load l2tp-client
				config_foreach del_l2tp_inface_ref lac

				# flag=1 got it 
				[ "$flag" -eq 1 ] && flag=0 && continue
			
				config_load pptp-client
				config_foreach del_pptp_inface_ref pnc
			fi
			flag=0
		done
	done
	uci commit
}

del_ipgroup_ref()
{
	[ "$flag" -eq 1 ] && return

	config_get name $1 name

	if [ "$ipgroup" == "$name" ];then
		config_get ref $1 ref
		ref=$(($ref-1))
		uci set ipgroup.$1.ref=$ref
		flag=1
	fi
}

# $1: ipgroups
ipgroup_ref_del()
{
	[ -n "$1" ] || return

	. /lib/functions.sh

	local flag=0	

	for ipgroup in $1;do
		config_load ipgroup			
		config_foreach del_ipgroup_ref rule_ipgroup
		flag=0
	done
	uci commit
}

# $1: services
service_ref_del()
{
	[ -n "$1" ] || return

	. /lib/functions.sh

	for service in $1;do		
		ref=`uci get service.$service.ref 2>/dev/null`
		[ -n "$ref" ] || continue

		ref=$(($ref-1))
		uci set service.$service.ref=$ref		
	done
	uci commit
}

# $1: interfaces
# $2: ipgroups
# $3: services
policy_route_ref_del()
{
	#iface_ref_del "$1"
	policyIface_ref_del "$1"

	ipgroup_ref_del "$2"

	service_ref_del "$3"
}

check_rule_state()
{
	config_get use_policy $1 use_policy

	if [ "$use_policy" == "$policy_name" ];then
		config_get state $1 state
		[ "$state" == "on" ] && flag=1
	fi
}

search_policy_iface()
{
	local tmp=0 policy_name="$1"

	[ $flag -eq 1 ] && return

	ifaces=`uci get policy_route.$1.use_iface`
	for iface in $ifaces;do
		if [ "$iface" == "$INTERFACE" ];then
			tmp=1
			break
		fi
	done

	if [ "$tmp" -eq 1 ];then
		config_foreach check_rule_state policy_rule
	fi
}

#$1:iface
handle_iface_down()
{
	[ -n "$1" ] || return

	local INTERFACE flag=0

	. /lib/zone/zone_api.sh

	INTERFACE=`zone_get_zone_byif $1`

	. /lib/functions.sh

	config_load policy_route
	config_foreach search_policy_iface policy

	[ $flag -eq 0 ] && return

	/etc/init.d/policy_route restart
}

update_policy_connect_ipset()
{
	tmp=`ipset list -t |grep TP_pr_connected 2>/dev/null`
	if [ -n "$tmp" ] ;then
		ipset flush TP_pr_connected

		for connected_network in $(ip -4 route | awk '{print $1}' | egrep '[0-9]{1,3}(\.[0-9]{1,3}){3}'); do			
			ipset -! add TP_pr_connected $connected_network
		done

		for connected_network in $(ip -4 route list table 0 | awk '{print $2}' | egrep '[0-9]{1,3}(\.[0-9]{1,3}){3}'); do
			ipset -! add TP_pr_connected $connected_network
		done
	fi
}


#$1:iface
handle_iface_up()
{
	[ -n "$1" ] || return

	if [ "$1" == "lan" ]; then
		update_policy_connect_ipset
	fi

	local INTERFACE flag=0

	. /lib/zone/zone_api.sh

	INTERFACE=`zone_get_zone_byif $1`	

	. /lib/functions.sh

	config_load policy_route
	config_foreach search_policy_iface policy

	[ $flag -eq 0 ] && return

	/etc/init.d/policy_route restart
}

#$1:iface
handle_vpniface_down()
{
	[ -n "$1" ] || return

	local INTERFACE flag=0

		. /lib/zone/zone_api.sh

	INTERFACE=$1

	. /lib/functions.sh

	config_load policy_route
	config_foreach search_policy_iface policy

	[ $flag -eq 0 ] && return

	/etc/init.d/policy_route restart
}

#$1:iface
handle_vpniface_up()
{
	[ -n "$1" ] || return

	local INTERFACE flag=0

	. /lib/zone/zone_api.sh

	INTERFACE=$1

	. /lib/functions.sh

	config_load policy_route
	config_foreach search_policy_iface policy

	[ $flag -eq 0 ] && return

	/etc/init.d/policy_route restart
}