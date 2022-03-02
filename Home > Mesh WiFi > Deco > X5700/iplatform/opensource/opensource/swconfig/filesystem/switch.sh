#!/bin/sh
# Copyright (C) 2009 OpenWrt.org

. /lib/network/vlan_func.sh

#update vlan info to config -- /etc/vlan.d/vlan
lock_vlan="/var/run/vlan.lock"

DEBUG_OUTOUT=1

switch_echo() {
    if [ "$DEBUG_OUTOUT" -gt 0 ]; then
            echo "${1}: ""$2"> /dev/console
        fi
}


__set_wan_vlan() {

    config_load iptv_v2
    config_get iptv_enable info enable 0
    config_get iptv_vid info iptv_vid
    config_get iptv_prio info iptv_prio
    config_get iptv_type info iptv_type "normal"
    config_clear

    local used_vid
    local vid_p0
    local vid_p1
    local used_vid=$(get_used_vlan)

    local is_eth0_at_wan=`brctl show br-wan | grep eth0`
    local is_eth1_at_wan=`brctl show br-wan | grep eth1`

    #switch_name=$(uci -c /etc/vlan.d get vlan.@switch[0].name)
    vlan_id=$(uci get network.vlan.id)
    vlan_tag=$(uci get network.vlan.tag_802_1q)

    local iptv_vlan_config="0"
    if [ -f "/tmp/iptv_vid" ]; then
        iptv_vlan_config=$(cat /tmp/iptv_vid)
    fi

    if [ "$vlan_tag" == "0" ]; then
        vlan_need_tag="off" 
    else
        vlan_need_tag="on" 
    fi

    echo "start to config vid for internet now!!!!!!!!!!!!!" > /dev/console

    if [ "$iptv_enable" = "0" ]; then
        if [ "$iptv_vlan_config" != "0" ]; then
            switch_echo switch "iptv disable, delete vlan config about iptv"
            unset_switch_vlan "$iptv_vlan_config"
        fi
    fi

    if [ -z "$is_eth0_at_wan" -a -z "$is_eth1_at_wan" ]; then
        switch_echo switch "no interface at br-wan"

    elif [ -z "$is_eth0_at_wan" ]; then
        switch_echo switch "eth1 at br-wan"
        if [ "$vlan_tag" == "0" ]; then
            __set_port0_wvid "$vlan_id" "u"
        else
            __set_port0_wvid "$vlan_id" "t"
        fi

        vid_p1=$(__set_port1_lvid "${used_vid}" "u")
        append used_vid "$vid_p1"
        switch_echo switch "set_wan_vlan: select p1: $vid_p1"

        #if [ "$iptv_enable" = "1" ]; then
        #    switch_echo switch "set eth0 to iptv"
            #uci -c /etc/vlan.d set vlan.iptv="switch_vlan"
            #uci -c /etc/vlan.d set vlan.iptv.ports="0t 1 2 3 4t"
            #uci -c /etc/vlan.d set vlan.iptv.device="$switch_name"
            #uci -c /etc/vlan.d set vlan.iptv.vlan="10"
            #uci -c /etc/vlan.d set vlan.iptv.vid=$iptv_vid
        #fi

        #uci commit -c /etc/vlan.d
        #swconfig dev $switch_name load /etc/vlan.d/vlan

    elif [ -z "$is_eth1_at_wan" ]; then
        switch_echo switch "eth0 at br-wan"

        if [ "$vlan_tag" == "0" ]; then
            __set_port1_wvid "$vlan_id" "u"
        else
            __set_port1_wvid "$vlan_id" "t"
        fi

        vid_p0=$(__set_port0_lvid "${used_vid}" "u")
        append used_vid "$vid_p0"
        switch_echo switch "set_wan_vlan: select p0: $vid_p0"

        if [ "$iptv_enable" = "1" ]; then
            switch_echo switch "set eth1 to iptv"
            __iptv_set_vlan 0 "$iptv_vid"
            #uci -c /etc/vlan.d set vlan.iptv="switch_vlan"
            #uci -c /etc/vlan.d set vlan.iptv.ports="0t 5t"
            #uci -c /etc/vlan.d set vlan.iptv.device="$switch_name"
            #uci -c /etc/vlan.d set vlan.iptv.vlan="10"
            #uci -c /etc/vlan.d set vlan.iptv.vid=$iptv_vid
        fi

        #uci commit -c /etc/vlan.d
        #swconfig dev $switch_name load /etc/vlan.d/vlan
    else
        switch_echo switch "both eth0 and eth1 at br-wan"

        local wanstatus=$(cat /tmp/wanDetection) 
        if [ "$wanstatus" = "0" ]; then
            local eth0_flag=$(isWan eth0)
            local eth1_flag=$(isWan eth1)
            if [ "$eth0_flag" = "true" ] && [ "$eth1_flag" = "false" ]; then
                #eth0 is wan
                if [ "$vlan_tag" == "0" ]; then
                    __set_port1_wvid "$vlan_id" "u"
                else
                    __set_port1_wvid "$vlan_id" "t"
                fi

                vid_p0=$(__set_port0_lvid "${used_vid}" "u")
                append used_vid "$vid_p0"
                switch_echo switch "set_wan_vlan: select p0: $vid_p0"

            elif [ "$eth0_flag" = "false" ] && [ "$eth1_flag" = "true" ]; then
                #eth1 is wan
                if [ "$vlan_tag" == "0" ]; then
                    __set_port0_wvid "$vlan_id" "u"
                else
                    __set_port0_wvid "$vlan_id" "t"
                fi

                vid_p1=$(__set_port1_lvid "${used_vid}" "u")
                append used_vid "$vid_p1"
                switch_echo switch "set_wan_vlan: select p1: $vid_p1"
            else
                if [ "$vlan_tag" == "0" ]; then
                    __set_both_wvid_tag "$vlan_id" "u"
                else
                    __set_both_wvid_tag "$vlan_id" "t"
                fi
            fi
        else
            if [ "$vlan_tag" == "0" ]; then
                __set_both_wvid_tag "$vlan_id" "u"
            else
                __set_both_wvid_tag "$vlan_id" "t"
            fi
        fi

        #uci commit -c /etc/vlan.d
        #swconfig dev $switch_name load /etc/vlan.d/vlan

    fi

}

set_wan_vlan() {
    echo "start to lock vlan" > /dev/console
    lock $lock_vlan
    echo "after to lock vlan" > /dev/console
    trap "" INT TERM ABRT QUIT ALRM 
    __set_wan_vlan
    trap - INT TERM ABRT QUIT ALRM 
    echo "start to unlock vlan" > /dev/console
    lock -u $lock_vlan
    echo "after to unlock vlan" > /dev/console
}

__reset_wan_vlan() {
    #switch_name=$(uci -c /etc/vlan.d get vlan.@switch[0].name)
    iptv_vlan_config=$(uci -c /etc/vlan.d get vlan.iptv)

    config_load iptv_v2
    config_get iptv_enable info enable 0
    config_get iptv_vid info iptv_vid
    config_get iptv_prio info iptv_prio
    config_get iptv_type info iptv_type "normal"
    config_clear


    echo "start to clean        vid for internet now!!!!!!!!!!!!!" > /dev/console

    if [ -f "/tmp/internet_vid" ]; then
        old_vid=$(cat /tmp/internet_vid)
        echo "we ######### get old vid $old_vid for internet now!!!!!!!!!!!!!" > /dev/console
        if [ "$old_vid" != "0" ]; then
            unset_switch_vlan "$old_vid"
        fi
    fi

    echo "start to clean        vid  to file     ooooooooooooooooooo now!!!!!!!!!!!!!" > /dev/console
    echo "0" > /tmp/internet_vid

    local used_vid
    local vid_p0
    local vid_p1
    local used_vid=$(get_used_vlan)

    local is_eth0_at_wan=`brctl show br-wan | grep eth0`
    local is_eth1_at_wan=`brctl show br-wan | grep eth1`

    if [ "$iptv_enable" = "0" ]; then
        if [ -n "$iptv_vlan_config" ]; then
            switch_echo switch "iptv disable, delete vlan config about iptv"
            __iptv_clear_vlan
            #uci -c /etc/vlan.d delete vlan.iptv
        fi
    else

        if [ -z "$is_eth0_at_wan" -a -z "$is_eth1_at_wan" ]; then
            switch_echo switch "vlan not enable, no interface at br-wan"
        elif [ -z "$is_eth0_at_wan" ]; then
            switch_echo switch "vlan not enable, eth1 at br-wan"

            if [ "$iptv_enable" = "1" ]; then
                switch_echo switch "set eth1 to iptv"
                __iptv_set_vlan "0" "$iptv_vid"
                #uci -c /etc/vlan.d set vlan.iptv="switch_vlan"
                #uci -c /etc/vlan.d set vlan.iptv.ports="0t 1 2 3 4t"
                #uci -c /etc/vlan.d set vlan.iptv.device="$switch_name"
                #uci -c /etc/vlan.d set vlan.iptv.vlan="10"
                #uci -c /etc/vlan.d set vlan.iptv.vid=$iptv_vid
            fi

        elif [ -z "$is_eth1_at_wan" ]; then
            switch_echo switch "vlan not enable, eth0 at br-wan"

            if [ "$iptv_enable" = "1" ]; then
                switch_echo switch "set eth0 to iptv"
                #uci -c /etc/vlan.d set vlan.iptv="switch_vlan"
                #uci -c /etc/vlan.d set vlan.iptv.ports="0t 5t"
                #uci -c /etc/vlan.d set vlan.iptv.device="$switch_name"
                #uci -c /etc/vlan.d set vlan.iptv.vlan="10"
                #uci -c /etc/vlan.d set vlan.iptv.vid=$iptv_vid
            fi
        fi
    fi

    vid_p0=$(__set_port0_lvid "${used_vid}" "u")
    append used_vid "$vid_p0"
    switch_echo switch "reset_wan_vlan: select p0: $vid_p0"

    vid_p1=$(__set_port1_lvid "${used_vid}" "u")
    append used_vid "$vid_p1"
    switch_echo switch "reset_wan_vlan: select p1: $vid_p1"

    #uci commit -c /etc/vlan.d
    #swconfig dev $switch_name load /etc/vlan.d/vlan

}

reset_wan_vlan()
{

    lock $lock_vlan
    trap "" INT TERM ABRT QUIT ALRM 
    __reset_wan_vlan
    trap - INT TERM ABRT QUIT ALRM 
    lock -u $lock_vlan
}

setup_switch_dev() {
	config_get name "$1" name
	name="${name:-$1}"

	device_id=$(getfirm DEV_ID)
	role=$(uci get bind_device_list."$device_id".role)
	vlan_enable=$(uci get network.vlan.enable)
	if [ "$vlan_enable" == "1" -o "$vlan_enable" == "0" ];then
        [ "$role" != "RE" ] && {
            if [ "$vlan_enable" == "1" ]; then 
                __set_wan_vlan
            elif [ "$vlan_enable" == "0" ]; then 
                __reset_wan_vlan
			fi
		}
	else
		uci set network.vlan=vlan
		uci set network.vlan.enable=0
		uci set network.vlan.isp_name=0
		uci set network.vlan.id=0
		uci set network_sync.vlan=vlan
		uci set network_sync.vlan.enable=0
		uci set network_sync.vlan.isp_name=0
		uci set network_sync.vlan.id=0
		uci commit network
		uci commit network_sync
		saveconfig 
	fi
	
	#set switch name
	[ -d "/sys/class/net/$name" ] && ifconfig "$name" up
	device_name=$(uci -c /etc/vlan.d get vlan.@switch[0].name)
	[ "$device_name" != "$name" ] && {
		uci -c /etc/vlan.d set vlan.@switch[0].name="$name"
		uci -c /etc/vlan.d set vlan.vlan0.device="$name"
		uci -c /etc/vlan.d set vlan.vlan1.device="$name"
	}

	#todo uci get network vlan info -> /etc/vlan.d/vlan
	#swconfig dev "$name" load /etc/vlan.d/vlan
}

set_switch_default_fdb() {
	mac=$(getfirm MAC)
	# bind lan mac to cpu port to avoid ARP attack #
    if [ -f /usr/sbin/ssdk_sh ]; then
        ssdk_sh fdb entry add $mac 1 forward forward 0 yes no no no no no no no
    fi
}

setup_switch() {
    lock $lock_vlan
    trap "" INT TERM ABRT QUIT ALRM 

	config_load network
	config_foreach setup_switch_dev switch
    config_clear
	#set_switch_default_fdb

    trap - INT TERM ABRT QUIT ALRM 
    lock -u $lock_vlan
}


