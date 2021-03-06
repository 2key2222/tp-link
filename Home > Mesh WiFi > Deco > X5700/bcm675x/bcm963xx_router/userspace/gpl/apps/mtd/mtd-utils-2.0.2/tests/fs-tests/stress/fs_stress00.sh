#!/bin/sh

prefix=/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/userspace/gpl/apps/mtd/mtd-utils-2.0.2/opt
exec_prefix=${prefix}
bindir=${exec_prefix}/bin
libexecpath=${exec_prefix}/libexec/mtd-utils
TESTBINDIR="."

TEST_DIR=$TEST_FILE_SYSTEM_MOUNT_DIR
if test -z "$TEST_DIR";
then
	TEST_DIR="/mnt/test_file_system"
fi

FREESPACE=`$TESTBINDIR/free_space "$TEST_DIR"`

if test -z "$FREESPACE";
then
	echo "Failed to determine free space"
	exit 1
fi

if test -n "$1";
then
	DURATION="-d$1";
else
	DURATION="";
fi

FWRITE00=$TESTBINDIR/fwrite00
RNDWR=$TESTBINDIR/rndwrite00
GCHUP=$TESTBINDIR/gcd_hupper
PDFLUSH=$TESTBINDIR/pdfrun
FSIZE=$(( $FREESPACE/15 ));

$TESTBINDIR/fstest_monitor $DURATION \
"$FWRITE00 -z $FSIZE -n0 -p 20" \
"$FWRITE00 -z $FSIZE -n0 -p 10 -s" \
"$FWRITE00 -z $FSIZE -n0 -p 20 -u" \
"$FWRITE00 -z $FSIZE -n0 -p 70 -o" \
"$FWRITE00 -z $FSIZE -n0 -p 15 -s -o -u" \
"$FWRITE00 -z $FSIZE -n0 -p 10 -u -c" \
"$FWRITE00 -z $FSIZE -n0 -p 10 -u -o -c" \
"$FWRITE00 -z $FSIZE -n0 -p 10 -o -c" \
"$FWRITE00 -z $FSIZE -n0 -p 100 -o -u" \
"$FWRITE00 -z $FSIZE -n0 -p 100 -s -o -u -c" \
"$FWRITE00 -z $FSIZE -n0 -p 100 -o -u" \
"$FWRITE00 -z $FSIZE -n0 -p 100 -u" \
"$FWRITE00 -z $FSIZE -n0 -p 100 -s -o" \
"$RNDWR -z $FSIZE -n0 -p 10 -e" \
"$RNDWR -z $FSIZE -n0 -p 100 -e" \
"$PDFLUSH -z 1073741824 -n0"

STATUS=$?

rm -rf ${TEST_DIR}/*

exit $STATUS
