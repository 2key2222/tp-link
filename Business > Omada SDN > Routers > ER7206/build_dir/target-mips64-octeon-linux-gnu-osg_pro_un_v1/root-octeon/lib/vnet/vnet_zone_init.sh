#!/bin/sh

. /lib/functions.sh
. /lib/config/uci.sh
. /lib/zone/zone_conf.sh

vnet_build_zones_configs()
{
	local interface="$1"; shift
	_build_a_interface_()
	{
		local config="$1"

		[ -n "$interface" -a "$interface" != "$config" ] && return

		local ifname=$(uci get vnetwork.$config.ifname)
		local zone=$(uci get vnetwork.$config.zone)
		
		[ -z "$ifname" -o -z "$zone" ] && return

		uci_add zone zone "$zone"
		uci_set zone "$zone" if_eth "$config"
		uci_set zone "$zone" dev_eth "$ifname"
		uci_set zone "$zone" creator "vnet"
	}

	config_load vnetwork
	config_foreach _build_a_interface_ vinterface
}

vnet_build_zones()
{
	config_load zone
	vnet_build_zones_configs "$@"
	uci_commit zone
}

vnet_clean_zones_configs()
{
	local interface="$1"; shift

	[ -n "$interface" ] && {
		_clean_a_interface_()
		{
			local config="$1"

			[ -n "$interface" -a "$interface" != "$config" ] && return

			local zone=$(uci get vnetwork.$config.zone)
			[ -z "$zone" ] && return

			uci_remove zone "$zone"
		}
		config_load vnetwork
		config_foreach _clean_a_interface_ vinterface
	}

	[ -z "$interface" ] && {
		_clean_a_zone_()
		{
			local config="$1"
			local creator=$(uci get zone.$config.creator)
			[ "$creator" != "vnet" ] && return
			uci_remove zone "$config"
		}
		config_foreach _clean_a_zone_ zone
	}

}

vnet_clean_zones()
{
	config_load zone
	vnet_clean_zones_configs "$@"
	uci_commit zone
}

vnet_rebuild_zones()
{
	config_load zone
	vnet_clean_zones_configs "$@"
	vnet_build_zones_configs "$@"
	uci_commit zone
}
