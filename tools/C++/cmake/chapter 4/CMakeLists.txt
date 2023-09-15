cmake_minimum_required(VERSION 2.8)

# project name
project(hello_slam)

# give some Variables such as version
set(hello_slam_VERSION_MAJOR 1)
set(hello_slam_VERSION_MINOR 0)
set(hello_slam_VERSION "${hello_slam_VERSION_MAJOR}.${hello_slam_VERSION_MINOR}")

# create the header file 
configure_file(ver.h.in ${CMAKE_BINARY_DIR}/ver.h)
configure_file(path.h.in ${CMAKE_BINARY_DIR}/path.h @ONLY)

# create the excutable procedure
add_executable(hello hello_slam.cpp)

#target connect the header file
target_include_directories(hello PUBLIC ${CMAKE_BINARY_DIR})