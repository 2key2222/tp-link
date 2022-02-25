#
# Copyright (C) 2010 OpenWrt.org
#

. /lib/ramips.sh

PART_NAME=firmware
RAMFS_COPY_DATA=/lib/ramips.sh

CI_BLKSZ=65536
CI_LDADR=0x80060000

platform_find_partitions() {
	local first dev size erasesize name
	while read dev size erasesize name; do
		name=${name#'"'}; name=${name%'"'}
		case "$name" in
			vmlinux.bin.l7|vmlinux|kernel|linux|linux.bin|rootfs|filesystem)
				if [ -z "$first" ]; then
					first="$name"
				else
					echo "$erasesize:$first:$name"
					break
				fi
			;;
		esac
	done < /proc/mtd
}

platform_find_kernelpart() {
	local part
	for part in "${1%:*}" "${1#*:}"; do
		case "$part" in
			vmlinux.bin.l7|vmlinux|kernel|linux|linux.bin)
				echo "$part"
				break
			;;
		esac
	done
}

platform_do_upgrade_combined() {
	local partitions=$(platform_find_partitions)
	local kernelpart=$(platform_find_kernelpart "${partitions#*:}")
	local erase_size=$((0x${partitions%%:*})); partitions="${partitions#*:}"
	local kern_length=0x$(dd if="$1" bs=2 skip=1 count=4 2>/dev/null)
	local kern_blocks=$(($kern_length / $CI_BLKSZ))
	local root_blocks=$((0x$(dd if="$1" bs=2 skip=5 count=4 2>/dev/null) / $CI_BLKSZ))

	if [ -n "$partitions" ] && [ -n "$kernelpart" ] && \
	   [ ${kern_blocks:-0} -gt 0 ] && \
	   [ ${root_blocks:-0} -gt ${kern_blocks:-0} ] && \
	   [ ${erase_size:-0} -gt 0 ];
	then
		local append=""
		[ -f "$CONF_TAR" -a "$SAVE_CONFIG" -eq 1 ] && append="-j $CONF_TAR"

		( dd if="$1" bs=$CI_BLKSZ skip=1 count=$kern_blocks 2>/dev/null; \
		  dd if="$1" bs=$CI_BLKSZ skip=$((1+$kern_blocks)) count=$root_blocks 2>/dev/null ) | \
			mtd -r $append -F$kernelpart:$kern_length:$CI_LDADR,rootfs write - $partitions
	fi
}

tplink_get_image_hwid() {
	get_image "$@" | dd bs=4 count=1 skip=16 2>/dev/null | hexdump -v -n 4 -e '1/1 "%02x"'
}

tplink_get_image_boot_size() {
	get_image "$@" | dd bs=4 count=1 skip=37 2>/dev/null | hexdump -v -n 4 -e '1/1 "%02x"'
}

platform_check_image() {
	local board=$(ramips_board_name)
	local magic="$(get_magic_word "$1")"
	local magic_long="$(get_magic_long "$1")"

	[ "$ARGC" -gt 1 ] && return 1

	case "$board" in
	3g-6200n | \
	3g-6200nl | \
	3g300m | \
	w150m | \
	air3gii | \
	all0239-3g | \
	all0256n | \
	all5002 | \
	all5003 | \
	ar725w | \
	asl26555 | \
	awm002-evb | \
	awm003-evb | \
	awapn2403 | \
	bc2 | \
	broadway | \
	carambola | \
	d105 | \
	dcs-930 | \
	dir-300-b1 | \
	dir-300-b7 | \
	dir-320-b1 | \
	dir-600-b1 | \
	dir-600-b2 | \
	dir-615-h1 | \
	dir-615-d | \
	dir-620-a1 | \
	dir-620-d1 | \
	dir-810l | \
	dap-1350 | \
	esr-9753 | \
	f7c027 | \
	fonera20n | \
	rt-n13u | \
	freestation5 | \
	hw550-3g | \
	hg255d | \
	hlk-rm04 | \
	ip2202 | \
	m3 | \
	m4 | \
	mlw221 | \
	mofi3500-3gn | \
	mpr-a1 | \
	mpr-a2 | \
	mzk-w300nh2 | \
	nbg-419n | \
	nw718 | \
	omni-emb | \
	omni-emb-hpm | \
	psr-680w | \
	px4885 | \
	rp-n53 | \
	rt-g32-b1 | \
	rt-n10-plus | \
	rt-n14u | \
	rt-n15 | \
	rt-n56u | \
	rut5xx | \
	sl-r7205 | \
	tew-691gr | \
	tew-692gr | \
	w306r-v20 |\
	w502u |\
	wr6202 |\
	v22rw-2x2 | \
	wl341v3 | \
	wl-330n | \
	wl-330n3g | \
	wl-351 | \
	wnce2001 | \
	wli-tx4-ag300n | \
	whr-g300n |\
	ur-326n4g |\
	ur-336un |\
	wr512-3gn |\
	wmr300 |\
	wr8305rt |\
	wrtnode |\
	x5 |\
	x8 |\
	zbt-wa05 |\
	y1 |\
	y1s)
		[ "$magic" != "27051956" ] && {
			echo "Invalid image type."
			return 1
		}
		return 0
		;;
	cy-swr1100 |\
	dir-610-a1 |\
	dir-645)
		[ "$magic" != "5ea3a417" ] && {
			echo "Invalid image type."
			return 1
		}
		return 0
		;;
	br-6475nd)
		[ "$magic" != "43535953" ] && {
			echo "Invalid image type."
			return 1
		}
		return 0
		;;
	esac

	echo "Sysupgrade is not yet supported on $board."
	return 1
}

platform_do_upgrade() {
	local board=$(ramips_board_name)

	case "$board" in
	routerstation | \
	routerstation-pro | \
	ls-sr71 | \
	all0305 | \
	eap7660d | \
	pb42 | \
	pb44 | \
	ja76pf | \
	ja76pf2 | \
	jwap003)
		platform_do_upgrade_combined "$ARGV"
		;;
	all0258n )
		platform_do_upgrade_allnet "0x9f050000" "$ARGV"
		;;
	all0315n )
		platform_do_upgrade_allnet "0x9f080000" "$ARGV"
		;;
	cap4200ag)
		platform_do_upgrade_allnet "0xbf0a0000" "$ARGV"
		;;
	dir-825-b1 |\
	tew-673gru)
		platform_do_upgrade_dir825b "$ARGV"
		;;
	mr600 | \
	om2p | \
	om2p-hs | \
	om2p-lc)
		platform_do_upgrade_openmesh "$ARGV"
		;;
	cus227)
		platform_do_upgrade_cus227 "$ARGV"
		;;
	ap147 |\
	ap151 |\
	ap152 |\
	ap135 |\
	ap135-dual |\
	ap135-nand)
		platform_do_upgrade_ap135 "$ARGV"
		;;
	*)
		default_do_upgrade "$ARGV"
		;;
	esac
}

disable_watchdog() {
	killall watchdog
	( ps | grep -v 'grep' | grep '/dev/watchdog' ) && {
		echo 'Could not disable watchdog'
		return 1
	}
}

append sysupgrade_pre_upgrade disable_watchdog
