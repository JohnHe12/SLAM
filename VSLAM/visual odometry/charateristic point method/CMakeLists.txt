cmake_minimum_required(VERSION 3.16)

project(orb_pose_estimation VERSION 1.0)

find_package(OpenCV REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(src)
add_subdirectory(app)




