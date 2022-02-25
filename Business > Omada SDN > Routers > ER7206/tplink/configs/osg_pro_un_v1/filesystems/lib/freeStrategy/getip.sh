#!/bin/sh

getip()
{
	for i in 1 2 3 4;do
		ip=$(dnsq "WAN${i}" $1 | grep -o '\([\.0-9]*\)')
		if [ "$ip" != "0.0.0.0" ];then
			echo "$ip"
		fi
	done
}