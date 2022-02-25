. /lib/functions.sh
. /lib/functions/network.sh
. /usr/share/libubox/jshn.sh
. /lib/netifd/netifd-proto.sh
. /lib/vnet/vnet_init.sh

BINDING=""
CONFIG="network"
LANTYPE="interface"
WANCONFIG="network"
WANTYPE="interface"

radvddir="/tmp/radvd-$CONFIG"
radvdfile="$radvddir/radvd.conf"
radvdpidfile="$radvddir/radvd.pid"

get_tunnel_prefix() {
	local ip4="$1"
	local oIFS="$IFS"; IFS="."; set -- $ip4; IFS="$oIFS"
	printf "2002:%02x%02x:%02x%02x:1::\n" $1 $2 $3 $4
}

get_wanif() {
    local result
    local wanx_eth="${1/v6/eth}"   
    local wanx_poe="${1/v6/poe}"
    local var="$2"   
    local poe_enable=$(uci get ${WANCONFIG}.${wanx_poe}.t_poe_enable)
    [ "x1" == "x$poe_enable" ] && result=$wanx_poe || result=$wanx_eth

    eval "export -- \"$var=$result\""                
}

create_radvd_conf() {
	local ifname="$1"
	local prefix="$2"
	local prefixlen="$3"
	local mode="$4"
	local dns1="$5"
	local dns2="$6"
	
	echo -e "interface $ifname " >> "$radvdfile"
	echo -e "{" >> "$radvdfile"
	echo -e "\tAdvSendAdvert on;" >> "$radvdfile"
	
	if [ "$mode" == "slaac" ]; then
		echo -e "\tAdvManagedFlag off;" >> "$radvdfile"
		echo -e "\tAdvOtherConfigFlag on;" >> "$radvdfile"
		echo -e "\tprefix $prefix/$prefixlen" >> "$radvdfile"
		echo -e "\t{" >> "$radvdfile"
		echo -e "\t\tAdvOnLink on;" >> "$radvdfile"
		echo -e "\t\tAdvAutonomous on;" >> "$radvdfile"
		echo -e "\t\tAdvRouterAddr on;" >> "$radvdfile"
		echo -e "\t};" >> "$radvdfile"
	elif [ "$mode" == "dhcpv6" ]; then
		echo -e "\tAdvManagedFlag on;" >> "$radvdfile"
		echo -e "\tAdvOtherConfigFlag on;" >> "$radvdfile"
		echo -e "\tprefix $prefix/$prefixlen"  >> "$radvdfile"
		echo -e "\t{" >> "$radvdfile"
		echo -e "\t\tAdvOnLink on;" >> "$radvdfile"
		echo -e "\t\tAdvAutonomous off;" >> "$radvdfile"
		echo -e "\t\tAdvRouterAddr off;" >> "$radvdfile"
		echo -e "\t};" >> "$radvdfile"
	elif [ "$mode" == "rdnss" ]; then
		echo -e "\tAdvManagedFlag off;" >> "$radvdfile"
		echo -e "\tAdvOtherConfigFlag off;" >> "$radvdfile"
		echo -e "\tprefix $prefix/$prefixlen" >> "$radvdfile"
		echo -e "\t{" >> "$radvdfile"
		echo -e "\t\tAdvOnLink on;" >> "$radvdfile"
		echo -e "\t\tAdvAutonomous on;" >> "$radvdfile"
		echo -e "\t\tAdvRouterAddr on;" >> "$radvdfile"
		echo -e "\t};" >> "$radvdfile"
		echo -e "\tRDNSS $dns1 $dns2" >> "$radvdfile"
		echo -e "\t{" >> "$radvdfile"
		echo -e "\t\tAdvRDNSSPreference 8;" >> "$radvdfile"
		echo -e "\t\tAdvRDNSSOpen off;" >> "$radvdfile"
		echo -e "\t};" >> "$radvdfile"
	fi
	echo -e "};" >> "$radvdfile"
}

stop_radvd(){
	
	[ -f "$radvdpidfile" ] && kill -15 `cat "$radvdpidfile"`
	[ -d "$radvddir" ] && rm -rf "$radvddir"
	
}

start_radvd(){
	local ifname="$1"
	local count=3
	local running=`vnete ifconfig $ifname | grep RUNNING`
	while [ $count -ne 0 -a ${#running} -eq 0 ]; do
		sleep 1
		running=`vnete ifconfig $ifname | grep RUNNING`
		let "count=count - 1"
	done
	[ -f "$radvdfile" ] && {
		vnete /usr/sbin/radvd -C "$radvdfile" -p "$radvdpidfile"
	}
}

load_proto_dns()
{
	local ifacev6="$1"
	local __ndns1="$2"
	local __ndns2="$3"
	local dns1="none"
	local dns2="none"
	local dns tmp
	local ppp_type

	# load wan config
	config_load /etc/config/${WANCONFIG}

	foreach_pppv6()
	{
		[ "$1" != "$ifacev6" ] && return
		[ "$dns1" == "none" -a "$dns2" == "none" ] || return

		config_get ppp_type "$1" t_type

		if [ "$ppp_type" == "pppoeshare" ]; then
			local tmp_dns arr
			network_get_dnsserver tmp_dns "$1"

			arr=$(echo $tmp_dns|tr " " "\n")
			for x in $arr; do
			  if [ $dns1 == "none" ]; then
				dns1=`echo $x|grep ":"`
				[ -z ${dns1} ] && dns1="none"
			  elif [ $dns2 == "none" ]; then 
				dns2=`echo $x|grep ":"`
				[ -z ${dns2} ] && dns2="none"
			  fi
			done
		fi
	}

	foreach_wanv6()
	{
		[ "$1" != "$ifacev6" ] && return
		[ "$dns1" == "none" -a "$dns2" == "none" ] || return

		network_get_dnsserver dns "$1"
		[ -n "$dns" ] && {
			tmp=${dns%% *}				
			[ -n "$tmp" ] && dns1="$tmp"
			[ "$tmp" != "${dns##* }" ] && dns2="${dns##* }"
		}
	}

	config_foreach foreach_pppv6 ${WANTYPE}

	[ "$dns1" == "none" -a "$dns2" == "none" ] && {
		config_foreach foreach_wanv6 ${WANTYPE}
	}

	[ "$dns1" == "none" -o "$dns1" == "::" ] && {
		dns1="2001:4860:4860::8888"
	}

	[ "$dns2" == "none" -o "$dns2" == "::"  ] && {
		dns2="2001:4860:4860::8844"
	}
	
	eval "export -- \"$__ndns1=$dns1\""
	eval "export -- \"$__ndns2=$dns2\""

	# load old config
	config_load /etc/config/${CONFIG}
}

load_proto_prefix()
{
	local ifacev6="$1"
	local __nprefix="$2"
	local __nprefixlen="$3"
	local wan_type
	local lprefix
	local lprefixlen

	# load wan config
	config_load /etc/config/${WANCONFIG}

	foreach_6to4(){
		[ "$1" != "$ifacev6" ] && return
		[ -n "$lprefix" ] && return
		
		config_get wan_type "$ifacev6" wan_type

		[ "$wan_type" == "6to4" ] && {
			lprefix=$(cat "/tmp/ipv6_prefix.info."$1)
			lprefixlen=$(cat "/tmp/ipv6_prefixlen.info."$1)

			eval "export -- \"$__nprefix=$lprefix\""
			eval "export -- \"$__nprefixlen=$lprefixlen\""
		}
	}

	foreach_6rd(){
		[ "$1" != "$ifacev6" ] && return
		[ -n "$lprefix" ] && return
		
		config_get wan_type "$1" wan_type

		[ "$wan_type" == "6rd" ] && {
			lprefix=$(cat "/tmp/ipv6_prefix.info."$1)
			lprefixlen=$(cat "/tmp/ipv6_prefixlen.info."$1)

			eval "export -- \"$__nprefix=$lprefix\""
			eval "export -- \"$__nprefixlen=$lprefixlen\""
		}
	}

	foreach_prefix_delegation(){
		[ "$1" != "$ifacev6" ] && return
		[ -n "$lprefix" ] && return

		config_get proto "$1" proto
		config_get ip_mode "$1" ip_mode
		config_get ip_config "$1" ip_config

		if [ "$proto" == "dhcp6c" -o "$proto" == "pppoev6" ]; then
			if [ "$ip_mode" == "prefix" ]; then
				local dprefix=`cat /tmp/dhcp6c/prefix.info.$1`
				local dprefixlen=`cat /tmp/dhcp6c/prefixlen.info.$1`
				if [ $? -eq 0 -a "$dprefix" != "::" ]; then
					lprefix="$dprefix"
					lprefixlen="${dprefixlen:-64}"
					eval "export -- \"$__nprefix=$lprefix\""
					eval "export -- \"$__nprefixlen=$lprefixlen\""
					return 0
				fi
			fi
		fi
	}
	config_foreach foreach_6to4 ${WANTYPE}
	[ -n "$lprefix" ] && return
	config_foreach foreach_6rd ${WANTYPE}
	[ -n "$lprefix" ] && return
	config_foreach foreach_prefix_delegation ${WANTYPE}

	# load old config
	config_load /etc/config/${CONFIG}
}

load_proto_subprefix()
{
	local ifacev6="$1"
	local prefixid="$2"
	local __nprefix="$3"
	local __nprefixlen="$4"
	local lprefix=""
	local lprefixlen=64
		
	load_proto_prefix "$ifacev6" gprefix gprefixlen

	[ -n "$gprefix" -a -n "$gprefixlen" -a "$gprefixlen" -le 64 ] && {
		local pre_size=$(((1<<(64 - ${gprefixlen}))-1))
		[ "$gprefixlen" -le 48 -o "$prefixid" -le "$pre_size" ] && {
			local oIFS="$IFS";
			lprefix="$gprefix"
			
			expr "$lprefix" : ".\+::$" > /dev/null && {
				lprefix="$lprefix""0000"
			}
			expr "$lprefix" : "::.\+$" > /dev/null && {
				lprefix="0000""$lprefix"
			}

			IFS=":"; set -- $lprefix; IFS="$oIFS"
			while [ $# -lt 8 ];
			do
				lprefix=${lprefix//::/:0000::}; IFS=":"; set -- $lprefix; IFS="$oIFS"
			done
			lprefix=${lprefix//::/:0000:}; IFS=":"; set -- $lprefix; IFS="$oIFS"
			if [ "$gprefixlen" -le 16 ]; then
				prefixn=$((0x${1}))
				prefixn=$((${prefixn} & (0xFFFF << (16 - ${gprefixlen}))))
				lprefix="$(printf "%x" ${prefixn}):${2}:${3}:$(printf "%x" ${prefixid})::"
			elif [ "$gprefixlen" -le 32 ]; then
				prefixn=$((0x${2}))
				prefixn=$((${prefixn} & (0xFFFF << (32 - ${gprefixlen}))))
				lprefix="${1}:$(printf "%x" ${prefixn}):${3}:$(printf "%x" ${prefixid})::"
			elif [ "$gprefixlen" -le 48 ]; then
				prefixn=$((0x${3}))
				prefixn=$((${prefixn} & (0xFFFF << (48 - ${gprefixlen}))))
				lprefix="${1}:${2}:$(printf "%x" ${prefixn}):$(printf "%x" ${prefixid})::"
			elif [ "$gprefixlen" -le 64 ]; then
				prefixn=$((0x${4}))
				prefixn=$(((${prefixn} & (0xFFFF << (64 - ${gprefixlen}))) + ${prefixid}))
				lprefix="${1}:${2}:${3}:$(printf "%x" ${prefixn})::"
			fi
		}
	}

	eval "export -- \"$__nprefix=$lprefix\""
	eval "export -- \"$__nprefixlen=$lprefixlen\""
}

stop_passthrough()
{
	rmmod  ipv6-pass-through

	# device left promiscuous mode
	for dev in $(cat /tmp/.wan_passthrough)
	do
		ifconfig $dev -promisc
	done
	for dev in $(cat /tmp/.lan_passthrough)
	do
		vnete ifconfig $dev -promisc
	done
}

setup_passthrough()
{
	export LAN_PASSTHROUGH="${LAN_PASSTHROUGH:+${LAN_PASSTHROUGH} }${1}"
	export WAN_PASSTHROUGH="${WAN_PASSTHROUGH:+${WAN_PASSTHROUGH} }${2}"
}

start_passthrough()
{
	# device enter promiscuous mode
	for dev in ${WAN_PASSTHROUGH}
	do
		ifconfig $dev promisc
	done
	for dev in ${LAN_PASSTHROUGH}
	do
		vnete ifconfig $dev promisc
	done
	
	[ -n "${WAN_PASSTHROUGH}" ] && {
		insmod ipv6-pass-through wan_eth_name="${WAN_PASSTHROUGH// /,}" lan_eth_name="${LAN_PASSTHROUGH// /,}"
	}
	
	# record devices
	echo ${WAN_PASSTHROUGH} > /tmp/.wan_passthrough
	echo ${LAN_PASSTHROUGH} > /tmp/.lan_passthrough
}

key_enable=""
key_ifacev6="ifacev6"
key_proto="proto"
key_ifname="ifname"
key_address="ip6addr"
key_prefix="prefix"
key_prefixlen="prefixlen"
key_leasetime="leasetime"
key_startip="startip"
key_endip="endip"

# interface
# proto
# prefix
# prefixlen
proto_common_addr_setup() {
	case $2 in
	"slaac"|"rdnss")
		if [ -n "$3" ]; then
			uci set ${CONFIG}.${1}.${key_prefix}="$3"
			uci set ${CONFIG}.${1}.${key_prefixlen}="$4"
		else
			uci del ${CONFIG}.${1}.${key_prefix}
			uci del ${CONFIG}.${1}.${key_prefixlen}
		fi
		uci commit ${CONFIG}
		;;
	*)
		;;
	esac
	clean_lan_interfaces_v6 "$1"
	setup_lan_interfaces_v6 "$1"
}

# interface
proto_common_setup() {
	local iface="$1"

    # stop radvd
	# need stop radvd first to avoid generating more than one radvd process. for bug163129 by liwei.
	stop_radvd
	# stop dhcp6s
	/etc/init.d/dhcp6s stop
	# stop passthrough
	stop_passthrough

	# setup radvd & dhcp6s
	mkdir -p "$radvddir"

	config_load /etc/config/${CONFIG}

	let radvd_cnt=0
	let dhcp6s_cnt=0
	control=""
	ddevice=""
	rdevice=""
	setup_iface()
	{
		[ -n "$iface" -a "$1" != "$iface" ] && return

		[ -n "$key_enable" ] && config_get enable_v "${1}" ${key_enable}
		config_get ifacev6 "${1}" ${key_ifacev6}
		config_get proto_v "${1}" ${key_proto}
		config_get ifname_v "${1}" ${key_ifname}
		config_get address_v "${1}" ${key_address}
		config_get prefix_v "${1}" ${key_prefix}
		config_get prefixlen_v "${1}" ${key_prefixlen}
		config_get leasetime_v "${1}" ${key_leasetime}
		config_get startip_v "${1}" ${key_startip}
		config_get endip_v "${1}" ${key_endip}
		config_get prefixid_v "${1}" ${key_prefixid}
		config_get pridns_v "${1}" ${key_pridns}
		config_get snddns_v "${1}" ${key_snddns}
		
		[ -n "$key_enable" -a "${enable_v}" != "on" ] && return
		[ -z "$proto_v" ] && return
		
		[ "$proto_v" == "passthrough" ] && {
			setup_passthrough "$ifname_v" "$(uci get ${WANCONFIG}."${ifacev6/v6/eth}".ifname)"
			return
		}

		[ -n "$ifacev6" -a -n "$prefixid_v" ] && {
			load_proto_subprefix "$ifacev6" "$prefixid_v" gprefix gprefixlen
			prefix_v=${gprefix}
			prefixlen_v=${gprefixlen}
			# setup new ipv6 addr for interface
			proto_common_addr_setup "$1" "$proto_v" "$prefix_v" "$prefixlen_v"
		}

		export gdns1=""
		export gdns2=""
		[ -z "$pridns_v" -a -z "$snddns_v" ] && load_proto_dns "$ifacev6" gdns1 gdns2
		
		[ "$proto_v" != "dhcpv6" -a -z "${prefix_v}" ] && return

		# configure radvd
		if [ "$proto_v" == "dhcpv6" -o "$proto_v" == "slaac" -o "$proto_v" == "rdnss" ]; then
			[ -z "$rdevice" ] && rdevice="$ifname_v"
			create_radvd_conf "$ifname_v" "${prefix_v:-$address_v}" "$prefixlen_v" "$proto_v" "${pridns_v:-${gdns1}}" "${snddns_v:-${gdns2}}"
			let radvd_cnt++
		fi

		# configure dhcp6s
		if [ "$proto_v" == "dhcpv6" -o "$proto_v" == "slaac" ]; then
			uci set dhcp6s.basic.iface_${dhcp6s_cnt}="$1"
			uci set dhcp6s.basic.proto_${dhcp6s_cnt}="$proto_v"
			uci set dhcp6s.basic.primary_dns_${dhcp6s_cnt}="${pridns_v:-${gdns1}}"
			uci set dhcp6s.basic.secondary_dns_${dhcp6s_cnt}="${snddns_v:-${gdns2}}"
			uci set dhcp6s.basic.ifname_${dhcp6s_cnt}="$ifname_v"
			[ "$proto_v" = "dhcpv6" ] && {
				leasetime_v="${leasetime_v:-86400}"
				startip_v="${prefix_v}${startip_v:-1000}"
				endip_v="${prefix_v}${endip_v:-2000}"

				uci set dhcp6s.basic.startip_${dhcp6s_cnt}="$startip_v"
				uci set dhcp6s.basic.endip_${dhcp6s_cnt}="$endip_v"
				uci set dhcp6s.basic.leasetime_${dhcp6s_cnt}="$leasetime_v"
			}
			[ -z "$control" ] && {
				control="$1"
				ddevice="$ifname_v"
			}
			let dhcp6s_cnt++
		fi
	}

	config_file=$(uci get dhcp6s.basic.config_file)
	uci delete dhcp6s.basic
	uci set dhcp6s.basic=dhcp6s
	uci set dhcp6s.basic.config_file=${config_file}
	config_foreach setup_iface ${LANTYPE}
	uci set dhcp6s.basic.ifcnt="$dhcp6s_cnt"
	if [ "$radvd_cnt" -ge 1 ]; then
		# start radvd
		start_radvd "$rdevice"
	fi

	if [ "$dhcp6s_cnt" -ge 1 ]; then
		# configure & start dhcp6s
		uci set dhcp6s.basic.enabled="1"
		uci set dhcp6s.basic.interface="$control"
		uci set dhcp6s.basic.ifname="$ddevice"
		uci commit dhcp6s
		/etc/init.d/dhcp6s start
	else
		uci set dhcp6s.basic.enabled="0"
		uci commit dhcp6s
	fi

	#start passthrough
	start_passthrough
}

proto_lanv6_setup() {
	anete sysctl -w net.ipv6.conf.all.forwarding=1 > /dev/null 2> /dev/null
	proto_common_setup
}

proto_lanv6_teardown() {
	stop_radvd
    /etc/init.d/dhcp6s stop
	stop_passthrough
}

proto_lanv6_multilan_env() {
	CONFIG="vnetwork"
	LANTYPE="vinterface"
	radvddir="/tmp/radvd-$CONFIG"
	radvdfile="$radvddir/radvd.conf"
	radvdpidfile="$radvddir/radvd.pid"
	key_enable="ipv6_enable"
	key_ifacev6="ipv6_ifacev6"
	key_proto="ipv6_proto"
	key_ifname="ifname"
	key_address="ipv6_addr"
	key_prefix="ipv6_prefix"
	key_prefixlen="ipv6_prefixlen"
	key_leasetime="ipv6_release"
	key_startip="ipv6_rstart"
	key_endip="ipv6_rend"
	key_prefixid="ipv6_prefixid"
	key_pridns="ipv6_priDns"
	key_snddns="ipv6_sndDns"
}

proto_lanv6_setup_multilan() {
	niface="$1"

	proto_lanv6_multilan_env

	[ -n "$niface" ] && {
		binding=""
		starting=""

		config_load /etc/config/${CONFIG}
		foreach_iface() {
			config_get ifacev6 "$1" "${key_ifacev6}" ""
			config_get enable_v "$1" "${key_enable}" ""
			[ "$enable_v" == "on" ] && starting="on"
			[ "$enable_v" == "on" -a "$ifacev6" == "$niface" ] && binding="on"
		}
		config_foreach foreach_iface ${LANTYPE}
		
		# WAN interface binding to LAN interface ?
		expr "$niface" : "\(^wan[1-4]_v6$\)" > /dev/null && {
			[ -z "$binding" ] && return
		}

		# LAN interface is on ?
		[ -z "$starting" ] && return
	}

	proto_lanv6_setup
}