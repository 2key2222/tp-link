#!/bin/sh

#get lan ip and mask
local br_lan
local mask
config_load "network"
config_get br_lan 'lan' ipaddr ""
config_get mask 'lan' netmask ""

#don't forward ip that is different from lan network to wan
if [ "${old_mode}" == "Non-Nat" -o "${old_mode}" == "Classic" ] && [ "${new_mode}" == "Nat" ]; then
        uci set firewall.global.lan_ip_limit=1
        uci set firewall.global.remote_access_lan=0
        uci commit firewall
        #echo "set lan_ip_limit 1" > /dev/console

	fw flush 4 f zone_lan_ip_limit
	fw flush 4 f zone_wan_lan_protection
        fw add 4 f zone_lan_ip_limit DROP { "! -s ${br_lan}/${mask}" }
	fw add 4 f zone_wan_lan_protection DROP { "-d ${br_lan}/32" }

#forward ip that is different from lan network to wan
elif [ "${old_mode}" == "Nat" ] && [ "${new_mode}" == "Non-Nat" -o "${new_mode}" == "Classic" ]; then
        uci set firewall.global.lan_ip_limit=0
	uci set firewall.global.remote_access_lan=1
        uci commit firewall
        #echo "set lan_ip_limit 0" > /dev/console
	fw flush 4 f zone_lan_ip_limit
	fw flush 4 f zone_wan_lan_protection

#do nothing
else
        echo "do nothing for firewall" > /dev/console
fi

