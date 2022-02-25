#!/bin/sh

. /lib/zone/zone_api_all.sh

zone_get_user_zonelist()
{
	zone_get_zonelist
}

[ -e /lib/vnet/vnet_zone_api.sh ] && . /lib/vnet/vnet_zone_api.sh
