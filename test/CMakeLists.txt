PROJECT (segment-image)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/")

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/include)

SET(CMAKE_CXX_FLAGS "-std=c++11" )
file( GLOB srcs *.cpp)
file( GLOB hdrs *.h)

ADD_SUBDIRECTORY(Meta_IO)

set (VTK_DIR "/home/sci/sdharan/VTK_build")
find_package(VTK)

include(${VTK_USE_FILE} REQUIRED)


ADD_EXECUTABLE(segment ${srcs} ${hdrs})
INCLUDE_DIRECTORIES(
    "/usr/local/include"
    "/usr/include"
    "/usr/local/cuda/include"
)

find_package(CUDA REQUIRED)

SET(CUDA_VERBOSE_BUILD ON CACHE BOOL "nvcc verbose" FORCE)
target_link_libraries(segment ${VTK_LIBRARIES} mincutlib gpumincut ${CUDA_LIBRARIES})
add_dependencies(segment gpumincut)

