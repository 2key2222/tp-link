#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     ipgroup core.sh
# brief    
# author   Chen chen
# version  1.0.0
# date     11June15
# histry   arg 1.0.0, 08June15, Chen chen, Create the file.

. /lib/zone/zone_api.sh
. /lib/functions/network.sh

ipgroup_load()
{
	{
		flock -w 30 165
		lua /usr/lib/lua/ipgroup/ipgroup_reload.lua
	} 165<>/tmp/ipgroup_lock
}

ipgoup_check_modify()
{

    while read root_group
    do
        ipset list "$root_group" > "/tmp/ipset_new_content_$root_group" 
        local old_content="/tmp/ipset_old_content_${root_group}"
        local new_content="/tmp/ipset_new_content_${root_group}"       
        if [ -e "$old_content" ]
            then
            local is_update=`cmp "$old_content" "$new_content"`
            if [ "$is_update" != "" ]
                then
                echo "hotplug-call $root_group update"
                export action="update"
                export update_group="$root_group"
                env -i ACTION=update group_name="$root_group" /sbin/hotplug-call ipgroup
            fi
        fi 
        rm "$old_content"
        rm "$new_content"
    done < /tmp/ipgroup_name.tmp   
}

ipgroup_load_default_ifaces_set()
{
	ipset create Me hash:ip -exist
	ipset flush Me
	
	vnete ipset create Me hash:ip -exist
	vnete ipset flush Me

	zone_list=$(zone_get_zonelist)
	for zone in ${zone_list};do
		ifaces=$(zone_get_wan_ifaces "${zone}")

		for iface in $ifaces; do
			if_ipaddr=""
			network_get_ipaddr if_ipaddr "$iface"
			
			[ -z "$if_ipaddr" ] && {
				continue
			}

			ipset add Me $if_ipaddr -exist

		done
	done

	#ipset create IPGROUP_LAN hash:net -exist
	#ipset flush IPGROUP_LAN
	#ifaces=$(zone_get_effect_ifaces "LAN")

	#for iface in $ifaces;do
	#	network_get_ipaddr if_ipaddr "$iface"
	#	if_ipaddr=${if_ipaddr%[0-9]}
	#	if_ipaddr=$if_ipaddr"0"
    #
	#	network_get_subnet if_mask "$iface"
	#	if_mask=${if_mask#*/}
	#				
	#	ipset add IPGROUP_LAN $if_ipaddr/$if_mask -exist
					
	#done
}


