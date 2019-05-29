# Install script for directory: /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opensubdiv/sdc" TYPE FILE PERMISSIONS OWNER_READ GROUP_READ WORLD_READ FILES
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc/bilinearScheme.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc/catmarkScheme.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc/crease.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc/loopScheme.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc/options.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc/scheme.h"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc/types.h"
    )
endif()

