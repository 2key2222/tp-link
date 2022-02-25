#!/bin/sh

. /lib/pppox/pppox-default-variables.sh
. /lib/pptp/pptp-ifdevice-info.sh

#actual_delete is just for route delete
actual_delete(){
	local path=$1
	local pid=$2
	local file=${pppox_configname}
	
	local dev=$(uci -c ${pppox_ppppath}/pid get $pid.@info[0].ifname 2>/dev/null)
	#local remotesubnet=$(uci -c $path get $file.@pnc[0].remotesubnet)
	#local workmode=$(uci -c $path get $file.@pnc[0].workmode)
	
	#route del -net ${remotesubnet} dev $dev
	#[ $workmode = "nat" ] && fw del 4 nat POSTROUTING MASQUERADE  $ { -o ${dev} }
}

#path is like '/tmp/pptp/client/client0'
client_delete(){
	#path,contains config
	local path=$1/config
	local ppp_pid=${path}/ppp
	local mgr_pid=${path}/mgr
	
	ppp_pid=$(cat $ppp_pid 2>/dev/null)
	mgr_pid=$(cat $mgr_pid 2>/dev/null)
	
	[ ${ppp_pid}x != ''x ] && ls ${pppox_ppppath}/pid 2>/dev/null | grep -iqE "$ppp_pid" && actual_delete $path $ppp_pid && rm -f ${pppox_ppppath}/pid/$ppp_pid
	kill -9 `cat ${path}/mgrfather 2>/dev/null`
	[ ${ppp_pid}x != ''x ] && kill -TERM $ppp_pid
	[ ${mgr_pid}x != ''x ] && kill -9 $mgr_pid

	[ -e ${path}/mgrfather ] && rm -f ${path}/mgrfather
	[ -e ${path}/ppp ] && rm -f ${path}/ppp
	[ -e ${path}/mgr ] && rm -f ${path}/mgr
	pptp_remove_ifdevice_info "$(basename ${1})"
}

#$1 is for the path,$2 means if delete the tmp files as well
client_delete $1
[ $2 = '1' ] && rm -rf $1