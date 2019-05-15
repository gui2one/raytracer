#!/bin/bash
./raytracer_SDL2 \
-o ~/Downloads/dragon.obj \
	-s 0.1 \
	-r 90.0 0.0 0.0 \
	-t 2.0 0.0 0.0 \
-o ../src/res/obj/plane_normals_uvs.obj \
	-s 10.0 \
	-r 90.0 0.0 0.0 \
	-t -2.0 0.0 0.0 \
-o ../src/res/obj/cow.obj \
	-s 0.3 \
	-r 90.0 0.0 0.0 \
	-t 0.0 2.0 1.0 \
-limit 10 \
-rw 160 \
-rh 120 \

