#!/bin/sh

#$1 is state of global enable ,$2 is state of garp enable
local enable=$1
local garp=$2
local interval=$3

[ x$interval = 'x' ] && interval=100

/etc/init.d/imb reload

#enable garp
if [ $enable == "on" ];then
		cp /lib/modules/files/50-arp_garp /etc/modules.d/
		rmmod arp_garp
		if [ x$garp != "xon" ];then
			insmod /lib/modules/$(uname -r)/arp_garp.ko sendflag=0 interval_time=$interval
		else
			insmod /lib/modules/$(uname -r)/arp_garp.ko sendflag=1 interval_time=$interval
		fi
else
		rm -f /etc/modules.d/50-arp_garp
		rmmod arp_garp
fi

/etc/init.d/arp_defense reload