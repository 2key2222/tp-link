#!/bin/sh

. /lib/zone/zone_api.sh
. /lib/firewall/fw.sh
. /lib/nat/nat_core.sh

UCI_TMP_PATH="/var/state"
UCI_TMP_CONFIG="upnp"
UCI_TMP_UPUP_PATH="${UCI_TMP_PATH}/${UCI_TMP_CONFIG}"
UPNP_LAN_CHAIN="UPNP_CHAIN"
UPNP_LOCK=/tmp/.upnp.lock

_delete_rule()
{
	local cfg=$1
	local del_pro=$2
	local del_eport=$3
	local del_iport=$4
	local del_ip=$5
	local protocal=
	local externalPort=
	local internalPort=
	local internalClient=

	config_get protocal "$cfg" protocal
	config_get externalPort "$cfg" externalPort
	config_get internalPort "$cfg" internalPort
	config_get internalClient "$cfg" internalClient

	if [[ $protocal == $del_pro && $externalPort == $del_eport && \
		$internalPort == $del_iport && $internalClient == $del_ip ]]; then
		uci -c "$UCI_TMP_PATH" delete "$UCI_TMP_CONFIG"."$cfg"
	fi
}

_reload_rule()
{
	local cfg=$1
	local protocal=
	local externalPort=
	local internalPort=
	local internalClient=
	local index=

	config_get protocal "$cfg" protocal
	config_get externalPort "$cfg" externalPort
	config_get internalPort "$cfg" internalPort
	config_get internalClient "$cfg" internalClient
	config_get index "$cfg" index

	_add_nat_rule $protocal $externalPort $internalPort $internalClient "$index" "skipped"
}

#$1: protocal
#$2: externalPort
#$3: internalPort
#$4: internalClient
#$5: natIndex
#$6: skipped
add_nat_rule()
{
	{
		flock -x 67
		_add_nat_rule "$1" "$2" "$3" "$4" "$5" "$6"
		flock -u 67
	} 67<>${UPNP_LOCK}
}

_add_nat_rule()
{
	local protocal=$1
	local index=$5
	local skipped=$6

	if [[ "$1" == "TCP/UDP" ]]; then
		protocal="tcp udp"
	elif [[ "$1" == "TCP" ]]; then
		protocal="tcp"
	elif [[ "$1" == "UDP" ]]; then
		protocal="udp"
	fi

	local server_zones=`uci get upnp.default.server_iface 2>/dev/null`
	local external_zones=`uci get upnp.default.external_iface 2>/dev/null`
	for ext_zone in $external_zones;do
		local ext_iface=$(zone_get_effect_ifaces "${ext_zone}" 2>/dev/null)
		local ext_device=$(zone_get_device_byif "${ext_iface}" 2>/dev/null)
		[[ -n "$ext_iface" && -n "$ext_device" ]] || continue

		for pro in $protocal; do
			nat_prerouting_add $MOD_UPNP "-A" "-i $ext_device -p $pro --dport $2 -j DNAT --to-destination $4:$3 ${index:+--nat-index $index}"

			for ser_zone in $server_zones;do
				ser_dev=$(zone_get_effect_devices "${ser_zone}") # LAN
				[ -n "$ser_dev" ] || continue
				nat_filter_add $ext_iface $MOD_UPNP "-A" "-o ${ser_dev} -d $4 -p $pro --dport $3 -j ACCEPT"
			done
		done
	done

	[[ "$skipped" == "skipped" ]] && return

	# save all rules for reload, they will be removed after reboot
	[[ ! -e "$UCI_TMP_UPUP_PATH" ]] && touch "$UCI_TMP_UPUP_PATH"

	local section=$(uci -c "${UCI_TMP_PATH}" add "${UCI_TMP_CONFIG}" upnp_rule)
	uci -c "${UCI_TMP_PATH}" set "${UCI_TMP_CONFIG}"."${section}".protocal=$1
	uci -c "${UCI_TMP_PATH}" set "${UCI_TMP_CONFIG}"."${section}".externalPort=$2
	uci -c "${UCI_TMP_PATH}" set "${UCI_TMP_CONFIG}"."${section}".internalPort=$3
	uci -c "${UCI_TMP_PATH}" set "${UCI_TMP_CONFIG}"."${section}".internalClient=$4
	uci -c "${UCI_TMP_PATH}" set "${UCI_TMP_CONFIG}"."${section}".index="$5"
	uci -c "${UCI_TMP_PATH}" commit "${UCI_TMP_CONFIG}"
}

#$1: protocal
#$2: externalPort
#$3: internalPort
#$4: internalClient
#$5: natIndex
del_nat_rule()
{
	{
		flock -x 67
		_del_nat_rule "$1" "$2" "$3" "$4" "$5"
		flock -u 67
	} 67<>${UPNP_LOCK}
		
}
_del_nat_rule()
{
	local protocal=0
	local index=$5

	if [[ "$1" == "TCP" ]]; then
		protocal="tcp"
	elif [[ "$1" == "UDP" ]]; then
		protocal="udp"
	elif [[ "$1" == "TCP/UDP" ]]; then
		protocal="tcp udp"
	fi

	local server_zones=`uci get upnp.default.server_iface 2>/dev/null`
	local external_zones=`uci get upnp.default.external_iface 2>/dev/null`

	for ext_zone in $external_zones;do
		local ext_iface=$(zone_get_effect_ifaces "${ext_zone}" 2>/dev/null)
		local ext_device=$(zone_get_device_byif "${ext_iface}" 2>/dev/null)
		[[ -n "$ext_iface" && -n "$ext_device" ]] || continue
		for pro in $protocal; do
			nat_prerouting_del $MOD_UPNP "-i $ext_device -p $pro --dport $2 -j DNAT --to-destination $4:$3 ${index:+--nat-index $index}"

			for ser_zone in $server_zones; do
				ser_dev=$(zone_get_effect_devices "${ser_zone}" 2>/dev/null)  # LAN
				[ -n "$ser_dev" ] || continue
				nat_filter_del $ext_iface $MOD_UPNP "-o ${ser_dev} -d $4 -p $pro --dport $3 -j ACCEPT"
			done
		done
	done

	config_load "$UCI_TMP_UPUP_PATH"
	config_foreach _delete_rule upnp_rule $1 $2 $3 $4
	uci -c "${UCI_TMP_PATH}" commit "${UCI_TMP_CONFIG}"
}

#$1:internalClient
#$2:internalPort
#$3:externalPort
#$4:protocal
del_server_rule()
{	
	ubus call upnp delete_rule "{\"internalClient\":\"$1\",\"internalPort\":$2,\"externalPort\":$3,\"proto\":\"$4\"}"
}

clean_iptables_rule()
{
	nat_prerouting_flush ${MOD_UPNP}
	local external_zones=`uci get upnp.default.external_iface 2>/dev/null`
	for ext_zone in $external_zones; do
		local ext_iface=$(zone_get_effect_ifaces "${ext_zone}" 2>/dev/null)
		if [[ -n "$ext_iface" ]]; then
			nat_filter_flush ${MOD_UPNP} $ext_iface
		fi
	done
	rm -f "$UCI_TMP_UPUP_PATH"
}

reload_nat_rule()
{
	{
		flock -x 67
		_reload_nat_rule
		flock -u 67
	} 67<>${UPNP_LOCK}
}

_reload_nat_rule()
{
	local en=`uci get upnp.default.state 2>/dev/null`
	if [[ "$en" == "on" ]]; then
		nat_prerouting_flush ${MOD_UPNP}

		local if_list=$(uci_get_state nat env if_list)
		if [[ -n "$if_list" ]]; then
			for iface in $if_list; do
				if [[ -n "$iface" && "$iface" != "lan" ]]; then
					nat_filter_flush ${MOD_UPNP} $iface
				fi
			done
		fi

		config_load "$UCI_TMP_UPUP_PATH"
		config_foreach _reload_rule upnp_rule
	fi
}

install_lan_network_iptables_rules()
{
	local prefix="$1"
	local upnp_tcp_port=1900
	local upnp_chain=${UPNP_LAN_CHAIN}

	if ! ${prefix} iptables -w -C INPUT -p tcp --dport 1900 -j ${upnp_chain} 2>/dev/null; then
		${prefix} iptables -N ${upnp_chain}
		${prefix} iptables -w -A INPUT -p tcp --dport 1900 -j ${upnp_chain}
		${prefix} iptables -w -I ${upnp_chain} 1 -p tcp -j REJECT --reject-with tcp-reset
		${prefix} iptables -w -I ${upnp_chain} 2 -j DROP
	fi

	server_iface=$(uci get upnp.default.server_iface)
	for zone in ${server_iface}
	do
		iface=$(zone_get_effect_ifaces ${zone})
		device=$(zone_get_effect_devices ${iface})
		${prefix} iptables -w -I ${upnp_chain} 1 -i ${device} -j RETURN
	done
}

clean_lan_network_iptables_rules()
{
	local prefix="$1"
	local upnp_chain=${UPNP_LAN_CHAIN}

	${prefix} iptables -w -D INPUT -p tcp --dport 1900 -j ${upnp_chain}
	${prefix} iptables -w -F ${upnp_chain}
	${prefix} iptables -w -X ${upnp_chain}
}
