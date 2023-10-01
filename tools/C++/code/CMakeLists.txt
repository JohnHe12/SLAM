cmake_minimum_required(VERSION 3.16)

project(code)

find_package(OpenCV REQUIRED)

set(CMAKE_BUILD_TYPE "Release")
#add_definitions("-DENABLE_SSE")
set(CMAKE_CXX_FLAGS "-std=c++14 -O2 ${SSE_FLAGS} -msse4")

add_executable(${PROJECT_NAME} const.cpp)

add_executable(char uchar.cpp)

add_executable(binay binary_operator.cpp)

target_compile_definitions(binay PUBLIC ENABLE_SSE)

add_executable(cv_mat cv_mat.cpp)
target_link_libraries(cv_mat ${OpenCV_LIBS})
