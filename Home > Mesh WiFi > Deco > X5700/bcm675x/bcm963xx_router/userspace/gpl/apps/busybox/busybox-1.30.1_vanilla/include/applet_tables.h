/* This is a generated file, don't edit */

#define NUM_APPLETS 86
#define KNOWN_APPNAME_OFFSETS 4

const uint16_t applet_nameofs[] ALIGN2 = {
103,
249,
372,
};

const char applet_names[] ALIGN1 = ""
"[" "\0"
"[[" "\0"
"add-shell" "\0"
"arp" "\0"
"arping" "\0"
"ash" "\0"
"bash" "\0"
"blockdev" "\0"
"cat" "\0"
"chmod" "\0"
"chrt" "\0"
"cp" "\0"
"cut" "\0"
"date" "\0"
"dd" "\0"
"depmod" "\0"
"df" "\0"
"dmesg" "\0"
"du" "\0"
"echo" "\0"
"expr" "\0"
"false" "\0"
"fatattr" "\0"
"free" "\0"
"fstrim" "\0"
"ftpget" "\0"
"grep" "\0"
"gzip" "\0"
"halt" "\0"
"i2cdetect" "\0"
"i2cdump" "\0"
"i2cget" "\0"
"i2cset" "\0"
"ifconfig" "\0"
"init" "\0"
"insmod" "\0"
"kill" "\0"
"killall" "\0"
"klogd" "\0"
"linux32" "\0"
"linux64" "\0"
"ln" "\0"
"logger" "\0"
"logread" "\0"
"ls" "\0"
"md5sum" "\0"
"mdev" "\0"
"mkdir" "\0"
"mknod" "\0"
"modprobe" "\0"
"more" "\0"
"mount" "\0"
"nc" "\0"
"netstat" "\0"
"ntpd" "\0"
"ping" "\0"
"ping6" "\0"
"ps" "\0"
"pwd" "\0"
"pwdx" "\0"
"reboot" "\0"
"remove-shell" "\0"
"rm" "\0"
"rmmod" "\0"
"route" "\0"
"sh" "\0"
"sha256sum" "\0"
"sleep" "\0"
"smemcap" "\0"
"stty" "\0"
"sync" "\0"
"syslogd" "\0"
"tar" "\0"
"taskset" "\0"
"test" "\0"
"tftp" "\0"
"tftpd" "\0"
"top" "\0"
"traceroute" "\0"
"traceroute6" "\0"
"true" "\0"
"tty" "\0"
"umount" "\0"
"uname" "\0"
"vconfig" "\0"
"wget" "\0"
;

#define APPLET_NO_arp 3
#define APPLET_NO_arping 4
#define APPLET_NO_ash 5
#define APPLET_NO_bash 6
#define APPLET_NO_blockdev 7
#define APPLET_NO_cat 8
#define APPLET_NO_chmod 9
#define APPLET_NO_chrt 10
#define APPLET_NO_cp 11
#define APPLET_NO_cut 12
#define APPLET_NO_date 13
#define APPLET_NO_dd 14
#define APPLET_NO_depmod 15
#define APPLET_NO_df 16
#define APPLET_NO_dmesg 17
#define APPLET_NO_du 18
#define APPLET_NO_echo 19
#define APPLET_NO_expr 20
#define APPLET_NO_false 21
#define APPLET_NO_fatattr 22
#define APPLET_NO_free 23
#define APPLET_NO_fstrim 24
#define APPLET_NO_ftpget 25
#define APPLET_NO_grep 26
#define APPLET_NO_gzip 27
#define APPLET_NO_halt 28
#define APPLET_NO_i2cdetect 29
#define APPLET_NO_i2cdump 30
#define APPLET_NO_i2cget 31
#define APPLET_NO_i2cset 32
#define APPLET_NO_ifconfig 33
#define APPLET_NO_init 34
#define APPLET_NO_insmod 35
#define APPLET_NO_kill 36
#define APPLET_NO_killall 37
#define APPLET_NO_klogd 38
#define APPLET_NO_linux32 39
#define APPLET_NO_linux64 40
#define APPLET_NO_ln 41
#define APPLET_NO_logger 42
#define APPLET_NO_logread 43
#define APPLET_NO_ls 44
#define APPLET_NO_md5sum 45
#define APPLET_NO_mdev 46
#define APPLET_NO_mkdir 47
#define APPLET_NO_mknod 48
#define APPLET_NO_modprobe 49
#define APPLET_NO_more 50
#define APPLET_NO_mount 51
#define APPLET_NO_nc 52
#define APPLET_NO_netstat 53
#define APPLET_NO_ntpd 54
#define APPLET_NO_ping 55
#define APPLET_NO_ping6 56
#define APPLET_NO_ps 57
#define APPLET_NO_pwd 58
#define APPLET_NO_pwdx 59
#define APPLET_NO_reboot 60
#define APPLET_NO_rm 62
#define APPLET_NO_rmmod 63
#define APPLET_NO_route 64
#define APPLET_NO_sh 65
#define APPLET_NO_sha256sum 66
#define APPLET_NO_sleep 67
#define APPLET_NO_smemcap 68
#define APPLET_NO_stty 69
#define APPLET_NO_sync 70
#define APPLET_NO_syslogd 71
#define APPLET_NO_tar 72
#define APPLET_NO_taskset 73
#define APPLET_NO_test 74
#define APPLET_NO_tftp 75
#define APPLET_NO_tftpd 76
#define APPLET_NO_top 77
#define APPLET_NO_traceroute 78
#define APPLET_NO_traceroute6 79
#define APPLET_NO_true 80
#define APPLET_NO_tty 81
#define APPLET_NO_umount 82
#define APPLET_NO_uname 83
#define APPLET_NO_vconfig 84
#define APPLET_NO_wget 85

#ifndef SKIP_applet_main
int (*const applet_main[])(int argc, char **argv) = {
test_main,
test_main,
add_remove_shell_main,
arp_main,
arping_main,
ash_main,
ash_main,
blockdev_main,
cat_main,
chmod_main,
chrt_main,
cp_main,
cut_main,
date_main,
dd_main,
depmod_main,
df_main,
dmesg_main,
du_main,
echo_main,
expr_main,
false_main,
fatattr_main,
free_main,
fstrim_main,
ftpgetput_main,
grep_main,
gzip_main,
halt_main,
i2cdetect_main,
i2cdump_main,
i2cget_main,
i2cset_main,
ifconfig_main,
init_main,
insmod_main,
kill_main,
kill_main,
klogd_main,
setarch_main,
setarch_main,
ln_main,
logger_main,
logread_main,
ls_main,
md5_sha1_sum_main,
mdev_main,
mkdir_main,
mknod_main,
modprobe_main,
more_main,
mount_main,
nc_main,
netstat_main,
ntpd_main,
ping_main,
ping6_main,
ps_main,
pwd_main,
pwdx_main,
halt_main,
add_remove_shell_main,
rm_main,
rmmod_main,
route_main,
ash_main,
md5_sha1_sum_main,
sleep_main,
smemcap_main,
stty_main,
sync_main,
syslogd_main,
tar_main,
taskset_main,
test_main,
tftp_main,
tftpd_main,
top_main,
traceroute_main,
traceroute6_main,
true_main,
tty_main,
umount_main,
uname_main,
vconfig_main,
wget_main,
};
#endif

