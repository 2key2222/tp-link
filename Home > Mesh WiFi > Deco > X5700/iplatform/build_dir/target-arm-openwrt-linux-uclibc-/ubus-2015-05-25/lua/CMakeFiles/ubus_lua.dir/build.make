# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/ubuntu/tp-link/GPL_X5700_1/iplatform/staging_dir/host/bin/cmake

# The command to remove a file.
RM = /home/ubuntu/tp-link/GPL_X5700_1/iplatform/staging_dir/host/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25

# Include any dependencies generated for this target.
include lua/CMakeFiles/ubus_lua.dir/depend.make

# Include the progress variables for this target.
include lua/CMakeFiles/ubus_lua.dir/progress.make

# Include the compile flags for this target's objects.
include lua/CMakeFiles/ubus_lua.dir/flags.make

lua/CMakeFiles/ubus_lua.dir/ubus.c.o: lua/CMakeFiles/ubus_lua.dir/flags.make
lua/CMakeFiles/ubus_lua.dir/ubus.c.o: lua/ubus.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lua/CMakeFiles/ubus_lua.dir/ubus.c.o"
	cd /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25/lua && /home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ubus_lua.dir/ubus.c.o   -c /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25/lua/ubus.c

lua/CMakeFiles/ubus_lua.dir/ubus.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ubus_lua.dir/ubus.c.i"
	cd /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25/lua && /home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25/lua/ubus.c > CMakeFiles/ubus_lua.dir/ubus.c.i

lua/CMakeFiles/ubus_lua.dir/ubus.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ubus_lua.dir/ubus.c.s"
	cd /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25/lua && /home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25/lua/ubus.c -o CMakeFiles/ubus_lua.dir/ubus.c.s

# Object files for target ubus_lua
ubus_lua_OBJECTS = \
"CMakeFiles/ubus_lua.dir/ubus.c.o"

# External object files for target ubus_lua
ubus_lua_EXTERNAL_OBJECTS =

lua/ubus.so: lua/CMakeFiles/ubus_lua.dir/ubus.c.o
lua/ubus.so: lua/CMakeFiles/ubus_lua.dir/build.make
lua/ubus.so: libubus.so
lua/ubus.so: lua/CMakeFiles/ubus_lua.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared module ubus.so"
	cd /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25/lua && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ubus_lua.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lua/CMakeFiles/ubus_lua.dir/build: lua/ubus.so

.PHONY : lua/CMakeFiles/ubus_lua.dir/build

lua/CMakeFiles/ubus_lua.dir/clean:
	cd /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25/lua && $(CMAKE_COMMAND) -P CMakeFiles/ubus_lua.dir/cmake_clean.cmake
.PHONY : lua/CMakeFiles/ubus_lua.dir/clean

lua/CMakeFiles/ubus_lua.dir/depend:
	cd /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25 /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25/lua /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25 /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25/lua /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/ubus-2015-05-25/lua/CMakeFiles/ubus_lua.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lua/CMakeFiles/ubus_lua.dir/depend

