LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CPP_EXTENSION := .cpp
LOCAL_CPPFLAGS := -fPIC -Wall -Wextra -DLINUX -finline-functions \
	-O3 -fno-strict-aliasing -fvisibility=hidden

LOCAL_MODULE := udt

LOCAL_SRC_FILES := \
	api.cpp \
	buffer.cpp \
	cache.cpp \
	ccc.cpp \
	channel.cpp \
	common.cpp \
	core.cpp \
	epoll.cpp \
	list.cpp \
	md5.cpp \
	packet.cpp \
	queue.cpp \
	window.cpp

#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)
