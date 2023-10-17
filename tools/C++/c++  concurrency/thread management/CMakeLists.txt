cmake_minimum_required(VERSION 3.16)
project(concurrency)
set(CMAKE_BUILD_TYPE Debug)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)

if(COMPILER_SUPPORTS_CXX17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
message(STATUS ${CMAKE_CXX_FLAGS})
endif()

include_directories(${PROJECT_SOURCE_DIR})
link_libraries(Threads::Threads)

find_package(Threads REQUIRED)

add_executable(pass_parameters pass_parameters.cpp)
## add the error
add_executable(error1 error_for_quote.cpp)
add_executable(g thread_guard.cpp)
add_executable(j join_thread.cpp)
add_executable(join join.cpp)