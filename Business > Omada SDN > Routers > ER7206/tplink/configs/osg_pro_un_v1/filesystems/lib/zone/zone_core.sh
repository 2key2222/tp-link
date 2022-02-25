# Copyight(c) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     zone_conf.sh
# bief     Config the zone info
# author   Yuan Fengjia
# vesion   1.0.0
# history  1.0.0, 13May15, Yuanfengjia, Ceate the file

. /lib/functions.sh
. /lib/functions/network.sh
. /lib/zone/zone_conf.sh
. /lib/zone/zone_init.sh
include /lib/network


zone_main() {
    config_load zone
    uci_revert_state zone
    uci_set_state zone core "" zone_state
    
    zone_config
}

zone_start() {
  zone_main
}

zone_stop() {
    uci_revert_state zone
}

zone_restart() {
    zone_start
}
