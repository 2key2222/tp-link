#!/bin/sh
#author: wangdechu
#brief: get all l2tp tunnel info
#Usage: get-tunnel-info.sh [-p|-t]
#	-p: print to monitor
#
. /lib/l2tp/l2tp-functions.sh

#the file that tunnel info stored
tunnelinfofile=${pppox_l2tp_main_path}/l2tp-tunnel-info #do not change this line
id=1

get_l2tp_info()
{
	local path=$1/$2/pid
	local path1=${pppox_ppppath}/pid
	for fil in `[ -d ${path} ] && ls ${path}`; do
		[ ! -f ${path1}/${fil} ] && continue
		echo "config ${3}info ${id}">>${tunnelinfofile}
		let id=id+1
		awk '{if ($0 !~ /^config/) {print $0}}' ${path}/${fil} >> ${tunnelinfofile}
		awk '{if ($0 !~ /^config/) {print $0}}' ${path1}/${fil} >> ${tunnelinfofile}
		echo "        option pppdid ${fil}" >> ${tunnelinfofile}
	done
}

rm -f ${tunnelinfofile}
touch ${tunnelinfofile}

#l2tp server
for dir in `ls ${pppox_l2tp_server_path}`; do
	get_l2tp_info ${pppox_l2tp_server_path} ${dir} "lns"
done

#l2tp client
for dir in `ls ${pppox_l2tp_client_path}`; do
	get_l2tp_info ${pppox_l2tp_client_path} ${dir} "lac"
done

[ "$1" = "-p" ] && cat ${tunnelinfofile}
[ "$1" = "-t" ] && echo "finished" #do not changed this line
