#
# Copyright (C) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# 
# brief        ip mac binding module core shell scripts
# author     Huang Zhenwei
# version    1.0.0 
# date         06May2015
# history     06May2015    Huang Zhenwei    Create the file
#                22May2015    Huang Zhenwei    Include 'zone' support

IMB_LIBDIR=${IMB_LIBDIR:-/lib/imb}

fw_is_loaded() {
    local bool=$(uci_get_state firewall.core.loaded)
    return $((! ${bool:-0}))
}

fw_init() {
    [ -z "$IMB_INITIALIZED" ] || return 0
    . $IMB_LIBDIR/config.sh
   # fw_config_append imb

    for file in $IMB_LIBDIR/core_*.sh; do
        . $file
    done

	. /lib/functions/network.sh
    
    IMB_INITIALIZED=1
    return 0
}

fw_start() {
    fw_init

    fw_is_loaded || {
        #syslog $ACCESS_CONTROL_LOG_WNG_FIREWALL_NOT_LOADED
        exit 1
    }

    echo "loading ip_mac_binding"
    fw_load_all imb
    #syslog $LOG_INF_SERVICE_START
}

fw_stop() {
    fw_init
    
    fw_is_loaded || {
        #syslog $ACCESS_CONTROL_LOG_WNG_FIREWALL_NOT_LOADED
        exit 1
    }

    echo "exiting ip_mac_binding"
    fw_exit_all imb
    #syslog $LOG_INF_SERVICE_STOP
}

fw_restart() {
    fw_stop
    fw_start
}

fw_reload() {
    fw_restart
}
