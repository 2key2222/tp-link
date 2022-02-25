#!/bin/sh
# public defines and handles \ adapt for QOS

[ "$INC_QOS_COM" != "" ] && return
export INC_QOS_COM="INC"

#################################################################################################
#include extern lib
. /lib/functions.sh
. /lib/zone/zone_api.sh
. /lib/time_mngt/timeobj_api.sh

#################################################################################################
# qos  module defines
export THIS_MODULE="qos"
export STYPE_RULE="rule"
export STYPE_GLOBAL="global"
export SNAME_GLOBAL="setting"
export STYPE_IFACE="interface"

export LINERATE=1000000kbps

#########################
# QOS SPEC, the total tc leafs on all netdevs, means the MAX nfmark cnt
	# limit to the mem resource, tc rules can NOT be increase unlimited.
# get qos spec from /etc/profile.d/profile
local QOS_RULE_SPEC=`uci -c /etc/profile.d show profile | grep "@qos.*" | awk -F'=' '/rule_spec/ {print $2}'`
[ -z $QOS_RULE_SPEC ] && QOS_RULE_SPEC=64
export QOS_RULE_SPEC=$(($QOS_RULE_SPEC * 2))
export QOS_CELL_SPEC=`uci -c /etc/profile.d show profile | grep "@qos.*" | awk -F'=' '/cell_spec/ {print $2}'`
[ -z $QOS_CELL_SPEC ] && QOS_CELL_SPEC=1024
#echo -e "@@@@ QOS_RULE_SPEC=$QOS_RULE_SPEC, QOS_CELL_SPEC=$QOS_CELL_SPEC "

export QOS_MARK_BIT_START=11     # start bit for qos in nfmark
export QOS_MARK_BIT_LEN=`awk "BEGIN{f=log($QOS_RULE_SPEC)/log(2); print f}" | awk -F'.' '{print $1+1}'`
local QOS_MARK_MASK_BITS_RAW=`awk "BEGIN{f=lshift(1,$QOS_MARK_BIT_LEN)-1; print f}"`
export QOS_MARK_MASK=`awk "BEGIN{f=lshift($QOS_MARK_MASK_BITS_RAW, $QOS_MARK_BIT_START); print f}"`
QOS_MARK_MASK=`printf "0x%x" $QOS_MARK_MASK`
#echo -e " MARK:$QOS_MARK_BIT_START, $QOS_MARK_BIT_LEN, $QOS_MARK_MASK_BITS_RAW, $QOS_MARK_MASK"

# nfmark for ifgroup rule
	# one ifgroup rule cost ONE mark,
local QOS_GMARK_BIT_LEN=`awk "BEGIN{f=log($QOS_RULE_SPEC)/log(2); print f}" | awk -F'.' '{print $1+1}'`
export QOS_GMARK_BIT_START=$((QOS_MARK_BIT_START + QOS_MARK_BIT_LEN))
local QOS_GMARK_MASK_BITS_RAW=`awk "BEGIN{f=lshift(1,$QOS_GMARK_BIT_LEN)-1; print f}"`
export QOS_GMARK_MASK=`awk "BEGIN{f=lshift($QOS_GMARK_MASK_BITS_RAW, $QOS_GMARK_BIT_START); print f}"`
QOS_GMARK_MASK=`printf "0x%x" $QOS_GMARK_MASK`
export QOS_AMARK_MASK=`printf "0x%x" $((QOS_GMARK_MASK + QOS_MARK_MASK))`  # mask for all qos bitfields
#echo -e " GMARK:$QOS_GMARK_BIT_START, $QOS_GMARK_BIT_LEN, $QOS_GMARK_MASK_BITS_RAW, $QOS_GMARK_MASK, $QOS_AMARK_MASK"

export QOS_NFMARK_MUTEX_START=$(($QOS_GMARK_BIT_START + $QOS_GMARK_BIT_LEN))
export IFG_NFMARK_MUTEX_START=$(($QOS_NFMARK_MUTEX_START + 1))
export QOS_NFMARK_MUTEX_BIT_LEN=2
export QOS_NFMARK_MUTEX=`awk "BEGIN{f=lshift(1, $QOS_NFMARK_MUTEX_START); print f}"`
QOS_NFMARK_MUTEX=`printf "0x%x" $QOS_NFMARK_MUTEX`
export QOS_NFMARK_MUTEX_MASK=$QOS_NFMARK_MUTEX
export QOS_NFMARK_MUTEX_IFG=`awk "BEGIN{f=lshift($QOS_NFMARK_MUTEX, 1); print f}"`
QOS_NFMARK_MUTEX_IFG=`printf "0x%x" $QOS_NFMARK_MUTEX_IFG`
export QOS_NFMARK_MUTEX_IFG_MASK=$QOS_NFMARK_MUTEX_IFG
#echo -e " mutex MARK:$QOS_NFMARK_MUTEX_START, $IFG_NFMARK_MUTEX_START, $QOS_NFMARK_MUTEX_BIT_LEN, $QOS_NFMARK_MUTEX, $QOS_NFMARK_MUTEX_MASK, $QOS_NFMARK_MUTEX_IFG, $QOS_NFMARK_MUTEX_IFG_MASK"

#########################
local QOS_CONFIG_DIR="/etc/config"
local QOS_LIB_DIR="/lib/qos-tplink"
local QOS_UCI="${QOS_CONFIG_DIR}/${THIS_MODULE}"
local QOS_TMP_DIR="/tmp/.qos"
local QOS_LOG="${QOS_TMP_DIR}/qos-tplink.log"
local QOS_READY="${QOS_TMP_DIR}/.ready"
export QOS_POLLING_FILE="${QOS_TMP_DIR}/.polling"
# extract uci-config without comments
 # link qos uci config
[ -f $QOS_UCI ] || {
    touch $QOS_UCI
    export QOS_CONFIG_INVALID="true"
    return
}

#sed '/^[ \t]*#.*/d' -i $QOS_UCI
ln -sf $QOS_UCI $QOS_LIB_DIR/uci

# dummt transfer UCI, change "" to ''
#local en=`uci get ${THIS_MODULE}.${SNAME_GLOBAL}.qos_enable 2>/dev/null`
#[ "$en" = "" -o "$en" = "off" ] && en_r="on" && en="off"
#[ "$en" = "on" ] && en_r="off"
#`uci set ${THIS_MODULE}.${SNAME_GLOBAL}.qos_enable=${en_r}  2>/dev/null`
#`uci set ${THIS_MODULE}.${SNAME_GLOBAL}.qos_enable=${en}  2>/dev/null`
#`uci commit ${THIS_MODULE}  2>/dev/null`
#[ $? -ne 0 ] && {
#    # no UCI setting exist
#    export QOS_CONFIG_INVALID="true"
#    return
#}

 # load my configs
config_load "$THIS_MODULE"
 # backup effective UCI config, for config reload changes get
export QOS_UCI_BAK="${QOS_TMP_DIR}/uci_qos.use"

#########################
# setup tmp dir and log file
[ ! -d $QOS_TMP_DIR ] && mkdir $QOS_TMP_DIR
[ ! -d ${QOS_TMP_DIR}/log ] && mkdir ${QOS_TMP_DIR}/log
[ ! -f $QOS_LOG ] && echo -e "time\t\t\tlog_info" > "$QOS_LOG" && echo -e " create qos.log file"
[ ! -f ${QOS_LIB_DIR}/log ] && ln -sf $QOS_LOG ${QOS_LIB_DIR}/log

#################################################################################################
# general-use base API
QOS_RET()
{
	echo "$1"
}

QOS_INFO_PRINT()
{
	echo -e "$1"
}

QOS_DEBUG_PRINT()
{
	local con=$1
	echo -e "$con"
}
QOS_ERROR()
{
	echo -e "$1"
}

QOS_WRITE_FILE()
{
	echo -e "$1" >> "$2" 2>/dev/null
}

QOS_WRITE_LOG()
{
	local log="$1"
#return
	local file=$QOS_LOG
	local time=`date +%Y%m%d-%H.%M.%S`
	local item="${time}    ${log}"
	# if log size > 150K, save and recreate
	[ `ls -l "$file" | awk '{print $5}'` -gt 100000 ] && {
		# keep count of logfile below 10
		[ `ls ${QOS_TMP_DIR}/log/ | wc -l` -ge 10 ] && {
			rm ${QOS_TMP_DIR}/log/`ls ${QOS_TMP_DIR}/log | awk 'NR==1 {print $1}'`
		}
		mv "$file" "${QOS_TMP_DIR}/log/${time}_qos.log"  2>/dev/null
		QOS_WRITE_FILE "time\t\t\tlog_info" "$file"
	}
	echo -e "$item" >> "$file" 2>/dev/null
}

QOS_LOG_PRINT()
{
	local item="$1"
#return
	QOS_WRITE_LOG "$item"
	echo -e "$item"
}

# get val from indirect var
# aaa=123;bbb=aaa; eval ccc=\${$bbb};
# echo ccc        stdout is 123
indirect_var_get()
{
	local raw=$1
	#variable name can not include char like '.' and '-', so change to '_'
	local raw=`echo ${raw//"."/"_"}`
	local raw=`echo ${raw//"-"/"_"}`
	eval val=\${$raw}
	QOS_RET "$val"
}

# ser val to a indirect var
# r_1=0; n=1 ;a=5; eval "r_$n=$a"
indirect_var_set()
{
	local raw="$1"
	#variable name can not include char like '.' and '-', so change to '_'
	local raw=`echo ${raw//"."/"_"}`
	local raw=`echo ${raw//"-"/"_"}`
	local val="$2"
	eval "$raw=\"$val\""
}

var_len_get()
{
	var=$1
	local len=${#var}
	QOS_RET "$len"
}

dec2hex()
{
	[ `echo $1 | grep -c "0x"` -ne 0 ] && QOS_RET "$1" && return
	QOS_RET `printf 0x%x $1`
}

hex2dec()
{
	[ `echo $1 | grep -c "0x"` -eq 0 ] && QOS_RET "$1" && return
	QOS_RET `printf %d $1`
}

#################################################################################################
# QOS module state maintain
# awk field seprate with "="
local QOS_STATE_FILE="${QOS_TMP_DIR}/state"
[ ! -f $QOS_STATE_FILE ] && touch $QOS_STATE_FILE
ln -sf $QOS_STATE_FILE $QOS_LIB_DIR/state
qos_get_state()
{
	local key="$1"
	grep "^${key}.*" "$QOS_STATE_FILE" 2>&1 >/dev/null || {
		return 1
	}
	QOS_RET "`awk -F= "/^${key}/" $QOS_STATE_FILE | awk -F= '{print $2}'`"
}
qos_set_state()
{
	local key="$1"
	local cont="$2"
	grep "^${key}.*" "$QOS_STATE_FILE" 2>&1 >/dev/null || {
		QOS_WRITE_FILE "${key}=${cont}" "$QOS_STATE_FILE"
		return 0
	}
	sed "/^${key}/ s/=.*$/=${cont}/" -i "$QOS_STATE_FILE"
}
qos_delete_state()
{
	local key="$1"
	# CAUTION: Actually, iface and rule need call this handle. IN CASE of name-include(r1<r11), MUST set the pattern with '.'
	grep "^${key}\..*" $QOS_STATE_FILE 2>&1 >/dev/null && sed "/^${key}\..*/d" -i $QOS_STATE_FILE
}
qos_clear_state()
{
	echo >$QOS_STATE_FILE
}
## qos state operate handle
QOS_STATE()
{
	local cmd="$1"
	shift
	case "$cmd" in
		new)
			qos_set_state "$1"  "$1_state"
		;;
		clear)
			qos_clear_state
		;;
		set)
			qos_set_state "$1" "$2"
		;;
		get)
			QOS_RET "$(qos_get_state "$1")"
		;;
		del)
			qos_delete_state "$1"
		;;
	esac;
}

export QOS_THRESHOLD=$(config_get "$SNAME_GLOBAL" qos_threshold)
[ -z $QOS_THRESHOLD ] && QOS_THRESHOLD=0
export SUPPORT_QOS_THRESHOLD="true"

#################################################################################################
# system interfaces and devices
# qos config mode diff by product info, for now wvr450G / ER7520
export PRODUCT_INFO="ER7520"
export QOS_CONFIG_ER="TRUE"  # ER7520
export QOS_IFGROUP_SUPPORT="TRUE"  # ifgroup (WAN-ALL) support
export QOS_TPLIMIT_ALL="TRUE"      # xt_tplimit for both single-iface rule and group-iface rule

# As connection item of uplink and downlink in conntrack system share the SAME CTMARK,
# thus brings the puzzle that we can NOT limit both up&down link in different rules.
# To resolve it, give up the ctmark, instead by packet filter.
# 20151103
export QOS_APPLY_CONTRK="FALSE"

# qos filter condition for users, all rules enabled should add themselves to this two set
export QOS_SET_SRC="QOS_MISC_SET_SRC"
export QOS_SET_DST="QOS_MISC_SET_DST"


#export QOS_IFACE_BWLIMIT_SUPPORT="TRUE" # support bandwidth limit by interface

# get user-defined interface(zone) from UCI global setting
	# return the valid user interface
qos_user_ifaces_get()
{
	local list=""
	config_get list "$SNAME_GLOBAL" "$STYPE_IFACE"
	# verify the iface in list is defined?
	for iface in $list;do
		grep -q "config.*${STYPE_IFACE}.*${iface}" $QOS_UCI || {
			#echo -e "   iface not defined, delete from global list"
			local nr=`awk "/(list|option).*${STYPE_IFACE}.*${iface}/ {print NR}" $QOS_UCI`
			#sed "${nr}d" -i $QOS_UCI
			list=`echo $list | sed "s/${iface}//g"`
		}
	done
	QOS_RET "$list"
}

## local iface only defined for 450G, named "LAN" constly
[ -z $QOS_CONFIG_ER ] && echo -e " QOS config mode is NOT ER! " && export LAN_IFACE_NAME="LAN"
export IFACE_LIST=$(qos_user_ifaces_get)
[ ${#IFACE_LIST} -eq 0 ] && QOS_CONFIG_INVALID="true"
export IFACE_NUM=0
export DEV_LIST=""
export ZONE_LIST="$LAN_IFACE_NAME $IFACE_LIST"  # all ifaces participate in qos
local cnt=1
for iface in $ZONE_LIST; do
	IFACE_NUM=$((IFACE_NUM + 1))
	local dev=$(zone_get_wan_devices $iface)
	indirect_var_set ${iface}_dev "${dev// /,}"
	DEV_LIST="$DEV_LIST $dev "
	indirect_var_set ${iface}_rootid $cnt
	indirect_var_set ${iface}_linerate $LINERATE
	cnt=$((cnt+1))
done
[ -z $QOS_CONFIG_ER ] && export LAN_NETDEV=$(indirect_var_get ${LAN_IFACE_NAME}_dev)



ifgroup_dev()
{
	local dev="$1"
	local ret=1
	[ "$dev" = "$GRPUP_dev" -o "$dev" = "$GRPDOWN_dev" ] && ret=0
	QOS_RET $ret
}

netdev2rid()
{
	local dev="$1"
	local list="$ZONE_LIST $GRP_LIST"
	for iface in $list; do
		[ "$dev" = "$(indirect_var_get ${iface}_dev)" ] && {
            QOS_RET $(indirect_var_get ${iface}_rootid)
            return
        }
	done
	QOS_RET 0
}

#FASTPATH: SFE/HWNAT
fastpath_sw_on()
{
#	local sfe_switch=`uci -q get sfe.setting.switch`
#	[ "$sfe_switch" == "on" ]
# don't set sfe mark for qos rules, because of already support qos control in sfe.
	return 1
}

fastpath_hw_on()
{
#	local nss_switch=`uci -q get ecm.global.enable`
#	local hwnat_switch=`uci -q get hwnat.global.enabled`
#	[ "$nss_switch" == "on" -o "$hwnat_switch" == "1" ]
# set hwnat mark.
	return 0
}

fastpath_sw_real_on()
{
	local sfe_switch=`uci -q get sfe.setting.switch`
	[ "$sfe_switch" == "on" ]
}

fastpath_hw_real_on()
{
	local nss_switch=`uci -q get ecm.global.enable`
	local hwnat_switch=`uci -q get hwnat.global.enabled`
	[ "$nss_switch" == "on" -o "$hwnat_switch" == "1" ]
}

# get the netdev from interface name
	# should archived by zone module API
    # intf: LAN  WAN1 WAN2
intf2netdev()
{
	local inf=$1
	local dev=$(zone_get_device_byif $inf)
	QOS_RET "$dev"
}

# get the ZONE_name from hotplug $INTERFACE wan1_dev->WAN1
intf2zone()
{
	local intf=$1
	[ 0 -eq ${#intf} ] && QOS_RET ""
	local zone=$(zone_get_zone_byif $intf)
	QOS_RET "$zone"
}

# check the netdev is valid
    # exist in ifconfig
	# ret 0: valid;   1: invalid
valid_dev()
{
    local mydev="$1"
    [ ${#mydev} -eq 0 ] && QOS_RET "2" && return
    `ifconfig | grep -w "Link encap" | awk '{print $1}' | grep -w -q "$mydev"`
    QOS_RET "$?"
}

valid_zone()
{
    local myintf="$1"
    [ ${#myintf} -eq 0 ] && QOS_RET "2" && return

    # IF myintf not exist in IFACE_LIST, return false
    [ `echo $ZONE_LIST | grep -wc "${myintf}"` -eq 0 ] && QOS_RET "3" && return

    local mydev=$(zone_get_effect_devices $myintf)
    QOS_RET "$(valid_dev $mydev)"
}

#################################################################################################
local LOCK="/tmp/.qos/.lock"
QOS_LOCK()
{
	while : ; do
		[ ! -f $LOCK ] && break
		local pid=`awk -F";" 'NR==1 {print $1}' $LOCK`
		local name=`awk -F";" 'NR==1 {print $2}' $LOCK`
		QOS_LOG_PRINT "wait qos lock(pid $$)...... owned by pid $pid, $name"
		sleep 1
	done
	local pid=$$
	local name=`ps -w |grep -w $pid | grep -v grep | awk '{for(i=5;i<=NF;i++) printf("%s ", $i)}'`
	touch $LOCK
	QOS_WRITE_FILE "$pid; $name" $LOCK
	#QOS_LOG_PRINT "get qos lock for pid $pid, $name"
}
QOS_UNLOCK()
{
	#QOS_LOG_PRINT "release qos lock \n"
	rm $LOCK
}

##################################################################################
# single $0 sh debug mode
if [ "$1" = "pubdebug" ];then
	QOS_INFO_PRINT "##############  enter $0 debug mode  ##############"
	QOS_INFO_PRINT " @user iface list=$IFACE_LIST"
	QOS_INFO_PRINT " @zone list=$ZONE_LIST"
	QOS_INFO_PRINT " @dev list=$DEV_LIST"

	QOS_INFO_PRINT " @dev LAN =$LAN_NETDEV"


	for iface in $ZONE_LIST; do
		local dev=$(indirect_var_get ${iface}_dev)
		local rid=$(indirect_var_get ${iface}_rootid)
		echo -e "   $iface dev=$dev, rootid=$rid "
	done

    ret=$(valid_dev eth0)
    echo " @@@@@  eth 0 ret1 = $ret"
    ret=$(valid_dev)
    echo " @@@@@  ret2 = $ret"
    ret=$(valid_dev eth0.100)
    echo " @@@@@  ret3 = $ret"


	echo @@@@@@@@@@@@@@@@@@
	netdev2rid "br-lan"
	netdev2rid eth0.10
	netdev2rid ifb1

fi
