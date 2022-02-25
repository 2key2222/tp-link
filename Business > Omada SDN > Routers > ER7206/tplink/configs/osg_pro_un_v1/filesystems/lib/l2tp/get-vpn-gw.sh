#!/bin/sh
# get the gateway of vpn interface
#usage:
#    <thisscript> <interface or device>
#

#$1: interface

. /lib/pppox/pppox-header.sh

get_vpn_gateway()
{
        . /lib/zone/zone_api.sh

        device=`zone_get_device_byif $1`
        [ -z "${device}" ] && device=$1

        if ! echo ${device} | grep -qE "^(${pppoe_header}|${l2tp_header}|${pptp_header})"; then
        	exit 1
        fi

        ifconfig -a|awk -v target=^${device} '
                BEGIN
                {
                        findit=0
                }

                {
                        if (match($0, target))
                        {
                                findit=1
                                next
                        }

                        if (findit == 1)
                        {
                                gsub(".*P-t-P:", "")
                                gsub(" +Mask:.*", "")
                                print $0;
                                exit
                        }
                }'
}