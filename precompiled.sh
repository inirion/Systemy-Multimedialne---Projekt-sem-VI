#!/bin/bash
CXX=g++
#Warning precompiled headers must have same compiler flags as in makefile, otherwise precompiled files will be ignored
ARGS="-std=c++11 -Wall -g"

if [ -e "$1" ]
then
	echo "Create one precompiled header";
	CMD="$CXX $ARGS $1";
	echo $CXX $ARGS $1
	$CMD
else
	echo "Refresh all precompiled headers";
	N=`nproc`

	for file in ./*.hpp
	do

		HEADS=`cat $file | grep "include \"" | awk '{print $2}' | tr -d '"' | tr '\n' ' '`
		HEADS="$file $HEADS"

		SUM=`cat $HEADS | md5sum | awk '{print $1}'`

		if [ ! -e "$file.md5" ]
		then
			OLDSUM=""
		else
			OLDSUM=`cat "$file.md5"`
		fi

		printf "\n$file\nHeaders: $HEADS\nTotal md5: $SUM\n"

		PRECOMPILED="$file.gch"

		if [ ! -e "$PRECOMPILED" ]
		then
			OLDSUM=""
		fi

		if [ "$OLDSUM" == "$SUM" ]
		then
			echo "[ SKIPPED ]"
		else
			echo $SUM > "$file.md5"
			rm -f "$PRECOMPILED"
			CMD="$CXX $ARGS $file";
			echo $CXX $ARGS $file

			((i=i%N)); ((i++==0)) && wait
			$CMD &
		fi

	done
fi
