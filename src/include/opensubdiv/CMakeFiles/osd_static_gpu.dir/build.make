# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/gui2one/Work/code_playground/libs/OpenSubdiv

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/gui2one/Work/code_playground/libs/OpenSubdiv

# Include any dependencies generated for this target.
include opensubdiv/CMakeFiles/osd_static_gpu.dir/depend.make

# Include the progress variables for this target.
include opensubdiv/CMakeFiles/osd_static_gpu.dir/progress.make

# Include the compile flags for this target's objects.
include opensubdiv/CMakeFiles/osd_static_gpu.dir/flags.make

opensubdiv/CMakeFiles/osd_static_gpu.dir/version.cpp.o: opensubdiv/CMakeFiles/osd_static_gpu.dir/flags.make
opensubdiv/CMakeFiles/osd_static_gpu.dir/version.cpp.o: opensubdiv/version.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/gui2one/Work/code_playground/libs/OpenSubdiv/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object opensubdiv/CMakeFiles/osd_static_gpu.dir/version.cpp.o"
	cd /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/osd_static_gpu.dir/version.cpp.o -c /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/version.cpp

opensubdiv/CMakeFiles/osd_static_gpu.dir/version.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/osd_static_gpu.dir/version.cpp.i"
	cd /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/version.cpp > CMakeFiles/osd_static_gpu.dir/version.cpp.i

opensubdiv/CMakeFiles/osd_static_gpu.dir/version.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/osd_static_gpu.dir/version.cpp.s"
	cd /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/version.cpp -o CMakeFiles/osd_static_gpu.dir/version.cpp.s

opensubdiv/CMakeFiles/osd_static_gpu.dir/version.cpp.o.requires:

.PHONY : opensubdiv/CMakeFiles/osd_static_gpu.dir/version.cpp.o.requires

opensubdiv/CMakeFiles/osd_static_gpu.dir/version.cpp.o.provides: opensubdiv/CMakeFiles/osd_static_gpu.dir/version.cpp.o.requires
	$(MAKE) -f opensubdiv/CMakeFiles/osd_static_gpu.dir/build.make opensubdiv/CMakeFiles/osd_static_gpu.dir/version.cpp.o.provides.build
.PHONY : opensubdiv/CMakeFiles/osd_static_gpu.dir/version.cpp.o.provides

opensubdiv/CMakeFiles/osd_static_gpu.dir/version.cpp.o.provides.build: opensubdiv/CMakeFiles/osd_static_gpu.dir/version.cpp.o


# Object files for target osd_static_gpu
osd_static_gpu_OBJECTS = \
"CMakeFiles/osd_static_gpu.dir/version.cpp.o"

# External object files for target osd_static_gpu
osd_static_gpu_EXTERNAL_OBJECTS = \
"/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/osd/CMakeFiles/osd_gpu_obj.dir/cpuGLVertexBuffer.cpp.o" \
"/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/osd/CMakeFiles/osd_gpu_obj.dir/glLegacyGregoryPatchTable.cpp.o" \
"/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/osd/CMakeFiles/osd_gpu_obj.dir/glPatchTable.cpp.o" \
"/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/osd/CMakeFiles/osd_gpu_obj.dir/glVertexBuffer.cpp.o" \
"/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/osd/CMakeFiles/osd_gpu_obj.dir/glslPatchShaderSource.cpp.o" \
"/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/osd/CMakeFiles/osd_gpu_obj.dir/glXFBEvaluator.cpp.o" \
"/media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/osd/CMakeFiles/osd_gpu_obj.dir/glComputeEvaluator.cpp.o"

lib/libosdGPU.a: opensubdiv/CMakeFiles/osd_static_gpu.dir/version.cpp.o
lib/libosdGPU.a: opensubdiv/osd/CMakeFiles/osd_gpu_obj.dir/cpuGLVertexBuffer.cpp.o
lib/libosdGPU.a: opensubdiv/osd/CMakeFiles/osd_gpu_obj.dir/glLegacyGregoryPatchTable.cpp.o
lib/libosdGPU.a: opensubdiv/osd/CMakeFiles/osd_gpu_obj.dir/glPatchTable.cpp.o
lib/libosdGPU.a: opensubdiv/osd/CMakeFiles/osd_gpu_obj.dir/glVertexBuffer.cpp.o
lib/libosdGPU.a: opensubdiv/osd/CMakeFiles/osd_gpu_obj.dir/glslPatchShaderSource.cpp.o
lib/libosdGPU.a: opensubdiv/osd/CMakeFiles/osd_gpu_obj.dir/glXFBEvaluator.cpp.o
lib/libosdGPU.a: opensubdiv/osd/CMakeFiles/osd_gpu_obj.dir/glComputeEvaluator.cpp.o
lib/libosdGPU.a: opensubdiv/CMakeFiles/osd_static_gpu.dir/build.make
lib/libosdGPU.a: opensubdiv/CMakeFiles/osd_static_gpu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/gui2one/Work/code_playground/libs/OpenSubdiv/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../lib/libosdGPU.a"
	cd /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv && $(CMAKE_COMMAND) -P CMakeFiles/osd_static_gpu.dir/cmake_clean_target.cmake
	cd /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/osd_static_gpu.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
opensubdiv/CMakeFiles/osd_static_gpu.dir/build: lib/libosdGPU.a

.PHONY : opensubdiv/CMakeFiles/osd_static_gpu.dir/build

opensubdiv/CMakeFiles/osd_static_gpu.dir/requires: opensubdiv/CMakeFiles/osd_static_gpu.dir/version.cpp.o.requires

.PHONY : opensubdiv/CMakeFiles/osd_static_gpu.dir/requires

opensubdiv/CMakeFiles/osd_static_gpu.dir/clean:
	cd /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv && $(CMAKE_COMMAND) -P CMakeFiles/osd_static_gpu.dir/cmake_clean.cmake
.PHONY : opensubdiv/CMakeFiles/osd_static_gpu.dir/clean

opensubdiv/CMakeFiles/osd_static_gpu.dir/depend:
	cd /media/gui2one/Work/code_playground/libs/OpenSubdiv && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/gui2one/Work/code_playground/libs/OpenSubdiv /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv /media/gui2one/Work/code_playground/libs/OpenSubdiv /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/CMakeFiles/osd_static_gpu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : opensubdiv/CMakeFiles/osd_static_gpu.dir/depend

