#!/bin/sh
#Copyright (C) 2015 tplink.com

[ "$INC_QOS_STATE" != "" ] && return
export INC_QOS_STATE="INC"

. /lib/qos-tplink/qos_public.sh

local IPT_PREFIX="iptables -w -t mangle"
local all_infs="$ZONE_LIST $GRP_LIST"
local all_devs=$DEV_LIST
QOS_DEBUG_PRINT " @@@ all_devs=$all_devs, all_infs=$all_infs"

# funcs
tc_state()
{
	local opt=$1;
	local dev=$2;

	local list="$dev $LAN_NETDEV"
	[ "$dev" = "all" -o "$dev" = "$LAN_NETDEV" ] && list="$all_devs"

	QOS_INFO_PRINT "*********** TC states ******************************************************************************** "
	for dev in $list; do
		#[ $(valid_dev $dev) -ne 0 ] && QOS_INFO_PRINT " ########## netdev $dev invalid, skip \n" && continue
		QOS_INFO_PRINT " \t\t\t\t # netdev $dev tc state # "
		tc $opt qdisc show dev $dev;
		echo " "
		tc $opt class show dev $dev;
		echo " "
		tc $opt filter show dev $dev;
		echo " "
	done
}

nf_state()
{
	QOS_INFO_PRINT "*********** nf states ******************************************************************************** "
	QOS_INFO_PRINT " \t\t\t\t FORWARD/OUTPUT/INPUT state # "
	$IPT_PREFIX -L FORWARD -vn --line | sed '/zone.*_MSSFIX/d' && QOS_INFO_PRINT ""

	local list=`iptables -t mangle -S | grep "^\-N[ ]qos_.*" | awk '{print $2}'`
	for chain in $list; do
		$IPT_PREFIX -L $chain -vn --line
		QOS_INFO_PRINT ""
	done
}

qos_state_usage()
{
	QOS_INFO_PRINT "-------------------------------------------------------------------------------------"
	QOS_INFO_PRINT "usage: "
	QOS_INFO_PRINT "  $0 [iface] /[option]"
	QOS_INFO_PRINT "  \tiface  := { all | $IFACE_list }"
	QOS_INFO_PRINT "  \toption := null | no null, no null is detail option for tc state"
	QOS_INFO_PRINT "  default: $0 all"
}

#############################################
# get args
local myiface="$1"
local option="$2"

if [ "$option" = "" ]; then
	option="-p"
else
	option="-s"
fi

if [ "$myiface" = "" -o "$myiface" = "all" ]; then
	#tc_state $option all
	nf_state all
else
	# fault tolerance
	`echo $all_infs | grep -q -w "$myiface"`
	[ $? -ne 0 ] && QOS_INFO_PRINT "\t \$1 invalid !!!" && qos_state_usage && exit
	local dev=$(indirect_var_get ${myiface}_dev)
	#tc_state $option $dev
	nf_state $myiface
fi
