#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     ipgroup core.sh
# brief    
# author   Chen chen
# version  1.0.0
# date     18June15
# histry   arg 1.0.0, 18June15, Chen chen, Create the file.

fw_config_get_global() {
	fw_config_get_section "$1" global { \
		string ip_frag "on" \
		string tcp_noflag "on" \
		string ping_death "on" \
		string ping_large "" \
		string ping_wan "" \
		string tcp_winnuke "" \
		string tcp_fin_syn "" \
		string tcp_fin_noack "" \
		string ip_option "" \
		string ipopt_secure "" \
		string ipopt_strict_route "" \
		string ipopt_stream "" \
		string ipopt_noop "" \
		string ipopt_loose_route "" \
		string ipopt_record_route "" \
		string ipopt_timestamp "" \
	} || return
}

fw_load_dos_defense()
{	
	fw_config_get_global global

	config_get global_ip_frag "settings" "ip_frag"
	config_get global_tcp_noflag "settings" "tcp_noflag"
	config_get global_ping_death "settings" "ping_death"
	config_get global_tcp_noflag "settings" "tcp_noflag"
	config_get global_ping_death "settings" "ping_death"
	config_get global_ping_large "settings" "ping_large"
	config_get global_ping_wan   "settings" "ping_wan"
	config_get global_tcp_winnuke "settings" "tcp_winnuke"
	config_get global_tcp_fin_syn "settings" "tcp_fin_syn"
	config_get global_tcp_fin_noack "settings" "tcp_fin_noack"

	config_get global_ip_option "settings" "ip_option"
	config_get global_ipopt_noop "settings" "ipopt_noop"
	config_get global_ipopt_secure "settings" "ipopt_secure"
	config_get global_ipopt_strict_route "settings" "ipopt_strict_route"
	config_get global_ipopt_stream "settings" "ipopt_stream"
	config_get global_ipopt_loose_route "settings" "ipopt_loose_route"
	config_get global_ipopt_record_route "settings" "ipopt_record_route"
	config_get global_ipopt_timestamp "settings" "ipopt_timestamp"
		
	if iptables -w -C forwarding_rule -j dos_defense 2>/dev/null; then
		iptables -w -F dos_defense
		iptables -w -F dos_defense_input
		iptables -w -F ping_defense -t raw
	else
		iptables -w -N dos_defense
		iptables -w -N dos_defense_input
		iptables -w -N ping_defense -t raw
		iptables -w -I forwarding_rule 1 -j dos_defense
		iptables -w -I input_rule 1 -j dos_defense_input
		iptables -w -I PREROUTING 1 -j ping_defense -p icmp --icmp-type 8 -t raw
	fi

	[ "on" == "$global_tcp_noflag" ] && {
		iptables -w -A dos_defense -p tcp --tcp-flags ALL FIN -j dosdrop --type tcp_noflag
		iptables -w -A dos_defense -p tcp --tcp-flags ALL FIN,URG,PSH -j dosdrop --type tcp_noflag
		iptables -w -A dos_defense -p tcp --tcp-flags ALL NONE -j dosdrop --type tcp_noflag
	}

	[ "on" == "$global_ping_death" ] && {
		iptables -w -A dos_defense -p icmp --icmp-type 8 -m length ! --length 0:65535 -j dosdrop --type ping_death
		iptables -w -A ping_defense -p icmp --icmp-type 8 -m length ! --length 0:65535 -j dosdrop --type ping_death -t raw
	}

	[ "on" == "$global_ping_large" ] && {
		iptables -w -A dos_defense -p icmp --icmp-type 8 -m length ! --length 0:1024 -j dosdrop --type ping_large
		iptables -w -A ping_defense -p icmp --icmp-type 8 -m length ! --length 0:1024 -j dosdrop --type ping_large -t raw
	}

	[ "on" == "$global_ping_wan" ] && {
		iptables -w -A dos_defense_input -p icmp --icmp-type 8 -j ipsecmark --type use

		. /lib/zone/zone_api.sh

		config_load network
		config_get wanmode "global" "wanmode" "1"
		config_get wan_numbers "global" "wan_numbers" ""

		[ -z "${wan_numbers}" ] && wan_numbers=$(seq 1 "${wanmode}")
		for index in ${wan_numbers}; do
			ifaces=$(zone_get_wan_ifaces "WAN${index}")
			for iface in $ifaces; do
				device=$(zone_get_device_byif "${iface}")
				iptables -w -A dos_defense_input -i "${device}" -p icmp --icmp-type 8 -j DROP
			done
		done
		# fw add 4 f dos_defense_input DROP $ { ! -i br-lan -p icmp --icmp-type 8 }
	}

	[ "on" == "$global_tcp_winnuke" ] && {
		iptables -w -A dos_defense -p tcp --tcp-flags URG URG -m multiport --dports 137,138,139,113,53 -j dosdrop --type winnuke
	}

	[ "on" == "$global_tcp_fin_syn" ] && {
		iptables -w -A dos_defense -p tcp --tcp-flags FIN,SYN FIN,SYN -j dosdrop --type tcp_finsyn
	}

	[ "on" == "$global_tcp_fin_noack" ] && {
		iptables -w -A dos_defense -p tcp --tcp-flags FIN,ACK FIN -j dosdrop --type tcp_finnoack
	}
	
	[ "on" == "$global_ip_option" ] && {
		flags=""
		
		[ "on" == "$global_ipopt_noop" ] && flags="$flags""1"
		[ "on" == "$global_ipopt_secure" ] && flags="$flags""2"
		[ "on" == "$global_ipopt_loose_route" ] && flags="$flags""3"
		[ "on" == "$global_ipopt_timestamp" ] && flags="$flags""4"
		[ "on" ==  "$global_ipopt_record_route" ] && flags="$flags""7"
		[ "on" == "$global_ipopt_strict_route" ] && flags="$flags""9"

		flags=$(echo $flags|sed 's/[0-9]/&,/g')
		flags=${flags%?}
		
		[ "on" == "$global_ipopt_stream" ] && flags="$flags"",8"

		iptables -w -A dos_defense -m ipv4options --flags "$flags" --any -j dosdrop --type ip_option
	}
}

fw_exit_all()
{
	if iptables -w -C forwarding_rule -j dos_defense 2>/dev/null; then
		iptables -w -F dos_defense
		iptables -w -D forwarding_rule -j dos_defense
		iptables -w -X dos_defense

		iptables -w -F dos_defense_input
		iptables -w -D input_rule -j dos_defense_input
		iptables -w -X dos_defense_input
		
		iptables -w -F ping_defense -t raw
		iptables -w -D PREROUTING -j ping_defense -p icmp --icmp-type 8 -t raw
		iptables -w -X ping_defense -t raw
	fi
}
