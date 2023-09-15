add_library(sayhello src/sayhello.cpp)
target_include_directories(sayhello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
message(STATUS "CMAKE CURRENT SOURCE DIR: " ${CMAKE_CURRENT_SOURCE_DIR})
