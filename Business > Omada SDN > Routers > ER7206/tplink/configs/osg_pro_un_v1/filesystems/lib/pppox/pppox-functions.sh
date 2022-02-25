#!/bin/sh
#author: wangdechu

. /lib/functions.sh
. /lib/pppox/pppox-default-variables.sh

# $1 type target
# $2 type default
# $3 flag
# $4 main path: /tmp/pppox/l2tp /tmp/pppox/pptp
# $5 server path: /tmp/l2tp/server /tmp/pptp/server
# $6 server name can be empty: server1
_check_pppox_type()
{
	#echo "_check_pppox_type $1 $2 $3 $4 $5 $6" > /dev/console
	
	if [ "${1}" = "${2}" -o  "${1}" = "all" ]; then
		if [ ! -f /tmp/pppox.controller.mode ]; then
			#echo "pppox.controller.mode standalone" > /dev/console
			[ ! -f ${pppox_path}/${2}.hasinited ] && 
			{ rm -rf ${4}; mkdir -p ${4}; \
			touch ${4}/${pppox_if_config}; \
			touch ${4}/${pppox_user_secrets}; \
			eval "$3=1"; }
		else
			#echo "pppox.controller.mode controller" > /dev/console
			{ rm -rf ${4}; mkdir -p ${4}; \
			touch ${4}/${pppox_if_config}; \
			touch ${4}/${pppox_user_secrets}; \
			eval "$3=1"; }
		fi
	fi	
		
	if [ "${1}" = "${2}" -o  "${1}" = "all" ]; then

		if [ "$6" = "" ]; then
			for dir in `ls ${5} | grep -v server-global | grep -v wan 2>/dev/null`; do
				rm -rf ${5}/${dir}/config/${pppox_if_config}
				rm -rf ${5}/${dir}/config/${pppox_user_secrets}
				rm -rf ${5}/${dir}/config/*${pppox_profile}
				rm -rf ${5}/${dir}/config/*${pppox_profilex}
				touch ${5}/${dir}/config/${pppox_if_config}
				touch ${5}/${dir}/config/${pppox_user_secrets}
				#echo "a:rm -rf ${5}/${dir}/config/${pppox_if_config}" > /dev/console
			done
		else
			rm -rf ${5}/${6}/config/${pppox_if_config}
			rm -rf ${5}/${6}/config/${pppox_user_secrets}
			rm -rf ${5}/${6}/config/*${pppox_profile}
			rm -rf ${5}/${6}/config/*${pppox_profilex}
			touch ${5}/${6}/config/${pppox_if_config}
			touch ${5}/${6}/config/${pppox_user_secrets}
			#echo "b:rm -rf ${5}/${6}/config/${pppox_if_config}" > /dev/console
		fi
	fi
}
# $1 type
# $2 name can be empty

_begin_load_user()
{
	#echo "_begin_load_user $1 $2 $3 $4" > /dev/console
	_check_pppox_type $1 ${pppox_l2tptype} initl2tp ${pppox_l2tp_path} ${pppox_l2tp_server_path} "$2"
	_check_pppox_type $1 ${pppox_pptptype} initpptp ${pppox_pptp_path}  ${pppox_pptp_server_path} "$2"
	_check_pppox_type $1 ${pppox_pppoetype} initpppoe ${pppox_pppoe_path} ${pppox_pptp_pppoe_path} "$2"

}

_copy_to_pppox()
{
	if [ ${1} = "all" -o "$2" = "" ]; then
		for dir in `ls ${3}  | grep -v server-global | grep -v wan 2>/dev/null`; do
			cp -f ${4}/* ${3}/${dir}/config/
		done
	else
		cp -f ${4}/* ${3}/${2}/config/
	
	fi
}

# $1 type
# $2 name can be empty
_end_load_user()
{
	if [ $initl2tp -eq 1 ]; then
		touch ${pppox_path}/${pppox_l2tptype}.hasinited	
	fi

	if [ $initpptp -eq 1 ]; then
		touch ${pppox_path}/${pppox_pptptype}.hasinited
	fi

	if [ $initpppoe -eq 1 ]; then
		touch ${pppox_path}/${pppox_pppoetype}.hasinited
	fi
	
}

# $1 main path: /tmp/pppox/l2tp /tmp/pppox/pptp
# $2 server path: /tmp/l2tp/server /tmp/pptp/server
# $3 type: l2tp pptp pppoe
# $4 name of server, can be empty: server1

_echo_info()
{ 
	local serverlist_type
	local serverlist_id
	local serverlist_pool
	local serverlist_local

	#echo "_echo_info $1 $2 $3 $4" > /dev/console

	local password1=${password//\\/\\\\}
	password1=${password1//\'/\\\'}
	local username1=${username//\\/\\\\}
	username1=${username1//\'/\\\'}
	username2=`asciimaker -a "${username}"`

	echo "'${username1}' * '${password1}' *" >>${1}/${pppox_user_secrets}
	echo -e "${localip}:\nippool ${ippool}\nms-dns ${ms_dns}" >>${1}/${username2}${pppox_profile}
	echo -e "maxsessions ${maxsessions}" >>${1}/${username2}${pppox_profilex}
	
	uci -c ${1} set ${pppox_if_config}.${username2}=if
	uci -c ${1} set ${pppox_if_config}.${username2}.netmode=${netmode}
	uci -c ${1} set ${pppox_if_config}.${username2}.remotesubnet="${remotesubnet}"
	uci -c ${1} set ${pppox_if_config}.${username2}.local_network="${local_network}"
#	uci -c ${1} set ${pppox_if_config}.${username}.workmode=${workmode}

	uci -c ${1} commit ${pppox_if_config}


	if [ "$4" = "" ]; then
		if [ -z "$serverlist" ]; then
			for dir in `ls ${2}  | grep -v server-global | grep -v wan 2>/dev/null`; do

				echo "'${username1}' * '${password1}' *" >>${2}/${dir}/config/${pppox_user_secrets}
				echo -e "${localip}:\nippool ${ippool}\nms-dns ${ms_dns}" >>${2}/${dir}/config/${username2}${pppox_profile}
				echo -e "maxsessions ${maxsessions}" >>${2}/${dir}/config/${username2}${pppox_profilex}
				
				uci -c ${2}/${dir}/config set ${pppox_if_config}.${username2}=if
				uci -c ${2}/${dir}/config set ${pppox_if_config}.${username2}.netmode=${netmode}
				uci -c ${2}/${dir}/config set ${pppox_if_config}.${username2}.remotesubnet="${remotesubnet}"
				uci -c ${2}/${dir}/config set ${pppox_if_config}.${username2}.local_network="${local_network}"
				#uci -c ${2}/${dir}/config set ${pppox_if_config}.${username}.workmode=${workmode}
				uci -c ${2}/${dir}/config commit ${pppox_if_config}
				#echo " a uci -c ${2}/${dir}/config set ${pppox_if_config}.${username2}.local_network=${local_network}" > /dev/console
			done
		else
			for server in ${serverlist}; do
				serverlist_type=$(echo "$server" | cut -d '/' -f 1)
				serverlist_id=$(echo "$server" | cut -d '/' -f 2)
				serverlist_pool=$(echo "$server" | cut -d '/' -f 3)
				serverlist_local=$(echo "$server" | cut -d '/' -f 4)
				serverlist_local=${serverlist_local//-/ }
				
				if [ "$serverlist_type" = "$3" ]; then

					echo "'${username1}' * '${password1}' *" >>${2}/${serverlist_id}/config/${pppox_user_secrets}
					echo -e "${localip}:\nippool ${serverlist_pool}\nms-dns ${ms_dns}" >>${2}/${serverlist_id}/config/${username2}${pppox_profile}
					echo -e "maxsessions ${maxsessions}" >>${2}/${serverlist_id}/config/${username2}${pppox_profilex}
					
					uci -c ${2}/${serverlist_id}/config set ${pppox_if_config}.${username2}=if
					uci -c ${2}/${serverlist_id}/config set ${pppox_if_config}.${username2}.netmode=${netmode}
					uci -c ${2}/${serverlist_id}/config set ${pppox_if_config}.${username2}.remotesubnet="${remotesubnet}"
					uci -c ${2}/${serverlist_id}/config set ${pppox_if_config}.${username2}.local_network="${serverlist_local}"
					#uci -c ${2}/${serverlist_id}/config set ${pppox_if_config}.${username}.workmode=${workmode}
					uci -c ${2}/${serverlist_id}/config commit ${pppox_if_config}

					#echo "uci -c ${2}/${serverlist_id}/config set ${pppox_if_config}.${username2}=if" > /dev/console
					#echo "uci -c ${2}/${serverlist_id}/config set ${pppox_if_config}.${username2}.netmode=${netmode}" > /dev/console
					#echo "uci -c ${2}/${serverlist_id}/config set ${pppox_if_config}.${username2}.remotesubnet=${remotesubnet}" > /dev/console
					#echo "uci -c ${2}/${serverlist_id}/config set ${pppox_if_config}.${username2}.local_network=${serverlist_local}" > /dev/console
					
				fi
			done
				
		fi
	else
		if [ -z "$serverlist" ]; then
			echo "'${username1}' * '${password1}' *" >>${2}/${4}/config/${pppox_user_secrets}
			echo -e "${localip}:\nippool ${ippool}\nms-dns ${ms_dns}" >>${2}/${4}/config/${username2}${pppox_profile}
			echo -e "maxsessions ${maxsessions}" >>${2}/${4}/config/${username2}${pppox_profilex}
			
			uci -c ${2}/${4}/config set ${pppox_if_config}.${username2}=if
			uci -c ${2}/${4}/config set ${pppox_if_config}.${username2}.netmode=${netmode}
			uci -c ${2}/${4}/config set ${pppox_if_config}.${username2}.remotesubnet="${remotesubnet}"
			uci -c ${2}/${4}/config set ${pppox_if_config}.${username2}.local_network="${local_network}"
			#uci -c ${2}/${4}/config set ${pppox_if_config}.${username}.workmode=${workmode}
			uci -c ${2}/${4}/config commit ${pppox_if_config}

			#echo " c uci -c ${2}/${dir}/config set ${pppox_if_config}.${username2}.local_network=${local_network}" > /dev/console
		else
			for server in ${serverlist}; do
				serverlist_type=$(echo "$server" | cut -d '/' -f 1)
				serverlist_id=$(echo "$server" | cut -d '/' -f 2)
				serverlist_pool=$(echo "$server" | cut -d '/' -f 3)
				serverlist_local=$(echo "$server" | cut -d '/' -f 4)
				serverlist_local=${serverlist_local//-/ }

				if [ "$serverlist_type" = "$3" -a "$serverlist_id" = "$4" ]; then

					echo "'${username1}' * '${password1}' *" >>${2}/${4}/config/${pppox_user_secrets}
					echo -e "${localip}:\nippool ${serverlist_pool}\nms-dns ${ms_dns}" >>${2}/${4}/config/${username2}${pppox_profile}
					echo -e "maxsessions ${maxsessions}" >>${2}/${4}/config/${username2}${pppox_profilex}
					
					uci -c ${2}/${4}/config set ${pppox_if_config}.${username2}=if
					uci -c ${2}/${4}/config set ${pppox_if_config}.${username2}.netmode=${netmode}
					uci -c ${2}/${4}/config set ${pppox_if_config}.${username2}.remotesubnet="${remotesubnet}"
					uci -c ${2}/${4}/config set ${pppox_if_config}.${username2}.local_network="${serverlist_local}"
					#uci -c ${2}/${4}/config set ${pppox_if_config}.${username}.workmode=${workmode}
					uci -c ${2}/${4}/config commit ${pppox_if_config}

					#echo " d uci -c ${2}/${serverlist_id}/config set ${pppox_if_config}.${username2}.local_network=${serverlist_local}" > /dev/console
				fi
			done
		fi
	fi

}


_load_one_user()
{
	local section=$1
	local ppptype=$2
	local server=$3
	
	local matchl2tp=0
	local matchpptp=0
	local matchpppoe=0
	#echo "_load_one_user $1 $2 $3 $4" > /dev/console
	for option in ${pppox_user_options}; do
		eval "config_get ${option} \"${section}\" \"${option}\""
	done
	
	if echo ${type} | grep -iqE "(${pppox_l2tptype}|auto)"; then
		matchl2tp=1
	fi
	if echo ${type} | grep -iqE "(${pppox_pptptype}|auto)"; then
		matchpptp=1
	fi
	if echo ${type} | grep -iqE "(${pppox_pppoetype}|auto)"; then
		matchpppoe=1
	fi

	[ ${matchl2tp} -eq 1 -a ${initl2tp} -eq 1 ] && 
		_echo_info ${pppox_l2tp_path} ${pppox_l2tp_server_path} "l2tp" "$3"
	[ ${matchpptp} -eq 1 -a ${initpptp} -eq 1 ] && 
		_echo_info ${pppox_pptp_path} ${pppox_pptp_server_path} "pptp" "$3"
	[ ${matchpppoe} -eq 1 -a ${initpppoe} -eq 1 ] && 
		_echo_info ${pppox_pppoe_path} ${pppox_pppoe_server_path} "pppoe" "$3"

}

# should run after load pppox configure 
# pppox_load_user { ({l2tp|pptp|pppoe} [<name>]) | all}
# pppox_load_user pptp server1
# $1 type
# $2 name can be empty
pppox_load_user()
{
	local configname=${pppox_user_configname}
	local initl2tp=0
	local initpptp=0
	local initpppoe=0

	#echo "pppox_load_user $1 $2" > /dev/console
	
	_begin_load_user $1 $2
	#echo "initl2tp = ${initl2tp}" > /dev/console
	#echo "initpptp = ${initpptp}" > /dev/console
	#echo "initpppoe = ${initpppoe}" > /dev/console
	if [ ${initl2tp} -eq 1 -o ${initpptp} -eq 1 -o ${initpppoe} -eq 1 ]; then
		config_load ${configname}
		config_foreach _load_one_user user $1 $2
		config_foreach config_clear
	fi
	
	#$2: name of config, can be empty
	_end_load_user $1 $2
}

#$1 l2tp pptp pppoe all
pppox_reset_loadflag()
{
	[ "$1" = "${pppox_l2tptype}" -o "$1" = "all" ] && { rm -rf ${pppox_l2tp_path} \
		${pppox_path}/${pppox_l2tptype}.hasinited; }
	[ "$1" = "${pppox_pptptype}" -o "$1" = "all" ] && { rm -rf ${pppox_pptp_path} \
		${pppox_path}/${pppox_pptptype}.hasinited; }
	[ "$1" = "${pppox_pppoetype}" -o "$1" = "all" ] && { rm -rf ${pppox_pppoe_path} \
		${pppox_path}/${pppox_pppoetype}.hasinited; }
}

