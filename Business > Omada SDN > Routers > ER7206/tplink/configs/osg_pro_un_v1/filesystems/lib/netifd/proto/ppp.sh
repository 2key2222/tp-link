#!/bin/sh

[ -x /usr/sbin/pppd ] || exit 0

[ -n "$INCLUDE_ONLY" ] || {
	. /lib/functions.sh
	. ../netifd-proto.sh
	init_proto "$@"
}

ppp_generic_init_config() {
	proto_config_add_string username
	proto_config_add_string password
	proto_config_add_string keepalive
	proto_config_add_int demand
	proto_config_add_string pppd_options
	proto_config_add_string 'connect:file'
	proto_config_add_string 'disconnect:file'
	proto_config_add_boolean ipv6
	proto_config_add_boolean authfail
	proto_config_add_int mru
	proto_config_add_string pppname
}

ppp_generic_get_zone() {
	local config="$1"
	config_load network
	config_get parent "$config" parent
	. /lib/zone/zone_api.sh
	local zonex=`zone_get_zone_byif $parent`
	[ -z "$zonex" ] && zonex=`zone_get_zone_byif $config`
	[ -z "$zonex" ] && {
		zonex="$(echo $parent | grep "wan[1-4]" | sed -e 's/.*\(wan[1-4]\).*/\1/g' | tr '[a-z]' '[A-Z]')"
	}
	[ -z "$zonex" ] && {
		zonex="$(echo $config | grep "wan[1-4]" | sed -e 's/.*\(wan[1-4]\).*/\1/g' | tr '[a-z]' '[A-Z]')"
	}
	echo "$zonex"
}

ppp_generic_setup() {
	local config="$1"; shift

	json_get_vars ipv6 demand keepalive username password pppd_options pppname
	if [ "$ipv6" = 0 ]; then
		ipv6=""
	else
		ipv6=1
	fi
	if [ "${demand:-0}" -gt 0 ]; then
		demand="precompiled-active-filter /etc/ppp/filter demand idle $demand"
	else
		demand="persist"
	fi
	[ "${keepalive:-0}" -lt 1 ] && keepalive=""
	[ -n "$mru" ] || json_get_var mru mru
	. /lib/pppox/pppox-wheader.sh
	[ -n "$pppname" ] || {
		if [ "${proto}" = "pppoe" ]; then
			pppname="${pppoe_header}$config";
		elif [ "${proto}" = "l2tp" ]; then
			pppname="${l2tp_header}$config";
		elif [ "${proto}" = "pptp" ]; then
			pppname="${pptp_header}$config";
		else
			pppname="${proto:-ppp}-$config";
		fi;
	}

	local v6up=/lib/netifd/pppv6-up
	local v6down=/lib/netifd/ppp-down
	if [ "${proto}" == "pppoe" ]; then
		local lcpechointerval=`uci get network.${config}.lcpechointerval 2>/dev/null`
		local lcpechofailure=`uci get network.${config}.lcpechofailure 2>/dev/null`
		lcpechofailure=${lcpechofailure:-5}
		lcpechointerval=${lcpechointerval:-2}
		[ "$keepalive" = "" ] && keepalive=${lcpechofailure},${lcpechointerval}
		poelogfile=/dev/null
		# ipv4 & ipv6 share the same ppp session,
		# save the ipv6 variables for interface <wan_ipv6>
		[ -n "$ipv6" ] && v6up=/lib/netifd/pppv6-share
	fi

	local interval="${keepalive##*[, ]}"
	[ "$interval" != "$keepalive" ] || interval=5
	[ -n "$connect" ] || json_get_var connect connect
	[ -n "$disconnect" ] || json_get_var disconnect disconnect

	local zonex="$(ppp_generic_get_zone $config)"

	local redail="$(uci get network.${config}.redail)"
	local localip="$(uci get network.${config}.ipaddr)"
	local remoteip="$(uci get network.${config}.gateway)"
	local netmask="$(uci get network.${config}.netmask)"
	local local_remote_ip="${localip}:${remoteip}"
	[ ":" == "${local_remote_ip}" ] && {
		local_remote_ip=""
		netmask=""
	}

	[ -e /usr/sbin/all_ifs ] && /usr/sbin/all_ifs > /tmp/.all_ifs_output

	proto_run_command "$config" /usr/sbin/pppd \
		nodetach ipparam "$config" \
		ifname "$pppname" \
		${poelogfile:+logfile /dev/null} \
		file /etc/ppp/options.default \
		${keepalive:+lcp-echo-interval $interval lcp-echo-failure ${keepalive%%[, ]*}} \
		${ipv6:++ipv6} \
		nodefaultroute \
		usepeerdns \
		${local_remote_ip} \
		${netmask:+netmask ${netmask}} \
		${redail:+redail-interval $redail} \
		$demand maxfail 3 \
		${username:+user "$username" password "$password"} \
		${connect:+connect "$connect"} \
		${disconnect:+disconnect "$disconnect"} \
		ip-up-script /lib/netifd/ppp-up \
		${v6up:+ipv6-up-script ${v6up}} \
		ip-down-script /lib/netifd/ppp-down \
		${v6down:+ipv6-down-script ${v6down}} \
		${mru:+mtu $mru mru $mru} \
		${zonex:+zonex $zonex} \
		ipcheck \
		"$@" $pppd_options
}

ppp_generic_teardown() {
	local interface="$1"

	case "$ERROR" in
		11|19)
			proto_notify_error "$interface" AUTH_FAILED
			json_get_var authfail authfail
			if [ "${authfail:-0}" -gt 0 ]; then
				proto_block_restart "$interface"
			fi
		;;
		2)
			proto_notify_error "$interface" INVALID_OPTIONS
			proto_block_restart "$interface"
		;;
	esac
	proto_kill_command "$interface"
}

# PPP on serial device

proto_ppp_init_config() {
	proto_config_add_string "device"
	ppp_generic_init_config
	no_device=1
	available=1
}

proto_ppp_setup() {
	local config="$1"

	json_get_var device device
	ppp_generic_setup "$config" "$device"
}

proto_ppp_teardown() {
	ppp_generic_teardown "$@"
}

proto_pppoe_init_config() {
	ppp_generic_init_config
	proto_config_add_string "ac"
	proto_config_add_string "service"
}

proto_pppoe_setup() {
	local config="$1"
	local iface="$2"
	local ipsetting=""

	for module in slhc ppp_generic pppox pppoe; do
		/sbin/insmod $module 2>&- >&-
	done

	json_get_var mru mru
	mru="${mru:-1492}"

	json_get_var ac ac
	json_get_var service service
	ipaddr=$(uci get network.$config.ipaddr)
	gateway=$(uci get network.$config.gateway)
	ipsetting=${ipaddr}${gateway}

	link_type=$(uci get network.$config.t_linktype)

	local zonex="$(ppp_generic_get_zone $config)"
	case "$link_type" in
		"auto")
			logger_reg 82 14202 "$zonex"
			;;
		"manual")
			logger_reg 82 14201 "$zonex"
			;;
		"time")
			logger_reg 82 14203 "$zonex"
			;;
	esac
	ppp_generic_setup "$config" \
		plugin rp-pppoe.so \
		${ac:+rp_pppoe_ac "$ac"} \
		${service:+rp_pppoe_service "$service"} \
		${ipsetting:+"${ipaddr}:${gateway}"} \
		tunnel-proto pppoe \
		"nic-$iface"
}

proto_pppoe_teardown() {
	local config="$1"
	link_type=$(uci get network.$config.t_linktype)

	local zonex="$(ppp_generic_get_zone $config)"
	case "$link_type" in
		"auto")
			;;
		"manual")
			logger_reg 82 14205 "$zonex"
			;;
		"time")
			logger_reg 82 14204 "$zonex"
			;;
	esac
	ppp_generic_teardown "$@"
}

proto_pppoa_init_config() {
	ppp_generic_init_config
	proto_config_add_int "atmdev"
	proto_config_add_int "vci"
	proto_config_add_int "vpi"
	proto_config_add_string "encaps"
	no_device=1
	available=1
}

proto_pppoa_setup() {
	local config="$1"
	local iface="$2"

	for module in slhc ppp_generic pppox pppoatm; do
		/sbin/insmod $module 2>&- >&-
	done

	json_get_vars atmdev vci vpi encaps

	case "$encaps" in
		1|vc) encaps="vc-encaps" ;;
		*) encaps="llc-encaps" ;;
	esac

	ppp_generic_setup "$config" \
		plugin pppoatm.so \
		${atmdev:+$atmdev.}${vpi:-8}.${vci:-35} \
		${encaps}
}

proto_pppoa_teardown() {
	ppp_generic_teardown "$@"
}

proto_pptp_init_config() {
	ppp_generic_init_config
	proto_config_add_string "server"
	#available=1
	#no_device=1
}

proto_dnslookup()
{
	local host_ip=""

	network_get_dnsserver dns_servers "$1"

	for dns_s in $dns_servers
	do
		host_ip=$(dnslookup "$2" "$dns_s")
		[ -n "$host_ip" ] && break
	done
	[ -z "$host_ip" ] && host_ip=$(resolveip -t 15 "$2")
	echo "$host_ip"
}

# optfile
# name
# value
install_opt()
{
	sed -i "/^$2/{h;\$bl;d};p;\$bl;d;:l;g;/^$2/{s|^$2 .*|$2 $3|;q};s|.*|$2 $3|" $1
}



proto_pptp_setup() {
	local config="$1"
	local iface="$2"

	local work_path="/tmp/pptp/wan-client/${config}"
	local conf_path="${work_path}/config"
	local opt_file="${work_path}/options.pptp"

	local ip serv_addr server parent

	config_load network
	config_get parent "$config" parent

	. /lib/zone/zone_api.sh
	local ifname="$iface"
	[ -z "$ifname" ] && ifname=`zone_get_device_byif $parent`
	local zonex="$(ppp_generic_get_zone $config)"

	json_get_var server server && {
		for ip in $(proto_dnslookup "$parent" "$server"); do
			( proto_add_host_dependency "$config" "$ip" "$parent" )
			serv_addr=1
		done
	}
	[ -n "$serv_addr" ] || {
		echo "Could not resolve server address"
		sleep 5
		proto_setup_failed "$config"
		exit 1
	}

	local load
	for module in slhc ppp_generic ppp_async ppp_mppe ip_gre gre pptp; do
		grep -q "^$module " /proc/modules && continue
		/sbin/insmod $module 2>&- >&-
		load=1
	done
	[ "$load" = "1" ] && sleep 1

	# install work path
	[ -d "$conf_path" ] || mkdir -p "$conf_path"
	cp /etc/ppp/options.pptp "${opt_file}"
	install_opt "${opt_file}" "path" "${work_path}" 
	install_opt "${opt_file}" "outif" "${ifname}"
	[ -z "$zonex" ] || install_opt "${opt_file}" "zonex" "${zonex}"

	ppp_generic_setup "$config" \
		plugin pptp.so \
		pptp_server $server \
		file ${opt_file} \
		tunnel-proto pptp
}

proto_pptp_teardown() {
	ppp_generic_teardown "$@"

	# remove work path
	rm -rf "/tmp/pptp/wan-client/$1"
}

[ -n "$INCLUDE_ONLY" ] || {
	add_protocol ppp
	[ -f /usr/lib/pppd/*/rp-pppoe.so ] && add_protocol pppoe
	[ -f /usr/lib/pppd/*/pppoatm.so ] && add_protocol pppoa
	[ -f /usr/lib/pppd/*/pptp.so ] && add_protocol pptp
}

