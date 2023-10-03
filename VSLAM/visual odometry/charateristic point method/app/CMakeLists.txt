set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/run)
add_executable(${PROJECT_NAME} orb_pose_estimation.cpp)
target_link_libraries(${PROJECT_NAME} pose_estimation)