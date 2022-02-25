#!/bin/sh
#Copyright (C) 2015 tplink.com

[ "$INC_QOS_NF" != "" ] && return
export INC_QOS_NF="INC"

. /lib/qos-tplink/qos_public.sh
. /lib/qos-tplink/qos_mark.sh
. /lib/qos-tplink/qos_grpmark.sh

#### netfilter adapt for qos-tplink
# uplink qos entry point:
#	-A FORWARD -i $LAN_NETDEV -o $WAN_dev -j $chain_LAN_to_WAN
#	-A OUTPUT  -o $WAN_dev -j $chain_LAN_to_WAN
# downlink qos entry point:
#	-A FORWARD -i $WAN_dev -o $LAN_NETDEV -j $chain_WAN_to_LAN
#	-A INPUT  -i $WAN_dev -j $chain_WAN_to_LAN

local IPT=iptables
local TABLE=mangle
local IPT_PREFIX="$IPT -w -t $TABLE"
local QOS_CHAIN="qos_chain_default"
local QOS_TPLIMIT_CHAIN="qos_tplimit"
local QOS_MARK_CHAIN="qos_mark"
local QOS_SFE_CHAIN="sfe_mark"
local QOS_HWNAT_CHAIN="hwnat_mark"

local NFMARK_MUTEX="$QOS_NFMARK_MUTEX"
local NFMARK_MUTEX_MASK="$QOS_NFMARK_MUTEX_MASK"

local XT_FUNCTION_MAXNAMELEN=30
local XT_EXTENSION_MAXNAMELEN=29
local XT_TABLE_MAXNAMELEN=32

qos_nf_sfe_toggle()
{
	local chain="$QOS_CHAIN"
	local isExist=`$IPT_PREFIX -L FORWARD --line | grep -w "$chain" | awk '{print $1}'`

	# should clean hwnat/sfe connections after iptables rules be renewed
	echo qos_nf_sfe_toggle >> /dev/console

	if fastpath_sw_real_on; then
		local sfe_qos="`uci get sfe.module.qos`"
		if [ ${#isExist} -ne 0 ]; then
			# real qos rule exist, "real" means rule is installed in netfilter(iptables)
			# notify sfe that qos is on when in need
			[ $sfe_qos = "off" ] && {
				uci set "sfe.module.qos=on"
				uci commit sfe
				# `/etc/init.d/sfe restart` 2>/dev/null
				xfwdm -F
			}
		else
			# notify sfe that qos is off when in need
			[ $sfe_qos = "on" ] && {
				uci set "sfe.module.qos=off"
				uci commit sfe
				# `/etc/init.d/sfe restart` 2>/dev/null
				xfwdm -F
			}
		fi
	fi

	if fastpath_sw_real_on; then
		xfwdm -F
	fi
	if fastpath_hw_real_on; then
		echo 1 > /sys/kernel/debug/ecm/ecm_db/defunct_all
		[ -e "/etc/init.d/hwnat" ] && hwnat -y
	fi
	if fastpath_sw_real_on; then
		xfwdm -F
	fi
}

# flush all qos chains
#   unmount the target to qos-chains
qos_nf_destroy()
{
	local chain="$QOS_CHAIN"
	qos_mark_flush
	qos_grpmark_flush

	# qos single iface chain flush
	local ln=`$IPT_PREFIX -L FORWARD --line | grep -w "$chain" | awk '{print $1}'`
	[ ${#ln} -ne 0 ] && $IPT_PREFIX -D FORWARD $ln
	$IPT_PREFIX -F $chain 2>/dev/null
	$IPT_PREFIX -X $chain 2>/dev/null

	# extra flush, those not mount in FORWARD
	for chain in `$IPT_PREFIX -S | awk '/-N[ ]qos_.*/ {print $2}'`; do
		$IPT_PREFIX -F $chain 2>/dev/null
		$IPT_PREFIX -X $chain 2>/dev/null
	done

	#QOS_LOG_PRINT "qos_nf_destroy, flush and umount all qos-chains in $TABLE"
}

# # create the qos chain named src_to_dst, if exist, return
# qos_nf_chain_create()
# {
# 	local if_src="$1"
# 	local if_dst="$2"
# 	local mask=$QOS_MARK_MASK
# 	local chain_pare="$QOS_CHAIN"

# 	# create qos_default target to
# 	$IPT_PREFIX -S FORWARD | grep -q -w "\-j $chain_pare" || {
# 		QOS_WRITE_LOG " info, create qos default chain $chain_pare"
# 		QOS_WRITE_LOG "\t$IPT_PREFIX -N $chain_pare 2>/dev/null"
# 		$IPT_PREFIX -N $chain_pare 2>/dev/null
# 		ln=`$IPT_PREFIX  -L FORWARD --line | awk '/zone.*MSSFIX/ {print $1}' | awk 'NR==1'`
# 		[ ${#ln} -ne 0 ] && plus="-I FORWARD $ln" || plus="-A FORWARD"
# 		QOS_WRITE_LOG "\t$IPT_PREFIX $plus -j $chain_pare"
# 		$IPT_PREFIX $plus -j $chain_pare
# 	}

# 	# add target to qos_chain_default
# 	local chain=qos_${if_src}_to_${if_dst}
# 	[ `echo $chain | wc -c` -ge $XT_EXTENSION_MAXNAMELEN ] && QOS_WRITE_LOG " info, $chain exceed XT_EXTENSION_MAXNAMELEN !!! " && return 1
# 	$IPT_PREFIX -S $chain_pare | grep -q -w "\-j $chain" && {
# 		QOS_WRITE_LOG " info, $chain has been created before, skip nf chain create! "
# 		return 0
# 	}

# 	QOS_WRITE_LOG " info, create chain $chain"
# 	QOS_WRITE_LOG "\t$IPT_PREFIX -N $chain 2>/dev/null"
# 	$IPT_PREFIX -N $chain 2>/dev/null || $IPT_PREFIX -F $chain 2>/dev/null

# 	# anti-reentry mechanism
# 	QOS_WRITE_LOG "\t$IPT_PREFIX -A $chain -m mark ! --mark 0/${NFMARK_MUTEX_MASK} -j RETURN"
# 	$IPT_PREFIX -A $chain -m mark ! --mark 0/${NFMARK_MUTEX_MASK} -j RETURN

# 	# insert after qos chain, but ahead MSSFIX
# 	local mode="-A $chain_pare"
# 	QOS_WRITE_LOG "\t$IPT_PREFIX $mode -i $(indirect_var_get ${if_src}_dev) -o $(indirect_var_get ${if_dst}_dev) -j $chain"
# 	$IPT_PREFIX $mode -i $(indirect_var_get ${if_src}_dev) -o $(indirect_var_get ${if_dst}_dev) -j $chain
# 	return 0
# }

# create base qos chains for uplink & downlink in mangle table
#  uplink qos entry point:
#	-A FORWARD -i $LAN_NETDEV -o $WAN_dev -j $chain_LAN_to_WAN
#	-A OUTPUT  -o $WAN_dev -j $chain_LAN_to_WAN
#  downlink qos entry point:
#	-A FORWARD -i $WAN_dev -o $LAN_NETDEV -j $chain_WAN_to_LAN
#	-A INPUT  -i $WAN_dev -j $chain_WAN_to_LAN
qos_nf_init_root()
{
	local ln=`$IPT_PREFIX  -L FORWARD --line | awk '/zone.*MSSFIX/ {print $1}' | awk 'NR==1'`
	local mode="-A FORWARD "
	[ ${#ln} -ne 0 ] && mode="-I FORWARD $ln"
	local mask=$QOS_MARK_MASK

	# new all iface chains
	for iface in $IFACE_LIST; do
		local dev=$(indirect_var_get ${iface}_dev)
		[ "$(valid_dev $dev)" -ne 0 ] && QOS_WRITE_LOG " info, ${iface} dev invalid, skip chain init!"&& continue

		local list="$(indirect_var_get chain_LAN_to_${iface}) $(indirect_var_get chain_${iface}_to_LAN)"
		for chain in $list; do
			local idx=`$IPT_PREFIX -L FORWARD -vn --line | grep -w "$chain" | awk '{print $1}'`
			[ "${#idx}" -ne 0 ] && $IPT_PREFIX -D FORWARD $idx

			QOS_WRITE_LOG "\t$IPT_PREFIX -N $chain"
			$IPT_PREFIX -N $chain 2>/dev/null
			QOS_WRITE_LOG "\t$IPT_PREFIX -A $chain -j CONNMARK --restore-mark "
			QOS_WRITE_LOG "\t$IPT_PREFIX -A $chain -m mark ! --mark 0/$mask -j RETURN"
			$IPT_PREFIX -A $chain -j CONNMARK --restore-mark
			$IPT_PREFIX -A $chain -m mark ! --mark 0/$mask -j RETURN

			if [ "$chain" == "$(indirect_var_get chain_LAN_to_${iface})" ]; then
				QOS_WRITE_LOG "\t$IPT_PREFIX $mode -i $LAN_NETDEV -o $dev -j $chain"
				QOS_WRITE_LOG "\t$IPT_PREFIX -A OUTPUT -o $dev -j $chain"
				$IPT_PREFIX $mode -i $LAN_NETDEV -o $dev -j $chain
				$IPT_PREFIX -A OUTPUT -o $dev -j $chain
			else
				QOS_WRITE_LOG "\t$IPT_PREFIX $mode -i $dev -o $LAN_NETDEV -j $chain"
				QOS_WRITE_LOG "\t$IPT_PREFIX -A INPUT -i $dev -j $chain"
				$IPT_PREFIX $mode -i $dev -o $LAN_NETDEV -j $chain
				$IPT_PREFIX -A INPUT -i $dev -j $chain
			fi
			[ ${#ln} -ne 0 ] && ln=$((ln+1)) && mode="-I FORWARD $ln"
		done
	done

	[ -z $QOS_IFGROUP_SUPPORT ] && return
	for iface in $GRP_LIST; do
		local chain="zone_qos_${iface}"
		local idx=`$IPT_PREFIX -L FORWARD -vn --line | grep -w "$chain" | awk '{print $1}'`
		[ "${#idx}" -ne 0 ] && $IPT_PREFIX -D FORWARD $idx
		$IPT_PREFIX -N $chain 2>/dev/null
		QOS_WRITE_LOG "\t$IPT_PREFIX -A $chain -j CONNMARK --restore-mark"
		QOS_WRITE_LOG "\t$IPT_PREFIX -A $chain -m mark ! --mark 0/$QOS_GMARK_MASK -j RETURN"
		$IPT_PREFIX -A $chain -j CONNMARK --restore-mark
		$IPT_PREFIX -A $chain -m mark ! --mark 0/$QOS_GMARK_MASK -j RETURN
	done
	#QOS_WRITE_LOG " install target qos-chains in ipt-$TABLE done!"
}


# handle to add rule to netfilter qos chain
	# universal for uplink/downlink, determined internally
	# ret: 0 OK
qos_nf_add_rule_old()
{
	local if_src=$1
	local if_dst=$2
	local mark=$3
	local flag=$4
	local iporset=$5
	local ret=1
	local mask=$QOS_MARK_MASK
	local chain_pare=$QOS_CHAIN

	# 1. get the chain by src and dst
		# check if chain is valid
	local chain=qos_${if_src}_to_${if_dst}
	$IPT_PREFIX -S $chain_pare | grep -q -w "\-j $chain" || {
		QOS_WRITE_LOG " error, qos_nf_add_rule $chain invalid "
		QOS_RET "$ret" && return 1
	}

	#QOS_WRITE_LOG "  qos_nf_add_rule, add target nfmark $mark item to $chain"

	# 2. set up items by flag
		# chose sip or dip by up/down
	[ -z $QOS_CONFIG_ER ] || {
		local rule=$(qos_mark2rule $mark)
		local ip_type=$(config_get $rule "ip_type")
		[ "$ip_type" != "src" -a "$ip_type" != "dst" ] && ip_type="src"
	}

	local mt_target=""
	if [ "$flag" = "ip" ]; then
		mt_target="--destination ${iporset} "
		[ `echo $chain | grep -c "qos_${LAN_IFACE_NAME}_to"` -gt 0 ] && mt_target="--source ${iporset} "
		[ "$ip_type" = "src" ] && mt_target="--source ${iporset} "
	elif [ "$flag" = "ipset_share" ]; then
		mt_target="-m set --match-set ${iporset} dst "
		[ `echo $chain | grep -c "qos_${LAN_IFACE_NAME}_to"` -gt 0 ] && mt_target="-m set --match-set ${iporset} src "
		[ "$ip_type" = "src" ] && mt_target="-m set --match-set ${iporset} src "
	else
		# IPGROUP_ANY
		QOS_WRITE_LOG "CAUTION, this is a IPGROUP_ANY rule!"
	fi

	# 3. new nf list
	#local mt_ct_new="-m conntrack --ctstate NEW"
	local mark_set="-j MARK --set-mark ${mark}/${mask}"
	local ctmark_save="-j CONNMARK --save-mark --nfmask $mask --ctmask $mask"
	QOS_WRITE_LOG "\t$IPT_PREFIX -A $chain $mt_target $mt_ct_new $mark_set"
	QOS_WRITE_LOG "\t$IPT_PREFIX -A $chain $mt_target $mt_ct_new $ctmark_save"
	$IPT_PREFIX -A $chain $mt_target $mt_ct_new $mark_set
	$IPT_PREFIX -A $chain $mt_target $mt_ct_new $ctmark_save

	QOS_RET 0
}

# setup a new handle to add rule
qos_nf_add_rule()
{
	local if_src="$1"
	local if_dst="$2"
	local rule="$3"
	local rate="$4"
	local flag="$5"
	local iporset="$6"

	local chain="$QOS_CHAIN"

	# create qos_default target to
	$IPT_PREFIX  -L FORWARD --line | grep -q -w "$chain" || {
		QOS_WRITE_LOG " info, create qos default chain $chain"
		QOS_WRITE_LOG "\t$IPT_PREFIX -N $chain 2>/dev/null"
		$IPT_PREFIX -N $chain 2>/dev/null

		# anti-reentry mechanism
		QOS_WRITE_LOG "\t$IPT_PREFIX -A $chain -m mark ! --mark 0/${NFMARK_MUTEX_MASK} -j RETURN"
		$IPT_PREFIX -A $chain -m mark ! --mark 0/${NFMARK_MUTEX_MASK} -j RETURN

		# global fastpath mark.
		$IPT_PREFIX -A $chain -m tplimit --rate 1000000 --maskbit $QOS_NFMARK_MUTEX_START --info global -j DROP

		ln=`$IPT_PREFIX  -L FORWARD --line | awk '/zone.*MSSFIX/ {print $1}' | awk 'NR==1'`
		[ ${#ln} -ne 0 ] && plus="-I FORWARD $ln" || plus="-A FORWARD"
		QOS_WRITE_LOG "\t$IPT_PREFIX $plus -j $chain"
		$IPT_PREFIX $plus -j $chain
	}

	#local mt_netdev="-i $(indirect_var_get ${if_src}_dev) -o $(indirect_var_get ${if_dst}_dev)"
	local mt_netdev="-m set --match-set $(zone_group ${if_src}) src -m set --match-set $(zone_group ${if_dst}) dst"

	[ -z $QOS_CONFIG_ER ] || {
		local ip_type=$(config_get $rule "ip_type")
		[ "$ip_type" != "src" -a "$ip_type" != "dst" ] && ip_type="src"
	}
	local mt_user=""
	local mt_limit="-m tplimit --rate ${rate/kbps/} --type share --maskbit $QOS_NFMARK_MUTEX_START --info $rule"
	if [ "$flag" = "ip" ]; then
		mt_user="--destination ${iporset} "
		[ "$ip_type" = "src" ] && mt_user="--source ${iporset} "
	elif [ "$flag" = "ipset_priv" ]; then
		# in tplimit priv mode, setup the tplimit to priv mode by --type
		mt_user="-m set --match-set ${iporset} $ip_type "
		mt_limit="-m tplimit --rate ${rate/kbps/} --type $ip_type --maskbit $QOS_NFMARK_MUTEX_START --info $rule"
	elif [ "$flag" = "ipset_share" ]; then
		mt_user="-m set --match-set ${iporset} $ip_type"
	else
		# IPGROUP_ANY, mt_user no need
		QOS_WRITE_LOG " CAUTION, $rule is a IPGROUP_ANY rule!"

		# even though is IPGROUP_ANY, allow to be priv mode now
		# be careful that if there is too many ip and over xt_tplimit cell_mempool, ip that overflow could not be qos
		local mode=$(config_get $rule "mode")
		[ "$mode" != "share" -a "$mode" != "priv" ] && mode="share"
		[ "$mode" = "priv" ] && {
			mt_limit="-m tplimit --rate ${rate/kbps/} --type $ip_type --maskbit $QOS_NFMARK_MUTEX_START --info $rule"
		}
	fi

	# determine insert index
	# local insert_index=2
	# local installed_rules=`$IPT_PREFIX -nL $chain --line | grep -w "rate.*type.*maskbit.*, info" | awk '{print $NF}'`
	# local install_rule_index=`cat ${QOS_TMP_DIR}/rules_order | grep -w "${rule}$" | awk '{print $1}'`
	# [ -z "$installed_rules" ] || {
	#    for installed_rule in $installed_rules; do
	# 	    installed_rule_index=`cat ${QOS_TMP_DIR}/rules_order | grep -w "${installed_rule}$" | awk '{print $1}'`
	# 	    [ $installed_rule_index -gt $install_rule_index ] && {
	# 		    break
	# 	    }
	# 	    let insert_index++
	#    done
	# }

	local insert="-A $chain"
	$IPT_PREFIX -nL $chain --line | sed -e '1,4d' | grep -w "rate.*type.*maskbit.*, info" | awk '{print $NF}' > ${QOS_TMP_DIR}/installed_file 2>/dev/null

	lua /lib/qos-tplink/find_index.lua ${rule}

	local insert_index=`cat ${QOS_TMP_DIR}/insert_index`
	[ ${insert_index} -gt 0 ] && {
		insert_index=$((insert_index-1))
		insert_index=$((insert_index*2))
		let insert_index++
		let insert_index++
		let insert_index++
		insert="-I $chain $insert_index"
	}

	if fastpath_sw_on; then
		$IPT_PREFIX $insert $mt_netdev $mt_user -m comment --comment $rule -j $QOS_SFE_CHAIN
	elif fastpath_hw_on; then
		$IPT_PREFIX $insert $mt_netdev $mt_user -m comment --comment $rule -j $QOS_HWNAT_CHAIN
	fi

	QOS_WRITE_LOG "\t$IPT_PREFIX $insert $mt_netdev $mt_user $mt_limit -j DROP"
	$IPT_PREFIX $insert $mt_netdev $mt_user $mt_limit -j DROP

	return 0
}

# delete the item defined by the nfmark from nf qos chain
	# nfmark is get from mark.data with arg rule_name
qos_nf_del_rule()
{
	local rule="$1"
	local chain="$QOS_CHAIN"

	local idx=`$IPT_PREFIX -nvL $chain --line | sed -e '1,4d' | grep -w "rate.*type.*maskbit.*, info[ ]$rule" | awk '{print $1}'`
	[ ${#idx} -ne 0 ] && {
		$IPT_PREFIX -D $chain $idx

		# delete sfe xfwdm mark rule
		( fastpath_sw_on || fastpath_hw_on ) && {	
			idx=`$IPT_PREFIX -nvL $chain --line | sed -e '1,4d' |  grep -w "/\* $rule \*/" | awk '{print $1}'`
			[ ${#idx} -ne 0 ] && $IPT_PREFIX -D $chain $idx
		}

		# IF $QOS_CHAIN is empty, smash it and delete target from FORWARD
		[ `$IPT_PREFIX -S $chain | awk 'END{print NR}'` = 2 ] && {
			QOS_WRITE_LOG " info, $chain is empty, should destroy! "
			local i=`$IPT_PREFIX -L FORWARD --line | grep -w "$chain" | awk '{print $1}'`
			[ ${#i} -ne 0 ] && $IPT_PREFIX -D FORWARD $i
			$IPT_PREFIX -F $chain
			$IPT_PREFIX -X $chain
		}
	}

	QOS_RET 0 && return 0
}

# delete all items/chains concerned by iface
qos_nf_del_rule_byiface()
{
	local iface="$1"
	local chain_pare="$QOS_CHAIN"
	QOS_WRITE_LOG " info, delete all nf items concerned by $iface"

	# 1. delete chain target
	local list=`$IPT_PREFIX -L $chain_pare --line | grep "qos_.*${iface}.*" | awk '{print $2}'`
	for chain in $list; do
		# nf item must delete in reverse order, SO plus `tac`
		for idx in `$IPT_PREFIX -L $chain_pare --line | grep -w "$chain" | awk '{print $1}' | tac`; do
			$IPT_PREFIX -D $chain_pare $idx 2>/dev/null
		done

		# 2. flush and delete chain
		$IPT_PREFIX -F $chain 2>/dev/nul
		$IPT_PREFIX -X $chain 2>/dev/nul
	done
}

##################################################################################
# single $0 sh debug mode
if [ "$1" = "nfdebug" ];then

	QOS_INFO_PRINT "##############  enter $0 debug mode  ##############"
	if [ $2 = "flush" ];then
		QOS_INFO_PRINT " ### debug, flush netfilter qos chains"
		qos_nf_destroy

	elif [ $2 = "init" ];then
		QOS_INFO_PRINT " ### debug, init netfilter qos chains "
		qos_nf_destroy
		qos_nf_init_root

	elif [ $2 = "create" ];then
		QOS_INFO_PRINT " ### debug, create netfilter qos chain "
		qos_nf_destroy
		src="$3"
		dst="$4"
		qos_nf_chain_create $src $dst


	elif [ $2 = "addrule" ]; then
		QOS_INFO_PRINT " ### debug, netfilter add qos rule "
		qos_nf_add_rule LAN WAN1 100 "ip" "1.1.1.1"
		qos_nf_add_rule LAN WAN2 200 "set" myset2

		qos_nf_add_rule WAN1 LAN 101 "set" myset1
		qos_nf_add_rule WAN2 LAN 202 "ip" "2.2.2.2"

	elif [ $2 = "delrule" ]; then
		#mark="$3"
		#QOS_INFO_PRINT " ### debug, netfilter del qos rule mark $mark"
		#qos_nf_del_rule $mark
		#qos_nf_del_rule "257 258 263"
		qos_nf_del_rule_byiface WAN1
	fi

fi
