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
include opensubdiv/sdc/CMakeFiles/sdc_obj.dir/depend.make

# Include the progress variables for this target.
include opensubdiv/sdc/CMakeFiles/sdc_obj.dir/progress.make

# Include the compile flags for this target's objects.
include opensubdiv/sdc/CMakeFiles/sdc_obj.dir/flags.make

opensubdiv/sdc/CMakeFiles/sdc_obj.dir/crease.cpp.o: opensubdiv/sdc/CMakeFiles/sdc_obj.dir/flags.make
opensubdiv/sdc/CMakeFiles/sdc_obj.dir/crease.cpp.o: opensubdiv/sdc/crease.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/gui2one/Work/code_playground/libs/OpenSubdiv/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object opensubdiv/sdc/CMakeFiles/sdc_obj.dir/crease.cpp.o"
	cd /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sdc_obj.dir/crease.cpp.o -c /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc/crease.cpp

opensubdiv/sdc/CMakeFiles/sdc_obj.dir/crease.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdc_obj.dir/crease.cpp.i"
	cd /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc/crease.cpp > CMakeFiles/sdc_obj.dir/crease.cpp.i

opensubdiv/sdc/CMakeFiles/sdc_obj.dir/crease.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdc_obj.dir/crease.cpp.s"
	cd /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc/crease.cpp -o CMakeFiles/sdc_obj.dir/crease.cpp.s

opensubdiv/sdc/CMakeFiles/sdc_obj.dir/crease.cpp.o.requires:

.PHONY : opensubdiv/sdc/CMakeFiles/sdc_obj.dir/crease.cpp.o.requires

opensubdiv/sdc/CMakeFiles/sdc_obj.dir/crease.cpp.o.provides: opensubdiv/sdc/CMakeFiles/sdc_obj.dir/crease.cpp.o.requires
	$(MAKE) -f opensubdiv/sdc/CMakeFiles/sdc_obj.dir/build.make opensubdiv/sdc/CMakeFiles/sdc_obj.dir/crease.cpp.o.provides.build
.PHONY : opensubdiv/sdc/CMakeFiles/sdc_obj.dir/crease.cpp.o.provides

opensubdiv/sdc/CMakeFiles/sdc_obj.dir/crease.cpp.o.provides.build: opensubdiv/sdc/CMakeFiles/sdc_obj.dir/crease.cpp.o


opensubdiv/sdc/CMakeFiles/sdc_obj.dir/typeTraits.cpp.o: opensubdiv/sdc/CMakeFiles/sdc_obj.dir/flags.make
opensubdiv/sdc/CMakeFiles/sdc_obj.dir/typeTraits.cpp.o: opensubdiv/sdc/typeTraits.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/gui2one/Work/code_playground/libs/OpenSubdiv/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object opensubdiv/sdc/CMakeFiles/sdc_obj.dir/typeTraits.cpp.o"
	cd /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sdc_obj.dir/typeTraits.cpp.o -c /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc/typeTraits.cpp

opensubdiv/sdc/CMakeFiles/sdc_obj.dir/typeTraits.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdc_obj.dir/typeTraits.cpp.i"
	cd /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc/typeTraits.cpp > CMakeFiles/sdc_obj.dir/typeTraits.cpp.i

opensubdiv/sdc/CMakeFiles/sdc_obj.dir/typeTraits.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdc_obj.dir/typeTraits.cpp.s"
	cd /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc/typeTraits.cpp -o CMakeFiles/sdc_obj.dir/typeTraits.cpp.s

opensubdiv/sdc/CMakeFiles/sdc_obj.dir/typeTraits.cpp.o.requires:

.PHONY : opensubdiv/sdc/CMakeFiles/sdc_obj.dir/typeTraits.cpp.o.requires

opensubdiv/sdc/CMakeFiles/sdc_obj.dir/typeTraits.cpp.o.provides: opensubdiv/sdc/CMakeFiles/sdc_obj.dir/typeTraits.cpp.o.requires
	$(MAKE) -f opensubdiv/sdc/CMakeFiles/sdc_obj.dir/build.make opensubdiv/sdc/CMakeFiles/sdc_obj.dir/typeTraits.cpp.o.provides.build
.PHONY : opensubdiv/sdc/CMakeFiles/sdc_obj.dir/typeTraits.cpp.o.provides

opensubdiv/sdc/CMakeFiles/sdc_obj.dir/typeTraits.cpp.o.provides.build: opensubdiv/sdc/CMakeFiles/sdc_obj.dir/typeTraits.cpp.o


sdc_obj: opensubdiv/sdc/CMakeFiles/sdc_obj.dir/crease.cpp.o
sdc_obj: opensubdiv/sdc/CMakeFiles/sdc_obj.dir/typeTraits.cpp.o
sdc_obj: opensubdiv/sdc/CMakeFiles/sdc_obj.dir/build.make

.PHONY : sdc_obj

# Rule to build all files generated by this target.
opensubdiv/sdc/CMakeFiles/sdc_obj.dir/build: sdc_obj

.PHONY : opensubdiv/sdc/CMakeFiles/sdc_obj.dir/build

opensubdiv/sdc/CMakeFiles/sdc_obj.dir/requires: opensubdiv/sdc/CMakeFiles/sdc_obj.dir/crease.cpp.o.requires
opensubdiv/sdc/CMakeFiles/sdc_obj.dir/requires: opensubdiv/sdc/CMakeFiles/sdc_obj.dir/typeTraits.cpp.o.requires

.PHONY : opensubdiv/sdc/CMakeFiles/sdc_obj.dir/requires

opensubdiv/sdc/CMakeFiles/sdc_obj.dir/clean:
	cd /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc && $(CMAKE_COMMAND) -P CMakeFiles/sdc_obj.dir/cmake_clean.cmake
.PHONY : opensubdiv/sdc/CMakeFiles/sdc_obj.dir/clean

opensubdiv/sdc/CMakeFiles/sdc_obj.dir/depend:
	cd /media/gui2one/Work/code_playground/libs/OpenSubdiv && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/gui2one/Work/code_playground/libs/OpenSubdiv /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc /media/gui2one/Work/code_playground/libs/OpenSubdiv /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc /media/gui2one/Work/code_playground/libs/OpenSubdiv/opensubdiv/sdc/CMakeFiles/sdc_obj.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : opensubdiv/sdc/CMakeFiles/sdc_obj.dir/depend

