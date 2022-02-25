#!/bin/sh
#author wangdechu
. /lib/functions.sh
. /lib/pppox/pppox-default-variables.sh
. /lib/l2tp/l2tp-functions.sh

serveripsecinfo=${pppox_l2tp_main_path}/l2tpserver-ipsec-info #do not change the line
clientipsecinfo=${pppox_l2tp_main_path}/l2tpclient-ipsec-info #do not change the line

[ ! -f ${serveripsecinfo} ] && touch ${serveripsecinfo}
[ ! -f ${clientipsecinfo} ] && touch ${clientipsecinfo}

case $PLUTO_VERB in
	up-*)
		action="up";;
	down-*)
		action="down";;
	*)
		exit 1;;
esac

#id is like server1, client1 ......
id=${PLUTO_CONNECTION##${l2tp_ipsec_prefix}}

if echo ${id}|grep -q "^client"; then
	isserver=0
	path=${pppox_l2tp_client_path}/${id}/config
else
	isserver=1
	path=${pppox_l2tp_server_path}/${id}/config
fi

ipsecenc=`uci -c ${path} get ${pppox_configname}.${id}.ipsecenc 2>/dev/null`


if [ "${action}" = "up" ]; then
	{
		flock -x 195
		if [ ${isserver} -eq 0 ]; then
			#xl2tpd-control connect $id
			uci -c ${pppox_l2tp_main_path} set l2tpclient-ipsec-info.${id}=info
			uci -c ${pppox_l2tp_main_path} commit l2tpclient-ipsec-info
			l2tp_distribute lac $id
		else
			uci -c ${pppox_l2tp_main_path} set l2tpserver-ipsec-info.${id}=info
			#uci -c ${pppox_l2tp_main_path} add_list l2tpserver-ipsec-info.${id}.remoteip=${PLUTO_PEER}
			#uci -c ${pppox_l2tp_main_path} add_list l2tpserver-ipsec-info.${id}.${PLUTO_PEER//./_}=${PLUTO_UNIQUEID}
			uci -c ${pppox_l2tp_main_path} add_list l2tpserver-ipsec-info.${id}.${PLUTO_PEER//./_}=${PLUTO_MARK_OUT}
			uci -c ${pppox_l2tp_main_path} commit l2tpserver-ipsec-info
		fi
	} 195> /tmp/l2tp_ipsec_up_down.lock
	/usr/lib/ipsec/_updown		
	exit 0
fi

if [ "${action}" = "down" ]; then
	{
		flock -x 195
		if [ ${isserver} -eq 0 ]; then
			[ "${ipsecenc}" = "yes" ] && xl2tpd-control disconnect $id
			uci -c ${pppox_l2tp_main_path} delete l2tpclient-ipsec-info.${id}
			uci -c ${pppox_l2tp_main_path} commit l2tpclient-ipsec-info
		else
			uci -c ${pppox_l2tp_main_path} set l2tpserver-ipsec-info.${id}=info
			#uci -c ${pppox_l2tp_main_path} del_list l2tpserver-ipsec-info.${id}.remoteip=${PLUTO_PEER}
			#uci -c ${pppox_l2tp_main_path} del_list l2tpserver-ipsec-info.${id}.${PLUTO_PEER//./_}=${PLUTO_UNIQUEID}
			uci -c ${pppox_l2tp_main_path} del_list l2tpserver-ipsec-info.${id}.${PLUTO_PEER//./_}=${PLUTO_MARK_OUT}
			uci -c ${pppox_l2tp_main_path} commit l2tpserver-ipsec-info
		
			if [ "${ipsecenc}" = "yes" ]; then
				for dir in `ls ${pppox_l2tp_server_path}/${id}/pid 2>/dev/null`; do
					remoteip=`uci -c ${pppox_l2tp_server_path}/${id}/pid get ${dir}.@info[0].remoteip 2>/dev/null`
					info_mark=`uci -c ${pppox_l2tp_server_path}/${id}/pid get ${dir}.@info[0].mark 2>/dev/null`

					if [ ${remoteip} = ${PLUTO_PEER} -a ${PLUTO_MARK_OUT} = ${info_mark} ]; then
						echo "now the ipsec peer ${PLUTO_PEER} with ${PLUTO_MARK_OUT} is down, need to kill ${dir}" > /dev/console
						kill -TERM ${dir}
					fi
				done
			fi
		fi
	} 195> /tmp/l2tp_ipsec_up_down.lock
	/usr/lib/ipsec/_updown		
	exit 0
fi






