#!/bin/sh
# dslite.sh - IPv4-in-IPv6 tunnel backend
# Copyright (c) 2013 OpenWrt.org

[ -n "$INCLUDE_ONLY" ] || {
    . /lib/functions.sh
    . /lib/functions/network.sh
    . ../netifd-proto.sh

    config_load /etc/config/sysmode
    config_get mode sysmode mode "router"
    [ "$mode" = "ap" ] && exit 0

    init_proto "$@"
}

proto_dslite_setup() {
    local cfg="$1"
    local iface="$2"
    local link="dslite-$cfg"
    local tunlink="wanv6"

    local mtu ttl peeraddr ip6addr 
    json_get_vars mtu ttl peeraddr ip6addr 

    local server
    json_get_var server AFTR_name
    [ -n "$server" ] && [ -z "$peeraddr" ] && {
        for ip6 in $(resolveip -6 -t 5 "$server"); do
            # ( proto_add_host_dependency "$cfg" "$ip6" )
            peeraddr="$ip6"
        done
    }

    [ -z "$peeraddr" ] && {
        proto_notify_error "$cfg" "MISSING_ADDRESS"
        proto_block_restart "$cfg"
        return
    }
        
    #( proto_add_host_dependency "$cfg" "::" "$tunlink" )

    [ -z "$ip6addr" ] && { 
        local wanif="$tunlink" 
        if [ -z "$wanif" ] && ! network_find_wan6 wanif; then 
            proto_notify_error "$cfg" "NO_WAN_LINK" 
            sleep 5 
            proto_setup_failed "$cfg" 
            return 
        fi 
        
        if ! network_get_ipaddr6 ip6addr "$wanif"; then 
            proto_notify_error "$cfg" "NO_WAN_LINK" 
            sleep 5 
            proto_setup_failed "$cfg" 
            return 
        fi 
    }

    proto_init_update "$link" 1
    proto_add_ipv4_route "0.0.0.0" 0
    proto_add_ipv4_address "192.0.0.2" "" "" "192.0.0.1"

    proto_add_tunnel
    json_add_string mode ipip6
    json_add_int mtu "${mtu:-1280}"
    json_add_int ttl "${ttl:-64}"
    json_add_string local "$ip6addr"
    json_add_string remote "$peeraddr"
    [ -n "$tunlink" ] && json_add_string link "$tunlink"
    proto_close_tunnel

    proto_send_update "$cfg"
}

proto_dslite_teardown() {
    local cfg="$1"
}

proto_dslite_init_config() {
    no_device=1             
    available=1
    proto_config_add_string "AFTR_name"
    proto_config_add_string "ip6addr"
    proto_config_add_string "peeraddr"
    proto_config_add_string "tunlink"
    proto_config_add_int "mtu"
    proto_config_add_int "ttl"
}

[ -n "$INCLUDE_ONLY" ] || {
    add_protocol dslite
}
