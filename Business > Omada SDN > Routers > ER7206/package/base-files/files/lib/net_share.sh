#!/bin/sh

. /lib/functions.sh

multilan_on()
{
	[ "$(get_version multilan)" == "1" ] && return 0
	return 1
}

vnet_on()
{
	[ -e /lib/vnet/vnet.sh ]
}