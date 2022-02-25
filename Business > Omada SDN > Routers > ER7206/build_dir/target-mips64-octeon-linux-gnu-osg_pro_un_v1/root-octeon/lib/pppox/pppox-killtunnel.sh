#!/bin/sh
#author: wangdechu

stop()
{
	local ifnamex=$1
	
	echo "kill all l2tp/pptp process with ${ifnamex}" >/dev/console
	local pppox_ppppath=/tmp/ppp
	for file in `ls ${pppox_ppppath}/pid 2>/dev/null`; do
		local getconfigpath=`uci -c ${pppox_ppppath}/pid get ${file}.@info[0].configpath 2>/dev/null`
		local getisserver=`uci -c ${pppox_ppppath}/pid get ${file}.@info[0].isserver 2>/dev/null`
		
		local optionx=outif
		if [ "${getisserver}" = "1" ]; then
			optionx=bindif
		fi
		
		if cat ${getconfigpath}/config/myconfig | grep -q "${optionx} *'${ifnamex}'"; then
			if [ -f "${getconfigpath}/config/l2tp.type" ]; then
				kill -TERM ${file}
			elif [ -f "${getconfigpath}/config/pptp.type" ]; then
			
				if [ "${getisserver}" = "1" ]; then
					kill -TERM ${file}
				else
					local path=${getconfigpath}/config
					local ppp_pid=${path}/ppp
					local mgr_pid=${path}/mgr
					local mgrfather_pid=${path}/mgrfather
		
					ppp_pid=$(cat $ppp_pid 2>/dev/null)
					mgr_pid=$(cat $mgr_pid 2>/dev/null)
					mgrfather_pid=$(cat $mgrfather_pid 2>/dev/null)
					[ ${ppp_pid}x != ''x ] && kill -TERM $ppp_pid
					[ ${mgrfather_pid}x != ''x ] && kill -TERM $mgrfather_pid
					[ ${mgr_pid}x != ''x ] && kill -TERM $mgr_pid
					
					rm -f ${path}/ppp ${path}/mgr ${path}/mgrfather
				fi
			fi
		fi
	done
}

stop $1
