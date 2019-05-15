cmake_minimum_required(VERSION 2.8)

project(raytracer_SDL2)

set(CMAKE_CXX_FLAGS -std=c++11)

#~ set(USE_GLOG 0)

add_library(PCHLib
	../src/pch.cpp
)

include_directories(../src/include/)
include_directories(../src/include/google)
include_directories(../src/include/google/base)
include_directories(../src/include/google/gflags)
include_directories(../src/include/google/glog)
include_directories(../src/include/google/gtest)

#~ include_directories(../src/include/boost/threadpool)
include_directories(~/Downloads/boost_1_50_0)
link_directories(../src/libs/)
link_directories(/usr/include/SDL2)


#~ link_directories(../src/include/google/)
add_executable(raytracer_SDL2

	../src/scene_file_loader.cpp
	../src/kdnode.cpp
	
	../src/vector3.cpp

	../src/utils/system_utils.cpp	
	../src/utils/objLoader.cpp
	../src/main.cpp
	../src/mesh.cpp
	../src/camera.cpp
	../src/light.cpp
	
	
	../src/raycaster.cpp
	../src/utils/mesh_utils.cpp
	
	../src/color.cpp
	../src/rtmaterial.cpp
	
	../src/renderer.cpp
	../src/shader.cpp
	../src/texture.cpp
	
	../src/vendor/stb_image.cpp
	../src/vendor/stb_image_write.cpp
	
	
)

target_link_libraries(raytracer_SDL2 -lassimp)
target_link_libraries(raytracer_SDL2 PCHLib)
target_link_libraries(raytracer_SDL2 -lGLEW)
target_link_libraries(raytracer_SDL2 -lGL)
#~ target_link_libraries(raytracer_SDL2 -lboost_asio)
target_link_libraries(raytracer_SDL2 -lboost_system)
target_link_libraries(raytracer_SDL2 -lboost_thread)
target_link_libraries(raytracer_SDL2 -lglog)

target_link_libraries(raytracer_SDL2 -pthread)


target_link_libraries(raytracer_SDL2 -L/usr/lib/arm-linux-gnueabihf -lSDL2)
#~ target_link_libraries(raytracer_SDL2  -L/usr/local/lib -lglfw3 -lrt -lm -ldl -lXrandr -lXinerama -lXxf86vm -lXext -lXcursor -lXrender -lXfixes -lX11 -lxcb -lXau -lXdmcp )



