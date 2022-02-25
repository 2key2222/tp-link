#!/bin/sh
# wrapper functions for vnet api.
. /lib/functions.sh

# locks sequence: 
# a: IFLOCK -> HPLOCK -> LOCK
# b: LOCK
VNET_LOCK=/tmp/.vnet.lock
# FD_LOCK=60
VNET_IFLOCK=/tmp/.vnet.interface.lock
# FD_IFLOCK=70
VNET_HPLOCK=/tmp/.vnet.hotplug.lock
# FD_HPLOCK=80

VNET_LIBDIR=/lib/vnet

. $VNET_LIBDIR/vnet_core.sh

decho() {
	echo "$@" > /dev/null
}

# command exec in vnet namespace.
###IN###
# see parameters of vnetc_exec_in_vnet
vnet_exec_in_vnet()
{
	decho "$vnet_exec_in_vnet $*"
	vnetc_exec_in_vnet "$@"
}

vnet_exec_in_dnet()
{
	decho "$vnet_exec_in_dnet $*"
	vnetc_exec_in_dnet "$@"
}

vnet_search_byip()
{
	local ip=$1; shift

	if $(vnet_exec_in_dnet ifconfig -a 2>/dev/null | grep -Eq "$ip( |\$)"); then
		echo -n "dnet"
	elif $(vnet_exec_in_vnet ifconfig -a 2>/dev/null | grep -Eq "$ip( |\$)"); then
		echo -n "vnet"
	fi
}

vnet_search_bydev()
{
	local dev=$1; shift

	if $(vnet_exec_in_dnet ifconfig $dev 2>/dev/null | grep -Eq "^$dev"); then
		echo -n "dnet"
	elif $(vnet_exec_in_vnet ifconfig $dev 2>/dev/null | grep -Eq "^$dev"); then
		echo -n "vnet"
	fi
}

vnet_search_bypid()
{
	local pid=$1; shift

	if [ "$(ip netns identify $pid 2>/dev/null)" == "vnet" ];
	then
		echo -n "vnet"
	elif [ "$(ip netns identify $pid 2>/dev/null)" == "dnet" ];
	then
		echo -n "dnet"
	fi
}

vnet_exec_byip()
{
	local ip=$1; shift

	if $(vnet_exec_in_dnet ifconfig -a 2>/dev/null | grep -Eq "$ip( |\$)"); then
		vnet_exec_in_dnet "$@"
	else
		vnet_exec_in_vnet "$@"
	fi
}

vnet_exec_bydev()
{
	local dev=$1; shift

	if $(vnet_exec_in_dnet ifconfig $dev 2>/dev/null | grep -Eq "^$dev"); then
		vnet_exec_in_dnet "$@"
	else
		vnet_exec_in_vnet "$@"
	fi
}

vnet_exec_bypid()
{
	local pid=$1; shift

	if [ "$(ip netns identify $pid 2>/dev/null)" == "vnet" ];
	then
		vnet_exec_in_vnet "$@"
	else
		vnet_exec_in_dnet "$@"
	fi
}
# interfaces moved to vnet namespace.
###IN###
# see parameters of vnetc_bind_to_vnet
vnet_bind_to_vnet()
{
	decho "vnet_bind_to_vnet $*"
	vnetc_bind_to_vnet "$@"
}

vnet_bind_to_dnet()
{
	decho "vnet_bind_to_dnet $*"
	vnetc_bind_to_dnet "$@"
}
# read network parameters/status of interface.
###IN###
# 1: interface
###OUT###
# network parameters/status
vnet_network_is_running()
{
	local ifname=$(uci_get_state vnetwork vinterface "${1}_ifname")
	local ipaddr=$(uci_get_state vnetwork vinterface "${1}_ipaddr")

	[ -z "$ifname" -o -z "$ipaddr" ] && return 1
	vnetc_dev_running "${ifname}"
}
vnet_network_get_ipaddr()
{
	echo -n $(uci_get_state vnetwork vinterface "${1}_ipaddr")
}
vnet_network_get_netmask()
{
	echo -n $(uci_get_state vnetwork vinterface "${1}_netmask")
}
vnet_network_get_ifname()
{
	echo -n $(uci_get_state vnetwork vinterface "${1}_ifname")
}

# add firewall & nat rules for vnet network.
###IN###
# 1: interface
# 2: see parameters of vnetc_set_internet
# 3: ...
vnet_set_internet()
{
	local interface

	decho "vnet_set_internet $*"

	interface="$1"; shift
	{
		flock -x 60
		vnet_network_is_running "${interface}" && {
			vnetc_set_internet "$@"
		}
		flock -u 60
	} 60<>${VNET_LOCK}
}

# del firewall & nat rules for vnet network.
###IN###
# 1: interface
# 2: see parameters of vnetc_unset_internet
# 3: ...
vnet_unset_internet()
{
	local interface

	decho "vnet_unset_internet $*"

	interface="$1"; shift
	{
		flock -x 60
		vnetc_unset_internet "$@"
		flock -u 60
	} 60<>${VNET_LOCK}
}

# add upstream route for vnet interface.
###IN###
# see parameters of vnetc_set_upstream_routes
vnet_add_upstream_routes()
{
	decho "vnet_add_upstream_routes $*"
	{
		flock -x 60
		vnetc_set_upstream_routes "$@"
		flock -u 60
	} 60<>${VNET_LOCK}
}
vnet_add_upstream_routes_v6()
{
	decho "vnet_add_upstream_routes_v6 $*"
	{
		flock -x 60
		vnetc_set_upstream_routes_v6 "$@"
		flock -u 60
	} 60<>${VNET_LOCK}
}

# del upstream route for vnet interface.
###IN###
# see parameters of vnetc_unset_upstream_routes
vnet_del_upstream_routes()
{
	decho "vnet_del_upstream_routes $*"
	{
		flock -x 60
		vnetc_unset_upstream_routes "$@"
		flock -u 60
	} 60<>${VNET_LOCK}
}
vnet_del_upstream_routes_v6()
{
	decho "vnet_del_upstream_routes_v6 $*"
	{
		flock -x 60
		vnetc_unset_upstream_routes_v6 "$@"
		flock -u 60
	} 60<>${VNET_LOCK}
}

# add downstream route for vnet interface.
###IN###
# see parameters of vnetc_set_downstream_routes
vnet_add_downstream_routes()
{
	local interface

	decho "vnet_add_downstream_routes $*"

	interface="$1"; shift
	{
		flock -x 60
		vnet_network_is_running "${interface}" && {
			vnetc_set_downstream_routes "$@"
		}
		flock -u 60
	} 60<>${VNET_LOCK}
}
vnet_add_downstream_routes_v6()
{
	local interface

	decho "vnet_add_downstream_routes_v6 $*"

	interface="$1"; shift
	{
		flock -x 60
		vnet_network_is_running "${interface}" && {
			vnetc_set_downstream_routes_v6 "$@"
		}
		flock -u 60
	} 60<>${VNET_LOCK}
}

# del downstream route for vnet interface.
###IN###
# see parameters of vnetc_unset_downstream_routes
vnet_del_downstream_routes()
{
	local interface

	decho "vnet_del_downstream_routes $*"

	interface="$1"; shift
	{
		flock -x 60
		vnet_network_is_running "${interface}" && {
			vnetc_unset_downstream_routes "$@"
		}
		flock -u 60
	} 60<>${VNET_LOCK}
}
vnet_del_downstream_routes_v6()
{
	local interface

	decho "vnet_del_downstream_routes_v6 $*"

	interface="$1"; shift
	{
		flock -x 60
		vnet_network_is_running "${interface}" && {
			vnetc_unset_downstream_routes_v6 "$@"
		}
		flock -u 60
	} 60<>${VNET_LOCK}
}

# service request redirected from <vnet> to <init net>
###IN###
# see parameters of vnetc_set_service_redirect
vnet_set_service_redirect()
{
	decho "vnet_set_service_redirect $*"
	{
		flock -x 60
		vnetc_set_service_redirect "$@"
		flock -u 60
	} 60<>${VNET_LOCK}
}
vnet_unset_service_redirect()
{
	decho "vnet_unset_service_redirect $*"
	{
		flock -x 60
		vnetc_unset_service_redirect "$@"
		flock -u 60
	} 60<>${VNET_LOCK}
}

# call hotplug event.
###IN###
# 1: ifname, netdevice of interface.
# 2: interface
# 3: action
vnet_call_hotplug()
{
	decho "vnet_call_hotplug $*"

	{
		flock -x 80
		vnetc_call_hotplug "$@"
		flock -u 80
	} 80<>${VNET_HPLOCK}
}

vnet_call_vvlan_hotplug()
{
	decho "vnet_call_vvlan_hotplug $*"

	{
		flock -x 80
		vnetc_call_vvlan_hotplug "$@"
		flock -u 80
	} 80<>${VNET_HPLOCK}
}

vnet_add_vlan_vvlan()
{
	local vvlan

	decho "vnet_add_vlan_vvlan $*"

	vvlan="$1"; shift
	{
		flock -x 70
		vnet_call_vvlan_hotplug "${vvlan}" "add"
		flock -u 70
	} 70<>${VNET_IFLOCK}
}

vnet_del_vlan_vvlan()
{
	local vvlan

	decho "vnet_del_vlan_vvlan $*"

	vvlan="$1"; shift
	{
		flock -x 70
		vnet_call_vvlan_hotplug "${vvlan}" "delete"
		flock -u 70
	} 70<>${VNET_IFLOCK}
}

vnet_notify_vlan_vvlan()
{
	local vvlan
	local properties

	decho "vnet_notify_vlan_vvlan $*"

	vvlan="$1"; shift
	properties="$1"; shift
	{
		flock -x 70
		vnet_call_vvlan_hotplug "${vvlan}" "notify" "$properties"
		flock -u 70
	} 70<>${VNET_IFLOCK}
}
# add vlan interface for vnet.
###IN###
# 1: interface
# 2: see parameters of vnetc_add_vlan_interface
# 3: ...
vnet_add_vlan_interface()
{
	local interface

	decho "vnet_add_vlan_interface $*"

	interface="$1"; shift
	{
		flock -x 70

		vnetc_add_vlan_interface "$@"
		uci_set_state vnetwork vinterface "${interface}_ifname" "$VIFNAME"
		uci_set_state vnetwork vinterface "${interface}_ipaddr" "$VIPADDR"
		uci_set_state vnetwork vinterface "${interface}_netmask" "$VNETMASK"
		vnet_call_hotplug "$VIFNAME" "$interface" "add"

		flock -u 70
	} 70<>${VNET_IFLOCK}
}

vnet_add_interface_addr_v6()
{
	local interface

	decho "vnet_add_interface_addr_v6 $*"

	interface="$1"; shift
	{
		flock -x 70

		vnetc_add_interface_addr_v6 "$@"
		uci_set_state vnetwork vinterface "${interface}_ifname" "$VIFNAME"
		uci_set_state vnetwork vinterface "${interface}_ipv6_addr" "$VIPADDR6"
		uci_set_state vnetwork vinterface "${interface}_ipv6_prefixlen" "$VPREFIXLEN6"
		# vnet_call_hotplug "$VIFNAME" "$interface" "add"

		flock -u 70
	} 70<>${VNET_IFLOCK}
}

# update vlan interface for vnet.
###IN###
# 1: interface
# 2: see parameters of vnetc_upd_vlan_interface
# 3: ...
vnet_upd_vlan_interface()
{
	local interface
	local oifname

	decho "vnet_upd_vlan_interface $*"

	interface="$1"; shift
	{
		flock -x 70

		oifname=$(uci_get_state vnetwork vinterface "${interface}_ifname")
		vnet_call_hotplug "$oifname" "$interface" "delete"

		vnetc_upd_vlan_interface "$@"
		uci_set_state vnetwork vinterface "${interface}_ifname" "$VIFNAME"
		uci_set_state vnetwork vinterface "${interface}_ipaddr" "$VIPADDR"
		uci_set_state vnetwork vinterface "${interface}_netmask" "$VNETMASK"
		uci_set_state vnetwork vinterface "${interface}_ipv6_addr" "$VIPADDR6"
		uci_set_state vnetwork vinterface "${interface}_ipv6_prefixlen" "$VPREFIXLEN6"

		vnet_call_hotplug "$VIFNAME" "$interface" "add"

		flock -u 70
	} 70<>${VNET_IFLOCK}
}

# notify vlan interface for vnet.
###IN###
# 1: interface
# 2: see parameters of vnetc_upd_vlan_interface
# 3: ...
vnet_notify_vlan_interface()
{
	local interface
	local ifname
	local properties

	decho "vnet_ntf_vlan_interface $*"

	interface="$1"; shift
	properties="$1"; shift
	{
		flock -x 70

		ifname=$(uci_get_state vnetwork vinterface "${interface}_ifname")
		vnet_call_hotplug "$ifname" "$interface" "notify" "$properties"

		flock -u 70
	} 70<>${VNET_IFLOCK}
}

# del vlan interface for vnet.
###IN###
# 1: interface
# 2: see parameters of vnetc_del_vlan_interface
# 3: ...
vnet_del_vlan_interface()
{
	local interface
	local oifname

	decho "vnet_del_vlan_interface $*"

	interface="$1"; shift
	{
		flock -x 70

		oifname=$(uci_get_state vnetwork vinterface "${interface}_ifname")
		vnet_call_hotplug "$oifname" "$interface" "delete"

		uci_revert_state vnetwork vinterface "${interface}_ifname"
		uci_revert_state vnetwork vinterface "${interface}_ipaddr"
		uci_revert_state vnetwork vinterface "${interface}_netmask"
		vnetc_del_vlan_interface "$@"

		flock -u 70
	} 70<>${VNET_IFLOCK}
}

vnet_del_interface_addr_v6()
{
	local interface
	local oifname

	decho "vnet_del_interface_addr_v6 $*"

	interface="$1"; shift
	{
		flock -x 70

		oifname=$(uci_get_state vnetwork vinterface "${interface}_ifname")
		# vnet_call_hotplug "$oifname" "$interface" "delete"

		uci_revert_state vnetwork vinterface "${interface}_ipv6_addr"
		uci_revert_state vnetwork vinterface "${interface}_ipv6_prefixlen"
		vnetc_del_interface_addr_v6 "$@"

		flock -u 70
	} 70<>${VNET_IFLOCK}
}

# set ip/mask for vwan interface.
###IN###
# 1: interface
# 2: see parameters of vnetc_set_vwan_interface
# 3: ...
vnet_set_vwan_interface()
{
	local interface

	decho "vnet_set_vwan_interface $*"

	interface="$1"; shift
	{
		flock -x 70

		vnetc_set_vwan_interface "$@"
		uci_set_state vnetwork vinterface "${interface}_ifname" "$VIFNAME"
		uci_set_state vnetwork vinterface "${interface}_ipaddr" "$VIPADDR"
		uci_set_state vnetwork vinterface "${interface}_netmask" "$VNETMASK"
		vnet_call_hotplug "$VIFNAME" "$interface" "add"

		flock -u 70
	} 70<>${VNET_IFLOCK}
}
vnet_set_vwan_interface_v6()
{
	local interface

	decho "vnet_set_vwan_interface_v6 $*"

	interface="$1"; shift
	{
		flock -x 70

		vnetc_set_vwan_interface_v6 "$@"
		uci_set_state vnetwork vinterface "${interface}_ifname" "$VIFNAME"
		uci_set_state vnetwork vinterface "${interface}_ipv6_addr" "$VIPADDR6"
		uci_set_state vnetwork vinterface "${interface}_ipv6_prefixlen" "$VPREFIXLEN6"
		# vnet_call_hotplug "$VIFNAME" "$interface" "add"

		flock -u 70
	} 70<>${VNET_IFLOCK}
}

# unset ip/mask for vwan interface.
###IN###
# 1: interface
# 2: see parameters of vnetc_unset_vwan_interface
# 3: ...
vnet_unset_vwan_interface()
{
	local interface

	decho "vnet_unset_vwan_interface $*"

	interface="$1"; shift
	{
		flock -x 70

		oifname=$(uci_get_state vnetwork vinterface "${interface}_ifname")
		vnet_call_hotplug "$oifname" "$interface" "delete"

		uci_revert_state vnetwork vinterface "${interface}_ifname"
		uci_revert_state vnetwork vinterface "${interface}_ipaddr"
		uci_revert_state vnetwork vinterface "${interface}_netmask"
		vnetc_unset_vwan_interface "$@"

		flock -u 70
	} 70<>${VNET_IFLOCK}
}
vnet_unset_vwan_interface_v6()
{
	local interface

	decho "vnet_unset_vwan_interface_v6 $*"

	interface="$1"; shift
	{
		flock -x 70

		oifname=$(uci_get_state vnetwork vinterface "${interface}_ifname")
		# vnet_call_hotplug "$oifname" "$interface" "delete"

		uci_revert_state vnetwork vinterface "${interface}_ipv6_addr"
		uci_revert_state vnetwork vinterface "${interface}_ipv6_prefixlen"
		vnetc_unset_vwan_interface_v6 "$@"

		flock -u 70
	} 70<>${VNET_IFLOCK}
}

# create vnet namespace
###IN###
vnet_create_vnet()
{
	decho "vnetc_create $*"
	vnetc_create
}

# destroy vnet namespace
###IN###
vnet_destroy_vnet()
{
	decho "vnetc_destroy $*"
	vnetc_destroy
}

# ZONE
vnet_get_iface_byzone()
{
	local iface=""
	local zone="$1"

	fetch_iface()
	{
		[ "$1" != "vwan" ] && {
			config_get zonex "$1" "zonex" ""
			[ "$zonex" == "$zone" ] && iface=$1
		}
	}	

	config_load vnetwork
	config_foreach fetch_iface vinterface "$zone"

	echo -n "$iface"
}

vnet_get_zone_byiface()
{
	[ "$1" != "vwan" ] && {
		uci -q get vnetwork."$1".zone
	}
}

vnet_get_device_byiface()
{
	[ "$1" != "vwan" ] && {
		uci -q get vnetwork."$1".ifname
	}
}

vnet_get_iface_bydevice()
{
	local iface=""
	local device="$1"

	fetch_iface()
	{
		[ "$1" != "vwan" ] && {
			config_get ifname "$1" "ifname" ""
			[ "$ifname" == "$device" ] && iface=$1
		}
	}	

	config_load vnetwork
	config_foreach fetch_iface vinterface "$device"

	echo -n "$iface"
}

vnet_get_zone_list()
{
	local zones=""

	fetch_iface()
	{
		[ "$1" != "vwan" ] && {
			zones="$zones $(vnet_get_zone_byiface $1)"
		}
	}	

	config_load vnetwork
	config_foreach fetch_iface vinterface

	echo -n "$zones"
}

# global init.
vnet_init()
{
	uci_revert_state vnetwork
	uci_set_state vnetwork vinterface "" vinterface_state
}
