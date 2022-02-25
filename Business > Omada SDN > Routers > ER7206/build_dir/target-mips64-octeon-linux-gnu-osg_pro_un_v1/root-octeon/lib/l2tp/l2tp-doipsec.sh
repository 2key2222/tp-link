#!/bin/sh
#author wangdechu
#Usage: 
#	for server->
#		l2tp-doipsec.sh <operation> server <name> <local_binding> <psk>
#	for client->
#		l2tp-doipsec.sh <operation> client <name> <local_binding> <remote_peer> <psk>

. /lib/functions.sh
. /lib/functions/network.sh
. /lib/zone/zone_api.sh
. /lib/l2tp/l2tp-functions.sh

operation=$1
exit 0

if [ "${operation}" = "delete" ]; then
	name=$2
elif [ "${operation}" = "add" ]; then
	isserver=$2
	name=$3
	local_binding=$4
else
	exit 1
fi

downipsec4l2tp()
{
	local xname=$1
#	local count=0
	
#	while :; do
#		let count=count+1
#		[ ${count} -gt 100 ] && break
#		local ress=`ipsec stroke down ${xname}`
#		[ -z "${ress}" ] && break
#	done
	ipsec stroke delete ${xname}
	ipsec stroke down-nb ${xname}{*}
	ipsec stroke purgeike
}

deleteipsec4l2tp()
{
	local section=$1
	local configname=$2
	
	config_get lname "${section}" "name"
	if ( [ "${lname}" = "${name}" ] || [ "${name}" = "all" ] ) && echo ${lname}|grep -q "^${l2tp_ipsec_prefix}" ; then
		downipsec4l2tp ${lname}
		uci delete ${configname}.${section}
		#hasdelete=1
	fi
}

########## delete ###############
if [ "${operation}" = "delete" ]; then
	#hasdelete=0
	config_load ipsec
	config_foreach deleteipsec4l2tp connection ipsec
	config_foreach config_clear
	uci commit ipsec
	
	config_load ipsec_secrets
	config_foreach deleteipsec4l2tp authentication ipsec_secrets
	config_foreach config_clear
	uci commit ipsec_secrets
	
	#cancel the ipsec reload to improve the efficiency when delete multi items --chenxing
	#[ ${hasdelete} -eq 1 ] && { 
	#	/etc/init.d/ipsec reload
	#	}
	exit 0
fi


########## add ###############
ipsecchanged=-1 
secretschanged=-1
ipsecsection=
secretssection=

if [ "${isserver}" = "server" ]; then

	remote_peer=0.0.0.0
	psk=$5
elif [ "${isserver}" = "client" ]; then
	remote_peer=$5
	psk=$6
else
	exit 1
fi


getipsecsection()
{
	local section=$1
	local lisserver=$2
	local sname=$3
	
	config_get lname "${section}" "name"
	if [ "${lname}" != "${sname}" ]; then
		return 0
	fi
	ipsecchanged=1
	ipsecsection=${section}	
	
}

getsecretssection()
{
	local section=$1
	local sname=$2
	
	config_get lname "${section}" "name"
	if [ "${lname}" != "${sname}" ]; then
		return 0
	fi
	secretschanged=1
	secretssection=${section}	

}

isipaddr()
{
	local regex="\b(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[1-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[1-9])\b"
	
	if echo $1|egrep -q ${regex}; then
		echo 1
	else
		echo 0
	fi
}


config_load ipsec
config_foreach getipsecsection connection ${isserver} ${3}
config_foreach config_clear

config_load ipsec_secrets
config_foreach getsecretssection authentication ${3}
config_foreach config_clear


if [ ${ipsecchanged} -eq 1 -o ${secretschanged} -eq 1 ]; then

	downipsec4l2tp ${name}
	uci delete ipsec.${ipsecsection} 2>/dev/null
	uci delete ipsec_secrets.${secretssection} 2>/dev/null
fi

[ "${operation}" != "add" ] && exit 1

iface=$(zone_get_effect_main_wan_ifaces ${local_binding})
network_get_ipaddr ipaddr ${iface}
if [ -z "${ipaddr}" ]; then
	local_network=---
else
	local_network=${ipaddr}/32
fi
	
if [ "${isserver}" = "server" ]; then
	local_port=1701

	remote_port=0
	remote_network=0.0.0.0/0
	connection_type=responder
		
	remote_id_type=ANY
	remote_id_value=
	
	

elif [ "${isserver}" = "client" ]; then
	#remote_peer is fqdn?
	remote_network=${remote_peer}/32
	local_port=0
	remote_port=1701
	connection_type=initiator
	
	#######################ipsec_secrets
	isip=`isipaddr "${remote_peer}"`
	if [ ${isip} -eq 1 ]; then
		remote_id_type=IP_ADDRESS_PURELY
	else
		remote_id_type=IP_ADDRESS_FROM_DNSNAME
	fi
	remote_id_value=${remote_peer}
fi

#######################ipsec_secrets
if [ -z "${ipaddr}" ]; then
	local_id_type=IP_ADDRESS_FROM_LOCAL_IFNAME
	local_id_value=${local_binding}
else
	local_id_type=IP_ADDRESS_PURELY
	local_id_value=${ipaddr}
fi

protocol=17
ike_stage2=_[[l2tp]]_ike_ph2
ike_stage1=_[[l2tp]]_ike_ph1
config_mode=disable
status=enable
rightfirewall=yes
leftupdown=/lib/l2tp/l2tp-ipsec-up-down.sh

uci add ipsec connection
uci set ipsec.@connection[-1].name=${name}
uci set ipsec.@connection[-1].local_binding=${local_binding}
uci set ipsec.@connection[-1].local_binding_type="if_name"
uci set ipsec.@connection[-1].remote_peer=${remote_peer}
[ "${remote_id_type}" = "IP_ADDRESS_FROM_DNSNAME" ] && {
	uci set ipsec.@connection[-1].remote_peer_type="domain_name"; }
[ "${remote_id_type}" = "IP_ADDRESS_PURELY" -o "${isserver}" = "server" ] && {
	uci set ipsec.@connection[-1].remote_peer_type="ip_address"; }
uci set ipsec.@connection[-1].local_port=${local_port}
uci set ipsec.@connection[-1].local_network=${local_network}

uci set ipsec.@connection[-1].protocol=${protocol}
uci set ipsec.@connection[-1].remote_port=${remote_port}
uci set ipsec.@connection[-1].remote_network=${remote_network}
uci set ipsec.@connection[-1].ike_stage2=${ike_stage2}
uci set ipsec.@connection[-1].ike_stage1=${ike_stage1}
uci set ipsec.@connection[-1].config_mode=${config_mode}
uci set ipsec.@connection[-1].connection_type=${connection_type}
uci set ipsec.@connection[-1].status=${status}
uci set ipsec.@connection[-1].leftupdown=${leftupdown}
uci set ipsec.@connection[-1].rightfirewall=${rightfirewall}


auth_mode=pre_share_key
uci add ipsec_secrets authentication
uci set ipsec_secrets.@authentication[-1].name=${name}
uci set ipsec_secrets.@authentication[-1].auth_mode=${auth_mode}
uci set ipsec_secrets.@authentication[-1].psk=${psk}
uci set ipsec_secrets.@authentication[-1].local_id_type=${local_id_type}
uci set ipsec_secrets.@authentication[-1].local_id_value=${local_id_value}
uci set ipsec_secrets.@authentication[-1].remote_id_type=${remote_id_type}
uci set ipsec_secrets.@authentication[-1].remote_id_value=${remote_id_value}



uci commit ipsec
uci commit ipsec_secrets

#/etc/init.d/ipsec reload 
#cancel the ipsec reload to improve the efficiency when add multi items(when DUT init) --chenxing




