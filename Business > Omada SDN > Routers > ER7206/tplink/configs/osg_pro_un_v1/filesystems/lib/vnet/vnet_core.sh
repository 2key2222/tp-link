#!/bin/sh
# Linux os-dependent shell code.

# Infrastructure
###
# +---------VNET---------------------+          +----------INIT NET-----------------+
# |   default_route_to_igateway      |          |  route_to_ipaddr0_via_vgateway   |
# |                                  |          |  route_to_ipaddr1_via_vgateway   |
# +----------------------------------+          +-----------------------------------+
#   |              |               |                       |                   |
#   |              |               |               BRIDGE(igateway)            |
#   |              |               |                       |                   |
# vif0(ipaddr0) vif1(ipaddr1)  veth1(vgateway)~~~~~~~~~~veth0                 WAN
# 
. /lib/functions.sh 

VNET_ROUTE_TABLE_ID=29
VNET_ROUTE_TABLE_PRIO=29
VNET_UPLOAD_MARK=0x80000000 #extmark,   lan  -> VNET
VNET_DOWNLOAD_MARK=0x40000000 #extmark, veth -> VNET
VNET_DEVICE_MARK=0x80000000 #extmark,   wan  -> VNET
VNET_FORWARD_MARK=0x10000 #mark, lan/veth <-> lan/veth
# command exec in vnet namespace.
###IN###
# 1: command
# 2: command parameters ...
# 3: ...
vnetc_exec_in_vnet()
{
	ip netns exec vnet "$@"
}

vnetc_exec_in_dnet()
{
	ip netns exec default "$@"
}
# bind devices to vnet namespace.
###IN###
# 1: device name
# 2: device name
# 3: ...
vnetc_bind_to_vnet()
{
	for iface in "$@"
	do
		ip link set dev $1 netns vnet
	done
}

vnetc_bind_to_dnet()
{
	for iface in "$@"
	do
		ip link set dev $1 netns default
	done
}

# vnet interface device running
###IN###
# 1: device
vnetc_dev_running()
{
	vnetc_exec_in_vnet ip link show "${1}" | grep -Eq 'state UP|UNKNOWN'
}

# wrapper of firewall command.
vnetc_fw()
{
	iptables "$@"
}
vnetc_vnet_fw()
{
	vnetc_exec_in_vnet iptables "$@"
}

# wrapper of ipv6 firewall command.
vnetc_fw6()
{
	ip6tables "$@"
}
vnetc_vnet_fw6()
{
	vnetc_exec_in_vnet ip6tables "$@"
}

# service request redirected from <vnet> to <init net>
###IN###
# 1: fromip
# 2: toip
# 3: tcpports or '', split by ',', for example=>1701,67,20001
# 4: udpports or '', split by ','
vnetc_set_service_redirect()
{
	local chian="service_redirect"
	local from="$1"; shift
	local to="$1"; shift
	local tcpports="$1"; shift
	local udpports="$1"; shift

	[ -n "${from}" -a -n "${to}" -a -n "${tcpports}" ] && {
		vnetc_vnet_fw -w -t nat -D "${chian}" -p tcp -m multiport --dports "${tcpports}" -d "${from}" -j DNAT --to-destination "${to}"
		vnetc_vnet_fw -w -t nat -A "${chian}" -p tcp -m multiport --dports "${tcpports}" -d "${from}" -j DNAT --to-destination "${to}"
	}
	[ -n "${from}" -a -n "${to}" -a -n "${udpports}" ] && {
		vnetc_vnet_fw -w -t nat -D "${chian}" -p udp -m multiport --dports "${udpports}" -d "${from}" -j DNAT --to-destination "${to}"
		vnetc_vnet_fw -w -t nat -A "${chian}" -p udp -m multiport --dports "${udpports}" -d "${from}" -j DNAT --to-destination "${to}"
	}
	vnetc_vnet_fw -w -t nat -D "${chian}" -d "${from}" -m socket --nowildcard -j RETURN
	vnetc_vnet_fw -w -t nat -A "${chian}" -d "${from}" -m socket --nowildcard -j RETURN
	vnetc_vnet_fw -w -t nat -D "${chian}" -d "${from}" -j DNAT --to-destination "${to}"
	vnetc_vnet_fw -w -t nat -A "${chian}" -d "${from}" -j DNAT --to-destination "${to}"

	# common rules are never deleted
	# rules for vnet loopback from dnet
	if ! vnetc_vnet_fw -w -t nat -C POSTROUTING -o veth1 -m extmark --extmark ${VNET_DOWNLOAD_MARK}/${VNET_DOWNLOAD_MARK} -m conntrack --ctstate DNAT -j MASQUERADE 2>/dev/null; then
		vnetc_vnet_fw -w -t nat -I POSTROUTING 1 -o veth1 -m extmark --extmark ${VNET_DOWNLOAD_MARK}/${VNET_DOWNLOAD_MARK} -m conntrack --ctstate DNAT -j MASQUERADE
	fi
	# rules for dnet send to lan networks.
	if ! vnetc_vnet_fw -w -t nat -C POSTROUTING ! -o veth1 -s "${to}" -j MASQUERADE 2>/dev/null; then
		vnetc_vnet_fw -w -t nat -I POSTROUTING 1 ! -o veth1 -s "${to}" -j MASQUERADE
	fi
}

vnetc_unset_service_redirect()
{
	local chian="service_redirect"
	local from="$1"; shift
	local to="$1"; shift
	local tcpports="$1"; shift
	local udpports="$1"; shift

	[ -n "${from}" -a -n "${to}" -a -n "${tcpports}" ] && {
		vnetc_vnet_fw -w -t nat -D "${chian}" -p tcp -m multiport --dports "${tcpports}" -d "${from}" -j DNAT --to-destination "${to}"
	}
	[ -n "${from}" -a -n "${to}" -a -n "${udpports}" ] && {
		vnetc_vnet_fw -w -t nat -D "${chian}" -p udp -m multiport --dports "${udpports}" -d "${from}" -j DNAT --to-destination "${to}"
	}

	vnetc_vnet_fw -w -t nat -D "${chian}" -d "${from}" -m socket --nowildcard -j RETURN
	vnetc_vnet_fw -w -t nat -D "${chian}" -d "${from}" -j DNAT --to-destination "${to}"

	#vnetc_vnet_fw -w -t nat -D "${chian}" -i veth1 -j RETURN
	#vnetc_vnet_fw -w -t nat -D POSTROUTING -i veth1 -s "${to}" -j MASQUERADE
}

#0x10000
vnetc_load_forwarding_mark()
{
	forwarding_mark=${VNET_FORWARD_MARK}
	vnetc_vnet_fw -t mangle -w -I FORWARD 1 -j CONNMARK --or-mark ${forwarding_mark}
	vnetc_vnet_fw -t mangle -w -I FORWARD 1 -j MARK --or-mark ${forwarding_mark}
	vnetc_vnet_fw6 -t mangle -w -I FORWARD 1 -j CONNMARK --or-mark ${forwarding_mark}
	vnetc_vnet_fw6 -t mangle -w -I FORWARD 1 -j MARK --or-mark ${forwarding_mark}
}

# Create Vnet Namespace.
###IN###
vnetc_create()
{
	local chian="service_redirect"
	local foward_chain="forwarding_rule"
	
	[ ! -e /var/run/netns/default ] && {
		mkdir -p /var/run/netns/
		ln -s /proc/1/ns/net /var/run/netns/default
	}
	ip netns add vnet
	# global config of net namespace.
	### packet forwarding
	vnetc_exec_in_vnet sysctl -w /proc/sys/net/ipv4/conf/default/forwarding=1
	vnetc_exec_in_vnet sysctl -w /proc/sys/net/ipv4/ip_forward=1
	### sfe config
	vnetc_exec_in_vnet sysctl -w /proc/sys/net/netfilter/nf_conntrack_acct=1
	vnetc_exec_in_vnet sysctl -w /proc/sys/net/netfilter/nf_conntrack_tcp_no_window_check=1
	# P-2-P virtual device
	ip link add type veth
	vnetc_bind_to_vnet veth1
	# service chain
	vnetc_vnet_fw -t nat -w -N "${chian}"
	vnetc_vnet_fw -t nat -w -I PREROUTING 1 -j "${chian}"
	vnetc_vnet_fw -t filter -w -N "${foward_chain}"
	vnetc_vnet_fw -t filter -w -A FORWARD -j "${foward_chain}"
	#forward_auth
	vnetc_vnet_fw -t filter -w -N forward_auth
	vnetc_vnet_fw -t filter -w -A FORWARD -j forward_auth
	
	vnetc_vnet_fw -t filter -w -N forward
	vnetc_vnet_fw -t filter -w -A FORWARD -j forward
	vnetc_vnet_fw -t filter -w -A forward -j ACCEPT

	#mark upload/download connection
	vnetc_vnet_fw -t mangle -w -A PREROUTING -i veth1 -j EXTMARK --or-mark ${VNET_DOWNLOAD_MARK}
	vnetc_vnet_fw -t mangle -w -A PREROUTING -i veth1 -j CONNEXTMARK --or-mark ${VNET_DOWNLOAD_MARK}
	vnetc_vnet_fw -t mangle -w -A PREROUTING ! -i veth1 -j EXTMARK --or-mark ${VNET_UPLOAD_MARK}
	vnetc_vnet_fw -t mangle -w -A PREROUTING ! -i veth1 -j CONNEXTMARK --or-mark ${VNET_UPLOAD_MARK}

	#only decrease TTL in default netstack, restore the TTL been decreased by vnet netstack.
	vnetc_vnet_fw -t mangle -w -A PREROUTING -i veth1 -m extmark --extmark ${VNET_DEVICE_MARK}/${VNET_DEVICE_MARK} -j TTL --ttl-inc 1
	vnetc_vnet_fw -t mangle -w -A FORWARD -o veth1 ! -i veth1 -j TTL --ttl-inc 1

	vnetc_vnet_fw6 -t mangle -w -A PREROUTING -i veth1 -m extmark --extmark ${VNET_DEVICE_MARK}/${VNET_DEVICE_MARK} -j HL --hl-inc 1
	vnetc_vnet_fw6 -t mangle -w -A FORWARD -o veth1 ! -i veth1 -j HL --hl-inc 1

	# forwarding mark
	vnetc_load_forwarding_mark

	# vnet IP Group
	ipset create VMe hash:ip -exist
	ipset flush VMe
	
	vnetc_exec_in_vnet ifconfig lo up
}

# Destroy Vnet Namespace.
###IN###
vnetc_destroy()
{
	ip link delete veth0 type veth
	ip netns delete vnet
}

# Install/Uninstall NAT & Firewall rules.
###IN###
# 1: ipaddr, ip address of vlan interface
# 2: netmask
# 3: outdev, wan device
vnetc_set_internet()
{
	local ipaddr="$1"; shift
	local netmask="$1"; shift
	local outdev="$1"; shift
	local network prefix

	network=$(ipcalc -n ${ipaddr} ${netmask})
	network=`echo $network |cut -d "=" -f 2`
	prefix=$(ipcalc -p ${netmask})
	prefix=`echo $prefix |cut -d "=" -f 2`

	vnetc_fw -w -t nat -D postrouting_rule_multinat -s "${network}"/"${prefix}" -o "${outdev}" -j MASQUERADE
	vnetc_fw -w -D zone_lan_natfd_multinat -s "${network}"/"${prefix}" -o "${outdev}" -j ACCEPT
	vnetc_fw -w -t nat -I postrouting_rule_multinat 1 -s "${network}"/"${prefix}" -o "${outdev}" -j MASQUERADE
	vnetc_fw -w -I zone_lan_natfd_multinat 1 -s "${network}"/"${prefix}" -o "${outdev}" -j ACCEPT
}
vnetc_unset_internet()
{
	local ipaddr="$1"; shift
	local netmask="$1"; shift
	local outdev="$1"; shift
	local network prefix

	network=$(ipcalc -n ${ipaddr} ${netmask})
	network=`echo $network |cut -d "=" -f 2`
	prefix=$(ipcalc -p ${netmask})
	prefix=`echo $prefix |cut -d "=" -f 2`

	vnetc_fw -w -t nat -D postrouting_rule_multinat -s "${network}"/"${prefix}" -o "${outdev}" -j MASQUERADE
	vnetc_fw -w -D zone_lan_natfd_multinat -s "${network}"/"${prefix}" -o "${outdev}" -j ACCEPT
}


# set/unset routes to <vnet> for <init net>.
###IN###
# 1: ipaddr, ip address of vlan interface.
# 2: netmask
# 3: gw_downstream, ip address of veth1.
vnetc_set_downstream_routes()
{
	local ipaddr="$1"; shift
	local netmask="$1"; shift
	local gw_downstream="$1"; shift
	local netowrk
	
	network=$(ipcalc -n ${ipaddr} ${netmask})
	network=`echo $network |cut -d "=" -f 2`

	if ! ip rule | grep -q -e "from all lookup vnet" ; then
		echo $VNET_ROUTE_TABLE_ID vnet >> /etc/iproute2/rt_tables
		ip rule add pref ${VNET_ROUTE_TABLE_PRIO} table vnet
	fi
	# <init net> route to <vnet>
	ip route add "${network}"/"${netmask}" via "${gw_downstream}" table vnet
}
vnetc_set_downstream_routes_v6()
{
	local ipv6_enable="$1"; shift
	local ipv6_addr="$1"; shift
	local ipv6_prefixlen="$1"; shift
	local gw_downstream6="$1"; shift
	local netowrk

	# <init net> route to <vnet>
	[ "$ipv6_enable" == "on" ] && {
		ip -6 route add "${ipv6_addr}"/"${ipv6_prefixlen}" via "${gw_downstream6}" dev br-lan
		echo "[vnetc_set_downstream_routes_v6] ip -6 route add ${ipv6_addr}/${ipv6_prefixlen} via ${gw_downstream6} dev br-lan" >> /tmp/log/vnetc_log
	}
}
vnetc_unset_downstream_routes()
{
	local ipaddr="$1"; shift
	local netmask="$1"; shift
	local gw_downstream="$1"; shift
	local netowrk
	
	network=$(ipcalc -n ${ipaddr} ${netmask})
	network=`echo $network |cut -d "=" -f 2`

	# <init net> route to <vnet>
	ip route del "${network}"/"${netmask}" via "${gw_downstream}" table vnet
}
vnetc_unset_downstream_routes_v6()
{
	local ipv6_enable="$1"; shift
	local ipv6_addr="$1"; shift
	local ipv6_prefixlen="$1"; shift
	local gw_downstream6="$1"; shift

	# <init net> route to <vnet>
	[ -n "$ipv6_addr" -a -n "$ipv6_prefixlen" ] && {
		ip -6 route del "${ipv6_addr}"/"${ipv6_prefixlen}" via "${gw_downstream6}" dev br-lan
		echo "[vnetc_unset_downstream_routes_v6] ip -6 route del ${ipv6_addr}/${ipv6_prefixlen} via ${gw_downstream6} dev br-lan" >> /tmp/log/vnetc_log
	}
}

# set/unset routes to wan internet for <vnet>.
###IN###
# 1: gw_upstream, ip address of br-lan.
vnetc_set_upstream_routes()
{
	local gw_upstream="$1"; shift

	vnetc_exec_in_vnet ip route add default via "${gw_upstream}"
}
vnetc_set_upstream_routes_v6()
{
	local ipv6_enable="$1"; shift
	local gw_upstream6="$1"; shift
	local ifname="$1"; shift

	[ "$ipv6_enable" == "on" ] && {
		vnetc_exec_in_vnet ip -6 route add default via "${gw_upstream6}" dev "${ifname}"
		echo "[vnetc_set_upstream_routes_v6] vnetc_exec_in_vnet ip -6 route add default via ${gw_upstream6} dev ${ifname}" >> /tmp/log/vnetc_log
	}
}
vnetc_unset_upstream_routes()
{
	local gw_upstream="$1"; shift

	vnetc_exec_in_vnet ip route del default via "${gw_upstream}"
}
vnetc_unset_upstream_routes_v6()
{
	local ipv6_enable="$1"; shift
	local gw_upstream6="$1"; shift
	local ifname="$1"; shift

	vnetc_exec_in_vnet ip -6 route del default via "${gw_upstream6}" dev "${ifname}"
	echo "[vnetc_unset_upstream_routes_v6] vnetc_exec_in_vnet ip -6 route del default via ${gw_upstream6} dev ${ifname}" >> /tmp/log/vnetc_log
}

# add/upd/del vlan interface (network) for <vnet>.
###IN###
# 1: device
# 2: vlanid
# 3: ipaddr
# 4: netmask
# 5: macaddr
###OUT###
# 1: VIFNAME
# 2: VIPADDR
# 3: VNETMASK
vnetc_add_vlan_interface()
{
	local device="$1"; shift
	local vlanid="$1"; shift
	local ipaddr="$1"; shift
	local netmask="$1"; shift
	local macaddr="$1"; shift
	local ifname="${device}.${vlanid}"

	# create vlan device.
	$(ip link show ${device} | grep -q 'DOWN') && {
		ip link set dev "${device}" up
	}
	vconfig add "${device}" "${vlanid}"

	# vnet.
	vnetc_bind_to_vnet "${ifname}"
	[ -n "$ipaddr" -a -n "$netmask" ] && {
		vnetc_exec_in_vnet ip addr add "${ipaddr}"/"${netmask}" dev "${ifname}"
	}
	[ -n "$macaddr" ] && {
		vnetc_exec_in_vnet ip link set dev "${ifname}" up address "${macaddr}"
	}
	
	ipset add VMe $ipaddr -exist
	
	export -n -- "VIFNAME=${ifname}"
	export -n -- "VIPADDR=${ipaddr}"
	export -n -- "VNETMASK=${netmask}"
}
vnetc_upd_vlan_interface()
{
	local device="$1"; shift
	local vlanid="$1"; shift
	local ipaddr="$1"; shift
	local netmask="$1"; shift
	local macaddr="$1"; shift
	local ifname="${device}.${vlanid}"

	# vnet.
	[ -n "$ipaddr" -a -n "$netmask" ] && {
		vnetc_exec_in_vnet ip addr add "${ipaddr}"/"${netmask}" dev "${ifname}"
	}
	[ -n "$macaddr" ] && {
		vnetc_exec_in_vnet ip link set dev "${ifname}" up address "${macaddr}"
	}
	
	ipset add VMe $ipaddr -exist

	export -n -- "VIFNAME=${ifname}"
	export -n -- "VIPADDR=${ipaddr}"
	export -n -- "VNETMASK=${netmask}"
}
vnetc_del_vlan_interface()
{
	local device="$1"; shift
	local vlanid="$1"; shift
	local ipaddr="$1"; shift
	local netmask="$1"; shift
	local ifname="${device}.${vlanid}"

	# vnet.
	vnetc_exec_in_vnet ip link set dev "${ifname}" down
	[ -n "$ipaddr" -a -n "$netmask" ] && {
		vnetc_exec_in_vnet ip addr del "${ipaddr}"/"${netmask}" dev "${ifname}"
	}
	vnetc_exec_in_vnet vconfig rem "${ifname}"

	ipset del VMe $ipaddr -exist
}
vnetc_add_interface_addr_v6()
{
	local device="$1"; shift
	local vlanid="$1"; shift
	local macaddr="$1"; shift
	local ipv6_enable="$1"; shift
	local ipv6_addr="$1"; shift
	local ipv6_prefixlen="$1"; shift
	local ifname="${device}.${vlanid}"

	# vnet.
	[ "$ipv6_enable" == "on" -a -n "$ipv6_addr" -a -n "$ipv6_prefixlen" ] && {
		vnetc_exec_in_vnet ip -6 addr add "${ipv6_addr}"/"${ipv6_prefixlen}" dev "${ifname}"
		echo "[vnetc_add_interface_addr_v6] vnetc_exec_in_vnet ip -6 addr add ${ipv6_addr}/${ipv6_prefixlen} dev ${ifname}" >> /tmp/log/vnetc_log
	}
	
	export -n -- "VIFNAME=${ifname}"
	export -n -- "VIPADDR6=${ipv6_addr}"
	export -n -- "VPREFIXLEN6=${ipv6_prefixlen}"
}
vnetc_del_interface_addr_v6()
{
	local device="$1"; shift
	local vlanid="$1"; shift
	local macaddr="$1"; shift
	local ipv6_enable="$1"; shift
	local ipv6_addr="$1"; shift
	local ipv6_prefixlen="$1"; shift
	local ifname="${device}.${vlanid}"

	# vnet.
	[ -n "$ipv6_addr" -a -n "$ipv6_prefixlen" ] && {
		vnetc_exec_in_vnet ip -6 addr del "${ipv6_addr}"/"${ipv6_prefixlen}" dev "${ifname}"
		echo "[vnetc_del_interface_addr_v6] vnetc_exec_in_vnet ip -6 addr del ${ipv6_addr}/${ipv6_prefixlen} dev ${ifname}" >> /tmp/log/vnetc_log
	}
	# TODO: delete ipv6 cfg
}
# set/unset virtual wan interface for <vnet>.
###IN###
# 1: ifname
# 2: ipaddr
# 3: netmask
# 4: macaddr
###OUT###
# 1: VIFNAME
# 2: VIPADDR
# 3: VNETMASK
vnetc_set_vwan_interface()
{
	local ifname="$1"; shift
	local ipaddr="$1"; shift
	local netmask="$1"; shift
	local macaddr="$1"; shift

	# vnet
	[ -n "$ipaddr" -a -n "$netmask" ] && {
		vnetc_exec_in_vnet ip addr add "${ipaddr}"/"${netmask}" dev "${ifname}"
	}
	[ -n "$macaddr" ] && {
		vnetc_exec_in_vnet ip link set dev "${ifname}" up address "${macaddr}"
	}

	ipset add VMe $ipaddr -exist

	export -n -- "VIFNAME=${ifname}"
	export -n -- "VIPADDR=${ipaddr}"
	export -n -- "VNETMASK=${netmask}"
}
vnetc_set_vwan_interface_v6()
{
	local ifname="$1"; shift
	local macaddr="$1"; shift
	local ipv6_enable="$1"; shift
	local ipv6_addr="$1"; shift
	local ipv6_prefixlen="$1"; shift

	# vnet
	[ "$ipv6_enable" == "on" -a -n "$ipv6_addr" -a -n "$ipv6_prefixlen" ] && {
		vnetc_exec_in_vnet ip -6 addr add "${ipv6_addr}"/"${ipv6_prefixlen}" dev "${ifname}"
		echo "[vnetc_set_vwan_interface_v6] vnetc_exec_in_vnet ip -6 addr add ${ipv6_addr}/${ipv6_prefixlen} dev ${ifname}" >> /tmp/log/vnetc_log
	}

	export -n -- "VIFNAME=${ifname}"
	export -n -- "VIPADDR6=${ipv6_addr}"
	export -n -- "VPREFIXLEN6=${ipv6_prefixlen}"
}
vnetc_unset_vwan_interface()
{
	local ifname="$1"; shift
	local ipaddr="$1"; shift
	local netmask="$1"; shift

	# vnet
	vnetc_exec_in_vnet ip link set dev "${ifname}" down
	[ -n "$ipaddr" -a -n "$netmask" ] && {
		vnetc_exec_in_vnet ip addr del "${ipaddr}"/"${netmask}" dev "${ifname}"
	}

	ipset del VMe $ipaddr -exist
}
vnetc_unset_vwan_interface_v6()
{
	local ifname="$1"; shift
	local ipv6_enable="$1"; shift
	local ipv6_addr="$1"; shift
	local ipv6_prefixlen="$1"; shift

	# vnet
	[ -n "$ipv6_addr" -a -n "$ipv6_prefixlen" ] && {
		vnetc_exec_in_vnet ip -6 addr del "${ipv6_addr}"/"${ipv6_prefixlen}" dev "${ifname}"
		echo "[vnetc_unset_vwan_interface_v6] vnetc_exec_in_vnet ip -6 addr del ${ipv6_addr}/${ipv6_prefixlen} dev ${ifname}" >> /tmp/log/vnetc_log
	}
}

# Notify events from <init net>
###IN###
# 1: ifname
# 2: interface
# 3: action
vnetc_call_hotplug()
{
	local ifname="$1"; shift
	local interface="$1"; shift
	local action="$1"; shift
	local properties="$1"; shift

	env -i NAMESPACE="vnet" VNET_BOOTING="$VNET_BOOTING" DELAY_COMMIT="$DELAY_COMMIT" DEVICE="$ifname" INTERFACE="$interface" ACTION="$action" PROPERTIES="$properties" /sbin/hotplug-call vnet
}

vnetc_call_vvlan_hotplug()
{
	local vvlan="$1"; shift
	local action="$1"; shift
	local properties="$1"; shift

	env -i NAMESPACE="vnet" VNET_BOOTING="$VNET_BOOTING" DELAY_COMMIT="$DELAY_COMMIT" VVLAN="$vvlan" ACTION="$action" PROPERTIES="$properties" /sbin/hotplug-call vnet
}

vnetc_call_hotplug_commit()
{
	local zaction="$1"; shift
	env -i NAMESPACE="vnet" DEVICE="null" INTERFACE="null" VVLAN="null" ACTION="commit" ZACTION="$zaction" PROPERTIES="" /sbin/hotplug-call vnet
}
