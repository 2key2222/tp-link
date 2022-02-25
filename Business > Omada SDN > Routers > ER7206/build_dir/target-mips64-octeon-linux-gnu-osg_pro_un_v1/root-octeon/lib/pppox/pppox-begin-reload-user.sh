#!/bin/sh
#author: wangdechu

. /lib/pppox/pppox-functions.sh

[ $# -ne 3 ] && return 1
operate=$1
usertype=$2
username=$3

[ "${operate}" != "delete" -a "${operate}" != "modify" ] && return 1

for file in `ls ${pppox_ppppath}/pid 2>/dev/null`; do
	getusername=`uci -c ${pppox_ppppath}/pid get ${file}.@info[0].username 2>/dev/null`
	getisserver=`uci -c ${pppox_ppppath}/pid get ${file}.@info[0].isserver 2>/dev/null`
	getconfigpath=`uci -c ${pppox_ppppath}/pid get ${file}.@info[0].configpath 2>/dev/null`
	
	[ "${getisserver}" != "1" ] && continue	
	[ "${username}" != "${getusername}" ] && continue	
	
	usertypematch=0
	getusertype=`echo ${usertype} | sed 's/,/ /g'`
	for tttt in ${getusertype}; do
		[ "${tttt}" = "${pppox_autotype}" ] && usertypematch=1 && break
		[ -f "${getconfigpath}/config/${tttt}.type" ] && usertypematch=1 && break #all pppox modules should create the type file
	done
	[ ${usertypematch} -ne 1 ] && continue
	une1=`asciimaker -a "${getusername}"`

	[ ! -f ${getconfigpath}/config/${une1}-profile ] && continue 
#! grep -qE "^('|\")?${une1}" ${getconfigpath}/config/${pppox_user_configname} && continue
	
	#[ -f ${getconfigpath}/pid/${file} ] && 
	ps | grep -iq "pppd" && kill -TERM ${file}
done
	
[ ${operate} != "delete" ] && return 0

delete_user_info()
{
	local une=`asciimaker -a "${username}"`
	for dir in `ls ${1} 2>/dev/null`; do
		rm -f ${1}/${dir}/config/${une}${pppox_profile}
		rm -f ${1}/${dir}/config/${une}${pppox_profilex}
	done
}

echo "${usertype}" | grep -iqE "(${pppox_l2tptype}|auto)" && delete_user_info ${pppox_l2tp_server_path}
echo "${usertype}" | grep -iqE "(${pppox_pptptype}|auto)" && delete_user_info ${pppox_pptp_server_path}
echo "${usertype}" | grep -iqE "(${pppox_pppoetype}|auto)" && delete_user_info ${pppox_pppoe_server_path}
