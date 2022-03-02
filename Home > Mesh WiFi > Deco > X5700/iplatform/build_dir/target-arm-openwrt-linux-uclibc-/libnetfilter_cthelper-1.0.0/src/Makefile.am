include $(top_srcdir)/Make_global.am
lib_LTLIBRARIES = libnetfilter_cthelper.la

libnetfilter_cthelper_la_LIBADD = ${LIBMNL_LIBS}
libnetfilter_cthelper_la_LDFLAGS = -Wl,--version-script=$(srcdir)/libnetfilter_cthelper.map -version-info $(LIBVERSION)
libnetfilter_cthelper_la_SOURCES = libnetfilter_cthelper.c	\
				   libnetfilter_cthelper.map	\
				   internal.h
