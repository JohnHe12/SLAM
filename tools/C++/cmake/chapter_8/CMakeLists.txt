cmake_minimum_required(VERSION 2.8)

project(install_hello)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 11)

# Set compiler specific settings (FixMe: Should not cmake do this for us automatically?)
IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
   SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")
   SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra  -Wno-deprecated-register -Qunused-arguments -fcolor-diagnostics")
ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
   SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")
   SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -std=c++11 -Wno-deprecated-declarations -ftemplate-backtrace-limit=0")
   SET(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG} --coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
   SET(CMAKE_EXE_LINKER_FLAGS_COVERAGE "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --coverage")
   SET(CMAKE_SHARED_LINKER_FLAGS_COVERAGE "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} --coverage")
ELSEIF(CMAKE_CXX_COMPILER_ID MATCHES "^MSVC$")
   ADD_DEFINITIONS("-D _USE_MATH_DEFINES /bigobj /wd4305 /wd4244 /MP")
ENDIF()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")

add_library(sayhello ${CMAKE_SOURCE_DIR}/src/sayhello.cpp)

message(STATUS "CMAKE SOURCE DIR: " ${CMAKE_SOURCE_DIR})

add_executable(hello hello_slam.cpp)

# Because after install the project the path is not same as the
# build.
target_include_directories(sayhello PUBLIC #${CMAKE_SOURCE_DIR}/include)

$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>

$<INSTALL_INTERFACE:include>)

target_link_libraries(hello sayhello)

install(FILES ${CMAKE_SOURCE_DIR}/include/hello.h
        DESTINATION include
)

#we need a <packagename>Targets.cmake
install(
    TARGETS sayhello

    DESTINATION lib

    EXPORT SayhelloTargets
)

install(
    EXPORT SayhelloTargets

    FILE SayhelloTargets.cmake
    
    DESTINATION lib/cmake/sayhello
    )

# create a <packagename>-Config.cmake

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/SayhelloConfig.cmake
    INSTALL_DESTINATION lib/cmake/example
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/SayhelloConfig.cmake
    DESTINATION lib/cmake/sayhello
)

# without install can import the project
export(
    EXPORT SayhelloTargets

    FILE ${CMAKE_BINARY_DIR}/SayhelloTargets.cmake
)