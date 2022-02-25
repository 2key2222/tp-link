#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file      nat_public.sh
# brief
# author    Chen chen
# version   1.1.0
# date      23Apr15
# history   arg 1.0.0, 23Apr15, Chen chen, Create the file.
#           arg 1.1.0, 21Dec17, Zhangzhongwei, Rewrite the file.

NAT_TRUE=0
NAT_FALSE=1
NAPT_DEVICE_MARK=0x80000000 # lan <-> wan
NAPT_DEVICE_MARK_LANIN=0x40000000 # lan -> wan
NAT_PREROUTING_MANGLE="NAT_PREROUTING_RULE"
NAPT_DEVICE_CHAIN="napt_netdevice_chain"
NAPT_DEVICE_CACHE="/tmp/.nat_napt_iface_list"

############### UCI Config Functions ###############
nat_config_append() # <package>
{ 
	CONFIG_APPEND=1 config_load "$@"
	unset CONFIG_APPEND
}

nat_config_once() # <function> <type>
{
	local func=$1
	local type=$2
	shift 2

	local config=cfg00nil
	nat_config__once()
	{
		config=$1
	}
	config_foreach nat_config__once "$type"

	$func $config "$@"
}

nat_config_get_section()  # <config> <prefix> <type> <name> <default> ...
{
	local config=$1
	local prefix=$2
	shift 2

	if [[ -z "$config" ]]; then
		return 1
	fi
	if [[ -n "$prefix" ]]; then
		prefix="${prefix}_"
		export ${NO_EXPORT:+-n} -- "${prefix}NAME"="${config}"
		config_get "${prefix}TYPE" "$config" TYPE
	fi

	local enabled
	config_get_bool enabled "$config" enabled 1
	[ $enabled -eq 1 ] || return 1

	[ "$1" == '{' ] && shift
	while [ $# -ge 3 ]; do
		local type=$1
		local name=$2
		local dflt=$3
		shift 3
		# TODO: Move handling of defaults to /lib/functions.sh
		# and get replace the case block with the following 
		# two lines:
		# type=${type#string}
		# config_get${type:+_${type}} "${prefix}${name}" "$config" "$name" "$dflt" || return
		case "$type" in
			string)
				local tmp
				config_get tmp "$config" "$name" || return
				[ -z "$tmp" ] && tmp=$dflt
				export ${NO_EXPORT:+-n} -- "${prefix}${name}=${tmp}"
				continue
			;;
			boolean)
				type=bool
			;;
		esac;

		local cmd=${prefix}config_get_${type}
		type $cmd > /dev/null || {
			cmd=config_get_${type} 
		}
		type $cmd > /dev/null || {
			echo "config type $type (for $name) not supported" >&2
			return 1
		}
		$cmd "${prefix}${name}" "$config" "$name" "$dflt" || return
	done
}


############### Common Functions ###############
nat_integer()
{
	if [[ -n "$(echo $1|sed -n "/^[0-9]\+$/p")" ]]; then
		return $NAT_TRUE
	fi
	return $NAT_FALSE
}

nat_port()
{
	if nat_integer $1 && [[ "$1" -ge 1 && "$1" -le 65535 ]]; then
		return $NAT_TRUE
	fi
	return $NAT_FALSE
}

nat_enable_network()
{
	iptables -w -D forward -j DROP
}

nat_disable_network()
{
	if ! iptables -w -C forward -j DROP 2>/dev/null; then
		iptables -w -I forward 1 -j DROP
	fi
}

nat_is_loaded()
{
	local bool=$(uci_get_state nat core loaded) 
	return $((! ${bool:-0}))
}


nat_napt_whole()
{	
	[ "$(uci get nat.global.whole_napt)" == "on" ]
}

nat_napt_lan_ipaddr()
{
	whole_napt=$(uci get nat.global.whole_napt)
	if ! $(nat_napt_whole); then
		echo $(uci get network.lan.ipaddr)
	else
		echo 0.0.0.0
	fi
}

nat_napt_lan_netmask()
{
	if ! $(nat_napt_whole); then
		echo $(uci get network.lan.netmask)
	else
		echo 0.0.0.0
	fi
}

nat_prerouting_mangle_hotplug()
{
	$(nat_napt_whole) || return
	[ "$2" != "br-lan" ] && return
	
	case "$1" in
		ifup)
			iptables -w -t mangle -L ${NAT_PREROUTING_MANGLE} >/dev/null 2>&1 && {
				iptables -w -t mangle -A ${NAT_PREROUTING_MANGLE} -i br-lan -j CONNEXTMARK --or-mark ${NAPT_DEVICE_MARK_LANIN}
				iptables -w -t mangle -A ${NAT_PREROUTING_MANGLE} -i br-lan -j EXTMARK --or-mark ${NAPT_DEVICE_MARK_LANIN}
			}
		;;
		ifdown)
			iptables -w -t mangle -L ${NAT_PREROUTING_MANGLE} >/dev/null 2>&1 && {	
				iptables -w -t mangle -D ${NAT_PREROUTING_MANGLE} -i br-lan -j CONNEXTMARK --or-mark ${NAPT_DEVICE_MARK_LANIN}
				iptables -w -t mangle -D ${NAT_PREROUTING_MANGLE} -i br-lan -j EXTMARK --or-mark ${NAPT_DEVICE_MARK_LANIN}
			}
		;;
	esac
}

nat_prerouting_mangle_create()
{
	$(nat_napt_whole) || return
	
	iptables -w -t mangle -L ${NAT_PREROUTING_MANGLE} >/dev/null 2>&1 || {	
		iptables -w -t mangle -N ${NAT_PREROUTING_MANGLE}
		iptables -w -t mangle -I PREROUTING 1 -j ${NAT_PREROUTING_MANGLE}
	}
	
	iptables -w -t mangle -F ${NAT_PREROUTING_MANGLE}
	iptables -w -t mangle -A ${NAT_PREROUTING_MANGLE} -i br-lan -j CONNEXTMARK --or-mark ${NAPT_DEVICE_MARK_LANIN}
	iptables -w -t mangle -A ${NAT_PREROUTING_MANGLE} -i br-lan -j EXTMARK --or-mark ${NAPT_DEVICE_MARK_LANIN}
}

nat_prerouting_mangle_clean()
{
	$(nat_napt_whole) || return

	iptables -w -t mangle -L ${NAT_PREROUTING_MANGLE} >/dev/null 2>&1 && {
		iptables -w -t mangle -F ${NAT_PREROUTING_MANGLE}
	}
}

#1: action
#2: device
nat_napt_iface_list_hotplug()
{
	$(nat_napt_whole) || return

	[ -f ${NAPT_DEVICE_CACHE} ] || touch ${NAPT_DEVICE_CACHE}

	case "$1" in
		ifup)
			echo "$2" >> ${NAPT_DEVICE_CACHE}
			iptables -w -t mangle -L ${NAPT_DEVICE_CHAIN} >/dev/null 2>&1 && {	
				iptables -w -t mangle -A ${NAPT_DEVICE_CHAIN} -i $2 -j CONNEXTMARK --or-mark ${NAPT_DEVICE_MARK}
				iptables -w -t mangle -A ${NAPT_DEVICE_CHAIN} -i $2 -j EXTMARK --or-mark ${NAPT_DEVICE_MARK}
				iptables -w -t mangle -A ${NAPT_DEVICE_CHAIN} -o $2 -j CONNEXTMARK --or-mark ${NAPT_DEVICE_MARK}
				iptables -w -t mangle -A ${NAPT_DEVICE_CHAIN} -o $2 -j EXTMARK --or-mark ${NAPT_DEVICE_MARK}
			}
		;;
		ifdown)
			sed -i "/^${2}/d" ${NAPT_DEVICE_CACHE}
			iptables -w -t mangle -L ${NAPT_DEVICE_CHAIN} >/dev/null 2>&1 && {	
				iptables -w -t mangle -D ${NAPT_DEVICE_CHAIN} -i $2 -j CONNEXTMARK --or-mark ${NAPT_DEVICE_MARK}
				iptables -w -t mangle -D ${NAPT_DEVICE_CHAIN} -i $2 -j EXTMARK --or-mark ${NAPT_DEVICE_MARK}
				iptables -w -t mangle -D ${NAPT_DEVICE_CHAIN} -o $2 -j CONNEXTMARK --or-mark ${NAPT_DEVICE_MARK}
				iptables -w -t mangle -D ${NAPT_DEVICE_CHAIN} -o $2 -j EXTMARK --or-mark ${NAPT_DEVICE_MARK}
			}
		;;
	esac
	
	nat_prerouting_mangle_hotplug $1 $2
}

nat_napt_iface_list_create()
{
	$(nat_napt_whole) || return

	iptables -w -t mangle -L ${NAPT_DEVICE_CHAIN} >/dev/null 2>&1 || {	
		iptables -w -t mangle -N ${NAPT_DEVICE_CHAIN}
		iptables -w -t mangle -I FORWARD 1 -j ${NAPT_DEVICE_CHAIN}
	}

	iptables -w -t mangle -F ${NAPT_DEVICE_CHAIN}
	for dev in $(cat ${NAPT_DEVICE_CACHE})
	do
		iptables -w -t mangle -A ${NAPT_DEVICE_CHAIN} -i $dev -j CONNEXTMARK --or-mark ${NAPT_DEVICE_MARK}
		iptables -w -t mangle -A ${NAPT_DEVICE_CHAIN} -i $dev -j EXTMARK --or-mark ${NAPT_DEVICE_MARK}
		iptables -w -t mangle -A ${NAPT_DEVICE_CHAIN} -o $dev -j CONNEXTMARK --or-mark ${NAPT_DEVICE_MARK}
		iptables -w -t mangle -A ${NAPT_DEVICE_CHAIN} -o $dev -j EXTMARK --or-mark ${NAPT_DEVICE_MARK}
	done
	
	nat_prerouting_mangle_create
}

nat_napt_iface_list_clean()
{
	$(nat_napt_whole) || return

	iptables -w -t mangle -L ${NAPT_DEVICE_CHAIN} >/dev/null 2>&1 && {
		iptables -w -t mangle -F ${NAPT_DEVICE_CHAIN}
	}
	
	nat_prerouting_mangle_clean
}