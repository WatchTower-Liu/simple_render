cmake_minimum_required(VERSION 3.2)

project(render_C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(OPENCV_DIR "D:/opencv/opencv/build")

include_directories("./include")
include_directories(${OPENCV_DIR}/include/)

link_directories(${OPENCV_DIR}/x64/vc15/lib/)

AUX_SOURCE_DIRECTORY(src  SRC_DIR_VAR)
AUX_SOURCE_DIRECTORY(include  INCLUDE_DIR_VAR)

add_executable(${CMAKE_PROJECT_NAME})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE opencv_world460.lib)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${SRC_DIR_VAR} ${INCLUDE_DIR_VAR} main.cpp)
