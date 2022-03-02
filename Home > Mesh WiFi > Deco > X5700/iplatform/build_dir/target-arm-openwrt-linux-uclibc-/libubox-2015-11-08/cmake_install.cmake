# Install script for directory: /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libubox" TYPE FILE FILES
    "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/avl-cmp.h"
    "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/avl.h"
    "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/blob.h"
    "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/blobmsg.h"
    "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/blobmsg_json.h"
    "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/json_script.h"
    "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/kvlist.h"
    "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/list.h"
    "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/md5.h"
    "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/runqueue.h"
    "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/safe_list.h"
    "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/ulog.h"
    "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/uloop.h"
    "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/usock.h"
    "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/ustream.h"
    "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/utils.h"
    "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/vlist.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/libubox.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/:" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/libubox.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libblobmsg_json.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libblobmsg_json.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libblobmsg_json.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/libblobmsg_json.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libblobmsg_json.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libblobmsg_json.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libblobmsg_json.so"
         OLD_RPATH "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/:" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libblobmsg_json.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/libblobmsg_json.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/jshn" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/jshn")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/jshn"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/jshn")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/jshn" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/jshn")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/jshn"
         OLD_RPATH "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/:" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/jshn")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson_script.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson_script.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson_script.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/libjson_script.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson_script.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson_script.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson_script.so"
         OLD_RPATH "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/:" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson_script.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/libubox" TYPE FILE FILES "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/sh/jshn.sh")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/lua/cmake_install.cmake")
  include("/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/examples/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/libubox-2015-11-08/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
