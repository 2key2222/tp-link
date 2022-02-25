#!/bin/sh
# Copyight(c) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     sysparams_net.sh
# bief     
# author   Yuan Fengjia
# vesion   1.0.0
# history  1.0.0, 13May15, Yuanfengjia, Ceate the file


conntrack_init() {
    local ct_max=`uci get profile.@system_params[0].nf_conntrack_max -c /etc/profile.d`
	echo $ct_max > /proc/sys/net/nf_conntrack_max
	echo 10000 > /proc/sys/net/netfilter/nf_conntrack_expect_max
	
}
	
sys_arp_init() {
    #local arp_max = uci_r:get_profile("system_params", "sys_arp_max") or 8192
	echo 512 > /proc/sys/net/ipv4/neigh/default/gc_thresh1
	echo 2048 > /proc/sys/net/ipv4/neigh/default/gc_thresh2
	echo 10000 > /proc/sys/net/ipv4/neigh/default/gc_thresh3
}

sys_fs_init() {
	echo 326060 > /proc/sys/fs/file-max
}

