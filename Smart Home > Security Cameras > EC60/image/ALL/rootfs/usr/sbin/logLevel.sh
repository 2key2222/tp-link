#!/bin/sh

mkdir -p /tmp/logLevel/
rm -f /tmp/logLevel/level_*
dir=/tmp/logLevel
level=$(uci get syslog.cfg.level)

i=$level
while [ $i -ge 0 ]
do
	touch $dir/level_$i
	i=$((i-1))
done



