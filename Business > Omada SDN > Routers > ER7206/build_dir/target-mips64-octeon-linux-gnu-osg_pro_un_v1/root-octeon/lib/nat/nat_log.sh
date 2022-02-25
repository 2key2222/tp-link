#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     nat_log.sh
# brief
# author   Chen chen
# version  1.1.0
# date     20Apr15
# history  arg 1.0.0, 20Apr15, Chen chen, Create the file.
#          arg 1.1.0, 21Dec17, Zhangzhongwei, Rewrite the file.


NAT_DEBUG=0
NAT_LOG_ENABLE=0

NAT_LIBDIR=${NAT_LIBDIR:-/lib/nat}
NAT_TMP_DIR="/tmp/.nat"
NAT_LOG_FILE="$NAT_TMP_DIR/nat.log"
NAT_LOG_DIR="$NAT_TMP_DIR/log"

nat_log_init()
{
	if [[ "$NAT_LOG_ENABLE" -eq 1 ]]; then
		# rm -rf $NAT_LOG_FILE
		mkdir -p $NAT_TMP_DIR

		if [[ "`ls -l $NAT_LOG_FILE | awk '{print $5}'`" -gt 50000 ]]; then
			rm -rf $NAT_LOG_FILE
		fi

		if [[ ! -d "$NAT_TMP_DIR" ]]; then
			mkdir $NAT_TMP_DIR
			mkdir -p $NAT_LOG_DIR
		fi

		if [[ ! -f "$NAT_LOG_FILE" ]]; then
			echo -e "time\t\t\tlog_info" > "$NAT_LOG_FILE"
			echo -e " create nat.log file"
		fi

		if [[ ! -f "${NAT_LIBDIR}/log" ]]; then
			ln -sf $NAT_LOG_FILE ${NAT_LIBDIR}/log
		fi
	else
		rm -rf $NAT_LOG_FILE
	fi
}

NAT_PRINT()
{
	if [[ "$NAT_DEBUG" -eq 1 ]]; then
		echo -e "NAT DBG: $1"
	fi
}

NAT_WRITE_FILE()
{
	if [[ "$NAT_DEBUG" -eq 1 ]]; then
		echo -e "$1" >> "$2"
	fi
}

NAT_WRITE_LOG()
{
	if [[ "$NAT_LOG_ENABLE" -eq 1 ]]; then

		local log="$1"
		local file=$NAT_LOG_FILE
		local time=`date +%Y%m%d-%H.%M.%S`
		local item="${time}    ${log}"

		# if log size > 150K, save and recreate
		if [[ `ls -l "$file" | awk '{print $5}'` -gt 100000 ]]; then
			# keep count of logfile below 10
			if [[ `ls $NAT_LOG_DIR | wc -l` -ge 10 ]]; then
				rm $NAT_LOG_DIR`ls $NAT_LOG_DIR | awk 'NR==1 {print $1}'`
			fi
			mv "$file" "${NAT_LOG_DIR}/${time}_nat.log"
			NAT_WRITE_FILE "time\t\t\tlog_info" "$file"
		fi

		echo -e "$item" >> "$file"
	fi
}

NAT_LOG_PRINT()
{
	NAT_WRITE_LOG "$1"
	NAT_PRINT "$1"
}

nat_log_init