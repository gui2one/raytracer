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
include CMakeFiles/editor.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/editor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/editor.dir/flags.make

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o: CMakeFiles/editor.dir/flags.make
CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o: /home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/projects/raytracer_SDL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o -c /home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp > CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.i

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.s

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o.requires:

.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o.requires

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o.provides: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o.requires
	$(MAKE) -f CMakeFiles/editor.dir/build.make CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o.provides.build
.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o.provides

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o.provides.build: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o


CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.o: CMakeFiles/editor.dir/flags.make
CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.o: /home/pi/projects/raytracer_SDL2/src/editor/editor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/projects/raytracer_SDL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.o -c /home/pi/projects/raytracer_SDL2/src/editor/editor.cpp

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/projects/raytracer_SDL2/src/editor/editor.cpp > CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.i

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/projects/raytracer_SDL2/src/editor/editor.cpp -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.s

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.o.requires:

.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.o.requires

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.o.provides: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.o.requires
	$(MAKE) -f CMakeFiles/editor.dir/build.make CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.o.provides.build
.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.o.provides

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.o.provides.build: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.o


CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.o: CMakeFiles/editor.dir/flags.make
CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.o: /home/pi/projects/raytracer_SDL2/src/editor/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/projects/raytracer_SDL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.o -c /home/pi/projects/raytracer_SDL2/src/editor/main.cpp

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/projects/raytracer_SDL2/src/editor/main.cpp > CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.i

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/projects/raytracer_SDL2/src/editor/main.cpp -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.s

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.o.requires:

.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.o.requires

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.o.provides: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/editor.dir/build.make CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.o.provides.build
.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.o.provides

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.o.provides.build: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.o


CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.o: CMakeFiles/editor.dir/flags.make
CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.o: /home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/projects/raytracer_SDL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.o -c /home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp > CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.i

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.s

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.o.requires:

.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.o.requires

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.o.provides: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.o.requires
	$(MAKE) -f CMakeFiles/editor.dir/build.make CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.o.provides.build
.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.o.provides

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.o.provides.build: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.o


CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.o: CMakeFiles/editor.dir/flags.make
CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.o: /home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/projects/raytracer_SDL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.o -c /home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp > CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.i

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.s

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.o.requires:

.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.o.requires

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.o.provides: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.o.requires
	$(MAKE) -f CMakeFiles/editor.dir/build.make CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.o.provides.build
.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.o.provides

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.o.provides.build: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.o


CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.o: CMakeFiles/editor.dir/flags.make
CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.o: /home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/projects/raytracer_SDL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.o -c /home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp > CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.i

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.s

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.o.requires:

.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.o.requires

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.o.provides: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.o.requires
	$(MAKE) -f CMakeFiles/editor.dir/build.make CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.o.provides.build
.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.o.provides

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.o.provides.build: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.o


CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.o: CMakeFiles/editor.dir/flags.make
CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.o: /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/projects/raytracer_SDL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.o -c /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp > CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.i

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.s

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.o.requires:

.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.o.requires

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.o.provides: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.o.requires
	$(MAKE) -f CMakeFiles/editor.dir/build.make CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.o.provides.build
.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.o.provides

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.o.provides.build: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.o


CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.o: CMakeFiles/editor.dir/flags.make
CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.o: /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/projects/raytracer_SDL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.o -c /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp > CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.i

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.s

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.o.requires:

.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.o.requires

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.o.provides: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.o.requires
	$(MAKE) -f CMakeFiles/editor.dir/build.make CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.o.provides.build
.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.o.provides

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.o.provides.build: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.o


CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.o: CMakeFiles/editor.dir/flags.make
CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.o: /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/projects/raytracer_SDL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.o -c /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp > CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.i

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.s

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.o.requires:

.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.o.requires

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.o.provides: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.o.requires
	$(MAKE) -f CMakeFiles/editor.dir/build.make CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.o.provides.build
.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.o.provides

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.o.provides.build: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.o


CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.o: CMakeFiles/editor.dir/flags.make
CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.o: /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/projects/raytracer_SDL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.o -c /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp > CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.i

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.s

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.o.requires:

.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.o.requires

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.o.provides: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.o.requires
	$(MAKE) -f CMakeFiles/editor.dir/build.make CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.o.provides.build
.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.o.provides

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.o.provides.build: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.o


CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.o: CMakeFiles/editor.dir/flags.make
CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.o: /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/projects/raytracer_SDL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.o -c /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp > CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.i

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.s

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.o.requires:

.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.o.requires

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.o.provides: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.o.requires
	$(MAKE) -f CMakeFiles/editor.dir/build.make CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.o.provides.build
.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.o.provides

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.o.provides.build: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.o


CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.o: CMakeFiles/editor.dir/flags.make
CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.o: /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/projects/raytracer_SDL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.o -c /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp > CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.i

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp -o CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.s

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.o.requires:

.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.o.requires

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.o.provides: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.o.requires
	$(MAKE) -f CMakeFiles/editor.dir/build.make CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.o.provides.build
.PHONY : CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.o.provides

CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.o.provides.build: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.o


# Object files for target editor
editor_OBJECTS = \
"CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o" \
"CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.o" \
"CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.o" \
"CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.o" \
"CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.o" \
"CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.o" \
"CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.o" \
"CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.o" \
"CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.o" \
"CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.o" \
"CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.o" \
"CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.o"

# External object files for target editor
editor_EXTERNAL_OBJECTS =

editor: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o
editor: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.o
editor: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.o
editor: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.o
editor: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.o
editor: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.o
editor: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.o
editor: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.o
editor: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.o
editor: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.o
editor: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.o
editor: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.o
editor: CMakeFiles/editor.dir/build.make
editor: libcoreLib.a
editor: libPCHLib.a
editor: CMakeFiles/editor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/projects/raytracer_SDL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable editor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/editor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/editor.dir/build: editor

.PHONY : CMakeFiles/editor.dir/build

CMakeFiles/editor.dir/requires: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/scene_file_loader.cpp.o.requires
CMakeFiles/editor.dir/requires: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/editor.cpp.o.requires
CMakeFiles/editor.dir/requires: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/main.cpp.o.requires
CMakeFiles/editor.dir/requires: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/entity3d.cpp.o.requires
CMakeFiles/editor.dir/requires: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/construction_grid.cpp.o.requires
CMakeFiles/editor.dir/requires: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/editor/ui/ui.cpp.o.requires
CMakeFiles/editor.dir/requires: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_opengl3.cpp.o.requires
CMakeFiles/editor.dir/requires: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_impl_sdl.cpp.o.requires
CMakeFiles/editor.dir/requires: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui.cpp.o.requires
CMakeFiles/editor.dir/requires: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_demo.cpp.o.requires
CMakeFiles/editor.dir/requires: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_draw.cpp.o.requires
CMakeFiles/editor.dir/requires: CMakeFiles/editor.dir/home/pi/projects/raytracer_SDL2/src/vendor/imgui/imgui_widgets.cpp.o.requires

.PHONY : CMakeFiles/editor.dir/requires

CMakeFiles/editor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/editor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/editor.dir/clean

CMakeFiles/editor.dir/depend:
	cd /home/pi/projects/raytracer_SDL2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/projects/raytracer_SDL2/build /home/pi/projects/raytracer_SDL2/build /home/pi/projects/raytracer_SDL2/build /home/pi/projects/raytracer_SDL2/build /home/pi/projects/raytracer_SDL2/build/CMakeFiles/editor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/editor.dir/depend

