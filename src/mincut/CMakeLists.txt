project(mincutlib)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


file(GLOB mincut_SOURCE_FILES *.cpp)

FILE(GLOB mincut_HEADER_FILES *.h)

SET(mincut_API_HEADER_FILES graph.h)

SET(mincut_INSTALLED_HEADER_FILES)


FOREACH(header_file ${mincut_API_HEADER_FILES})
  # When debugging, uncomment this line                                                                                                               
  MESSAGE(STATUS "Copy header file: ${header_file}")                                                                                                 
  GET_FILENAME_COMPONENT(file_no_path "${header_file}" NAME)
  CONFIGURE_FILE("${header_file}"
    "${CMAKE_BINARY_DIR}/include/${file_no_path}" COPYONLY IMMEDIATE)
  SET(Cleaver_INSTALLED_HEADER_FILES
    ${Cleaver_INSTALLED_HEADER_FILES}
    "${CMAKE_BINARY_DIR}/include/${file_no_path}")
ENDFOREACH(header_file)

# output library                                                                                                                                      
ADD_LIBRARY(mincutlib STATIC ${mincut_HEADER_FILES} ${mincut_SOURCE_FILES})
#add_dependencies(mincutlib )

