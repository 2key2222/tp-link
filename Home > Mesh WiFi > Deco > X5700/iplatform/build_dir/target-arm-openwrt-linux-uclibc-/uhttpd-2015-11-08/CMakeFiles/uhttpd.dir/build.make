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
CMAKE_SOURCE_DIR = /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08

# Include any dependencies generated for this target.
include CMakeFiles/uhttpd.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/uhttpd.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/uhttpd.dir/flags.make

CMakeFiles/uhttpd.dir/main.c.o: CMakeFiles/uhttpd.dir/flags.make
CMakeFiles/uhttpd.dir/main.c.o: main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/uhttpd.dir/main.c.o"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/uhttpd.dir/main.c.o   -c /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/main.c

CMakeFiles/uhttpd.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/uhttpd.dir/main.c.i"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/main.c > CMakeFiles/uhttpd.dir/main.c.i

CMakeFiles/uhttpd.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/uhttpd.dir/main.c.s"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/main.c -o CMakeFiles/uhttpd.dir/main.c.s

CMakeFiles/uhttpd.dir/listen.c.o: CMakeFiles/uhttpd.dir/flags.make
CMakeFiles/uhttpd.dir/listen.c.o: listen.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/uhttpd.dir/listen.c.o"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/uhttpd.dir/listen.c.o   -c /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/listen.c

CMakeFiles/uhttpd.dir/listen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/uhttpd.dir/listen.c.i"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/listen.c > CMakeFiles/uhttpd.dir/listen.c.i

CMakeFiles/uhttpd.dir/listen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/uhttpd.dir/listen.c.s"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/listen.c -o CMakeFiles/uhttpd.dir/listen.c.s

CMakeFiles/uhttpd.dir/client.c.o: CMakeFiles/uhttpd.dir/flags.make
CMakeFiles/uhttpd.dir/client.c.o: client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/uhttpd.dir/client.c.o"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/uhttpd.dir/client.c.o   -c /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/client.c

CMakeFiles/uhttpd.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/uhttpd.dir/client.c.i"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/client.c > CMakeFiles/uhttpd.dir/client.c.i

CMakeFiles/uhttpd.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/uhttpd.dir/client.c.s"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/client.c -o CMakeFiles/uhttpd.dir/client.c.s

CMakeFiles/uhttpd.dir/utils.c.o: CMakeFiles/uhttpd.dir/flags.make
CMakeFiles/uhttpd.dir/utils.c.o: utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/uhttpd.dir/utils.c.o"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/uhttpd.dir/utils.c.o   -c /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/utils.c

CMakeFiles/uhttpd.dir/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/uhttpd.dir/utils.c.i"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/utils.c > CMakeFiles/uhttpd.dir/utils.c.i

CMakeFiles/uhttpd.dir/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/uhttpd.dir/utils.c.s"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/utils.c -o CMakeFiles/uhttpd.dir/utils.c.s

CMakeFiles/uhttpd.dir/file.c.o: CMakeFiles/uhttpd.dir/flags.make
CMakeFiles/uhttpd.dir/file.c.o: file.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/uhttpd.dir/file.c.o"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/uhttpd.dir/file.c.o   -c /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/file.c

CMakeFiles/uhttpd.dir/file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/uhttpd.dir/file.c.i"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/file.c > CMakeFiles/uhttpd.dir/file.c.i

CMakeFiles/uhttpd.dir/file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/uhttpd.dir/file.c.s"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/file.c -o CMakeFiles/uhttpd.dir/file.c.s

CMakeFiles/uhttpd.dir/auth.c.o: CMakeFiles/uhttpd.dir/flags.make
CMakeFiles/uhttpd.dir/auth.c.o: auth.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/uhttpd.dir/auth.c.o"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/uhttpd.dir/auth.c.o   -c /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/auth.c

CMakeFiles/uhttpd.dir/auth.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/uhttpd.dir/auth.c.i"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/auth.c > CMakeFiles/uhttpd.dir/auth.c.i

CMakeFiles/uhttpd.dir/auth.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/uhttpd.dir/auth.c.s"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/auth.c -o CMakeFiles/uhttpd.dir/auth.c.s

CMakeFiles/uhttpd.dir/cgi.c.o: CMakeFiles/uhttpd.dir/flags.make
CMakeFiles/uhttpd.dir/cgi.c.o: cgi.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/uhttpd.dir/cgi.c.o"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/uhttpd.dir/cgi.c.o   -c /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/cgi.c

CMakeFiles/uhttpd.dir/cgi.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/uhttpd.dir/cgi.c.i"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/cgi.c > CMakeFiles/uhttpd.dir/cgi.c.i

CMakeFiles/uhttpd.dir/cgi.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/uhttpd.dir/cgi.c.s"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/cgi.c -o CMakeFiles/uhttpd.dir/cgi.c.s

CMakeFiles/uhttpd.dir/relay.c.o: CMakeFiles/uhttpd.dir/flags.make
CMakeFiles/uhttpd.dir/relay.c.o: relay.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/uhttpd.dir/relay.c.o"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/uhttpd.dir/relay.c.o   -c /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/relay.c

CMakeFiles/uhttpd.dir/relay.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/uhttpd.dir/relay.c.i"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/relay.c > CMakeFiles/uhttpd.dir/relay.c.i

CMakeFiles/uhttpd.dir/relay.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/uhttpd.dir/relay.c.s"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/relay.c -o CMakeFiles/uhttpd.dir/relay.c.s

CMakeFiles/uhttpd.dir/proc.c.o: CMakeFiles/uhttpd.dir/flags.make
CMakeFiles/uhttpd.dir/proc.c.o: proc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/uhttpd.dir/proc.c.o"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/uhttpd.dir/proc.c.o   -c /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/proc.c

CMakeFiles/uhttpd.dir/proc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/uhttpd.dir/proc.c.i"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/proc.c > CMakeFiles/uhttpd.dir/proc.c.i

CMakeFiles/uhttpd.dir/proc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/uhttpd.dir/proc.c.s"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/proc.c -o CMakeFiles/uhttpd.dir/proc.c.s

CMakeFiles/uhttpd.dir/plugin.c.o: CMakeFiles/uhttpd.dir/flags.make
CMakeFiles/uhttpd.dir/plugin.c.o: plugin.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/uhttpd.dir/plugin.c.o"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/uhttpd.dir/plugin.c.o   -c /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/plugin.c

CMakeFiles/uhttpd.dir/plugin.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/uhttpd.dir/plugin.c.i"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/plugin.c > CMakeFiles/uhttpd.dir/plugin.c.i

CMakeFiles/uhttpd.dir/plugin.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/uhttpd.dir/plugin.c.s"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/plugin.c -o CMakeFiles/uhttpd.dir/plugin.c.s

CMakeFiles/uhttpd.dir/handler.c.o: CMakeFiles/uhttpd.dir/flags.make
CMakeFiles/uhttpd.dir/handler.c.o: handler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/uhttpd.dir/handler.c.o"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/uhttpd.dir/handler.c.o   -c /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/handler.c

CMakeFiles/uhttpd.dir/handler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/uhttpd.dir/handler.c.i"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/handler.c > CMakeFiles/uhttpd.dir/handler.c.i

CMakeFiles/uhttpd.dir/handler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/uhttpd.dir/handler.c.s"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/handler.c -o CMakeFiles/uhttpd.dir/handler.c.s

CMakeFiles/uhttpd.dir/tls.c.o: CMakeFiles/uhttpd.dir/flags.make
CMakeFiles/uhttpd.dir/tls.c.o: tls.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/uhttpd.dir/tls.c.o"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/uhttpd.dir/tls.c.o   -c /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/tls.c

CMakeFiles/uhttpd.dir/tls.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/uhttpd.dir/tls.c.i"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/tls.c > CMakeFiles/uhttpd.dir/tls.c.i

CMakeFiles/uhttpd.dir/tls.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/uhttpd.dir/tls.c.s"
	/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/tls.c -o CMakeFiles/uhttpd.dir/tls.c.s

# Object files for target uhttpd
uhttpd_OBJECTS = \
"CMakeFiles/uhttpd.dir/main.c.o" \
"CMakeFiles/uhttpd.dir/listen.c.o" \
"CMakeFiles/uhttpd.dir/client.c.o" \
"CMakeFiles/uhttpd.dir/utils.c.o" \
"CMakeFiles/uhttpd.dir/file.c.o" \
"CMakeFiles/uhttpd.dir/auth.c.o" \
"CMakeFiles/uhttpd.dir/cgi.c.o" \
"CMakeFiles/uhttpd.dir/relay.c.o" \
"CMakeFiles/uhttpd.dir/proc.c.o" \
"CMakeFiles/uhttpd.dir/plugin.c.o" \
"CMakeFiles/uhttpd.dir/handler.c.o" \
"CMakeFiles/uhttpd.dir/tls.c.o"

# External object files for target uhttpd
uhttpd_EXTERNAL_OBJECTS =

uhttpd: CMakeFiles/uhttpd.dir/main.c.o
uhttpd: CMakeFiles/uhttpd.dir/listen.c.o
uhttpd: CMakeFiles/uhttpd.dir/client.c.o
uhttpd: CMakeFiles/uhttpd.dir/utils.c.o
uhttpd: CMakeFiles/uhttpd.dir/file.c.o
uhttpd: CMakeFiles/uhttpd.dir/auth.c.o
uhttpd: CMakeFiles/uhttpd.dir/cgi.c.o
uhttpd: CMakeFiles/uhttpd.dir/relay.c.o
uhttpd: CMakeFiles/uhttpd.dir/proc.c.o
uhttpd: CMakeFiles/uhttpd.dir/plugin.c.o
uhttpd: CMakeFiles/uhttpd.dir/handler.c.o
uhttpd: CMakeFiles/uhttpd.dir/tls.c.o
uhttpd: CMakeFiles/uhttpd.dir/build.make
uhttpd: /home/ubuntu/tp-link/GPL_X5700_1/iplatform/staging_dir/target-arm-openwrt-linux-uclibc-/usr/lib/libjson-c.so
uhttpd: CMakeFiles/uhttpd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking C executable uhttpd"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/uhttpd.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/uhttpd.dir/build: uhttpd

.PHONY : CMakeFiles/uhttpd.dir/build

CMakeFiles/uhttpd.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/uhttpd.dir/cmake_clean.cmake
.PHONY : CMakeFiles/uhttpd.dir/clean

CMakeFiles/uhttpd.dir/depend:
	cd /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08 /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08 /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08 /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08 /home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/target-arm-openwrt-linux-uclibc-/uhttpd-2015-11-08/CMakeFiles/uhttpd.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/uhttpd.dir/depend

