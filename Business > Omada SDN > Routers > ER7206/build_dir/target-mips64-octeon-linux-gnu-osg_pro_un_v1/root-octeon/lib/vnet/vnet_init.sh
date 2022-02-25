#!/bin/sh
# startup functions of vnet module.
# read/load configs from uci config file.

. /lib/zone/zone_api.sh                                    
. /lib/functions/network.sh

VNET_LIBDIR=/lib/vnet

. $VNET_LIBDIR/vnet.sh

LOG_CONSOLE="/tmp/log/vnetc_log"

# get real ipv6 address from prefix/prefixlen for vnetwork
get_eui_64_id()
{
	local macaddr="$1"
	local __var="$2"
	
	local oIFS="$IFS"; IFS=":"; set -- $macaddr; IFS="$oIFS"
	
	local tmp="0x$1"
	tmp=`printf %02x $((${tmp}^2))`
	
	local id="$tmp$2:$3ff:fe$4:$5$6"
	eval "export -- \"$__var=$id\""
}

calc_vnet_ipv6_addr()
{
	local vinterface=$1
	local __var="$2"
	local vif_is_lan=$3
	local macaddr ipv6_prefix ipv6_prefixlen ipv6_suffix __ipv6_addr
	local ifacev6
	
	# make sure to get the latest parameters
	ipv6_prefix=$(uci get vnetwork.${vinterface}.ipv6_prefix)
	ipv6_prefixlen=$(uci get vnetwork.${vinterface}.ipv6_prefixlen)
	
	[ -z "$ipv6_prefix" ] && return
	
	[ "$vif_is_lan" == "1" ] && {
		macaddr=$(uci get network.lan.macaddr)
	}
	[ "$vif_is_lan" != "1" ] && {
		macaddr=$(uci get network.wan1_eth.macaddr)
	}
	
	echo "[calc_vnet_ipv6_addr] vif:$1, vif_is_lan:$3, ipv6_prefix:$ipv6_prefix" >> ${LOG_CONSOLE}

	# calculate lan ipv6 address
	get_eui_64_id $macaddr ipv6_suffix
	__ipv6_addr="${ipv6_prefix}${ipv6_suffix}"
	ipv6_prefixlen="${ipv6_prefixlen:-64}"
	
	local oIFS="$IFS"; IFS=":"; set -- $ipv6_prefix; IFS="$oIFS"
	[ "$#" == "5" ] && {
		__ipv6_addr="${ipv6_prefix%:}${ipv6_suffix}"
	}
	[ "$#" == "6" ] && {
		__ipv6_addr="${ipv6_prefix%%1::}${ipv6_suffix}"
	}
	
	# upper case -> lower case
	__ipv6_addr=$(echo ${__ipv6_addr} | tr '[A-Z]' '[a-z]')
	eval "export -- \"$__var=${__ipv6_addr}\""
}

get_vlan_ipv6_addr()
{
	local vinterface=$1

	ipv6_addr=$(cat /tmp/.vnet_${vinterface}_ipv6_addr)

	echo "$ipv6_addr"
}

get_vlan_ipv6_prefixlen()
{
	local vinterface=$1

	ipv6_subnet="$(uci get vnetwork.${vinterface}.ipv6_prefixlen)"
	[ -z "$ipv6_subnet" ] && ipv6_subnet="64"

	echo "$ipv6_subnet"
}

init_vlan_ipv6_addr()
{
	local vinterface=$1
	
	export ipv6_addr=$(uci get vnetwork.${vinterface}.ipv6_addr)

	[ -z "$ipv6_addr" ] && calc_vnet_ipv6_addr ${vinterface} ipv6_addr 1
	if [ -n "$ipv6_addr" ]; then
		echo "$ipv6_addr" > /tmp/.vnet_${vinterface}_ipv6_addr
	else
		rm -rf /tmp/.vnet_${vinterface}_ipv6_addr
	fi
}

init_vwan_ipv6_addr()
{
	local vinterface=$1

	export ipv6_addr=$(uci get vnetwork.${vinterface}.ipv6_addr)
	[ -n "$ipv6_addr" ] && return

	calc_vnet_ipv6_addr ${vinterface} ipv6_addr 0
	[ -n "$ipv6_addr" ] && {
		uci set vnetwork.${vinterface}.ipv6_addr=$ipv6_addr
		uci commit vnetwork
	}
}

init_vwan_ipv6_peer()
{
	export ipv6_peer=$(uci get vnetwork.vwan.ipv6_peer)
	[ -n "$ipv6_peer" ] && return

	calc_vnet_ipv6_addr "vwan" ipv6_peer 1
	[ -n "$ipv6_peer" ] && {
		uci set vnetwork.vwan.ipv6_peer=$ipv6_peer
		uci commit vnetwork
	}
}

# Build/clean interface's firewall & nat rules of wan device.
###IN###
# 1. outdev
# 2: interface name (optional).
build_gateway_fw_nat_rules()
{
	local outdev="$1"; shift
	local interface="$1"; shift

	_build_a_interface_fw_nat_()
	{
		local config="$1"
		local vlanid ipaddr netmask

		[ -n "$interface" -a "$interface" != "$config" ] && return

		config_get vlanid "$config" vlanid ''
		config_get ipaddr "$config" ipaddr ''
		config_get netmask "$config" netmask ''

		[ -z "$vlanid" ] && return

		vnet_set_internet "${config}" "${ipaddr}" "${netmask}" "${outdev}"
	}

	config_load vnetwork
	config_foreach _build_a_interface_fw_nat_ vinterface
}
clean_gateway_fw_nat_rules()
{
	local outdev="$1"; shift
	local interface="$1"; shift

	_clean_a_interface_fw_nat_()
	{
		local config="$1"
		local vlanid ipaddr netmask

		[ -n "$interface" -a "$interface" != "$config" ] && return

		config_get vlanid "$config" vlanid ''
		config_get ipaddr "$config" ipaddr ''
		config_get netmask "$config" netmask ''

		[ -z "$vlanid" ] && return

		vnet_unset_internet "${config}" "${ipaddr}" "${netmask}" "${outdev}"
	}

	config_load vnetwork
	config_foreach _clean_a_interface_fw_nat_ vinterface
}

# Build/clean interface's firewall & nat rules.
###IN###
# 1: interface name (optional)
build_gateway_rules()
{
	local interface="$1"; shift
	network_flush_cache                                                                      
	for zone in $(zone_get_zonelist) ; do                                                 
		local ifaces

		[ "${zone:0:3}" != "WAN" ] && continue

		ifaces=$(zone_get_wan_ifaces $zone)
		for iface in ${ifaces} ; do                                                      
			if network_is_up "${iface}"; then                                                   
				local device=$(zone_get_device_byif $iface)      
				build_gateway_fw_nat_rules "${device}" "${interface}"
			fi
		done                                      
	done
}

clean_gateway_rules()
{
	local interface="$1"; shift
	network_flush_cache                                                                      
	for zone in $(zone_get_zonelist) ; do
		local ifaces

		[ "${zone:0:3}" != "WAN" ] && continue

		ifaces=$(zone_get_wan_ifaces $zone)
		for iface in ${ifaces} ; do
			if network_is_up "${iface}"; then
				local device=$(zone_get_device_byif $iface)
				clean_gateway_fw_nat_rules "${device}" "${interface}"
			fi
		done
	done
}

# Build/clean redirect service rules for <vnet> interfaces.
###IN###
# 1: interface name (optional).
build_redirect_service_rules()
{
	local redirect
	local interface="$1"; shift

	_build_a_interface_service_()
	{
		local config="$1"
		local vlanid ipaddr netmask system

		[ -n "$interface" -a "$interface" != "$config" ] && return

		config_get vlanid "$config" vlanid ''
		config_get ipaddr "$config" ipaddr ''
		config_get netmask "$config" netmask ''
		config_get system "$config" system ''

		[ -z "$vlanid" -o -z "$system" ] && return

		vnet_set_service_redirect "${ipaddr}" "${redirect}" "80,22,443" ""
	}

	config_load vnetwork
	config_get redirect "vwan" ippeer ''
	config_foreach _build_a_interface_service_ vinterface
}
clean_redirect_service_rules()
{
	local redirect
	local interface="$1"; shift

	_clean_a_interface_service_()
	{
		local config="$1"
		local vlanid ipaddr netmask system

		[ -n "$interface" -a "$interface" != "$config" ] && return

		config_get vlanid "$config" vlanid ''
		config_get ipaddr "$config" ipaddr ''
		config_get netmask "$config" netmask ''
		config_get system "$config" system ''

		[ -z "$vlanid" -o -z "$system" ] && return

		vnet_unset_service_redirect "${ipaddr}" "${redirect}" "80,22,443" ""
	}

	config_load vnetwork
	config_get redirect "vwan" ippeer ''
	config_foreach _clean_a_interface_service_ vinterface
}

# Build/clean upstream routes to internet for <vnet> interfaces.
build_upstream_routes_v6()
{
	local ipv6_enable=''
	local ipv6_peer=''
	local ifname=''
	
	init_vwan_ipv6_peer "vwan"
	echo "[build_upstream_routes_v6] init_vwan_ipv6_peer vwan" >> ${LOG_CONSOLE}

	config_load vnetwork
	config_get ipv6_enable "vwan" ipv6_enable ''
	config_get ipv6_peer "vwan" ipv6_peer ''
	config_get ifname "vwan" ifname ''

	vnet_add_upstream_routes_v6 "${ipv6_enable}" "${ipv6_peer}" "${ifname}"
	echo "[build_upstream_routes_v6] vnet_add_upstream_routes_v6 ${ipv6_enable} ${ipv6_peer} ${ifname}" >> ${LOG_CONSOLE}
}
clean_upstream_routes_v6()
{
	local ipv6_enable=''
	local ipv6_peer=''
	local ifname=''

	config_load vnetwork
	config_get ipv6_enable "vwan" ipv6_enable ''
	config_get ipv6_peer "vwan" ipv6_peer ''
	config_get ifname "vwan" ifname ''

	vnet_del_upstream_routes_v6 "${ipv6_enable}" "${ipv6_peer}" "${ifname}"
	echo "[clean_upstream_routes_v6] vnet_del_upstream_routes_v6 ${ipv6_enable} ${ipv6_peer} ${ifname}" >> ${LOG_CONSOLE}
}
build_upstream_routes()
{
	local ippeer=''

	config_load vnetwork
	config_get ippeer "vwan" ippeer ''

	vnet_add_upstream_routes "${ippeer}"
}
clean_upstream_routes()
{
	local ippeer=''

	config_load vnetwork
	config_get ippeer "vwan" ippeer ''

	vnet_del_upstream_routes "${ippeer}"
}


# Build/clean downstream routes in <init net> for <vnet> interfaces.
###IN###
# 1: interface name (optional).
build_downstream_routes_v6()
{
	local gateway6
	local interface="$1"; shift

	_build_a_interface_route_v6_()
	{
		local config="$1"
		local vlanid ipv6_enable ipv6_addr ipv6_prefixlen

		[ -n "$interface" -a "$interface" != "$config" ] && return
		
		config_get vlanid "$config" vlanid ''
		config_get ipv6_enable "$config" ipv6_enable ''
		
		[ -z "$vlanid" ] && return
		[ "$config" == "vwan" -o "$ipv6_enable" != "on" ] && return
		
		init_vlan_ipv6_addr "$config"
		echo "[build_downstream_routes] init_vlan_ipv6_addr $config" >> ${LOG_CONSOLE}
		
		ipv6_addr=$(get_vlan_ipv6_addr $config)
		ipv6_prefixlen=$(get_vlan_ipv6_prefixlen $config)
		[ -z "$ipv6_addr" -o -z "$ipv6_prefixlen" ] && return
		vnet_add_downstream_routes_v6 "${config}" "${ipv6_enable}" "${ipv6_addr}" "${ipv6_prefixlen}" "${gateway6}"
		echo "[build_downstream_routes_v6] vnet_add_downstream_routes_v6 ${config} ${ipv6_enable} ${ipv6_addr} ${ipv6_prefixlen} ${gateway6}" >> ${LOG_CONSOLE}
	}

	config_load vnetwork
	config_get gateway6 "vwan" ipv6_addr ''
	config_foreach _build_a_interface_route_v6_ vinterface
}
clean_downstream_routes_v6()
{
	local gateway6
	local interface="$1"; shift

	_clean_a_interface_route_v6_()
	{
		local config="$1"
		local vlanid ipv6_enable ipv6_addr ipv6_prefixlen

		[ -n "$interface" -a "$interface" != "$config" ] && return

		config_get vlanid "$config" vlanid ''
		config_get ipv6_enable "$config" ipv6_enable ''

		[ -z "$vlanid" ] && return
		[ "$config" == "vwan" ] && return

		echo "[clean_downstream_routes_v6] init_vlan_ipv6_addr $config" >> ${LOG_CONSOLE}

		ipv6_addr=$(get_vlan_ipv6_addr $config)
		ipv6_prefixlen=$(get_vlan_ipv6_prefixlen $config)
		[ -z "$ipv6_addr" -o -z "$ipv6_prefixlen" ] && return
		vnet_del_downstream_routes_v6 "${config}" "${ipv6_enable}" "${ipv6_addr}" "${ipv6_prefixlen}" "${gateway6}"
		echo "[clean_downstream_routes_v6] vnet_del_downstream_routes_v6 ${config} ${ipv6_enable} ${ipv6_addr} ${ipv6_prefixlen} ${gateway6}" >> ${LOG_CONSOLE}
	}

	config_load vnetwork
	config_get gateway6 "vwan" ipv6_addr ''
	config_foreach _clean_a_interface_route_v6_ vinterface
}
build_downstream_routes()
{
	local gateway
	local interface="$1"; shift

	_build_a_interface_route_()
	{
		local config="$1"
		local vlanid ipaddr netmask

		[ -n "$interface" -a "$interface" != "$config" ] && return

		config_get vlanid "$config" vlanid ''
		config_get ipaddr "$config" ipaddr ''
		config_get netmask "$config" netmask ''

		[ -z "$vlanid" ] && return

		vnet_add_downstream_routes "${config}" "${ipaddr}" "${netmask}" "${gateway}"
	}

	config_load vnetwork
	config_get gateway "vwan" ipaddr ''
	config_foreach _build_a_interface_route_ vinterface
	
	# build_downstream_routes_v6 may fail when br-lan is down, do build_downstream_routes_v6 # again when br-lan if-up event happens and calls build_downstream_routes
	build_downstream_routes_v6
}
clean_downstream_routes()
{
	local gateway
	local interface="$1"; shift

	_clean_a_interface_route_()
	{
		local config="$1"
		local vlanid ipaddr netmask

		[ -n "$interface" -a "$interface" != "$config" ] && return

		config_get vlanid "$config" vlanid ''
		config_get ipaddr "$config" ipaddr ''
		config_get netmask "$config" netmask ''

		[ -z "$vlanid" ] && return

		vnet_del_downstream_routes "${config}" "${ipaddr}" "${netmask}" "${gateway}"
	}

	clean_downstream_routes_v6
	
	config_load vnetwork
	config_get gateway "vwan" ipaddr ''
	config_foreach _clean_a_interface_route_ vinterface
}

setup_lan_vvlans()
{
	local vvlan="$1"; shift
	_load_a_vvlan_()
	{
		local config="$1"
		local vlanid

		[ -n "$vvlan" -a "$vvlan" != "$config" ] && return

		config_get vlanid "$config" vlanid ''

		[ -z "$vlanid" ] && return

		vnet_add_vlan_vvlan "${config}"
	}

	config_load vnetwork
	config_foreach _load_a_vvlan_ vvlan
}

clean_lan_vvlans()
{
	local vvlan="$1"; shift
	_load_a_vvlan_()
	{
		local config="$1"
		local vlanid

		[ -n "$vvlan" -a "$vvlan" != "$config" ] && return

		config_get vlanid "$config" vlanid ''

		[ -z "$vlanid" ] && return

		vnet_del_vlan_vvlan "${config}"
	}

	config_load vnetwork
	config_foreach _load_a_vvlan_ vvlan
}
# Load/unload interfaces' config
setup_lan_interfaces_v6()
{
	local interface="$1"; shift
	_load_a_interface_v6_()
	{
		local config="$1"
		local device vlanid macaddr ipv6_enable ipv6_addr ipv6_prefixlen

		[ -n "$interface" -a "$interface" != "$config" ] && return
		
		config_get vlanid "$config" vlanid ''
		config_get ipv6_enable "$config" ipv6_enable ''
		device=$(uci get network.global.lan_device)
		macaddr=$(uci get network.lan.macaddr)
		
		[ -z "$vlanid" ] && return
		[ "$config" == "vwan" -o "$ipv6_enable" != "on" ] && return
		
		init_vlan_ipv6_addr "$config"
		echo "[setup_lan_interfaces_v6] init_vlan_ipv6_addr $config" >> ${LOG_CONSOLE}
		
		ipv6_addr=$(get_vlan_ipv6_addr $config)
		ipv6_prefixlen=$(get_vlan_ipv6_prefixlen $config)
		[ -z "$ipv6_addr" -o -z "$ipv6_prefixlen" ] && return
		vnet_add_interface_addr_v6 "${config}" "${device}" "${vlanid}" "${macaddr}" "${ipv6_enable}" "${ipv6_addr}" "${ipv6_prefixlen}"
		echo "[setup_lan_interfaces_v6] vnet_add_interface_addr_v6 ${config} ${device} ${vlanid} ${macaddr} ${ipv6_enable} ${ipv6_addr} ${ipv6_prefixlen}" >> ${LOG_CONSOLE}
	}

	config_load vnetwork
	config_foreach _load_a_interface_v6_ vinterface
	
	build_downstream_routes_v6 "${interface}"
}
clean_lan_interfaces_v6()
{
	local interface="$1"; shift
	_clean_a_interface_v6_()
	{
		local config="$1"
		local device vlanid macaddr ipv6_enable ipv6_addr ipv6_prefixlen

		[ -n "$interface" -a "$interface" != "$config" ] && return

		config_get vlanid "$config" vlanid ''
		config_get ipv6_enable "$config" ipv6_enable ''
		device=$(uci get network.global.lan_device)
		macaddr=$(uci get network.lan.macaddr)

		[ -z "$vlanid" ] && return
		[ "$config" == "vwan" ] && return

		echo "[clean_lan_interfaces_v6] init_vlan_ipv6_addr $config" >> ${LOG_CONSOLE}

		ipv6_addr=$(get_vlan_ipv6_addr $config)
		ipv6_prefixlen=$(get_vlan_ipv6_prefixlen $config)
		[ -z "$ipv6_addr" -o -z "$ipv6_prefixlen" ] && return
		vnet_del_interface_addr_v6 "${config}" "${device}" "${vlanid}" "${macaddr}" "${ipv6_enable}" "${ipv6_addr}" "${ipv6_prefixlen}"
		echo "[clean_lan_interfaces] vnet_del_interface_addr_v6 ${config} ${device} ${vlanid} ${macaddr} ${ipv6_enable} ${ipv6_addr} ${ipv6_prefixlen}" >> ${LOG_CONSOLE}
	}
	
	clean_downstream_routes_v6 "${interface}"

	config_load vnetwork
	config_foreach _clean_a_interface_v6_ vinterface
}
setup_lan_interfaces()
{
	local interface="$1"; shift
	_load_a_interface_()
	{
		local config="$1"
		local device vlanid ipaddr netmask macaddr

		[ -n "$interface" -a "$interface" != "$config" ] && return

		config_get vlanid "$config" vlanid ''
		config_get ipaddr "$config" ipaddr ''
		config_get netmask "$config" netmask ''
		config_get name "$config" name ""
		device=$(uci get network.global.lan_device)
		macaddr=$(uci get network.lan.macaddr)

		[ -z "$vlanid" ] && return

		vnet_add_vlan_interface "${config}" "${device}" "${vlanid}" "${ipaddr}" "${netmask}" "${macaddr}"
		logger_reg 20 12654 "$name" "$ipaddr" "$netmask"
	}

	config_load vnetwork
	config_foreach _load_a_interface_ vinterface
	setup_lan_interfaces_v6
}
clean_lan_interfaces()
{
	local interface="$1"; shift
	_clean_a_interface_()
	{
		local config="$1"
		local device vlanid ipaddr netmask macaddr

		[ -n "$interface" -a "$interface" != "$config" ] && return

		config_get vlanid "$config" vlanid ''
		config_get ipaddr "$config" ipaddr ''
		config_get netmask "$config" netmask ''
		device=$(uci get network.global.lan_device)
		macaddr=$(uci get network.lan.macaddr)

		[ -z "$vlanid" ] && return

		vnet_del_vlan_interface "${config}" "${device}" "${vlanid}" "${ipaddr}" "${netmask}" "${macaddr}"
	}

	clean_lan_interfaces_v6
	config_load vnetwork
	config_foreach _clean_a_interface_ vinterface
}
# Load/unload vwan interface's config
setup_vwan_interface_v6()
{
	local config="vwan"
	local ifname macaddr ipv6_enable ipv6_addr ipv6_prefixlen
	
	config_load vnetwork
	config_get ifname "$config" ifname ''
	config_get ipv6_enable "$config" ipv6_enable ''
	config_get ipv6_prefixlen "$config" ipv6_prefixlen ''
	macaddr=$(uci get network.wan1_eth.macaddr)
	
	[ "$ipv6_enable" == "on" ] && {
		init_vwan_ipv6_addr "$config"
		echo "[setup_vwan_interface] init_vwan_ipv6_addr $config" >> ${LOG_CONSOLE}
	}
	ipv6_addr=$(uci get vnetwork.${config}.ipv6_addr)

	vnet_set_vwan_interface_v6 "${config}" "${ifname}" "${macaddr}" "${ipv6_enable}" "${ipv6_addr}" "${ipv6_prefixlen}"
	echo "[setup_vwan_interface_v6] vnet_set_vwan_interface_v6 ${config} ${ifname} ${macaddr} ${ipv6_enable} ${ipv6_addr} ${ipv6_prefixlen}" >> ${LOG_CONSOLE}
	build_upstream_routes_v6
}
clean_vwan_interface_v6()
{
	local config="vwan"
	local ifname macaddr ipv6_enable ipv6_addr ipv6_prefixlen

	config_load vnetwork
	config_get ifname "$config" ifname ''
	config_get ipv6_enable "$config" ipv6_enable ''
	config_get ipv6_addr "$config" ipv6_addr ''
	config_get ipv6_prefixlen "$config" ipv6_prefixlen ''

	clean_upstream_routes_v6
	vnet_unset_vwan_interface_v6 "${config}" "${ifname}" "${ipaddr}" "${netmask}" "${ipv6_enable}" "${ipv6_addr}" "${ipv6_prefixlen}"
	echo "[clean_vwan_interface_v6] vnet_unset_vwan_interface_v6 ${config} ${ifname} ${ipv6_enable} ${ipv6_addr} ${ipv6_prefixlen}" >> ${LOG_CONSOLE}
}
setup_vwan_interface()
{
	local config="vwan"
	local ipaddr netmask ifname macaddr

	config_load vnetwork
	config_get ipaddr "$config" ipaddr ''
	config_get netmask "$config" netmask ''
	config_get ifname "$config" ifname ''
	macaddr=$(uci get network.wan1_eth.macaddr)

	# default config for old software.
	config_get ipv6_enable "$config" ipv6_enable ''
	config_get ipv6_prefix "$config" ipv6_prefix ''
	[ -z "$ipv6_enable" -o -z "$ipv6_prefix" ] && {
		uci set vnetwork.${config}.ipv6_enable="on"
		uci set vnetwork.${config}.ipv6_prefix="fe80::"
		uci set vnetwork.${config}.ipv6_prefixlen="64"
		uci commit
	}

	vnet_set_vwan_interface "${config}" "${ifname}" "${ipaddr}" "${netmask}" "${macaddr}"
	build_upstream_routes
	setup_vwan_interface_v6
}
clean_vwan_interface()
{
	local config="vwan"
	local ipaddr netmask ifname macaddr

	config_load vnetwork
	config_get ipaddr "$config" ipaddr ''
	config_get netmask "$config" netmask ''
	config_get ifname "$config" ifname ''

	clean_vwan_interface_v6
	clean_upstream_routes
	vnet_unset_vwan_interface "${config}" "${ifname}" "${ipaddr}" "${netmask}"
}

# Load/clean network config
setup_vnetworks()
{
	export DELAY_COMMIT=y
	setup_vwan_interface
	setup_lan_interfaces
	setup_lan_vvlans
	export -n DELAY_COMMIT
	vnetc_call_hotplug_commit
}
clean_vnetworks()
{
	clean_lan_interfaces
	clean_vwan_interface
	clean_lan_vvlans
}

vnet_start()
{
	export VNET_BOOTING=y
	echo "==== [vnet_start: vnet_init] ====" >> ${LOG_CONSOLE}
	vnet_init
	echo "==== [vnet_start: vnet_create_vnet] ====" >> ${LOG_CONSOLE}
	vnet_create_vnet
	echo "==== [vnet_start: setup_vnetworks] ====" >> ${LOG_CONSOLE}
	setup_vnetworks
	echo "==== [vnet_start: end] ====" >> ${LOG_CONSOLE}
}

vnet_stop()
{
	echo "==== [vnet_stop: clean_vnetworks] ====" >> ${LOG_CONSOLE}
	clean_vnetworks
	echo "==== [vnet_stop: vnet_destroy_vnet] ====" >> ${LOG_CONSOLE}
	vnet_destroy_vnet
	echo "==== [vnet_stop: end] ====" >> ${LOG_CONSOLE}
}

vnet_restart()
{
	export VNET_BOOTING=y
	vnet_stop
	vnet_start
}

vnet_reload()
{
	export VNET_BOOTING=y
	vnet_stop
	vnet_start
}
