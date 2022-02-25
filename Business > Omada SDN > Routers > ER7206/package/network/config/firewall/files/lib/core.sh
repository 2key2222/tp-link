# Copyright (C) 2009-2010 OpenWrt.org

FW_LIBDIR=${FW_LIBDIR:-/lib/firewall}

. $FW_LIBDIR/fw.sh
include /lib/network

fw_start() {
	fw_init

	FW_DEFAULTS_APPLIED=

	if fw_is_loaded; then
		echo "firewall already loaded" >&2
		exit 1
	fi

	uci_set_state firewall core "" firewall_state
	fw_clear DROP

	fw_config_once fw_build_defaults defaults
	fw_build_zones
	fw_build_zones_v6

	fw_load_vpn
	fw_load_manage_vlan
	fw_load_manage_devs
	fw_load_sfe
	fw_load_service_default
	fw_load_forwarding_mark

	uci_set_state firewall core loaded 1
	
	echo 1 > /proc/sys/net/ipv4/conf/all/forwarding
}

fw_stop() {
	echo 0 > /proc/sys/net/ipv4/conf/all/forwarding

	fw_init
	fw_clear ACCEPT
	uci_revert_state firewall
	config_clear

	unset FW_INITIALIZED
}

fw_restart() {
	fw_stop
	fw_start
	env -i RESTART=on /sbin/hotplug-call firewall
}

fw_reload() {
	fw_restart
}

fw_is_loaded() {
	local bool=$(uci_get_state firewall.core.loaded)
	return $((! ${bool:-0}))
}

fw_log() {
	local level="$1"
	[ -n "$2" ] && shift || level=notice
	[ "$level" != error ] || echo "Error: $@" >&2
	logger -t firewall -p user.$level "$@"
}


fw_init() {
	[ -z "$FW_INITIALIZED" ] || return 0

	. $FW_LIBDIR/config.sh

	mkdir -p /tmp/.firewall

	fw_config_append firewall

	local file
	for file in $FW_LIBDIR/core_*.sh; do
		. $file
	done
	FW_INITIALIZED=1
	return 0
}
