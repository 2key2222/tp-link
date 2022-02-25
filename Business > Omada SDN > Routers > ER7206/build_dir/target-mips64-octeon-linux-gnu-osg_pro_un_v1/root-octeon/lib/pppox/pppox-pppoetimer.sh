#!/bin/sh
#author: wangdechu
#pppoe timer

. /lib/functions.sh

_load_one_pppoe()
{
	local section=$1
	
	config_get myproto ${section} "proto"
	[ "${myproto}" != "pppoe" -a "${myproto}" != "l2tp" -a "${myproto}" != "pptp" ] && return 0
	
	config_get mylinktype ${section} "t_linktype"
	[ "${mylinktype}" != "time" ] && return 0
	
	config_get mytimeobj ${section} "t_timeobj"
	[ "${mytimeobj}" == "Any" ] && return 0
	
	if [ "${whatoperate}" == "DELADD" ]; then
		/lib/netifd/if-do-timeobj.sh DEL "${mytimeobj}" pppoe "${section}"
	fi
	
	/lib/netifd/if-do-timeobj.sh ADD "${mytimeobj}" pppoe "${section}"
}

load_pppoe()
{
	whatoperate=$1
	config_load network
	config_foreach _load_one_pppoe "interface"
	config_foreach config_clear
}

