project(MINCUT)
SET(CMAKE_BUILD_TYPE Debug)

ADD_SUBDIRECTORY(src/mincut)
ADD_SUBDIRECTORY(src/parallel)
ADD_SUBDIRECTORY(test)



# cmake_minimum_required(VERSION 2.8)
# aux_source_directory(. SRC_LIST)
# FILE(GLOB mincut_SOURCE_FILES *.cpp)
# FILE(GLOB mincut_HEADER_FILES *.h)
# SET(CMAKE_CXX_FLAGS "-std=c++11" )

# ADD_SUBDIRECTORY(Meta_IO)

# # packages                                                                                                                                                                                                 
# find_package(CUDA)

# # nvcc flags                                                                                                                                                                                               
# set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS} -gencode arch=compute_30,code=sm_30)

# SET(LIB_TYPE STATIC)
# CUDA_ADD_LIBRARY(driverlib ${LIB_TYPE} driver.h driver.cu)


# set (VTK_DIR "/home/sci/sdharan/VTK_build")
# find_package(VTK)

# include(${VTK_USE_FILE} REQUIRED)

# add_executable(${PROJECT_NAME} main.cpp)
# #ADD_DEPENDENCIES(${PROJECT_NAME} driverlib)
# #TARGET_LINK_LIBRARIES(${PROJECT_NAME} driverlib)
# ADD_LIBRARY(mincutlib STATIC ${mincut_HEADER_FILES} ${mincut_SOURCE_FILES})
# #add_dependencies(${PROJECT_NAME} driverlib)
# target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES} mincutlib driverlib)


