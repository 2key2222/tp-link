# Copyight(c) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     zone_api.sh
# bief     The Api for zone
# author   Yuan Fengjia
# vesion   1.0.0
# history  1.0.0, 13May15, Yuanfengjia, Ceate the file

. /lib/functions.sh
. /lib/functions/network.sh
. /lib/zone/zone_conf.sh
include /lib/network

#Get all zone int system
__zone_get_zonelist() {
    local zonelist
    
    zonelist=$(uci_get_state zone core zones)
    echo "$zonelist"
}

#Get interfaces(netifd) by one zone 
__zone_get_ifaces() {
    local zone_name="$1"
    local ifname_eth=""
    local ifname_x=""
    local ifaces=""
    
    ifname_eth=$(uci_get_state zone $zone_name ifname_eth)
    append ifaces $ifname_eth
    
    ifname_x=$(uci_get_state zone $zone_name ifname_1)
    [ -n "$ifname_x" ] && {
        append ifaces $ifname_x    
    }   
    
    ifname_x=$(uci_get_state zone $zone_name ifname_2)
    [ -n "$ifname_x" ] && {          
        append ifaces $ifname_x      
    }
    
    [ "$zone_name" == "VPN" ] && {
        ifaces=""
        ifaces=$(uci_get_state zone $zone_name ifaces)
    }
	
	[ "$zone_name" == "NORMAL" ] && {
        ifaces=""
        ifaces=$(uci_get_state zone $zone_name ifaces)
    }
    
    echo "$ifaces" 
}

#Get wan interfaces(netifd) by one zone or interface
__zone_get_wan_ifaces() {
    local zone_name="$1"
    local effect_ifaces=""

    effect_ifaces=$(uci_get_state zone $zone_name effect_ifs)
    [ "$effect_ifaces" == "" ] && {
        #maybe is a normal or vpn interface
        local device=""
        device=$(uci_get_state zone $zone_name devname)
        [ -n "$device" ] && {
           #it is a normal or vpn interface
           effect_ifaces=$zone_name
        }
    }
    echo "$effect_ifaces"
}

#Get effect main wan interfaces(netifd) by one zone
__zone_get_effect_main_wan_ifaces() {
    local zone_name="$1"
    local effect_ifaces=""
    local t_poe_enable
    local ret=""

    effect_ifaces=$(uci_get_state zone $zone_name effect_ifs)

    for iface in $effect_ifaces ; do
        t_poe_enable=$(uci get network.$iface.t_poe_enable)
        [ -n "$t_poe_enable" -a "$t_poe_enable" = "1" ] && {
            ret=$iface
        }
    done

    [ "$ret" == "" ] && {
        ret=$effect_ifaces
    }

    echo "$ret"
}

#Get effect interfaces(netifd) by one zone or interface
__zone_get_effect_ifaces() {
    local zone_name="$1"
    local effect_ifaces=""
    effect_ifaces=$(__zone_get_effect_main_wan_ifaces "$zone_name")

    [ "$effect_ifaces" == "" ] && {
        #maybe is a normal or vpn interface
        local device=""
        device=$(uci_get_state zone "$zone_name" devname)
        [ -n "$device" ] && {
           #it is a normal or vpn interface
           effect_ifaces=$zone_name
        }
    }

    echo "$effect_ifaces"
}

#Get all devices(netifd) by one zone 
__zone_get_devices() {
    local zone_name="$1"
    local devname_eth=""
    local devname_x=""
    local devices=""

    
    devname_eth=$(uci_get_state zone $zone_name devname_eth)
    append devices $devname_eth  
    
    devname_x=$(uci_get_state zone $zone_name devname_1)
    [ -n "$devname_x" ] && {
        append devices $devname_x    
    }   
    
    devname_x=$(uci_get_state zone $zone_name devname_2)
    [ -n "$devname_x" ] && {          
        append device $devname_x      
    }
    
    [ "$zone_name" == "VPN" ] && {
        devices=""
        devices=$(uci_get_state zone $zone_name devices)
    }
	
	[ "$zone_name" == "NORMAL" ] && {
        devices=""
        devices=$(uci_get_state zone $zone_name devices)
    }
    
    echo "$devices"    
}

#Get wan effect devices(netifd) by one zone or interface
__zone_get_wan_devices() {
    local zone_name="$1"
    local effect_devices=""

    effect_devices=$(uci_get_state zone $zone_name effect_devs)
    [ "$effect_devices" == "" ] && {
        #maybe is a normal or vpn interface 
        effect_devices=$(uci_get_state zone $zone_name devname)
    }
    
    echo "$effect_devices"
}

#Get main wan effect devices by one zone
__zone_get_effect_main_wan_devices() {
    local effect_iface=$(__zone_get_effect_main_wan_ifaces $1)
    local effect_devices=$(__zone_get_device_byif $effect_iface)

    echo "$effect_devices"
}

#Get all effect devices(netifd) by one zone or interface
__zone_get_effect_devices() {
    local zone_name="$1"
    local effect_devices=""

    effect_devices=$(__zone_get_effect_main_wan_devices "$zone_name")
    [ "$effect_devices" == "" ] && {
        #maybe is a normal or vpn interface 
        effect_devices=$(uci_get_state zone "$zone_name" devname)
    }

    echo "$effect_devices" 
}

#Get the device by one interface
__zone_get_device_byif() {
    local iface="$1"
    local device=""
    
    device=$(uci_get_state zone $iface devname)
    echo "$device"
}

#Get the interface by one device(tmp,just for ipsec)
__zone_get_iface_bydev() {
    local device="$1"
    
    local iface=""
    #local devs=""
   
    device=${device/-/_}
    device=${device/./_}
    iface=$(uci_get_state zone $device ifname)
    echo "$iface" 
}

#Get the zone by one interface.
__zone_get_zone_byif() {
    local iface="$1"
    local zonelist=""
    local zone=""
    
    zonelist=$(uci_get_state zone core zones)
    for i in $zonelist; do
		    local ifaces=$(__zone_get_ifaces $i)
			  for j in $ifaces; do
				    [ "$j" == "$iface" ] && {
				        echo "$i"
				        return 0
				    }
			  done
	  done
}

#Get the iface state by one device.state:UP,DOWN
__zone_get_iface_state() {
    local iface="$1"
    
    local ipaddr=""
	network_flush_cache
    network_get_ipaddr ipaddr "$iface"
    if [ "$ipaddr" == "" ]; then
        echo "DOWN"
    else
        echo "UP"
    fi
}

#Get VPN interface list
__zone_get_vpn_ifaces() {
    local vpn_ifaces=""
    
    vpn_ifaces=$(uci_get_state zone VPN ifaces)
    echo "$vpn_ifaces"
}

#Get VPN device list
__zone_get_vpn_devices() {
    local vpn_devs=""
    
    vpn_devs=$(uci_get_state zone VPN devices)
    echo "$vpn_devs"
}

#Get NORMAL interface list
__zone_get_normal_ifaces() {
    local normal_ifaces=""
    
    normal_ifaces=$(uci_get_state zone NORMAL ifaces)
    echo "$normal_ifaces"
}

#Get NORMAL device list
__zone_get_normal_devices() {
    local normal_devs=""
    
    normal_devs=$(uci_get_state zone NORMAL devices)
    echo "$normal_devs"
}

__zone_check_if_effect()
{
    local iface=$1
    local zonelist=$(uci_get_state zone core zones)
    for i in $zonelist; do
        local effect_ifs=$(__zone_get_effect_ifaces $i)
        for j in $effect_ifs; do
            [ "$j" == "$iface" ] && {
                return 0
            }
        done
    done
    return 1  
}

__zone_check_dev_effect()
{
    local dev=$1
    local zonelist=$(uci_get_state zone core zones)
    for i in $zonelist; do
        local effect_devs=$(__zone_get_effect_devices $i)
        for j in $effect_devs; do
            [ "$j" == "$dev" ] && {
                return 0
            }
        done
    done
    return 1 
}

#Get ethernet device by one interface
__zone_get_eth_device() {
    local zone_name="$1"
	local eth_device=""

	network_get_physdev eth_device $zone_name
    echo "$eth_device"
}

#Get the zone by one interface.
__zone_get_zone_by_device() {
    local device="$1"
    local zonelist=""
    local devname_eth=""
    local iface=""

    zonelist=$(uci_get_state zone core zones)
    [ -z "$zonelist" ] && zonelist="WAN1 WAN2 WAN3 WAN4"
    for i in $zonelist; do
        iface=$(echo $i | tr '[A-Z]' '[a-z]')_eth
        network_get_physdev devname_eth "$iface"
        [ "$device" == "$devname_eth" ] && {
            echo "$i"
            return 0
        }
    done
    return 1
}

#check VPN interface
__zone_check_vpn_interface() {
	local iface="$1"
	
	local vpn_ifaces=$(__zone_get_vpn_ifaces)
	for i in $vpn_ifaces; do
        [ "$i" == "$iface" ] && {
			echo "true"
            return 0
        }
    done
	
	echo "false"
	return 1
}