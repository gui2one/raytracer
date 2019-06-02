#! /bin/bash

rm -f CMakeCache.txt &&\
	rm -f MakeFile &&\
	rm -f -r CMakeFiles &&\
	cmake CMakeLists.txt

