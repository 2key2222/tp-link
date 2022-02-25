#!/bin/sh

. /lib/functions/network.sh
. /lib/zone/zone_api.sh
include /lib/network

OPENVPN_SECRETS=/var/etc/openvpn-psw-file
PUBLIC_DNS_SERVER="8.8.8.8"
LIST_SEP="
"

get_network() {
	local ipaddr="$1"
	local netmask="$2"

	echo "$ipaddr-$netmask" | awk -F '[.-]' '{ ip = lshift($1, 24) + lshift($2, 16) + lshift($3, 8) + $4; \
		mask = lshift($5, 24) + lshift($6, 16) + lshift($7, 8) + $8; \
		net = and(ip, mask); \
		printf("%d.%d.%d.%d", and(rshift(net, 24), 0x00FF), and(rshift(net, 16), 0x00FF), and(rshift(net, 8), 0x00FF), and(net, 0x00FF)); \
	}'
}

append_param() {
	local s="$1"
	local v="$2"
	case "$v" in
		*_*_*_*) v=${v%%_*}-${v#*_}; v=${v%%_*}-${v#*_}; v=${v%%_*}-${v#*_} ;;
		*_*_*)   v=${v%%_*}-${v#*_}; v=${v%%_*}-${v#*_} ;;
		*_*)     v=${v%%_*}-${v#*_} ;;
	esac
	echo -n "$v" >> "/var/etc/openvpn-$s.conf"
	return 0
}

append_bools() {
	local p; local v; local s="$1"; shift
	for p in $*; do
		config_get_bool v "$s" "$p"
		[ "$v" = 1 ] && append_param "$s" "$p" && echo >> "/var/etc/openvpn-$s.conf"
	done
}

append_params() {
	local p; local v; local s="$1"; shift
	for p in $*; do
		config_get v "$s" "$p"
		IFS="$LIST_SEP"
		if [ "$p" == "server" ]; then
		    local ipaddr=${v%% *}
		    local mask=${v##* }
		    local network="$(get_network $ipaddr $mask)"
		    echo "$p $network $mask" >> "/var/etc/openvpn-$s.conf"
		elif [ "$p" == "management" ]; then
			local mgmthost=`echo ${v##*\ }`
			echo "$p 127.0.0.1 ${mgmthost}" >> "/var/etc/openvpn-$s.conf"
		else
		    #for v in $v; do
			    [ -n "$v" ] && append_param "$s" "$p" && echo " $v" >> "/var/etc/openvpn-$s.conf"
		    #done
		fi
		unset IFS
	done
}

append_access() {
	local s="$1"
	local access=
	local server=
	local local_network=
	local ipaddr=
	local netmask=
	local network=
	local lanip=


	# default gateway
	# case client doesn't have gateway route
	#echo "push \"route 0.0.0.0 0.0.0.0\"" >> "/var/etc/openvpn-$s.conf"
	# redirect gateway route
	#echo "push \"redirect-gateway def1\"" >> "/var/etc/openvpn-$s.conf"

	config_get local_network "$s" "local_network" "0.0.0.0/0"
	if [ "$local_network" != "0.0.0.0/0" ]; then
		for local in ${local_network} 
		do
			if [ -z "$lanip" ]; then
				lanip=`echo ${local%/*}`
			fi
			network=$(ipcalc -n ${local})
			network=`echo $network |cut -d "=" -f 2`
			netmask=$(ipcalc -m ${local})
			netmask=`echo $netmask |cut -d "=" -f 2`
			echo "push \"route $network $netmask\"" >> "/var/etc/openvpn-$s.conf"  
		done
	fi
	
	config_get server "$s" "server" "0.0.0.0"
	if [ "$server" != "0.0.0.0" ]; then
		ipaddr=${server%% *}
		netmask=${server##* }
		network="$(get_network $ipaddr $netmask)"
		echo "push \"route $network $netmask\"" >> "/var/etc/openvpn-$s.conf"  
		
		#push dns
		#serverip=$(echo $network | awk -F"." '{print $1 "." $2 "." $3 ".1"}')
		echo "push \"dhcp-option DNS $lanip\"" >> "/var/etc/openvpn-$s.conf"
		echo "push \"dhcp-option DNS $PUBLIC_DNS_SERVER\"" >> "/var/etc/openvpn-$s.conf"
	fi
	
	config_get wan "$s" "wan" "all"
	if [ "$wan" != "all" ]; then
		 local effect_iface=$(zone_get_effect_main_wan_ifaces ${wan})
		 network_get_ipaddr local ${effect_iface}
		 if [ -n "$local" ]; then
			echo "local $local" >> "/var/etc/openvpn-$s.conf"
		 fi
	fi
		
}

section_enabled() {
	config_get_bool enable  "$1" 'enable'  0
	config_get_bool enabled "$1" 'enabled' 0
	[ $enable -gt 0 ] || [ $enabled -gt 0 ]
}

setup_login() {
	local section="$1"

	config_get username "$section" username
	config_get password "$section" password
	[ -n "$username" ] || return 0
	[ -n "$password" ] || return 0

	echo "$username $password" >> $OPENVPN_SECRETS
}

#client-to-client
#duplicate-cn
#persist-key
#persist-tun
#ca /etc/openvpn/ca.crt
#cert /etc/openvpn/server.crt
#cipher AES-128-CBC
#comp-lzo yes
#dev tun
#dh /etc/openvpn/dh1024.pem
#ifconfig-pool-persist /tmp/ipp.txt
#keepalive 10 120
#key /etc/openvpn/server.key
#management localhost 7505
#max-clients 10
#port 1194
#proto udp
#server 10.8.0.0 255.255.255.0
#status /tmp/openvpn-status.log 5
#status-version 2
#verb 3
#push "route 192.168.0.0 255.255.255.0"
#push "route 10.8.0.0 255.255.255.0"
#push "dhcp-option DNS 10.8.0.1"
#push "dhcp-option DNS 8.8.8.8"

start_instance() {
	local s="$1"

	section_enabled "$s" || return 1

	[ ! -d "/var/run" ] && mkdir -p "/var/run"
	[ ! -d "/var/etc" ] && mkdir -p "/var/etc"
	[ -f "/var/etc/openvpn-$s.conf" ] && rm "/var/etc/openvpn-$s.conf"

	# append flags
	append_bools "$s" \
		auth_nocache auth_retry auth_user_pass_optional bind ccd_exclusive client client_cert_not_required \
		client_to_client comp_noadapt disable \
		disable_occ down_pre duplicate_cn fast_io float http_proxy_retry \
		ifconfig_noexec ifconfig_nowarn ifconfig_pool_linear management_forget_disconnect management_hold \
		management_query_passwords management_signal mktun mlock mtu_test multihome mute_replay_warnings \
		nobind no_iv no_name_remapping no_replay opt_verify passtos persist_key persist_local_ip \
		persist_remote_ip persist_tun ping_timer_rem pull push_reset \
		remote_random rmtun route_noexec route_nopull single_session socks_proxy_retry \
		suppress_timestamps tcp_nodelay test_crypto tls_client tls_exit tls_server \
		tun_ipv6 up_delay up_restart username_as_common_name

	# append params
	append_params "$s" \
		cd askpass auth auth_user_pass auth_user_pass_verify bcast_buffers ca cert \
		chroot cipher client_config_dir client_connect client_disconnect comp_lzo connect_freq \
		connect_retry connect_timeout connect_retry_max crl_verify dev dev_node dev_type dh \
		echo engine explicit_exit_notify fragment group hand_window hash_size \
		http_proxy http_proxy_option http_proxy_timeout ifconfig ifconfig_pool \
		ifconfig_pool_persist ifconfig_push inactive ipchange iroute keepalive \
		key key_method keysize learn_address link_mtu lladdr local log log_append \
		lport management management_log_cache max_clients \
		max_routes_per_client mode mssfix mtu_disc mute nice ns_cert_type ping \
		ping_exit ping_restart pkcs12 plugin port port_share prng proto rcvbuf \
		redirect_gateway remap_usr1 remote remote_cert_eku remote_cert_ku remote_cert_tls \
		reneg_bytes reneg_pkts reneg_sec \
		replay_persist replay_window resolv_retry route route_delay route_gateway \
		route_metric route_up rport script_security secret server server_bridge setenv shaper sndbuf \
		socks_proxy status status_version syslog tcp_queue_limit tls_auth \
		tls_cipher tls_remote tls_timeout tls_verify tmp_dir topology tran_window \
		tun_mtu tun_mtu_extra txqueuelen user verb down push up

	# handle client access type
	append_access "$s"

	SERVICE_PID_FILE="/var/run/openvpn-$s.pid"
	
	service_start /usr/sbin/openvpn --log "/tmp/openvpn_$s.txt" \
	--writepid "$SERVICE_PID_FILE" \
	--config "/var/etc/openvpn-$s.conf" \
	--script-security 2 \
	--up "/lib/openvpn/openvpn-server-up.sh" \
	--down "/lib/openvpn/openvpn-server-down.sh" 
}


start_client_instance() {
	local s="$1"
	#section_enabled "$s" || return 1
	echo "start_client_instance,$s" > /dev/console
	
	config_get remote_server "$s" "remote_server" "0.0.0.0"
	config_get port "$s" "port"
	config_get proto "$s" "proto"
	config_get wan "$s" "wan"
	
	sed -i '/remote /d' "/etc/openvpn/client_$s.ovpn"
	sed -i "1a\remote $remote_server $port" "/etc/openvpn/client_$s.ovpn"
	
	local effect_iface=$(zone_get_effect_main_wan_ifaces ${wan})
	network_get_ipaddr local ${effect_iface}
	if [ -n "$local" ]; then
		sed -i '/nobind/d' "/etc/openvpn/client_$s.ovpn"
		sed -i '/local/d' "/etc/openvpn/client_$s.ovpn"
		sed -i "2a\local $local" "/etc/openvpn/client_$s.ovpn"
	else
		sed -i '/nobind/d' "/etc/openvpn/client_$s.ovpn"
		sed -i '/local/d' "/etc/openvpn/client_$s.ovpn"
		sed -i "2a\nobind" "/etc/openvpn/client_$s.ovpn"
	fi
	
	SERVICE_PID_FILE="/var/run/openvpn-$s.pid"
	service_start /usr/sbin/openvpn --log "/tmp/openvpn_$s.txt" \
	--writepid "$SERVICE_PID_FILE" \
	--config "/etc/openvpn/client_$s.ovpn" \
	--script-security 2 \
	--up "/lib/openvpn/openvpn-client-up.sh" \
	--down "/lib/openvpn/openvpn-client-down.sh" 
}

stop_instance() {
	local s="$1"
	
	echo "stop_instance,$s" > /dev/console
	SERVICE_PID_FILE="/var/run/openvpn-$s.pid"
	service_stop /usr/sbin/openvpn
}

client_instance_update_ifconfig() {
	local s="$1"
	local exists
	local effect_iface
	local client_pid
	local cnt
	
	echo "reload_ovpn_instance,$s" > /dev/console
	config_get exists "$s" 'TYPE'
	if [ "$exists" == "client" ]; then
		
		config_get remote_server "$s" "remote_server" "0.0.0.0"
		config_get port "$s" "port"
		config_get wan "$s" "wan"
		
		sed -i '/remote /d' "/etc/openvpn/client_$s.ovpn"
		sed -i "1a\remote $remote_server $port" "/etc/openvpn/client_$s.ovpn"
		
		effect_iface=$(zone_get_effect_main_wan_ifaces ${wan})
		network_get_ipaddr local ${effect_iface}
		if [ -n "$local" ]; then
			sed -i '/nobind/d' "/etc/openvpn/client_$s.ovpn"
			sed -i '/local/d' "/etc/openvpn/client_$s.ovpn"
			sed -i "2a\local $local" "/etc/openvpn/client_$s.ovpn"
		else
			sed -i '/nobind/d' "/etc/openvpn/client_$s.ovpn"
			sed -i '/local/d' "/etc/openvpn/client_$s.ovpn"
			sed -i "2a\nobind" "/etc/openvpn/client_$s.ovpn"
		fi
		
		client_pid=$(cat /var/run/openvpn-$s.pid)
		#echo "pid:$client_pid"  > /dev/console
		cnt=`ps | awk '{ print $1 }' | grep -e "^${client_pid}$"`
		#echo "cnt:$cnt"  > /dev/console
		if [ $cnt -gt 0 ] ; then
			echo "kill -s SIGHUP $client_pid"  > /dev/console
			kill -s SIGHUP $client_pid
		else
			#echo "start_client_instance "$s""  > /dev/console
			start_client_instance "$s"
		fi
	else
		config_get wan "$s" "wan"
		effect_iface=$(zone_get_effect_main_wan_ifaces ${wan})
		network_get_ipaddr local ${effect_iface}
		if [ -n "$local" ]; then
			sed -i '/local/d' "/var/etc/openvpn-$s.conf"
			sed -i "1a\local $local" "/var/etc/openvpn-$s.conf"
		else
			sed -i '/local/d' "/var/etc/openvpn-$s.conf"
		fi
		
		client_pid=$(cat /var/run/openvpn-$s.pid)
		# echo "pid:$client_pid"  > /dev/console
		cnt=`ps | awk '{ print $1 }' | grep -e "^${client_pid}$"`
		# echo "cnt:$cnt"  > /dev/console
		if [ $cnt -gt 0 ] ; then
			echo "kill -s SIGHUP $client_pid"  > /dev/console
			kill -s SIGHUP $client_pid
		else
			# echo "start_instance "$s""  > /dev/console
			start_instance "$s"
		fi

	fi
}


reload_instance() {
	local s="$1"

	section_enabled "$s" || return 1

	SERVICE_PID_FILE="/var/run/openvpn-$s.pid"
	service_reload /usr/sbin/openvpn
}
