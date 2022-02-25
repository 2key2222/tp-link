#!/bin/sh
#Copyright (C) 2015 tplink.com

[ "$INC_QOS_TC" != "" ] && return
export INC_QOS_TC="INC"

. /lib/qos-tplink/qos_public.sh
. /lib/qos-tplink/qos_cid.sh
. /lib/qos-tplink/qos_mark.sh

# TC adapt for qos-tplink
local TC=tc
local QDISC_C=htb
local QDISC_L=pfifo_fast
#local QDISC_L="sfq perturb 10"
local DEFAULT_HDL=9990  # for easy to arith calc, set it to decimal, all netdev has same defaultID
local R2Q_HTB=10
local PRIO_DEFAULT=7 #lowest prio of htb class
local MAX_BURST=100000  # NOT sure
local PRIO_FLT_DEF=2
local PRIO_FLT=6


TC_DEBUG()
{
	local con="$1"
#	echo -e "$con"
}

# kmods insmod and rmmod
qos_kmod_load()
{
	local ko_path="/lib/modules/`uname -r`"
	[ `lsmod | grep -c sch_htb` -eq 0 ] && insmod ${ko_path}/sch_htb.ko
	[ `lsmod | grep -c sch_sfq` -eq 0 ] &&  insmod ${ko_path}/sch_sfq.ko
	[ `lsmod | grep -c cls_fw` -eq 0 ] && insmod ${ko_path}/cls_fw.ko
	[ `lsmod | grep -c cls_u32` -eq 0 ] && insmod ${ko_path}/cls_u32.ko
}

qos_kmod_unload()
{
	local ko_path="/lib/modules/`uname -r`"
	[ `lsmod | grep -c sch_htb` -gt 0 ] && rmmod ${ko_path}/sch_htb.ko
	[ `lsmod | grep -c sch_sfq` -gt 0 ] && rmmod ${ko_path}/sch_sfq.ko
	[ `lsmod | grep -c cls_fw` -gt 0 ] && rmmod ${ko_path}/cls_fw.ko
	[ `lsmod | grep -c cls_u32` -gt 0 ] && rmmod ${ko_path}/cls_u32.ko
}

# get MTU by netdev,  stub to const 1600
dev_mtu_get()
{
	local dev=$1
	local mtu=1500
	# TODO:  get mtu by netdev
	QOS_RET $mtu
}

# get HTB burst from rate & mtu 
htb_burst_get()
{
	local dev=$1
	local rate=$2
	local burst=0
	local mtu=$(dev_mtu_get $dev)

	# cut of the unit
	rate=`echo $rate | sed 's/[ ]//g' | sed 's/b.*//g'`
	rate=`echo $rate | sed 's/[Kk]/000/'`
	rate=`echo $rate | sed 's/[Mm]/000000/'`
	rate=`echo $rate | sed 's/[Gg]/000000000/'`

	#calc burst,  according to C9
	burst=$(($rate/8/100))
	[ $burst -lt $mtu ] && burst=$mtu
	[ $burst -gt $MAX_BURST ] && burst=$MAX_BURST

	QOS_RET "$burst"
}


# get htb quantum by rate,ceil,r2q, 
htb_quantum_get()
{
	local dev=$1
	local rate=$2
	local r2q=$3
	local mtu=$(dev_mtu_get $dev)
	
	# cut of the unit
	rate=`echo $rate | sed 's/[ ]//g' | sed 's/b.*//g'`
	rate=`echo $rate | sed 's/[Kk]/000/'`
	rate=`echo $rate | sed 's/[Mm]/000000/'`
	rate=`echo $rate | sed 's/[Gg]/000000000/'`

	#quantum calc by HTB manual
	# According to HTB manual, import divisor const 8
		# when r2q value is 10 and typical MTU is 1500, it is good for rates from 120 kbps #
	quantum=$(($rate / $r2q / 8))
	if [ $quantum -lt $mtu ];then
		quantum=$mtu
	elif [ $quantum -gt $mtu ];then
		quantum=60000
	fi
	QOS_RET "$quantum"
}

# get the tc cmd arg val from the tc state string
# eg: str="qdisc htb 3: root refcnt 2 r2q 10 default 9993 direct_packets_stat 0"
#    `arg_val_get $str default`  will return 9993
arg_val_get()
{
	local str="$1"
	local arg_name="$2"
	echo `echo "$str" | awk '{ for(i=1;i<NF;i++) {if ($i==pp) {print $(i+1);exit}}}' pp="$arg_name"`
}

# destroy TC tree on all LAN/WAN netdevs
qos_tc_destroy()
{
	qos_tcid_flush
	#qos_mark_flush

	for dev in ${DEV_LIST}; do
		$TC qdisc del dev $dev root 2>/dev/null
	done

	#qos_kmod_unload
	QOS_LOG_PRINT "qos_tc_destroy, flush tc on all netdevs!"
}

# destroy tc root on dev
qos_tc_del_rule_bydev()
{
	local dev="$1"
	QOS_WRITE_LOG " info, delete tc root qdisc concerned by $dev"
	$TC qdisc del dev $dev root 2>/dev/null
}

# check IF dev has been init, and install rules
# make sure we shall NOT install rule twice for this dev
	# ret: 0 no qos init   1 has init
qos_tc_dev_check()
{
	local dev="$1"
	local ret=0
	[ "$QDISC_C" = "`$TC -p qdisc show dev $dev | awk 'NR==1 {print $2}'`" ] && ret=1
	QOS_RET "$ret"
}

# api to create a basic TC root tree on dev
# TC tree framework:
#      root wn:0
#      ----
#        |
# L1:  class :1
#     -------------------------------
#        ...   |      ...           |
# L2:    ... class:n  ...        class:def
#     base class :1 = L1 class, reflected as the intf global limit
qos_tc_dev_init()
{
	local dev=$1
	local rate=`echo $2 | sed 's/kbps/kbit/g'`  # unit kbps->kbit
	local rid=$(netdev2rid $dev)

	# 1. IF root qdisc is QDISC_C, just return to keep the user rule mount on it.
	[ $(qos_tc_dev_check $dev) -ne 0 ] && { 
		QOS_WRITE_LOG " info, tc root on dev $dev was init before, just return !" && return
	}

	$TC qdisc del dev $dev root 2>/dev/null 
	QOS_WRITE_LOG "\t$TC qdisc add dev $dev root handle $rid:0 $QDISC_C default $DEFAULT_HDL r2q $R2Q_HTB"
	$TC qdisc add dev $dev root handle $rid:0 $QDISC_C default $DEFAULT_HDL r2q $R2Q_HTB

	# 2. create a base class on root
	local burst=$(htb_burst_get $dev $rate)
	local quantum=$(htb_quantum_get $dev $rate $R2Q_HTB)
	local ceil=$rate
	local cburst=$(htb_burst_get $dev $ceil)
	QOS_WRITE_LOG "\t$TC class add dev $dev parent $rid:0 classid $rid:1 $QDISC_C rate $rate burst $burst cburst $cburst quantum $quantum"
	$TC class add dev $dev parent $rid:0 classid $rid:1 $QDISC_C rate $rate burst $burst cburst $cburst quantum $quantum
	
	# 3. create default branch class
		# for WAN egress, default rate should be uplik limit and lowest prio
	local rate_def=$rate
	local burst_def=$(htb_burst_get $dev $rate_def)
	local quantum_def=$(htb_quantum_get $dev $rate_def $R2Q_HTB)
	local ceil_def=$rate_def
	local cburst_def=$(htb_burst_get $dev $ceil_def)
	QOS_WRITE_LOG "\t$TC class add dev $dev parent $rid:1 classid $rid:$DEFAULT_HDL $QDISC_C prio $PRIO_DEFAULT rate $rate_def burst $burst_def cburst $cburst_def quantum $quantum_def"
	$TC class add dev $dev parent $rid:1 classid $rid:$DEFAULT_HDL $QDISC_C prio $PRIO_DEFAULT rate $rate_def burst $burst_def cburst $cburst_def quantum $quantum_def
	
	# add the default filter
	[ -z $DEADBEEF_IFGROUP ] || {
		QOS_WRITE_LOG "\t$TC filter add dev $dev parent $rid:0 prio $PRIO_FLT_DEF protocol ip u32 match u32 0 0 classid $rid:1"
		$TC filter add dev $dev parent $rid:0 prio $PRIO_FLT_DEF protocol ip u32 match u32 0 0 classid $rid:1
	}

	# 4. tc.data file for DFX 
		# TODO    tc.data 
}

qos_tc_iface_init()
{
	local iface="$1"
	local dev=$(indirect_var_get ${iface}_dev)

	config_get uplink "$iface" "uplink"
	# IF uplink not exist, USE line-rate
	[ ${#uplink} -eq 0 -o `echo $uplink|sed 's/[a-zA-Z]//g'` -eq 0 ] && uplink=$(indirect_var_get ${iface}_linerate)
	uplink="`echo $uplink | sed 's/[^0-9]//g'`kbps"
	qos_tc_dev_init "$dev" "$uplink"
}

# API to create a base downlink class(A WAN) on LAN_NETDEV 
#  TC tree framework:
#                 root
#                  |
#               class:1
#      ---------------------------------
#      |                |              |   
#      class:WAN1   class:WAN2  ...   class:def
# L1:  ---------    ----------
#       ...    |       ...   |
# L2:   ...    def     ...   def
#    number of L1 class is defined by WAN number
#    class :1  means WAN1->LAN  downlink
# THIS handle only called in 450G  system
qos_tc_dev_init_LAN()
{
	local dev=$1
	local drate_WAN=`echo $2 | sed 's/kbps/kbit/g'`  # unit kbps->kbit
	local intf_WAN=$3   # WAN intf 
	local rid=$(netdev2rid $dev)

	
	# 1. create dev root qdisc HTB, IF NO root qdisc HTB is found
		# CAUTION: L1 default branch SUM rate 
	local defid=$DEFAULT_HDL
	local op="add"
	local rate_def=0     # for the default branch
	if [ "$QDISC_C" != "`$TC -p qdisc show dev $dev | awk 'NR==1 {print $2}'`" ]; then 
		#QOS_WRITE_LOG " init tc LAN, , root qdisc NOT created!"
		# 1.1 
		QOS_WRITE_LOG "\t$TC qdisc add dev $dev root handle $rid:0 $QDISC_C default $defid r2q $R2Q_HTB"
		$TC qdisc add dev $dev root handle $rid:0 $QDISC_C default $defid r2q $R2Q_HTB

		# add root class as the single iface downlink parent
		local rate=`echo $LAN_linerate | sed 's/kbps/kbit/g'`
		local burst=$(htb_burst_get $dev $rate)
		local quantum=$(htb_quantum_get $dev $rate $R2Q_HTB)
		local ceil=$rate
		local cburst=$(htb_burst_get $dev $ceil)
		QOS_WRITE_LOG "\t$TC class add dev $dev parent $rid:0 classid $rid:1 $QDISC_C rate $rate burst $burst cburst $cburst quantum $quantum"
		$TC class add dev $dev parent $rid:0 classid $rid:1 $QDISC_C rate $rate burst $burst cburst $cburst quantum $quantum

		# add the default filter for ifgroup
		[ -z $DEADBEEF_IFGROUP ] || {
			QOS_WRITE_LOG "\t$TC filter add dev $dev parent $rid:0 prio $PRIO_FLT_DEF protocol ip u32 match u32 0 0 classid $rid:1"
			$TC filter add dev $dev parent $rid:0 prio $PRIO_FLT_DEF protocol ip u32 match u32 0 0 classid $rid:1
		}

		# 1.2 get L1 default branch rate for LAN egress
		op="add"
		rate_def=$drate_WAN
	else
		# IF WAN->LAN downlink L1 class has created
			#    cid.data has __downlinkroot_WAN cid alloced
			# && br-lan tc tree find class :cid
		# just return to keep the rules mount safe
		local cid=$(($(netdev2rid $(indirect_var_get ${intf_WAN}_dev))+1))
		[ $cid -ne 0 ] && {
			local cnt=`$TC -p class show dev $dev | grep -cw "$rid:$cid"`
			[ $cnt -gt 0 ] && QOS_WRITE_LOG " init tc LAN, downlink $intf_WAN was init before, just return !" && return
		}
		#QOS_WRITE_LOG " init tc LAN, root qdisc need change default branch!"
		op="change"
		
		# 2. IF default exist, sum the rate and change the L1 default branch 
		local rate=`echo $drate_WAN | sed 's/[A-Za-z]//g'`
		#local rate_pre=`$TC -p class show dev $dev | grep -w "$rid:$defid"| awk '{print $8}' | sed 's/bit//g'`
		local rate_pre=$(arg_val_get "`$TC -p class show dev $dev | grep -w "$rid:$defid"`" rate)
		local wt=`echo $rate_pre | sed 's/[0-9]//g' | sed 's/bit//g'` 
		if [ "$wt" = "k" -o "$wt" = "K" ]; then
			wt=1
		elif [ "$wt" = "m" -o "$wt" = "M" ]; then
			wt=1000
		else
			wt="1/1000"
		fi
		rate_pre=`echo $rate_pre | sed 's/[A-Za-z]//g'`
		local rate_total=$(($rate_pre * $wt + $rate))
		[ $rate_total -ge `echo $LAN_linerate | sed 's/[A-Za-z]//g'` ] && rate_total=`echo $LAN_linerate | sed 's/[A-Za-z]//g'`
		rate_def=${rate_total}kbit
	fi

	# $op the root default branch, if a rate change or branch create
	local burst_def=$(htb_burst_get $dev $rate_def)
	local quantum_def=$(htb_quantum_get $dev $rate_def $R2Q_HTB)
	local ceil_def=$rate_def
	local cburst_def=$(htb_burst_get $dev $ceil_def)
	QOS_WRITE_LOG "\t$TC class $op dev $dev parent $rid:0 classid $rid:$defid $QDISC_C prio $PRIO_DEFAULT rate $rate_def burst $burst_def cburst $cburst_def quantum $quantum_def"
	$TC class $op dev $dev parent $rid:0 classid $rid:$defid $QDISC_C prio $PRIO_DEFAULT rate $rate_def burst $burst_def cburst $cburst_def quantum $quantum_def
	
	# 2. create a L1 downlink class root for A wan 
	local rate=$(indirect_var_get drate_WAN)
	#rate_total=$(($rate_total + `echo $rate | sed 's/[a-zA-Z].*//g'`)) # NO unit for arith op
	local quantum=$(htb_quantum_get $dev $rate $R2Q_HTB)
	local burst=$(htb_burst_get $dev $rate)
	local ceil=$rate
	local cburst=$(htb_burst_get $dev $ceil)
	
	# 3. set up the WAN->LAN downlink flow limit class
	# 3.1 get the L1 class id with dummy_rule
	local cid=$(($(netdev2rid $(indirect_var_get ${intf_WAN}_dev))+1))
	[ "$cid" -eq 0 ] && QOS_WRITE_LOG " error, qos_tc_init_root_LAN, alloc downlink cid error!" && QOS_RET 1 && return
	QOS_WRITE_LOG "\t$TC class add dev $dev parent $rid:1 classid $rid:$cid $QDISC_C rate $rate burst $burst cburst $cburst quantum $quantum"
	$TC class add dev $dev parent $rid:1 classid $rid:$cid $QDISC_C rate $rate burst $burst cburst $cburst quantum $quantum

	# 4 tc.data file for DFX 
		# TODO    tc.data 
	#QOS_WRITE_LOG "  create $intf_WAN  downlink L1 class root tc on $dev / $rid:$cid done!"
} # end qos_tc_init_root_LAN

# UCI 'global' section init handle
	# this is the ENTRY condition of qos 
qos_tc_init()
{
	# 1. generate a basic tc root for all WAN and LAN devs
	for iface in $IFACE_LIST; do
		local dev=$(indirect_var_get ${iface}_dev)
		# IF dev is valid
		[ $(valid_dev $dev) -ne 0 ] && QOS_WRITE_LOG " info, $iface dev invalid, skip tc init!" && continue

		qos_tc_iface_init "$iface"
		
		# setup wan downlink root class on LAN_NETDEV
		# get downlink limit rates for lan intf, IF downlink not exist, USE line-rate
		config_get downlink "$iface" "downlink"
		[ ${#downlink} -eq 0 -o `echo $downlink|sed 's/[a-zA-Z]//g'` -eq 0 ] && downlink=$(indirect_var_get ${iface}_linerate)
		downlink="`echo $downlink | sed 's/[^0-9]//g'`kbps"
		qos_tc_dev_init_LAN "$LAN_NETDEV" "$downlink" "${iface}"
	done

	[ -z $DEADBEEF_IFGROUP ] && return
	# 2. init ifb 
	for iface in $GRP_LIST; do
		local dev=$(indirect_var_get ${iface}_dev)
		local rid=$(netdev2rid $dev)
		QOS_WRITE_LOG "$TC qdisc add dev $dev root handle $rid:0 $QDISC_C default $DEFAULT_HDL r2q $R2Q_HTB"
		$TC qdisc add dev $dev root handle $rid:0 $QDISC_C default $DEFAULT_HDL r2q $R2Q_HTB
		local rate=$(indirect_var_get ${iface}_linerate) 
		rate=`echo $rate | sed 's/kbps/kbit/g'`
		local burst=$(htb_burst_get $dev $rate)
		local quantum=$(htb_quantum_get $dev $rate $R2Q_HTB)
		local ceil=$rate
		local cburst=$(htb_burst_get $dev $ceil)
		QOS_WRITE_LOG "$TC class add dev $dev parent $rid:0 classid $rid:$DEFAULT_HDL $QDISC_C prio $PRIO_DEFAULT rate $rate burst $burst cburst $cburst quantum $quantum"
		$TC class add dev $dev parent $rid:0 classid $rid:$DEFAULT_HDL $QDISC_C prio $PRIO_DEFAULT rate $rate burst $burst cburst $cburst quantum $quantum
	done
}

# get parent classid for user_rule
	# $2: represent the classify base, generally it is IP of user_rule
#CAUTION:  pcid=WAN ser_number in numerical for WVR450Gv3(single level tree classified by IP)
tc_parentcid_get()
{
	local dev=$1
	local rule=$2
	local id=0

	# import the dev-tc.data
		# tc.data file manage and maintain the whole TC architecture of $dev

	# 1. get sub classification basis of rule
	#config_get newip "$rule" "ip"

	# 2. traverse the dev-tc.data to confirm if there is a SAME ip already exist
		# if so, get the rule_parent,  rule=$rule_parent
		# TODO

	# 3. get cid of rule_parent from tcid.data
		# TODO 
			# id=$(qos_tcid_getby_rule $rule $dev)
			# [ id -eq 0] 

	# 4. confirm the rule is a total NEW guy, so get the pcid by WAN ser_number
		# simply mount rule to root class
		# FOR LAN dev pcid=cid in tcid.data by "__downlinkroot_WAN1" (WVR450Gv3 single level tree classified by IP etc)
		# FOR WAN dev pcid=1 constant, represent the top level class
	if [ "$dev" = "$LAN_NETDEV" -o "$dev" = "$dmz_dev" ]; then
		config_get if_pong "$rule" "if_pong"
		id=$(($(netdev2rid $(indirect_var_get ${if_pong}_dev))+1))
	elif [ "$dev" = "$GRPUP_dev" -o "$dev" = "GRPDOWN_dev" ] ;then
		# for ifb dev, user rule class should always mounted on ROOT
		id=0
	else
		# for uplink dev, rule class mount to root:1, which the total limit class for iface .
		id=1;
	fi
	QOS_RET "$id"
}

# mount user_rule as a handle to a subclass, which is created internally
	#    ### IF necessary, find a parent classid first ***
	#    subclass generate   HTB
	#    leaf generate       SFQ
	#    filter generate     fwmark 
# ret:  !0 valid nfmark, for netfilter chain set
#       0 error, total rule num exceed QOS_SPEC
qos_tc_add_rule()
{
	local dev=$1
	local user_rule=$2
	local rate=`echo $3 | sed 's/bps/bit/g'`
	local rid=$(netdev2rid $dev)
	local ret=0
	local mask=$QOS_MARK_MASK

	# 1. alloc a nfmark for rule
	local nfmark=$(qos_mark_alloc $user_rule)
	[ $nfmark = 0 ] && QOS_RET $nfmark && return 1

	# 2. alloc tc classid (handleid)
	local cid=$(qos_tcid_alloc $user_rule $dev)
	[ $cid -eq 0 ] && $(qos_mark_free_bymark $nfmark) && QOS_RET $cid && return 1
	local hid=$cid   # leaf handle id can equal to classid?

	# IF dev is a ifbdev ? transfer to groupmark and groupmask
	[ -z $DEADBEEF_IFGROUP ] || {
		[ $(ifgroup_dev $dev) -eq 0 ] && {
			nfmark=`awk "BEGIN{f=lshift($nfmark,$QOS_MARK_BIT_LEN); print f}"`
			nfmark=$(dec2hex $nfmark)
			mask=$QOS_GMARK_MASK
		}
	}

	# 3. get parent class id
	local pcid=$(tc_parentcid_get $dev $user_rule)

	# 4. set up class and filter
		# protype:
		# tc class add dev eth0 parent rid:0 classid rid:cid htb rate $MYRATE;
		# tc filter add dev eth0 parent rid:0 handle nfmark fw flowid rid:cid;
		# ##  leaf no need ## tc qdisc add dev eth0 parent rid:cid handle hid sfq perturb 10;
	local quantum=$(htb_quantum_get $dev $rate $R2Q_HTB)
	local burst=$(htb_burst_get $dev $rate)
	local ceil=$rate
	local cburst=$(htb_burst_get $dev $ceil)

	QOS_WRITE_LOG "\t$TC class add dev $dev parent $rid:$pcid classid $rid:$cid $QDISC_C rate $rate burst $burst cburst $cburst quantum $quantum"
	QOS_WRITE_LOG "\t$TC filter add dev $dev parent $rid:0 prio $PRIO_FLT handle $nfmark/$mask fw flowid $rid:$cid"
	[ "$QDISC_L" = 'pfifo_fast' ] || QOS_WRITE_LOG "\t$TC qdisc add dev $dev parent $rid:$cid handle $hid $QDISC_L"

	$TC class add dev $dev parent $rid:$pcid classid $rid:$cid $QDISC_C rate $rate burst $burst cburst $cburst quantum $quantum
	$TC filter add dev $dev parent $rid:0 prio $PRIO_FLT handle $nfmark/$mask fw flowid $rid:$cid
	# only setup classless handle for NON-pfifo_fast qdisc 
	[ "$QDISC_L" = 'pfifo_fast' ] || $TC qdisc add dev $dev parent $rid:$cid handle $hid $QDISC_L

	QOS_RET "$nfmark"
}


# transfer tc state file to tc command and install
tc_state2cmd()
{
	local state="$1"
	local dev="$2"

	# 1. root qdisc process
	local st_root=`awk '/^qdisc.*root.*r2q/' $state`
	local qd=$(arg_val_get "$st_root" qdisc)
	local rid=$(arg_val_get "$st_root" $qd)
	local r2q=$(arg_val_get "$st_root" r2q)
	local def_cid=$(arg_val_get "$st_root" default)
	QOS_WRITE_LOG "\t$TC qdisc add dev $dev root handle $rid $qd default $def_cid r2q $r2q"
	$TC qdisc add dev $dev root handle $rid $qd default $def_cid r2q $r2q

	# 2. class process
	local st_clss=`awk 'BEGIN{ORS=",\n"} /^class/ ' $state`
	IFS_BAK=$IFS; IFS=','
	for cls in $st_clss; do
		cls="`echo -e "$cls" | sed 's/[\r\n]//g'`"
		qd=$(arg_val_get $cls class)
		classid=$(arg_val_get $cls $qd)
		parent=$(arg_val_get $cls parent)
		[ ${#parent} -eq 0 ] && parent="root"
		prio=$(arg_val_get $cls prio)
		[ ${#prio} -eq 0 ] && prio=0
		rate=$(arg_val_get $cls rate)
		ceil=$(arg_val_get $cls ceil)
		burst=$(arg_val_get $cls burst)
		cburst=$(arg_val_get $cls cburst)
		quantum=$(htb_quantum_get $dev $rate $r2q)
	
		QOS_WRITE_LOG "\t$TC class add dev $dev parent $parent classid $classid $qd prio $prio rate $rate ceil $ceil burst $burst cburst $cburst quantum $quantum"
		$TC class add dev $dev parent $parent classid $classid $qd prio $prio rate $rate ceil $ceil burst $burst cburst $cburst quantum $quantum 
	done
	
	# 3. filter process
	local st_flts=`awk 'BEGIN{ORS=",\n"} /^filter.*handle/' $state`
	for flt in $st_flts; do
		flt="`echo -e "$flt" | sed 's/[\r\n]//g'`"
		parent=$(arg_val_get $flt parent)
		handle=$(arg_val_get $flt handle) # fwmark in hex
		#handle=`printf "%d" $handle`
		classid=$(arg_val_get $flt classid)
		prio=$(arg_val_get $flt pref)
		QOS_WRITE_LOG "\t$TC filter add dev $dev parent $parent handle $handle fw flowid $classid"
		$TC filter add dev $dev parent $parent prio $prio handle $handle fw flowid $classid 
	done
	
	# 4. leaf process, only support sfq
	[ "$QDISC_L" = 'pfifo_fast' ] || {
		local st_leafs=`awk 'BEGIN{ORS=",\n"} /^qdisc.*parent/' $state`
		for leaf in $st_leafs; do
			leaf="`echo -e "$leaf" | sed 's/[\r\n]//g'`"
			qd=$(arg_val_get $leaf qdisc) 
			handle=`echo $(arg_val_get $leaf $qd)| sed 's/://g'`
			parent=$(arg_val_get $leaf parent)
			#[ "$qd" = sfq ] && qd="$QDISC_L"
			QOS_WRITE_LOG "\t$TC qdisc add dev $dev parent $parent handle $handle $QDISC_L"
			$TC qdisc add dev $dev parent $parent handle $handle sfq perturb 10
			#########  FUCKING resonless, why canNOT use $QDISC_L?!
		done
	}
	IFS=$IFS_BAK
}


# uninstall user rule from TC tree, uplink and downlink
# This is fake del packing base on tc NOT support delete-op
qos_tc_del_rule()
{
	local dev_list="$1"
	local mark_list="$2"
	local cid_list="$3"
	local FILE_ST="/tmp/tc_state.tmp"

#echo -e " @@ args: $dev_list, $mark_list, $cid_list "
	for dev in $dev_list; do
		[ $(valid_dev $dev) -ne 0 ] && { 
			# The situation is only present on hotplug ifdown response
			# uplink rule has delete with netdev smashed by system
			QOS_WRITE_LOG "  info, $dev not valid" 
			QOS_RET 1 
			continue
		}
		# extract dev tc tree
		`$TC -p qdisc show dev $dev > $FILE_ST`
		`$TC -p class show dev $dev >> $FILE_ST`
		`$TC -p filter show dev $dev >> $FILE_ST`

		# delete filter and class defined by the list
		for mark in $mark_list; do
			mark=`printf 0x%x $mark`
#echo -e " @@ sed \"/^filter.*fw handle ${mark}.*/d\" -i $FILE_ST"
			`sed "/^filter.*fw handle ${mark}.*/d" -i $FILE_ST`
		done
		
		# IF tc on dev have NO leaf left, just flush the dev
		grep -q "^filter.*fw handle.*" $FILE_ST || {
			QOS_WRITE_LOG " info, no filter leaf left on $dev, should destroy tc! "
			$TC qdisc del dev $dev root 2>/dev/null
			QOS_RET 0 && return 0
		}

		for cid in $cid_list; do
#echo -e " @@ sed \"/^class ${QDISC_C} [1-9]:${cid}.*/d\" -i $FILE_ST"
			`sed "/^class ${QDISC_C} [1-9]:${cid}.*/d" -i $FILE_ST`
			[ "$QDISC_L" = 'pfifo_fast' ] || `sed "/^qdisc.*${cid}.*/d" -i $FILE_ST`
		done

		# transfer the state file to tc command and config 
		QOS_WRITE_LOG " info, rebuild the tc tree for warm tc-rule-delete "
		$TC qdisc del dev $dev root 2>/dev/null
		tc_state2cmd "$FILE_ST" "$dev"
	done
	QOS_RET 0 && return 0
}

##################################################################################
# single $0 sh debug mode
if [ "$1" = "tcdebug" ];then
	QOS_INFO_PRINT "##############  enter $0 debug mode  ##############"
		echo -e "ZONE_LIST=$ZONE_LIST"
	
	if [ $2 = "flush" ];then
		QOS_INFO_PRINT " ### debug, flush TC on all devs"
		qos_tc_destroy 

	elif [ $2 = "init" ];then
		QOS_INFO_PRINT " ### debug, create TC root on all LAN/WAN devs"
		qos_tc_destroy
		qos_tc_init_root
		#qos_tc_init_root_WAN $WAN1_dev 20000kbit
		#qos_tc_init_root_WAN $WAN2_dev 8000kbit
		#qos_tc_init_root_LAN $LAN_NETDEV 100000kbit WAN1
		#qos_tc_init_root_LAN $LAN_NETDEV 50000kbit WAN2
		

	elif [ $2 = "pcid" ];then
		QOS_INFO_PRINT " ### debug, get TC parent class id test "
		ret=$(tc_parentcid_get $LAN_NETDEV r1) && QOS_INFO_PRINT " @@@@ ret $ret"
		ret=`tc_parentcid_get $LAN_NETDEV r2` && QOS_INFO_PRINT " @@@@ ret $ret"

	elif [ $2 = "addrule" ];then
		QOS_INFO_PRINT " ### debug, add TC rule test "
		rule=$3
		config_get rate "$rule" "rate_max"
	
		# uplink rule add to WAN dev 
		config_get inf "$rule" "if_pong"
		local dev=$(indirect_var_get ${inf}_dev)
		QOS_INFO_PRINT "   ###debug, add uplink rule $rule rate $rate on $inf - $dev"
		[ $(var_len_get `tc -p class ls dev $dev`) -eq 0 ] && QOS_ERROR " ###debug, dev $dev NO root class, create first!" && exit
	
		nfmark=$(qos_tc_add_rule $dev $rule $rate)
		[ $nfmark = 0 ] && QOS_ERROR "\n ###debug, add rule uplink $dev tc fail!" && exit

	elif [ $2 = "delrule" ]; then
		QOS_INFO_PRINT " ### debug, delete TC rule test "
		shift 2
		dev=$1
		mark=$2
		cid=$3
		qos_tc_del_rule $dev $mark $cid
		
    elif [ $2 = "test" ]; then
		htb_burst_get "1Gbps"
		
		
	fi
fi
