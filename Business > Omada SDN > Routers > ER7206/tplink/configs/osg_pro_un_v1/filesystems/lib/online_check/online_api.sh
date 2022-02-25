#!/bin/sh

ONLINE_STATE_DIR="/tmp/online/"
ONLINE_STATE_FILE="/tmp/online/state"
ONLINE_DEV_FILE="/tmp/online/zone"
ONLINE_LATENCY_FILE="/tmp/online/latency"
ONLINE_BLOCK_FILE="/tmp/online/block"

. /lib/zone/zone_api.sh
. /lib/functions/network.sh 

online_set_state()
{
	local dev="$1"
	#[ -n "$key" ] || { echo "set online state failed! can not get interface by device ${1}" > /dev/console }
	local cont="on"
	if [ "$2" = "0" ]; then
		cont="off"
	fi

	[ ! -e $ONLINE_STATE_DIR ] && mkdir -p $ONLINE_STATE_DIR
	[ ! -f $ONLINE_STATE_FILE ] && touch $ONLINE_STATE_FILE

	[ -n "$3" ] && {
		local device=""
		local i=""

		for i in `seq 1 4`
		do
			network_get_device device wan${i}_eth
			[ "$device" == "$dev" ] && break
			network_get_device device wan${i}_poe
			[ "$device" == "$dev" ] && break
		done
		[ "$device" == "$dev" ] && echo -e "$3" > ${ONLINE_LATENCY_FILE}${i}
		echo -e "$3" > ${ONLINE_LATENCY_FILE}_${dev}
	}

	grep "^${dev}=.*" "$ONLINE_STATE_FILE" 2>&1 >/dev/null || {
		echo -e "${dev}=${cont}" >> "$ONLINE_STATE_FILE" 2>/dev/null
		return 0
	}

	sed -i "s/^${dev}=.*/${dev}=${cont}/" $ONLINE_STATE_FILE	
}

online_del_state()
{
	#[ -n "$1" ] || { echo "delete online state failed! no device ${1}" > /dev/console }
	[ -z ${1} ] && return
	local dev="$1"
	#[ -n "$key" ] || { echo "delete online state failed! can not get interface by device ${1}" > /dev/console }
	grep "^${dev}=.*" $ONLINE_STATE_FILE 2>&1 >/dev/null && sed "/^${dev}=.*/d" -i $ONLINE_STATE_FILE
}

online_clear_state()
{
	[ ! -e $ONLINE_STATE_DIR ] && return 
	[ ! -f $ONLINE_STATE_FILE ] && return 
	echo >$ONLINE_STATE_FILE 
}

add_online_check()
{
	[ -n "$1" ] || return
	local zone_or_iface="$1"
	for cnt in $(seq 1 300); do
		dev=`zone_get_effect_devices $zone_or_iface`
		if [ -n "$dev" ]; then
			break
		fi	
		sleep 1
	done
	#[ -n "$dev" ] || continue

	ubus call online add_info "{\"dev\":\"$dev\"}"
	add_online_dev_state ${zone_or_iface} ${dev}
}

add_online_dev_state()
{
	[ -z ${1} ] && return
	[ -z ${2} ] && return 
	local zone_or_iface="$1"
	local dev="$2"

	[ ! -e $ONLINE_STATE_DIR ] && mkdir -p $ONLINE_STATE_DIR
	[ ! -f $ONLINE_DEV_FILE ] && touch $ONLINE_DEV_FILE

	grep "^${zone_or_iface}=.*" "$ONLINE_DEV_FILE" 2>&1 >/dev/null || {
		echo -e "${zone_or_iface}=${dev}" >> "$ONLINE_DEV_FILE" 2>/dev/null
		return 0
	}
	sed -i "s/^${zone_or_iface}=.*/${zone_or_iface}=${dev}/" $ONLINE_DEV_FILE

}

del_online_check()
{
	[ -z "$1" ] && return
	local zone_or_iface="$1"
	local dev="`cat $ONLINE_DEV_FILE |grep "\<${zone_or_iface}\>" |cut -d '=' -f 2`"
	[ -z "$dev" ] && return

	ubus call online delete_info "{\"dev\":\"$dev\"}"
	del_online_dev_state ${zone_or_iface}
}

del_online_dev_state()
{
	[ -z ${1} ] && return
	local zone_or_iface="$1"
	grep "^${zone_or_iface}=.*" $ONLINE_DEV_FILE 2>&1 >/dev/null && sed "/^${zone_or_iface}=.*/d" -i $ONLINE_DEV_FILE
}

flush_online_check()
{
	. /usr/share/libubox/jshn.sh

	jdata=`ubus call online get_info`
	json_load "$jdata"
	json_get_keys jkeys
	for jkey in $jkeys
	do
		json_select "$jkey"
		json_get_var jval dev
		ubus call online delete_info "{\"dev\":\"$jval\"}"
		json_select ..
	done
}

update_online_manual_check()
{
	[ -n "$1" ] || [ -n "$2" ] || [ -n "$3" ] || [ -n "$4" ] || return

	. /lib/zone/zone_api.sh
	dev=`zone_get_effect_devices $1`
	[ -n "$dev" ] || return

	ubus call online update_manual_info "{\"dev\":\"$dev\",\"mode\":\"$2\",\"manual_gw\":\"$3\",\"manual_dns\":\"$4\"}"
}

#$1: ifaces
del_ifaces_online_check()
{
	[ -n "$1" ] || return

	for i in $1;do
		del_online_check $i
	done
}

#$1: interval
update_online_interval()
{
	[ -z "$1" ] && return
	ubus call online update_interval "{\"interval\":$1}"
}

#$1: zone name
#$2: block status
#return old status
update_online_dev_blocked()
{
	. /lib/zone/zone_api.sh
	devs=`zone_get_devices $1`

	blocked="no"
	for dev in $devs
	do
		if [ -e ${ONLINE_BLOCK_FILE}"_${dev}" ];
		then
			blocked="yes"
		fi
	done

	if [ "$2" != "0" ];
	then
		for dev in $devs
		do
			echo -n "$1" > ${ONLINE_BLOCK_FILE}"_${dev}"
			[ "$blocked" == "no" ] && ubus call online refresh "{\"dev\":\"$dev\"}"
		done
	else
		for devfile in `ls ${ONLINE_BLOCK_FILE}_*`
		do
			if [ "$1" == "`cat ${devfile}`" ];
			then
				rm -f ${devfile}
				dev="${devfile##${ONLINE_BLOCK_FILE}_}"
				[ "$blocked" == "yes" ] && ubus call online refresh "{\"dev\":\"$dev\"}"
			fi
		done
	fi
}
