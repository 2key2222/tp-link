#!/bin/sh 
# Copyright(c) 2011-2016 Shenzhen TP-LINK Technologies Co.Ltd.
# file    ipsec_execute_stroke.sh 
# brief   used to execute the ipsec stroke commands 
# author   Chen Xing
# version  1.0.0
# date     16Apr16
# histry   arg 1.0.0, 16Apr16, Chen Xing, Create the file. 

ipsec_stroke_for_modify()
{
	local tunnel_name=$1
	{
		ipsec stroke down-nb ${tunnel_name}{*}
		echo "ipsec stroke down-nb ${tunnel_name}{*}" > /dev/console
		ipsec stroke purgeike
		echo "ipsec stroke purgeike" > /dev/console
		ipsec rereadsecrets
		echo "ipsec rereadsecrets" > /dev/console
		echo "sleep 1" > /dev/console
		sleep 1
		ipsec update
		echo "ipsec update" > /dev/console
		echo "ipsec stroke for modify done" > /dev/console
		exit 0
	}&
	return 0
}


ipsec_stroke_for_delete_all()
{
	{
		ipsec stroke purgeike
		echo "ipsec stroke purgeike" > /dev/console
		ipsec rereadsecrets
		echo "ipsec rereadsecrets" > /dev/console
		echo "sleep 1" > /dev/console
		sleep 1
		ipsec update
		echo "ipsec update" > /dev/console
		echo "ipsec stroke for delete done" > /dev/console
		exit 0
	}&
	return 0
}

ipsec_stroke_for_add()
{
	ipsec rereadsecrets
	echo "ipsec rereadsecrets" > /dev/console
	{
		echo "sleep 1" > /dev/console
		sleep 1
		ipsec update
		echo "ipsec update" > /dev/console
		echo "ipsec stroke for add done" > /dev/console
		exit 0
	}&
	return 0
}

operation=$1

echo "ipsec execute stroke begin" > /dev/console

if [ "${operation}" = "modify" ]; then
	tunnel_name=$2
	if [ ! -n "$tunnel_name" ]; then  
  		echo "tunnel name is null" > /dev/console
  		exit 1
  	fi
  	ipsec_stroke_for_modify ${tunnel_name}

elif [ "${operation}" = "delete" ]; then
	ipsec_stroke_for_delete_all

elif [ "${operation}" = "add" ]; then
	ipsec_stroke_for_add
fi

exit 0






