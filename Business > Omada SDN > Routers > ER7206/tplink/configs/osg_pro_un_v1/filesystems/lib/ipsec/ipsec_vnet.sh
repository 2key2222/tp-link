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

# vnet 配合问题
REMOTE_NETWORK=""

fw_check() {
	local ret=$(vnete iptables -w -t $1 -C $2 $3 2>&1)
	echo "vnete iptables -w -t $1 -C $2 $3" > /dev/console
	[ -n "$ret" ] && return 0||return 1
}

ipsec_each_connection(){
	local remote
	local status

	config_get remote "$1" remote_network
	[ -z "$remote" ] && return
	config_get status "$1" status

	if [ "$status" == "enable" ];then
		REMOTE_NETWORK=${REMOTE_NETWORK}" "${remote}
	fi
}
# 访问本机的数据
vnet_check_each_connection(){
	local ipaddr
	local remote
	local ifname
	local ippeer
	local ret
	
	if [ "$1" = "vwan" ]; then
		return
	fi
	
	# 192.168.0.1
	config_get ipaddr "$1" ipaddr
	[ -z "$ipaddr" ] && return
	# veth1
	config_get ifname "vwan" ifname
	# 169.254.11.21
	config_get ippeer "vwan" ippeer
	
	for remote in ${REMOTE_NETWORK}
	do
		#echo "remote ${remote}" > /dev/console
		#echo "ipaddr ${ipaddr}" > /dev/console
		# dnet到vnet 允许进来，并再dnat到dnet
		ret=$(vnete iptables -w -t nat -C vpn_pre -i ${ifname} -s ${remote}  -d ${ipaddr} -j DNAT --to ${ippeer} 2>&1)
		#echo "vnete iptables -w -t nat -C vpn_pre -i ${ifname} -s ${remote}  -d ${ipaddr} -j DNAT --to ${ippeer}" > /dev/console
		[ -n "$ret" ] && vnete iptables -w -t nat -I vpn_pre -i ${ifname} -s ${remote}  -d ${ipaddr} -j DNAT --to ${ippeer} 
		# 从vnet dnat 到 dnet之后，为防止dnet返回的包直接匹配到通道从wan发出，还要进行snat，把s addr换掉
		ret=$(vnete iptables -w -t nat -C vpn_post -s ${remote}  -d ${ippeer} -j SNAT --to ${ipaddr} 2>&1)
		#echo "vnete iptables -w -t nat -C vpn_post -s ${remote}  -d ${ippeer} -j SNAT --to ${ipaddr}" > /dev/console
		[ -n "$ret" ] && vnete iptables -w -t nat -I vpn_post -s ${remote}  -d ${ippeer} -j SNAT --to ${ipaddr} 
	done
}

vnet_service_fw_refresh()
{
	fw_check "nat" "PREROUTING" "-j vpn_pre"
	if [ x$? == x0 ]; then
		#echo "new vpn_pre" > /dev/console
		vnete iptables -w -t nat -N vpn_pre
		# portal之后，service_redirect之前
		vnete iptables -w -t nat -I PREROUTING 2 -j vpn_pre
	else
		#echo "old vpn_pre" > /dev/console
		vnete iptables -w -t nat -F vpn_pre
	fi
	
	fw_check "nat" "POSTROUTING" "-j vpn_post"
	if [ x$? == x0 ]; then
		#echo "new vpn_post" > /dev/console
		vnete iptables -w -t nat -N vpn_post
		vnete iptables -w -t nat -I POSTROUTING -j vpn_post
	else
		#echo "old vpn_post" > /dev/console
		vnete iptables -w -t nat -F vpn_post
	fi
	
	REMOTE_NETWORK=""
	config_load ipsec
	config_foreach ipsec_each_connection connection
	
	config_load vnetwork
	config_foreach vnet_check_each_connection vinterface
}
# 现在所有通道的vnet自环已经统一处理，删除ipsec独立的处理
#vnet_service_fw_refresh

