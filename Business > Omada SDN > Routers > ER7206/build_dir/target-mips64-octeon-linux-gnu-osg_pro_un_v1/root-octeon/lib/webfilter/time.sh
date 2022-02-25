#!/bin/sh
NAME="webfilter"
#$1: timeobj
add_timeobj()
{
	if [ -n "$1" ]; then
		. /lib/time_mngt/timeobj_api.sh

		timeobj_api_add $1 $NAME $2
		timeobj_api_commit $NAME
	fi
}

del_timeobj()
{
	if [ -n "$1" ]; then
		. /lib/time_mngt/timeobj_api.sh

		timeobj_api_delete $1 $NAME $2
		timeobj_api_commit $NAME
	fi
}


