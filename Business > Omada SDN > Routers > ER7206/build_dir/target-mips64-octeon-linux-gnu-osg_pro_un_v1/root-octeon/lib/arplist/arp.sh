#!/bin/sh
. /lib/zone/zone_api.sh

anete arp -n | grep -v 'incomplete' | grep -v 'Address' | awk '{print $1,$3,$5,0}'>/tmp/arplist
while read LINE
do
	local loop=0
	local conflict=0
	local ip=$(echo $LINE | awk '{print $1}')
	local mac=$(echo $LINE | awk '{print $2}')
	local mac_conf=$(uci get imb.@imb_rule[$loop].mac 2>/dev/null)
	while [ x"$mac_conf" != 'x' ];do
		local ip_conf=$(uci get imb.@imb_rule[$loop].ipaddr 2>/dev/null)
		local new_mac=$(echo $mac | tr ':' '-' | tr '[a-z]' '[A-Z]')
		if [ x$ip == x$ip_conf ];then
			mac_conf=$(echo $mac_conf |tr ':' '-' | tr '[a-z]' '[A-Z]')
			if [ x$mac_conf != x$new_mac ];then
				conflict=1
			else
				conflict=2
			fi
			break
		fi
		loop=$(($loop+1))
		mac_conf=$(uci get imb.@imb_rule[$loop].mac 2>/dev/null)
	done
	local dev=$(echo $LINE | awk '{print $3}')
	local interface=$(zone_get_iface_bydev $dev)
	echo -e "$ip $mac $interface $conflict" >>/tmp/arplist1
done </tmp/arplist
rm -f /tmp/arplist
mv /tmp/arplist1 /tmp/arplist
echo "finished"
