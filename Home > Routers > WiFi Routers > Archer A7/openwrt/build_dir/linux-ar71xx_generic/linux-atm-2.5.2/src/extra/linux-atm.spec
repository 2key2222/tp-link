Summary: linux-atm - Tools to support ATM networking under Linux.
Name: linux-atm
%define linux_atm_version 2.5.2
%define lib_current 1
%define lib_age 0
%define lib_revision 0
Version: %{linux_atm_version}
%define includedir /usr/include
Release: 1%{?dist}%{!?dist:.%{_vendor}}
License: BSD License, GNU General Public License (GPL), GNU Lesser General Public License (LGPL)
Group: System Environment/Daemons
ExclusiveOS: Linux
BuildRoot: %{_tmppath}/%{name}-%{version}-build
%define _sourcedir %(pwd)
%define _specdir %(pwd)/src/extra
%define _rpmdir %(pwd)/src/extra/RPMS
%define _srcrpmdir %(pwd)/src/extra/SRPMS
Source: linux-atm-%{linux_atm_version}.tar.gz

%define multipoint 1

%description
Tools to support ATM networking under Linux.  Eventually this will also include
support for some types of DSL modems.

%prep
%setup -q

%build
./configure --prefix=/usr --sysconfdir=%{_sysconfdir} --libdir=%{_libdir} --mandir=%{_mandir} \
		%{?multipoint:--enable-multipoint}
make

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/etc
install -c -m 644 src/config/hosts.atm $RPM_BUILD_ROOT/etc
mkdir -p $RPM_BUILD_ROOT/etc/sysconfig
install -c -m 644 src/config/init-redhat/atm-sysconfig $RPM_BUILD_ROOT/etc/sysconfig/atm
mkdir -p $RPM_BUILD_ROOT/etc/init.d
install -c -m 755 src/config/init-redhat/atm $RPM_BUILD_ROOT/etc/init.d/atm
mkdir -p $RPM_BUILD_ROOT/etc/sysconfig/network-scripts

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-, root, root, -)
%config(noreplace) /etc/hosts.atm
%config(noreplace) /etc/sysconfig/atm
%config(noreplace) /etc/atmsigd.conf
%config /etc/init.d/atm
%doc AUTHORS BUGS ChangeLog COPYING COPYING.GPL COPYING.LGPL
%doc INSTALL NEWS README THANKS
%doc doc/ src/extra/ANS src/config/init-redhat/
%{_mandir}/man[478]/*
/usr/include/atm.h
/usr/include/atmd.h
/usr/include/atmsap.h
/usr/include/atmarp.h
/usr/include/atmarpd.h
%{_libdir}/libatm.so.%{lib_current}.%{lib_age}.%{lib_revision}
%{_libdir}/libatm.so.%{lib_current}
%{_libdir}/libatm.so
%{_libdir}/libatm.la
%{_libdir}/libatm.a
/usr/bin/aread
/usr/bin/awrite
/usr/bin/svc_send
/usr/bin/svc_recv
%if multipoint
/usr/bin/pmp_send
%endif
/usr/bin/atmswitch
/usr/bin/ttcp_atm
/usr/sbin/atmsigd
/usr/bin/atmdiag
/usr/bin/atmdump
/usr/bin/sonetdiag
/usr/bin/saaldump
/usr/sbin/atmaddr
/usr/sbin/esi
/usr/sbin/atmloop
/usr/sbin/atmtcp
/usr/sbin/enitune
/usr/sbin/zntune
/usr/sbin/hediag
/usr/sbin/atmarp
/usr/sbin/atmarpd
/usr/sbin/br2684ctl
/usr/sbin/ilmid
/usr/sbin/ilmidiag
/usr/sbin/zeppelin
/usr/sbin/les
/usr/sbin/bus
/usr/sbin/lecs
/usr/sbin/mpcd

%post
/sbin/ldconfig -n %{_libdir}
/sbin/chkconfig --add atm

%postun
/sbin/ldconfig -n %{_libdir}

%changelog
* Fri Sep 14 2001 Paul Schroeder <paulsch@@us.ibm.com>
- First build of linux-atm RPM.

