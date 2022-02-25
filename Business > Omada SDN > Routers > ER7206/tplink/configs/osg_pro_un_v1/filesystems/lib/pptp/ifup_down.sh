#!/bin/sh
. /lib/zone/zone_api.sh
. /lib/pptp/pptp-option.sh
. /lib/pppox/pppox-default-variables.sh

local cmd=$1
local ifname=$2
local loop=0
local username=""
local passwd=""
local pns=""
local outif=""
local client_path=""
local filepath=${pppox_ppppath}/pid

local result=$(uci get pptp-client.@pnc[$loop].tunnelname 2>/dev/null)
while [ x$result != 'x' ];do
	[ $result == $ifname -o "pptp-$result" == $ifname ] && {
		username=$(uci get pptp-client.@pnc[$loop].username 2>/dev/null)
		passwd=$(uci get pptp-client.@pnc[$loop].password 2>/dev/null)
		pns=$(uci get pptp-client.@pnc[$loop].pns 2>/dev/null)
		outif=$(uci get pptp-client.@pnc[$loop].outif 2>/dev/null)
		outif=$(zone_get_device_byif $outif)
		client_path=$(uci get pptp-client.@pnc[$loop].confname 2>/dev/null)
		client_path="/tmp/pptp/client/$client_path/config"
		break
	}
	loop=$(($loop+1))
	result=$(uci get pptp-client.@pnc[$loop].tunnelname 2>/dev/null)
done
[ x$username == 'x' -a x$passwd == 'x' ] && echo "not found corresponding item" && return 0
case $cmd in
	*ifup)
		#check if it's already up
		echo $ifname | grep -q '^pptp-' || ifname="pptp-"$ifname
		ifconfig | grep -q "^$ifname" && return 0
		#start it up
		client_start_pppd $username $passwd $pns $outif $client_path
	;;
	*ifdown)
		#check it's already running
		local pppfile=$client_path/ppp
		local pid=$(cat $pppfile)
		[ x$pid == 'x' -o ! -f $filepath/$pid ] && echo "the interface is not up " && return 0
		local mgrfile=$client_path/mgr
		local mgrpid=$(cat $mgrfile)
		kill -TERM $pid
		kill -9 $mgrpid
		rm -f $mgrfile
		rm -f $pppfile
	;;
esac