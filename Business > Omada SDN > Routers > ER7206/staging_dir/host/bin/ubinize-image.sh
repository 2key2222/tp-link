#!/bin/sh

echo "$0 $@"

part=""
ubootenv=""
ubinize_param=""
kernel=""
rootfs=""
outfile=""
err=""

get_magic_word() {
	dd if=$1 bs=2 count=1 2>/dev/null | hexdump -v -n 2 -e '1/1 "%02x"'
}

is_ubifs() {
	if [ "$( get_magic_word $1 )" = "3118" ]; then
		echo "1"
	fi
}

ubivol() {
	volid=$1
	name=$2
	image=$3
	autoresize=$4
	vtype=$5
	size="$6"
	echo "[$name]"
	echo "mode=ubi"
	echo "vol_id=$volid"
	echo "vol_type=${vtype:-dynamic}"
	echo "vol_name=$name"
	if [ "$image" ]; then
		echo "image=$image"
		[ -n "$size" ] && echo "vol_size=${size}"
	else
		if [ -n "$size" ]; then
			echo "vol_size=${size}"
		else
			echo "vol_size=1MiB"
		fi
	fi
	if [ "$autoresize" ]; then
		echo "vol_flags=autoresize"
	fi
}

ubilayout() {
	local vol_id=0
	if [ "$1" = "ubootenv" ]; then
		ubivol $vol_id ubootenv
		vol_id=$(( $vol_id + 1 ))
		ubivol $vol_id ubootenv2
		vol_id=$(( $vol_id + 1 ))
	fi
	for part in $parts; do
		name="${part%%=*}"
		prev="$part"
		part="${part#*=}"
		[ "$prev" = "$part" ] && part=

		image="${part%%=*}"
		prev="$part"
		part="${part#*=}"
		[ "$prev" = "$part" ] && part=

		size="${part%%=*}"
		prev="$part"
		part="${part#*=}"
		[ "$prev" = "$part" ] && part=

		vtype="$part"

		ubivol $vol_id "$name" "$image" "" "$vtype" "$size"
		vol_id=$(( $vol_id + 1 ))
	done
}

while [ "$1" ]; do
	case "$1" in
	"--part")
		parts="$parts $2"
		shift
		shift
		continue
		;;
	"-"*)
		ubinize_param="$@"
		break
		;;
	*)
		if [ ! "$outfile" ]; then
			outfile=$1
			shift
			continue
		fi
		;;
	esac
done

if [ ! "$outfile" ]; then
	echo "syntax: $0 [--part <name>=<file>[=size]] out [ubinize opts]"
	exit 1
fi

ubinize="$( which ubinize )"
if [ ! -x "$ubinize" ]; then
	echo "ubinize tool not found or not usable"
	exit 1
fi

ubinizecfg="$( mktemp 2> /dev/null )"
if [ -z "$ubinizecfg" ]; then
	# try OSX signature
	ubinizecfg="$( mktemp -t 'ubitmp' )"
fi
ubilayout > "$ubinizecfg"

cat "$ubinizecfg"
ubinize -o "$outfile" $ubinize_param "$ubinizecfg"
err="$?"
[ ! -e "$outfile" ] && err=2
rm "$ubinizecfg"

exit $err
