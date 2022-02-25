#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file      nat_core.sh
# brief
# author    Chen chen
# version   1.1.0
# date      20Apr15
# history   arg 1.0.0, 20Apr15, Chen chen, Create the file.
#           arg 1.1.0, 21Dec17, Zhangzhongwei, Rewrite the file.

include /lib/network
. /lib/functions.sh
. /lib/functions/network.sh
. /lib/zone/zone_api.sh
. /lib/firewall/fw.sh
. /lib/nat/nat_log.sh
. /lib/nat/nat_config.sh
. /lib/nat/nat_common.sh

NAT_SWITCH_ENABLED=


get_nat_binding_index()
{
	dnete cat /proc/net/nat_index
}

put_nat_binding_index()
{
	dnete echo "$1" > /proc/net/nat_index
}

# Priority: alg/vpn > onenat > vs > pt > multinat > upnp > dmz
nat_get_insert_index()
{
	local table=$1
	local parent=$2
	local module=$3
	local priority=""
	local index=1

	case $module in
		onenat)   priority="$MOD_VPN";;
		vs)       priority="$MOD_VPN $MOD_ONE";;
		pt)       priority="$MOD_VPN $MOD_ONE $MOD_VS";;
		multinat) priority="$MOD_VPN $MOD_ONE $MOD_VS $MOD_PT";;
		upnp)     priority="$MOD_VPN $MOD_ONE $MOD_VS $MOD_PT";;
		dmz)      priority="$MOD_VPN $MOD_ONE $MOD_VS $MOD_PT $MOD_UPNP";;
	esac
	for mod in $priority; do
		iptables -w -t $table -C $parent -j ${parent}_${mod} 2>/dev/null && index=$((index+1))
	done
	echo -n $index
}

nat_get_chain_name()
{
	local module=$1
	local place=$2
	local iface=$3
	case $place in
		prerouting)  echo -n "${NAT_PREROUTNIG_ROOT}_${module}";;
		postrouting) echo -n "${NAT_POSTROUTING_ROOT}_${module}";;
		filter)      echo -n "zone_${iface}_natfd_${module}";;
	esac
}

nat_exec_and_print()
{
	local cmd_to_exec=$1
	$cmd_to_exec >/dev/null 2>&1
	NAT_PRINT "    - $cmd_to_exec"
}

nat_check_nat_parent()
{
	local table=$1
	local root=$2
	local parent=$3
	local module=$4
	local index=1

	if ! iptables -w -t $table -C $root -j $parent 2>/dev/null; then
		nat_exec_and_print "iptables -w -t $table -N $parent"
		nat_exec_and_print "iptables -w -t $table -I $root -j $parent"
	fi
	if ! iptables -w -t $table -C $parent -j ${parent}_${module} 2>/dev/null; then
		index=$(nat_get_insert_index $table $parent $module)
		nat_exec_and_print "iptables -w -t $table -N ${parent}_${module}"
		nat_exec_and_print "iptables -w -t $table -I $parent $index -j ${parent}_${module}"
	fi
}

nat_check_prerouting_parent()
{
	nat_check_nat_parent nat PREROUTING $NAT_PREROUTNIG_ROOT $1
}

nat_check_postrouting_parent()
{
	nat_check_nat_parent nat POSTROUTING $NAT_POSTROUTING_ROOT $1
}

nat_check_filter_parent()
{
	local module=$1
	local iface=$2
	local device=$(zone_get_device_byif $iface)

	if [[ -n "$device" ]]; then
		if ! iptables -w -C forward -i $device -j zone_${iface}_forward 2>/dev/null; then
			NAT_LOG_PRINT "! ${iface} is down, stop building filter rule for ${iface}."
			return 1
		fi
		nat_check_nat_parent filter zone_${iface}_forward zone_${iface}_natfd $module
	fi
}

# Try to add a chain, and the parent chains would be built if necessary.
nat_check_add()
{
	local place=$1   # prerouting/postrouting/filter
	local table=$2
	local module=$3
	local operate=$4
	local params=$5
	local iface=$6

	if [[ -z "$module" || -z "$operate" || -z "$params" ]] || [[ "$place" == "filter" && -z "$iface" ]]; then
		NAT_LOG_PRINT "! nat_check_add failed, null params"
		return 1
	fi

	local index=${operate##*\ }
	if [[ "$operate" == "$index" ]]; then
		index=""
	else
		operate=${operate%%\ *}
	fi

	local chain=$(nat_get_chain_name $module $place $iface)
	local cmd_to_exec="iptables -w -t $table $operate $chain $index $params"

	NAT_PRINT "    - $(echo $cmd_to_exec | tr '  ' ' ')"
	if ! $cmd_to_exec 2>/dev/null; then
		NAT_PRINT "    need to build $place parent chains"
		nat_check_${place}_parent $module $iface && $cmd_to_exec
	fi
}

#$1:module
#$2:operate
#$3:params
nat_prerouting_add()
{
	nat_check_add prerouting nat "$1" "$2" "$3"
}

#$1:module
#$2:operate
#$3:params
nat_postrouting_add()
{
	nat_check_add postrouting nat "$1" "$2" "$3"
}

#$1:iface
#$2:module
#$3:operate
#$4:params
nat_filter_add()
{
	nat_check_add filter filter "$2" "$3" "$4" "$1"
}

# Try to delete a chain, and the parent chains would be deleted if they had no child chain.
nat_check_del()
{
	local place=$1
	local table=$2
	local module=$3
	local params=$4
	local iface=$5
	local root parent child
	local cmd_to_exec

	if [[ -z "$module" || -z "$params" ]] || [[ "$place" == "filter" && -z "$iface" ]]; then
		NAT_LOG_PRINT "! nat_check_del failed, null params"
		return 1
	fi

	case $place in
		prerouting)  root=PREROUTING;;
		postrouting) root=POSTROUTING;;
		filter)      root=zone_${iface}_forward;;
	esac

	child=$(nat_get_chain_name $module $place $iface)
	parent=${child%_*}

	cmd_to_exec="iptables -w -t $table -D $child $params"
	$cmd_to_exec >/dev/null 2>&1
	NAT_PRINT "    - $(echo $cmd_to_exec | tr '  ' ' ')"

	if [[ $(iptables -w -t $table -S $child 2>/dev/null | wc -l) -eq 1 ]]; then
		nat_exec_and_print "iptables -w -t $table -D $parent -j $child"
		nat_exec_and_print "iptables -w -t $table -X $child"

		if [[ $(iptables -w -t $table -S $parent 2>/dev/null | wc -l) -eq 1 ]]; then
			nat_exec_and_print "iptables -w -t $table -D $root -j $parent"
			nat_exec_and_print "iptables -w -t $table -X $parent"
		fi
	fi
}

#$1:module
#$2:params
nat_prerouting_del()
{
	nat_check_del prerouting nat "$1" "$2"
}

#$1:module
#$2:params
nat_postrouting_del()
{
	nat_check_del postrouting nat "$1" "$2"
}

#$1:iface
#$2:module
#$3:params
nat_filter_del()
{
	nat_check_del filter filter "$2" "$3" "$1"
}

# Try to flush a chain, and the parent chains would be deleted if they had no child chain.
nat_flush_chains()
{
	local table=$1
	local root=$2
	local parent=$3
	local child=$4

	if [[ -z "$table" || -z "$root" || -z "$parent" || -z "$child" ]]; then
		NAT_LOG_PRINT "! nat_flush_chains failed, null params"
		return 1
	fi

	if [[ $(iptables -w -t $table -S $child 2>/dev/null | wc -l) -gt 1 ]]; then
		nat_exec_and_print "iptables -w -t $table -F $child"
		nat_exec_and_print "iptables -w -t $table -D $parent -j $child"
		nat_exec_and_print "iptables -w -t $table -X $child"

		if [[ $(iptables -w -t $table -S $parent 2>/dev/null | wc -l) -eq 1 ]]; then
			nat_exec_and_print "iptables -w -t $table -D $root -j $parent"
			nat_exec_and_print "iptables -w -t $table -X $parent"
		fi
	fi
}

nat_prerouting_flush()
{
	local module=$1
	nat_flush_chains nat PREROUTING ${NAT_PREROUTNIG_ROOT} ${NAT_PREROUTNIG_ROOT}_${module}
}

nat_postrouting_flush()
{
	local module=$1
	nat_flush_chains nat POSTROUTING ${NAT_POSTROUTING_ROOT} ${NAT_POSTROUTING_ROOT}_${module}
}

nat_filter_flush()
{
	local module=$1
	local iface=$2
	nat_flush_chains filter zone_${iface}_forward zone_${iface}_natfd zone_${iface}_natfd_${module}
}

nat_load_global_config()
{
	NAT_SWITCH_ENABLED=$(uci get nat.global.enable)
	NAT_LOG_PRINT "@ loading global config, NAT_SWITCH_ENABLED=$NAT_SWITCH_ENABLED"
}

nat_prepare_env()
{
	NAT_LOG_PRINT "@ loading nat config and source files"

	# load uci config
	nat_config_append nat
	nat_config_append administration

	# source nat_*.sh
	. /lib/nat/nat_alg.sh
	. /lib/nat/nat_dmz.sh
	. /lib/nat/nat_napt.sh
	. /lib/nat/nat_one.sh
	. /lib/nat/nat_pt.sh
	. /lib/nat/nat_vs.sh
}

nat_put_each_index()
{
	local _natIndex
	config_get _natIndex "$1" natIndex
	
	if [[ -n "$_natIndex" ]]; then
		# put _natIndex
		put_nat_binding_index $_natIndex
		echo "put _natIndex($_natIndex)"
	fi
}

nat_get_each_index()
{
	local _natIndex
	config_get _natIndex "$1" natIndex
	
	if [[ -n "$_natIndex" ]]; then
		# refresh natIndex
		_natIndex=$(get_nat_binding_index)
		uci set nat.$1.natIndex=$_natIndex
		echo "write back _natIndex($_natIndex)"
	fi
}

nat_refresh_ipstat_index()
{
	NAT_LOG_PRINT "@ initializing nat ipstat index for nat config"
	
	# only vs&dmz are available in controller mode
	config_load nat
	config_foreach nat_put_each_index rule_vs
	config_foreach nat_put_each_index rule_dmz
	config_foreach nat_get_each_index rule_vs
	config_foreach nat_get_each_index rule_dmz
	uci commit
}

nat_refresh_state()
{
	NAT_LOG_PRINT "@ initializing nat state"

	local list=""
	uci_revert_state nat
	uci_set_state nat core "" nat_state
	uci_set_state nat env "" nat_env_state

	zone_list=$(zone_get_zonelist)
	for zone in ${zone_list}; do
		[[ "$zone" == "VPN" ]] && continue
		ifaces=$(zone_get_wan_ifaces "${zone}" 2>/dev/null)
		for iface in ${ifaces}; do
			NAT_LOG_PRINT "  parsing zone $zone, iface $iface"
			if [[ -n "$iface" && "$iface" != "loopback" ]]; then
				list="$iface $list"
				dev=$(zone_get_device_byif "${iface}")
				uci_set_state nat env ${iface}_dev "$dev"
				network_get_ipaddr if_ipaddr "$iface"
				uci_set_state nat env ${iface}_ip "$if_ipaddr"
				network_get_subnet if_mask "$iface"
				if_mask="${if_mask#*/}"
				uci_set_state nat env ${iface}_mask "$if_mask"
				# network_get_gateway if_gateway "$iface"
				# uci_set_state nat env ${iface}_gateway "$if_gateway"
			fi
		done
	done

	NAT_LOG_PRINT "  all valid iface list: $list"
	uci_set_state nat env if_list "$list"
}

nat_config_rule_operation()
{
	local operation=$1
	local module=$2

	case $module in
		onenat) nat_rule_one_nat_operation $operation;;
		napt)   nat_rule_napt_operation $operation;;
		vs)     nat_rule_vs_operation $operation;;
		pt)     nat_rule_pt_operation $operation;;
		dmz)    nat_rule_dmz_operation $operation;;
		alg)    nat_alg_run $operation;;
		*)
			nat_rule_vs_operation $operation
			nat_rule_pt_operation $operation
			nat_rule_one_nat_operation $operation
			nat_rule_napt_operation $operation
			nat_rule_dmz_operation $operation
			nat_alg_run $operation
		;;
	esac
}

nat_main()
{
	local operation=$1
	local module=$2

	nat_load_global_config

	if [[ "$NAT_SWITCH_ENABLED" == "on" ]]; then
		if [[ -z "$module" ]]; then
			nat_config_rule_operation $operation nat
		else
			nat_config_rule_operation "$@"
		fi

		uci_set_state nat core loaded 1
		uci_set_state nat core enabled 1
		NAT_LOG_PRINT "@ nat is ok"
	fi
}

nat_start()
{
	NAT_LOG_PRINT "################## nat start $1 ##################"
	{
		flock -x 50

		if nat_is_loaded; then
			NAT_LOG_PRINT "! nat was already loaded, exit "
			exit 1
		else
			# load config, initialize nat state and environment
			nat_prepare_env
			nat_refresh_state
			nat_refresh_ipstat_index
			nat_main start "$1"
		fi

		nat_enable_network
		touch $NAT_READY

		flock -u 50
	} 50<>/tmp/nat.lock
}

nat_stop()
{
	NAT_LOG_PRINT "################## nat stop $1 ##################"
	{
		flock -x 50

		nat_disable_network
		nat_prepare_env
		nat_main stop "$1"
		config_clear
		uci_set_state nat core loaded 0
		uci_set_state nat core enabled 0
		rm -rf $NAT_READY

		flock -u 50
	} 50<>/tmp/nat.lock
}

nat_restart()
{
	NAT_LOG_PRINT "################## nat restart $1 ##################"
	{
		flock -x 50

		nat_disable_network
		nat_prepare_env
		nat_main stop "$1"

		# State is no need to refresh when restarting napt.
		if [[ "$1" != "napt" ]]; then
			nat_refresh_state
		fi

		nat_main start "$1"
		nat_enable_network
		touch $NAT_READY

		flock -u 50
	} 50<>/tmp/nat.lock

	# env -i RESTART=on /sbin/hotplug-call nat  	 # Now hotplug event will be set in napt.
}

nat_reload()
{
	NAT_LOG_PRINT "################## nat reload $1 ##################"
	nat_restart "$1"
}
