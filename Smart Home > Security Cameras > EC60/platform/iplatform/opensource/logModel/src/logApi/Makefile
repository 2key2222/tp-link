#=============================================#
#TARGET: 			target file name ,if the name includes .a ,output file is static lib ,if not output file is excute file
#EXPORT_INC_FILE:	output headder file name ,only when output target is static lib its out .h file
#EXPORT_TARGET_DIR: directory of targer file
#EXPORT_INC_DIR:    directory of header files
#CFLAGS:			compile option
#LDFLAGS:			link option
#=============================================#
EXP_TARGET_DIR = ../output/libapi
EXP_INC_DIR    = ../output/libapi

#CC= gcc
TARGET = liblogApi.so
INCFILE = logApi.h
EXPORT_INC_FILE= ../inc/logApi.h
EXPORT_TARGET_DIR=$(EXP_TARGET_DIR)
EXPORT_INC_DIR=$(EXP_INC_DIR)

INC_DIR = ../inc/
#DEF_FLAGS = -DSYSV -fomit-frame-pointer  -fno-strength-reduce -DSYSLOG_INET -DSYSLOG_UNIXAF -DNO_SCCS -DFSSTND -DALLOW_KERNEL_LOGGING
#LDFLAGS += -lpthread -lubox
LDFLAGS += -luci
INC_FLAGS = -I$(INC_DIR)
CFLAGS := -Wall -O3 -s  $(INC_FLAGS)  $(DEF_FLAGS) -fpic $(CFLAGS)
INSTALL = cp -rvf 

SRCPATH:=$(shell pwd | xargs basename)
SOURCES:=$(shell find . -name "*.c" -o -name "*.cpp")
HSOURCE:=$(shell find ../inc -type f -name "*.h")
SRC_C   = $(filter-out %.cpp,$(SOURCES))
SRC_CXX = $(filter-out %.c,$(SOURCES))
OBJECTS:=$(addsuffix .o, $(basename $(SOURCES)))
OBJ_C  :=$(addsuffix .o, $(basename $(SRC_C)))
OBJ_CXX:=$(addsuffix .o, $(basename $(SRC_CXX)))

DEPS    = $(OBJECTS:.o=.d)
DEP_C	= $(OBJ_C:.o=.d)
DEP_CXX	= $(OBJ_CXX:.o=.d)

COMPILE.c   := $(CC)   $(CFLAGS) -c
COMPILE.cxx := $(CXX)  $(CXXFLAGS) -c
LINK.c      := $(CC)   $(CFLAGS)  
LINK.cxx    := $(CXX)  $(CXXFLAGS) $(LDFLAGS)

DEP_OPT = $(shell if `$(CC) --version | grep "GCC" >/dev/null`; then \
		  echo "-MM -MP"; else echo "-M"; fi )
DEPEND      = $(CC)  $(DEP_OPT)  $(CFLAGS)
DEPEND.d	=$(subst -g ,,$(DEPEND))

ifneq ($(SRC_CXX),)
	__LINK := $(LINK.cxx)
else
	__LINK := $(LINK.c)
endif

ifndef TARGET
	ERROR0 := "TARGET IS NULL!" 
	ERR_F := 1
endif

ifndef ERR_F
TARGET_IS_LIB := $(findstring .a;,$(TARGET);)
ifeq ($(TARGET_IS_LIB),)
TARGET_IS_LIB := $(findstring .so;,$(TARGET);)
TARGET_IS_SO := 1
endif
endif

ifndef ERR_F
	ifneq ($(TARGET_IS_LIB),)
		TARGET_LIB := $(TARGET)
		ifndef EXPORT_INC_FILE
			ERROR1 := "EXPORT_INC_FILE IS NULL!"
			ERR_F := 1
		endif
	endif
	ifeq ($(TARGET_IS_LIB),)
		TARGET_ELF := $(TARGET) 
	endif
endif

ifdef ERR_F
define ERROR
	$(ERROR0)
	$(ERROR1)
endef
endif

.PHONY: default clean

ifndef ERR_F
deflaut:$(TARGET_ELF) $(TARGET_LIB)
else
deflaut:
	$(error $(ERROR))
endif

ifneq ($(TARGET_IS_LIB),)
$(TARGET_LIB):$(OBJECTS)
	@echo "========= is lib:$(TARGET_LIB) =========="
ifeq ($(TARGET_IS_SO),1)
	$(CC) $(OBJECTS) -fPIC -shared -o $@ $(LDFLAGS)
else
	$(AR) -r $@ $(OBJECTS)
endif
	$(INSTALL) $(TARGET) $(EXPORT_TARGET_DIR)	
	#$(INSTALL) $(EXPORT_INC_FILE) $(EXPORT_INC_DIR)	
endif

ifeq ($(TARGET_IS_LIB),)
$(TARGET_ELF):$(OBJECTS)
	@echo "========= is exe:$(TARGET_LIB) =========="
	$(__LINK) -o $@  $(OBJECTS) $(LDFLAGS)
endif

ifndef NODEP
ifneq ($(DEPS),)
-include $(DEPS)
endif
endif

$(OBJ_C): %.o: %.c
	@echo "======== compile.c: $< -o $@ =======" 
	$(COMPILE.c) $< -o $@

$(OBJ_CXX):%.o:%.cpp
	@echo "======== compile.cpp:$(OBJ_CXX) =======" 
	$(COMPILE.cxx) $< -o $@


#$(DEP_C): %.d:%.c
#	@echo -n $(dir $<) > $@
#	@$(DEPEND.d) $< >> $@

#$(DEP_CXX): %.d:%.cpp
#	@echo -n $(dir $<) > $@
#	@$(DEPEND.d) $< >> $@




clean:	
	-$(RM) $(TARGET) $(EXP_TARGET_DIR)/$(TARGET) $(EXP_TARGET_DIR)/$(INCFILE) $(OBJECTS) $(DEPS) -rf




