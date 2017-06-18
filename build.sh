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

# functions
buildObjectFiles() {
    if [ ! -d "build" ]; then
        mkdir build
    fi
    
}

# script start

buildObjectFiles
