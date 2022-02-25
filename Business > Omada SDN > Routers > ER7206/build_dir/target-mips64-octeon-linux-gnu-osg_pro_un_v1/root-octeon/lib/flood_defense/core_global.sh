#
# Copyright (C) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# 
# brief        flood defense module core_global shell scripts
# author     Huang Zhenwei
# version    1.0.0 
# date         29May2015
# history     29May2015    Huang Zhenwei    Create the file

#
# use "-C" to check if the rule exists
# return: 1 rule exists;
#            0 rule not exists;
#
fw_check() {
	local ret=$(iptables -w -t $1 -C $2 $3 2>&1)
	[ -n "$ret" ] && return 0||return 1
}

fw_config_get_global() {
	fw_config_get_section "$1" global { \
		string tcp_conn_en "off" \
		string udp_conn_en "off" \
		string icmp_conn_en "off" \
		string tcp_src_en "off" \
		string udp_src_en "off" \
		string icmp_src_en "off" \
	} || return
}

fw_config_get_threshold() {
	fw_config_get_section "$1" threshold { \
		string tcp_conn_lim "3000/s" \
		string udp_conn_lim "4000/s" \
		string icmp_conn_lim "500/s" \
		string tcp_src_lim "1000/s" \
		string udp_src_lim "2000/s" \
		string icmp_src_lim "200/s" \
		string tcp_conn_bst "3000" \
		string udp_conn_bst "4000" \
		string icmp_conn_bst "500" \
		string tcp_src_bst "1000" \
		string udp_src_bst "2000" \
		string icmp_src_bst "200" \
	} || return
}

fw_load_all() {
	fw_config_once fw_load_global global threshold
}

fw_exit_all() {
	fw flush 4 m flood_defense
	fw_check "mangle" "FORWARD" "-j flood_defense"
	while [ x$? == x1 ]; do
		fw del 4 m FORWARD flood_defense
		fw_check "mangle" "FORWARD" "-j flood_defense"
	done
	
	fw_check "mangle" "INPUT" "-j flood_defense"
	while [ x$? == x1 ]; do
		fw del 4 m INPUT flood_defense
		fw_check "mangle" "INPUT" "-j flood_defense"
	done
	
	fw del 4 m flood_defense
	
	
	rmmod xt_flood
	rm -f /etc/modules.d/50-xt_flood
}

fw_load_global() {
	fw_config_get_global $1
	
	if [ "on" == $global_tcp_conn_en -o "on" == $global_udp_conn_en \
		-o "on" == $global_icmp_conn_en -o "on" == $global_tcp_src_en \
		-o "on" == $global_udp_src_en -o "on" == $global_icmp_src_en ]; then
		
		cp /lib/modules/files/50-xt_flood /etc/modules.d/50-xt_flood
		insmod xt_flood
		
		if iptables -w -t mangle -A FORWARD -j flood_defense 2>/dev/null; then
			return
		fi

		fw add 4 m flood_defense
		fw add 4 m FORWARD flood_defense 1
		fw add 4 m INPUT flood_defense 1
		
		fw_config_once fw_config_get_threshold $2
		local rule="-m flood --tcp-conn-en $global_tcp_conn_en --tcp-conn-lim $threshold_tcp_conn_lim \
							--tcp-conn-bst $threshold_tcp_conn_bst --udp-conn-en $global_udp_conn_en \
							--udp-conn-lim $threshold_udp_conn_lim --udp-conn-bst $threshold_udp_conn_bst \
							--icmp-conn-en $global_icmp_conn_en --icmp-conn-lim $threshold_icmp_conn_lim \
							--icmp-conn-bst $threshold_icmp_conn_bst --tcp-src-en $global_tcp_src_en \
							--tcp-src-lim $threshold_tcp_src_lim --tcp-src-bst $threshold_tcp_src_bst \
							--udp-src-en $global_udp_src_en --udp-src-lim $threshold_udp_src_lim \
							--udp-src-bst $threshold_udp_src_bst --icmp-src-en $global_icmp_src_en \
							--icmp-src-lim $threshold_icmp_src_lim --icmp-src-bst $threshold_icmp_src_bst"
							
		fw add 4 m flood_defense DROP { "$rule" }
	else
		echo "All types of flood defense are off."
	fi
}
