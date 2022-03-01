#!/bin/sh
# Copyright (C) 2006-2013 OpenWrt.org
# Copyright (C) 2010 Vertical Communications

boot_hook_splice_start() {
	export -n PI_HOOK_SPLICE=1
}

boot_hook_splice_finish() {
	local hook
	for hook in $PI_STACK_LIST; do
		local v; eval "v=\${${hook}_splice:+\$${hook}_splice }$hook"
		export -n "${hook}=${v% }"
		export -n "${hook}_splice="
	done
	export -n PI_HOOK_SPLICE=
}

boot_hook_init() {
	local hook="${1}_hook"
	export -n "PI_STACK_LIST=${PI_STACK_LIST:+$PI_STACK_LIST }$hook"
	export -n "$hook="
}

boot_hook_add() {
	local hook="${1}_hook${PI_HOOK_SPLICE:+_splice}"
	local func="${2}"

	[ -n "$func" ] && {
		local v; eval "v=\$$hook"
		export -n "$hook=${v:+$v }$func"
	}
}

boot_hook_shift() {
	local hook="${1}_hook"
	local rvar="${2}"

	local v; eval "v=\$$hook"
	[ -n "$v" ] && {
		local first="${v%% *}"

		[ "$v" != "${v#* }" ] && \
			export -n "$hook=${v#* }" || \
			export -n "$hook="

		export -n "$rvar=$first"
		return 0
	}

	return 1
}

boot_run_hook() {
	local hook="$1"
	local func

	while boot_hook_shift "$hook" func; do
		local ran; eval "ran=\$PI_RAN_$func"
		[ -n "$ran" ] || {
			export -n "PI_RAN_$func=1"
			$func "$1" "$2"
		}
	done
}

pivot() { # <new_root> <old_root>
	/bin/mount -o noatime,move /proc $1/proc && \
	pivot_root $1 $1$2 && {
		/bin/mount -o noatime,move $2/dev /dev
		/bin/mount -o noatime,move $2/tmp /tmp
		/bin/mount -o noatime,move $2/sys /sys 2>&-
		/bin/mount -o noatime,move $2/overlay /overlay 2>&-
		return 0
	}
}

#fopivot() { # <rw_root> <work_root> <ro_root> <dupe?>
#	/bin/mount -o noatime,lowerdir=/,upperdir=$1,workdir=$2 -t overlay "overlayfs:$1" /mnt
#	pivot /mnt $3
#}
fopivot() { # <rw_root> <ro_root> <dupe?>
	if [ -e /proc/cmdline ]; then
		kernel_major_version=$(uname -r|awk -F. '{print $1}')
		if [ "$kernel_major_version" = "4" ]; then
			mkdir -p $1/root $1/work
			mount | grep -q "/sp_rom" \
			&& /bin/mount -o noatime,lowerdir=/sp_rom:/,upperdir=$1/root,workdir=$1/work -t overlay "overlayfs:$1" /mnt \
			|| /bin/mount -o noatime,lowerdir=/,upperdir=$1/root,workdir=$1/work -t overlay "overlayfs:$1" /mnt
		else
			mount | grep -q "/sp_rom" && {
				/bin/mount -o noatime,lowerdir=/,upperdir=/sp_rom -t overlayfs "overlayfs:$1" /mnt
				/bin/mount -o noatime,lowerdir=/mnt,upperdir=$1 -t overlayfs "overlayfs:$1" /mnt
			} || /bin/mount -o noatime,lowerdir=/,upperdir=$1 -t overlayfs "overlayfs:$1" /mnt
		fi
	fi
	
	pivot /mnt $2 && {
		[ -e /proc/cmdline ] && {
			rwdev=$(awk 'BEGIN { RS=" "; FS="="; } $1 == "rwdev" { print $2 }' < /proc/cmdline)
			if [ "$rwdev" != "" ]; then
				[ -e /etc/rwdir ] || mkdir -p /etc/rwdir
				/bin/mount -t jffs2 -o rw,noatime $rwdev /etc/rwdir && {
					rm -rf /etc/config && ln -sf /etc/rwdir/config /etc/config
					[ -e /etc/rwdir/log ] || mkdir -p /etc/rwdir/log
					rm -rf /usr/log && ln -sf /etc/rwdir/log /usr/log
				}
			fi
		}
	}
}

#ramoverlay() {
#	mkdir -p /tmp/root
#	/bin/mount -t tmpfs -o noatime,mode=0755 root /tmp/root
#	mkdir -p /tmp/root/root /tmp/root/work
#	fopivot /tmp/root/root /tmp/root/work /rom 1
#}
ramoverlay() {
	mkdir -p /overlay
	mount -t tmpfs -o mode=0755 root /overlay
	if [ -e /proc/cmdline ]; then
		spdev=$(awk 'BEGIN { RS=" "; FS="="; } $1 == "spdev" { print $2 }' < /proc/cmdline)
		if [ "$spdev" != "" ]; then
			/bin/mount -t squashfs -o relatime $spdev /sp_rom
			mount | grep -q $spdev || /bin/mount -t jffs2 -o relatime $spdev /sp_rom
		fi
	fi
	
	fopivot /overlay /rom 1
}
