# 1: destination variable
# 2: interface
# 3: path
# 4: separator
# 5: limit
__network_ifstatus() {
	local __tmp

	[ -z "$__NETWORK_CACHE" ] && \
		export __NETWORK_CACHE="$(ubus call network.interface dump)"

	__tmp="$(jsonfilter ${4:+-F "$4"} ${5:+-l "$5"} -s "$__NETWORK_CACHE" -e "$1=@.interface${2:+[@.interface='$2']}$3")"

	[ -z "$__tmp" ] && \
		unset "$1" && \
		return 1

	eval "$__tmp"
}

# determine first IPv4 address of given logical interface
# 1: destination variable
# 2: interface
network_get_ipaddr() {
	__network_ifstatus "$1" "$2" "['ipv4-address'][0].address";
	local ipx
	eval ipx=\$${1}
	[ -z "${ipx}" ] && eval $1=`/lib/l2tp/get-vpn-ip.sh $2`;
	eval ipx=\$${1}
	[ -z "${ipx}" ] && return 1 || return 0
}

# determine first IPv6 address of given logical interface
# 1: destination variable
# 2: interface
network_get_ipaddr6() {
	local __addr

	if __network_ifstatus "__addr" "$2" "['ipv6-address','ipv6-prefix-assignment'][0].address"; then
		case "$__addr" in
			*:)	export "$1=${__addr}1" ;;
			*)	export "$1=${__addr}" ;;
		esac
		return 0
	fi

	unset $1
	return 1
}

network_get_netmask() {
    __network_ifstatus "$1" "$2" "['ipv4-address'][0].mask";
	local ipx
	eval ipx=\$${1}
	[ -z "${ipx}" ] && { ipx=`/lib/l2tp/get-vpn-ip.sh $2`;
		[ -n "${ipx}" ] && eval $1=32
	}
	eval ipx=\$${1}
	[ -z "${ipx}" ] && return 1 || return 0
}
# determine first IPv4 subnet of given logical interface
# 1: destination variable
# 2: interface
network_get_subnet() {
	__network_ifstatus "$1" "$2" "['ipv4-address'][0]['address','mask']" "/"
	local ipx
	eval ipx=\$${1}
	[ -z "${ipx}" ] && { ipx=`/lib/l2tp/get-vpn-ip.sh $2`;
		[ -n "${ipx}" ] && eval $1=${ipx}/32
	}
	eval ipx=\$${1}
	[ -z "${ipx}" ] && return 1 || return 0
}

# determine first IPv4 target of given logical interface
# 1: destination variable
# 2: interface
network_get_target() {
	__network_ifstatus "$1" "$2" "['route'][0].target";
}

# determine first IPv6 subnet of given logical interface
# 1: destination variable
# 2: interface
network_get_subnet6() {
	__network_ifstatus "$1" "$2" "['ipv6-address'][0]['address','mask']" "/"
}

# determine first IPv6 prefix of given logical interface
# 1: destination variable
# 2: interface
network_get_prefix6() {
	__network_ifstatus "$1" "$2" "['ipv6-prefix'][0]['address','mask']" "/"
}

# determine all IPv4 addresses of given logical interface
# 1: destination variable
# 2: interface
network_get_ipaddrs() {
	__network_ifstatus "$1" "$2" "['ipv4-address'][*].address"
}

# determine all IPv6 addresses of given logical interface
# 1: destination variable
# 2: interface
network_get_ipaddrs6() {
	local __addr
	local __list=""

	if __network_ifstatus "__addr" "$2" "['ipv6-address','ipv6-prefix-assignment'][*].address"; then
		for __addr in $__addr; do
			case "$__addr" in
				*:)	__list="${__list:+$__list }${__addr}1" ;;
				*)  __list="${__list:+$__list }${__addr}"  ;;
			esac
		done

		export "$1=$__list"
		return 0
	fi

	unset "$1"
	return 1
}

# determine all IPv4 subnets of given logical interface
# 1: destination variable
# 2: interface
network_get_subnets() {
	__network_ifstatus "$1" "$2" "['ipv4-address'][*]['address','mask']" "/ "
}

# determine all IPv6 subnets of given logical interface
# 1: destination variable
# 2: interface
network_get_subnets6() {
	local __addr
	local __list=""

	if __network_ifstatus "__addr" "$2" "['ipv6-address','ipv6-prefix-assignment'][*]['address','mask']" "/ "; then
		for __addr in $__addr; do
			case "$__addr" in
				*:/*) __list="${__list:+$__list }${__addr%/*}1/${__addr##*/}" ;;
				*)    __list="${__list:+$__list }${__addr}"                   ;;
			esac
		done

		export "$1=$__list"
		return 0
	fi

	unset "$1"
	return 1
}

# determine all IPv6 prefixes of given logical interface
# 1: destination variable
# 2: interface
network_get_prefixes6() {
	__network_ifstatus "$1" "$2" "['ipv6-prefix'][*]['address','mask']" "/ "
}

# determine IPv4 gateway of given logical interface
# 1: destination variable
# 2: interface
# 3: consider inactive gateway if "true" (optional)
network_get_gateway() {
	__network_ifstatus "$1" "$2" ".route[@.target='0.0.0.0' && !@.table].nexthop" "" 1 && \
		return 0

	[ "$3" = 1 -o "$3" = "true" ] && \
		__network_ifstatus "$1" "$2" ".inactive.route[@.target='0.0.0.0' && !@.table].nexthop" "" 1
	local gwx
	eval gwx=\$${1}
	[ -z "${gwx}" ] && {	
		. /lib/l2tp/get-vpn-gw.sh
		eval $1=`get_vpn_gateway $2`
	}
	eval gwx=\$${1}
	[ -z "${gwx}" ] && return 1 || return 0
}

# determine IPv6 gateway of given logical interface
# 1: destination variable
# 2: interface
# 3: consider inactive gateway if "true" (optional)
network_get_gateway6() {
	__network_ifstatus "$1" "$2" ".route[@.target='::' && !@.table].nexthop" "" 1 && \
		return 0

	[ "$3" = 1 -o "$3" = "true" ] && \
		__network_ifstatus "$1" "$2" ".inactive.route[@.target='::' && !@.table].nexthop" "" 1
}

# determine the DNS servers of the given logical interface
# 1: destination variable
# 2: interface
# 3: consider inactive servers if "true" (optional)
network_get_dnsserver() {
	__network_ifstatus "$1" "$2" "['dns-server'][*]" && return 0

	[ "$3" = 1 -o "$3" = "true" ] && \
		__network_ifstatus "$1" "$2" ".inactive['dns-server'][*]"
}

# determine the domains of the given logical interface
# 1: destination variable
# 2: interface
# 3: consider inactive domains if "true" (optional)
network_get_dnssearch() {
	__network_ifstatus "$1" "$2" "['dns-search'][*]" && return 0

	[ "$3" = 1 -o "$3" = "true" ] && \
		__network_ifstatus "$1" "$2" ".inactive['dns-search'][*]"
}


# 1: destination variable
# 2: addr
# 3: inactive
__network_wan()
{
	__network_ifstatus "$1" "" \
		"[@.route[@.target='$2' && !@.table]].interface" "" 1 && \
			return 0

	[ "$3" = 1 -o "$3" = "true" ] && \
		__network_ifstatus "$1" "" \
			"[@.inactive.route[@.target='$2' && !@.table]].interface" "" 1
}

# find the logical interface which holds the current IPv4 default route
# 1: destination variable
# 2: consider inactive default routes if "true" (optional)
network_find_wan() { __network_wan "$1" "0.0.0.0" "$2"; }

# find the logical interface which holds the current IPv6 default route
# 1: destination variable
# 2: consider inactive dafault routes if "true" (optional)
network_find_wan6() { __network_wan "$1" "::" "$2"; }

# test whether the given logical interface is running
# 1: interface
network_is_up()
{
	local __up
	__network_ifstatus "__up" "$1" ".up" && [ "$__up" = 1 ]
}

network_is_up_x()
{
	local __up
	__network_ifstatus "__up" "$1" ".up"
	echo $__up
}

# determine the protocol of the given logical interface
# 1: destination variable
# 2: interface
network_get_protocol() { __network_ifstatus "$1" "$2" ".proto"; }

# determine the layer 3 linux network device of the given logical interface
# 1: destination variable
# 2: interface
network_get_device() { __network_ifstatus "$1" "$2" ".l3_device"; }

# determine the layer 2 linux network device of the given logical interface
# 1: destination variable
# 2: interface
network_get_physdev() { __network_ifstatus "$1" "$2" ".device"; }

# defer netifd actions on the given linux network device
# 1: device name
network_defer_device()
{
	ubus call network.device set_state \
		"$(printf '{ "name": "%s", "defer": true }' "$1")" 2>/dev/null
}

# continue netifd actions on the given linux network device
# 1: device name
network_ready_device()
{
	ubus call network.device set_state \
		"$(printf '{ "name": "%s", "defer": false }' "$1")" 2>/dev/null
}

# test whether the given logical interface is autostart
# 1: interface
network_is_autostart()
{
	local __autostart
	__network_ifstatus "__autostart" "$1" ".autostart" && [ "$__autostart" = 1 ]
}

# test whether the given logical interface is running or autostart
# 1: interface
network_is_up_autostart()
{
	network_is_up "$1" && return 0
	network_is_autostart "$1"
}

# flush the internal value cache to force re-reading values from ubus
network_flush_cache() { unset __NETWORK_CACHE; }
