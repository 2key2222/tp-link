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

# Utility rule file for syscall-names-h.

# Include the progress variables for this target.
include CMakeFiles/syscall-names-h.dir/progress.make

CMakeFiles/syscall-names-h: syscall-names.h


syscall-names.h: ./make_syscall_h.sh
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating syscall-names.h"
	./make_syscall_h.sh /home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc > ./syscall-names.h

syscall-names-h: CMakeFiles/syscall-names-h
syscall-names-h: syscall-names.h
syscall-names-h: CMakeFiles/syscall-names-h.dir/build.make

.PHONY : syscall-names-h

# Rule to build all files generated by this target.
CMakeFiles/syscall-names-h.dir/build: syscall-names-h

.PHONY : CMakeFiles/syscall-names-h.dir/build

CMakeFiles/syscall-names-h.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/syscall-names-h.dir/cmake_clean.cmake
.PHONY : CMakeFiles/syscall-names-h.dir/clean

CMakeFiles/syscall-names-h.dir/depend:
	cd /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1 /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1 /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1 /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1 /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/procd-2015-10-29.1/CMakeFiles/syscall-names-h.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/syscall-names-h.dir/depend

