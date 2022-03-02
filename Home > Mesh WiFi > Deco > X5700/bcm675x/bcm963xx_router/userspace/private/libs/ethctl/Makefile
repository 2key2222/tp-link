LIB = libethctl.so
default: dynamic


libethctl.so:
	cp libethctl.so_$(PROFILE).save libethctl.so

dynamic: generic_private_lib_install

clean:
	rm -f libethctl.so

CURR_DIR := $(shell pwd)
BUILD_DIR := $(subst /userspace, /userspace,$(CURR_DIR))
BUILD_DIR := $(word 1, $(BUILD_DIR))
include $(BUILD_DIR)/make.common
