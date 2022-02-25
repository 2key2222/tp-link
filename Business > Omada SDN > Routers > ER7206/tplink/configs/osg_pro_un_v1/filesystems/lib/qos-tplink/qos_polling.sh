#!/bin/sh
#Copyright (C) 2015 tplink.com

# qos polling daemon

# reset mark to make include available
qos_polling_reset() {
    INC_QOS_COM=""
    INC_QOS_CORE=""
    INC_QOS_NF=""
    INC_QOS_IFGROUP=""
    INC_QOS_CID=""
    INC_QOS_GRPMARK=""
    INC_QOS_MARK=""
    INC_QOS_STATE=""
    INC_QOS_TC=""
}

qos_polling_reset
. /lib/qos-tplink/qos_public.sh

QOS_LOG_PRINT " info, pid $$ QOS_THRESHOLD polling on devs:$DEV_LIST! "

# clear throughput tmp file (if exsit)
rm -f $QOS_TMP_DIR/ifstate_cur 2>/dev/null
rm -f $QOS_TMP_DIR/ifstate_pre 2>/dev/null

local time_unit=`uci get ${THIS_MODULE}.polling.time_unit 2>/dev/null`
local enable_time=`uci get ${THIS_MODULE}.polling.enable_time 2>/dev/null`
local disable_time=`uci get ${THIS_MODULE}.polling.disable_time 2>/dev/null`
local trust_threshold=`uci get ${THIS_MODULE}.polling.trust_threshold 2>/dev/null`

# if no polling setting, set default value as below
[ -z $time_unit ] && time_unit=10
[ -z $enable_time ] && enable_time=1
[ -z $disable_time ] && disable_time=24
[ -z $trust_threshold ] && trust_threshold=0.8

local tt=$trust_threshold

get_qos_dev_bytes()
{
	local zone="$1"
	local ndev="$2"
	local dir="$3"
	local bx=0

	[ -z "$zone" -o -z "$ndev" ] && {
		echo -n "0"
		return
	}

	if fastpath_hw_real_on; then
		if [ -n "$zone" -a "${zone:0:3}" = "WAN" ]; then
			local port=$(uci get network.switch.wan_ports_value | awk -F'|' '{print $4}' | awk -v p=${zone:3:1} '{print $p}')
			if [ "$dir" == "rx" ]; then
				bx="$(switch -t statistic -o get -p ${port} | grep 'RxAll' | awk '{print $3}')"
				[ ${#bx} -gt 3 ] && bx=${bx:0:$((${#bx}-3))} || bx=0
			else
				bx="$(switch -t statistic -o get -p ${port} | grep 'TxAll' | awk '{print $3}')"
				[ ${#bx} -gt 3 ] && bx=${bx:0:$((${#bx}-3))} || bx=0
			fi
		else
			if [ "$dir" == "rx" ]; then
				bx=$(awk '/(^| )'$ndev':/{print $2}' /proc/net/dev)
				[ ${#bx} -gt 3 ] && bx=${bx:0:$((${#bx}-3))} || bx=0
			else
				bx=$(awk '/(^| )'$ndev':/{print $10}' /proc/net/dev)
				[ ${#bx} -gt 3 ] && bx=${bx:0:$((${#bx}-3))} || bx=0
			fi
		fi
	else
		if [ "$dir" == "rx" ]; then
			bx=$(awk '/(^| )'$ndev':/{print $2}' /proc/net/dev)
			[ ${#bx} -gt 3 ] && bx=${bx:0:$((${#bx}-3))} || bx=0
		else
			bx=$(awk '/(^| )'$ndev':/{print $10}' /proc/net/dev)
			[ ${#bx} -gt 3 ] && bx=${bx:0:$((${#bx}-3))} || bx=0
		fi
	fi

	echo -n "${bx:-0}"
}

for iface in $ZONE_LIST; do
    # only calc physical interface
    # [ $iface = "WAN" -o $iface = "WAN1" -o $iface = "WAN2" -o $iface = "WAN3" -o $iface = "WAN4" -o $iface = "LAN" ] || continue
	local ndev=$(zone_get_effect_devices $iface)
	local rx=$(get_qos_dev_bytes "$iface" "$ndev" "rx")
	local tx=$(get_qos_dev_bytes "$iface" "$ndev" "tx")
    local downlink=`uci get ${THIS_MODULE}.${iface}.downlink 2>/dev/null`
	local uplink=`uci get ${THIS_MODULE}.${iface}.uplink 2>/dev/null`
    [ -z $downlink ] && downlink=${LINERATE/[^0-9]*/}
	[ -z $uplink ] && uplink=${LINERATE/[^0-9]*/}
    indirect_var_set ${iface}_downlink $downlink
	indirect_var_set ${iface}_uplink $uplink
    echo "${ndev} rx $rx tx $tx" >> $QOS_TMP_DIR/ifstate_cur
done

while true; do
    # reset calc param
	local active_flag_sum=0
	local count=0
    trust_threshold=$tt


	[ -f $QOS_READY ] && count=$disable_time || count=$enable_time
	while [ $count -gt 0 ]; do
        sleep $time_unit

        local active_flag=0
        cp -f $QOS_TMP_DIR/ifstate_cur $QOS_TMP_DIR/ifstate_pre 2>/dev/null
        rm -f $QOS_TMP_DIR/ifstate_cur 2>/dev/null
    	for iface in $ZONE_LIST; do
            # [ $iface = "WAN" -o $iface = "WAN1" -o $iface = "WAN2" -o $iface = "WAN3" -o $iface = "WAN4" -o $iface = "LAN" ] || continue
            local ndev=$(zone_get_effect_devices $iface)
    		local rx_pre=$(awk '/'$ndev\ '/{print $3}' $QOS_TMP_DIR/ifstate_pre)
    		local tx_pre=$(awk '/'$ndev\ '/{print $5}' $QOS_TMP_DIR/ifstate_pre)
		local rx=$(get_qos_dev_bytes "$iface" "$ndev" "rx")
		local tx=$(get_qos_dev_bytes "$iface" "$ndev" "tx")
    		local downlink=`indirect_var_get ${iface}_downlink`
            local uplink=`indirect_var_get ${iface}_uplink`

    		local rx_flag=$((rx*8*100 - rx_pre*8*100 - downlink*$QOS_THRESHOLD*$time_unit))
    		local tx_flag=$((tx*8*100 - tx_pre*8*100 - uplink*$QOS_THRESHOLD*$time_unit))

    		[ $rx_flag -gt 0 -o $tx_flag -gt 0 ] && {
    			active_flag=1
    		}
    		echo "${ndev} rx $rx tx $tx" >> $QOS_TMP_DIR/ifstate_cur
    	done
        local active_flag_sum=$(($active_flag_sum + $active_flag))

        count=$(($count-1))
	done

    [ ! -f $QOS_READY ] && count=$enable_time || {
        count=$disable_time
        trust_threshold=`echo "$trust_threshold" | awk '{print 1-$1}'`
    }
    local rate=`echo "$active_flag_sum $count" | awk '{print $1/$2}'`
    active_flag=`echo "$rate $trust_threshold" | awk '{if($1<$2) {print 0} else {print 1}}'`

	[ $active_flag -gt 0 ] && {
        [ ! -f $QOS_READY ] && {
            QOS_LOG_PRINT " info, throughput overflow $QOS_THRESHOLD%, turn on qos "
            qos_polling_reset
            . /lib/qos-tplink/qos_public.sh
            local usr_cmd=". /lib/qos-tplink/main.sh"
            local usr_cmd="$usr_cmd start"
            $usr_cmd
	   }
	}

	[ $active_flag -eq 0 ] && {
        [ -f $QOS_READY ] && {
            QOS_LOG_PRINT " info, throughput lower than $QOS_THRESHOLD%, turn off qos "
            qos_polling_reset
            . /lib/qos-tplink/qos_public.sh
            local usr_cmd=". /lib/qos-tplink/main.sh"
            local usr_cmd="$usr_cmd stop"
            $usr_cmd
        }
	}
done
