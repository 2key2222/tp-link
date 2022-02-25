#!/bin/bash

PTN_NAME=partition-table
OPTION=$1
export OPTION
ret=""

while read line
do
	if echo "$line" | grep -n '{' >/dev/null; then
		block_start="1"
		base=""
		flash=""
		part_start=""
		continue
	elif echo "$line" | grep -n '}' >/dev/null; then
		block_start=""
		continue
	fi
	[ -z "$block_start" ] && continue
	if echo "$line" | grep -n 'name' | grep -n ${PTN_NAME} >/dev/null; then
		part_start="1"
		continue
	fi
	[ -z "$part_start" ] && continue
	if echo "$line" | grep -n 'base' >/dev/null; then
		base=`echo "$line" | cut -d ':' -f 2 | cut -d ',' -f 1 | sed "s/\"//g"`
	fi
	if echo "$line" | grep -n 'write_to_flash' | grep -n 'true' >/dev/null; then
		flash="1"
	fi
	if [ -n "$base" -a -n "$flash" ] ; then
		ret=$base
		break
	fi
done < $1

if [ "$ret" != "" ];then
	echo $ret
else
	echo "0x00000000"
fi