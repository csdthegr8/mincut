project(mincut)
SET(CMAKE_BUILD_TYPE Debug)

cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} main.cpp)
ADD_SUBDIRECTORY(MetaIO)
find_package(VTK)

include(${VTK_USE_FILE})
target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})
