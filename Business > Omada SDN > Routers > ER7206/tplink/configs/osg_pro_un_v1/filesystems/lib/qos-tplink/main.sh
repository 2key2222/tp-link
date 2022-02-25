#!/bin/sh
#Copyright (C) 2015 tplink.com

############################################################################### debug
#rm -f /tmp/.qos/mark.data
#rm -f /tmp/.qos/cid.data
#rm -f /tmp/.qos/qos-tplink.log
# debug  add stub ipset : begin
#ipset destroy myset1 2>/dev/null
#ipset destroy myset2 2>/dev/null
#ipset -N myset1 iphash 2>/dev/null
#ipset -N myset2 iphash 2>/dev/null
#ipset -A myset1 192.168.0.20-192.168.0.22 2>/dev/null
#ipset -A myset2 2.2.2.20 2>/dev/null
#ipset -A myset2 192.168.0.50 2>/dev/null

############################################################################### debug:end

############################################################################
# include dependence
. /lib/qos-tplink/qos_public.sh
. /lib/qos-tplink/qos_core.sh

local RULE_OPT_LIST="enable if_ping if_pong rate_max ip_group mode time"
[ -z $QOS_CONFIG_ER ] && RULE_OPT_LIST="$RULE_OPT_LIST rate_max_mate" || RULE_OPT_LIST="$RULE_OPT_LIST ip_type"

# destroy all qos cfgs
# del tc rule and netfilter rule
qos_destroy()
{
	rm -rf $QOS_READY 2>/dev/null
	QOS_STATE clear
	# del the bak-UCI
	rm -f $QOS_UCI_BAK 2>/dev/null

	# destroy all tc
	[ -z $QOS_TPLIMIT_ALL ] && qos_tc_destroy
	# destroy all nf qos chains
	qos_nf_destroy

	# delete time object

	ret=$(timeobj_api_deleteAll ${THIS_MODULE})
	ret=$(timeobj_api_commit ${THIS_MODULE})

	rm -f ${QOS_TMP_DIR}/stop_flag 2>/dev/null

	# toggle sfe_qos according to the fact that whether netfilter(iptables) qos rule exist
	qos_nf_sfe_toggle

	QOS_LOG_PRINT "qos_destroy, flush all rules!"
}

# get rule_list with the callback $1, which define the match method
qos_rulelist_get()
{
	local cb="$1"
	local list=""
	config_foreach $cb $STYPE_RULE
	QOS_RET "$list"
}

#############################################################################
# qos module UCI rule parse handle: set up rule leafs
	# UCI rule leaf -> tc
	# UCI rule leaf -> netfilter
qos_rules_parse()
{
	local rule_list="$1"
	local flag=0  # IF have time obj reg
	local rule_num=$(QOS_STATE get rule_num)

	# 1. get evary rule within a big big big loop
	for rule_name in $rule_list; do
		[ -f ${QOS_TMP_DIR}/stop_flag ] && break

		QOS_WRITE_LOG "qos_rule, parsing rule $rule_name ..."

		[ "$rule_num" -ge "$QOS_RULE_SPEC" ] && {
			QOS_LOG_PRINT " error, qos_rule_parse, user rule num exceed the spec: $QOS_RULE_SPEC !"
			return 1
		}
		let rule_num++

		# 1. check rule should be to install
		# IF rule is enable?
		config_get enable "$rule_name" "enable"
		[ "$enable" != "on" ] && QOS_WRITE_LOG " info, rule disable, skip install !" && continue

		# IF rule has option time, reg rule to time manager module, then parse next rule
		config_get timeobj "$rule_name" "time"
		[ "$timeobj" = "" ] && timeobj="Any"
		[ "$timeobj" != "Any" ] && {
			QOS_WRITE_LOG " info, rule reg to tmngtd, timeobj=$timeobj, rule=$rule_name ! "
			ret=$(timeobj_api_add $timeobj $THIS_MODULE $rule_name)
			flag=$((flag + 1))
			continue
		}

		qos_rule_install $rule_name || {
			QOS_LOG_PRINT " error, qos_rule_parse, install rule $rule_name fail!" && break
		}
	done
	QOS_STATE set rule_num "$rule_num"
	[ $flag -gt 0 ] && ret=$(timeobj_api_commit $THIS_MODULE)

	# flush conntracks, for nfmark may vary on every qos_start
	#conntrack -F >/dev/null 2>&1
	return 0
}

# qos start entry
	# complete hard init qos in TC & nf
qos_start()
{

	[ -z $QOS_CONFIG_INVALID ] || {
		QOS_WRITE_LOG "  NO UCI config, exit the QOS process ! "
		return
	}

	# 1. global init root
	[ $(qos_global_init) -ne 0 ] && return

	# 2. extract all user rules from UCI config file
	#local rule_list=`awk '/rule/ {print $3}' $QOS_UCI | sed s/\'*//g`
	rule_get()
	{
		[ -z "$list" ] && list="$1" || list="$list $1"
	}
	local rule_list=$(qos_rulelist_get rule_get)
	if [ ${#rule_list} -eq 0 ]; then
		QOS_LOG_PRINT " info, NO user rule find!"
	else
		# get current UCI rules list for rule order
		# local rules_order="${QOS_TMP_DIR}/rules_order"
		# echo -e "$rule_list" | sed 's/[ ]/\n/g' | awk '{print NR,$0}' > $rules_order

		QOS_LOG_PRINT " qos_start, rule list: $rule_list"
		# store all rules info as qos_state
		QOS_STATE set rule_list "$rule_list "
		QOS_STATE set rule_num "0"

		lua /lib/qos-tplink/state_gen.lua

		# for rule in $rule_list; do
		# 	for opt in $RULE_OPT_LIST; do
		# 		QOS_STATE set ${rule}.${opt} "$(config_get $rule $opt)"
		# 	done
		# done

		qos_rules_parse "$rule_list"
	fi

	# 3. backup UCI config
	cp -f "$QOS_UCI" "$QOS_UCI_BAK" 2>/dev/null

	# toggle sfe_qos according to the fact that whether netfilter(iptables) qos rule exist
	qos_nf_sfe_toggle

	# set READY flag
	touch $QOS_READY
}

# handle time object response
	# ACTIVE
qos_time_handle()
{
	[ ! -f $QOS_READY ] && QOS_LOG_PRINT " info, qos not config, NO need time handle ! " && return

	local mode="$1"  # active or expire or reset
	[ "$mode" = "RESET" ] && {
		QOS_LOG_PRINT " info, time objects RESET, STUB now ! "
		#qos_start
		return
	}
	local symbol="$2"  # time object name

	# reserve rule_list support
	[ "$mode" = ACTIVE ] && cb=qos_rule_install || cb=qos_rule_uninstall
	for rule in $symbol; do
		[ -f ${QOS_TMP_DIR}/stop_flag ] && break

		# check IF rule exist in UCI?
		[ "`uci get ${THIS_MODULE}.${rule} 2>/dev/null`" != "rule" ]&& {
			QOS_LOG_PRINT " exception qos_time_handle, rule $rule not exist in UCI "
			continue
		}

		$cb $rule || {
			QOS_WRITE_LOG " error, qos_time_handle process $cb $rule fail!"
			break
		}
	done

	# toggle sfe_qos according to the fact that whether netfilter(iptables) qos rule exist
	qos_nf_sfe_toggle

	## [ "$mode" = ACTIVE ] && conntrack -F >/dev/null 2>&1
	return 0
}

qos_ipgroup_handle()
{
	[ ! -f $QOS_READY ] && QOS_LOG_PRINT " info, qos not config, NO need ipgroup handle ! " && return
	local mode="$1"  # UPDATE or DELETE
	local ipobj="$2"

	[ "$mode" != "update" ] && QOS_LOG_PRINT " info, ipgroup handle mode != update ! " && return

	# compose the rule_list match the ipgroup obj
	rule_get()
	{
		local rule="$1"
		[ "$(config_get "$rule" ip_group)" = "$ipobj" ] && list="$list $rule"
	}
	local rule_list=$(qos_rulelist_get rule_get)
	[ ${#rule_list} -eq 0 ] && {
		QOS_LOG_PRINT " info, No rule match ipgroup $ipobj "
		return
	}

	QOS_LOG_PRINT " info, ipgroup $ipobj apply by rule_list:$rule_list "
	for rule in $rule_list; do
		[ -f ${QOS_TMP_DIR}/stop_flag ] && break

		[ -z $QOS_TPLIMIT_ALL ] || continue # for tplimit_all mode, priv bwc also be matched by ipset group

		# for rule in BW-share mode, only need to delete the conntrack item
		[ "$(QOS_STATE get "${rule}.mode")" = share ] && continue
		# for those in BW-priv mode, MUST reparse iplist & reinstall rule
		qos_rule_uninstall $rule && qos_rule_install $rule || QOS_LOG_PRINT " error, uninstall rule $rule fail! "
	done
	#conntrack -F >/dev/null 2>&1

	# toggle sfe_qos according to the fact that whether netfilter(iptables) qos rule exist
	qos_nf_sfe_toggle
}

# deactive nf and tc rules by interface
	# uninstall rules:
		# 1. netfilter: chain by zone
		# 2. tc: root qdisc
		# 3. mark.data: rule_name nfmarks
		# 4. tcid.data: rule_name dev
# This handle called by hotplug script
qos_hotplug_ifdown()
{
	[ ! -f $QOS_READY ] && QOS_LOG_PRINT " info, NO QOS policy installed, just return!" && return
	local iface=$1   # eg:  wan1_eth wan2_poe
	# for 450G hotplug interface should translate to zone
	[ -z $QOS_CONFIG_ER ] && iface=$(intf2zone $iface)
	[ ${#iface} -eq 0 ] && QOS_LOG_PRINT " error, qos_hotplug_ifdown interface invalid! " && return
	local dev=$(indirect_var_get ${iface}_dev)
	QOS_LOG_PRINT " info, ifdown iface=$iface, dev=$dev"

	# 2. IF lan down, then qos is waste, so just stop all qos
		# for WAN down, just destroy tc and nf items on this dev
	[ -z $QOS_CONFIG_ER -a "$dev" = "$LAN_NETDEV" ] && {
		QOS_LOG_PRINT "qos_hotplug, LAN down, issue qos stop!"
		qos_destroy
		return
	}

	# get the user rules by iface name
		# uninstall them from tc and nf
	rule_get()
	{
		local rule="$1"
		config_get if_ping "$rule" "if_ping"
		config_get if_pong "$rule" "if_pong"
		[ "$if_ping" = "$iface" -o "$if_pong" = "$iface" ] && list="$list $rule"
	}
	local rule_list=$(qos_rulelist_get rule_get)
	[ ${#rule_list} -ne 0 ] && {
		QOS_LOG_PRINT " info, uninstall rule by $iface down: $rule_list "
		for rule in $rule_list; do
			qos_rule_uninstall $rule || QOS_LOG_PRINT " exception, uninstall rule $rule fail"
		done
	}

	# delete root qdisc on $dev
	# delete items in nf
	qos_nf_del_rule_byiface $iface
	qos_tc_del_rule_bydev $dev

	return
}

# install nf and tc rules by $INTERFACE from hotplug
	# this handle service hotplug
qos_hotplug_ifup_abandon()
{
	local iface="$1"
	# 1. if get the zone by INTERFACE
	local zone=$(intf2zone $iface)
	[ $(valid_zone $zone) -ne 0 ] && QOS_LOG_PRINT " info, $iface zone $zone invalid ! " && return
	local dev=$(indirect_var_get ${zone}_dev)
	QOS_LOG_PRINT " info, ifup zone=$zone, dev=$dev"

	# IF dev has been setup qos
	[ $(qos_tc_dev_check $dev) -ne 0 ] && QOS_LOG_PRINT " info, $iface has init, skip! THIS IS ONLY OCCURED ON BOOT! *****************" && return

	# 3. create tc&nf root for zone
		# CAUTION: DO NOT crash the valid rules that installed on other zone
	[ $(qos_global_init) -ne 0 ] && return

	# 4. global init root
	#ret=$(qos_global_init)
	# 1. get the user rules by zone name
		# ** ONLY BOTH pingpong zone is active, that rule is to install **
	rule_get()
	{
		local rule="$1"
		config_get if_ping "$rule" "if_ping"
		config_get if_pong "$rule" "if_pong"
		[ "$if_ping" = "$zone" -o "$if_pong" = "$zone" ] && {
			[ 0 -eq $(valid_zone $if_ping) -a 0 -eq $(valid_zone $if_pong) ] && list="$list $rule"
		}
	}
	local rule_list=$(qos_rulelist_get rule_get)
	[ ${#rule_list} -eq 0 ] && QOS_LOG_PRINT " info, NO rule to ifup install, return!" && return
	QOS_LOG_PRINT " info, ifup install rule: $rule_list "

	# 5. install rule_list
	qos_rules_parse "$rule_list"
	return
}

qos_relaod_rule()
{
    local rule_name=$1
	local timeobj
	local timeobj_bk

	QOS_WRITE_LOG "**************：rule_name=$rule_name"
	local timeobj_bk=$(QOS_STATE get "${rule_name}.time")
	config_get timeobj "$rule_name" "time"
	QOS_WRITE_LOG "timeobj=$timeobj,timeobj_bk=$timeobj_bk"

	[ "$timeobj" = "" ] && timeobj="Any"

	[ "$timeobj_bk" != "Any" ] && {
		QOS_WRITE_LOG " info, rule del from tmngtd, timeobj_bk=$timeobj_bk, rule=$rule_name ! "
		ret=$(timeobj_api_delete $timeobj_bk $THIS_MODULE $rule_name)
		ret=$(timeobj_api_commit $THIS_MODULE)
	}

	[ "$timeobj" != "Any" ] && {
		QOS_WRITE_LOG " info, rule reg to tmngtd, timeobj=$timeobj, rule=$rule_name ! "
		ret=$(timeobj_api_add $timeobj $THIS_MODULE $rule_name)
		ret=$(timeobj_api_commit $THIS_MODULE)
		return
	}


	qos_rule_install $rule_name || {
		QOS_LOG_PRINT " error, qos_rule_parse, install rule $rule_name fail!"
	}
}

# qos warm change adapt
	# for now, only support rule-add warm init
	        #  rule delete MUST re start
qos_reload()
{
	local op="$1"
	shift
	[ "$op" = "update" ] && {
		local update_list="$@"
	}
	[ "$op" = "add" ] && {
		local add_list="$@"
	}
	[ "$op" = "delete" ] && {
		local del_list="$@"
	}

	# if no qos.ready, proc total start
	[ ! -f $QOS_READY ] && { QOS_LOG_PRINT "qos_reload, NO effective config, run hard start!"
		qos_start
		return
	}

	# if global qos_enable changed, ONLY happen enable on->off
	local enable_cur=$(config_get "$SNAME_GLOBAL" qos_enable)
	local enable_bak=$(QOS_STATE get qos_enable)
	[ "$enable_cur" != "$enable_bak" ] && { QOS_LOG_PRINT "qos_reload, qos_enable->off! run stop"
		qos_destroy
		return
	}

	###############################################
	# IF list interface change ?
		# tip: IFACE_LIST always the latest UCI ifaces
	iface_list_bak=$(QOS_STATE get iface_list)
#QOS_DEBUG_PRINT "@@@@ iface_list=$IFACE_LIST   `echo $IFACE_LIST | wc -w`"
#QOS_DEBUG_PRINT "@@@@ iface_list_bak=$iface_list_bak  `echo $iface_list_bak | wc -w`"
	[ "`echo $iface_list_bak | wc -w`" != "`echo $IFACE_LIST | wc -w`" ] && {
		QOS_LOG_PRINT "qos_reload, interface varied, run hard start"
		qos_start
		return
	}

	for iface in $IFACE_LIST; do
		# IF iface exist in bak file
		`echo $iface_list_bak | grep -w -q "${iface}" ` || {
			QOS_LOG_PRINT "qos_reload, ${iface} is new, run hard start!"
			qos_start
			return
		}

		# up/down link rate of the iface change?
		for item in uplink downlink; do
			local cur=$(config_get "$iface" $item)
			local bak=$(QOS_STATE get "${iface}.${item}")
#QOS_DEBUG_PRINT " @@@@ $iface $item: $cur -- $bak"
			[ "$cur" != "$bak" ] && {
				QOS_LOG_PRINT "qos_reload, ${iface} $item changed, run hard start!"
				qos_start
				return
			}
		done
	done

	##############################################
	# get user rule change list
		# current UCI and bak-UCI  diff_rule list
	local rules_cur="${QOS_TMP_DIR}/rules_cur"
	local rules_bak="${QOS_TMP_DIR}/rules_bak"
	# local rules_update="${QOS_TMP_DIR}/rules_update"
	rule_get()
	{
		[ -z "$list" ] && list="$1" || list="$list $1"
	}

	local rule_list=$(qos_rulelist_get rule_get)

	# get current UCI rules list for rule order
	local rules_order="${QOS_TMP_DIR}/rules_order"
	cp ${rules_order} ${rules_order}_bak
	echo -e "$rule_list" | sed 's/[ ]/\n/g' | awk '{print NR,$0}' > $rules_order

	# echo -e "$rule_list" | sed 's/[ ]/\n/g' > $rules_cur
	# echo -e "$(QOS_STATE get rule_list)" | sed 's/[ ]*$//g' | sed 's/[ ]/\n/g' > $rules_bak
	# sort only support data sep by \n
	# `sort $rules_cur > ${rules_cur}_sort`
	# `sort $rules_bak > ${rules_bak}_sort`
	# local add_list=`comm ${rules_cur}_sort ${rules_bak}_sort -2 -3`
	# local del_list=`comm ${rules_cur}_sort ${rules_bak}_sort -1 -3`
	#local update_list=`comm ${rules_cur}_sort ${rules_bak}_sort -1 -2`

	# `cp $rules_cur ${rules_update}_cur`
	# `cp $rules_bak ${rules_update}_bak`
	#for rule in $add_list; do
	#	sed -i "/$rule/d" ${rules_update}_cur
	# done

	#for rule in $del_list; do
	#	sed -i "/$rule/d" ${rules_update}_bak
	# done

	# local update_list=`cat ${rules_update}_cur`
	# add row number for order compare
	# `awk '{print NR,$0}' ${rules_update}_cur > ${rules_update}_cur_linenum`
	# `awk '{print NR,$0}' ${rules_update}_bak > ${rules_update}_bak_linenum`

	#QOS_INFO_PRINT "  qos_reload, add_list = $add_list"
	#QOS_INFO_PRINT "  qos_reload, del_list = $del_list"
	#QOS_INFO_PRINT "  qos_reload, update_list = $update_list"

	# this process order is important : delete -> add -> update
	# proc dellist
	[ 0 -ne ${#del_list} ] && {
		local rule_num=$(QOS_STATE get rule_num)
		for rule in $del_list; do
			[ -f ${QOS_TMP_DIR}/stop_flag ] && break

			QOS_LOG_PRINT "qos_reload, delete rules: ${rule}"
			[ "$(QOS_STATE get ${rule}.enable)" = "on" ] && qos_rule_uninstall $rule

			tobj=$(QOS_STATE get ${rule}.time)
			if [ ${#tobj} -ne 0 -a $tobj != "Any" ]; then
				#QOS_LOG_PRINT "qos_reload, $rule delete timeobj $tobj"
				timeobj_api_delete $tobj $THIS_MODULE $rule && timeobj_api_commit $THIS_MODULE
			fi
			# local list="$(QOS_STATE get rule_list)"
			# QOS_STATE set rule_list "${list/${rule} /}"
			QOS_STATE del "$rule"
			let rule_num--
		done
		QOS_STATE set rule_list "$rule_list "
		[ $rule_num -lt 0 ] && rule_num=0
		QOS_STATE set rule_num "$rule_num"
	}

	# proc addlist
	[ 0 -ne ${#add_list} ] && {
		for rule in $add_list; do
			QOS_LOG_PRINT "qos_reload, add new rules: ${rule}"
			for opt in $RULE_OPT_LIST; do
				QOS_STATE set ${rule}.${opt} "$(config_get $rule $opt)"
			done
		done
		QOS_STATE set rule_list "$rule_list "

		qos_rules_parse "$add_list"
		#conntrack -F >/dev/null 2>&1
	}

	# confirm rules in comlist is changed ?
	if [ 0 -ne ${#update_list} ]; then
		# QOS_LOG_PRINT "qos_reload, confirm if update rules: ${update_list/^[ \t]*$/}"
		# IF rule changed
		#local need_update=0
		for rule in $update_list; do
			qos_rule_uninstall $rule
		done

		for rule in $update_list; do
			# check rule order change?
			# local order_new=`grep -w $rule ${rules_order} | awk '{print $1}'`
			# local order_old=`grep -w $rule ${rules_order}_bak | awk '{print $1}'`
			# [ "$order_new" -ne "$order_old" ] && {
			# 	QOS_LOG_PRINT " info, detect $rule order change, run warm update !"
			# 	need_update=1
			# }

			# check rule option change?
			# [ $need_update -gt 0 ] || {
			# 	for opt in $RULE_OPT_LIST; do
			# 		opt_cur=$(config_get $rule $opt)
			# 		opt_bak=$(QOS_STATE get "${rule}.${opt}")
			# 		[ "$opt_cur" != "$opt_bak" ] && {
			# 			QOS_LOG_PRINT " info, detect $rule option $opt change, run warm update !"
			# 			need_update=1;
			# 			break;
			# 		}
			# 	done
			# }

			# qos_rule_uninstall $rule
			[ "$(config_get $rule enable)" == "on" ] && {
				 qos_relaod_rule $rule || {
					QOS_LOG_PRINT " error, update rule $rule fail! "
					return;
				}
			}

			[ "$(config_get $rule enable)" == "off" ] && {
			    local timeobj_del=$(QOS_STATE get "${rule}.time")
			    [ "$timeobj_del" != "Any" ] && {
            		ret=$(timeobj_api_delete $timeobj_del $THIS_MODULE $rule)
            		ret=$(timeobj_api_commit $THIS_MODULE)
            		QOS_WRITE_LOG " info, rule del from tmngtd, timeobj_del=$timeobj_del, rule=$rule ! "
        		}
			}

			# update rule info in qos_state
			for haha in $RULE_OPT_LIST; do
				QOS_STATE set "${rule}.${haha}" "$(config_get $rule $haha)"
			done
			# need_update=0

		done
		QOS_STATE set rule_list "$rule_list "
	fi

	# toggle sfe_qos according to the fact that whether netfilter(iptables) qos rule exist
	qos_nf_sfe_toggle

	#rm -r ${rules_cur}* ${rules_bak}*
	cp -f "$QOS_UCI" "$QOS_UCI_BAK" 2>/dev/null
}

##################################################################################
# qos module root command
if [ "$1" = "stop" ]; then
	touch ${QOS_TMP_DIR}/stop_flag
fi

{
    flock -x 25
    local args="$@"
    #QOS_LOG_PRINT "$0 $args. begin @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ! "
    if [ "$1" = "start" ]; then
    	qos_start

    elif [ "$1" = "stop" ]; then
    	qos_destroy

    elif [ "$1" = "reload" ]; then
        shift
        local op="$1"
        shift
        local op_list="$@"
    	qos_reload "$op" "$op_list"

    elif [ "$1" = "ifdown" ]; then
    	local intf="$2"
    	#qos_hotplug_ifdown $intf
    	qos_start

    elif [ "$1" = "ifup" ]; then
    	local intf="$2"
    	# AS downlink rule limitted by tc delete unsupport, NOT support INTERFACE ifup method, otherwise, cause tc class and tcid serious leek !!
    	# qos_hotplug_ifup $intf
    	qos_start

    elif [ "$1" = "time" ]; then
    	local mode="$2"
    	shift 2
    	local symbol="$@"  # precise rule_name regged by timeobj_add_api
    	qos_time_handle "$mode" "$symbol"

    elif [ "$1" = "ipgroup" ]; then
    	local mode="$2"
    	local obj="$3"
    	qos_ipgroup_handle $mode $obj

    else
    	QOS_INFO_PRINT "$0 NO support arg $args "
    fi

    #QOS_LOG_PRINT "$0 $args. done !\n"
    flock -u 25
} 25<> /tmp/.qos/qos.lock
