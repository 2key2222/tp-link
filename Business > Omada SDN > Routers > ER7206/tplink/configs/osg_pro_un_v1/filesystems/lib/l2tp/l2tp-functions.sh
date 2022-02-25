#!/bin/sh
#author: wangdechu
#brief: common functions used for dealing with l2tp server and client

. /lib/functions.sh
. /lib/pppox/pppox-default-variables.sh
. /lib/zone/zone_api.sh
. /lib/pppox/pppox-header.sh
. /lib/firewall/fw.sh
. /lib/pppox/pppox-remote-management.sh

l2tp_global_options="l2tphellointerval lcpechointerval"
l2tp_lns_options="bindif ipsecenc presharekey enable authtype"
l2tp_lac_options="tunnelname username password lns outif ipsecenc presharekey workmode remotesubnet enable local_network"

l2tp_server_configname=l2tp-server
l2tp_client_configname=l2tp-client

l2tp_global4server_path=/tmp/l2tp/global4server
l2tp_global4client_path=/tmp/l2tp/global4client

l2tp_ifdevice_info=l2tp-ifdevice-info
l2tp_started=l2tp-started
l2tp_ipsec_prefix=X_l2tp_

fw_check() {
	local ret=$(iptables -w -t $1 -C $2 $3 2>&1)
	[ -n "$ret" ] && return 0||return 1
}

_load_global() 
{
	local section=$1
	local subpath=$2
	local configname=${pppox_configname}
	local section=global
	local configtype=global
	local path
	
	path=${subpath}/config
	mkdir -p ${path}
	touch ${path}/${configname}
	uci -c ${path} set ${configname}.${section}=${configtype}
	
	for option in ${l2tp_global_options}; do
		config_get myoptionvalue ${section} ${option}
		[ "${myoptionvalue}" = "" ] && continue
		uci -c ${path} set ${configname}.${section}.${option}=${myoptionvalue}
	done
	uci -c ${path} commit ${configname}
}


_load_one_client_or_server()
{
	local section=$1
	local subpath=$2
	local configname=$3
	local options=$4
	local configtype=$5
	local wishsection=$6
	local path
	
	if [ "${configtype}" = "lac" ]; then
		config_get idd ${section} "id"
		section1=${idd}
	else
		section1=${section}
	fi
	
	[ "${wishsection}" != "${section1}" -a "${wishsection}" != "all" ] && return 0
	
	path=${subpath}/${section1}/config
	mkdir -p ${path}
	touch ${path}/${configname}
	uci -c ${path} set ${configname}.${section1}=${configtype}
	
	for option in ${options}; do
		config_get myoptionvalue ${section} ${option}
		[ "${myoptionvalue}" = "" ] && continue
		uci -c ${path} set ${configname}.${section1}.${option}="${myoptionvalue}"
	done
	

	uci -c ${path} commit ${configname}
	
	touch ${path}/${pppox_l2tptype}.type #used for user manager checking the type of pppox

}

##
#l2tp_load_client_or_server {lns|lac} {all|global|<section>}
l2tp_load_client_or_server()
{
	local configtype=$1
	local wishsection=$2
	local configname
	local globalpath
	local subpath
	local options
	
	[ "${configtype}" != "lac" -a "${configtype}" != "lns" ] && return 0
	
	[ "${configtype}" = "lns" ] && mkdir -p ${pppox_l2tp_server_path}
	[ "${configtype}" = "lac" ] && mkdir -p ${pppox_l2tp_client_path}
	
	[ "${configtype}" = "lac" ] && configname=${l2tp_client_configname} && subpath=${pppox_l2tp_client_path} && 
		options=${l2tp_lac_options} && globalpath=${l2tp_global4client_path}
	[ "${configtype}" = "lns" ] && configname=${l2tp_server_configname} && subpath=${pppox_l2tp_server_path} && 
		options=${l2tp_lns_options} && globalpath=${l2tp_global4server_path}
	
	config_load ${configname}
	[ "${wishsection}" = "global" -o "${wishsection}" = "all" ] && config_foreach _load_global global ${globalpath}
	config_foreach _load_one_client_or_server ${configtype} ${subpath} ${pppox_configname} "${options}" ${configtype} ${wishsection}
	config_foreach config_clear
}


_l2tp_pppoptions_for_server()
{
	echo "auth" >$1
	[ "${2}" != "0" ] && { echo "lcp-echo-interval ${2}" >>$1;
		echo "lcp-echo-failure 5" >>$1; }
	echo "plugin ${pppox_ppp4tplinkso}" >>$1
	echo "path ${3}" >>$1
	echo "plugin ${pppox_ippoolso}" >>$1
	echo "require-mschap-v2" >>$1
	echo "mru 1460" >>$1
	echo "mtu 1460" >>$1
	echo "refuse-pap" >>$1
	echo "refuse-chap" >>$1
	echo "refuse-mschap" >>$1
	echo "refuse-eap" >>$1
	echo "noccp" >>$1
	echo "99.99.99.99:" >>$1
	echo "proxyarp" >>$1
	echo "zonex ${4}" >>$1
}

_l2tp_pppoptions_for_client()
{
	echo "user '${2}'" >$1
	echo "password '${3}'" >>$1
	[ "${4}" != "0" ] && { echo "lcp-echo-interval ${4}" >>$1;
		echo "lcp-echo-failure 5" >>$1; }
	echo "noipdefault" >>$1
	echo "usepeerdns" >>$1
	echo "noauth" >>$1
	echo "persist" >>$1
	echo "maxfail 5" >>$1
	echo "plugin ${pppox_ppp4tplinkso}" >>$1
	echo "path ${5}" >>$1
	echo "ifname ${l2tp_header}${6}" >>$1 #interface name like "l2tp-<tunnelname>"
	echo "noccp" >>$1
	echo "refuse-eap" >>$1
	echo "zonex ${7}" >>$1
}

l2tp_save_ifdevice_info()
{
	local mif=$1
	local name=$2
	local option=$3

	[ ! -f ${pppox_l2tp_main_path}/${l2tp_ifdevice_info} ] && touch ${pppox_l2tp_main_path}/${l2tp_ifdevice_info}

	mif=`zone_get_effect_main_wan_ifaces ${mif}`
	[ -z "${mif}" ] && { echo ""; return 0; }

	local device=`zone_get_device_byif ${mif}`
	device=${device%% *}

#	local lstate=`zone_get_iface_state ${mif}`
#	[ ${lstate} == "DOWN" ] && device=

	local ifsection
	local devsection
	if [ -n "${device}" ]; then 
		ifsection=if_${mif}
		ifsection=${ifsection//./_}
		#ifsection=${ifsection//-/_}
		devsection=dev_${device}
		devsection=${devsection//./_}
		#devsection=${devsection//-/_}
		uci -c ${pppox_l2tp_main_path} set ${l2tp_ifdevice_info}.${ifsection}=info
		uci -c ${pppox_l2tp_main_path} add_list ${l2tp_ifdevice_info}.${ifsection}.${option}=${name}
		uci -c ${pppox_l2tp_main_path} set ${l2tp_ifdevice_info}.${devsection}=info
		uci -c ${pppox_l2tp_main_path} add_list ${l2tp_ifdevice_info}.${devsection}.${option}=${name}
		uci -c ${pppox_l2tp_main_path} commit ${l2tp_ifdevice_info}
	fi
	echo ${device}
}

#$1 (1|0)
#$2 (interface or device)
enable_packet(){
	local local_service_chain=local_service_rule
	if [ "$1" == "0" -o $1 == "off" ];then
		#block the packet from $2
		echo "block"
		#interface=$(zone_get_effect_devices $2)
		local inter=$(zone_get_effect_main_wan_ifaces $2)
		interface=$(zone_get_device_byif $inter)
		for iface in $interface;do
			[ -n "$iface" -a "$iface" != "loopback" ] && {
				local rule="-i ${iface} -p udp --dport 1701"
				fw_check "filter" "$local_service_chain" "$rule -j ACCEPT"
				[ x$? == x1 ] && fw del 4 f $local_service_chain ACCEPT $ { "$rule" }
			}
		done
		refresh_vpn_remote_management
	else
		echo "allow"
		#interface=$(zone_get_effect_devices $2)
		local inter=$(zone_get_effect_main_wan_ifaces $2)
		interface=$(zone_get_device_byif $inter)
		for iface in $interface;do
			[ -n "$iface" -a "$iface" != "loopback" ] && {
				local rule="-i ${iface} -p udp --dport 1701"
				fw_check "filter" "$local_service_chain" "$rule -j ACCEPT"
				[ x$? == x0 ] && fw add 4 f $local_service_chain ACCEPT $ { "$rule" }
			}
		done
		refresh_vpn_remote_management
	fi
}

##
#_l2tp_distribute_server <servername>
_l2tp_distribute_server()
{
	local server_name=$1
	local path=${pppox_l2tp_server_path}/${server_name}/config
	
	local enable=`uci -c ${path} get ${pppox_configname}.${server_name}.enable 2>/dev/null`
	[ "${enable}" != "yes" ] && return 0
	
	local bindif=`uci -c ${path} get ${pppox_configname}.${server_name}.bindif 2>/dev/null`
	local ipsecenc=`uci -c ${path} get ${pppox_configname}.${server_name}.ipsecenc 2>/dev/null`
	local presharekey=`uci -c ${path} get ${pppox_configname}.${server_name}.presharekey 2>/dev/null`
	local authtype=`uci -c ${path} get ${pppox_configname}.${server_name}.authtype 2>/dev/null`
	local lcpechointerval=`uci -c ${l2tp_global4server_path}/config get ${pppox_configname}.global.lcpechointerval 2>/dev/null`
	
	local pppoptfile
	pppoptfile=${pppox_l2tp_server_path}/${server_name}/config/ppp-options
	_l2tp_pppoptions_for_server "${pppoptfile}" "${lcpechointerval}" "${path%\/config}" "${bindif}"
	
#ipsec do something

	#save the interface and device info
	local device=`l2tp_save_ifdevice_info "${bindif}" "${server_name}" "server"`
	[ -z "${device}" ] && return 0

	enable_packet "1" "$bindif"
	
	#distribute l2tp config to xl2tpd process
	xl2tpd-control add-lns ${server_name} bind if = ${device} pppoptfile = ${pppoptfile} \
		hidden bit = yes length bit = yes assign ip = no 
	
	#distribute ipsec config to charon process
	#[ "${ipsecenc}" != "no" ] && [ -n "${presharekey}" ] && {
	#	/lib/l2tp/l2tp-doipsec.sh add server ${l2tp_ipsec_prefix}${server_name} ${bindif} "${presharekey}"
	#	}
}

##
#_l2tp_distribute_client <clientname>
_l2tp_distribute_client()
{
	local name=$1
	local path=${pppox_l2tp_client_path}/${name}/config
	local username=`uci -c ${path} get ${pppox_configname}.${name}.username 2>/dev/null`
	local password=`uci -c ${path} get ${pppox_configname}.${name}.password 2>/dev/null`
	local lns=`uci -c ${path} get ${pppox_configname}.${name}.lns 2>/dev/null`
	local outif=`uci -c ${path} get ${pppox_configname}.${name}.outif 2>/dev/null`
	local ipsecenc=`uci -c ${path} get ${pppox_configname}.${name}.ipsecenc 2>/dev/null`
	local presharekey=`uci -c ${path} get ${pppox_configname}.${name}.presharekey 2>/dev/null`
	local enable=`uci -c ${path} get ${pppox_configname}.${name}.enable 2>/dev/null`
	local tunnelname=`uci -c ${path} get ${pppox_configname}.${name}.tunnelname 2>/dev/null`	
	local lcpechointerval=`uci -c ${l2tp_global4client_path}/config get ${pppox_configname}.global.lcpechointerval 2>/dev/null`
	
	
	[ "${enable}" != "yes" ] && return 0
	
	local pppoptfile
	password=${password//\\/\\\\}
	password=${password//\'/\\\'}
	username=${username//\\/\\\\}
	username=${username//\'/\\\'}
	pppoptfile=${pppox_l2tp_client_path}/${name}/config/ppp-options
	_l2tp_pppoptions_for_client "${pppoptfile}" "${username}" "${password}" "${lcpechointerval}" "${path%\/config}" "${tunnelname}" "${outif}"
	
#ipsec do something
	
	#save the interface and device info
	local device=`l2tp_save_ifdevice_info "${outif}" "${name}" "client"`
	[ -z "${device}" ] && return 0

	#distribute l2tp config to xl2tpd process
	xl2tpd-control add-lac ${name} lns = ${lns} out if = ${device} pppoptfile = ${pppoptfile} \
		autodial = no redial = yes redial timeout = 30
	
	#distribute ipsec config to charon process
	#[ "${ipsecenc}" != "no" ] && [ -n "${presharekey}" ] && {
	#	/lib/l2tp/l2tp-doipsec.sh add client ${l2tp_ipsec_prefix}${name} ${outif} ${lns} ${presharekey}
	#	}
	
	#if ipsec tunnel has been installed, then connect the client directly
	local ipsecdone=`uci -c ${pppox_l2tp_main_path} get l2tpclient-ipsec-info.${name} 2>/dev/null`
	[ "${ipsecdone}" = "info" -o "${ipsecenc}" != "yes" ] && xl2tpd-control connect ${name}
}

##
#distribute the global config of l2tp server
_l2tp_distribute_global4server()
{
	local path=${l2tp_global4server_path}/config
	local hellodelay=`uci -c ${path} get ${pppox_configname}.global.l2tphellointerval 2>/dev/null`
	xl2tpd-control add-global global hello delay server = ${hellodelay}
}

##
#distribute the global config of l2tp client
_l2tp_distribute_global4client()
{
	local path=${l2tp_global4client_path}/config
	local hellodelay=`uci -c ${path} get ${pppox_configname}.global.l2tphellointerval 2>/dev/null`
	xl2tpd-control add-global global hello delay client = ${hellodelay}
}

l2tp_distribute()
{
	[ $# -ne 2 ] && return 1

	if [ "$1" = "lns" ]; then
		[ "$2" != "global" ] && _l2tp_distribute_server $2
		[ "$2" = "global" ] && _l2tp_distribute_global4server
	elif [ "$1" = "lac" ]; then
		[ "$2" != "global" ] && _l2tp_distribute_client $2
		[ "$2" = "global" ] && _l2tp_distribute_global4client
	else
		return 1 #error
	fi
}

_delete_ifdevice_info()
{
	local lsection=$1
	local ltype=$2
	local lname=$3
	local option

	[ "${ltype}" == "lns" ] && option=server
	[ "${ltype}" == "lac" ] && option=client

	config_get l2tpconfig ${lsection} ${option}
	for ii in ${l2tpconfig}; do
		[ "${ii}" == "${lname}" ] && {
			uci -c ${pppox_l2tp_main_path} del_list ${l2tp_ifdevice_info}.${lsection}.${option}=${lname}
		}
	done
	uci -c ${pppox_l2tp_main_path} commit ${l2tp_ifdevice_info}

}

_l2tp_cdistribute()
{
	local ltype=$1
	local lname=$2
	local option
	local path=${pppox_l2tp_server_path}/${lname}/config
	local bindif=`uci -c ${path} get ${pppox_configname}.${lname}.bindif 2>/dev/null`

	[ "${ltype}" == "lns" ] && {
		option=server
		enable_packet "0" "$bindif"
	}
	[ "${ltype}" == "lac" ] && option=client

	xl2tpd-control remove-${ltype} ${lname}
	#/lib/l2tp/l2tp-doipsec.sh delete ${l2tp_ipsec_prefix}${lname}
#	export UCI_CONFIG_DIR=${pppox_l2tp_main_path}
#	config_load ${l2tp_ifdevice_info}
#	config_foreach _delete_ifdevice_info info ${ltype} ${lname}
#	config_foreach config_clear
#	export UCI_CONFIG_DIR=

	## wvr1300 can not deal regular expression: \s, use space
	sed -ri "/list +${option} +'${lname}'/d" ${pppox_l2tp_main_path}/${l2tp_ifdevice_info}
}

#contrary to l2tp_distribute
l2tp_cdistribute()
{
	[ $# -ne 2 ] && return 1

	if [ "$1" = "lns" ]; then
		[ "$2" != "global" ] && _l2tp_cdistribute lns $2
	elif [ "$1" = "lac" ]; then
		[ "$2" != "global" ] && _l2tp_cdistribute lac $2
	else
		return 1 #error
	fi
}

