#!/bin/sh
#author: wangdechu
#$1: <operate>, may be "add" "modify" "delete",   
#$2: <old usertype>, may be ${pppox_l2tptype} ${pppox_pptptype} ${pppox_pppoetype} "auto",  more to read pppox-default-variables.sh
#$3: <new usertype>
#$4: <username>

. /lib/pppox/pppox-functions.sh

username=$4
/lib/pppox/pppox-begin-reload-user.sh $1 $2 "${username}"

if [ "$2" = "$pppox_autotype" -o "$3" = "$pppox_autotype" ]; then
	pppox_reset_loadflag all
	pppox_load_user l2tp
	pppox_load_user pptp
	return 0
fi

#old type should be load
pppox_reset_loadflag $2
pppox_load_user $2

#new type should be load	
[ "$2" != "$3" ] && { pppox_reset_loadflag $3; pppox_load_user $3; }

