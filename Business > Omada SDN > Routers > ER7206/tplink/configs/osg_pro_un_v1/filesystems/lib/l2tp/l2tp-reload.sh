#!/bin/sh
#author: wangdechu
#
#note: the global config for server and client can only be modified, delete or other operations are illegal

. /lib/l2tp/l2tp-functions.sh
. /lib/pppox/pppox-functions.sh

[ $# -ne 3 ] && exit 1
operate=$1
l2tptype=$2
l2tpname=$3

[ "${l2tpname}" = "global" -a "${operate}" != "modify" ] && exit 1
#echo "pppox_reset_loadflag" > /dev/console
l2tp_begin_reload()
{
	local path
	if [ "${l2tptype}" = "lns" ]; then
		if [ "${l2tpname}" != "global" ]; then
			path=${pppox_l2tp_server_path}
			l2tp_cdistribute lns ${l2tpname}
		else
			for dir in `ls ${pppox_l2tp_server_path} 2>/dev/null`; do
				l2tp_cdistribute lns ${dir}
			done
			return 0
		fi
	elif [ "${l2tptype}" = "lac" ]; then
		if [ "${l2tpname}" != "global" ]; then
			path=${pppox_l2tp_client_path}
			l2tp_cdistribute lac ${l2tpname}
		else
			for dir in `ls ${pppox_l2tp_client_path} 2>/dev/null`; do
				l2tp_cdistribute lac ${dir}
			done
			return 0
		fi
	fi
	
	case "${operate}" in
		"delete")
		rm -rf ${path}/${l2tpname};;
		"modify")
		rm -f ${path}/${l2tpname}/config/${pppox_configname};;
	esac
}

[ "${operate}" = "delete" -o "${operate}" = "modify" ] && l2tp_begin_reload 
[ "${operate}" = "delete" ] && exit 0

if [ "${l2tptype}" = "lns" ]; then
	if [ "${l2tpname}" != "global" ]; then
		l2tp_load_client_or_server lns ${l2tpname};
		if [ "${operate}" = "add" ]; then
		#Bug 463892 	standalone mode: need load vpn users
			if [ ! -f /tmp/pppox.controller.mode ]; then
				pppox_reset_loadflag l2tp
				#echo "pppox_load_user l2tp ${l2tpname}" > /dev/console
				pppox_load_user l2tp ${l2tpname}
			fi
		fi
		l2tp_distribute lns ${l2tpname}
	else
		l2tp_load_client_or_server lns global
		l2tp_distribute lns global
		for dir in `ls ${pppox_l2tp_server_path} 2>/dev/null`; do
			l2tp_distribute lns ${dir}
		done
	fi
	
elif [ "${l2tptype}" = "lac" ]; then
	if [ "${l2tpname}" != "global" ]; then
		l2tp_load_client_or_server lac ${l2tpname};
		l2tp_distribute lac ${l2tpname}
	else
		l2tp_load_client_or_server lac global
		l2tp_distribute lac global
		for dir in `ls ${pppox_l2tp_client_path} 2>/dev/null`; do
			l2tp_distribute lac ${dir}
		done
	fi
fi
