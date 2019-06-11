#! /bin/bash

read -p "Are you sure?  
This will remove all relevant compilation files ...
(y or n) " ANSWER

if [ ${ANSWER} == y ];
then

	rm -f CMakeCache.txt &&\
		rm -f MakeFile &&\
		rm -f -r CMakeFiles &&\
		cmake CMakeLists.txt
fi

if [ ${ANSWER} == n ];
then
	exit 1
fi


