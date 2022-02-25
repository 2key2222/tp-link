#!/bin/sh
# get the ip of vpn interface
#

#$1: interface

. /lib/pppox/pppox-header.sh

get_vpn_ip()
{
        . /lib/zone/zone_api.sh

        mif=`zone_get_effect_main_wan_ifaces $1`
        [ -z "${mif}" ] && mif=$1
        device=`zone_get_device_byif $mif`
        [ -z "${device}" ] && device=$1

        if ! echo ${device} | grep -qE "^(${pppoe_header}|${l2tp_header}|${pptp_header})"; then
        	exit 1
        fi

        ifconfig ${device}|awk '
                {
                        if (match($0, "inet +addr:"))
                        {
                                gsub(".*inet +addr:", "")
                                gsub(" +P-t-P:.*", "")
                                print $0
                                exit
                        }
                }'
}

get_vpn_ip $1
