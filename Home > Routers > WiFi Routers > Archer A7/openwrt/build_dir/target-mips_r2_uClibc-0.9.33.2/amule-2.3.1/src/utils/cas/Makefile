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
bin_PROGRAMS = cas$(EXEEXT)
subdir = src/utils/cas
DIST_COMMON = README $(dist_cas_DATA) $(noinst_HEADERS) \
	$(srcdir)/Makefile.am $(srcdir)/Makefile.in
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
am__installdirs = "$(DESTDIR)$(bindir)" "$(DESTDIR)$(casdir)"
PROGRAMS = $(bin_PROGRAMS)
am_cas_OBJECTS = cas-cas.$(OBJEXT) cas-configfile.$(OBJEXT) \
	cas-functions.$(OBJEXT) cas-graphics.$(OBJEXT) \
	cas-html.$(OBJEXT) cas-lines.$(OBJEXT)
cas_OBJECTS = $(am_cas_OBJECTS) $(nodist_cas_OBJECTS)
am__DEPENDENCIES_1 =
cas_DEPENDENCIES = $(am__DEPENDENCIES_1)
cas_LINK = $(CCLD) $(cas_CFLAGS) $(CFLAGS) $(cas_LDFLAGS) $(LDFLAGS) \
	-o $@
DEFAULT_INCLUDES = -I. -I$(top_builddir)
depcomp = $(SHELL) $(top_srcdir)/depcomp
am__depfiles_maybe = depfiles
am__mv = mv -f
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
SOURCES = $(cas_SOURCES) $(nodist_cas_SOURCES)
DIST_SOURCES = $(cas_SOURCES)
RECURSIVE_TARGETS = all-recursive check-recursive dvi-recursive \
	html-recursive info-recursive install-data-recursive \
	install-dvi-recursive install-exec-recursive \
	install-html-recursive install-info-recursive \
	install-pdf-recursive install-ps-recursive install-recursive \
	installcheck-recursive installdirs-recursive pdf-recursive \
	ps-recursive uninstall-recursive
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
DATA = $(dist_cas_DATA)
HEADERS = $(noinst_HEADERS)
RECURSIVE_CLEAN_TARGETS = mostlyclean-recursive clean-recursive	\
  distclean-recursive maintainer-clean-recursive
AM_RECURSIVE_TARGETS = $(RECURSIVE_TARGETS:-recursive=) \
	$(RECURSIVE_CLEAN_TARGETS:-recursive=) tags TAGS ctags CTAGS \
	distdir
ETAGS = etags
CTAGS = ctags
DIST_SUBDIRS = $(SUBDIRS)
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)
am__relativize = \
  dir0=`pwd`; \
  sed_first='s,^\([^/]*\)/.*$$,\1,'; \
  sed_rest='s,^[^/]*/*,,'; \
  sed_last='s,^.*/\([^/]*\)$$,\1,'; \
  sed_butlast='s,/*[^/]*$$,,'; \
  while test -n "$$dir1"; do \
    first=`echo "$$dir1" | sed -e "$$sed_first"`; \
    if test "$$first" != "."; then \
      if test "$$first" = ".."; then \
        dir2=`echo "$$dir0" | sed -e "$$sed_last"`/"$$dir2"; \
        dir0=`echo "$$dir0" | sed -e "$$sed_butlast"`; \
      else \
        first2=`echo "$$dir2" | sed -e "$$sed_first"`; \
        if test "$$first2" = "$$first"; then \
          dir2=`echo "$$dir2" | sed -e "$$sed_rest"`; \
        else \
          dir2="../$$dir2"; \
        fi; \
        dir0="$$dir0"/"$$first"; \
      fi; \
    fi; \
    dir1=`echo "$$dir1" | sed -e "$$sed_rest"`; \
  done; \
  reldir="$$dir2"
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
abs_builddir = /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/amule-2.3.1/src/utils/cas
abs_srcdir = /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/amule-2.3.1/src/utils/cas
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
EXTRA_DIST = README
SUBDIRS = docs
dist_cas_DATA = tmp.html stat.png
casdir = $(datadir)/cas
cas_SOURCES = cas.c \
	      configfile.c \
	      functions.c \
	      graphics.c \
	      html.c \
	      lines.c
noinst_HEADERS = configfile.h \
	      functions.h \
	      graphics.h \
	      html.h \
	      lines.h \
	      version.h
cas_CPPFLAGS = $(MULECPPFLAGS) $(CAS_DEFS)
cas_CFLAGS = $(MULECFLAGS) $(GDLIB_CFLAGS)
cas_LDFLAGS = $(MULELDFLAGS) $(GDLIB_LDFLAGS) $(am__append_1)
cas_LDADD = $(GDLIB_LIBS) 
MAINTAINERCLEANFILES = Makefile.in
all: all-recursive
.SUFFIXES:
.SUFFIXES: .rc .$(OBJEXT) .c .o .obj
$(srcdir)/Makefile.in: # $(srcdir)/Makefile.am  $(am__configure_deps)
	@for dep in $?; do \
	  case '$(am__configure_deps)' in \
	    *$$dep*) \
	      ( cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh ) \
	        && { if test -f $@; then exit 0; else break; fi; }; \
	      exit 1;; \
	  esac; \
	done; \
	echo ' cd $(top_srcdir) && $(AUTOMAKE) --foreign src/utils/cas/Makefile'>/dev/null; \
	$(am__cd) $(top_srcdir) && \
	  $(AUTOMAKE) --foreign src/utils/cas/Makefile
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
cas$(EXEEXT): $(cas_OBJECTS) $(cas_DEPENDENCIES) 
	echo "Linking $(@F)"
	@rm -f cas$(EXEEXT)
	$(cas_LINK) $(cas_OBJECTS) $(cas_LDADD) $(LIBS)
mostlyclean-compile:
	-rm -f *.$(OBJEXT)
distclean-compile:
	-rm -f *.tab.c
include ./$(DEPDIR)/cas-cas.Po
include ./$(DEPDIR)/cas-configfile.Po
include ./$(DEPDIR)/cas-functions.Po
include ./$(DEPDIR)/cas-graphics.Po
include ./$(DEPDIR)/cas-html.Po
include ./$(DEPDIR)/cas-lines.Po
.c.o:
	echo "Compiling $(<F)"
	$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
	$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
.c.obj:
	echo "Compiling $(<F)"
	$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ `$(CYGPATH_W) '$<'`
	$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
cas-cas.o: cas.c
	echo "Compiling $(<F)"
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(cas_CPPFLAGS) $(CPPFLAGS) $(cas_CFLAGS) $(CFLAGS) -MT cas-cas.o -MD -MP -MF $(DEPDIR)/cas-cas.Tpo -c -o cas-cas.o `test -f 'cas.c' || echo '$(srcdir)/'`cas.c
	$(am__mv) $(DEPDIR)/cas-cas.Tpo $(DEPDIR)/cas-cas.Po
cas-cas.obj: cas.c
	echo "Compiling $(<F)"
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(cas_CPPFLAGS) $(CPPFLAGS) $(cas_CFLAGS) $(CFLAGS) -MT cas-cas.obj -MD -MP -MF $(DEPDIR)/cas-cas.Tpo -c -o cas-cas.obj `if test -f 'cas.c'; then $(CYGPATH_W) 'cas.c'; else $(CYGPATH_W) '$(srcdir)/cas.c'; fi`
	$(am__mv) $(DEPDIR)/cas-cas.Tpo $(DEPDIR)/cas-cas.Po
cas-configfile.o: configfile.c
	echo "Compiling $(<F)"
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(cas_CPPFLAGS) $(CPPFLAGS) $(cas_CFLAGS) $(CFLAGS) -MT cas-configfile.o -MD -MP -MF $(DEPDIR)/cas-configfile.Tpo -c -o cas-configfile.o `test -f 'configfile.c' || echo '$(srcdir)/'`configfile.c
	$(am__mv) $(DEPDIR)/cas-configfile.Tpo $(DEPDIR)/cas-configfile.Po
cas-configfile.obj: configfile.c
	echo "Compiling $(<F)"
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(cas_CPPFLAGS) $(CPPFLAGS) $(cas_CFLAGS) $(CFLAGS) -MT cas-configfile.obj -MD -MP -MF $(DEPDIR)/cas-configfile.Tpo -c -o cas-configfile.obj `if test -f 'configfile.c'; then $(CYGPATH_W) 'configfile.c'; else $(CYGPATH_W) '$(srcdir)/configfile.c'; fi`
	$(am__mv) $(DEPDIR)/cas-configfile.Tpo $(DEPDIR)/cas-configfile.Po
cas-functions.o: functions.c
	echo "Compiling $(<F)"
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(cas_CPPFLAGS) $(CPPFLAGS) $(cas_CFLAGS) $(CFLAGS) -MT cas-functions.o -MD -MP -MF $(DEPDIR)/cas-functions.Tpo -c -o cas-functions.o `test -f 'functions.c' || echo '$(srcdir)/'`functions.c
	$(am__mv) $(DEPDIR)/cas-functions.Tpo $(DEPDIR)/cas-functions.Po
cas-functions.obj: functions.c
	echo "Compiling $(<F)"
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(cas_CPPFLAGS) $(CPPFLAGS) $(cas_CFLAGS) $(CFLAGS) -MT cas-functions.obj -MD -MP -MF $(DEPDIR)/cas-functions.Tpo -c -o cas-functions.obj `if test -f 'functions.c'; then $(CYGPATH_W) 'functions.c'; else $(CYGPATH_W) '$(srcdir)/functions.c'; fi`
	$(am__mv) $(DEPDIR)/cas-functions.Tpo $(DEPDIR)/cas-functions.Po
cas-graphics.o: graphics.c
	echo "Compiling $(<F)"
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(cas_CPPFLAGS) $(CPPFLAGS) $(cas_CFLAGS) $(CFLAGS) -MT cas-graphics.o -MD -MP -MF $(DEPDIR)/cas-graphics.Tpo -c -o cas-graphics.o `test -f 'graphics.c' || echo '$(srcdir)/'`graphics.c
	$(am__mv) $(DEPDIR)/cas-graphics.Tpo $(DEPDIR)/cas-graphics.Po
cas-graphics.obj: graphics.c
	echo "Compiling $(<F)"
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(cas_CPPFLAGS) $(CPPFLAGS) $(cas_CFLAGS) $(CFLAGS) -MT cas-graphics.obj -MD -MP -MF $(DEPDIR)/cas-graphics.Tpo -c -o cas-graphics.obj `if test -f 'graphics.c'; then $(CYGPATH_W) 'graphics.c'; else $(CYGPATH_W) '$(srcdir)/graphics.c'; fi`
	$(am__mv) $(DEPDIR)/cas-graphics.Tpo $(DEPDIR)/cas-graphics.Po
cas-html.o: html.c
	echo "Compiling $(<F)"
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(cas_CPPFLAGS) $(CPPFLAGS) $(cas_CFLAGS) $(CFLAGS) -MT cas-html.o -MD -MP -MF $(DEPDIR)/cas-html.Tpo -c -o cas-html.o `test -f 'html.c' || echo '$(srcdir)/'`html.c
	$(am__mv) $(DEPDIR)/cas-html.Tpo $(DEPDIR)/cas-html.Po
cas-html.obj: html.c
	echo "Compiling $(<F)"
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(cas_CPPFLAGS) $(CPPFLAGS) $(cas_CFLAGS) $(CFLAGS) -MT cas-html.obj -MD -MP -MF $(DEPDIR)/cas-html.Tpo -c -o cas-html.obj `if test -f 'html.c'; then $(CYGPATH_W) 'html.c'; else $(CYGPATH_W) '$(srcdir)/html.c'; fi`
	$(am__mv) $(DEPDIR)/cas-html.Tpo $(DEPDIR)/cas-html.Po
cas-lines.o: lines.c
	echo "Compiling $(<F)"
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(cas_CPPFLAGS) $(CPPFLAGS) $(cas_CFLAGS) $(CFLAGS) -MT cas-lines.o -MD -MP -MF $(DEPDIR)/cas-lines.Tpo -c -o cas-lines.o `test -f 'lines.c' || echo '$(srcdir)/'`lines.c
	$(am__mv) $(DEPDIR)/cas-lines.Tpo $(DEPDIR)/cas-lines.Po
cas-lines.obj: lines.c
	echo "Compiling $(<F)"
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(cas_CPPFLAGS) $(CPPFLAGS) $(cas_CFLAGS) $(CFLAGS) -MT cas-lines.obj -MD -MP -MF $(DEPDIR)/cas-lines.Tpo -c -o cas-lines.obj `if test -f 'lines.c'; then $(CYGPATH_W) 'lines.c'; else $(CYGPATH_W) '$(srcdir)/lines.c'; fi`
	$(am__mv) $(DEPDIR)/cas-lines.Tpo $(DEPDIR)/cas-lines.Po
install-dist_casDATA: $(dist_cas_DATA)
	@$(NORMAL_INSTALL)
	test -z "$(casdir)" || $(MKDIR_P) "$(DESTDIR)$(casdir)"
	@list='$(dist_cas_DATA)'; test -n "$(casdir)" || list=; \
	for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  echo "$$d$$p"; \
	done | $(am__base_list) | \
	while read files; do \
	  echo " $(INSTALL_DATA) $$files '$(DESTDIR)$(casdir)'">/dev/null; \
	echo "Installing $(casdir)"; \
	  $(INSTALL_DATA) $$files "$(DESTDIR)$(casdir)" || exit $$?; \
	done
uninstall-dist_casDATA:
	@$(NORMAL_UNINSTALL)
	@list='$(dist_cas_DATA)'; test -n "$(casdir)" || list=; \
	files=`for p in $$list; do echo $$p; done | sed -e 's|^.*/||'`; \
	test -n "$$files" || exit 0; \
	echo " ( cd '$(DESTDIR)$(casdir)' && rm -f" $$files ")">/dev/null; \
	cd "$(DESTDIR)$(casdir)" && rm -f $$files
$(RECURSIVE_TARGETS):
	@fail= failcom='exit 1'; \
	for f in x $$MAKEFLAGS; do \
	  case $$f in \
	    *=* | --[!k]*);; \
	    *k*) failcom='fail=yes';; \
	  esac; \
	done; \
	dot_seen=no; \
	target=`echo $@ | sed s/-recursive//`; \
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  echo "Making $$target in $$subdir">/dev/null; \
	  if test "$$subdir" = "."; then \
	    dot_seen=yes; \
	    local_target="$$target-am"; \
	  else \
	    local_target="$$target"; \
	  fi; \
	  ($(am__cd) $$subdir && $(MAKE) $(AM_MAKEFLAGS) $$local_target) \
	  || eval $$failcom; \
	done; \
	if test "$$dot_seen" = "no"; then \
	  $(MAKE) $(AM_MAKEFLAGS) "$$target-am" || exit 1; \
	fi; test -z "$$fail"
$(RECURSIVE_CLEAN_TARGETS):
	@fail= failcom='exit 1'; \
	for f in x $$MAKEFLAGS; do \
	  case $$f in \
	    *=* | --[!k]*);; \
	    *k*) failcom='fail=yes';; \
	  esac; \
	done; \
	dot_seen=no; \
	case "$@" in \
	  distclean-* | maintainer-clean-*) list='$(DIST_SUBDIRS)' ;; \
	  *) list='$(SUBDIRS)' ;; \
	esac; \
	rev=''; for subdir in $$list; do \
	  if test "$$subdir" = "."; then :; else \
	    rev="$$subdir $$rev"; \
	  fi; \
	done; \
	rev="$$rev ."; \
	target=`echo $@ | sed s/-recursive//`; \
	for subdir in $$rev; do \
	  echo "Making $$target in $$subdir">/dev/null; \
	  if test "$$subdir" = "."; then \
	    local_target="$$target-am"; \
	  else \
	    local_target="$$target"; \
	  fi; \
	  ($(am__cd) $$subdir && $(MAKE) $(AM_MAKEFLAGS) $$local_target) \
	  || eval $$failcom; \
	done && test -z "$$fail"
tags-recursive:
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  test "$$subdir" = . || ($(am__cd) $$subdir && $(MAKE) $(AM_MAKEFLAGS) tags); \
	done
ctags-recursive:
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  test "$$subdir" = . || ($(am__cd) $$subdir && $(MAKE) $(AM_MAKEFLAGS) ctags); \
	done
ID: $(HEADERS) $(SOURCES) $(LISP) $(TAGS_FILES)
	list='$(SOURCES) $(HEADERS) $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '{ files[$$0] = 1; nonempty = 1; } \
	      END { if (nonempty) { for (i in files) print i; }; }'`; \
	mkid -fID $$unique
tags: TAGS
TAGS: tags-recursive $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	set x; \
	here=`pwd`; \
	if ($(ETAGS) --etags-include --version) >/dev/null 2>&1; then \
	  include_option=--etags-include; \
	  empty_fix=.; \
	else \
	  include_option=--include; \
	  empty_fix=; \
	fi; \
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  if test "$$subdir" = .; then :; else \
	    test ! -f $$subdir/TAGS || \
	      set "$$@" "$$include_option=$$here/$$subdir/TAGS"; \
	  fi; \
	done; \
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
CTAGS: ctags-recursive $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
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
	@list='$(DIST_SUBDIRS)'; for subdir in $$list; do \
	  if test "$$subdir" = .; then :; else \
	    test -d "$(distdir)/$$subdir" \
	    || $(MKDIR_P) "$(distdir)/$$subdir" \
	    || exit 1; \
	  fi; \
	done
	@list='$(DIST_SUBDIRS)'; for subdir in $$list; do \
	  if test "$$subdir" = .; then :; else \
	    dir1=$$subdir; dir2="$(distdir)/$$subdir"; \
	    $(am__relativize); \
	    new_distdir=$$reldir; \
	    dir1=$$subdir; dir2="$(top_distdir)"; \
	    $(am__relativize); \
	    new_top_distdir=$$reldir; \
	    echo " (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) top_distdir="$$new_top_distdir" distdir="$$new_distdir" \\">/dev/null; \
	    echo "     am__remove_distdir=: am__skip_length_check=: am__skip_mode_fix=: distdir)">/dev/null; \
	    ($(am__cd) $$subdir && \
	      $(MAKE) $(AM_MAKEFLAGS) \
	        top_distdir="$$new_top_distdir" \
	        distdir="$$new_distdir" \
		am__remove_distdir=: \
		am__skip_length_check=: \
		am__skip_mode_fix=: \
	        distdir) \
	      || exit 1; \
	  fi; \
	done
check-am: all-am
check: check-recursive
all-am: Makefile $(PROGRAMS) $(DATA) $(HEADERS)
installdirs: installdirs-recursive
installdirs-am:
	for dir in "$(DESTDIR)$(bindir)" "$(DESTDIR)$(casdir)"; do \
	  test -z "$$dir" || $(MKDIR_P) "$$dir"; \
	done
install: install-recursive
install-exec: install-exec-recursive
install-data: install-data-recursive
uninstall: uninstall-recursive
install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
installcheck: installcheck-recursive
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
	-test -z "$(MAINTAINERCLEANFILES)" || rm -f $(MAINTAINERCLEANFILES)
clean: clean-recursive
clean-am: clean-binPROGRAMS clean-generic mostlyclean-am
distclean: distclean-recursive
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
distclean-am: clean-am distclean-compile distclean-generic \
	distclean-tags
dvi: dvi-recursive
dvi-am:
html: html-recursive
html-am:
info: info-recursive
info-am:
install-data-am: install-dist_casDATA
install-dvi: install-dvi-recursive
install-dvi-am:
install-exec-am: install-binPROGRAMS
install-html: install-html-recursive
install-html-am:
install-info: install-info-recursive
install-info-am:
install-man:
install-pdf: install-pdf-recursive
install-pdf-am:
install-ps: install-ps-recursive
install-ps-am:
installcheck-am:
maintainer-clean: maintainer-clean-recursive
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
maintainer-clean-am: distclean-am maintainer-clean-generic
mostlyclean: mostlyclean-recursive
mostlyclean-am: mostlyclean-compile mostlyclean-generic
pdf: pdf-recursive
pdf-am:
ps: ps-recursive
ps-am:
uninstall-am: uninstall-binPROGRAMS uninstall-dist_casDATA
.MAKE: $(RECURSIVE_CLEAN_TARGETS) $(RECURSIVE_TARGETS) ctags-recursive \
	install-am install-strip tags-recursive
.PHONY: $(RECURSIVE_CLEAN_TARGETS) $(RECURSIVE_TARGETS) CTAGS GTAGS \
	all all-am check check-am clean clean-binPROGRAMS \
	clean-generic ctags ctags-recursive distclean \
	distclean-compile distclean-generic distclean-tags distdir dvi \
	dvi-am html html-am info info-am install install-am \
	install-binPROGRAMS install-data install-data-am \
	install-dist_casDATA install-dvi install-dvi-am install-exec \
	install-exec-am install-html install-html-am install-info \
	install-info-am install-man install-pdf install-pdf-am \
	install-ps install-ps-am install-strip installcheck \
	installcheck-am installdirs installdirs-am maintainer-clean \
	maintainer-clean-generic mostlyclean mostlyclean-compile \
	mostlyclean-generic pdf pdf-am ps ps-am tags tags-recursive \
	uninstall uninstall-am uninstall-binPROGRAMS \
	uninstall-dist_casDATA
.NOEXPORT:
