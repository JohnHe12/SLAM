cmake_minimum_required(VERSION 3.16)

project(orb_pose_estimation VERSION 1.0)

# Use debug build as recommended
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++14 -O2 ${SSE_FLAGS} -msse4")

# Have cmake create a compile database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(src)
add_subdirectory(app)




