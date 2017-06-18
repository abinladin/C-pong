#!/bin/bash

#
# Author: Abdullah Binladin
# Date: 18 June 2017
#

# compiler to use
CC="gcc"

# compiler flags to pass
CFLAGS="-lSDL2 -lSDL2_image -Wall"

# source files to compile
SRC="
src/main/main.c
src/gameobject/gameobject.c
src/gameobject/gameobject.h
src/graphics/graphics.c
src/graphics/graphics.h
"

#SRC split into an array by newline
IFS=$'\n' split_src_string=($SRC)

# array of source file filenames


# functions
buildObjectFiles() {
    
    if [ ! -d "build" ]; then
        mkdir build
    fi
    
    #get the name of the file from the path without the file extention
    current_string=$(basename ${split_src_string[0]} .c)
    
    echo making  $current_string
    $CC $CFLAGS -c ${split_src_string[0]} -o ./build/${current_string}.o    
    
    #TODO: Find a way to loop through array without hardcoding
    for i in {1..4}
    do
        if [ ! $(($i%2)) -eq 0 ]; then
             current_string=$(basename ${split_src_string[$i]} .c)
             echo making $current_string
             $CC $CFLAGS -c ${split_src_string[$i]} -o ./build/${current_string}.o
        fi
    done
}

# script start

buildObjectFiles
