# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_SOURCE_DIR = /home/pi/projects/raytracer_SDL2/build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/projects/raytracer_SDL2/build

# Include any dependencies generated for this target.
include CMakeFiles/raytracer_SDL2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/raytracer_SDL2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raytracer_SDL2.dir/flags.make

CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.o: CMakeFiles/raytracer_SDL2.dir/flags.make
CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.o: /home/pi/projects/raytracer_SDL2/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/projects/raytracer_SDL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.o -c /home/pi/projects/raytracer_SDL2/src/main.cpp

CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/projects/raytracer_SDL2/src/main.cpp > CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.i

CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/projects/raytracer_SDL2/src/main.cpp -o CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.s

CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.o.requires:

.PHONY : CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.o.requires

CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.o.provides: CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/raytracer_SDL2.dir/build.make CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.o.provides

CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.o.provides.build: CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.o


CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.o: CMakeFiles/raytracer_SDL2.dir/flags.make
CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.o: /home/pi/projects/raytracer_SDL2/src/renderer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/projects/raytracer_SDL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.o -c /home/pi/projects/raytracer_SDL2/src/renderer.cpp

CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/projects/raytracer_SDL2/src/renderer.cpp > CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.i

CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/projects/raytracer_SDL2/src/renderer.cpp -o CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.s

CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.o.requires:

.PHONY : CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.o.requires

CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.o.provides: CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.o.requires
	$(MAKE) -f CMakeFiles/raytracer_SDL2.dir/build.make CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.o.provides.build
.PHONY : CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.o.provides

CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.o.provides.build: CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.o


CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o: CMakeFiles/raytracer_SDL2.dir/flags.make
CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o: /home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/projects/raytracer_SDL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o -c /home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp

CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp > CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.i

CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp -o CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.s

CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o.requires:

.PHONY : CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o.requires

CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o.provides: CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o.requires
	$(MAKE) -f CMakeFiles/raytracer_SDL2.dir/build.make CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o.provides.build
.PHONY : CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o.provides

CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o.provides.build: CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o


# Object files for target raytracer_SDL2
raytracer_SDL2_OBJECTS = \
"CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.o" \
"CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.o" \
"CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o"

# External object files for target raytracer_SDL2
raytracer_SDL2_EXTERNAL_OBJECTS =

raytracer_SDL2: CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.o
raytracer_SDL2: CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.o
raytracer_SDL2: CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o
raytracer_SDL2: CMakeFiles/raytracer_SDL2.dir/build.make
raytracer_SDL2: libPCHLib.a
raytracer_SDL2: libcoreLib.a
raytracer_SDL2: CMakeFiles/raytracer_SDL2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/projects/raytracer_SDL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable raytracer_SDL2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raytracer_SDL2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/raytracer_SDL2.dir/build: raytracer_SDL2

.PHONY : CMakeFiles/raytracer_SDL2.dir/build

CMakeFiles/raytracer_SDL2.dir/requires: CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/main.cpp.o.requires
CMakeFiles/raytracer_SDL2.dir/requires: CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/renderer.cpp.o.requires
CMakeFiles/raytracer_SDL2.dir/requires: CMakeFiles/raytracer_SDL2.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o.requires

.PHONY : CMakeFiles/raytracer_SDL2.dir/requires

CMakeFiles/raytracer_SDL2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/raytracer_SDL2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/raytracer_SDL2.dir/clean

CMakeFiles/raytracer_SDL2.dir/depend:
	cd /home/pi/projects/raytracer_SDL2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/projects/raytracer_SDL2/build /home/pi/projects/raytracer_SDL2/build /home/pi/projects/raytracer_SDL2/build /home/pi/projects/raytracer_SDL2/build /home/pi/projects/raytracer_SDL2/build/CMakeFiles/raytracer_SDL2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/raytracer_SDL2.dir/depend

