. /lib/functions.sh
. /lib/iptv/iptv_func.sh

eth0_dft_vid=2
eth1_dft_vid=1


select_vid()
{
	local used="$1"
	local vid=1

	
	for id in `seq 4094 -1 1`; do
		! list_contains used $id && {
			vid=$id
			break		
		}
	done

    eval "$2='$vid'"
}

# $1: vid
# $2: used vid
is_used_vid()
{
	local used="$1"
	local vid="$2"
	if list_contains used "$vid"; then
        return 0;
	else 
        return 1;
	fi
}

#eth0 lan vid
select_port1_lvid()
{
    local used_vid="$1"
    local slt

    if is_used_vid "$used_vid" "$eth0_dft_vid"; then
        select_vid "$used_vid" slt
    else
        slt="$eth0_dft_vid"
    fi

    eval "$2='$slt'"
}

select_port0_lvid()
{
    local used_vid="$1"
    local slt

    if is_used_vid "$used_vid" "$eth1_dft_vid"; then
        select_vid "$used_vid" slt
    else
        slt="$eth1_dft_vid"
    fi

    eval "$2='$slt'"
}

#eth1 lan vid

set_port1_dft_vlan()
{
    local vlan_id=$1
    #echo $vlan_id > /proc/sys/net/edma/default_wan_tag
}

set_port0_dft_vlan()
{
    local vlan_id=$1
    #echo $vlan_id > /proc/sys/net/edma/default_lan_tag
}


get_used_vlan()
{
    local used_vid
    local internet_vid
    local iptv_vid
    local gst_vid

    #internet vid
    config_load network
    config_get internet_vid "vlan" "id" "0"
    config_clear
    if [ "$internet_vid" != "0" ]; then
        append used_vid "$internet_vid"
    fi

    #iptv vid
    config_load iptv_v2
    config_get iptv_vid "info" "iptv_vid" "0"
    config_clear
    if [ "$iptv_vid" != "0" ]; then
        append used_vid "$iptv_vid"
    fi

    #guest eth vid
    config_load wifi 
    config_get gst_vid "guest" "vlan_id" "0"
    config_clear
    if [ "$gst_vid" != "0" ]; then
        append used_vid "$gst_vid"
    fi

    echo "$used_vid"
}

__set_port0_lvid()
{
    local used_vid="$1"
    local tag="$2"
    local vid_p0

    if [ "$tag" == "t" ]; then
        tag="on"
    elif [ "$tag" == "u" ]; then
        tag="off"
    fi

    select_port0_lvid "$used_vid" vid_p0
    #uci -c /etc/vlan.d set vlan.vlan0.vid="$vid_p4"
    #set_switch_vlan "$vid_p0" "0" "$tag" 1
    #set_port0_dft_vlan "$vid_p0"
    echo "$vid_p0"
}

__set_port1_lvid()
{
    local used_vid="$1"
    local tag="$2"
    local vid_p1

    #if [ "$tag" == "t" ]; then
    #    uci -c /etc/vlan.d set vlan.vlan1.ports="0t 5t"
    #elif [ "$tag" == "u" ]; then
    #    uci -c /etc/vlan.d set vlan.vlan1.ports="0t 5"
    #fi
    select_port1_lvid "$used_vid" vid_p1
    #uci -c /etc/vlan.d set vlan.vlan1.vid="$vid_p5"
    #set_port1_dft_vlan "$vid_p1"
    echo "$vid_p1"
}


__set_port0_wvid()
{
    local vid="$1"
    local tag="$2"
    #uci -c /etc/vlan.d set vlan.vlan0.vid=$vid
    if [ "$tag" == "t" ]; then
        tag="on"
    elif [ "$tag" == "u" ]; then
        tag="off"
    fi

    if [ -f "/tmp/internet_vid" ]; then
        old_vid=$(cat /tmp/internet_vid)
        echo "we get old internet vid $old_vid new vid $vid now!!!!!!!!!!!!!" > /dev/console
        if [ "$old_vid" != "0" ]; then
            unset_switch_vlan "$old_vid"
        fi
    fi

    set_switch_vlan "$vid" "0" "$tag" 1
    echo "write vid $vid to file                !!!!!!!!!!!!!" > /dev/console
    echo "$vid" > /tmp/internet_vid

#    set_port0_dft_vlan "4095"
}

__set_port1_wvid()
{
    local vid="$1"
    local tag="$2"

    unset_switch_vlan "$vid"
    #echo "0" > /tmp/internet_vid
    echo "start to clear vlan for eth1 $vid $tag" > /dev/console
#    uci -c /etc/vlan.d set vlan.vlan1.vid=$vid
#    if [ "$tag" == "t" ]; then
#        uci -c /etc/vlan.d set vlan.vlan1.ports="0t 5t"
#    elif [ "$tag" == "u" ]; then
#        uci -c /etc/vlan.d set vlan.vlan1.ports="0t 5"
#    fi
#    set_port5_dft_vlan "4095"
}

__set_both_wvid_tag()
{
#    local vlan_id="$1"
#    local tag="$2"

    __set_port0_wvid $1 $2
#    uci -c /etc/vlan.d set vlan.vlan0.vid="1"
#    uci -c /etc/vlan.d set vlan.vlan0.ports="0t 1 2 3 4"
#    uci -c /etc/vlan.d set vlan.vlan1.vid="$vlan_id"
#    if [ "$tag" == "t" ];then
#        uci -c /etc/vlan.d set vlan.vlan1.ports="0t 4t 5t"
#    elif [ "$tag" == "u" ]; then
#        uci -c /etc/vlan.d set vlan.vlan1.ports="0t 4 5"
#    fi
#    set_port4_dft_vlan "4095"
#    set_port5_dft_vlan "4095"
}


__iptv_set_vlan()
{
    local port="$1"
    local iptv_vid="$2"

    echo "iptv start to set iptv vid $iptv_vid" > /dev/console

    if [ -f "/tmp/iptv_vid" ]; then
        old_vid=$(cat /tmp/iptv_vid)
        if [ "$old_vid" != "0" ]; then
            unset_switch_vlan "$old_vid"
        fi
    fi
    set_switch_vlan "$iptv_vid" "0" "on" 1
    echo "iptv start to write iptv vid $iptv_vid to file" > /dev/console
    echo "$iptv_vid" > /tmp/iptv_vid

}

__iptv_clear_vlan()
{
    if [ -f "/tmp/iptv_vid" ]; then
        old_vid=$(cat /tmp/iptv_vid)
        if [ "$old_vid" != "0" ]; then
            unset_switch_vlan "$old_vid"
        fi
    fi

    echo "0" > /tmp/iptv_vid

    return 1
}

__guest_set_vlan()
{
    local port="$1"
    local guest_vlan_id="$2"

    local switch_device=$(uci -c /etc/vlan.d get vlan.@switch[0].name)

    uci -c /etc/vlan.d set vlan.guest_eth="switch_vlan"                              
    uci -c /etc/vlan.d set vlan.guest_eth.device="$switch_device"
    uci -c /etc/vlan.d set vlan.guest_eth.vlan="3"
    uci -c /etc/vlan.d set vlan.guest_eth.vid="$guest_vlan_id"
    uci -c /etc/vlan.d set vlan.guest_eth.ports="0t ${port}t"
    
}

__guest_set_both_vlan()
{
    local switch_device=$(uci -c /etc/vlan.d get vlan.@switch[0].name)
    uci -c /etc/vlan.d set vlan.guest_eth="switch_vlan"                              
    uci -c /etc/vlan.d set vlan.guest_eth.device="$switch_device"
    uci -c /etc/vlan.d set vlan.guest_eth.vlan="3"
    uci -c /etc/vlan.d set vlan.guest_eth.vid="$guest_vlan_id"
    uci -c /etc/vlan.d set vlan.guest_eth.ports="0t 4t 5t"
}

__guest_clear_vlan()
{
    local section_name
    section_name=$(uci -c /etc/vlan.d get vlan.guest_eth 2>/dev/null)

    [ -n "$section_name" ] && {
        uci -c /etc/vlan.d delete vlan.guest_eth
        return 0
    }
    return 1

}
