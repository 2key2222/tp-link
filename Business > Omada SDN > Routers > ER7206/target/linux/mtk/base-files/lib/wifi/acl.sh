#!/bin/sh

acl_reset()
{
	local iface=$1

	iwpriv $iface set ACLClearAll=1 > /dev/null 2>&1
	iwpriv $iface set AccessPolicy=2 > /dev/null 2>&1
}

kick_wlan_device()
{
	local iface=$1
	local mac=$2

	iwpriv $iface set DisConnectSta="$mac" > /dev/null 2>&1
}

append_to_acl()
{
	local iface=$1
	local mac=$2

	iwpriv $iface set ACLAddEntry="$mac" > /dev/null 2>&1
	iwpriv $iface set DisConnectSta="$mac" > /dev/null 2>&1
}

delete_from_acl()
{
	local iface=$1
	local mac=$2

	iwpriv $iface set ACLDelEntry="$mac" > /dev/null 2>&1
}

