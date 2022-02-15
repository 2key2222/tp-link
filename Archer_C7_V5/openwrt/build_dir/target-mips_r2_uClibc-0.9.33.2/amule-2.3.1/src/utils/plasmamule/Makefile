MAKEFLAGS=-s --no-print-directory
pkgdatadir = $(datadir)/amule
pkgincludedir = $(includedir)/amule
pkglibdir = $(libdir)/amule
pkglibexecdir = $(libexecdir)/amule
am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
install_sh_SCRIPT = $(install_sh) -c
INSTALL_HEADER = $(INSTALL_DATA)
transform = $(program_transform_name)
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_triplet = i686-pc-linux-gnu
host_triplet = mips-openwrt-linux-gnu
subdir = src/utils/plasmamule
DIST_COMMON = $(am__dist_apps_DATA_DIST) $(am__dist_icon_DATA_DIST) \
	$(am__dist_mime_DATA_DIST) $(am__dist_service_DATA_DIST) \
	$(noinst_HEADERS) $(srcdir)/Makefile.am $(srcdir)/Makefile.in
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
am__aclocal_m4_deps = $(top_srcdir)/m4/GeoIP.m4 \
	$(top_srcdir)/m4/build-tools.m4 $(top_srcdir)/m4/codeset.m4 \
	$(top_srcdir)/m4/cryptopp.m4 $(top_srcdir)/m4/fallocate.m4 \
	$(top_srcdir)/m4/gdlib.m4 $(top_srcdir)/m4/gettext.m4 \
	$(top_srcdir)/m4/glibc21.m4 $(top_srcdir)/m4/iconv.m4 \
	$(top_srcdir)/m4/intdiv0.m4 $(top_srcdir)/m4/inttypes-pri.m4 \
	$(top_srcdir)/m4/inttypes.m4 $(top_srcdir)/m4/inttypes_h.m4 \
	$(top_srcdir)/m4/isc-posix.m4 $(top_srcdir)/m4/kde.m4 \
	$(top_srcdir)/m4/lcmessage.m4 $(top_srcdir)/m4/lib-ld.m4 \
	$(top_srcdir)/m4/lib-link.m4 $(top_srcdir)/m4/lib-prefix.m4 \
	$(top_srcdir)/m4/libpng.m4 $(top_srcdir)/m4/libupnp.m4 \
	$(top_srcdir)/m4/nls.m4 $(top_srcdir)/m4/pkg.m4 \
	$(top_srcdir)/m4/plasmamule.m4 $(top_srcdir)/m4/progtest.m4 \
	$(top_srcdir)/m4/qt.m4 $(top_srcdir)/m4/readline.m4 \
	$(top_srcdir)/m4/stdint_h.m4 $(top_srcdir)/m4/uintmax_t.m4 \
	$(top_srcdir)/m4/ulonglong.m4 $(top_srcdir)/m4/wxwin.m4 \
	$(top_srcdir)/m4/zlib.m4 $(top_srcdir)/acinclude.m4 \
	$(top_srcdir)/configure.in
am__configure_deps = $(am__aclocal_m4_deps) $(CONFIGURE_DEPENDENCIES) \
	$(ACLOCAL_M4)
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = $(top_builddir)/config.h
CONFIG_CLEAN_FILES =
CONFIG_CLEAN_VPATH_FILES =
am__installdirs = "$(DESTDIR)$(bindir)" "$(DESTDIR)$(modulesdir)" \
	"$(DESTDIR)$(appsdir)" "$(DESTDIR)$(icondir)" \
	"$(DESTDIR)$(mimedir)" "$(DESTDIR)$(servicedir)"
PROGRAMS = $(bin_PROGRAMS) $(modules_PROGRAMS)
am_plasma_applet_plasmamule_so_OBJECTS = plasma_applet_plasmamule_so-plasma-applet-plasmamule.$(OBJEXT) \
	plasma_applet_plasmamule_so-plasmamule-dbus.$(OBJEXT)
nodist_plasma_applet_plasmamule_so_OBJECTS =
plasma_applet_plasmamule_so_OBJECTS =  \
	$(am_plasma_applet_plasmamule_so_OBJECTS) \
	$(nodist_plasma_applet_plasmamule_so_OBJECTS)
plasma_applet_plasmamule_so_LDADD = $(LDADD)
plasma_applet_plasmamule_so_LINK = $(CXXLD) \
	$(plasma_applet_plasmamule_so_CXXFLAGS) $(CXXFLAGS) \
	$(AM_LDFLAGS) $(LDFLAGS) -o $@
am_plasma_engine_plasmamule_so_OBJECTS = plasma_engine_plasmamule_so-plasma-engine-plasmamule.$(OBJEXT) \
	plasma_engine_plasmamule_so-qt-emc.$(OBJEXT)
nodist_plasma_engine_plasmamule_so_OBJECTS =
plasma_engine_plasmamule_so_OBJECTS =  \
	$(am_plasma_engine_plasmamule_so_OBJECTS) \
	$(nodist_plasma_engine_plasmamule_so_OBJECTS)
plasma_engine_plasmamule_so_LDADD = $(LDADD)
plasma_engine_plasmamule_so_LINK = $(CXXLD) \
	$(plasma_engine_plasmamule_so_CXXFLAGS) $(CXXFLAGS) \
	$(AM_LDFLAGS) $(LDFLAGS) -o $@
am_plasmamule_engine_feeder_OBJECTS =  \
	plasmamule_engine_feeder-plasmamule-engine-feeder.$(OBJEXT) \
	plasmamule_engine_feeder-plasmamule-dbus.$(OBJEXT)
plasmamule_engine_feeder_OBJECTS =  \
	$(am_plasmamule_engine_feeder_OBJECTS)
plasmamule_engine_feeder_LDADD = $(LDADD)
plasmamule_engine_feeder_LINK = $(CXXLD) \
	$(plasmamule_engine_feeder_CXXFLAGS) $(CXXFLAGS) \
	$(plasmamule_engine_feeder_LDFLAGS) $(LDFLAGS) -o $@
DEFAULT_INCLUDES = -I. -I$(top_builddir)
depcomp = $(SHELL) $(top_srcdir)/depcomp
am__depfiles_maybe = depfiles
am__mv = mv -f
CXXCOMPILE = $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
	$(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)
CXXLD = $(CXX)
CXXLINK = $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) \
	-o $@
SOURCES = $(plasma_applet_plasmamule_so_SOURCES) \
	$(nodist_plasma_applet_plasmamule_so_SOURCES) \
	$(plasma_engine_plasmamule_so_SOURCES) \
	$(nodist_plasma_engine_plasmamule_so_SOURCES) \
	$(plasmamule_engine_feeder_SOURCES)
DIST_SOURCES = $(plasma_applet_plasmamule_so_SOURCES) \
	$(plasma_engine_plasmamule_so_SOURCES) \
	$(plasmamule_engine_feeder_SOURCES)
am__dist_apps_DATA_DIST = plasmamule-engine-feeder.desktop
am__vpath_adj_setup = srcdirstrip=`echo "$(srcdir)" | sed 's|.|.|g'`;
am__vpath_adj = case $$p in \
    $(srcdir)/*) f=`echo "$$p" | sed "s|^$$srcdirstrip/||"`;; \
    *) f=$$p;; \
  esac;
am__strip_dir = f=`echo $$p | sed -e 's|^.*/||'`;
am__install_max = 40
am__nobase_strip_setup = \
  srcdirstrip=`echo "$(srcdir)" | sed 's/[].[^$$\\*|]/\\\\&/g'`
am__nobase_strip = \
  for p in $$list; do echo "$$p"; done | sed -e "s|$$srcdirstrip/||"
am__nobase_list = $(am__nobase_strip_setup); \
  for p in $$list; do echo "$$p $$p"; done | \
  sed "s| $$srcdirstrip/| |;"' / .*\//!s/ .*/ ./; s,\( .*\)/[^/]*$$,\1,' | \
  $(AWK) 'BEGIN { files["."] = "" } { files[$$2] = files[$$2] " " $$1; \
    if (++n[$$2] == $(am__install_max)) \
      { print $$2, files[$$2]; n[$$2] = 0; files[$$2] = "" } } \
    END { for (dir in files) print dir, files[dir] }'
am__base_list = \
  sed '$$!N;$$!N;$$!N;$$!N;$$!N;$$!N;$$!N;s/\n/ /g' | \
  sed '$$!N;$$!N;$$!N;$$!N;s/\n/ /g'
am__dist_icon_DATA_DIST = application-x-emulecollection.svg
am__dist_mime_DATA_DIST = amule.xml
am__dist_service_DATA_DIST = plasma-engine-plasmamule.desktop \
	plasma-applet-plasmamule.desktop ed2k.protocol magnet.protocol
DATA = $(dist_apps_DATA) $(dist_icon_DATA) $(dist_mime_DATA) \
	$(dist_service_DATA)
HEADERS = $(noinst_HEADERS)
ETAGS = etags
CTAGS = ctags
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)
ACLOCAL = ${SHELL} /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/amule-2.3.1/missing --run aclocal-1.11
ALCC_MANPAGES = 
ALC_MANPAGES = 
ALLOCA = 
AMTAR = ${SHELL} /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/amule-2.3.1/missing --run tar
AMULECMD_MANPAGES = 
AMULEWEB_DEFS = 
AMULE_DAEMON_MANPAGES = 
AMULE_GUI_MANPAGES = 
AR = mips-openwrt-linux-uclibc-ar
AUTOCONF = ${SHELL} /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/amule-2.3.1/missing --run autoconf
AUTOHEADER = ${SHELL} /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/amule-2.3.1/missing --run autoheader
AUTOMAKE = ${SHELL} /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/amule-2.3.1/missing --run automake-1.11
AWK = mawk
BFD_CPPFLAGS = 
BFD_LIBS = 
BUILD_CC = i686-linux-gnu-gcc
BUILD_CFLAGS = 
BUILD_CPPFLAGS = 
BUILD_EXEEXT = 
BUILD_INCLUDED_LIBINTL = no
BUILD_LDFLAGS = 
CAS_DEFS = 
CAS_MANPAGES = 
CATOBJEXT = 
CC = mips-openwrt-linux-uclibc-gcc
CCDEPMODE = depmode=gcc3
CFLAGS = -Os -pipe -mips32r2 -mtune=74kc -fno-caller-saves -freorder-blocks -fhonour-copts -Wno-error=unused-but-set-variable -msoft-float -std=gnu99 -DENABLE_UBUS_RPC 
CPP = mips-openwrt-linux-uclibc-gcc -E
CPPFLAGS = -I/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/target-mips_r2_uClibc-0.9.33.2/usr/include -I/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/target-mips_r2_uClibc-0.9.33.2/include -I/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/usr/include -I/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/include 
CRYPTOPP_CPPFLAGS = -I/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/target-mips_r2_uClibc-0.9.33.2/usr/include/tomcrypt -DLTM_DESC -DLTC_SOURCE -DENABLE_TOMCRYPT
CRYPTOPP_LDFLAGS = -L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/target-mips_r2_uClibc-0.9.33.2/usr/lib
CRYPTOPP_LIBS = -ltomcrypt -ltommath
CXX = mips-openwrt-linux-uclibc-g++
CXXCPP = mips-openwrt-linux-uclibc-g++ -E
CXXDEPMODE = depmode=gcc3
CXXFLAGS = -Os -pipe -mips32r2 -mtune=74kc -fno-caller-saves -freorder-blocks -fhonour-copts -msoft-float -std=gnu99 -DENABLE_UBUS_RPC 
CYGPATH_W = echo
DATADIRNAME = share
DEBUGFLAG = 
DEFS = -DHAVE_CONFIG_H
DEPDIR = .deps
ECHO_C = 
ECHO_N = -n
ECHO_T = 
ED2K_MANPAGES = 
EGREP = /bin/grep -E
EXEEXT = 
GDLIB_CFLAGS = 
GDLIB_CONFIG_PATH = 
GDLIB_LDFLAGS = 
GDLIB_LIBS = 
GENCAT = gencat
GEOIP_CPPFLAGS = 
GEOIP_LDFLAGS = 
GEOIP_LIBS = 
GLIBC21 = yes
GMSGFMT = /usr/bin/msgfmt
GREP = /bin/grep
INCINTL = 
INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_STRIP_PROGRAM = $(install_sh) -c -s
INSTOBJEXT = .mo
INTLBISON = bison
INTLLIBS = 
INTLOBJS = 
INTL_LIBTOOL_SUFFIX_PREFIX = 
KDE4_CONFIG = 
KDE_APPLNK_PATH = 
KDE_HEADER_DIR = 
KDE_ICON_PATH = 
KDE_MIME_PATH = 
KDE_MODULE_PATH = 
KDE_SERVICE_PATH = 
LD = mips-openwrt-linux-uclibc-ld
LDFLAGS = -L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/target-mips_r2_uClibc-0.9.33.2/usr/lib -L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/target-mips_r2_uClibc-0.9.33.2/lib -L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/usr/lib -L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/lib 
LEX = flex
LEXLIB = 
LEX_OUTPUT_ROOT = lex.yy
LIBICONV = 
LIBINTL = 
LIBOBJS =  ${LIBOBJDIR}strtod$U.o
LIBPNG_CFLAGS = 
LIBPNG_CONFIG_PATH = 
LIBPNG_LDFLAGS = 
LIBPNG_LIBS = 
LIBS = -lubox -lubus
LIBUPNP_CFLAGS = 
LIBUPNP_CPPFLAGS = 
LIBUPNP_LDFLAGS = 
LIBUPNP_LIBS = 
LTLIBICONV = 
LTLIBINTL = 
LTLIBOBJS =  ${LIBOBJDIR}strtod$U.lo
MAINT = #
MAKEINFO = ${SHELL} /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/amule-2.3.1/missing --run makeinfo
MKDIR_P = /bin/mkdir -p
MKINSTALLDIRS = ./mkinstalldirs
MONOLITHIC_MANPAGES = 
MSGFMT = /usr/bin/msgfmt
MSGMERGE = /usr/bin/msgmerge
MULECFLAGS = -w  -O2
MULECPPFLAGS =  -DUSE_WX_EXTENSIONS
MULECXXFLAGS = -w  -O2
MULELDFLAGS =  -lpthread
MULERCFLAGS = -I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/lib/wx/include/mips-openwrt-linux-base-unicode-release-static-2.8 -I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/include -I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/contrib/include -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -DwxUSE_GUI=0 
OBJEXT = o
PACKAGE = amule
PACKAGE_BUGREPORT = admin@amule.org
PACKAGE_NAME = aMule
PACKAGE_STRING = aMule 2.3.1
PACKAGE_TARNAME = amule
PACKAGE_URL = 
PACKAGE_VERSION = 2.3.1
PATH_SEPARATOR = :
PKG_CONFIG = /home/ubuntu/Archer_C7_V5/openwrt/staging_dir/host/bin/pkg-config
POSUB = 
POW_LIB = -lm
QT_CORE_CXXFLAGS = 
QT_CORE_LIBS = 
QT_DBUS_LDFLAGS = 
QT_GUI_CXXFLAGS = 
QT_GUI_LIBS = 
QT_MOC = 
RANLIB = mips-openwrt-linux-uclibc-ranlib
RC = 
RCFLAGS = 
READLINE_LIBS = 
RESOLV_LIB = 
SET_MAKE = 
SHELL = /bin/bash
STRIP = mips-openwrt-linux-uclibc-strip
SVNDATE = 
USE_INCLUDED_LIBINTL = no
USE_NLS = no
VERSION = 2.3.1
WEBSERVER_MANPAGES = 
WXBASE_CPPFLAGS = -I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/lib/wx/include/mips-openwrt-linux-base-unicode-release-static-2.8 -I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/include -I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/contrib/include -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -DwxUSE_GUI=0 -DwxUSE_GUI=0
WXBASE_LIBS = -L/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/lib -pthread -L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/target-mips_r2_uClibc-0.9.33.2/usr/lib -L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/target-mips_r2_uClibc-0.9.33.2/lib -L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/usr/lib -L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/lib   /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/lib/libwx_baseu_net-2.8-mips-openwrt-linux.a /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/lib/libwx_baseu-2.8-mips-openwrt-linux.a -lwxregexu-2.8-mips-openwrt-linux -lz -ldl -lm 
WXCAS_MANPAGES = 
WX_CFLAGS = -I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/lib/wx/include/mips-openwrt-linux-base-unicode-release-static-2.8 -I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/include -I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/contrib/include -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -DwxUSE_GUI=0 -pthread
WX_CFLAGS_ONLY = -pthread
WX_CONFIG_PATH = /home/ubuntu/Archer_C7_V5/openwrt/staging_dir/target-mips_r2_uClibc-0.9.33.2/usr/bin/wx-config
WX_CPPFLAGS = -I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/lib/wx/include/mips-openwrt-linux-base-unicode-release-static-2.8 -I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/include -I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/contrib/include -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -DwxUSE_GUI=0
WX_CXXFLAGS = -I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/lib/wx/include/mips-openwrt-linux-base-unicode-release-static-2.8 -I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/include -I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/contrib/include -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -DwxUSE_GUI=0 -pthread
WX_CXXFLAGS_ONLY = 
WX_DEBUG = 0
WX_LIBS = -L/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/lib -pthread -L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/target-mips_r2_uClibc-0.9.33.2/usr/lib -L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/target-mips_r2_uClibc-0.9.33.2/lib -L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/usr/lib -L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/lib   /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/lib/libwx_baseu_adv-2.8-mips-openwrt-linux.a /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/lib/libwx_baseu_core-2.8-mips-openwrt-linux.a /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/lib/libwx_baseu_net-2.8-mips-openwrt-linux.a /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/wxgtk-2.8.12/lib/libwx_baseu-2.8-mips-openwrt-linux.a -lwxregexu-2.8-mips-openwrt-linux -lz -ldl -lm 
WX_PORT = base
WX_RESCOMP = 
WX_SHARED = 0
WX_UNICODE = 
WX_VERSION_FULL = 2.8.12
WX_VERSION_MAJOR = 2
WX_VERSION_MINOR = 8
XGETTEXT = /usr/bin/xgettext
YACC = bison -y
YFLAGS = 
ZLIB_CPPFLAGS = -I/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/target-mips_r2_uClibc-0.9.33.2/usr/include
ZLIB_LDFLAGS = -L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/target-mips_r2_uClibc-0.9.33.2/usr/lib
ZLIB_LIBS = -lz
abs_builddir = /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/amule-2.3.1/src/utils/plasmamule
abs_srcdir = /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/amule-2.3.1/src/utils/plasmamule
abs_top_builddir = /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/amule-2.3.1
abs_top_srcdir = /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/amule-2.3.1
ac_ct_BUILD_CC = 
ac_ct_CC = 
ac_ct_CXX = 
am__include = include
am__leading_dot = .
am__quote = 
am__tar = ${AMTAR} chof - "$$tardir"
am__untar = ${AMTAR} xf -
bindir = /usr/bin
build = i686-pc-linux-gnu
build_alias = i686-linux-gnu
build_cpu = i686
build_os = linux-gnu
build_vendor = pc
builddir = .
datadir = /usr/share
datarootdir = ${prefix}/share
docdir = ${datarootdir}/doc/${PACKAGE_TARNAME}
dvidir = ${docdir}
exec_prefix = /usr
host = mips-openwrt-linux-gnu
host_alias = mips-openwrt-linux
host_cpu = mips
host_os = linux-gnu
host_vendor = openwrt
htmldir = ${docdir}
includedir = ${prefix}/include
infodir = /usr/info
install_sh = ${SHELL} /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/amule-2.3.1/install-sh
libdir = ${exec_prefix}/lib
libexecdir = /usr/lib
localedir = ${datarootdir}/locale
localstatedir = /var
mandir = /usr/man
mkdir_p = /bin/mkdir -p
oldincludedir = /usr/include
pdfdir = ${docdir}
prefix = /usr
program_transform_name = s&$$&&;s&^&&
psdir = ${docdir}
sbindir = /usr/sbin
sharedstatedir = ${prefix}/com
srcdir = .
sysconfdir = /etc
target_alias = mips-openwrt-linux
top_build_prefix = ../../../
top_builddir = ../../..
top_srcdir = ../../..
plasma_engine_plasmamule_so_SOURCES = plasma-engine-plasmamule.cpp qt-emc.cpp
plasma_applet_plasmamule_so_SOURCES = plasma-applet-plasmamule.cpp plasmamule-dbus.cpp
plasmamule_engine_feeder_SOURCES = plasmamule-engine-feeder.cpp plasmamule-dbus.cpp
nodist_plasma_engine_plasmamule_so_SOURCES = plasma-engine-plasmamule.moc
nodist_plasma_applet_plasmamule_so_SOURCES = plasma-applet-plasmamule.moc
plasma_engine_plasmamule_so_CXXFLAGS = -shared -I${KDE_HEADER_DIR} ${QT_CORE_CXXFLAGS} -DPIC -fPIC ${DEBUGFLAG}
plasma_applet_plasmamule_so_CXXFLAGS = -shared -D__IMG_PATH__=\"${KDE_ICON_PATH}\" -I${KDE_HEADER_DIR} ${QT_GUI_CXXFLAGS} -DPIC -fPIC ${DEBUGFLAG}
plasmamule_engine_feeder_CXXFLAGS = -I${KDE_HEADER_DIR} ${QT_GUI_CXXFLAGS} ${DEBUGFLAG}
plasmamule_engine_feeder_LDFLAGS = ${QT_GUI_LIBS} -lkdecore -lplasma ${QT_DBUS_LDFLAGS}
noinst_HEADERS = plasma-engine-plasmamule.h plasma-applet-plasmamule.h plasmamule-dbus.h qt-emc.h
CLEANFILES = *.moc
MAINTAINERCLEANFILES = Makefile.in
all: $(BUILT_SOURCES)
	$(MAKE) $(AM_MAKEFLAGS) all-am
.SUFFIXES:
.SUFFIXES: .cpp .o .obj
$(srcdir)/Makefile.in: # $(srcdir)/Makefile.am  $(am__configure_deps)
	@for dep in $?; do \
	  case '$(am__configure_deps)' in \
	    *$$dep*) \
	      ( cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh ) \
	        && { if test -f $@; then exit 0; else break; fi; }; \
	      exit 1;; \
	  esac; \
	done; \
	echo ' cd $(top_srcdir) && $(AUTOMAKE) --foreign src/utils/plasmamule/Makefile'>/dev/null; \
	$(am__cd) $(top_srcdir) && \
	  $(AUTOMAKE) --foreign src/utils/plasmamule/Makefile
.PRECIOUS: Makefile
Makefile: $(srcdir)/Makefile.in $(top_builddir)/config.status
	@case '$?' in \
	  *config.status*) \
	    cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh;; \
	  *) \
	    echo ' cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe)'>/dev/null; \
	    cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe) denoiser;; \
	esac;
$(top_builddir)/config.status: $(top_srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(top_srcdir)/configure: # $(am__configure_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(ACLOCAL_M4): # $(am__aclocal_m4_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(am__aclocal_m4_deps):
install-binPROGRAMS: $(bin_PROGRAMS)
	@$(NORMAL_INSTALL)
	test -z "$(bindir)" || $(MKDIR_P) "$(DESTDIR)$(bindir)"
	@list='$(bin_PROGRAMS)'; test -n "$(bindir)" || list=; \
	for p in $$list; do echo "$$p $$p"; done | \
	sed 's/$(EXEEXT)$$//' | \
	while read p p1; do if test -f $$p; \
	  then echo "$$p"; echo "$$p"; else :; fi; \
	done | \
	sed -e 'p;s,.*/,,;n;h' -e 's|.*|.|' \
	    -e 'p;x;s,.*/,,;s/$(EXEEXT)$$//;$(transform);s/$$/$(EXEEXT)/' | \
	sed 'N;N;N;s,\n, ,g' | \
	$(AWK) 'BEGIN { files["."] = ""; dirs["."] = 1 } \
	  { d=$$3; if (dirs[d] != 1) { print "d", d; dirs[d] = 1 } \
	    if ($$2 == $$4) files[d] = files[d] " " $$1; \
	    else { print "f", $$3 "/" $$4, $$1; } } \
	  END { for (d in files) print "f", d, files[d] }' | \
	while read type dir files; do \
	    if test "$$dir" = .; then dir=; else dir=/$$dir; fi; \
	    test -z "$$files" || { \
	      echo " $(INSTALL_PROGRAM_ENV) $(INSTALL_PROGRAM) $$files '$(DESTDIR)$(bindir)$$dir'">/dev/null; \
	echo "Installing $(bindir)$$dir"; \
	      $(INSTALL_PROGRAM_ENV) $(INSTALL_PROGRAM) $$files "$(DESTDIR)$(bindir)$$dir" || exit $$?; \
	    } \
	; done
uninstall-binPROGRAMS:
	@$(NORMAL_UNINSTALL)
	@list='$(bin_PROGRAMS)'; test -n "$(bindir)" || list=; \
	files=`for p in $$list; do echo "$$p"; done | \
	  sed -e 'h;s,^.*/,,;s/$(EXEEXT)$$//;$(transform)' \
	      -e 's/$$/$(EXEEXT)/' `; \
	test -n "$$list" || exit 0; \
	echo " ( cd '$(DESTDIR)$(bindir)' && rm -f" $$files ")">/dev/null; \
	cd "$(DESTDIR)$(bindir)" && rm -f $$files
clean-binPROGRAMS:
	-test -z "$(bin_PROGRAMS)" || rm -f $(bin_PROGRAMS)
install-modulesPROGRAMS: $(modules_PROGRAMS)
	@$(NORMAL_INSTALL)
	test -z "$(modulesdir)" || $(MKDIR_P) "$(DESTDIR)$(modulesdir)"
	@list='$(modules_PROGRAMS)'; test -n "$(modulesdir)" || list=; \
	for p in $$list; do echo "$$p $$p"; done | \
	sed 's/$(EXEEXT)$$//' | \
	while read p p1; do if test -f $$p; \
	  then echo "$$p"; echo "$$p"; else :; fi; \
	done | \
	sed -e 'p;s,.*/,,;n;h' -e 's|.*|.|' \
	    -e 'p;x;s,.*/,,;s/$(EXEEXT)$$//;$(transform);s/$$/$(EXEEXT)/' | \
	sed 'N;N;N;s,\n, ,g' | \
	$(AWK) 'BEGIN { files["."] = ""; dirs["."] = 1 } \
	  { d=$$3; if (dirs[d] != 1) { print "d", d; dirs[d] = 1 } \
	    if ($$2 == $$4) files[d] = files[d] " " $$1; \
	    else { print "f", $$3 "/" $$4, $$1; } } \
	  END { for (d in files) print "f", d, files[d] }' | \
	while read type dir files; do \
	    if test "$$dir" = .; then dir=; else dir=/$$dir; fi; \
	    test -z "$$files" || { \
	      echo " $(INSTALL_PROGRAM_ENV) $(INSTALL_PROGRAM) $$files '$(DESTDIR)$(modulesdir)$$dir'">/dev/null; \
	echo "Installing $(modulesdir)"; \
	      $(INSTALL_PROGRAM_ENV) $(INSTALL_PROGRAM) $$files "$(DESTDIR)$(modulesdir)$$dir" || exit $$?; \
	    } \
	; done
uninstall-modulesPROGRAMS:
	@$(NORMAL_UNINSTALL)
	@list='$(modules_PROGRAMS)'; test -n "$(modulesdir)" || list=; \
	files=`for p in $$list; do echo "$$p"; done | \
	  sed -e 'h;s,^.*/,,;s/$(EXEEXT)$$//;$(transform)' \
	      -e 's/$$/$(EXEEXT)/' `; \
	test -n "$$list" || exit 0; \
	echo " ( cd '$(DESTDIR)$(modulesdir)' && rm -f" $$files ")">/dev/null; \
	cd "$(DESTDIR)$(modulesdir)" && rm -f $$files
clean-modulesPROGRAMS:
	-test -z "$(modules_PROGRAMS)" || rm -f $(modules_PROGRAMS)
plasma-applet-plasmamule.so$(EXEEXT): $(plasma_applet_plasmamule_so_OBJECTS) $(plasma_applet_plasmamule_so_DEPENDENCIES) 
	echo "Linking $(@F)"
	@rm -f plasma-applet-plasmamule.so$(EXEEXT)
	$(plasma_applet_plasmamule_so_LINK) $(plasma_applet_plasmamule_so_OBJECTS) $(plasma_applet_plasmamule_so_LDADD) $(LIBS)
plasma-engine-plasmamule.so$(EXEEXT): $(plasma_engine_plasmamule_so_OBJECTS) $(plasma_engine_plasmamule_so_DEPENDENCIES) 
	echo "Linking $(@F)"
	@rm -f plasma-engine-plasmamule.so$(EXEEXT)
	$(plasma_engine_plasmamule_so_LINK) $(plasma_engine_plasmamule_so_OBJECTS) $(plasma_engine_plasmamule_so_LDADD) $(LIBS)
plasmamule-engine-feeder$(EXEEXT): $(plasmamule_engine_feeder_OBJECTS) $(plasmamule_engine_feeder_DEPENDENCIES) 
	echo "Linking $(@F)"
	@rm -f plasmamule-engine-feeder$(EXEEXT)
	$(plasmamule_engine_feeder_LINK) $(plasmamule_engine_feeder_OBJECTS) $(plasmamule_engine_feeder_LDADD) $(LIBS)
mostlyclean-compile:
	-rm -f *.$(OBJEXT)
distclean-compile:
	-rm -f *.tab.c
include ./$(DEPDIR)/plasma_applet_plasmamule_so-plasma-applet-plasmamule.Po
include ./$(DEPDIR)/plasma_applet_plasmamule_so-plasmamule-dbus.Po
include ./$(DEPDIR)/plasma_engine_plasmamule_so-plasma-engine-plasmamule.Po
include ./$(DEPDIR)/plasma_engine_plasmamule_so-qt-emc.Po
include ./$(DEPDIR)/plasmamule_engine_feeder-plasmamule-dbus.Po
include ./$(DEPDIR)/plasmamule_engine_feeder-plasmamule-engine-feeder.Po
.cpp.o:
	echo "Compiling $(<F)"
	$(CXXCOMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
	$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
.cpp.obj:
	echo "Compiling $(<F)"
	$(CXXCOMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ `$(CYGPATH_W) '$<'`
	$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
plasma_applet_plasmamule_so-plasma-applet-plasmamule.o: plasma-applet-plasmamule.cpp
	echo "Compiling $(<F)"
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(plasma_applet_plasmamule_so_CXXFLAGS) $(CXXFLAGS) -MT plasma_applet_plasmamule_so-plasma-applet-plasmamule.o -MD -MP -MF $(DEPDIR)/plasma_applet_plasmamule_so-plasma-applet-plasmamule.Tpo -c -o plasma_applet_plasmamule_so-plasma-applet-plasmamule.o `test -f 'plasma-applet-plasmamule.cpp' || echo '$(srcdir)/'`plasma-applet-plasmamule.cpp
	$(am__mv) $(DEPDIR)/plasma_applet_plasmamule_so-plasma-applet-plasmamule.Tpo $(DEPDIR)/plasma_applet_plasmamule_so-plasma-applet-plasmamule.Po
plasma_applet_plasmamule_so-plasma-applet-plasmamule.obj: plasma-applet-plasmamule.cpp
	echo "Compiling $(<F)"
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(plasma_applet_plasmamule_so_CXXFLAGS) $(CXXFLAGS) -MT plasma_applet_plasmamule_so-plasma-applet-plasmamule.obj -MD -MP -MF $(DEPDIR)/plasma_applet_plasmamule_so-plasma-applet-plasmamule.Tpo -c -o plasma_applet_plasmamule_so-plasma-applet-plasmamule.obj `if test -f 'plasma-applet-plasmamule.cpp'; then $(CYGPATH_W) 'plasma-applet-plasmamule.cpp'; else $(CYGPATH_W) '$(srcdir)/plasma-applet-plasmamule.cpp'; fi`
	$(am__mv) $(DEPDIR)/plasma_applet_plasmamule_so-plasma-applet-plasmamule.Tpo $(DEPDIR)/plasma_applet_plasmamule_so-plasma-applet-plasmamule.Po
plasma_applet_plasmamule_so-plasmamule-dbus.o: plasmamule-dbus.cpp
	echo "Compiling $(<F)"
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(plasma_applet_plasmamule_so_CXXFLAGS) $(CXXFLAGS) -MT plasma_applet_plasmamule_so-plasmamule-dbus.o -MD -MP -MF $(DEPDIR)/plasma_applet_plasmamule_so-plasmamule-dbus.Tpo -c -o plasma_applet_plasmamule_so-plasmamule-dbus.o `test -f 'plasmamule-dbus.cpp' || echo '$(srcdir)/'`plasmamule-dbus.cpp
	$(am__mv) $(DEPDIR)/plasma_applet_plasmamule_so-plasmamule-dbus.Tpo $(DEPDIR)/plasma_applet_plasmamule_so-plasmamule-dbus.Po
plasma_applet_plasmamule_so-plasmamule-dbus.obj: plasmamule-dbus.cpp
	echo "Compiling $(<F)"
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(plasma_applet_plasmamule_so_CXXFLAGS) $(CXXFLAGS) -MT plasma_applet_plasmamule_so-plasmamule-dbus.obj -MD -MP -MF $(DEPDIR)/plasma_applet_plasmamule_so-plasmamule-dbus.Tpo -c -o plasma_applet_plasmamule_so-plasmamule-dbus.obj `if test -f 'plasmamule-dbus.cpp'; then $(CYGPATH_W) 'plasmamule-dbus.cpp'; else $(CYGPATH_W) '$(srcdir)/plasmamule-dbus.cpp'; fi`
	$(am__mv) $(DEPDIR)/plasma_applet_plasmamule_so-plasmamule-dbus.Tpo $(DEPDIR)/plasma_applet_plasmamule_so-plasmamule-dbus.Po
plasma_engine_plasmamule_so-plasma-engine-plasmamule.o: plasma-engine-plasmamule.cpp
	echo "Compiling $(<F)"
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(plasma_engine_plasmamule_so_CXXFLAGS) $(CXXFLAGS) -MT plasma_engine_plasmamule_so-plasma-engine-plasmamule.o -MD -MP -MF $(DEPDIR)/plasma_engine_plasmamule_so-plasma-engine-plasmamule.Tpo -c -o plasma_engine_plasmamule_so-plasma-engine-plasmamule.o `test -f 'plasma-engine-plasmamule.cpp' || echo '$(srcdir)/'`plasma-engine-plasmamule.cpp
	$(am__mv) $(DEPDIR)/plasma_engine_plasmamule_so-plasma-engine-plasmamule.Tpo $(DEPDIR)/plasma_engine_plasmamule_so-plasma-engine-plasmamule.Po
plasma_engine_plasmamule_so-plasma-engine-plasmamule.obj: plasma-engine-plasmamule.cpp
	echo "Compiling $(<F)"
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(plasma_engine_plasmamule_so_CXXFLAGS) $(CXXFLAGS) -MT plasma_engine_plasmamule_so-plasma-engine-plasmamule.obj -MD -MP -MF $(DEPDIR)/plasma_engine_plasmamule_so-plasma-engine-plasmamule.Tpo -c -o plasma_engine_plasmamule_so-plasma-engine-plasmamule.obj `if test -f 'plasma-engine-plasmamule.cpp'; then $(CYGPATH_W) 'plasma-engine-plasmamule.cpp'; else $(CYGPATH_W) '$(srcdir)/plasma-engine-plasmamule.cpp'; fi`
	$(am__mv) $(DEPDIR)/plasma_engine_plasmamule_so-plasma-engine-plasmamule.Tpo $(DEPDIR)/plasma_engine_plasmamule_so-plasma-engine-plasmamule.Po
plasma_engine_plasmamule_so-qt-emc.o: qt-emc.cpp
	echo "Compiling $(<F)"
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(plasma_engine_plasmamule_so_CXXFLAGS) $(CXXFLAGS) -MT plasma_engine_plasmamule_so-qt-emc.o -MD -MP -MF $(DEPDIR)/plasma_engine_plasmamule_so-qt-emc.Tpo -c -o plasma_engine_plasmamule_so-qt-emc.o `test -f 'qt-emc.cpp' || echo '$(srcdir)/'`qt-emc.cpp
	$(am__mv) $(DEPDIR)/plasma_engine_plasmamule_so-qt-emc.Tpo $(DEPDIR)/plasma_engine_plasmamule_so-qt-emc.Po
plasma_engine_plasmamule_so-qt-emc.obj: qt-emc.cpp
	echo "Compiling $(<F)"
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(plasma_engine_plasmamule_so_CXXFLAGS) $(CXXFLAGS) -MT plasma_engine_plasmamule_so-qt-emc.obj -MD -MP -MF $(DEPDIR)/plasma_engine_plasmamule_so-qt-emc.Tpo -c -o plasma_engine_plasmamule_so-qt-emc.obj `if test -f 'qt-emc.cpp'; then $(CYGPATH_W) 'qt-emc.cpp'; else $(CYGPATH_W) '$(srcdir)/qt-emc.cpp'; fi`
	$(am__mv) $(DEPDIR)/plasma_engine_plasmamule_so-qt-emc.Tpo $(DEPDIR)/plasma_engine_plasmamule_so-qt-emc.Po
plasmamule_engine_feeder-plasmamule-engine-feeder.o: plasmamule-engine-feeder.cpp
	echo "Compiling $(<F)"
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(plasmamule_engine_feeder_CXXFLAGS) $(CXXFLAGS) -MT plasmamule_engine_feeder-plasmamule-engine-feeder.o -MD -MP -MF $(DEPDIR)/plasmamule_engine_feeder-plasmamule-engine-feeder.Tpo -c -o plasmamule_engine_feeder-plasmamule-engine-feeder.o `test -f 'plasmamule-engine-feeder.cpp' || echo '$(srcdir)/'`plasmamule-engine-feeder.cpp
	$(am__mv) $(DEPDIR)/plasmamule_engine_feeder-plasmamule-engine-feeder.Tpo $(DEPDIR)/plasmamule_engine_feeder-plasmamule-engine-feeder.Po
plasmamule_engine_feeder-plasmamule-engine-feeder.obj: plasmamule-engine-feeder.cpp
	echo "Compiling $(<F)"
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(plasmamule_engine_feeder_CXXFLAGS) $(CXXFLAGS) -MT plasmamule_engine_feeder-plasmamule-engine-feeder.obj -MD -MP -MF $(DEPDIR)/plasmamule_engine_feeder-plasmamule-engine-feeder.Tpo -c -o plasmamule_engine_feeder-plasmamule-engine-feeder.obj `if test -f 'plasmamule-engine-feeder.cpp'; then $(CYGPATH_W) 'plasmamule-engine-feeder.cpp'; else $(CYGPATH_W) '$(srcdir)/plasmamule-engine-feeder.cpp'; fi`
	$(am__mv) $(DEPDIR)/plasmamule_engine_feeder-plasmamule-engine-feeder.Tpo $(DEPDIR)/plasmamule_engine_feeder-plasmamule-engine-feeder.Po
plasmamule_engine_feeder-plasmamule-dbus.o: plasmamule-dbus.cpp
	echo "Compiling $(<F)"
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(plasmamule_engine_feeder_CXXFLAGS) $(CXXFLAGS) -MT plasmamule_engine_feeder-plasmamule-dbus.o -MD -MP -MF $(DEPDIR)/plasmamule_engine_feeder-plasmamule-dbus.Tpo -c -o plasmamule_engine_feeder-plasmamule-dbus.o `test -f 'plasmamule-dbus.cpp' || echo '$(srcdir)/'`plasmamule-dbus.cpp
	$(am__mv) $(DEPDIR)/plasmamule_engine_feeder-plasmamule-dbus.Tpo $(DEPDIR)/plasmamule_engine_feeder-plasmamule-dbus.Po
plasmamule_engine_feeder-plasmamule-dbus.obj: plasmamule-dbus.cpp
	echo "Compiling $(<F)"
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(plasmamule_engine_feeder_CXXFLAGS) $(CXXFLAGS) -MT plasmamule_engine_feeder-plasmamule-dbus.obj -MD -MP -MF $(DEPDIR)/plasmamule_engine_feeder-plasmamule-dbus.Tpo -c -o plasmamule_engine_feeder-plasmamule-dbus.obj `if test -f 'plasmamule-dbus.cpp'; then $(CYGPATH_W) 'plasmamule-dbus.cpp'; else $(CYGPATH_W) '$(srcdir)/plasmamule-dbus.cpp'; fi`
	$(am__mv) $(DEPDIR)/plasmamule_engine_feeder-plasmamule-dbus.Tpo $(DEPDIR)/plasmamule_engine_feeder-plasmamule-dbus.Po
install-dist_appsDATA: $(dist_apps_DATA)
	@$(NORMAL_INSTALL)
	test -z "$(appsdir)" || $(MKDIR_P) "$(DESTDIR)$(appsdir)"
	@list='$(dist_apps_DATA)'; test -n "$(appsdir)" || list=; \
	for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  echo "$$d$$p"; \
	done | $(am__base_list) | \
	while read files; do \
	  echo " $(INSTALL_DATA) $$files '$(DESTDIR)$(appsdir)'">/dev/null; \
	echo "Installing $(appsdir)"; \
	  $(INSTALL_DATA) $$files "$(DESTDIR)$(appsdir)" || exit $$?; \
	done
uninstall-dist_appsDATA:
	@$(NORMAL_UNINSTALL)
	@list='$(dist_apps_DATA)'; test -n "$(appsdir)" || list=; \
	files=`for p in $$list; do echo $$p; done | sed -e 's|^.*/||'`; \
	test -n "$$files" || exit 0; \
	echo " ( cd '$(DESTDIR)$(appsdir)' && rm -f" $$files ")">/dev/null; \
	cd "$(DESTDIR)$(appsdir)" && rm -f $$files
install-dist_iconDATA: $(dist_icon_DATA)
	@$(NORMAL_INSTALL)
	test -z "$(icondir)" || $(MKDIR_P) "$(DESTDIR)$(icondir)"
	@list='$(dist_icon_DATA)'; test -n "$(icondir)" || list=; \
	for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  echo "$$d$$p"; \
	done | $(am__base_list) | \
	while read files; do \
	  echo " $(INSTALL_DATA) $$files '$(DESTDIR)$(icondir)'">/dev/null; \
	echo "Installing $(icondir)"; \
	  $(INSTALL_DATA) $$files "$(DESTDIR)$(icondir)" || exit $$?; \
	done
uninstall-dist_iconDATA:
	@$(NORMAL_UNINSTALL)
	@list='$(dist_icon_DATA)'; test -n "$(icondir)" || list=; \
	files=`for p in $$list; do echo $$p; done | sed -e 's|^.*/||'`; \
	test -n "$$files" || exit 0; \
	echo " ( cd '$(DESTDIR)$(icondir)' && rm -f" $$files ")">/dev/null; \
	cd "$(DESTDIR)$(icondir)" && rm -f $$files
install-dist_mimeDATA: $(dist_mime_DATA)
	@$(NORMAL_INSTALL)
	test -z "$(mimedir)" || $(MKDIR_P) "$(DESTDIR)$(mimedir)"
	@list='$(dist_mime_DATA)'; test -n "$(mimedir)" || list=; \
	for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  echo "$$d$$p"; \
	done | $(am__base_list) | \
	while read files; do \
	  echo " $(INSTALL_DATA) $$files '$(DESTDIR)$(mimedir)'">/dev/null; \
	echo "Installing $(mimedir)"; \
	  $(INSTALL_DATA) $$files "$(DESTDIR)$(mimedir)" || exit $$?; \
	done
uninstall-dist_mimeDATA:
	@$(NORMAL_UNINSTALL)
	@list='$(dist_mime_DATA)'; test -n "$(mimedir)" || list=; \
	files=`for p in $$list; do echo $$p; done | sed -e 's|^.*/||'`; \
	test -n "$$files" || exit 0; \
	echo " ( cd '$(DESTDIR)$(mimedir)' && rm -f" $$files ")">/dev/null; \
	cd "$(DESTDIR)$(mimedir)" && rm -f $$files
install-dist_serviceDATA: $(dist_service_DATA)
	@$(NORMAL_INSTALL)
	test -z "$(servicedir)" || $(MKDIR_P) "$(DESTDIR)$(servicedir)"
	@list='$(dist_service_DATA)'; test -n "$(servicedir)" || list=; \
	for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  echo "$$d$$p"; \
	done | $(am__base_list) | \
	while read files; do \
	  echo " $(INSTALL_DATA) $$files '$(DESTDIR)$(servicedir)'">/dev/null; \
	echo "Installing $(servicedir)"; \
	  $(INSTALL_DATA) $$files "$(DESTDIR)$(servicedir)" || exit $$?; \
	done
uninstall-dist_serviceDATA:
	@$(NORMAL_UNINSTALL)
	@list='$(dist_service_DATA)'; test -n "$(servicedir)" || list=; \
	files=`for p in $$list; do echo $$p; done | sed -e 's|^.*/||'`; \
	test -n "$$files" || exit 0; \
	echo " ( cd '$(DESTDIR)$(servicedir)' && rm -f" $$files ")">/dev/null; \
	cd "$(DESTDIR)$(servicedir)" && rm -f $$files
ID: $(HEADERS) $(SOURCES) $(LISP) $(TAGS_FILES)
	list='$(SOURCES) $(HEADERS) $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '{ files[$$0] = 1; nonempty = 1; } \
	      END { if (nonempty) { for (i in files) print i; }; }'`; \
	mkid -fID $$unique
tags: TAGS
TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	set x; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)  $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '{ files[$$0] = 1; nonempty = 1; } \
	      END { if (nonempty) { for (i in files) print i; }; }'`; \
	shift; \
	if test -z "$(ETAGS_ARGS)$$*$$unique"; then :; else \
	  test -n "$$unique" || unique=$$empty_fix; \
	  if test $$# -gt 0; then \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      "$$@" $$unique; \
	  else \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      $$unique; \
	  fi; \
	fi
ctags: CTAGS
CTAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	list='$(SOURCES) $(HEADERS)  $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '{ files[$$0] = 1; nonempty = 1; } \
	      END { if (nonempty) { for (i in files) print i; }; }'`; \
	test -z "$(CTAGS_ARGS)$$unique" \
	  || $(CTAGS) $(CTAGSFLAGS) $(AM_CTAGSFLAGS) $(CTAGS_ARGS) \
	     $$unique
GTAGS:
	here=`$(am__cd) $(top_builddir) && pwd` \
	  && $(am__cd) $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) "$$here"
distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH tags
distdir: $(DISTFILES)
	@srcdirstrip=`echo "$(srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	topsrcdirstrip=`echo "$(top_srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	list='$(DISTFILES)'; \
	  dist_files=`for file in $$list; do echo $$file; done | \
	  sed -e "s|^$$srcdirstrip/||;t" \
	      -e "s|^$$topsrcdirstrip/|$(top_builddir)/|;t"`; \
	case $$dist_files in \
	  */*) $(MKDIR_P) `echo "$$dist_files" | \
			   sed '/\//!d;s|^|$(distdir)/|;s,/[^/]*$$,,' | \
			   sort -u` ;; \
	esac; \
	for file in $$dist_files; do \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  if test -d $$d/$$file; then \
	    dir=`echo "/$$file" | sed -e 's,/[^/]*$$,,'`; \
	    if test -d "$(distdir)/$$file"; then \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      cp -fpR $(srcdir)/$$file "$(distdir)$$dir" || exit 1; \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    cp -fpR $$d/$$file "$(distdir)$$dir" || exit 1; \
	  else \
	    test -f "$(distdir)/$$file" \
	    || cp -p $$d/$$file "$(distdir)/$$file" \
	    || exit 1; \
	  fi; \
	done
check-am: all-am
check: $(BUILT_SOURCES)
	$(MAKE) $(AM_MAKEFLAGS) check-am
all-am: Makefile $(PROGRAMS) $(DATA) $(HEADERS)
installdirs:
	for dir in "$(DESTDIR)$(bindir)" "$(DESTDIR)$(modulesdir)" "$(DESTDIR)$(appsdir)" "$(DESTDIR)$(icondir)" "$(DESTDIR)$(mimedir)" "$(DESTDIR)$(servicedir)"; do \
	  test -z "$$dir" || $(MKDIR_P) "$$dir"; \
	done
install: $(BUILT_SOURCES)
	$(MAKE) $(AM_MAKEFLAGS) install-am
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am
install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
installcheck: installcheck-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	  install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	  `test -z '$(STRIP)' || \
	    echo "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'"` install
mostlyclean-generic:
clean-generic:
	-test -z "$(CLEANFILES)" || rm -f $(CLEANFILES)
distclean-generic:
	-test -z "$(CONFIG_CLEAN_FILES)" || rm -f $(CONFIG_CLEAN_FILES)
	-test . = "$(srcdir)" || test -z "$(CONFIG_CLEAN_VPATH_FILES)" || rm -f $(CONFIG_CLEAN_VPATH_FILES)
maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
	-test -z "$(BUILT_SOURCES)" || rm -f $(BUILT_SOURCES)
	-test -z "$(MAINTAINERCLEANFILES)" || rm -f $(MAINTAINERCLEANFILES)
clean: clean-am
clean-am: clean-binPROGRAMS clean-generic clean-modulesPROGRAMS \
	mostlyclean-am
distclean: distclean-am
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
distclean-am: clean-am distclean-compile distclean-generic \
	distclean-tags
dvi: dvi-am
dvi-am:
html: html-am
html-am:
info: info-am
info-am:
install-data-am: install-dist_appsDATA install-dist_iconDATA \
	install-dist_mimeDATA install-dist_serviceDATA \
	install-modulesPROGRAMS
install-dvi: install-dvi-am
install-dvi-am:
install-exec-am: install-binPROGRAMS
install-html: install-html-am
install-html-am:
install-info: install-info-am
install-info-am:
install-man:
install-pdf: install-pdf-am
install-pdf-am:
install-ps: install-ps-am
install-ps-am:
installcheck-am:
maintainer-clean: maintainer-clean-am
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
maintainer-clean-am: distclean-am maintainer-clean-generic
mostlyclean: mostlyclean-am
mostlyclean-am: mostlyclean-compile mostlyclean-generic
pdf: pdf-am
pdf-am:
ps: ps-am
ps-am:
uninstall-am: uninstall-binPROGRAMS uninstall-dist_appsDATA \
	uninstall-dist_iconDATA uninstall-dist_mimeDATA \
	uninstall-dist_serviceDATA uninstall-modulesPROGRAMS
.MAKE: all check install install-am install-strip
.PHONY: CTAGS GTAGS all all-am check check-am clean clean-binPROGRAMS \
	clean-generic clean-modulesPROGRAMS ctags distclean \
	distclean-compile distclean-generic distclean-tags distdir dvi \
	dvi-am html html-am info info-am install install-am \
	install-binPROGRAMS install-data install-data-am \
	install-dist_appsDATA install-dist_iconDATA \
	install-dist_mimeDATA install-dist_serviceDATA install-dvi \
	install-dvi-am install-exec install-exec-am install-html \
	install-html-am install-info install-info-am install-man \
	install-modulesPROGRAMS install-pdf install-pdf-am install-ps \
	install-ps-am install-strip installcheck installcheck-am \
	installdirs maintainer-clean maintainer-clean-generic \
	mostlyclean mostlyclean-compile mostlyclean-generic pdf pdf-am \
	ps ps-am tags uninstall uninstall-am uninstall-binPROGRAMS \
	uninstall-dist_appsDATA uninstall-dist_iconDATA \
	uninstall-dist_mimeDATA uninstall-dist_serviceDATA \
	uninstall-modulesPROGRAMS
%.moc : %.h
	${QT_MOC} -o $@ $<
.NOEXPORT:
