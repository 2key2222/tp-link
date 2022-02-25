#!/bin/sh

. /lib/functions.sh
. ../netifd-proto.sh
init_proto "$@"

proto_dhcp_init_config() {
	renew_handler=1

	proto_config_add_string 'ipaddr:ipaddr'
	proto_config_add_string 'hostname:hostname'
	proto_config_add_string clientid
	proto_config_add_string vendorid
	proto_config_add_boolean 'dbroadcast:bool'
	proto_config_add_string 'reqopts:list(string)'
	proto_config_add_string iface6rd
	proto_config_add_string sendopts
	proto_config_add_boolean delegate
	proto_config_add_string zone6rd
	proto_config_add_string zone
}

dhcp_vendorid()
{
	lua -e "print(require 'luci.sys.config'.getsysinfo('HARDVERSION'))"
}

proto_dhcp_setup() {
	local config="$1"
	local iface="$2"

	local ipaddr hostname clientid vendorid dbroadcast reqopts iface6rd sendopts delegate zone6rd zone
	json_get_vars ipaddr hostname clientid vendorid dbroadcast reqopts iface6rd sendopts delegate zone6rd zone

	local opt dhcpopts
	for opt in $reqopts; do
		append dhcpopts "-O $opt"
	done

	for opt in $sendopts; do
		append dhcpopts "-x $opt"
	done

	[ -z "$vendorid" ] && vendorid="$(dhcp_vendorid)"

	[ "$dbroadcast" = 1 ] && dbroadcast="-B" || dbroadcast=
	#[ -n "$clientid" ] && clientid="-x 0x3d:${clientid//:/}" || clientid="-C"
	[ -n "$clientid" ] && clientid="-x 0x3d:${clientid//:/} -C"
	[ -n "$iface6rd" ] && proto_export "IFACE6RD=$iface6rd"
	[ -n "$iface6rd" ] && append dhcpopts "-O 212"
	[ -n "$zone6rd" ] && proto_export "ZONE6RD=$zone6rd"
	[ -n "$zone" ] && proto_export "ZONE=$zone"
	[ "$delegate" = "0" ] && proto_export "IFACE6RD_DELEGATE=0"

	[ -e /usr/sbin/all_ifs ] && /usr/sbin/all_ifs > /tmp/.all_ifs_output

	proto_export "INTERFACE=$config"
	proto_run_command "$config" udhcpc -a\
		-p /var/run/udhcpc-$iface.pid \
		-s /lib/netifd/dhcp.script \
		-f -t 10 -i "$iface" \
		${ipaddr:+-r $ipaddr} \
		${hostname:+-H $hostname} \
		${vendorid:+-V "$vendorid"} \
		$clientid $dbroadcast $dhcpopts
}

proto_dhcp_renew() {
	local interface="$1"
	# SIGUSR1 forces udhcpc to renew its lease
	local sigusr1="$(kill -l SIGUSR1)"
	[ -n "$sigusr1" ] && proto_kill_command "$interface" $sigusr1
}

proto_dhcp_teardown() {
	local interface="$1"
	# SIGUSR2 forces udhcpc to send release packet
	local sigusr2="$(kill -l SIGUSR2)"
	[ -n "$sigusr2" ] && proto_kill_command "$interface" $sigusr2
}

add_protocol dhcp
