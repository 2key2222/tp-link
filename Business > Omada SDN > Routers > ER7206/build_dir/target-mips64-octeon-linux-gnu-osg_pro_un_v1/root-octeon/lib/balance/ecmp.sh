#!/bin/sh

RT_FILE="/tmp/.route_table"
RT_FLAG="/tmp/.route_flag"
RT_RET="/tmp/.route_ret"

rm $RT_FILE -f

route -n >> $RT_FILE

flags=$(route -n |awk '{print $1","$4}')

i=1
for flag in $flags; do
	ret=`echo $flag |grep G |grep -v H |grep "0.0.0.0"`
	if [ -n "$ret" ]; then
		sed -n "${i}p" $RT_FILE >> $RT_FLAG
	fi
	let i++
done

lua /lib/balance/ecmp.lua

cat $RT_RET | while read line
do
	route=""
	gw=`echo $line |cut -d "," -f 1`
	devs=`echo $line |cut -d "," -f 2`

	for dev in $devs; do
		route=${route}" nexthop via $gw dev $dev weight 1"
	done
	ip route replace default scope global $route  
done

rm $RT_FILE -f
rm $RT_FLAG -f
rm $RT_RET -f