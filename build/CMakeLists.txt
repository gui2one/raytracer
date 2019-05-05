cmake_minimum_required(VERSION 2.8)

project(raytracer)

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
#~ link_directories(../src/include/google/)
add_executable(raytracer

	../src/kdnode.cpp
	
	../src/utils/objLoader.cpp
	../src/main.cpp
	../src/mesh.cpp
	../src/camera.cpp
	
	#~ ../src/raycaster.cpp
	../src/raycaster2.cpp
	../src/utils/mesh_utils.cpp
	
	../src/color.cpp
	../src/rtmaterial.cpp
	
	../src/renderer.cpp
	../src/shader.cpp
	../src/texture.cpp
	
	../src/vendor/stb_image.cpp
	
	
)

target_link_libraries(raytracer -lassimp)
target_link_libraries(raytracer PCHLib)
target_link_libraries(raytracer -lGL)
#~ target_link_libraries(raytracer -lboost_asio)
target_link_libraries(raytracer -lboost_system)
target_link_libraries(raytracer -lboost_thread)
target_link_libraries(raytracer -lglog)

target_link_libraries(raytracer -pthread)


#~ target_link_libraries(raytracer -lglfw)
target_link_libraries(raytracer  -L/usr/local/lib -lglfw3 -lrt -lm -ldl -lXrandr -lXinerama -lXxf86vm -lXext -lXcursor -lXrender -lXfixes -lX11 -lxcb -lXau -lXdmcp )

target_link_libraries(raytracer -lGLEW)

