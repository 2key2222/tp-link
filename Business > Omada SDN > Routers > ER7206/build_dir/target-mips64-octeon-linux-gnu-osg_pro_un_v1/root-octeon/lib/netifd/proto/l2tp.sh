#!/bin/sh

. /lib/pppox/pppox-wheader.sh

[ -x /usr/sbin/xl2tpd ] || exit 0

[ -n "$INCLUDE_ONLY" ] || {
	. /lib/functions.sh
	. ../netifd-proto.sh
	init_proto "$@"
}

proto_l2tp_init_config() {
	proto_config_add_string "username"
	proto_config_add_string "password"
	proto_config_add_string "keepalive"
	proto_config_add_string "pppd_options"
	proto_config_add_boolean "ipv6"
	proto_config_add_int "mru"
	proto_config_add_string "server"
	#available=1
	#no_device=1
}

proto_l2tp_get_zone() {
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

# opt_file
# name
# value
install_opt()
{
	#sed -i "/^$2/{h;\$bl;d};p;\$bl;d;:l;g;/^$2/{s|^$2 .*|$2 $3|;q};s|.*|$2 $3|" $1
	sed -i '/^'"$2"'/d' $1
	echo "$2 $3" >> $1
}

proto_l2tp_setup() {
	local config="$1"
	local iface="$2"

	local work_path="/tmp/l2tp/wan-client/${config}"
	local conf_path="${work_path}/config"
	local optfile="${work_path}/options.l2tp"
	
	local ip serv_addr server parent

	config_load network
	config_get parent "$config" parent

	. /lib/zone/zone_api.sh
	local ifname="$iface"
	[ -z "$ifname" ] && ifname=`zone_get_device_byif $parent`
	local zonex="$(proto_l2tp_get_zone $config)"

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

	if [ ! -p /var/run/xl2tpd/l2tp-control ]; then
		/etc/init.d/xl2tpd start
	fi

	json_get_vars ipv6 demand keepalive username password pppd_options
	[ "$ipv6" = 1 ] || ipv6=""
	if [ "${demand:-0}" -gt 0 ]; then
		demand="precompiled-active-filter /etc/ppp/filter demand idle $demand"
	else
		demand="persist"
	fi

	[ -n "$mru" ] || json_get_var mru mru

	local interval="${keepalive##*[, ]}"
	[ "$interval" != "$keepalive" ] || interval=5

	# install work path
	[ -d "$conf_path" ] || mkdir -p "$conf_path"
	cp /etc/ppp/options.l2tp "${optfile}"
	if [ -n "$username" ]; then
		username=${username//\\/\\\\}
		password=${password//\\/\\\\}
		install_opt "${optfile}" "user" "'${username//\'/\\'}'" 
		install_opt "${optfile}" "password" "'${password//\'/\\'}'"
	fi

	redail_interval="$(uci get network.${config}.redail)"
	if [ -n "$redail_interval" ]; then
		install_opt "${optfile}" "redail-interval" "${redail_interval}"
	fi

	localip="$(uci get network.${config}.ipaddr)"
	remoteip="$(uci get network.${config}.gateway)"
	netmask="$(uci get network.${config}.netmask)"
	if [ -n "$localip" -o -n "$remoteip" ]; then
		install_opt "${optfile}" "${localip}:${remoteip}" ""
		[ -n "$netmask" ] && {
			install_opt "${optfile}" "netmask" "${netmask}"
		}
	fi

	if [ -n "$keepalive" ]; then
		install_opt "${optfile}" "lcp-echo-interval" "${interval}" 
		install_opt "${optfile}" "lcp-echo-failure" "${keepalive%%[, ]*}"
	fi
	install_opt "${optfile}" "ipparam \"$config\""
	{
		install_opt "${optfile}" "ifname" "\"${l2tp_header}${config}\""
	}
	# Don't wait for LCP term responses; exit immediately when killed.
	# echo "lcp-max-terminate 0" >> "${optfile}"
	if [ -n "$ipv6" ]; then
		install_opt "${optfile}" "+ipv6" ""
	fi
	if [ -n "${pppd_options}" ]; then
		install_opt "${optfile}" "${pppd_options}" ""
	fi
	if [ -n "$mru" ]; then
		install_opt "${optfile}" "mtu" "$mru"
		install_opt "${optfile}" "mru" "$mru"
	fi
	install_opt "${optfile}" "path" "${work_path}"

	[ -z "$zonex" ] || install_opt "${optfile}" "zonex" "${zonex}"
	install_opt "${optfile}" "ipcheck"

	[ "x$(pgrep xl2tpd)" == "x" ] && {
		/etc/init.d/l2tp restart
		sleep 1s
	}

	[ -e /usr/sbin/all_ifs ] && /usr/sbin/all_ifs > /tmp/.all_ifs_output

	[ -z "$redail_interval" ] && redail_interval=20
	[ $redail_interval -le 0 ] && redail_interval=1

	xl2tpd-control add l2tp-${config} pppoptfile=${optfile} lns=${server} redial=yes redial timeout=${redail_interval} out if=${ifname}
	xl2tpd-control connect l2tp-${config}
}

proto_l2tp_teardown() {
	local interface="$1"
	local optfile="/tmp/l2tp/options.${interface}"
	local timeout=5

	case "$ERROR" in
		11|19)
			proto_notify_error "$interface" AUTH_FAILED
			proto_block_restart "$interface"
		;;
		2)
			proto_notify_error "$interface" INVALID_OPTIONS
			proto_block_restart "$interface"
		;;
	esac

	[ ! -d /tmp/l2tp/wan-client/${interface} ] && return 0

	xl2tpd-control disconnect l2tp-${interface}
	# Wait for interface to go down
	while [ -d /sys/class/net/${l2tp_header}${interface} ]; do
		sleep 1
		timeout=$((${timeout}-1))
		if [ ${timeout} -le 0 ]; then
			break
		fi
	done

	xl2tpd-control remove l2tp-${interface}
	rm -rf "/tmp/l2tp/wan-client/${interface}"
}

[ -n "$INCLUDE_ONLY" ] || {
	add_protocol l2tp
}
