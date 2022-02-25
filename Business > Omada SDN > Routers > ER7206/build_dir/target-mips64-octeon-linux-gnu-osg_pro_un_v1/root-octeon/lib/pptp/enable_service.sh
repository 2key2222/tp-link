#!/bin/sh

. /lib/pptp/pptp-startup.sh
. /lib/pptp/pptp-ifdevice-info.sh

kill_server_pppd(){
	local service_name=$1
	for file in `ls ${pppox_ppppath}/pid 2>/dev/null`; do
		local getisserver=`uci -c ${pppox_ppppath}/pid get ${file}.@info[0].isserver 2>/dev/null`
		getconfigpath=`uci -c ${pppox_ppppath}/pid get ${file}.@info[0].configpath 2>/dev/null`
		
		[ "${getisserver}" != "1" ] && continue	
		[ $service_name != $(basename $getconfigpath) ] && continue
		[ -f "${getconfigpath}/config/pptp.type" ] && kill -TERM ${file} #/lib/pptp/pptp-tunnel-action.sh '1' $file
	done
}
#totally should get 7 parameters
# $1--> service is enabled ?
# $2 --> the new bindif
# $3--> mppe is enabled ?
# $4 --> authtype
# $5 --> service name
# $6 --> old enable
# $7 --> old bindif
# $8 --> old_service_name ??
local old_enable=$6
local old_bindif=$7

[ $old_enable = 'on' ] && kill_server_pppd $5

if [ $old_bindif = $2 -a $old_enable != $1 ];then #interface is the same but enable is different
	enable_packet $1 $2
	#[ $old_enable = 'on' ] && kill_server_pppd $5
fi

local path=/tmp/pptp/server/$5/config
if [ $old_bindif != $2 ];then  #interface is different
	enable_packet '0' $old_bindif
	enable_packet $1 $2
	#the change of the map of service_name  <--> bindif,need to notify pptpd
	#still,it's better not to change the bindif
	#local devices=$(zone_get_effect_devices $2)
	local inter=$(zone_get_effect_main_wan_ifaces $2)
	local devices=$(zone_get_device_byif $inter)
	fifo_write "$5#$devices"
	zone_change $2 $path options.pptpd
fi

pptp_set_ifdevice_info "${2}"  "${5}"

enable_mppe $3 $path options.pptpd

uci -c $path set ${pppox_configname}.@pns[-1].bindif=$2 
uci -c $path set ${pppox_configname}.@pns[-1].enable=$1
uci -c $path set ${pppox_configname}.@pns[-1].authtype=$4

uci -c $path commit ${pppox_configname}
