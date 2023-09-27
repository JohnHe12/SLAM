cmake_minimum_required(VERSION 3.16)

project(g2o_curve)


find_package(OpenCV REQUIRED)

find_package(Eigen3 REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(g2o)

if(NOT G2O_FOUND)
    message(FATAL_ERROR "can not find g2o")
endif()

include_directories(
    ${EIGEN3_INCLUDE_DIR}
    ${g2o_INCLUDE_DIR}
)

add_executable(${PROJECT_NAME} g2oCurveFitting.cpp)

target_link_libraries(
    ${PROJECT_NAME}
    ${OpenCV_LIBS}
    ${g2o_LIB}
)