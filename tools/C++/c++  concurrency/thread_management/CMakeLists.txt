
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_libraries(Threads::Threads)

find_package(Threads REQUIRED)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/run)
add_executable(pass_parameters pass_parameters.cpp)
## add the error
add_executable(error1 error_for_quote.cpp)
add_executable(g thread_guard.cpp)
add_executable(j join_thread.cpp)
add_executable(join join.cpp)