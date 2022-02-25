#
# Copyright (C) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# 
# brief        mac filter module core shell scripts
# author     Huang Zhenwei
# version    1.0.0 
# date         30Apr2015
# history     30Apr2015    Huang Zhenwei    Create the file

MF_LIBDIR=${MF_LIBDIR:-/lib/mac_filter}

fw_is_loaded() {
    local bool=$(uci_get_state firewall.core.loaded)
    return $((! ${bool:-0}))
}

fw_init() {
    [ -z "$MF_INITIALIZED" ] || return 0
    . $MF_LIBDIR/config.sh
    fw_config_append mac_filter

    for file in $MF_LIBDIR/core_*.sh; do
        . $file
    done
    
    MF_INITIALIZED=1
    return 0
}

fw_start() {
    fw_init

    fw_is_loaded || {
        #syslog $ACCESS_CONTROL_LOG_WNG_FIREWALL_NOT_LOADED
        exit 1
    }

    echo "loading mac_filter"
    fw_load_all mac_filter
    #syslog $LOG_INF_SERVICE_START
}

fw_stop() {
    fw_init
    
    fw_is_loaded || {
        #syslog $ACCESS_CONTROL_LOG_WNG_FIREWALL_NOT_LOADED
        exit 1
    }

    echo "exiting mac_filter"
    fw_exit_all mac_filter
    #syslog $LOG_INF_SERVICE_STOP
}

fw_restart() {
    fw_stop
    fw_start
}

fw_reload() {
    fw_restart
}
