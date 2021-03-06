IF(NOT EXISTS "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/host/cmake-2.8.9/install_manifest.txt")
  MESSAGE(FATAL_ERROR "Cannot find install manifest: \"/home/ubuntu/Archer_C7_V5/openwrt/build_dir/host/cmake-2.8.9/install_manifest.txt\"")
ENDIF(NOT EXISTS "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/host/cmake-2.8.9/install_manifest.txt")

FILE(READ "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/host/cmake-2.8.9/install_manifest.txt" files)
STRING(REGEX REPLACE "\n" ";" files "${files}")
FOREACH(file ${files})
  MESSAGE(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  IF(EXISTS "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM(
      "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/host/cmake-2.8.9/Bootstrap.cmk/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )
    IF("${rm_retval}" STREQUAL 0)
    ELSE("${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    ENDIF("${rm_retval}" STREQUAL 0)
  ELSE(EXISTS "$ENV{DESTDIR}${file}")
    MESSAGE(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  ENDIF(EXISTS "$ENV{DESTDIR}${file}")
ENDFOREACH(file)
