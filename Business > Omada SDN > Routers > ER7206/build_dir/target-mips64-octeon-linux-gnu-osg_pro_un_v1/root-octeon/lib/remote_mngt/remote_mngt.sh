# Copyight(c) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     remtoe_mngt.sh
# bief     The Api for remote_mngt
# author   Gui Yongshi
# vesion   1.0.0
# history  1.0.0, 3Nov15, GuiYongshi, Ceate the file

# this is the managable inteface

. /lib/zone/zone_api.sh

SERVER_PORTS=
REJECT_PORTS=
IPSET_USED=0


export RM_CHAIN="remote_mngt_chain"
export accept_ip="rsa_rule"

get_service_port()   #$service
{
	local port http_list https_list ssh_list
	case "$1" in
	http|HTTP|Http)
		port="$(uci get uhttpd.main.listen_http |cut -d : -f 5)"
		;;
	https|HTTPS|Https)
		port="$(uci get uhttpd.main.listen_https |cut -d : -f 5)"
		;;
	ssh|SSH|Ssh) 
		port="$(uci get dropbear.@dropbear[0].Port)"
		;;
	*) 
		port=$(uci get remote_mngt.port.$1)
		;;
	esac

	echo "$port"
}


rmc_add_iface_cmd() # <chain> <interface> <ports> <vlan>
{
	fw_check()
	{
		local ret=$(iptables -w -t $1 -C $2 $3 2>&1)
		[ -n "$ret" ] && return 0||  return 1
	}

	if [[ -n "$4" ]]; then
		local ret
		fw_check "filter" "$1" "-i $2 -m vlan --vid $4 -p tcp -m multiport --dport $3 -j ACCEPT"
		[ x$? == x0 ] && ret=$(iptables -w -I $1 1 -i $2 -m vlan --vid "$4" -p tcp -m multiport --dport "$3" -j ACCEPT 2>&1)
		fw_check "filter" "$1" "-i $2 -m vlan ! --vid $4 -p tcp -m multiport --dport $3 -j DROP"
		[ x$? == x0 ] && ret=$(iptables -w -I $1 1 -i $2 -m vlan ! --vid "$4" -p tcp -m multiport --dport "$3" -j DROP 2>&1)
		[ -z "$ret" ] && return 0||return 1
	fi

	fw_check "filter" "$1" "-i $2 -p tcp -m multiport --dport $3 -j ACCEPT"
	[ x$? == x0 ] || return 0
	local ret=$(iptables -w -I $1 1 -i $2 -p tcp -m multiport --dport "$3" -j ACCEPT 2>&1)
	[ -z "$ret" ] && return 0||return 1
}

rmc_add_reject_iface_cmd() # <chain> <interface> <ports>
{
	fw_check()
	{
		local ret=$(iptables -w -t $1 -C $2 $3 2>&1)
		[ -n "$ret" ] && return 0||  return 1
	}

	fw_check "filter" "$1" "-i $2 -p tcp -m multiport --dport $3 -j reject"
	[ x$? == x0 ] || return 0
	local ret=$(iptables -w -A $1 -i $2 -p tcp -m multiport --dport "$3" -j reject 2>&1)
	[ -z "$ret" ] && return 0||return 1
}

rmc_add_mngt_iface_list()
{
	local iface state mvlan dev

	config_get state "$1" enabled
	config_get iface "$1" iface
	config_get mvlan "$1" mvlan

	dev=$(zone_get_device_byif "$iface")
	[ -z "$dev" ] && return 1

	if [[ "$state" == "on" ]]; then
		rmc_add_iface_cmd $RM_CHAIN $dev "$SERVER_PORTS" "$mvlan"
	elif [[ "$state" == "off" ]]; then
		rmc_add_reject_iface_cmd $RM_CHAIN $dev "$SERVER_PORTS" 
	fi
	return 0
}

# reject from LAN networks.
rmc_add_rej_rule_list()
{
	local ret
	local count=0
	local ipset_used=0
	local lan_accept_ip_set="lan_remote_mngt_accept_ip_set"
	ret=$(ipset destroy "$lan_accept_ip_set")
	ret=$(ipset create "$lan_accept_ip_set" hash:net -exist 2>&1)

	_ipset_add_ip()
	{
		local ipaddr state
		config_get state "$1" enabled
		config_get ipaddr "$1" ipaddr

		if [[ "$state" == "on" && -n "$ipaddr" ]]; then
			if [[ "$ipaddr" == "0.0.0.0/0" ]]; then
				ipset_used=1
				return 0
			fi
			#rmc_add_rsa_cmd "$remote_mngt_accept_set" "$ipaddr"
			ipset add "$lan_accept_ip_set" "$ipaddr"
			count=$(($count+1))
		fi
	}

	[ "$(uci get remote_mngt.@reject[0].enabled)" != "on" ] && return 0

	config_foreach _ipset_add_ip lan_rsa_rule	

	if [[ "$ipset_used" -eq 0 ]]; then
		if [[ "$count" -gt 0 ]]; then
			iptables -w -I "$RM_CHAIN" 1 -m set ! --match-set "$lan_accept_ip_set" src -p tcp -m multiport --dport "$REJECT_PORTS" -j reject
		fi
	fi

	return 0
}

# accept from WAN internet.
rmc_add_rsa_rule_list()
{
	local ret
	local count=0
	local ipset_used=0
	local accept_ip_set="remote_mngt_accept_ip_set"
	ret=$(ipset destroy "$accept_ip_set")
	ret=$(ipset create "$accept_ip_set" hash:net -exist 2>&1)

	_ipset_add_ip()
	{
		local ipaddr state
		config_get state "$1" enabled
		config_get ipaddr "$1" ipaddr

		if [[ "$state" == "on" && -n "$ipaddr" ]]; then
			if [[ "$ipaddr" == "0.0.0.0/0" ]]; then
				ipset_used=1
				return 0
			fi
			#rmc_add_rsa_cmd "$remote_mngt_accept_set" "$ipaddr"
			ipset add "$accept_ip_set" "$ipaddr"
			count=$(($count+1))
		fi
	}

	config_foreach _ipset_add_ip rsa_rule

	if [[ "$ipset_used" -eq 0 ]]; then
		if [[ "$count" -gt 0 ]]; then
			iptables -w -I "$RM_CHAIN" 1 -m set --match-set "$accept_ip_set" src -p tcp -m multiport --dport "$SERVER_PORTS" -j ACCEPT
		fi
	else
		iptables -w -I "$RM_CHAIN" 1 -p tcp -m multiport --dport "$SERVER_PORTS" -j ACCEPT
	fi

	return 0
}

rmc_start()
{
	{
	flock -x -w 10 60

		# Time out
		[ "$?" -eq "1" ] && return 1

		# local ret
		[ ! -f /etc/config/remote_mngt ] && touch /etc/config/remote_mngt

		if ! iptables -w -C INPUT -j "$RM_CHAIN" 2>/dev/null; then
			iptables -w -N "$RM_CHAIN"
			iptables -w -I INPUT 1 -j "$RM_CHAIN"
		else
			iptables -w -F "$RM_CHAIN"
		fi

		config_load remote_mngt

		local service="$(uci get remote_mngt.@support[0].service)"
		for serv in $service;do
			port=$(get_service_port $serv)
			[ -z "$port" ] && continue
			[ -z "$SERVER_PORTS" ] && SERVER_PORTS="$port" && continue
			SERVER_PORTS="$SERVER_PORTS,$port"
		done

		local service="$(uci get remote_mngt.@reject[0].service)"
		for serv in $service;do
			port=$(get_service_port $serv)
			[ -z "$port" ] && continue
			[ -z "$REJECT_PORTS" ] && REJECT_PORTS="$port" && continue
			REJECT_PORTS="$REJECT_PORTS,$port"
		done

		if [[ -n "$SERVER_PORTS" ]]; then
			rmc_add_rsa_rule_list
			config_foreach rmc_add_mngt_iface_list mngt_iface
		fi

		if [[ -n "$REJECT_PORTS" ]]; then
			rmc_add_rej_rule_list
		fi

		if [[ -n "$SERVER_PORTS" ]]; then
			iptables -w -I "$RM_CHAIN" 1 -p tcp -m multiport --dport "$SERVER_PORTS" -j ipsecmark --type use
		fi
	flock -u 60
	} 60<>/tmp/rmc.lock

	return 0
}

rmc_restart()
{
	rmc_stop
	rmc_start
}

rmc_stop()
{
	{
	flock -x -w 10 60

		# Time out
		[ "$?" -eq "1" ] && return 1

		if iptables -w -C INPUT -j "$RM_CHAIN" 2>/dev/null; then
			iptables -w -F "$RM_CHAIN"
			iptables -w -D INPUT -j "$RM_CHAIN"
			iptables -w -X "$RM_CHAIN"
		fi

	flock -u 60
	} 60<>/tmp/rmc.lock

	return 0
}

get_rule_num()
{
	config_get interface $1 interface
	config_get enable $1 enable
	
	if [ -n "${interface}" -a "${enable}" == "on" ];then
		let dmz_rule_num++
	fi
}

get_dmz_ruleNum()
{
	config_load nat
	config_foreach get_rule_num rule_dmz
}

rmc_reload()
{
	echo -e "start to load the remote_mngt_chain" > /dev/console
	rmc_restart
	echo -e "finish load the remote_mngt_chain" > /dev/console
	
	local dmz_rule_num=0
	get_dmz_ruleNum
	
	if [ ${dmz_rule_num} -gt 0 ];then
	
		echo "dmz_rule_num = ${dmz_rule_num},restart nat" > /dev/console
		/etc/init.d/nat restart
	fi		
}
