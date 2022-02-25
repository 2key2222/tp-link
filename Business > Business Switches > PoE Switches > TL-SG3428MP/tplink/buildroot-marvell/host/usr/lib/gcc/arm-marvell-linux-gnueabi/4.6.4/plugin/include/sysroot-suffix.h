#undef SYSROOT_SUFFIX_SPEC
#define SYSROOT_SUFFIX_SPEC "" \
"%{mthumb:" \
  "%{mcpu=marvell-pj4|march=armv7|march=armv7-a|mcpu=marvell-fv7|mcpu=marvell-pj4b|mcpu=marvell-pj4c|mcpu=marvell-whitney|mcpu=generic-armv7-a|mcpu=cortex-a5|mcpu=cortex-a7|mcpu=cortex-a8|mcpu=cortex-a9|mcpu=cortex-a15:/thumb2;" \
  ":};" \
":}"
