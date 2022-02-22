#!/bin/sh
if test -e /proc/version
then
 echo
else

 hostname MARVELL_LINUX
 HOME=/root

 test -d /dev/shm || mkdir /dev/shm
 test -d /dev/pts || mkdir /dev/pts

 mount -t proc   proc /proc
 mount -t sysfs  none /sys
 mount -t tmpfs  -n -o size=128M none /dev/shm
 mount -t devpts -o mode=0622    none /dev/pts

 /usr/sbin/telnetd -l /bin/sh -f /etc/welcome

 kernel_ver=`uname -r`
 #create modules.dep file to make modinfo command run
 mkdir -p /lib/modules/
 touch /lib/modules//modules.dep
 for module_f in /lib/modules/${kernel_ver%%-*}/*.ko /lib/modules/*.ko
 do
   if [ -e $module_f ]
   then
     insmod $module_f
   fi
 done


date 092317232021

 # Start the network interface
 /sbin/ifconfig lo 127.0.0.1

 rm -f /tmp/tasks

fi

export LD_PRELOAD=/lib/libSegFault.so

# print logo
# clear
echo
echo
echo
echo
uname -nrsv
cat /etc/motd

if test -e /usr/bin/appDemo
then
  if test -e /usr/local/auto_run.txt
  then
   echo PTK nfs, not running appDemo
  else
    /usr/bin/appDemo
  fi
else
  echo /usr/bin/appDemo not found
fi

exec /bin/sh
