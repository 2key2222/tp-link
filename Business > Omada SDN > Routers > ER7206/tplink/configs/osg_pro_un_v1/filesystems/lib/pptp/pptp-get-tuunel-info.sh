#!/bin/sh
#did not get  callid info in ppp output
. /lib/pppox/pppox-default-variables.sh

tunnelinfofile=${pppox_pptp_path}/pptp-tunnel-info
 [ ! -e ${pppox_pptp_path} ] && mkdir -p ${pppox_pptp_path}
 [ -e $tunnelinfofile ] && rm -f $tunnelinfofile
 touch $tunnelinfofile >/dev/null 2>&1
 
 local path=${pppox_ppppath}/pid
 
 for file in `ls $path 2>/dev/null`;do
	tail -n 4 ${path}/${file} | grep -q '/tmp/pptp/' && {
		echo -e 'config info\n' >>${tunnelinfofile}
		echo -e "\toption pid $file\n" >>${tunnelinfofile}
		awk '{if ($0 !~ /^config/) {print $0}}' ${path}/${file} >> ${tunnelinfofile}
 }	
 done
 
[ "$1" = "-p" ] && cat ${tunnelinfofile}
[ "$1" = "-t" ] && echo "finished"