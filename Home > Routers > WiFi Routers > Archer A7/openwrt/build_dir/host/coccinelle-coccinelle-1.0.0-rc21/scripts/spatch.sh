#! /bin/sh -e

# generic wrapper script to invoke 'spatch' or 'spatch.opt'
# it sets the python variables (if relevant)
# and COCCINELLE_HOME

SHAREDIR="/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/host/share/coccinelle"
LIBDIR="/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/host/lib"

if test ! -d "$SHAREDIR"; then
    SHAREDIR="$(pwd)"
fi

COCCINELLE_HOME="${COCCINELLE_HOME:=$SHAREDIR}"
#echo setting COCCINELLE_HOME=${COCCINELLE_HOME:=$SHAREDIR}

if [ ! -d "${COCCINELLE_HOME}" ]; then
  echo "\$COCCINELLE_HOME is not a directory: ${COCCINELLE_HOME}" 1>&2
fi

if [ ! -r "${COCCINELLE_HOME}/standard.iso" ] ; then
  echo "There is no standard.iso in ${COCCINELLE_HOME}." 1>&2
  echo -n "Are you sure you run a properly installed version of spatch ?\n" 1>&2
else

export COCCINELLE_HOME

export LD_LIBRARY_PATH="${LIBDIR}:$LD_LIBRARY_PATH:${SHAREDIR}:${COCCINELLE_HOME}"
export PYTHONPATH="${COCCINELLE_HOME}/python:$PYTHONPATH"

# echo setting LD_LIBRARY_PATH="$LD_LIBRARY_PATH"
# echo setting PYTHONPATH="$PYTHONPATH"

fi

extension="${0##*.}"
if [ "x$extension" = "xopt" ]; then
  TOOL="spatch.opt"
elif [ "x$extension" = "xbyte" ]; then
  TOOL="spatch"
else
  # autodetect
  if [ -f "${COCCINELLE_HOME}/spatch.opt" ]; then
    TOOL="spatch.opt"
  elif [ -f "${COCCINELLE_HOME}/spatch" ]; then
    TOOL="spatch"
  else
    echo "No 'spatch' nor 'spatch.opt' found in ${COCCINELLE_HOME}" 1>&2
    exit 1
  fi
fi

exec "${COCCINELLE_HOME}/${TOOL}" "$@"
