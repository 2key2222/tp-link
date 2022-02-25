#!/bin/sh

echo 1 > /proc/irq/24/smp_affinity  #GMAC
echo 3 > /sys/class/net/eth1/queues/rx-0/rps_cpus
echo 3 > /sys/class/net/agl0/queues/rx-0/rps_cpus
