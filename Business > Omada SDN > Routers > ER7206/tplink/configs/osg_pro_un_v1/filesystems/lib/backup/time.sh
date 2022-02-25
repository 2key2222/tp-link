#!/bin/sh


#$1: rule
check_backup_mode()
{
	config_get slave_iface $1 slave_iface
	config_get mode $1 mode

	[ "$in_slave_iface" == "$slave_iface" -a "$mode" == "timer" ] && /usr/sbin/line_backup -t timer -s $slave_iface -o "on"

}

#$1: timeobj
#$2: slave_iface
add_timeobj()
{
	if [ -n "$1" ]; then
		. /lib/time_mngt/timeobj_api.sh

		timeobj_api_add $1 "line_backup" $2
		timeobj_api_commit "line_backup"
	fi

	if [ $1 == "Any" ];then
		in_slave_iface=$2

		. /lib/functions.sh

		config_load line_backup

		config_foreach check_backup_mode rule		 
	fi
}

#$1: timeobj
#$2: slave_iface
del_timeobj()
{
	if [ -n "$1" -a "$1" != "Any" ]; then
		. /lib/time_mngt/timeobj_api.sh

		timeobj_api_delete $1 "line_backup" $2
		timeobj_api_commit "line_backup"
	fi
}
