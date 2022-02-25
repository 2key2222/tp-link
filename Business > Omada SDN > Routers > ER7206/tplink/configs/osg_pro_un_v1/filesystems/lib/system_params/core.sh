# Copyight(c) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     core.sh
# bief     
# author   Yuan Fengjia
# vesion   1.0.0
# history  1.0.0, 13May15, Yuanfengjia, Ceate the file

. /lib/system_params/sysparams_net.sh

sysparams_start() {
    conntrack_init
	sys_arp_init
	sys_fs_init
}

sysparams_stop() {
    return 1
}

sysparams_restart() {
    sysparams_stop
    sysparams_start
}

sysparams_reload() {
    sysparams_restart
}
