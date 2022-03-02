if(NOT "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/host/cmake-3.13.2/Tests/CMakeTests" MATCHES "^/")
  set(slash /)
endif()
set(url "file://${slash}/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/host/cmake-3.13.2/Tests/CMakeTests/FileDownloadInput.png")
set(dir "/home/ubuntu/tp-link/GPL_X5700_1/iplatform/build_dir/host/cmake-3.13.2/Tests/CMakeTests/downloads")

file(DOWNLOAD
  ${url}
  ${dir}/file3.png
  TIMEOUT 2
  STATUS status
  EXPECTED_HASH SHA1=5555555555555555555555555555555555555555
  )
