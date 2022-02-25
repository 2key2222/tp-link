#!/bin/sh

# Copyright (C) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# 
# brief        ip mac binding module core shell scripts
# author     Huang Zhenwei
# version    1.0.0 
# date         06May2015
# history     06May2015    Huang Zhenwei    Create the file
#                22May2015    Huang Zhenwei    Include 'zone' support

. /lib/zone/zone_api.sh

IMB_PREFIX="imb_ipmac_"
IP_PREFIX="imb_ip_"

local action=$1
case $action in 
    add)
        local ip=$2
        local mac=$3
        local interface=$4
        interface=$(zone_get_wan_ifaces $interface)
        local device=$(zone_get_device_byif $interface)
        local ipset_dev=$(zone_get_eth_device $interface)
        [ x"$device" != 'x' ] && {
            anete ipset add ${IP_PREFIX}${ipset_dev} $ip -exist
            anete ipset add ${IMB_PREFIX}${ipset_dev} $ip,$mac -exist
            anete arp -s -i $ipset_dev $ip $mac
        }
    ;;
    del)
        local oldip=$2
        local oldmac=$3
        local oldzone=$4
        oldzone=$(zone_get_wan_ifaces $oldzone)
        local device=$(zone_get_device_byif $oldzone)
         local ipset_dev=$(zone_get_eth_device $oldzone)
        [ x"$device" != 'x' ] && {
            anete ipset del ${IP_PREFIX}${ipset_dev} $oldip
            anete ipset del ${IMB_PREFIX}${ipset_dev} $oldip,$oldmac
            anete arp -d $oldip -i $ipset_dev
        }
    ;;
    *)
        return
    ;;
esac
