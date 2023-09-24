find_library(
    sayhello_LIBRARY
    NAMES sayhello
    PATHS "/home/john/SLAM/tools/C++/cmake/chapter 7/chapter_8/build"
)

find_path(sayhello_INCLUDE_DIR
  NAMES hello.h
  PATHS "/home/john/SLAM/tools/C++/cmake/chapter 7/chapter_8/include"
  
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Sayhello
  FOUND_VAR Sayhello_FOUND
  REQUIRED_VARS
  sayhello_LIBRARY
  sayhello_INCLUDE_DIR
)