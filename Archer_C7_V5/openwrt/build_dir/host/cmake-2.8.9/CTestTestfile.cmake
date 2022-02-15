# CMake generated Testfile for 
# Source directory: /home/ubuntu/Archer_C7_V5/openwrt/build_dir/host/cmake-2.8.9
# Build directory: /home/ubuntu/Archer_C7_V5/openwrt/build_dir/host/cmake-2.8.9
# 
# This file includes the relevent testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
INCLUDE("/home/ubuntu/Archer_C7_V5/openwrt/build_dir/host/cmake-2.8.9/Tests/EnforceConfig.cmake")
ADD_TEST(SystemInformationNew "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/host/cmake-2.8.9/bin/cmake" "--system-information" "-G" "Unix Makefiles")
SUBDIRS(Utilities/KWIML)
SUBDIRS(Source/kwsys)
SUBDIRS(Utilities/cmzlib)
SUBDIRS(Utilities/cmcurl)
SUBDIRS(Utilities/cmcompress)
SUBDIRS(Utilities/cmbzip2)
SUBDIRS(Utilities/cmlibarchive)
SUBDIRS(Utilities/cmexpat)
SUBDIRS(Source)
SUBDIRS(Utilities)
SUBDIRS(Tests)
SUBDIRS(Docs)
