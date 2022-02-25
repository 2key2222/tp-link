#
# Copyright (C) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# 
# brief        arp defense module core shell scripts
# author     Huang Zhenwei
# version    1.0.0 
# date         15May2015
# history     15May2015    Huang Zhenwei    Create the file

AD_LIBDIR=${AD_LIBDIR:-/lib/arp_defense}

fw_is_loaded() {
    local bool=$(uci_get_state firewall.core.loaded)
    return $((! ${bool:-0}))
}

fw_init() {
    [ -z "$AD_INITIALIZED" ] || return 0
    . $AD_LIBDIR/config.sh
    fw_config_append arp_defense

    for file in $AD_LIBDIR/core_*.sh; do
        . $file
    done
    
    AD_INITIALIZED=1
    return 0
}

fw_start() {
    fw_init

    fw_is_loaded || {
        #syslog $ACCESS_CONTROL_LOG_WNG_FIREWALL_NOT_LOADED
        exit 1
    }

    echo "loading arp_defense"
    fw_load_all arp_defense
    #syslog $LOG_INF_SERVICE_START
}

fw_stop() {
    fw_init
    
    fw_is_loaded || {
        #syslog $ACCESS_CONTROL_LOG_WNG_FIREWALL_NOT_LOADED
        exit 1
    }

    echo "exiting arp_defense"
    fw_exit_all arp_defense
    #syslog $LOG_INF_SERVICE_STOP
}

fw_restart() {
    fw_stop
    fw_start
}

fw_reload() {
    fw_restart
}
