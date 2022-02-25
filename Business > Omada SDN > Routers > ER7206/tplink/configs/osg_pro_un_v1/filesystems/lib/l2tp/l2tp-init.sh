#!/bin/sh
#author: wangdechu

. /lib/l2tp/l2tp-functions.sh
. /lib/pppox/pppox-functions.sh

l2tp_load_client_or_server lns all
l2tp_load_client_or_server lac all

pppox_load_user ${pppox_l2tptype}

l2tp_distribute lns global
l2tp_distribute lac global

for dir in `ls ${pppox_l2tp_server_path}`; do
	l2tp_distribute lns ${dir}
done

for dir in `ls ${pppox_l2tp_client_path}`; do
	l2tp_distribute lac ${dir}
done