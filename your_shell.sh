#!/bin/sh

if [ ! -d "build" ]; then
    mkdir build
fi
cd build

cmake ..

cmake --build .

# cmake -B build 
# cmake --build ./build
# exec ./build/shell "$@"