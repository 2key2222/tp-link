CMAKE_MINIMUM_REQUIRED(VERSION 2.1)

# Settings:
SET(CTEST_DASHBOARD_ROOT                "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/host/cmake-2.8.9/Tests/CTestTest")
SET(CTEST_SITE                          "ubuntu")
SET(CTEST_BUILD_NAME                    "CTestTest-Linux-g++-BadExe")

SET(CTEST_SOURCE_DIRECTORY              "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/host/cmake-2.8.9/Tests/CTestTestBadExe")
SET(CTEST_BINARY_DIRECTORY              "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/host/cmake-2.8.9/Tests/CTestTestBadExe")
SET(CTEST_CVS_COMMAND                   "CVSCOMMAND-NOTFOUND")
SET(CTEST_CMAKE_GENERATOR               "Unix Makefiles")
SET(CTEST_BUILD_CONFIGURATION           "$ENV{CMAKE_CONFIG_TYPE}")
SET(CTEST_COVERAGE_COMMAND              "/usr/bin/gcov")
SET(CTEST_NOTES_FILES                   "${CTEST_SCRIPT_DIRECTORY}/${CTEST_SCRIPT_NAME}")

#CTEST_EMPTY_BINARY_DIRECTORY(${CTEST_BINARY_DIRECTORY})

CTEST_START(Experimental)
CTEST_CONFIGURE(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res)
CTEST_BUILD(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res)
CTEST_TEST(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res)
