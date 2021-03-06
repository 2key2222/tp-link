#!/bin/sh -euf

prefix=/usr
exec_prefix=/usr
bindir=/usr/bin
libexecpath=/usr/lib/mtd-utils
TESTBINDIR="."

tests="mkvol_basic mkvol_bad mkvol_paral rsvol io_basic io_read io_update io_paral volrefcnt"

fatal()
{
	echo "Error: $1" 1>&2
	echo "FAILURE"
	exit 1
}

usage()
{
	cat 1>&2 <<EOF
Run all UBI tests for on an UBI device.
Usage:
  ${0##*/} <UBI device node>
Example:
  ${0##*/} /dev/ubi1 - test /dev/ubi1.
EOF
}

if [ "$#" -lt 1 ]; then
	usage
	exit 1
fi

ubidev="$1"
[ -c "$ubidev" ] || fatal "$ubidev is not character device"

for t in $tests; do
	echo "Running $t $ubidev"
	"$TESTBINDIR/$t" "$ubidev" || fatal "$t failed"
done

echo "SUCCESS"
