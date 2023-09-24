cmake_minimum_required(VERSION 3.16)

project(gauss_newton)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

message(STATUS "EIGEM3 INCLUDE DIR:" ${EIGEN3_INCLUDE_DIR})
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(gauss_newton ${PROJECT_SOURCE_DIR}/src/GaussNewton.cpp)

target_link_libraries(
    gauss_newton 
    ${OpenCV_LIBS}
    )