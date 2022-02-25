#!/bin/sh

ROUTING_MODE=1

#$1: master infaces
check_infaces_status()
{
	. /lib/zone/zone_api.sh

	local o_infaces

	zones=`zone_get_zonelist`

	for zone in $zones; do
		if [ "$zone" != "LAN" ]; then
			ifaces=`zone_get_effect_ifaces $zone`
			for i in $ifaces; do
				for j in "$1"; do				
					[ "$i" != "$j" ] && append o_infaces $i
				done
			done
		fi
	done

	local flag=0

	for inface in "$o_infaces"; do
		. /lib/balance/api.sh
	
		gateway=`get_inface_gw $1`

		if [ -n "$gateway" ];then
			ping -c 3 -W 2 -s 4 -q $gateway &> /dev/null
			[ $? -eq 0 ] && let flag++			
		fi
	done

	if [ $flag -gt 0 ];then
		echo "1"
	else
		echo "0"
	fi
}

# $1:inface
get_inface_status()
{
	. /lib/balance/api.sh                                           
	state=`balance_get_state $1`                                    
        
	if [ "$state" == "on" ];then   
		echo "1"               
	else                           
		echo "0"               
	fi
}


#$1 : inface
inface_existed()
{
	. /lib/zone/zone_api.sh

	dev=`zone_get_effect_devices $1`

	tmp=`ifconfig $dev 2>/dev/null`

	if [ "$tmp" != " " ];then
		echo "1"
	else
		echo "0"
	fi
}

get_master_infaces()
{
	config_get slave_iface $1 slave_iface
	if [ "$g_slave_iface" == "$slave_iface" ];then
		backup_master_ifaces=`uci get line_backup.$1.master_iface 2>/dev/null`
	fi
}

# when master inface down, let slave inface take the flow
#$1 slave_inface
clean_inface_flow()
{
	local g_slave_iface=$1 backup_master_ifaces flag=0

	. /lib/functions.sh

	config_load line_backup
	config_foreach get_master_infaces rule

	[ -z "$backup_master_ifaces" ] && exit 1

	master_iface=`uci get load_balance.interface.master_iface 2>/dev/null`
	slave_iface=`uci get load_balance.interface.slave_iface 2>/dev/null`


	for i in $backup_master_ifaces; do
		if [ -n "$master_iface" ];then
			for j in $master_iface; do
				if [ $i == $j ];then
					flag=1
					list_remove master_iface $i
					break;
				fi
			done
		fi
		[ $flag -eq 0 ] && uci add_list load_balance.interface.master_iface=$i

		flag=0
	done

	if [ -n "$slave_iface" ];then
		for i in $slave_iface;do
			if [ $1 == $i ]; then
				flag=1
				break;
			fi
		done
	fi

	if [ $flag -eq 0 ]; then
		uci add_list load_balance.interface.slave_iface=$1
	fi

	uci commit 2>/dev/null
	
	/etc/init.d/default_balance restart

	load_balance=`uci get load_balance.balance.state 2>/dev/null`		
	if [ "$load_balance" == "on" ]; then
		/etc/init.d/load_balance restart
	else
		/etc/init.d/load_balance stop
		/usr/sbin/load_balance &
	fi
}

CONFIG_NAME="mwan3"

# when master inface up, recover the flow from slave infaces
#$1 slave_inface
recover_inface_flow()
{
	local g_slave_iface=$1 backup_master_ifaces flag=0

	. /lib/functions.sh

	config_load line_backup
	config_foreach get_master_infaces rule

	for i in $backup_master_ifaces; do
		uci del_list load_balance.interface.master_iface=$i 2>/dev/null
	done

	uci del_list load_balance.interface.slave_iface=$1 2>/dev/null

	uci commit 2>/dev/null
	
	/etc/init.d/default_balance restart

	load_balance=`uci get load_balance.balance.state 2>/dev/null`
	if [ "$load_balance" == on ]; then
		/etc/init.d/load_balance restart
	else	
		/etc/init.d/load_balance stop
		/usr/sbin/load_balance &		
	fi
}

# ifup inteface
#$1: interface
backup_ifup()
{
    if [ -z "ROUTING_MODE" ]; then
        . /lib/zone/zone_api.sh

        local retry_cnt=0                         
        inface=`zone_get_effect_ifaces $1`
        while [ $((retry_cnt++)) -lt 3 ] && [ -z "$inface" ]; do
                sleep 1
                inface=`zone_get_effect_ifaces $1`
                #echo "up $1 retry $retry_cnt" > /dev/console
        done

        . /lib/functions/network.sh
        network_flush_cache
        $(network_is_up $inface) || {
            ifup $inface
            /lib/l2tp/ifup-l2tp.sh $1 2>/dev/null
            /lib/pptp/ifup_down.sh ifup $1 2>/dev/null
        }
    else
        # notify to online check.
        . /lib/online_check/online_api.sh
        update_online_dev_blocked "$1" "0"
    fi
}

#$1: interface
backup_ifdown()
{
    if [ -z "ROUTING_MODE" ]; then
        . /lib/zone/zone_api.sh

        local retry_cnt=0                         
        inface=`zone_get_effect_ifaces $1`
        while [ $((retry_cnt++)) -lt 3 ] && [ -z "$inface" ]; do
                sleep 1
                inface=`zone_get_effect_ifaces $1`
                #echo "down $1 retry $retry_cnt" > /dev/console
        done

        . /lib/functions/network.sh
        network_flush_cache
        $(network_is_up_autostart $inface) && {
            ifdown $inface
            /lib/l2tp/ifdown-l2tp.sh $1 2>/dev/null
            /lib/pptp/ifup_down.sh ifdown $1 2>/dev/null
        }
    else
        # notify to online check.
        . /lib/online_check/online_api.sh
        update_online_dev_blocked "$1" "1"
    fi
}


# ifup intefaces
#$1: interfaces
backup_ifup_infaces()
{
	[ -n "$1" ] || return 1

	for inface in $1 ;do
		backup_ifup $inface
	done
}

#$1: interfaces
backup_ifdown_infaces()
{
	[ -n "$1" ] || return 1

	for inface in $1 ;do
		backup_ifdown $inface
	done
}

#$1: interfaces
line_backup_flow_stop()
{
	[ -n "$1" ] || return 1

	for inface in $1 ;do
		backup_ifup $inface
	done
}

load_balance()
{
	/usr/sbin/load_balance &
}

get_master_infaces()
{
	config_get slave_iface $1 slave_iface
	if [ "$g_slave_iface" == "$slave_iface" ];then
		backup_master_ifaces=`uci get line_backup.$1.master_iface 2>/dev/null`
	fi
}

# start the online checking for infaces
#$1: slave_interface
#$2: master_interface
line_backup_track_start()
{
	#ifdown slave_inface
	[ -n "$1" ] && backup_ifdown_infaces "$1"
	[ -n "$2" ] && {
		. /lib/balance/api.sh
		. /lib/zone/zone_api.sh

		for zone in $2
		do
			dev=`zone_get_effect_devices $zone`
			balance_iface_set_event "$dev" up
		done
	}
}

set_interface_managed()
{
	[ -n "$ROUTING_MODE" ] && return

	. /lib/netifd/netifd-proto.sh
	for mzone in $1
	do
		[ "$mzone" == "WAN1" ] && mifaces="wan1_eth wan1_poe"
		[ "$mzone" == "WAN2" ] && mifaces="wan2_eth wan2_poe"
		[ "$mzone" == "WAN3" ] && mifaces="wan3_eth wan3_poe"
		[ "$mzone" == "WAN4" ] && mifaces="wan4_eth wan4_poe"
		for miface in $mifaces
		do
			proto_set_managed "$miface" "$2"
			if [ "$2" == "1" ] ; then
				touch "/tmp/.interface_managed_$miface"
			else
				rm -rf "/tmp/.interface_managed_$miface"
			fi
		done
	done
}

# $1:mode
# $2:timeobj
# $3:slave_iface
# $4:master_iface
# $5:state
line_backup_add()
{
	. /lib/balance/api.sh

	set_interface_managed "$3" "0"
	set_interface_managed "$4" "0"

	state=`get_balance_global_state`
	[ "$state" == "off" ] && return 

	[ "$5" == "on" ] && {
		set_interface_managed "$3" "1"
		set_interface_managed "$4" "1"
	}
	if [ "$1" == "fault" ];then
		line_backup_track_start $3 "$4"
	else
		if [ "$2" == "Any" ] ;then
			/usr/sbin/line_backup -t timer -s $3 -o "on"
		else
			. /lib/time_mngt/timeobj_api.sh

			timeobj_api_add $2 "line_backup" $3
			timeobj_api_commit "line_backup"
		fi
	fi
}

# $1: timer_infaces
# $2: fault_slave_infaces
# $3: fault_master_infaces
# $4: timeobjs
# $5: del_slave_ifaces
line_backup_del()
{ 

	. /lib/balance/api.sh

	set_interface_managed "$2" "0"
	set_interface_managed "$3" "0"

	state=`get_balance_global_state`
	[ "$state" == "off" ] && return 

	if [ -n "$3" ] ;then
		. /lib/balance/api.sh		

		#delete the master's online_check
		#del_online_check "$3"

		#ifup fault_slave_infaces
		backup_ifup_infaces "$3"
	fi

	#ifup timer_infaces
	[ -n "$1" ] && backup_ifup_infaces "$1"

	#ifup fault_slave_infaces
	[ -n "$2" ] && backup_ifup_infaces "$2"

	if [ -n "$4" -a -n "$5" ];then
		. /lib/backup/time.sh

		num=`echo "$4" |awk -F " " '{print NF-1}'`

		if [ $num -eq 0 ] ;then
			del_timeobj $4 $5		
		elif [ $num -ge 1 ];then		
			for i in `seq $(($num+1))`; do
				timeobj=`echo "$4" |cut -d " " -f $i`
				slave_iface=`echo "$5" |cut -d " " -f $i`
				
				del_timeobj $timeobj $slave_iface
			done
		fi
	fi

}


# $1:old_mode
# $2:old_timeobj
# $3:old_slave_iface
# $4:old_master_iface
# $5:new_mode
# $6:new_timeobj
# $7:new_slave_iface
# $8:new_master_iface
# $9:new_state
# $10:old_state
line_backup_update()
{
	. /lib/balance/api.sh

	set_interface_managed "$3" "0"
	set_interface_managed "$4" "0"
	set_interface_managed "$7" "0"
	set_interface_managed "$8" "0"

	state=`get_balance_global_state`
	[ "$state" == "off" ] && return 

	if [ "$10" == "on" ];then
		#old mode is fault 
		if [ "$1" == "fault" ];then
			. /lib/balance/api.sh
			#del_online_check "$4"
		else
		#old mode is timer
			if [ "$2" != "Any" ]; then
				#delete the old timeobj	
				. /lib/time_mngt/timeobj_api.sh
				timeobj_api_delete $2 "line_backup" $3
				timeobj_api_commit "line_backup"
			fi
		fi

		#ifup old slave and master iface
		[ -n "$3" ] && backup_ifup_infaces "$3"
		[ -n "$4" ] && backup_ifup_infaces "$4"
	fi

	if [ "$9" == "on" ];then
		set_interface_managed "$7" "1"
		set_interface_managed "$8" "1"

		if [ "$5" == "fault" ];then
			line_backup_track_start $7 "$8"
		else
			# if the [mode == timer and [timeobj == Any]
			if [ "$6" == "Any" ]; then
				/usr/sbin/line_backup -t timer -s $7 -o "on"
			else
				#add the new timeobj	
				. /lib/time_mngt/timeobj_api.sh
				timeobj_api_add $6 "line_backup" $7
				timeobj_api_commit "line_backup"
			fi
		fi	
	fi
}

handle_backup_enable()
{
	config_get mode $1 mode
	config_get state $1 state
	config_get timeobj $1 timeobj	
	config_get slave_iface $1 slave_iface
	config_get master_iface $1 master_iface

	set_interface_managed "$slave_iface" "0"
	set_interface_managed "$master_iface" "0"

	if [ "$state" == "on" ];then
		set_interface_managed "$slave_iface" "1"
		set_interface_managed "$master_iface" "1"

		if [ "$mode" == "fault" ];then
			[ -n "$slave_iface" ] && backup_ifdown_infaces "$slave_iface"
		else
			if [ "$timeobj" == "Any" ] ;then
				/usr/sbin/line_backup -t timer -s $slave_iface -o "on"
			else
				. /lib/time_mngt/timeobj_api.sh

				timeobj_api_add $timeobj "line_backup" $slave_iface
				timeobj_api_commit "line_backup"
			fi
		fi
		
	fi
}

global_enable_backup()
{
	. /lib/functions.sh

	config_load line_backup
	config_foreach handle_backup_enable rule
}

handle_backup_disable()
{
	config_get mode $1 mode
	config_get state $1 state
	config_get timeobj $1 timeobj	
	config_get slave_iface $1 slave_iface
	config_get master_iface $1 master_iface

	set_interface_managed "$slave_iface" "0"
	set_interface_managed "$master_iface" "0"

	if [ "$state" == "on" ];then
		backup_ifup_infaces "$slave_iface"
		backup_ifup_infaces "$master_iface"	

		if [ "$mode" == "timer" -a "$timeobj" != "Any" ] ;then
			. /lib/time_mngt/timeobj_api.sh

			timeobj_api_delete $timeobj "line_backup" $slave_iface
			timeobj_api_commit "line_backup"
		fi		
	fi
}

global_disable_backup()
{
	. /lib/functions.sh

	config_load line_backup
	config_foreach handle_backup_disable rule
}
