#!/bin/sh /etc/rc.common

START=98


ROUTE_STATE_DIR="/tmp/"
ROUTE_STATE_FILE="/tmp/.route"

route_get_state()
{
	local key="$1"
	grep "^${key}=.*" "$ROUTE_STATE_FILE" 2>&1 >/dev/null || {
		return 1
	}
	
	echo "`cat $ROUTE_STATE_FILE |grep "\<${key}\>" |cut -d '=' -f 2`"
}

route_set_state()
{
	local key="$1"
	local cont="$2"

	[ ! -e $ROUTE_STATE_DIR ] && mkdir -p $ROUTE_STATE_DIR
	[ ! -f $ROUTE_STATE_FILE ] && touch $ROUTE_STATE_FILE

	grep "^${key}=.*" "$ROUTE_STATE_FILE" 2>&1 >/dev/null || {
		echo -e "${key}=${cont}" >> "$ROUTE_STATE_FILE" 2>/dev/null
		return 0
	}

	sed -i "s/^${key}=.*/${key}=${cont}/" $ROUTE_STATE_FILE
}

route_del_state()
{
	local key="$1"
	
	grep "^${key}=.*" $ROUTE_STATE_FILE 2>&1 >/dev/null && sed "/^${key}=.*/d" -i $ROUTE_STATE_FILE
}

route_clear_state()
{
	echo >$ROUTE_STATE_FILE 
}

#$1: device
route_get_iface()
{
	. /lib/zone/zone_api.sh

	iface=`zone_get_iface_bydev $1`
	if [ -z "$iface" ];then
		echo "$1"
		return 1
	fi

	zone=`zone_get_zone_byif $iface`
	if [ -z "$zone" ];then
		echo "$iface"
		return 1
	fi

	if [ "$zone" == "VPN" ];then
		zone=$iface
	fi

	echo "$zone"
}

add_lan_default_route()
{
	local iface="LAN"
	local metric=0
	local ip netmask dev target

	ip=`uci get network.lan.ipaddr`
	[ -n "$ip" ] || return

	netmask=`uci get network.lan.netmask`
	[ -n "$netmask" ] || return

	dev=`zone_get_effect_devices $iface`
	[ -n "$dev" ] || return 

	tmp=`ipcalc -n $ip $netmask`
	target=`echo $tmp |cut -d "=" -f 2`

	[ -n "$target" ] || return

	ip route append $target/$netmask via $ip dev $dev metric $metric table $ROUTE_NUM 2>&1
}
