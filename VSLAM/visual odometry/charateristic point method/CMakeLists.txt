cmake_minimum_required(VERSION 3.16)

project(orb_pose_estimation VERSION 1.0)

# Use debug build as recommended
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++14 -O2 ${SSE_FLAGS} -msse4")

# Have cmake create a compile database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)
find_package(Sophus REQUIRED)
find_package(Eigen3 REQUIRED)

if(Sophus_FOUND)
get_target_property(Sophus_INCLUDE Sophus::Sophus INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS ${Sophus_INCLUDE})
endif()
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    "usr/include/eigen3/Eigen"
    ${EIGEN3_INCLUDE_DIR}
    ${Sophus_INCLUDE}
)
option(USE_CV_ESS "calculate the esstion matrix with opencv" OFF)
add_subdirectory(src)
add_subdirectory(app)




