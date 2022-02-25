# Copyright (C) 2009-2010 OpenWrt.org

syslog() {
    local log_id=$2
    local model_id=$1
    shift
    logx -p $$ $model_id $log_id "$@"
}

add_device() {
    local lenable
    local lmac
    config_get lenable $1 enable "off"
    config_get lmac $1 mac "0"

    # Process firewall rule for each device.
    if [ $lenable == 'on' ]; then
        if [ $lmac != '0' ]; then
            fw add_local_mgnt $lmac
            echo fw add_local_mgnt $lmac
        fi
    fi
}

del_device() {
    local lenable
    local lmac
    config_get lenable $1 enable "off"
    config_get lmac $1 mac "0"

    # Process firewall rule for each device.
    if [ $lenable == 'on' ]; then
        if [ $lmac != '0' ]; then
            fw del_local_mgnt $lmac
            echo fw del_local_mgnt $lmac
        fi
    fi
}

administration_start() {
    echo "loading administration management"
}

administration_stop() {
    echo "stopping administration management"
}

administration_restart() {
    administration_stop 
    administration_start
}
