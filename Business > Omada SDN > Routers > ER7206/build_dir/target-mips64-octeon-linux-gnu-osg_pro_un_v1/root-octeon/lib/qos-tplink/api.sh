#!/bin/sh
#Copyright (C) 2015 tplink.com

# API of qos-tplink
local n=$#
[ "$n" -eq 0 ] && return

. /lib/qos-tplink/qos_public.sh

QOS_LOG_PRINT " $0 $@ begin @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ! "

# Deal with qos polling daemon process
[ $QOS_THRESHOLD -gt 0 ] && {
    [ $1 = "stop" ] && {
        [ -f $QOS_POLLING_FILE ] && {
            kill -9 `cat $QOS_POLLING_FILE`
            rm -f $QOS_POLLING_FILE 2>/dev/null
            QOS_LOG_PRINT " stop qos polling "
        }
    }

    [ $1 = "start" ] && {
        # if polling exist, kill the old polling process and create new
        [ -f $QOS_POLLING_FILE ] && {
            kill -9 `cat $QOS_POLLING_FILE`
            rm -f $QOS_POLLING_FILE 2>/dev/null
            QOS_LOG_PRINT " stop qos polling "
        }
        /lib/qos-tplink/qos_polling.sh &
        touch $QOS_POLLING_FILE
        echo `ps -w | grep -w qos_polling.sh | awk '/\{qos_polling.sh\}/ {print $1}'` > $QOS_POLLING_FILE
        QOS_LOG_PRINT " start qos polling "
    }

    [ ! -f $QOS_READY ] && {
        [ $1 != "stop" ] && {
            # throughout not enough, keep polling and do nothing
            QOS_LOG_PRINT " info, polling daemon show that throughout lower than $QOS_THRESHOLD% now, just return the $1 action "
            return
        }
    }
}

[ $QOS_THRESHOLD -eq 0 ] && {
    [ -f $QOS_POLLING_FILE ] && {
        kill -9 `cat $QOS_POLLING_FILE`
        rm -f $QOS_POLLING_FILE 2>/dev/null
        QOS_LOG_PRINT " stop qos polling "
    }
}

# compose the usr_cmd
usr_cmd=". /lib/qos-tplink/main.sh"

for i in $(seq 1 1 $n); do
	usr_cmd="$usr_cmd $1"
	shift
done

$usr_cmd

return
