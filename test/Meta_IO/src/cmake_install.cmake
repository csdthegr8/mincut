# Install script for directory: /home/sci/sdharan/mincut/test/Meta_IO/src

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/sci/sdharan/mincut/test/Meta_IO/src/libITKMetaIO.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaArrow.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaTubeGraph.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaEvent.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaVesselTube.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaMesh.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaTube.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaOutput.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaImage.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaEllipse.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaFEMObject.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaArray.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaUtils.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaITKUtils.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaCommand.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/localMetaConfiguration.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaGaussian.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaTypes.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaImageUtils.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaLandmark.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaTransform.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaObject.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaSurface.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaIOConfig.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaDTITube.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaForm.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaImageTypes.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaBlob.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaGroup.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaScene.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaLine.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaContour.h"
    "/home/sci/sdharan/mincut/test/Meta_IO/src/metaIOConfig.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")

