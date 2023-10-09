set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_library(pose_estimation SHARED
bfmatch_haming.cpp
generate_descriptor.cpp
fundam.cpp
EPnP.cpp
icp.cpp
)
option(USE_CV "use distance average" OFF)
target_link_libraries(pose_estimation PUBLIC ${OpenCV_LIBS})

if(USE_CV)
target_compile_definitions(pose_estimation PUBLIC USE_CV)
message((STATUS "add use_cv"))
endif(USE_CV)