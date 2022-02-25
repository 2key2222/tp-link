#!/bin/sh

. /lib/pptp/pptp-startup.sh

[ $# -ne 3 ] && echo "parameter is not right" && return 0
update_global $1 $2 $3