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
CMAKE_SOURCE_DIR = /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1

# Include any dependencies generated for this target.
include CMakeFiles/setlbf.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/setlbf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/setlbf.dir/flags.make

CMakeFiles/setlbf.dir/service/setlbf.c.o: CMakeFiles/setlbf.dir/flags.make
CMakeFiles/setlbf.dir/service/setlbf.c.o: service/setlbf.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/setlbf.dir/service/setlbf.c.o"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/setlbf.dir/service/setlbf.c.o   -c /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1/service/setlbf.c

CMakeFiles/setlbf.dir/service/setlbf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/setlbf.dir/service/setlbf.c.i"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1/service/setlbf.c > CMakeFiles/setlbf.dir/service/setlbf.c.i

CMakeFiles/setlbf.dir/service/setlbf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/setlbf.dir/service/setlbf.c.s"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1/service/setlbf.c -o CMakeFiles/setlbf.dir/service/setlbf.c.s

# Object files for target setlbf
setlbf_OBJECTS = \
"CMakeFiles/setlbf.dir/service/setlbf.c.o"

# External object files for target setlbf
setlbf_EXTERNAL_OBJECTS =

libsetlbf.so: CMakeFiles/setlbf.dir/service/setlbf.c.o
libsetlbf.so: CMakeFiles/setlbf.dir/build.make
libsetlbf.so: CMakeFiles/setlbf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libsetlbf.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/setlbf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/setlbf.dir/build: libsetlbf.so

.PHONY : CMakeFiles/setlbf.dir/build

CMakeFiles/setlbf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/setlbf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/setlbf.dir/clean

CMakeFiles/setlbf.dir/depend:
	cd /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1 /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1 /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1 /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1 /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1/CMakeFiles/setlbf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/setlbf.dir/depend

