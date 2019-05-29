# Install script for directory: /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opensubdiv" TYPE FILE PERMISSIONS OWNER_READ GROUP_READ WORLD_READ FILES "/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/version.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/media/gui2one/Work/code_playground/libs/OpenSubdiv/lib/libosdCPU.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/media/gui2one/Work/code_playground/libs/OpenSubdiv/lib/libosdGPU.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libosdCPU.so.3.3.3"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libosdCPU.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/usr/local/lib")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/lib/libosdCPU.so.3.3.3"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/lib/libosdCPU.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libosdCPU.so.3.3.3"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libosdCPU.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "::::::::::::::"
           NEW_RPATH "/usr/local/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libosdGPU.so.3.3.3"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libosdGPU.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/usr/local/lib")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/lib/libosdGPU.so.3.3.3"
    "/media/gui2one/Work/code_playground/libs/OpenSubdiv/lib/libosdGPU.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libosdGPU.so.3.3.3"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libosdGPU.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/media/gui2one/Work/code_playground/libs/OpenSubdiv/lib:"
           NEW_RPATH "/usr/local/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/tools/stringify/cmake_install.cmake")
  include("/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/hbr/cmake_install.cmake")
  include("/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc/cmake_install.cmake")
  include("/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/vtr/cmake_install.cmake")
  include("/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/far/cmake_install.cmake")
  include("/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/osd/cmake_install.cmake")

endif()

