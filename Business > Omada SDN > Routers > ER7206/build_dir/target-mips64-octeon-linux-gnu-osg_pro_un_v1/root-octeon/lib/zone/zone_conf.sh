# Copyight(c) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     zone_conf.sh
# bief     Config the zone info
# author   Yuan Fengjia
# vesion   1.0.0
# history  1.0.0, 13May15, Yuanfengjia, Ceate the file

. /usr/share/libubox/jshn.sh

GROUP_ZONES="LAN VPN WAN1 WAN2 WAN3 WAN4"

_zone_create_group() {
    if [ "$1" != "list" ]; then
        ipset create "ZONE_${2}" hash:iface
    else
        zones="${2// /_}"
        ipset create "ZONE_${zones}" list:set
        for zone in ${2}
        do
            ipset add "ZONE_${zones}" "ZONE_${zone}"
        done
    fi
}

zone_create_group() {
    # create wan group
    _zone_create_group one ""
    _zone_create_group one "LAN"
    _zone_create_group one "VPN"
    _zone_create_group one "WAN1"
    _zone_create_group one "WAN2"
    _zone_create_group one "WAN3"
    _zone_create_group one "WAN4"

    # create wan groups
    _zone_create_group list "WAN1 WAN2"
    _zone_create_group list "WAN1 WAN3"
    _zone_create_group list "WAN1 WAN4"
    _zone_create_group list "WAN2 WAN3"
    _zone_create_group list "WAN2 WAN4"
    _zone_create_group list "WAN3 WAN4"
    _zone_create_group list "WAN1 WAN2 WAN3"
    _zone_create_group list "WAN1 WAN2 WAN4"
    _zone_create_group list "WAN1 WAN3 WAN4"
    _zone_create_group list "WAN2 WAN3 WAN4"
    _zone_create_group list "WAN1 WAN2 WAN3 WAN4"

    # create wan & vpn groups
    _zone_create_group list "VPN WAN1"
    _zone_create_group list "VPN WAN2"
    _zone_create_group list "VPN WAN3"
    _zone_create_group list "VPN WAN4"
    _zone_create_group list "VPN WAN1 WAN2"
    _zone_create_group list "VPN WAN1 WAN3"
    _zone_create_group list "VPN WAN1 WAN4"
    _zone_create_group list "VPN WAN2 WAN3"
    _zone_create_group list "VPN WAN2 WAN4"
    _zone_create_group list "VPN WAN3 WAN4"
    _zone_create_group list "VPN WAN1 WAN2 WAN3"
    _zone_create_group list "VPN WAN1 WAN2 WAN4"
    _zone_create_group list "VPN WAN1 WAN3 WAN4"
    _zone_create_group list "VPN WAN2 WAN3 WAN4"
    _zone_create_group list "VPN WAN1 WAN2 WAN3 WAN4"
}

zone_rebuild_group() {
    echo $GROUP_ZONES | grep -vqE "(^| )${1}( |$)" && return

    #create zone group
    ipset flush "ZONE_$1"

    devs=$(uci_get_state zone $1 effect_devs)

    for dev in $devs
    do
        ipset add "ZONE_$1" "$dev"
    done
}

zone_group() {
    local zones=""

    for gzone in $GROUP_ZONES
    do
        for zone in $@
        do
            if [ "$gzone" == "$zone" ]; then
		if [ -z "$zones" ]; then
                    zones=$gzone
                else
                    zones=$zones" "$gzone
                fi
            fi
        done
    done

    echo -n "ZONE_${zones// /_}"
}

_config_vpn_iface() {
    local vpn_iface=""
    local name="" 
    local count=""
    
    local iface=""
    local device="" 
    name=$(uci_get zone "$1")
    [ -n "$name"  ] && {
        for i in $(uci_get_state zone VPN ifaces); do
            local j=${i#}
            append iface $j
        done
        
        local tmp=$(uci_get zone "$1" iface)
        append iface $tmp
        #echo "ifaces=$iface"
        uci_toggle_state zone VPN ifaces "$iface"
        uci_toggle_state zone VPN effect_ifs "$iface"
        
        for m in $(uci_get_state zone VPN devices); do
            local n=${m#}                          
            append device $n                           
        done
        #echo "devices_old=$device"
        tmp=""
        tmp=$(uci_get zone "$1" dev)
        append device $tmp
        #echo "devices=$device"                                         
        uci_toggle_state zone VPN devices "$device"
        uci_toggle_state zone VPN effect_devs "$device"
        
        iface=""
        device=""
        iface=$(uci_get zone "$1" iface)
        device=$(uci_get zone "$1" dev)
        #echo "iface=$iface"
        uci_set_state zone $iface "" ${iface}_state
        uci_set_state zone $iface devname $device
        device=${device/-/_}
 
        uci_set_state zone $device "" ${device}_state
        uci_set_state zone $device ifname $iface
    }
}

_config_normal_iface() {
    local normal_iface=""
    local name="" 
    local count=""
    
    local iface=""
    local device="" 
    name=$(uci_get zone "$1")
    [ -n "$name"  ] && {
        for i in $(uci_get_state zone NORMAL ifaces); do
            local j=${i#}
            append iface $j
        done
        
        local tmp=$(uci_get zone "$1" iface)
        append iface $tmp
        #echo "ifaces=$iface"
        uci_toggle_state zone NORMAL ifaces "$iface"
        uci_toggle_state zone NORMAL effect_ifs "$iface"
        
        for m in $(uci_get_state zone NORMAL devices); do
            local n=${m#}                          
            append device $n                           
        done
        tmp=""
        tmp=$(uci_get zone "$1" dev)
        append device $tmp
        #echo "devices=$device"                                         
        uci_toggle_state zone NORMAL devices "$device"
        uci_toggle_state zone NORMAL effect_devs "$device"
        
        iface=""
        device=""
        iface=$(uci_get zone "$1" iface)
        device=$(uci_get zone "$1" dev)
        #echo "iface=$iface"
        uci_set_state zone $iface "" ${iface}_state
        uci_set_state zone $iface devname $device
        device=${device/./_}
        device=${device/-/_}
 
        uci_set_state zone $device "" ${device}_state
        uci_set_state zone $device ifname $iface
    }
}

_zone_state_config() {
    local zone_name=$1
    
    local ifname_eth
    local ifname_x
    local devname_eth
    local devname_x
    local zone_old
    local proto

    #echo "zone_name=$zone_name"
    [ -n "$zone_name" ] && {
        #echo "set zones"
        for zs in $(uci_get_state zone core zones); do
                local i=${zs#*}
                append zone_old $i
        done
                                                               

        append zone_old $zone_name  
 
        #echo "zone_old=$zone_old"
        uci_toggle_state zone core zones "$zone_old"
        
        #echo "set interfaces"
        ifname_eth=$(uci_get zone "$zone_name" if_eth)
        #echo "ifname_eth=$ifname_eth"
        uci_set_state zone $zone_name ifname_eth "$ifname_eth"
        
        ifname_x=$(uci_get zone "$zone_name" if_1)
        #echo "ifname_x=$ifname_x"
        [ -n "$ifname_x" ] && {
        	uci_set_state zone $zone_name ifname_1 "$ifname_x"
        }
        
        ifname_x=$(uci_get zone "$zone_name" if_2)
        #echo "ifname_x=$ifname_x"
        [ -n "$ifname_x" ] && {
        	uci_set_state zone $zone_name ifname_2 "$ifname_x"
        }
        
        #echo "set devices"
        devname_eth=$(uci_get zone "$zone_name" dev_eth)
        #echo "devname_eth=$devname_eth"
        uci_set_state zone $zone_name devname_eth "$devname_eth"
        
        devname_x=$(uci_get zone "$zone_name" dev_1)
        #echo "devname_x=$devname_x"
        [ -n "$devname_x" ] && {
        	uci_set_state zone $zone_name devname_1 "$devname_x"
        }
        
        devname_x=$(uci_get zone "$zone_name" dev_2)
        #echo "devname_x=$devname_x"
        [ -n "$devname_x" ] && {
        	uci_set_state zone $zone_name devname_2 "$devname_x"
        }
        #get the proto
        proto=$(uci_get network "$ifname_eth" proto)
        [ "none" == "$proto" ] && {
          ifname_eth=""
          devname_eth=""
        }
        
        #echo "set effect interfaces"
        ifname_x=$(uci_get zone "$zone_name" if_1)
        append ifname_eth $ifname_x
        #echo "effect_ifs=$ifname_eth"
        uci_set_state zone $zone_name effect_ifs "$ifname_eth"
        
        #echo "set effect devices"
        devname_x=$(uci_get zone "$zone_name" dev_1)
        append devname_eth $devname_x
        #echo "effect_devs=$devname_eth"
        uci_set_state zone $zone_name effect_devs "$devname_eth"
        
        #echo "set interfaces devices map"
        ifname_eth=$(uci_get zone "$zone_name" if_eth)
        devname_eth=$(uci_get zone "$zone_name" dev_eth)
        #echo "ifname_eth=$ifname_eth,devname_eth=$devname_eth"
        uci_set_state zone $ifname_eth "" ${ifname_eth}_state
        uci_set_state zone $ifname_eth devname "$devname_eth"
        
        #echo "devname_eth=$devname_eth"
        devname_eth=${devname_eth/./_}
        devname_eth=${devname_eth/-/_}
        #echo "devname_eth=$devname_eth" 
        uci_set_state zone $devname_eth "" ${devname_eth}_state
        uci_set_state zone $devname_eth ifname "$ifname_eth" 
        
        ifname_x=""
        devname_x=""
        ifname_x=$(uci_get zone "$zone_name" if_1)
        devname_x=$(uci_get zone "$zone_name" dev_1)
        #echo "ifname_x=$ifname_x,devname_x=$devname_x"
        [ -n "$ifname_x" ] && [ -n "$devname_x" ] && {
            uci_set_state zone $ifname_x "" ${ifname_x}_state
            uci_set_state zone $ifname_x devname "$devname_x"
            
            devname_x=${devname_x/./_}
            devname_x=${devname_x/-/_}
            uci_set_state zone $devname_x "" ${devname_x}_state
            uci_set_state zone $devname_x ifname "$ifname_x" 
        }
        
        ifname_x=""
        devname_x=""
        ifname_x=$(uci_get zone "$zone_name" if_2)
        devname_x=$(uci_get zone "$zone_name" dev_2)
        #echo "ifname_x=$ifname_x,devname_x=$devname_x"
        [ -n "$ifname_x" ] && [ -n "$devname_x" ] && {
            uci_set_state zone $ifname_x "" ${ifname_x}_state
            uci_set_state zone $ifname_x devname "$devname_x"
            
            devname_x=${devname_x/./_}
            devname_x=${devname_x/-/_}                                                                                      
            uci_set_state zone $devname_x "" ${devname_x}_state                                                             
            uci_set_state zone $devname_x ifname "$ifname_x" 
        }   
        
        #VPN
        [ "$zone_name" == "VPN" ] && {
            #config_foreach _config_vpn_iface
            local vpn_iface
            local count
            
            config_get vpn_iface "$zone_name" iface
            #echo "vpn_iface=$vpn_iface"
            let count=0
            for i in $vpn_iface
            do 
                let count=$count+1
                #echo "i=$i"
                #config_foreach _config_vpn_iface iface $i $count
                _config_vpn_iface $i
            done       
        } 
		
		#NORMAL:for multi interface product such as TL-ER7520G
		[ "$zone_name" == "NORMAL" ] && {
            local normal_iface
            local count
            
            config_get normal_iface "$zone_name" iface
            #echo "normal_iface=$normal_iface"
            let count=0
            for i in $normal_iface
            do 
                let count=$count+1
                #echo "i=$i"
                _config_normal_iface $i
            done       
        }
	zone_rebuild_group "$zone_name"
    }

}

zone_config() {
    config_foreach _zone_state_config zone
    
    local zones=$(uci_get_state zone core zones)
    #echo "zones=$zones"
    uci_toggle_state zone core zones "$zones"
}

