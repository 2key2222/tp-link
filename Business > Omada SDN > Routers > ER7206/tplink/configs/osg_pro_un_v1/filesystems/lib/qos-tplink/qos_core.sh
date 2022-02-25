#!/bin/sh
#Copyright (C) 2015 tplink.com

[ "$INC_QOS_CORE" != "" ] && return
export INC_QOS_CORE="INC"

. /lib/qos-tplink/qos_public.sh
[ -z $QOS_IFGROUP_SUPPORT ] || . /lib/qos-tplink/qos_ifgroup.sh
. /lib/qos-tplink/qos_tc.sh
. /lib/qos-tplink/qos_nf.sh

############################################################################

####
#qos_config_get_ip      # get ip, transfer list to ip
#qos_config_get_port    # get port, transfer list to port

# get the whole option from section
qos_config_get_section()
{
	local cfg=$1
	local sect=$2;
	echo "###debug, get sect $sect of cfg $cfg!"
}

# create tc and nf root for zone&dev, which has NOT init before
	# for which was init, just skip.
# This is A reenterable handle
qos_global_init()
{
	local qos_enable=""

	# 1. if QOS module is enabled?
	config_get qos_enable "$SNAME_GLOBAL" "qos_enable"
	[ "$qos_enable" != "on" ] && QOS_WRITE_LOG " QOS disable, NO need config, just return! " &&  QOS_RET 1 && return
	QOS_WRITE_LOG "qos_global_init, begin ..."

	# 2. prepare dependence for QOS  - kmods , ipt-chains
	[ -z $QOS_TPLIMIT_ALL ] && qos_kmod_load

	[ ${#IFACE_LIST} -eq 0 ] && {
		QOS_WRITE_LOG " info, NO user interface find, can not config QOS!"
		QOS_RET 2
		return
	}
	QOS_STATE set qos_enable "on"
	QOS_STATE set iface_list "$IFACE_LIST"
	for iface in $IFACE_LIST; do
		# MUST set the dev txqueuelen NON-zero, it affect the pfifo_fast performance
		#ifconfig "$(indirect_var_get ${iface}_dev)" txqueuelen 500 2>/dev/null

		QOS_STATE set ${iface}.t_name $iface
		QOS_STATE set ${iface}.uplink "$(config_get $iface  uplink)"
		QOS_STATE set ${iface}.downlink "$(config_get $iface  downlink)"
	done

	# init tc ROOT on lan dev, only for 450G
	[ -z $QOS_CONFIG_ER ] && qos_tc_init

	QOS_WRITE_LOG "qos_global_init, global ok!"
	QOS_RET 0
}

# qos user rule config on TC and netfilter  positive direction for both ER and 450G
	#ret: 0 OK
qos_rule_install_raw_old()
{
	local if_src=$1
	local if_dst=$2
	local rule_name=$3
	local rate=$4
	local flag=$5     # if a single IP or a ip_group name ip/ipset_share/ipset_priv
	local iporset=$6      ##### $7 is ip or set determined by flag
	local ret=1;

	# 1. if rate no value, skip this step
	if [ 0 -eq ${rate/[^0-9]*/} ]; then
		QOS_WRITE_LOG "  qos_rule_install_raw, NO limit for rule $rule_name on $if_src -> $if_dst, skip "
		return 0
	fi

	# 2. create limit on direction $src -> $dst
	# 2.1 single IP or ipset_share mode, establish A tc leaf and A nf item
	local dev=$(indirect_var_get ${if_dst}_dev)
	if [ "$flag" != "ipset_priv" ]; then
		# 2.1.1 set up a tc tree leaf
		#QOS_WRITE_LOG "  qos_rule_install_raw, set up limit $rate on $dev "
		nfmark=$(qos_tc_add_rule $dev $rule_name $rate)
		[ $nfmark = 0 ] && QOS_WRITE_LOG " error, qos_rule_install_raw add rule $rule_name fail, exceed support SPEC!"\
		&& QOS_RET 1 && return 1
		#QOS_WRITE_LOG "    returned nfmark = $nfmark"

		# 2.1.2 set up A nf mark item
		#QOS_WRITE_LOG "    $iporset nf mark item add"
		ret=$(qos_nf_add_rule $if_src $if_dst $nfmark $flag $iporset)

	# 2.2 ipset_priv mode, set number of tc leafs and nf items
	else
		#QOS_WRITE_LOG "  qos_rule_install_raw, set up ip_group priv mark items "
		# 2.2.1 get the ips in the set
		local iplist=`ipset list "$iporset" | awk 'NR>7 {print $1}'`
		[ ${#iplist} -eq 0 ] && QOS_WRITE_LOG " ipset $iporset has NO member!" && return 0
		for item in $iplist; do
			# 2.2.2 set up a tc tree leaf
			#QOS_WRITE_LOG "    ip_group $iporset - $ip tc leaf add"

			## adapt the ipgroup with nethash, transer ip/mask to list
			local list="$item"
			[ `echo $item | grep -c "/"` -gt 0 ] && which net2ip >/dev/null && list=`net2ip "$item"`
			for ip in $list; do
				nfmark=$(qos_tc_add_rule $dev $rule_name $rate)
				[ $nfmark = 0 ] && QOS_WRITE_LOG "    error, add rule $rule_name fail, exceed support SPEC $QOS_CELL_SPEC!" \
				&& QOS_RET 1 && return 1
				#QOS_WRITE_LOG "    returned nfmark = $nfmark"

				# 2.2.3 set up a nf mark item
				#QOS_WRITE_LOG "    ip_group $iporset - $ip nf mark item add"
				flag="ip" # MUST set flag to ip, used by nf item --dest $ip
				ret=$(qos_nf_add_rule $if_src $if_dst $nfmark $flag $ip)
			done
		done
	fi

	return 0
}

qos_rule_install_raw()
{
	local if_src="$1"
	local if_dst="$2"
	local rule_name="$3"
	local rate="$4"
	local flag="$5"     # if a single IP or a ip_group name ip/ipset_share/ipset_priv
	local iporset="$6"      ##### $7 is ip or set determined by flag

	# 1. if rate no value, skip this step
	if [ 0 -eq ${rate/[^0-9]*/} ]; then
		QOS_WRITE_LOG "  qos_rule_install_raw, NO limit for rule $rule_name on $if_src -> $if_dst, skip "
		QOS_RET 0
		return 0
	fi

	qos_nf_add_rule "$if_src" "$if_dst" $rule_name $rate $flag $iporset || {
		QOS_WRITE_LOG "  qos_rule_install_raw, add rule $rule_name fail! "
		QOS_RET 1
		return 1
	}

	return 0
}


# config one rule for qos module
    # ret: 0 ok,  1 err.  (err condition is only SPEC exceed!)
qos_rule_install()
{
    local rule_name="$1"
	local group_rule="" # IF rule is a ifgroup rule

	QOS_WRITE_LOG " install rule $rule_name ... "
	[ "$(QOS_STATE get ${rule_name}.install)" = "true" ] && {
		QOS_WRITE_LOG " info, rule $rule_name has alreay install, skip !" && QOS_RET 0 && return 1
	} || {
		qos_grpmark_get $rule_name &&
		QOS_WRITE_LOG " info, rule $rule_name has alreay install, skip !" && QOS_RET 0 && return 1
	}

	# IF iface is valid ?
	# Temp fix now!! if we add the invalid iface rule in iptables, it doesn't matter.
	# Here we have lots of ifaces and if one down, the whole rule install will be skipped.
	# So the codes below to skip rule install must be comment out !! Until we found more effect way to due with this problem.
	config_get if_ping "$rule_name" "if_ping"
	[ "$if_ping" = "WAN_ALL" ] && {
		local list=""
		local if_ping=""
		config_get list "$SNAME_GLOBAL" "$STYPE_IFACE"
		for iface in $list;do
			[ $iface != "LAN" ] && {
				[ -z "$if_ping" ] && if_ping="$iface" || if_ping="$if_ping $iface"
			}
		done
	}
	[ ${#if_ping} -eq 0 ] && QOS_WRITE_LOG " info, inf_ping not set, skip !" && QOS_RET 0 && return 1
	# for iface in $if_ping; do
	# 	 [ "$(valid_zone "$iface")" -ne 0 ] && QOS_WRITE_LOG " info, rule's if_ping $iface invalid, skip !" && QOS_RET 0 && return 1
	# done
	config_get if_pong "$rule_name" "if_pong"
	[ "$if_pong" = "WAN_ALL" ] && {
		local list=""
		local if_pong=""
		config_get list "$SNAME_GLOBAL" "$STYPE_IFACE"
		for iface in $list;do
			[ $iface != "LAN" ] && {
				[ -z "$if_pong" ] && if_pong="$iface" || if_pong="$if_pong $iface"
			}
		done
	}
	[ ${#if_pong} -eq 0 ] && QOS_WRITE_LOG " info, if_pong not set, skip !" && QOS_RET 0 && return 1
	# for iface in $if_pong; do
	#	 [ "$(valid_zone "$iface")" -ne 0 ] && QOS_WRITE_LOG " info, rule's iface $iface invalid, skip !" && QOS_RET 0 && return 1
	# done
	[ "$if_ping" = "$if_pong" ] && QOS_WRITE_LOG " info, rule's iface src = dst invalid, skip !" && QOS_RET 0 && return 1

	# 2. get all options from a rule section
	config_get rate "$rule_name" "rate_max"
	[ "$rate" = "" ] && rate="0kbps"
	rate="${rate/[^0-9]*/}kbps"
	[ -z $QOS_CONFIG_ER ] && {
		config_get downrate "$rule_name" "rate_max_mate"
		[ "$downrate" = "" ] && downrate="0kbps"
		downrate="${downrate/[^0-9]*/}kbps"
	}
	[ "$rate" = "0kbps" -a "$downrate" = "0kbps" ] && QOS_WRITE_LOG " info, rule bandwidth not assigned! skip install" && QOS_RET 0 && return 1

	config_get ip "$rule_name" "ip"
	config_get ip_group "$rule_name" "ip_group"
	if [ "$ip_group" != "" ]; then
		# add adapt for IPGROUP_ANY, this means NO consider ipaddr
		[ "$ip_group" != "IPGROUP_ANY" ] && {
			[ `ipset list -n | grep -cw "$ip_group"` -eq 0 ] && QOS_WRITE_LOG " error, rule ip_group $ip_group NOT exist in system! " && QOS_RET 0 && return 1
			[ "$ip" != "" ] && QOS_WRITE_LOG " error, ip & ip_group coexist illegal! next" && QOS_RET 0 && return 1
		}
	else
		[ "$ip" = "" ] && QOS_WRITE_LOG " error, ip & ip_group NOT found! next" && QOS_RET 0 && return 1
	fi

	############## IF this is an ifgroup rule, iump into the branch    BEGIN
	if [ `echo "$if_pong" | wc -w` -gt 1 -o `echo "$if_ping" | wc -w` -gt 1 ]; then
		group_rule="true"
		QOS_WRITE_LOG " !!!!!!!!info, rule $rule_name is an ifgroup rule!"
		[ -z $QOS_IFGROUP_SUPPORT ] && QOS_WRITE_LOG "  NO permission ifgroup rule now! "&& QOS_RET 0 && return 1
	# 	ifgroup_nf_chain_create "${if_ping}" "${if_pong}" "$rule_name" || {
	# 		QOS_WRITE_LOG "  error, ifgroup_nf_chain_create fail! "&& QOS_RET 0 && return 2
	#	}
	# else
	#	# single iface rule use tplimit
	#	qos_nf_chain_create "$if_ping" "$if_pong" || {
	#		QOS_WRITE_LOG "  info, rule init nf chain fail, skip! "&& QOS_RET 0 && return 2
	#	}
	else
		dev_pong=$(indirect_var_get ${if_pong}_dev)
		dev_ping=$(indirect_var_get ${if_ping}_dev)
		if [ `echo ${dev_pong//,/ } | wc -w` -gt 1 -o `echo ${dev_ping//,/ } | wc -w` -gt 1 ]; then
			group_rule="true"
		fi
	fi

	# 4. uplink and downlink config
	local flag=""
	local ip_set=""
	if [ "$ip" != "" -a "$ip_group" = "" ]; then
		# single IP mode, no concern option $mode
		QOS_WRITE_LOG "\t single IP limit mode"
		flag="ip"
		ip_set="$ip"
	elif [ "$ip_group" != "" -a "$ip" = "" -a "$ip_group" != "IPGROUP_ANY" ]; then
		local flag="ip_group"
		config_get mode "$rule_name" "mode"
		[ "$mode" != "share" -a "$mode" != "priv" ] && mode="share"
		flag="ipset_share"
		[ "$mode" = "priv" ] && flag="ipset_priv"
		QOS_WRITE_LOG " rule is $ip_group $flag limit mode"
		ip_set="$ip_group"
	elif [ "$ip_group" == "IPGROUP_ANY" ]; then
		# IPGROUP_ANY
		flag="ipset_any"
		ip_set="$ip_group"
	else
		QOS_WRITE_LOG "  error, rule $rule_name illegal, ip & ip_group! next"
	fi

	local handle=qos_rule_install_raw
	[ ${#group_rule} -ne 0 ] && handle=ifgroup_rule_install_raw
	$handle "$if_ping" "$if_pong" "$rule_name" "$rate" "$flag" "$ip_set" || {
		QOS_WRITE_LOG "  error, qos_rule_install $rule_name limit fail"
		QOS_RET 1 && return 1
	}
	[ -z $QOS_CONFIG_ER ] && {
		$handle "$if_pong" "$if_ping" "$rule_name" "$downrate" "$flag" "$ip_set" || {
			QOS_WRITE_LOG "  error, qos_rule_install $rule_name downlink limit fail"
			QOS_RET 1
			return 1
		}
	}

	QOS_STATE set ${rule_name}.install true

	return 0
}

# uninstall rule_list from tc and nf  for time manager response handle
qos_rule_uninstall_raw_old()
{
	local rule="$1"
	QOS_WRITE_LOG " uninstall rule $rule ... "
#	for rule in $rule_list; do
		# get nfmark and tcid alloced for rule
		local mark_list=$(qos_mark_get $rule)
#QOS_LOG_PRINT " @@@@@ marks: $mark_list"
		[ "${#mark_list}" -eq 0 ] && QOS_WRITE_LOG "  info, rule $rule NOT install nfmark" && QOS_RET 0 && return 1
		ret=$(qos_nf_del_rule "$mark_list")

		local cid_list=$(qos_tcid_get $rule)
#QOS_LOG_PRINT " @@@@@ cids: $cid_list"
		[ "${#cid_list}" -eq 0 ] && QOS_WRITE_LOG "  info, rule $rule NOT install tcid" && QOS_RET 0 && return 1

		local list="if_pong"
		[ -z $QOS_CONFIG_ER ] && list="$list if_ping" ##### for 450G, also delete tc rules of downlink direction
		local dev_list=""
		for opt in $list; do
			for iface in $(QOS_STATE get "${rule}.${opt}"); do
				local dev=$(indirect_var_get ${iface}_dev)
#QOS_LOG_PRINT " @@@@@ iface $iface, dev $dev"
				### for timeobj response, devs are always valid!;
				### for ifdown dev is not exist, but no matter, ifup'll setup with the right dev
				#[ $(valid_dev $dev) -ne 0 ] && QOS_WRITE_LOG "  info, rule $iface $dev not valid" && QOS_RET 1 && return
				dev_list="$dev_list $dev"
			done
		done
#QOS_LOG_PRINT " @@@@@ devs: $dev_list"
		ret=$(qos_tc_del_rule "$dev_list" "$mark_list" "$cid_list")
#	done

	ret=$(qos_mark_free "$rule")
	ret=$(qos_tcid_free "$rule")
	QOS_RET 0 && return 0
}

qos_rule_uninstall_raw()
{
	local rule="$1"
	QOS_WRITE_LOG " uninstall qos rule $rule ... "

	ret=$(qos_nf_del_rule "$rule")

	return 0
}

# support siface or giface rule uninstall
qos_rule_uninstall()
{
	local rule="$1"

	[ "$(QOS_STATE get ${rule}.install)" != "true" ]  && QOS_WRITE_LOG "  info, rule $rule NOT install" && QOS_RET 0 && return 1

	cb=qos_rule_uninstall_raw
	# [ "`echo $(QOS_STATE get ${rule}.if_ping)`" = "WAN_ALL" -o \
	# "`echo $(QOS_STATE get ${rule}.if_pong)`" = "WAN_ALL" ] && cb=ifgroup_rule_uninstall_raw

	$cb $rule && QOS_STATE set ${rule}.install false || return 1

	return 0
}

##################################################################################
# single $0 sh debug mode
if [ "$1" = "coredebug" ];then
	QOS_INFO_PRINT "##############  enter $0 debug mode  ##############"
	if [ $2 = "init" ]; then
		[ -z $QOS_TPLIMIT_ALL ] && qos_tc_destroy
		qos_nf_destroy
		qos_global_init

	elif [ $2 = "uninstall" ];then
		echo -e " @@@@ qos rule uninstall test! "
		local rule="$3"
		qos_rule_uninstall $rule

	elif [ $2 = "install" ];then
		echo -e " @@@@ qos rule install test! "
		local rule="$3"
		qos_rule_install $rule

	else
		echo -e "NO support arg 2 by $0"
	fi
fi


