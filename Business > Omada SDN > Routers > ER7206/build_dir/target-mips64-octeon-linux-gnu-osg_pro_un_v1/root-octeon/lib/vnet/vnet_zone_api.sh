#!/bin/sh

. /lib/functions.sh
. /lib/net_share.sh

multilan_on && vnet_on && {
	. /lib/vnet/vnet.sh
	ZONE_FILE_LOCK=/tmp/zone.file.lock

	zone_get_zonelist()
	{
		echo $(. /lib/zone/zone_api_all.sh; zone_get_zonelist)
	}

	zone_get_user_zonelist()
	{
		echo $(. /lib/zone/zone_api_all.sh; zone_get_zonelist | sed -e 's/LAN$//g' -e 's/LAN \+//g')
	}

	__zone_api_return_()
	{
		echo ${2:-$3}
	}
	
	zone_get_wan_ifaces()
	{
		local ret=$(. /lib/zone/zone_api_all.sh; zone_get_wan_ifaces $1)
		{
			flock -s 199
			__zone_api_return_ "$1" "$ret" "$(vnet_get_iface_byzone $1)"
			flock -u 199
		} 199<>${ZONE_FILE_LOCK}
	}

	zone_get_device_byif()
	{
		local ret=$(. /lib/zone/zone_api_all.sh; zone_get_device_byif $1)
		{
			flock -s 199
			__zone_api_return_ "$1" "$ret" "$(vnet_get_device_byiface $1)"
			flock -u 199
		} 199<>${ZONE_FILE_LOCK}
	}

	zone_get_eth_device()
	{
		local ret=$(. /lib/zone/zone_api_all.sh; zone_get_eth_device $1)
		{
			flock -s 199
			__zone_api_return_ "$1" "$ret" "$(vnet_get_device_byiface $1)"
			flock -u 199
		} 199<>${ZONE_FILE_LOCK}
	}

	zone_get_effect_ifaces()
	{
		local ret=$(. /lib/zone/zone_api_all.sh; zone_get_effect_ifaces $1)
		{
			flock -s 199
			__zone_api_return_ "$1" "$ret" "$(vnet_get_iface_byzone $1)"
			flock -u 199
		} 199<>${ZONE_FILE_LOCK}
	}

	zone_get_effect_devices()
	{
		local ret=$(. /lib/zone/zone_api_all.sh; zone_get_effect_devices $1)
		{
			flock -s 199
			__zone_api_return_ "$1" "$ret" "$(vnet_get_device_byiface $1)"
			flock -u 199
		} 199<>${ZONE_FILE_LOCK}
	}

	zone_get_wan_devices()
	{
		local ret=$(. /lib/zone/zone_api_all.sh; zone_get_wan_devices $1)
		{
			flock -s 199
			__zone_api_return_ "$1" "$ret" "$(vnet_get_device_byiface $1)"
			flock -u 199
		} 199<>${ZONE_FILE_LOCK}
	}

	zone_get_iface_bydev()
	{
		local ret=$(. /lib/zone/zone_api_all.sh; zone_get_iface_bydev $1)
		{
			flock -s 199
			__zone_api_return_ "$1" "$ret" "$(vnet_get_iface_bydevice $1)"
			flock -u 199
		} 199<>${ZONE_FILE_LOCK}
	}

	zone_get_zone_byif()
	{
		local ret=$(. /lib/zone/zone_api_all.sh; zone_get_zone_byif $1)
		{
			flock -s 199
			__zone_api_return_ "$1" "$ret" "$(vnet_get_zone_byiface $1)"
			flock -u 199
		} 199<>${ZONE_FILE_LOCK}
	}
}
