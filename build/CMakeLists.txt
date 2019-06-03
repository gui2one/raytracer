cmake_minimum_required(VERSION 2.8)

project(raytracer_SDL2)


# example found online 

# Configuration types
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
IF(DEFINED CMAKE_BUILD_TYPE AND CMAKE_VERSION VERSION_GREATER "2.8")
  SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS  ${CMAKE_CONFIGURATION_TYPES})
ENDIF()


###



set(CMAKE_CXX_FLAGS -std=c++14)
add_definitions(-Wall -Wno-unused-function)
#~ set(CMAKE_CXX_FLAGS -Wall)
set(CMAKE_BUILD_TYPE "Debug")



set(PROJECT_ROOT ~/projects/raytracer_SDL2/)

include_directories(../src/include/)
include_directories(../src/include/opensubdiv)
include_directories(../src/include/opensubdiv/far)
include_directories(../src/include/opensubdiv/osd)

include_directories(/usr/local/include)
include_directories(../src/vendor/imgui)


include_directories(../src/include/google)
include_directories(../src/include/google/base)
include_directories(../src/include/google/gflags)
include_directories(../src/include/google/glog)
include_directories(../src/include/google/gtest)
include_directories(~/Downloads/boost_1_50_0)

link_directories(${PROJECT_ROOT}/src/libs/)
link_directories(${PROJECT_ROOT}/src/libs/opensubdiv)
link_directories(/usr/include/SDL2)


#~ link_directories(../src/include/google/)

add_library(PCHLib
	../src/pch.cpp
)

add_library(coreLib
	../src/mesh.cpp
	../src/utils/mesh_utils.cpp	

	../src/light.cpp
	../src/color.cpp
	../src/rtmaterial.cpp	
	../src/texture.cpp	
	
	../src/shader.cpp
	
	../src/vendor/stb_image.cpp
	../src/vendor/stb_image_write.cpp	
	../src/utils/system_utils.cpp	
	../src/utils/objLoader.cpp		
	../src/scene_file_loader.cpp

		
)


add_executable(raytracer_SDL2

	../src/main.cpp
	../src/renderer.cpp
		
	../src/camera.cpp

	../src/kdnode.cpp

	../src/raycaster.cpp	
	
	


	
	
)

target_link_libraries(raytracer_SDL2 PCHLib)
target_link_libraries(raytracer_SDL2 coreLib)

target_link_libraries(raytracer_SDL2 -lassimp)



target_link_libraries(raytracer_SDL2 -lGLEW)
target_link_libraries(raytracer_SDL2 -lGL)
#~ target_link_libraries(raytracer_SDL2 -lboost_asio)
target_link_libraries(raytracer_SDL2 -lboost_system)
target_link_libraries(raytracer_SDL2 -lboost_thread)
target_link_libraries(raytracer_SDL2 -lglog)

target_link_libraries(raytracer_SDL2 -pthread)


target_link_libraries(raytracer_SDL2 -L/usr/lib/arm-linux-gnueabihf -lSDL2)
#~ target_link_libraries(raytracer_SDL2  -L/usr/local/lib -lglfw3 -lrt -lm -ldl -lXrandr -lXinerama -lXxf86vm -lXext -lXcursor -lXrender -lXfixes -lX11 -lxcb -lXau -lXdmcp )




add_executable(editor

	../src/editor/editor.cpp
	../src/editor/utils/editor_gizmo_utils.cpp
	../src/editor/main.cpp
	
	../src/editor/editor_camera.cpp
	../src/editor/entity3d.cpp
	
	../src/editor/construction_grid.cpp
	
	../src/editor/ui/ui.cpp	
	../src/vendor/imgui/imgui_impl_opengl3.cpp
	../src/vendor/imgui/imgui_impl_sdl.cpp
	
	../src/vendor/imgui/imgui.cpp
	../src/vendor/imgui/imgui_demo.cpp
	../src/vendor/imgui/imgui_draw.cpp
	../src/vendor/imgui/imgui_widgets.cpp	
	
	
	../src/editor/kdnode2.cpp

	../src/editor/raycaster2.cpp	
	
	../src/editor/utils/editor_mesh_utils.cpp
	../src/editor/mesh_generators/mesh_generator.cpp
	../src/editor/mesh_generators/plane_mesh_generator.cpp
)

target_link_libraries(editor coreLib)
target_link_libraries(editor -losdCPU -lgomp)
target_link_libraries(editor -lassimp)
target_link_libraries(editor PCHLib)
target_link_libraries(editor -lGLEW)
target_link_libraries(editor -lGL)
target_link_libraries(editor -L/usr/lib/arm-linux-gnueabihf -lSDL2 -lSDL2_ttf)


