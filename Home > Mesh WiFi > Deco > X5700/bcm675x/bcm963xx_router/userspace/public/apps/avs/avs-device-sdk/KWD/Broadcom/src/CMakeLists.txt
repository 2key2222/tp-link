add_definitions("-DACSDK_LOG_MODULE=broadcomTabKeyDetector")
add_library(BROADCOM SHARED
    BroadcomTabKeyDetector.cpp)

target_include_directories(BROADCOM PUBLIC
    "${BROADCOM_TAB_KEY_DETECTOR_INCLUDE_DIR}"
	"${KWD_SOURCE_DIR}/include" 
    "${BROADCOM_SOURCE_DIR}/include")

target_link_libraries(BROADCOM KWD AVSCommon "${BROADCOM_TAB_KEY_DETECTOR_LIB_PATH}")

# install target
asdk_install()
