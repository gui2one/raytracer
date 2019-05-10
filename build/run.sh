#!/bin/bash
./raytracer \
-o ../src/res/obj/monkey.obj \
	-s 1.0 \
	-r 90.0 0.0 0.0 \
	-t 0.0 0.0 1.0 \
-o ../src/res/obj/plane_normals.obj \
	-s 30.0 \
	-r 90.0 0.0 0.0 \
-o ../src/res/obj/cow.obj \
	-s 0.3 \
	-r 90.0 0.0 0.0 \
	-t 2.0 2.0 1.0 \
-limit 100 \
-rw 320 \
-rh 240
