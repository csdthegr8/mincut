project(mincut)
SET(CMAKE_BUILD_TYPE Debug)

cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
FILE(GLOB mincut_SOURCE_FILES *.cpp)
FILE(GLOB mincut_HEADER_FILES *.h)



add_executable(${PROJECT_NAME} main.cpp)
ADD_SUBDIRECTORY(Meta_IO)

set (VTK_DIR "/home/sci/sdharan/VTK_build")
find_package(VTK)

include(${VTK_USE_FILE} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})
ADD_LIBRARY(mincutlib STATIC ${mincut_HEADER_FILES} ${mincut_SOURCE_FILES})
