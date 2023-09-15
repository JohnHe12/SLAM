# tell the cmake version
cmake_minimum_required(VERSION 2.8)

# tell the project name
project(hello_slam)

add_library(sayhello say_hello.cpp)

message(STATUS "PROJECT SOURCE DIR: " ${PROJECT_SOURCE_DIR})
#include_directories("./include")
set(TARGET_T sayhello)
# add the code you use
add_executable(hello hello_slam.cpp)
#list(APPEND T hello)
target_include_directories(sayhello PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(hello sayhello)