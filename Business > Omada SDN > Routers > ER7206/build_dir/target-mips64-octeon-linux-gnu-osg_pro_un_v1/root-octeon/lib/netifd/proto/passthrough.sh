#!/bin/sh
. /usr/share/libubox/jshn.sh
. /lib/net_share.sh

[ -n "$INCLUDE_ONLY" ] || {
	. /lib/functions.sh
	. ../netifd-proto.sh
	init_proto "$@"
}

LOG_MODULE_IPV6=89
LOG_IPV6_PASSTHROUGH_UP=13707

proto_passthrough_init_config() {
	no_device=1
	available=1
}

proto_passthrough_setup() {
	local interface="$1"
	local config="${1/v6/eth}"
	json_init
	json_load "`ubus call network.interface.$config status`"
	json_get_var device device

	if ! multilan_on; then
		insmod ipv6-pass-through wan_eth_name=$device lan_br_name=br-lan
		/etc/init.d/dhcp6s stop
	#	killall dhcp6c
		/etc/init.d/radvd stop

		# device eth.X and br-lan enter promiscuous mode
		ifconfig $device promisc
		ifconfig br-lan promisc
	fi
	# notify netifd
	proto_init_update "$device" 1
	proto_send_update "$interface"

	local log_wan=`echo "${interface%_v6}" | tr '[a-z]' '[A-Z]'`
	logger_reg $LOG_MODULE_IPV6 $LOG_IPV6_PASSTHROUGH_UP "$log_wan"
}

proto_passthrough_teardown() {
	local interface="$1"
	local config="${1/v6/eth}"
	json_init
	json_load "`ubus call network.interface.$config status`"
	json_get_var device device
	
	if ! multilan_on; then
		rmmod  ipv6-pass-through

		# device eth0.X and br-lan left promiscuous mode
		ifconfig $device -promisc
		ifconfig br-lan -promisc
	}
	# notify netifd
	proto_init_update "$device" 0
	proto_send_update "$interface"
}

[ -n "$INCLUDE_ONLY" ] || {
	add_protocol passthrough
}
