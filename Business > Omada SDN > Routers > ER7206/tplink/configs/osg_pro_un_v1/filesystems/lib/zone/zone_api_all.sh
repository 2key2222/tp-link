# Copyight(c) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     zone_api.sh
# bief     The Api for zone
# author   Yuan Fengjia
# vesion   1.0.0
# history  1.0.0, 13May15, Yuanfengjia, Ceate the file
. /lib/zone/zone_api_core.sh
ZONE_FILE_LOCK=/tmp/zone.file.lock

#Get all zone int system
zone_get_zonelist() {
	{
		flock -s 199
		__zone_get_zonelist "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get interfaces(netifd) by one zone 
zone_get_ifaces() {
	{
		flock -s 199
		__zone_get_ifaces "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get wan interfaces(netifd) by one zone or interface
zone_get_wan_ifaces() {
	{
		flock -s 199
		__zone_get_wan_ifaces "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get effect main wan interfaces(netifd) by one zone
zone_get_effect_main_wan_ifaces() {
	{
		flock -s 199
		__zone_get_effect_main_wan_ifaces "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get effect interfaces(netifd) by one zone or interface
zone_get_effect_ifaces() {
	{
		flock -s 199
		__zone_get_effect_ifaces "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get all devices(netifd) by one zone 
zone_get_devices() {
	{
		flock -s 199
		__zone_get_devices "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get wan effect devices(netifd) by one zone or interface
zone_get_wan_devices() {
	{
		flock -s 199
		__zone_get_wan_devices "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get main wan effect devices by one zone
zone_get_effect_main_wan_devices() {
	{
		flock -s 199
		__zone_get_effect_main_wan_devices "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get all effect devices(netifd) by one zone or interface
zone_get_effect_devices() {
	{
		flock -s 199
		__zone_get_effect_devices "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get the device by one interface
zone_get_device_byif() {
	{
		flock -s 199
		__zone_get_device_byif "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get the interface by one device(tmp,just for ipsec)
zone_get_iface_bydev() {
	{
		flock -s 199
		__zone_get_iface_bydev "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get the zone by one interface.
zone_get_zone_byif() {
	{
		flock -s 199
		__zone_get_zone_byif "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get the iface state by one device.state:UP,DOWN
zone_get_iface_state() {
	{
		flock -s 199
		__zone_get_iface_state "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get VPN interface list
zone_get_vpn_ifaces() {
	{
		flock -s 199
		__zone_get_vpn_ifaces "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get VPN device list
zone_get_vpn_devices() {
	{
		flock -s 199
		__zone_get_vpn_devices "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get NORMAL interface list
zone_get_normal_ifaces() {
	{
		flock -s 199
		__zone_get_normal_ifaces "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get NORMAL device list
zone_get_normal_devices() {
	{
		flock -s 199
		__zone_get_normal_devices "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

zone_check_if_effect()
{
	{
		flock -s 199
		__zone_check_if_effect "$@"
		return $?
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

zone_check_dev_effect()
{
	{
		flock -s 199
		__zone_check_dev_effect "$@"
		return $?
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get ethernet device by one interface
zone_get_eth_device() {
	{
		flock -s 199
		__zone_get_eth_device "$@"
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get the zone by one interface.
zone_get_zone_by_device() {
	{
		flock -s 199
		__zone_get_zone_by_device "$@"
		return $?
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#check VPN interface
zone_check_vpn_interface() {
	{
		flock -s 199
		__zone_check_vpn_interface "$@"
		return $?
		flock -u 199
	} 199<>${ZONE_FILE_LOCK}
}

#Get VPN interface by device name
#zone_get_vpn_
zone_test() {
    local zonelist=$(zone_get_zonelist)
    echo "zonelist=$zonelist"
    
    local ifaces=$(zone_get_ifaces "NORMAL")
    echo "ifaces=$ifaces"
    
    local effect_ifaces=$(zone_get_effect_ifaces "pppoe1")
    echo "effect_ifaces=$effect_ifaces"
    
    local devices=$(zone_get_devices "NORMAL")
    echo "devices=$devices"
    
    local effect_devices=$(zone_get_effect_devices "pppoe1")
    echo "effect_devices=$effect_devices"
    
    local device=$(zone_get_device_byif "pppoe1")
    echo "device=$device"
    
    local iface=$(zone_get_iface_bydev "pppoe-pppoe1")
    echo "iface=$iface"
    
    local zone=$(zone_get_zone_byif "wan1_poe")
    echo "zone=$zone"
    
    local state=$(zone_get_iface_state "pppoe1")
    echo "state=$state"
    
    local vpn_ifaces=$(zone_get_vpn_ifaces)
    echo "vpn_ifaces=$vpn_ifaces"
    
    local vpn_devices=$(zone_get_vpn_devices)
    echo "vpn_devices=$vpn_devices"
	
	local normal_ifaces=$(zone_get_normal_ifaces)
    echo "normal_ifaces=$normal_ifaces"
    
    local normal_devices=$(zone_get_normal_devices)
    echo "normal_devices=$normal_devices"
}
