#!/bin/sh

time=$(date "+%Y-%m-%d %H:%M:%S %A")
runtime=$(cat /proc/uptime| awk -F. '{run_days=$1 / 86400;run_hour=($1 % 86400)/3600;run_minute=($1 % 3600)/60;run_second=$1 % 60;printf("%d %d %d %d",run_days,run_hour,run_minute,run_second)}')
echo "$time#$runtime"