cmake_minimum_required(VERSION 2.8)

find_package(CUDA)

CUDA_INCLUDE_DIRECTORIES(
  "${CMAKE_CURRENT_SOURCE_DIR}"
  )


list(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35)

CUDA_ADD_LIBRARY(gpumincut driver.cu driver.h SHARED)
ADD_DEPENDENCIES(gpumincut mincutlib)


FILE(GLOB Parallel_API_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

SET(Parallel_INSTALLED_HEADER_FILES)
FOREACH(header_file ${Parallel_API_HEADER_FILES})
  GET_FILENAME_COMPONENT(file_no_path "${header_file}" NAME)
  CONFIGURE_FILE("${header_file}"
    "${CMAKE_BINARY_DIR}/include/${file_no_path}" COPYONLY IMMEDIATE)
  SET(Parallel_INSTALLED_HEADER_FILES
    ${Parallel_INSTALLED_HEADER_FILES}
    "${CMAKE_BINARY_DIR}/include/${file_no_path}")
ENDFOREACH(header_file)

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/include)

