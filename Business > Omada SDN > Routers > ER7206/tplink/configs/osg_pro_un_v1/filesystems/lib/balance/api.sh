#!/bin/sh

#get interface's gateway
# $1: interface
get_inface_gw()
{
	local gateway

	. /lib/functions/network.sh
	. /lib/zone/zone_api.sh

	inface=`zone_get_effect_ifaces $1`

	network_get_gateway gateway $inface

	if [ -z "$gateway" ]; then

		. /lib/l2tp/get-vpn-gw.sh

		gateway=`get_vpn_gateway $inface`
	fi

	echo $gateway
}


BA_STATE_DIR="/tmp/balance/"
BA_STATE_FILE="/tmp/balance/cur_state"

#dev=on
balance_get_state()
{
	local iface dev
	. /lib/zone/zone_api.sh

	#zone->iface->dev
	iface=`zone_get_effect_ifaces $1`
	dev=`zone_get_device_byif $iface`

	grep "^${dev}=.*" "$BA_STATE_FILE" 2>&1 >/dev/null || {
		return 1
	}

	echo "`cat $BA_STATE_FILE |grep "\<${dev}\>" |cut -d '=' -f 2`"
}

balance_set_state()
{
	local key="$1"
	local cont="$2"

	[ ! -e $BA_STATE_DIR ] && mkdir -p $BA_STATE_DIR
	[ ! -f $BA_STATE_FILE ] && touch $BA_STATE_FILE

	grep "^${key}=.*" "$BA_STATE_FILE" 2>&1 >/dev/null || {
		echo -e "${key}=${cont}" >> "$BA_STATE_FILE" 2>/dev/null
		return 0
	}

	sed -i "s/^${key}=.*/${key}=${cont}/" $BA_STATE_FILE	
}

balance_del_state()
{
	local key="$1"
	
	grep "^${key}=.*" $BA_STATE_FILE 2>&1 >/dev/null && sed "/^${key}=.*/d" -i $BA_STATE_FILE
}

balance_clear_state()
{
	echo >$BA_STATE_FILE 
}


#$1:interface
add_interface_state()
{
	balance_set_state $1 "off"
}

#$1:interfaces
del_interface_state()
{
	[ -n "$1" ] || return 1

	for inface in $1;do
		balance_del_state $inface
	done	
}

# add the inface to global interfaces
add_inface()
{
	#for i in $g_total_inface;do
		#[ "$i" == $1 ] && return
	#done

	append g_total_inface $1 
}

interface_in_balance()
{
	[ "$g_flag" -eq 1 ] && return

	config_get balance $1 balance
	if [ "$g_inface" == "$1" -a "$balance" -eq 1 ];then
		g_flag=1
	fi
}

#$1:inface
adjust_online_check()
{
	[ -n "$1" ] || return

	local g_inface=$1 g_flag=0

	. /lib/functions.sh

	#get default balance interface
	config_load mwan3
	config_foreach interface_in_balance interface

	echo "$g_flag"
}

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
	iface_ref_del "$1"

	ipgroup_ref_del "$2"

	service_ref_del "$3"
}

#$1:inface
#$2:balance ?1:0
add_interface_handle()
{
	[ -n "$1" ] || return

	#add_interface_state "$1"

	#if balance setted 1
	#if [ "$2" -eq 1 ]; then
		#add_online_check "$1"
	#fi
}

#$1:balance_infaces
#$2:non_balance_infaces
del_interface_handle()
{
	if [ -n "$1" ];then
		#del_online_check "$1"
		/etc/init.d/default_balance restart
	fi

	#del_interface_state "$1"
	#del_interface_state "$2"
}

#$1:balance global state
balance_global_set()
{
	if [ "$1" == "on" ];then
		/usr/sbin/balance_loop &
		
		/etc/init.d/isp_route restart
		/etc/init.d/default_balance restart
		/etc/init.d/load_balance restart
		/etc/init.d/mwan3 restart

		. /lib/backup/backup.sh
		global_enable_backup
	elif [ "$1" == "off" ]; then
		
		/etc/init.d/isp_route stop
		/etc/init.d/default_balance stop
		/etc/init.d/load_balance stop
		/etc/init.d/mwan3 stop

		. /lib/backup/backup.sh
		global_disable_backup

		#kill the balance_loop process
		if [ -e /var/run/balance_loop.pid ] ; then
			kill $(cat /var/run/balance_loop.pid) &> /dev/null
			rm /var/run/balance_loop.pid &> /dev/null
		fi
	fi
}

get_balance_global_state()
{
	state=`uci get mwan3.global.state 2>/dev/null`
	echo "$state"
}

handl_default_load_balance()
{
	/etc/init.d/default_balance restart 
	/etc/init.d/load_balance restart
}


BA_IFACE_DIR="/tmp/balance/"
BA_IFACE_FILE="/tmp/balance/.iface_event"

#$1:dev
#return up/down
balance_iface_get_event()
{
	local dev="$1"

	if [ ! -f "$BA_IFACE_FILE" ];then
		echo "none"
		return 1
	fi

	grep "^${dev}=.*" "$BA_IFACE_FILE" 2>&1 >/dev/null || {
		return 1
	}

	echo "`cat $BA_IFACE_FILE |grep "\<${dev}\>" |cut -d '=' -f 2`"
}

#$1:dev
#$2:event:up/down
balance_iface_set_event()
{
	local dev="$1"
	local cont="$2"

	[ ! -e $BA_IFACE_DIR ] && mkdir -p $BA_IFACE_DIR
	[ ! -f $BA_IFACE_FILE ] && touch $BA_IFACE_FILE

	grep "^${dev}=.*" "$BA_IFACE_FILE" 2>&1 >/dev/null || {
		echo -e "${dev}=${cont}" >> "$BA_IFACE_FILE" 2>/dev/null
		return 0
	}

	sed -i "s/^${dev}=.*/${dev}=${cont}/" $BA_IFACE_FILE	
}

#$1:dev
balance_iface_del_event()
{
	local key="$1"
	
	grep "^${key}=.*" $BA_IFACE_FILE 2>&1 >/dev/null && sed "/^${key}=.*/d" -i $BA_IFACE_FILE
}

balance_iface_clear_event()
{
	echo >$BA_IFACE_FILE 
}

BA_ONLINE_IFACES_FILE="/tmp/balance/.online_ifaces"
# balance policy changed notify!
balance_policy_notify()
{
	. /lib/functions/network.sh
	. /lib/zone/zone_api.sh

	local ifaces="$1"
	local online_ifaces=""
	local old_ifaces="$(cat ${BA_ONLINE_IFACES_FILE})"

	# save online interfaces.	
	for iface in ${ifaces}; do
		state=`balance_get_state $iface`
		[ "$state" == "on" ] && {
			online_ifaces="$iface $online_ifaces"

			#record ipaddr
			wiface=$(zone_get_effect_main_wan_ifaces "$iface")
			network_get_ipaddr wanv4addr "$wiface"
			echo "$wanv4addr" > /tmp/balance/IPADDR_$iface
		}
	done

	[ "$old_ifaces" == "$online_ifaces" ] && return

	echo -n "$online_ifaces" > ${BA_ONLINE_IFACES_FILE}

	# find offline interfaces, cleanup conntracks.
	[ -z "$old_ifaces" ] && old_ifaces="$ifaces"
	for oiface in ${old_ifaces}; do
		offline="yes"	
		for iface in ${online_ifaces}; do
			if [ "$oiface" == "$iface" ]; then
				offline="no"
				break;
			fi
		done
		# offline
		[ "$offline" == "yes" ] && {
			# clean conntracks for this offline WAN.	
			wiface=$(zone_get_effect_main_wan_ifaces "$oiface")
			network_get_ipaddr wanv4addr "$wiface"
			[ -z "$wanv4addr" ] && wanv4addr="$(cat /tmp/balance/IPADDR_$oiface)"

			[ -n "$wanv4addr" ] && conntrack -D -m 0x10000 ${wiface:+-n $wanv4addr}
		}
	done
}
