#!/bin/sh
#
# Copyright (C) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# 
# brief        ip mac binding module core shell scripts
# author     Huang Zhenwei
# version    1.0.0 
# date         06May2015
# history     06May2015    Huang Zhenwei    Create the file
#                22May2015    Huang Zhenwei    Include 'zone' support

. /lib/imb/core_global.sh
. /lib/zone/zone_api.sh

addDevice_IP_mac()
{
  local ZONES=$(zone_get_zonelist)
  for i in $ZONES; do
    #local EFF_IF=$(zone_get_effect_devices $i)
    [ $i == "VPN" ] && continue
    local EFF_IF=$(zone_get_wan_devices $i)
    for j in $EFF_IF; do
      #local EFF_IF=$(zone_get_effect_ifaces NORMAL)
      #local effect_device=$(zone_get_device_byif $j)
      echo $j | grep -q '_poe$' && continue
      grep -q "^${j} " /tmp/state/imb || {
		echo "${j} ${IMB_PREFIX}${j} ${IP_PREFIX}${j}" >>/tmp/state/imb
		anete ipset create "${IMB_PREFIX}${j}" hash:ip,mac  -exist
		anete ipset create "${IP_PREFIX}${j}"  hash:ip  -exist
      }
      local effect_device=${j}
      local device_ip=$(anete ifconfig $effect_device | grep 'inet addr' | awk -F : '{print $2}' | awk '{print $1}')
      [ x"$device_ip" != "x" ] && {
        local device_mac=$(anete ifconfig $effect_device | grep 'HWaddr' | awk '{print $5}')
        if [ x"$device_mac" != "x" ];then
          anete arp -s -i $effect_device $device_ip $device_mac
          anete ipset add "${IMB_PREFIX}${effect_device}" "${device_ip},${device_mac}" -exist
          anete ipset add "${IP_PREFIX}${effect_device}" "${device_ip}" -exist
        fi
      }
    done
  done
}

stop(){
    while read LINE
    do
        local devname=$(echo $LINE | awk '{print $1}')
        local setname=$(echo $LINE | awk '{print $2}')
        local ipname=$(echo $LINE | awk '{print $3}')
        ipset list $ipname | sed -n '/^Members/,$p' | grep -v 'Members' >/tmp/.debind
        anete ipmac -d /tmp/.debind $devname
       # ipset destroy $setname
       # ipset destroy $ipname
       anete ipset flush $setname
       anete ipset flush $ipname
    done < /tmp/state/imb
    
    #rm /tmp/state/imb
}

start(){
   # local global_enable=$(uci get arp_defense.settings.enable)
   # local imb_pass=$(uci get arp_defense.settings.imb_pass)
   # local garp=$(uci get arp_defense.settings.garp)
   # local time=$(uci get arp_defense.settings.time)
    addDevice_IP_mac 
    lua /usr/lib/lua/imb/imb_reload.lua
}

{
#local time1=$(date +%s)
  flock 9
  stop
#local time2=$(date +%s)
  start
#local time3=$(date +%s)

#echo "$time3,$time2,$time1,$(($time3-$time2)),$(($time2-$time1))" >>/tmp/imb.time
} 9<>/tmp/imb.lock
