/* This is a generated file, don't edit */

#define NUM_APPLETS 116

const char applet_names[] ALIGN1 = ""
"[" "\0"
"[[" "\0"
"addgroup" "\0"
"adduser" "\0"
"arping" "\0"
"ash" "\0"
"awk" "\0"
"basename" "\0"
"cat" "\0"
"chgrp" "\0"
"chmod" "\0"
"chown" "\0"
"chroot" "\0"
"clear" "\0"
"cmp" "\0"
"cp" "\0"
"crond" "\0"
"crontab" "\0"
"cut" "\0"
"date" "\0"
"dd" "\0"
"delgroup" "\0"
"deluser" "\0"
"dirname" "\0"
"dmesg" "\0"
"echo" "\0"
"egrep" "\0"
"env" "\0"
"expr" "\0"
"false" "\0"
"fgrep" "\0"
"find" "\0"
"free" "\0"
"fsync" "\0"
"grep" "\0"
"gunzip" "\0"
"gzip" "\0"
"halt" "\0"
"head" "\0"
"hexdump" "\0"
"hostid" "\0"
"id" "\0"
"ifconfig" "\0"
"init" "\0"
"insmod" "\0"
"kill" "\0"
"killall" "\0"
"klogd" "\0"
"ln" "\0"
"lock" "\0"
"logger" "\0"
"ls" "\0"
"lsmod" "\0"
"mac_addr" "\0"
"md5sum" "\0"
"mkdir" "\0"
"mkfifo" "\0"
"mknod" "\0"
"mktemp" "\0"
"mount" "\0"
"mv" "\0"
"nice" "\0"
"ntpd" "\0"
"passwd" "\0"
"pgrep" "\0"
"pidof" "\0"
"ping" "\0"
"ping6" "\0"
"pivot_root" "\0"
"poweroff" "\0"
"printf" "\0"
"ps" "\0"
"pwd" "\0"
"readlink" "\0"
"reboot" "\0"
"reset" "\0"
"rm" "\0"
"rmdir" "\0"
"rmmod" "\0"
"route" "\0"
"sed" "\0"
"seq" "\0"
"sh" "\0"
"sleep" "\0"
"sort" "\0"
"start-stop-daemon" "\0"
"strings" "\0"
"switch_root" "\0"
"sync" "\0"
"sysctl" "\0"
"tail" "\0"
"tar" "\0"
"tee" "\0"
"telnet" "\0"
"test" "\0"
"tftp" "\0"
"time" "\0"
"top" "\0"
"touch" "\0"
"tr" "\0"
"traceroute" "\0"
"true" "\0"
"udhcpc" "\0"
"umount" "\0"
"uname" "\0"
"uniq" "\0"
"uptime" "\0"
"vconfig" "\0"
"vi" "\0"
"watchdog" "\0"
"wc" "\0"
"wget" "\0"
"which" "\0"
"xargs" "\0"
"yes" "\0"
"zcat" "\0"
;

#ifndef SKIP_applet_main
int (*const applet_main[])(int argc, char **argv) = {
test_main,
test_main,
addgroup_main,
adduser_main,
arping_main,
ash_main,
awk_main,
basename_main,
cat_main,
chgrp_main,
chmod_main,
chown_main,
chroot_main,
clear_main,
cmp_main,
cp_main,
crond_main,
crontab_main,
cut_main,
date_main,
dd_main,
deluser_main,
deluser_main,
dirname_main,
dmesg_main,
echo_main,
grep_main,
env_main,
expr_main,
false_main,
grep_main,
find_main,
free_main,
fsync_main,
grep_main,
gunzip_main,
gzip_main,
halt_main,
head_main,
hexdump_main,
hostid_main,
id_main,
ifconfig_main,
init_main,
insmod_main,
kill_main,
kill_main,
klogd_main,
ln_main,
lock_main,
logger_main,
ls_main,
lsmod_main,
mac_addr_main,
md5_sha1_sum_main,
mkdir_main,
mkfifo_main,
mknod_main,
mktemp_main,
mount_main,
mv_main,
nice_main,
ntpd_main,
passwd_main,
pgrep_main,
pidof_main,
ping_main,
ping6_main,
pivot_root_main,
halt_main,
printf_main,
ps_main,
pwd_main,
readlink_main,
halt_main,
reset_main,
rm_main,
rmdir_main,
rmmod_main,
route_main,
sed_main,
seq_main,
ash_main,
sleep_main,
sort_main,
start_stop_daemon_main,
strings_main,
switch_root_main,
sync_main,
sysctl_main,
tail_main,
tar_main,
tee_main,
telnet_main,
test_main,
tftp_main,
time_main,
top_main,
touch_main,
tr_main,
traceroute_main,
true_main,
udhcpc_main,
umount_main,
uname_main,
uniq_main,
uptime_main,
vconfig_main,
vi_main,
watchdog_main,
wc_main,
wget_main,
which_main,
xargs_main,
yes_main,
gunzip_main,
};
#endif

const uint16_t applet_nameofs[] ALIGN2 = {
0x3000,
0x3002,
0x0005,
0x000e,
0x0016,
0x001d,
0x2021,
0x3025,
0x302e,
0x2032,
0x2038,
0x203e,
0x0044,
0x004b,
0x0051,
0x2055,
0x0058,
0x805e,
0x2066,
0x006a,
0x206f,
0x0072,
0x007b,
0x3083,
0x008b,
0x3091,
0x0096,
0x209c,
0x00a0,
0x30a5,
0x00ab,
0x20b1,
0x00b6,
0x30bb,
0x00c1,
0x00c6,
0x00cd,
0x00d2,
0x20d7,
0x20dc,
0x30e4,
0x20eb,
0x00ee,
0x00f7,
0x00fc,
0x0103,
0x0108,
0x0110,
0x2116,
0x0119,
0x011e,
0x2125,
0x0128,
0x012e,
0x2137,
0x313e,
0x2144,
0x214b,
0x0151,
0x0158,
0x015e,
0x0161,
0x0166,
0x816b,
0x0172,
0x0178,
0x417e,
0x4183,
0x0189,
0x0194,
0x319d,
0x01a4,
0x31a7,
0x01ab,
0x01b4,
0x01bb,
0x31c1,
0x31c4,
0x01ca,
0x01d0,
0x01d6,
0x31da,
0x01de,
0x01e1,
0x21e7,
0x01ec,
0x01fe,
0x0206,
0x3212,
0x0217,
0x021e,
0x0223,
0x0227,
0x022b,
0x3232,
0x0237,
0x023c,
0x0241,
0x3245,
0x024b,
0x424e,
0x3259,
0x025e,
0x0265,
0x026c,
0x0272,
0x0277,
0x027e,
0x0286,
0x0289,
0x0292,
0x0295,
0x029a,
0x22a0,
0x32a6,
0x02aa,
};


#define MAX_APPLET_NAME_LEN 17
