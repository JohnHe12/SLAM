cmake_minimum_required(VERSION 3.0)

project(external_project)


#set(Sayhello_DIR "${CMAKE_SOURCE_DIR}/chapter_8/build")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

message(STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})
find_package(Sayhello)
include_directories(${sayhello_INCLUDE_DIR})
#find_package(Sayhello CONFIG PATHS ${CMAKE_MODULE_PATH})
# find_package(Sophus)
# find_package(OpenCV)
# if(Sophus_FOUND)

#     get_target_property(linklib Sophus::Sophus INTERFACE_LIBRARY)

#     message(${OpenCV_LIBRARYs})

#     message("PROJECT SOURCE DIR: " ${PROJECT_SOURCE_DIR})

# endif()

# if(NOT Sayhello_FOUND)
#     message(FATAL_ERROR "sayhello not found")
    
# endif()

add_executable(main main.cpp)

target_link_libraries(main ${sayhello_LIBRARY})

