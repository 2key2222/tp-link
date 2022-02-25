#!/bin/sh
#Copyright (C) 2015 tplink.com

[ "$INC_QOS_CID" != "" ] && return
export INC_QOS_CID="INC"

. /lib/qos-tplink/qos_public.sh

#### tcid manager for qos-tplink
# TODO state the design principle 

local TCID_BASE=1000
local TCID_MIN=$(( $TCID_BASE + 1))
local TCID_SPEC=$QOS_CELL_SPEC
local TCID_MAX=$(($TCID_SPEC + $TCID_BASE))
local QOS_TCID_FILE="${QOS_TMP_DIR}/cid.data"

# CAUTION, tcid.data modified ##ONLY## by this script
[ ! -f $QOS_TCID_FILE ] && QOS_WRITE_FILE "tcid user_rule_name netdev" "$QOS_TCID_FILE" && QOS_INFO_PRINT " create cid.data" 
[ ! -f /lib/qos-tplink/cid.data ] && ln -sf $QOS_TCID_FILE /lib/qos-tplink/cid.data

nr2tcid()
{
	QOS_RET $(($1 + $TCID_BASE))
}

# alloc a tcid for user_rule, and update tcid.data file
# ret: !0 valid tcid
#      0 error, total rule num exceed QOS_SPEC
qos_tcid_alloc_old()
{
	local user_rule=$1
	local dev=$2
	local lnum=`wc -l $QOS_TCID_FILE | awk '{print $1}'` 
	local tcid
	local item
	
	if [ $lnum -lt $(($TCID_MAX - $TCID_BASE + 1)) ]; then
		# tcid.data NOT full, get tcid by the file line numbers
		tcid=$(nr2tcid $lnum)
		item="${tcid} ${user_rule} ${dev}"
		QOS_WRITE_FILE "$item" "$QOS_TCID_FILE"
	else
		# tcid.data IS full, wrap to find if there is a tcid valid ahead!
		# return the first tcid valid and full fill the line with user_rule
		echo &&
		nr=`grep -n "^[0-9]" $QOS_TCID_FILE | grep "[' ']$" | awk -F':' 'NR==1 {print $1}'`
		if [ 0 -ne $nr ] 2>/dev/null; then
			tcid=$(($(nr2tcid $nr) - 1))
			item="${tcid} ${user_rule} ${dev}"
			sed "s/${tcid}[' ']/${item}/g" -i $QOS_TCID_FILE
			#sed "/${tcid}/s/[' ']/[' ']${item}/" -i $QOS_TCID_FILE
		else
			tcid=0
		fi
	fi
	
	QOS_RET "$tcid"
}

# alloc a tcid for user_rule, and update tcid.data file
# ret: !0 valid tcid
#      0 error, total rule num exceed QOS_SPEC
qos_tcid_alloc()
{
	local user_rule=$1
	local lnum=`wc -l $QOS_TCID_FILE | awk '{print $1}'` 
	local tcid=""
	local item=""

	# IF has a tcid freed ahead, first use the freed tcid. 
	# This is useful in case of modifing rules
	local free=`awk '{if(NF==1) {print $1}}' $QOS_TCID_FILE | awk 'NR==1 {printf $1}'`
	[ ${#free} -ne 0 ] && {
		item="${free} ${user_rule} ${dev}"
		sed "s/^${free}[ ]/${item}/" -i $QOS_TCID_FILE
		tcid=$free
	} || {
		[ $lnum -le $TCID_SPEC ] && {
			# tcid.data NOT full, get by the file line numbers
			tcid=$(nr2tcid $lnum)
			item="${tcid} ${user_rule} ${dev}"
			QOS_WRITE_FILE "$item" "$QOS_TCID_FILE"
		} || {
			tcid=0
		}
	}

	QOS_RET "$tcid"
}



# get the tcid that alloced to the user_rule
qos_tcid_getby_rule()
{
	local user_rule=$1
	local dev=$2
	local tcid=0
	local item="$user_rule $dev"
	local cnt=`grep -c -w "$item" $QOS_TCID_FILE`
	
	if [ $cnt -eq 0 ]; then
		tcid=0    ### no find rule in tcid.data
	else
		tcid=`grep -n -w "$user_rule $dev" $QOS_TCID_FILE | awk -F: 'NR==1 {print $2}' | awk '{print $1}'`
	fi
	QOS_RET "$tcid"
}

# get the tcid alloc to rule $1
qos_tcid_get()
{
	local rule="$1"
	cid=`grep -w "$rule" $QOS_TCID_FILE | awk '{print $1}'`

	QOS_RET "$cid"
}

qos_tcid_free_old()
{
	local user_rule="$1"
#	local dev="$2"
	local cnt=`grep -c -w "$user_rule" $QOS_TCID_FILE`
	
	# del all user_rule
	#sed "s/${user_rule}[' ']${dev}$//g" -i $QOS_TCID_FILE
	sed "s/${user_rule} .*//g" -i $QOS_TCID_FILE
	
	QOS_RET "$cnt"
}

# deattach user_rule_name to tcid , and update tcid.data file
# support multi rule list
# ret: !0 free ok, tcid freed counter
#      0 error, no find rule in tcid.data
qos_tcid_free()
{
	local list="$1"
	[ ${#list} -eq 0 ] && return
	local total=0

	for rule in $list; do
		local cnt=`grep -c -w "$rule" $QOS_TCID_FILE`
		[ $cnt -gt 0 ] && sed "s/${rule} .*//g" -i $QOS_TCID_FILE
		total=$((total + cnt))
	done
	QOS_RET "$total"
}

qos_tcid_flush()
{
	[ -f $QOS_TCID_FILE ] && { rm -f $QOS_TCID_FILE
	QOS_WRITE_FILE "tcid user_rule_name netdev" "$QOS_TCID_FILE" 
	}
}

##################################################################################
# single sh debug mode
if [ "$1" = "ciddebug" ];then
	QOS_INFO_PRINT " ##############  enter $0 debug mode  ##############"
	if [ $2 = "auto" ];then
		for nn in $(seq 1 1 $(($TCID_SPEC + 2))); do
			local user_rule=debug${nn}
			local dev=dev${nn}
			local ret_tcid=$(qos_tcid_alloc $user_rule $dev)
			[ $ret_tcid -eq 0 ] && QOS_ERROR " error, alloc tcid for rule $user_rule fail, exceed support SPEC"
		done
	
	elif [ $2 = "add" ]; then
		local user_rule=debug_rule1
		local dev=eth1
		local ret_tcid=$(qos_tcid_alloc $user_rule $dev)
		[ $ret_tcid -eq 0 ] && QOS_ERROR " error, alloc tcid for rule $user_rule fail, exceed support SPEC"\
		|| QOS_INFO_PRINT "  ### add alloc rule $user_rule with $ret_tcid "
	
	elif [ $2 = "freerule" ]; then
		rule="$3"
		qos_tcid_free "$rule"
		#local ret=$(qos_tcid_free $user_rule $dev)
		#[ $ret -eq 0 ] && QOS_ERROR " error, del rule $user_rule fail, NOT found "
	elif [ $2 = "test" ]; then
		inf=WAN1
		qos_tcid_getby_rule "__downlinkroot_$inf" "$LAN_NETDEV"
		inf=WAN2
		qos_tcid_getby_rule "__downlinkroot_$inf" "$LAN_NETDEV"
	fi
fi
