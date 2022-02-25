#!/bin/sh

. /lib/net_share.sh

[ -x /usr/sbin/dhcp6c ] || exit 0

dhcp6cdir="/tmp/dhcp6c"
conffile="$dhcp6cdir/dhcp6c.conf"
dhcp6cpid="$dhcp6cdir/dhcp6c.pid"

[ -n "$INCLUDE_ONLY" ] || {
	. /lib/functions.sh
	. ../netifd-proto.sh
	init_proto "$@"
}

proto_dhcp6c_init_config() {
	proto_config_add_string "dns"
	proto_config_add_string "ip_mode"
	proto_config_add_string "ip_config"
	proto_config_add_string "ifname"
	proto_config_add_string "dns_mode"
	proto_config_add_string "lanif"
}

proto_dhcp6c_create_conffile(){
	local ip_mode="$1"
	local dns_mode="$2"
	local ifname="$3"
	local lanif="$4"
	local ip_config="$5"
	#local id=`date +%s`

	#id=`expr $id % 1000000`

	#local id2=`expr $id + 1`
	
	local id=1
	local id2=$id

	rm -rf ${dhcp6cdir}
	mkdir -p ${dhcp6cdir}


	[ "$ip_mode" == "prefix" ] && {
		echo "interface $ifname {" > "${conffile}"

		[ "$ip_config" == "dhcpv6" ] && echo -e "\tsend ia-na $id;" >> "${conffile}"
		echo -e "\tsend ia-pd $id2;" >> "${conffile}"

		[ "$dns_mode" == "dynamic" ] && echo -e "\trequest domain-name-servers;" >> "${conffile}"
		echo -e "\tscript \"/lib/netifd/dhcp6c.script\";" >> "${conffile}"

		echo -e "};\n" >>  "${conffile}"

		echo -e "id-assoc na $id {};\n" >> "${conffile}"

		echo "id-assoc pd $id2 {" >> "${conffile}"
		echo -e "\tprefix-interface $lanif {" >> "${conffile}"
		echo -e "\t\tsla-id 1;" >> "${conffile}"
		echo -e "\t};" >>  "${conffile}"
		echo "};" >>  "${conffile}"
	}

	[ "$ip_mode" == "non_temp" ] && {
		echo "interface $ifname {" > "${conffile}"
		[ "$ip_config" == "dhcpv6" ] && echo -e "\tsend ia-na $id;" >> "${conffile}"

		[ "$dns_mode" == "dynamic" ] && echo -e "\trequest domain-name-servers;" >> "${conffile}"
		echo -e "\tscript \"/lib/netifd/dhcp6c.script\";" >> "${conffile}"

		echo "};" >>  "${conffile}"

		echo "id-assoc na $id {};" >> "${conffile}"
	}
}

proto_dhcp6c_create_config() {
	local config="$1"
	local ip_mode="$2"
	local dns_mode="$3"
	local ifname="$4"
	local lanif="$5"
	local ip_config="$6"

	uci_set dhcp6c $config enabled '0'
	uci_set dhcp6c $config interface $ifname
	if [ "$ip_config" == "dhcpv6" ]; then
		uci_set dhcp6c $config enabled '1'
		uci_set dhcp6c $config na '1'
	else
		uci_set dhcp6c $config na '0'
	fi
	if [ "$ip_mode" == "prefix" ]; then
		uci_set dhcp6c $config enabled '1'
		uci_set dhcp6c $config pd '1'
		uci_set dhcp6c lan lanif $lanif
		uci_set dhcp6c lan sla_id '1'
		uci_set dhcp6c lan enabled '1'
		$(multilan_on) && uci_set dhcp6c lan enabled '0'
	else
		uci_set dhcp6c $config pd '0'
	fi
	if [ "$dns_mode" == "dynamic" ]; then
		uci_set dhcp6c $config enabled '1'
		uci_set dhcp6c $config domain_name_servers '1'
	else
		uci_set dhcp6c $config domain_name_servers '0'
	fi
	uci_set dhcp6c $config script "/lib/netifd/dhcp6c.script"

	uci_commit dhcp6c
}

wait_for_mbit() {
	local ifname="$1"
	local mbit=0

	# wait for RS.
	defcnt=$(cat /proc/sys/net/ipv6/conf/$ifname/router_solicitations)
	echo 1024 > /proc/sys/net/ipv6/conf/$ifname/router_solicitations
	echo 1 > /proc/sys/net/ipv6/conf/$ifname/disable_ipv6
	echo 0 > /proc/sys/net/ipv6/conf/$ifname/disable_ipv6
	sleep 1
	mbit=`cat /proc/sys/net/ipv6/conf/$ifname/ndisc_mbit`
	while [ "$mbit" == "-1" ];
	do
		sleep 1
		mbit=`cat /proc/sys/net/ipv6/conf/$ifname/ndisc_mbit`
	done
	echo $defcnt > /proc/sys/net/ipv6/conf/$ifname/router_solicitations
	# end of RS.
}

proto_dhcp6c_setup() {
	local config="$1"
	local ifname="$2"
	local mbit=0

	json_get_vars dns_mode ip_mode lanif ip_config

	echo 2 > /proc/sys/net/ipv6/conf/$ifname/accept_ra

	if [ "$ip_config" == "auto" -o "$ip_config" == "slaac" ]; then
		wait_for_mbit $ifname
	fi

	if [ "$ip_config" == "auto" ]; then
		mbit=`cat /proc/sys/net/ipv6/conf/$ifname/ndisc_mbit`
		if [ $mbit -eq 1 ]; then
			ip_config="dhcpv6"
		elif [ $mbit -eq 0 ]; then
			ip_config="slaac"
		else
			sleep 3
			return
		fi
	else
		echo 1 > /proc/sys/net/ipv6/conf/$ifname/disable_ipv6
		echo 0 > /proc/sys/net/ipv6/conf/$ifname/disable_ipv6
	fi
	
	# [ "$ip_config" == "slaac" ] && {

	# }

	#proto_dhcp6c_create_conffile "$ip_mode" \
	#	"$dns_mode" "$ifname" "$lanif" "$ip_config"

	#proto_run_command "$config" /usr/sbin/dhcp6c -f \
	#	-p "$dhcp6cpid" \
	#	-c "$conffile" \
	#	-t "$config" \
	#	"$ifname"

	proto_dhcp6c_create_config "$config" "$ip_mode" \
		"$dns_mode" "$ifname" "$lanif" "$ip_config"	
	if [ "$(uci_get dhcp6c $config enabled)" == "1" ]; then
		/etc/init.d/dhcp6c start $config "/tmp/dhcp6c/proto_dhcp6c_cmd.$config"
		proto_run_command "$config" $(cat /tmp/dhcp6c/proto_dhcp6c_cmd.$config)
	else
		# sync exec for dhcp6c callback script.
		ifname="$ifname" interface="$config" new_dhcpc_state="3" \
		/lib/netifd/dhcp6c.script
	fi
}

proto_dhcp6c_teardown() {
	local interface="$1"
	local ifname="$2"

        rm /tmp/dhcp6c/prefix.info
        rm /tmp/dhcp6c/prefix.info.${interface}
        rm /tmp/dhcp6c/prefixlen.info.${interface}

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

	[ -n "$ifname" ] && {
		echo "1" > /proc/sys/net/ipv6/conf/$ifname/accept_ra
		ip -6 route del ::/0 dev "$ifname"
	}

	#proto_kill_command  "$interface" 15
	#sleep 1
	#rm -rf ${dhcp6cdir}

	echo 3 > /proc/sys/net/ipv6/conf/$ifname/router_solicitations

	if [ "$(uci_get dhcp6c $interface enabled)" == "1" ]; then
		local sigterm="$(kill -l SIGTERM)"
		[ -n "$sigterm" ] && proto_kill_command "$interface" $sigterm
		/etc/init.d/dhcp6c stop $interface "/tmp/dhcp6c/proto_dhcp6c_cmd.$interface"
	fi
	uci_set dhcp6c $interface enabled '0'         
	uci_commit dhcp6c
}

[ -n "$INCLUDE_ONLY" ] || {
	add_protocol dhcp6c
}
