#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file      nat_mod_alg.sh
# brief	
# author    Chen chen
# version   1.1.0
# date      23Apr15
# history   arg 1.0.0, 23Apr15, Chen chen, Create the file.
#           arg 1.1.0, 21Dec17, Zhangzhongwei, Rewrite the file.

nat_config_alg()
{
	nat_config_get_section "$1" nat_alg { \
		string ftp on \
		string tftp on \
		string h323 on \
		string sip on \
		string pptp on \
		string l2tp on \
		string ipsec on \
	}|| return
}

nat_config_load_alg()
{
	nat_config_alg "$1"

	nat__do_vpn_passthrough()
	{
		local vpn=$1
		local enable=$2
		local setup_mods=$3	   

		if [[ "$enable" == "off" ]]; then
			local dev=$(uci_get_state nat env lan_dev)
			[ -z "$dev" ] && return
			case $vpn in
				ipsec)
					nat_filter_add lan $MOD_VPN "-A" "-p ah -j DROP"
					nat_filter_add lan $MOD_VPN "-A" "-p esp -j DROP"
					nat_filter_add lan $MOD_VPN "-A" "-p udp -m udp --dport 500 -j DROP"
					nat_filter_add lan $MOD_VPN "-A" "-p udp -m udp --dport 4500 -j DROP"
				;;
				*)
				;;
			esac
			# We have to flush all conntrack, fo make vpn passthrough close at once
			# echo f >/proc/net/nf_conntrack 2>/dev/null
			return
		fi
	}

	nat__do_alg()
	{
		local alg=$1
		local enable=$2
		local setup_mods=$3

		if [[ "$enable" == "on" ]]; then
			for mod in nf_conntrack_${alg} nf_nat_${alg}; do
				list_contains setup_mods $mod || insmod ${mod}
			done
			if [[ "$alg" == "sip" ]]; then
				echo 0 > /sys/module/nf_conntrack_sip/parameters/sip_direct_media
			fi
			if [[ "$alg" == "h323" ]]; then
				echo 0 > /sys/module/nf_conntrack_h323/parameters/gkrouted_only
			fi
		else   
			for mod in nf_nat_${alg} nf_conntrack_${alg}; do
				list_contains setup_mods $mod && rmmod ${mod}
			done
		fi
	}

	[ -n "$nat_alg_ftp" ] && nat__do_alg ftp $nat_alg_ftp "$2"
	[ -n "$nat_alg_tftp" ] && nat__do_alg tftp $nat_alg_tftp "$2"
	[ -n "$nat_alg_h323" ] && nat__do_alg h323 $nat_alg_h323 "$2"
	[ -n "$nat_alg_rtsp" ] && nat__do_alg rtsp $nat_alg_rtsp "$2"
	[ -n "$nat_alg_sip" ] && nat__do_alg sip $nat_alg_sip "$2"
	[ -n "$nat_alg_pptp" ] && nat__do_alg pptp $nat_alg_pptp "$2"
	[ -n "$nat_alg_ipsec" ] && nat__do_vpn_passthrough ipsec $nat_alg_ipsec "$2"
}

nat_alg_load()
{
	local setup_mods=$(lsmod|grep -E 'nf_(nat|conntrack)_*'|awk -F ' ' '{print $1}')
	setup_mods=$(echo $setup_mods | tr '\n' ' ')
	nat_config_once nat_config_load_alg $1 "$setup_mods"
}

nat_flush_rule_alg()
{
	nat_filter_flush ${MOD_VPN} lan
}

nat_alg_run()
{
	local operation=$1
	NAT_LOG_PRINT "@ enter ALG"
	case $operation in
		start)
			# NAT_LOG_PRINT "  flusing old ALG rules"
			# nat_flush_rule_alg

			NAT_LOG_PRINT "  loading ALG modules, building new ALG rules"
			nat_alg_load nat_alg
		;;
		stop)
			NAT_LOG_PRINT "  flusing old ALG rules"
			nat_flush_rule_alg
		;;
	esac
}