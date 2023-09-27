find_library(
    g2o_LIB
    NAME g2o
    PATHS "/home/john/ORB_SLAM3/Thirdparty/g2o/lib"
)
message(STATUS "G2O LIB： " ${g2o_LIB})
find_path(
    g2o_INCLUDE_DIR
    NAME g2o/core/base_vertex.h
    PATHS "/home/john/ORB_SLAM3/Thirdparty/g2o"
)

set(g2o_INCLUDE_DIR "/home/john/ORB_SLAM3/Thirdparty/g2o")

message(STATUS "g2o include dir: " ${g2o_INCLUDE_DIR})
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    g2O
    FOUND_VAR G2O_FOUND
    REQUIRED_VARS
    g2o_LIB
    g2o_INCLUDE_DIR
)