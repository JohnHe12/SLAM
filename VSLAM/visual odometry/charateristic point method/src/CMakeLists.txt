set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_library(pose_estimation SHARED
bfmatch_haming.cpp
generate_descriptor.cpp
)
target_link_libraries(pose_estimation PUBLIC ${OpenCV_LIBS})