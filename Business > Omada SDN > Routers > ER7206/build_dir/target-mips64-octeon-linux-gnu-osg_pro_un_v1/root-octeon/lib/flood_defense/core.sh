#
# Copyright (C) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# 
# brief        flood defense module core shell scripts
# author     Huang Zhenwei
# version    1.0.0 
# date         29May2015
# history     29May2015    Huang Zhenwei    Create the file

FD_LIBDIR=${FD_LIBDIR:-/lib/flood_defense}

fw_is_loaded() {
    local bool=$(uci_get_state firewall.core.loaded)
    return $((! ${bool:-0}))
}

fw_init() {
    [ -z "$FD_INITIALIZED" ] || return 0
    . $FD_LIBDIR/config.sh
    fw_config_append flood_defense

    for file in $FD_LIBDIR/core_*.sh; do
        . $file
    done
    
    FD_INITIALIZED=1
    return 0
}

fw_start() {
    fw_init

    fw_is_loaded || {
        #syslog $ACCESS_CONTROL_LOG_WNG_FIREWALL_NOT_LOADED
        exit 1
    }

    echo "loading flood defense"
    fw_load_all flood_defense
    #syslog $LOG_INF_SERVICE_START
}

fw_stop() {
    fw_init
    
    fw_is_loaded || {
        #syslog $ACCESS_CONTROL_LOG_WNG_FIREWALL_NOT_LOADED
        exit 1
    }

    echo "exiting flood defense"
    fw_exit_all flood_defense
    #syslog $LOG_INF_SERVICE_STOP
}

fw_restart() {
    fw_stop
    fw_start
}

fw_reload() {
    fw_restart
}
