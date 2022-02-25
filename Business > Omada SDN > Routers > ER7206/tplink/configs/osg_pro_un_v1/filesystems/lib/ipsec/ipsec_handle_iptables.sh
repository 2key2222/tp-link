#!/bin/sh
#author ChenXing
#Usage: 	
#		ipsec_handle_iptables.sh <operation> TARGET_CHAIN
#Chain:
#       ipsec_pre_rule: mark the enc packet that receive
#       ipsec_input_rule: transform the packet to NFQUEUE
. /lib/functions.sh
. /lib/zone/zone_api.sh
. /lib/firewall/fw.sh

IPT="iptables -t mangle -w"

operation=$1

if [ "$operation" = "add" -o "$operation" = "del" ]; then
	target_chain=$2
fi

try_add_pre_chain()
{
	if ! $IPT -S PREROUTING | grep ipsec_pre_rule &> /dev/null; then
		$IPT -I PREROUTING -j ipsec_pre_rule
	fi
}

try_add_input_chain()
{
	if ! $IPT -S INPUT | grep ipsec_input_rule &> /dev/null; then
		$IPT -I INPUT -p udp -j ipsec_input_rule
	fi
}

try_del_pre_chain()
{
	if $IPT -S PREROUTING | grep ipsec_pre_rule &> /dev/null; then
		$IPT -D PREROUTING -j ipsec_pre_rule
	fi
}

#init_ipsec_chain()
# {
#	$IPT  -N ipsec_pre_rule
#	$IPT  -N ipsec_input_rule
#	$IPT -I INPUT -p udp -j ipsec_input_rule
#	$IPT -A ipsec_pre_rule -p udp -j CONNMARK --dport 4500 --restore-mark --nfmask 0xfe000000 --ctmask 0xfe000000
#	$IPT -A ipsec_pre_rule -p udp -m mark ! --mark 0x0/0xfe000000 -j RETURN
#	$IPT -A ipsec_pre_rule -p udp -j CONNMARK --save-mark --nfmask 0xfe000000 --ctmask 0xfe000000
#	$IPT -A ipsec_input_rule -p udp -m l2tp --type control --dport 1701 -m policy --strict --dir in --pol ipsec --proto esp -j NFQUEUE --queue-num 0 --queue-bypass
#}

init_ipsec_chain()
{
	$IPT  -N ipsec_pre_rule
	$IPT  -I ipsec_pre_rule -p esp -j CONNMARK --save-mark --nfmask 0x0ff00000 --ctmask 0x0ff00000
	$IPT  -N ipsec_input_rule
	try_add_input_chain
	$IPT -A ipsec_input_rule -p udp -m l2tp --type control --dport 1701 -m policy --strict --dir in --pol ipsec --proto esp -j NFQUEUE --queue-num 0 --queue-bypass
}

fw_check() {
	local ret=$(iptables -w -t $1 -C $2 $3 2>&1)
	[ -n "$ret" ] && return 0||return 1
}

ONLINE_ZONES=""
ipsec_each_connection(){
	local zone
	local status

	config_get zone "$1" local_binding
	[ -z "$zone" ] && return
	config_get status "$1" status

	if [ "$status" == "enable" ];then
		ONLINE_ZONES=${ONLINE_ZONES}" "${zone}
	fi
}

ipsec_service_fw_refresh()
{
	local local_service_chain=local_service_rule
	local ipsec_service_chain=ipsec_service_rule

	ONLINE_ZONES=""
	config_load ipsec
	config_foreach ipsec_each_connection connection

	fw_check "filter" "${local_service_chain}" "-j ${ipsec_service_chain}"
	if [ x$? == x0 ]; then
		iptables -w -N ${ipsec_service_chain}
		iptables -w -A ${local_service_chain} -j ${ipsec_service_chain}
	else
		iptables -w -F ${ipsec_service_chain}
	fi

	for zone in ${ONLINE_ZONES}
	do
		local inter=$(zone_get_effect_main_wan_ifaces $zone)
		interface=$(zone_get_device_byif $inter)
		for iface in $interface;do
			[ -n "$iface" -a "$iface" != "loopback" ] && {
				local rule="-i ${iface} -p udp -m multiport --dports 500,4500"
				fw_check "filter" "$ipsec_service_chain" "$rule -j ACCEPT"
				[ x$? == x0 ] && fw add 4 f $ipsec_service_chain ACCEPT $ { "$rule" }
			}
		done
	done
}

if [ "${operation}" = "add" ]; then
	if [ "${target_chain}" = "pre" ]; then
		try_add_pre_chain
	fi
	ipsec_service_fw_refresh
elif [ "${operation}" = "del" ]; then
	if [ "${target_chain}" = "pre" ]; then
		try_del_pre_chain
	fi
	ipsec_service_fw_refresh
elif [ "${operation}" = "init" ]; then
	init_ipsec_chain
else 
	exit 0
fi

