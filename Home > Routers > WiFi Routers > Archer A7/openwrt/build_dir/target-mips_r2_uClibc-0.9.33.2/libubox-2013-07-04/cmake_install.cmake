# Install script for directory: /home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libubox" TYPE FILE FILES
    "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/runqueue.h"
    "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/safe_list.h"
    "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/blob.h"
    "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/list_compat.h"
    "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/json_script.h"
    "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/blobmsg_json.h"
    "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/avl.h"
    "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/avl-cmp.h"
    "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/blobmsg.h"
    "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/utils.h"
    "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/vlist.h"
    "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/usock.h"
    "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/ustream.h"
    "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/uloop.h"
    "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/list.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/libubox.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/:" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libblobmsg_json.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libblobmsg_json.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libblobmsg_json.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/libblobmsg_json.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libblobmsg_json.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libblobmsg_json.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libblobmsg_json.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/:" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libblobmsg_json.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/jshn" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/jshn")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/jshn"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/jshn")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/jshn" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/jshn")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/:" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/jshn")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson_script.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson_script.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson_script.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/libjson_script.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson_script.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson_script.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson_script.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/:" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson_script.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/libubox" TYPE FILE FILES "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/sh/jshn.sh")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/lua/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/target-mips_r2_uClibc-0.9.33.2/libubox-2013-07-04/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
