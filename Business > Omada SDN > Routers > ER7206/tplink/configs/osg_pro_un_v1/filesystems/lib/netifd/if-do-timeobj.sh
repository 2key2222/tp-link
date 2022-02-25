#!/bin/sh
#author: wangdechu

. /lib/time_mngt/timeobj_api.sh

[ "$#" -lt 4 ] && exit 1

action=$1
timeobj=$2
module=$3
iface=$4

case "${action}" in
    "ADD")
		timeobj_api_add "${timeobj}" "${module}" "${iface}";
		timeobj_api_commit "${module}";;
    "DEL")
        timeobj_api_delete "${timeobj}" "${module}" "${iface}";
		timeobj_api_commit "${module}";;
    *)
        exit 1
esac
