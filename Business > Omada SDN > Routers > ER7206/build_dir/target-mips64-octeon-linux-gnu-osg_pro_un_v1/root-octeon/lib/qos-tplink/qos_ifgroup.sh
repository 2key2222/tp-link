#!/bin/sh
#Copyright (C) 2015 tplink.com

[ "$INC_QOS_IFGROUP" != "" ] && return
export INC_QOS_IFGROUP="INC"

. /lib/qos-tplink/qos_public.sh
# . /lib/qos-tplink/qos_tc.sh
. /lib/qos-tplink/qos_nf.sh
. /lib/qos-tplink/qos_grpmark.sh

##### ifgroup adapt for qos-tplink, in order NOT to pollute the iface qos flow frame
	# all ifgroup scripts in this file
# local PRIO_FLT_G=1
# local IFG_MARK_CHAIN="qos_ifgroup"
# local NFMARK_MUTEX_IFG="$QOS_NFMARK_MUTEX_IFG"
# local NFMARK_MUTEX_IFG_MASK="$QOS_NFMARK_MUTEX_IFG_MASK"

local NFMARK_MUTEX="$QOS_NFMARK_MUTEX"
local NFMARK_MUTEX_MASK="$QOS_NFMARK_MUTEX_MASK"
local QOS_SFE_CHAIN="sfe_mark"
local QOS_HWNAT_CHAIN="hwnat_mark"

# # create chain for ifgroup rule
# #    for ifgroup qos, band limit will be realized in xt_tplimit, thus NO need tc participate.
# #    all ifgroup rules mount under qos_ifgroup
# ifgroup_nf_chain_create()
# {
# 	local if_src="$1"
# 	local if_dst="$2"
# 	local rule="$3"
# 	local chain="$IFG_MARK_CHAIN"
# 	local mask=$QOS_GMARK_MASK
# 	local chain_pare="$QOS_CHAIN"

# 	# create qos_default target to
# 	$IPT_PREFIX  -L FORWARD --line | grep -q -w "$chain_pare" || {
# 		QOS_WRITE_LOG " info, create qos default chain $chain_pare"
# 		QOS_WRITE_LOG "\t$IPT_PREFIX -N $chain_pare 2>/dev/null"
# 		$IPT_PREFIX -N $chain_pare 2>/dev/null
# 		ln=`$IPT_PREFIX  -L FORWARD --line | awk '/zone.*MSSFIX/ {print $1}' | awk 'NR==1'`
# 		[ ${#ln} -ne 0 ] && plus="-I FORWARD $ln" || plus="-A FORWARD"
# 		QOS_WRITE_LOG "\t$IPT_PREFIX $plus -j $chain_pare"
# 		$IPT_PREFIX $plus -j $chain_pare
# 	}

# 	# init ifgroup chain
# 	`$IPT_PREFIX -S $chain_pare | grep -q "\-j[ ]${chain}"` || {

# 		QOS_WRITE_LOG " info, create chain $chain"
# 		QOS_WRITE_LOG "\t$IPT_PREFIX -N $chain 2>/dev/null"
# 		$IPT_PREFIX -N $chain 2>/dev/null

# 		QOS_WRITE_LOG "\t$IPT_PREFIX -A $chain -m mark ! --mark 0/${NFMARK_MUTEX_IFG_MASK} -j RETURN"
# 		$IPT_PREFIX -A $chain -m mark ! --mark 0/${NFMARK_MUTEX_IFG_MASK} -j RETURN
# 	}

# 	# add target to $chain
# 	# get the index to insert or add, qos target MUST ahead TCPMSS target
# 	# make sure the ifgroup target ahead  single if rule target
# 	#local ln=`$IPT_PREFIX -L $chain_pare --line | awk '/qos_.*_to_.*/ {print $1}' | awk 'NR==1'`

# 	local insert_index=1
# 	local installed_rules=`$IPT_PREFIX -nL $chain_pare --line | grep -w "input.*output.*info" | awk '{print $NF}'`
# 	local install_rule_index=`cat ${QOS_TMP_DIR}/rules_order | grep -w $rule | awk '{print $1}'`
# 	[ -z "$installed_rules" ] || {
# 	   for installed_rule in $installed_rules; do
# 		    installed_rule_index=`cat ${QOS_TMP_DIR}/rules_order | grep -w $installed_rule | awk '{print $1}'`
# 		    [ $installed_rule_index -gt $install_rule_index ] && {
# 			    break
# 		    }
# 		    let insert_index++
# 	   done
# 	}

# 	local mode="-I $chain_pare $insert_index"

# 	local mt_netdev="-m multinetdev "
# 	local dev_list=""
# 	for iface in $if_src; do
# 		dev_list="$dev_list,$(indirect_var_get ${iface}_dev)"
# 	done
# 	mt_netdev="$mt_netdev --in `echo $dev_list | sed 's/^,//'`"
# 	local dev_list=""
# 	for iface in $if_dst; do
# 		dev_list="$dev_list,$(indirect_var_get ${iface}_dev)"
# 	done
# 	mt_netdev="$mt_netdev --out `echo $dev_list | sed 's/^,//'` --info $rule"

# 	QOS_WRITE_LOG "\t$IPT_PREFIX $mode $mt_netdev -j $chain 2>/dev/null"
# 	$IPT_PREFIX $mode $mt_netdev -j $chain 2>/dev/null

# 	return 0
# }

# setup a new handle to add rule
ifgroup_nf_add_rule()
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

	[ -z $QOS_CONFIG_ER ] || {
		local ip_type=$(config_get $rule "ip_type")
		[ "$ip_type" != "src" -a "$ip_type" != "dst" ] && ip_type="src"
	}

	#local mt_netdev="-m multinetdev "
	#local dev_list=""
	#for iface in $if_src; do
	#	dev_list="$dev_list,$(indirect_var_get ${iface}_dev)"
	#done
	#mt_netdev="$mt_netdev --in `echo $dev_list | sed 's/^,//'`"
	#local dev_list=""
	#for iface in $if_dst; do
	#	dev_list="$dev_list,$(indirect_var_get ${iface}_dev)"
	#done
	#mt_netdev="$mt_netdev --out `echo $dev_list | sed 's/^,//'`"
	local mt_netdev="-m set --match-set $(zone_group ${if_src}) src -m set --match-set $(zone_group ${if_dst}) dst"

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

	QOS_WRITE_LOG "\t$IPT_PREFIX $insert $mt_netdev $mt_user $mt_limit -j DROP 2>/dev/null"
	$IPT_PREFIX $insert $mt_netdev $mt_user $mt_limit -j DROP

	return 0
}

# qos user rule config on TC and netfilter  positive direction for both ER and 450G
	#ret: 0 OK
ifgroup_rule_install_raw()
{
	local if_src="$1"
	local if_dst="$2"
	local rule_name="$3"
	local rate="$4"
	local flag="$5"     # if a single IP or a ip_group name ip/ipset_share/ipset_priv
	local iporset="$6"      ##### $7 is ip or set determined by flag

	# 1. if rate no value, skip this step
	if [ 0 -eq `echo $rate | sed 's/[a-z A-Z]//g'` ]; then
		QOS_WRITE_LOG "  ifgroup_rule_install_raw, NO limit for rule $rule_name on $if_src -> $if_dst, skip "
		QOS_RET 0
		return 0
	fi

	ifgroup_nf_add_rule "$if_src" "$if_dst" $rule_name $rate $flag $iporset || {
		QOS_WRITE_LOG "  ifgroup_rule_install_raw, add rule $rule_name fail! "
		QOS_RET 1
		return 1
	}

	return 0
}

ifgroup_nf_del_rule()
{
	local rule="$1"
	local chain="$QOS_CHAIN"

	local idx=`$IPT_PREFIX -nvL $chain --line | sed -e '1,4d' |  grep -w "rate.*type.*maskbit.*, info[ ]$rule" | awk '{print $1}'`
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

ifgroup_rule_uninstall_raw()
{
	local rule="$1"
	QOS_WRITE_LOG " uninstall ifgroup rule $rule ... "

	ret=$(ifgroup_nf_del_rule "$rule")

	return 0
}

##################################################################################
# single $0 sh debug mode
if [ "$1" = "ifgrpdebug" ];then
	QOS_INFO_PRINT "##############  enter $0 debug mode  ##############"

	if [ $2 = "install" ];then
		QOS_INFO_PRINT " ### debug, install ifgroup rule"


	elif [ $2 = "uninstall" ];then
		QOS_INFO_PRINT " ### debug, uninstall ifgroup rule"

	fi

fi
