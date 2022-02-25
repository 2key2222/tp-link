#!/bin/sh
#
#

[ $# -lt 1 ] && exit 1

l2tpifname=$1


. /lib/functions.sh
. /lib/pppox/pppox-default-variables.sh
. /lib/l2tp/l2tp-functions.sh

l2tp_client_configname=l2tp-client

l2tpid=`uci get ${l2tp_client_configname}.${l2tpifname}.id 2>/dev/null`

[ "${l2tpid}" = "" ] && { echo "not found config for ${l2tpifname}"; exit 1; }

enable=`uci get ${l2tp_client_configname}.${l2tpifname}.enable 2>/dev/null`

[ "${enable}" == "no" ] && { echo "${l2tpifname} not runned, no need down again"; exit 0; }
uci set ${l2tp_client_configname}.${l2tpifname}.enable="no"
uci commit ${l2tp_client_configname}
/lib/l2tp/l2tp-reload.sh  modify lac ${l2tpid}
lua /lib/l2tp/l2tp-ipsec-setstatus.lua ${l2tpid} off "${l2tpifname}"

