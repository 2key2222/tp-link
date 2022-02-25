#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     config_wportal.sh
# brief    
# author   Qian uujun
# version  1.0.0
# date     19Sep15
# histry   arg 1.0.0, 19Sep15, Qian xujun, Create the file.

. /lib/zone/zone_api.sh
. /lib/functions/network.sh

g_iface_enable="off"
g_iface_authserver="no"
g_lan_zone="LAN1"

setWportalIface()
{
	config_foreach wportal_load_authserver wportal $1
    #config_foreach wportal_load_authserver wechat $1
    config_foreach wportal_load_wifiserver wifi $1
}

checkAuthIface()
{
    config_foreach wportal_check_authiface wportal $1
    #config_foreach wportal_check_authiface wechat $1
    config_foreach wportal_check_authiface wifi $1
}

set_wifidog_conf()
{
	delAllAuthServerIface
	delAllWechatIface
	delAllSsid
	delWiredAuth

	vnete ipset create "wlan_mac_list" hash:mac -exist
	
	config_get device dft_wportal interface
	
	for lan_device in ${device}; do
		setWportalIface $lan_device
	done
}

auth_server_start()
{
    config_get global_enable global_set enable

    echo "global_enable is $global_enable"
    echo "g_iface_enable is $g_iface_enable"
    if [ "$global_enable" == "on" ]
    then
        if [ "$g_iface_enable" == "on" ]
        then
            # first start nginx. by Liwei
			mkdir -p /var/log/nginx
			mkdir -p /var/lib/nginx
			mkdir -p /usr/logs
            vnete /etc/init.d/nginx start
            echo "/usr/bin/wifidog-init start"
            vnete /usr/bin/wifidog-init start
        fi
    fi
}

delAllWechatIface()
{
	sed -i '/WechatWhiteIpListInterface/d' /etc/wifidog.conf
	sed -i '/WechatAppId/d' /etc/wifidog.conf
	sed -i '/WechatSecret/d' /etc/wifidog.conf
	sed -i '/WechatCheckInterval/d' /etc/wifidog.conf
}

delAllAuthServerIface()
{
	sed -i '/GatewayInterface/d' /etc/wifidog.conf	
}

delAllSsid()
{
	sed -i '/WLAN_SSID/d' /etc/wifidog.conf	
}

delWiredAuth()
{
	sed -i '/WIRED_AUTH/d' /etc/wifidog.conf	
}


setWifidogIface()
{
    var="\$aGatewayInterface $1"
    sed -i "$var" /etc/wifidog.conf
       
    g_iface_enable="on"
}

setWifidogSsid()
{
    if [ "$1" != "" ]
    then
        var="\$aWLAN_SSID $1"
        sed -i "$var" /etc/wifidog.conf
    fi 
}

setWifidogWiredAuth()
{
    if [ "$1" != "" ]
    then
        var="\$aWIRED_AUTH $1"
        sed -i "$var" /etc/wifidog.conf
    fi	
}

setWifidogWechatIface()
{	
    var="\$aWechatWhiteIpListInterface $1"
    sed -i "$var" /etc/wifidog.conf
}

wportal_config_append(){
	CONFIG_APPEND=1 config_load "$@"
	unset CONFIG_APPEND
}

wportal_load_authserver()
{
	wportal_get_webauth "$1"
    
	if [ "$wportal_enable" == "on" ]
	then
        for iface in ${wportal_interface};do
            if [ "$2" == "$iface" ]
            then
                setWifidogIface $iface
                setWifidogWiredAuth $wportal_wired_auth
                return
            fi
        done			
	fi
}

wportal_load_wifiserver()
{
	wportal_get_wifiauth $1

	if [ "$wifi_enable" == "on" ]
		then
        for iface in ${wifi_interface};do
            if [ "$2" == "$iface" ]
            then
                setWifidogIface $iface
                setWifidogWechatIface $iface
                setWifidogSsid $wifi_ssid
                setWifidogWiredAuth $wifi_wired_auth
                return
            fi
        done			
	fi

	
}

wportal_check_authiface()
{
    wportal_get_webauth "$1"
	if [ "$wportal_enable" == "on" ]
	then
        for iface in ${wportal_interface};do            
            if [ "$2" == "$iface" ]
            then
                g_iface_authserver="yes"
                return
            fi
        done			
	fi    
}

wifidog_interface_restart()
{
    checkAuthIface $1
    echo "g_iface_authserver is $g_iface_authserver" > /tmp/hotdog.log
    if [ "$g_iface_authserver" == "yes" ]
    then
        vnete /usr/bin/wifidog-init restart
    fi
}

wportal_get_webauth() {
	wportal_config_get_section "$1" wportal { \
		string enable "" \
		string interface "" \
		string wired_auth "" \
	} || return

}

wportal_get_wechatauth() {
	wportal_config_get_section "$1" wechat { \
		string enable "" \
		string interface "" \
	} || return

}

wportal_get_wifiauth() {
	wportal_config_get_section "$1" wifi { \
		string enable "" \
		string interface "" \
		string ssid "" \
		string wired_auth "" \
	} 	
}

wportal_config_get_section() { # <config> <prefix> <type> <name> <default> ...
	local config=$1
	local prefix=$2
	shift 2

	[ -n "$config" ] || return 1
	[ -n "$prefix" ] && {
        prefix="${prefix}_"
    }

	#local enabled
	#config_get_bool enabled "$config" enabled 1
	#[ $enabled -eq 1 ] || return 1

	[ "$1" == '{' ] && shift
	while [ $# -ge 3 ]; do
		local type=$1
		local name=$2
		local dflt=$3
		shift 3
		# TODO: Move handling of defaults to /lib/functions.sh
		# and get replace the case block with the following 
		# two lines:
		# type=${type#string}
		# config_get${type:+_${type}} "${prefix}${name}" "$config" "$name" "$dflt" || return
		case "$type" in
			string)
				local tmp
				config_get tmp "$config" "$name" || return
				[ -z "$tmp" ] && tmp=$dflt
				export ${NO_EXPORT:+-n} -- "${prefix}${name}=${tmp}"
				continue
			;;
			boolean)
				type=bool
			;;
		esac;
		
		local cmd=${prefix}config_get_${type}
		type $cmd > /dev/null || {
			cmd=config_get_${type} 
		}
		type $cmd > /dev/null || {
			echo "config type $type (for $name) not supported" >&2
			return 1
		}
		$cmd "${prefix}${name}" "$config" "$name" "$dflt" || return
	done
}
