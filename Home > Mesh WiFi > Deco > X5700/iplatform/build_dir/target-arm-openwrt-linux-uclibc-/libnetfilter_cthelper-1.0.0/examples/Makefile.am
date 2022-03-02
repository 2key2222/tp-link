include $(top_srcdir)/Make_global.am

check_PROGRAMS = nfct-helper-get nfct-helper-add nfct-helper-del

nfct_helper_add_SOURCES = nfct-helper-add.c
nfct_helper_add_LDADD = ../src/libnetfilter_cthelper.la ${LIBMNL_LIBS}

nfct_helper_del_SOURCES = nfct-helper-del.c
nfct_helper_del_LDADD = ../src/libnetfilter_cthelper.la ${LIBMNL_LIBS}

nfct_helper_get_SOURCES = nfct-helper-get.c
nfct_helper_get_LDADD = ../src/libnetfilter_cthelper.la ${LIBMNL_LIBS}
