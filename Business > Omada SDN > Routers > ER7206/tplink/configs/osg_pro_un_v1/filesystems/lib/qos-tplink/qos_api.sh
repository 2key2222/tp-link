#!/bin/sh
#Copyright (C) 2015 tplink.com
# API offered by qos module

. /lib/qos-tplink/qos_public.sh



# get interface uplink bandwidth
# ret:  -1  iface not defined
qos_iface_get_uplink_bandwidth()
{
        local iface="$1"

        # IF iface exist in qos UCI
        grep -q "config.*${STYPE_IFACE}.*${iface}" $QOS_UCI || {
                QOS_RET "-1"
                return
        }

        rate=$(config_get $iface "uplink")
        [ ${#rate} -eq 0 ] && rate=0
        QOS_RET "`echo $rate | sed 's/[^0-9]//g'`"
}

# get interface downlink bandwidth
# ret:  -1  iface not defined
qos_iface_get_downlink_bandwidth()
{
        local iface="$1"

        # IF iface exist in qos UCI
        grep -q "config.*${STYPE_IFACE}.*${iface}" $QOS_UCI || {
                QOS_RET "-1"
                return
        }

        rate=$(config_get $iface "downlink")
        [ ${#rate} -eq 0 ] && rate=0
        QOS_RET "`echo $rate | sed 's/[^0-9]//g'`"
}

# get the nfmark bit region that possess by qos
qos_nfmark_bitfield_get()
{
	QOS_RET "$QOS_MARK_BIT_START $((QOS_MARK_BIT_START + QOS_MARK_BIT_LEN*2 - 1)) `printf "0x%x" $((QOS_GMARK_MASK + QOS_MARK_MASK))`"
}

