# Install script for directory: /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/far

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opensubdiv/far" TYPE FILE PERMISSIONS OWNER_READ GROUP_READ WORLD_READ FILES
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/far/error.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/far/patchDescriptor.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/far/patchParam.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/far/patchMap.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/far/patchTable.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/far/patchTableFactory.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/far/primvarRefiner.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/far/ptexIndices.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/far/stencilTable.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/far/stencilTableFactory.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/far/topologyDescriptor.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/far/topologyLevel.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/far/topologyRefiner.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/far/topologyRefinerFactory.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/far/types.h"
    )
endif()

