#!/bin/sh

dhcps_option_add()
{
	local section="$1"
	local value="$2"
	local configfile="$3"
	echo -e "\toption $section '$value'" >> $configfile
}

dhcps_list_add()
{
	local list="$1"
	local value="$2"
	local configfile="$3"
	echo "	list $list '$value'" >> $configfile
}

build_dhcps_config()
{
	local config="$1"
	
	config_get dhcp_on "$config" dhcp_on
	[ -z "$dhcp_on" ] && {
		return 0
	}
	
	local CONFIGFILE="$2"

	config_get netmask "$config" netmask ''
	config_get dhcp_start "$config" dhcp_start ''
	config_get dhcp_end "$config" dhcp_end ''
	config_get dhcp_release_time "$config" dhcp_release_time ''
	config_get dhcp_gateway "$config" dhcp_gateway ''
	config_get dhcp_dns "$config" dhcp_dns
	config_get dhcp_controller "$config" dhcp_controller ''
	config_get dhcp_option15 "$config" dhcp_option15 ''
	config_get dhcp_option43 "$config" dhcp_option43 ''
	config_get dhcp_option60 "$config" dhcp_option60 '' 
	config_get dhcp_option66 "$config" dhcp_option66 ''
	config_get dhcp_option138 "$config" dhcp_option138 ''
	config_get dhcp_option150 "$config" dhcp_option150 ''
	config_get dhcp_option159 "$config" dhcp_option159 ''
	config_get dhcp_option160 "$config" dhcp_option160 ''
	config_get dhcp_option176 "$config" dhcp_option176 ''
	config_get dhcp_option242 "$config" dhcp_option242 ''
	config_get ifname "$config" ifname
	
 	[ -f $CONFIGFILE ] && {
		sed -i -e "/config vinterface '$config'/,/option ifname '$ifname'/d" $CONFIGFILE
	}
	echo -e "config vinterface '$config'" >> $CONFIGFILE
	
	if [ $dhcp_on = "0" ];then
		dhcps_option_add ignore '1' $CONFIGFILE
	else
		dhcps_option_add ignore '0' $CONFIGFILE
	fi
	
	if [ -n "$dhcp_gateway" ];then
		dhcps_list_add dhcp_option "3,$dhcp_gateway" $CONFIGFILE
	fi
	
	if [ -n "$dhcp_dns" ];then
		dhcps_list_add dhcp_option "6,$dhcp_dns" $CONFIGFILE
	fi
	
	if [ -n "$dhcp_option15" ];then
		dhcps_list_add dhcp_option "15,$dhcp_option15" $CONFIGFILE
	else
		dhcps_list_add dhcp_option "15," $CONFIGFILE
	fi
	
	if [ -n "$dhcp_option60" ];then
		dhcps_list_add dhcp_option "60,${dhcp_option60//'/'\''}" $CONFIGFILE
	fi
	
	if [ -n "$dhcp_option66" ];then
		dhcps_list_add dhcp_option "66,${dhcp_option66//'/'\''}" $CONFIGFILE
	fi
	
	if [ -n "$dhcp_option150" ];then
		dhcps_list_add dhcp_option "150,${dhcp_option150//'/'\''}" $CONFIGFILE
	fi
	
	if [ -n "$dhcp_option159" ];then
		dhcps_list_add dhcp_option "159,${dhcp_option159//'/'\''}" $CONFIGFILE
	fi
	
	if [ -n "$dhcp_option160" ];then
		dhcps_list_add dhcp_option "160,${dhcp_option160//'/'\''}" $CONFIGFILE
	fi
	
	if [ -n "$dhcp_option176" ];then
		dhcps_list_add dhcp_option "176,${dhcp_option176//'/'\''}" $CONFIGFILE
	fi
	
	if [ -n "$dhcp_option242" ];then
		dhcps_list_add dhcp_option "242,${dhcp_option242//'/'\''}" $CONFIGFILE
	fi
	
	if [ -n "$dhcp_option138" ];then
		dhcps_list_add dhcp_option "138,$dhcp_option138" $CONFIGFILE
	elif [ -n "$dhcp_controller" ];then
		dhcps_list_add dhcp_option "138,$dhcp_controller" $CONFIGFILE
	fi
	
	if [ -z "$dhcp_start" ];then
		dhcps_option_add dhcp_start '0.0.0.0' $CONFIGFILE
	else
		dhcps_option_add dhcp_start $dhcp_start $CONFIGFILE
	fi
	
	if [ -z "$dhcp_end" ];then
		dhcps_option_add dhcp_end '0.0.0.0' $CONFIGFILE
	else
		dhcps_option_add dhcp_end $dhcp_end $CONFIGFILE
	fi
	
	if [ -z "$netmask" ];then
		dhcps_option_add netmask '255.255.255.0' $CONFIGFILE
	else
		dhcps_option_add netmask $netmask $CONFIGFILE
	fi
	
	if [ -z "$dhcp_release_time" ];then
		dhcps_option_add dhcp_release_time '120m' $CONFIGFILE
	else
		dhcps_option_add dhcp_release_time $dhcp_release_time $CONFIGFILE
	fi
	
	dhcps_option_add dynamicdhcp '1' $CONFIGFILE
	dhcps_option_add addrtype 'iprange' $CONFIGFILE
	dhcps_option_add interface 'lan' $CONFIGFILE
	# it should be set last so that we could override the config
	dhcps_option_add ifname $ifname $CONFIGFILE

	echo >> $CONFIGFILE
	chmod +x $CONFIGFILE
	
}

build_dhcps_dnsmasq()
{
	local CONFIGFILE="$1"
	sed -i "/config dnsmasq/,/option nonwildcard*/d" $CONFIGFILE
	
	echo "config dnsmasq" >> $CONFIGFILE
	
	dhcps_option_add domainneeded '1' $CONFIGFILE
	dhcps_option_add port '0' $CONFIGFILE
	dhcps_option_add boguspriv '1' $CONFIGFILE
	dhcps_option_add filterwin2k '0' $CONFIGFILE
	dhcps_option_add localise_queries '1' $CONFIGFILE
	dhcps_option_add rebind_protection '1' $CONFIGFILE
	dhcps_option_add rebind_localhost '1' $CONFIGFILE
	dhcps_option_add local '/lan/' $CONFIGFILE
	dhcps_option_add domain 'lan' $CONFIGFILE
	dhcps_option_add expandhosts '1' $CONFIGFILE
	dhcps_option_add nonegcache '0' $CONFIGFILE
	dhcps_option_add authoritative '1' $CONFIGFILE
	dhcps_option_add readethers '1' $CONFIGFILE
	dhcps_option_add leasefile '/tmp/dhcp.leases' $CONFIGFILE
	dhcps_option_add resolvfile '/tmp/resolv.conf.auto' $CONFIGFILE
	dhcps_option_add nonwildcard '1' $CONFIGFILE

	echo >> $CONFIGFILE

}

clean_dhcps_config()
{
	local config="$1"
	
	local CONFIGFILE="$2"
	
 	[ -f $CONFIGFILE ] && {
		config_load dhcp
		config_get ifname "$config" ifname
		sed -i -e "/config vinterface '$config'/,/option ifname '$ifname'/d" $CONFIGFILE
		chmod +x $CONFIGFILE
	}
	
}
