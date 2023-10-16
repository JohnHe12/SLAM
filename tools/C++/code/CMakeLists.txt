cmake_minimum_required(VERSION 3.16)

project(code)

find_package(OpenCV REQUIRED)

# set(CMAKE_BUILD_TYPE "Release")
# #add_definitions("-DENABLE_SSE")
# set(CMAKE_CXX_FLAGS "-std=c++14 -O2 ${SSE_FLAGS} -msse4")

# add_executable(${PROJECT_NAME} const.cpp)

# add_executable(char uchar.cpp)

# add_executable(binay binary_operator.cpp)

# target_compile_definitions(binay PUBLIC ENABLE_SSE)

# add_executable(cv_mat cv_mat.cpp)
# target_link_libraries(cv_mat ${OpenCV_LIBS})

# add_executable(for_loop for_loop.cpp)

# add_executable(cv_norm cv_norm.cpp)
# target_link_libraries(cv_norm ${OpenCV_LIBS})

# add_executable(depth depth_imread.cpp)
# target_link_libraries(depth ${OpenCV_LIBS})

add_executable(rng cv_rng_uniform.cpp)
target_link_libraries(rng ${OpenCV_LIBS})