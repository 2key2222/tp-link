#!/bin/sh

#this is typically for pptp-service delete
#author : luopei
# try to find the pppd that through the given wan,then kill it
# in tunnel output info,there is file named by pid of pppd,which contains the config path,which indicate which
# interface pppd packet goes through

. /lib/pppox/pppox-functions.sh
. /lib/pptp/pptp-startup.sh
. /lib/pptp/pptp-ifdevice-info.sh

local service_name=$1
local getconfigpath

for file in `ls ${pppox_ppppath}/pid 2>/dev/null`; do
	local getisserver=`uci -c ${pppox_ppppath}/pid get ${file}.@info[0].isserver 2>/dev/null`
	getconfigpath=`uci -c ${pppox_ppppath}/pid get ${file}.@info[0].configpath 2>/dev/null`
	
	[ "${getisserver}" != "1" ] && continue	
	[ $service_name != $(basename $getconfigpath) ] && continue
	[ -f "${getconfigpath}/config/pptp.type" ] && /lib/pptp/pptp-tunnel-action.sh '1' $file
done

local path=/tmp/pptp/server/${service_name}/config
local bindif=$(uci -c $path get ${pppox_configname}.@pns[0].bindif)
rm -rf /tmp/pptp/server/${service_name}
enable_packet '0' $bindif
pptp_remove_ifdevice_info "${service_name}"

