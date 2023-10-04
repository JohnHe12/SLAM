set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/run)
add_executable(${PROJECT_NAME} orb_pose_estimation.cpp)
target_link_libraries(${PROJECT_NAME} pose_estimation)

if(USE_CV_ESS)
target_compile_definitions(${PROJECT_NAME} PUBLIC USE_CV_ESS)
message(STATUS "Add cv compile defimitions")
endif(USE_CV_ESS)