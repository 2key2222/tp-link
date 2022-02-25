#!/bin/sh
#Copyright (C) 2015 tplink.com

[ "$INC_QOS_GRPMARK" != "" ] && return
export INC_QOS_GRPMARK="INC"

. /lib/qos-tplink/qos_public.sh

#### nfmark manager for qos-tplink
local GRPMARK_BIT_BASE=$QOS_GMARK_BIT_START
local GRPMARK_SPEC=$QOS_RULE_SPEC
local GRPMARK_BASE=`awk "BEGIN{val=lshift(1, $GRPMARK_BIT_BASE); print val}"`
local GRPMARK_MAX=`awk "BEGIN{val=lshift($GRPMARK_SPEC, $GRPMARK_BIT_BASE); print val}"`

local NULL_RULE="!@#$"      # nfmark attach NULL rule, is valid for a new rule
local QOS_GRPMARK_FILE="${QOS_TMP_DIR}/grpmark.data"

# CAUTION, grpmark.data modified ##ONLY## by this script
[ ! -f $QOS_GRPMARK_FILE ] && QOS_WRITE_FILE "mark user_rule_name" "$QOS_GRPMARK_FILE" && QOS_INFO_PRINT " create grpmark.data"
[ ! -f /lib/qos-tplink/grpmark.data ] && ln -sf $QOS_GRPMARK_FILE /lib/qos-tplink/grpmark.data

nr2grpmark()
{
	local ln="$1"
	QOS_RET `awk "BEGIN{val=lshift($((ln-1)), $GRPMARK_BIT_BASE); print val}"`
}

# alloc a nfmark for user_rule, and update mark.data file
# ret: !0 valid nfmark
#      0 error, total rule num exceed QOS_SPEC
qos_grpmark_alloc()
{
	local user_rule=$1
	local lnum=`wc -l $QOS_GRPMARK_FILE | awk '{print $1}'` 
	local nfmark=""
	local item=""

	# IF has a mark freed ahead, first use the freed mark. 
	# This is useful in case of modifing rules
	local free=`awk '{if(NF==1) {print $1}}' $QOS_GRPMARK_FILE | awk 'NR==1 {printf $1}'`
	[ ${#free} -ne 0 ] && {
		item="${free} ${user_rule}"
		sed "s/^${free}[ ]/${item}/" -i $QOS_GRPMARK_FILE
		nfmark=$free
	} || {
		[ $lnum -le $GRPMARK_SPEC ] && {
			# mark.data NOT full, get NFMARK by the file line numbers
			nfmark=$(($(nr2grpmark $lnum) + $GRPMARK_BASE))
			nfmark=$(dec2hex $nfmark)
			item="${nfmark} ${user_rule}"
			QOS_WRITE_FILE "$item" "$QOS_GRPMARK_FILE"
		} || {
			nfmark=0
		}
	}

	QOS_RET "$nfmark"
}



qos_grpmark_free_abandon()
{
	local user_rule="$1"
	local cnt=`grep -c -w "$user_rule" $QOS_GRPMARK_FILE`
	
	# del all user_rule
	sed "s/${user_rule}$//g" -i $QOS_GRPMARK_FILE
	
	QOS_RET "$cnt"
}
# deattach user_rule_name to nfmark , and update mark.data file
# ret: !0 free ok, nfmark freed counter
#      0 error, no find rule in mark.data
qos_grpmark_free()
{
	local list="$1"
	[ ${#list} -eq 0 ] && return
	local total=0
	
	for rule in $list; do
		local cnt=`grep -c -w "$rule" $QOS_GRPMARK_FILE`
		[ $cnt -gt 0 ] && sed "s/${rule}$//g" -i $QOS_GRPMARK_FILE
		total=$((total + cnt))
	done
	QOS_RET "$total"
}

# get the nfmark alloc to rule $1
qos_grpmark_get()
{
	local rule="$1"
	mark=`grep -w "$rule" $QOS_GRPMARK_FILE | awk '{print $1}'`
	QOS_RET "$mark"
	[ ${#mark} -ne 0 ] && return 0 || return 1
}

# get rule from nfmark already alloced
qos_grpmark2rule()
{
	local mark="$1"
	rule=`awk "/${mark}/" $QOS_GRPMARK_FILE | awk '{print $2}'`
	QOS_RET "$rule"
}

# free a specified nfmark
#     only use in rule add process
qos_grpmark_free_bymark()
{
	local nfmark=$1
	sed "/${nfmark}[ ]/s/[' '].*/ /g" -i $QOS_GRPMARK_FILE
}

# flush all nfmark
qos_grpmark_flush()
{
	[ -f $QOS_GRPMARK_FILE ] && { rm -f $QOS_GRPMARK_FILE
	QOS_WRITE_FILE "mark user_rule_name" "$QOS_GRPMARK_FILE"
	}
}


##################################################################################
# single sh debug mode
if [ "$1" = "markdebug" ];then
	QOS_INFO_PRINT " ##############  enter $0 debug mode  ##############"
	if [ $2 = "auto" ];then
		for nn in $(seq 1 1 $(($GRPMARK_SPEC + 2))); do
			local user_rule=debug${nn}
			local ret_mark=$(qos_grpmark_alloc $user_rule)
			[  $ret_mark = 0 ] && QOS_ERROR " error, alloc nfmark for rule $user_rule fail, exceed support SPEC"
		done
	
	elif [ $2 = "add" ]; then
		local user_rule=debug_rule1
		local ret_mark=$(qos_grpmark_alloc $user_rule)
		[  $ret_mark = 0 ] && QOS_ERROR " error, alloc nfmark for rule $user_rule fail, exceed support SPEC"\
		|| QOS_INFO_PRINT "  ### add, alloc rule $user_rule with nfmark $ret_mark "
	
	elif [ $2 = "freerule" ]; then
		user_rule="$3"
		QOS_INFO_PRINT "  ###, $0 free rule $user_rule "
		local ret=$(qos_grpmark_free "$user_rule")
		[ $ret -eq 0 ] && QOS_ERROR " info, del rule $user_rule fail, NOT found "
	
	elif [ $2 = "freemark" ]; then
		local nfmark=$3
		QOS_INFO_PRINT "  ###, $0 free mark $nfmark "
		$(qos_grpmark_free_bymark $nfmark)
	
	elif [ $2 = "test" ]; then
		user_rule=$3
		qos_grpmark_alloc $user_rule
	fi
fi
