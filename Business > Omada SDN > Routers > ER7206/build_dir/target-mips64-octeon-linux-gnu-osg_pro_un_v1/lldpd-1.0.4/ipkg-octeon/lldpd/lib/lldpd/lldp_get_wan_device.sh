#!/bin/sh

. /lib/zone/zone_api.sh

local device=""
local zone=""
zone=$(zone_get_zone_by_device $1)
device=$(zone_get_effect_main_wan_devices $zone)
echo -n "$device"
