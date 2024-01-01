#!/bin/bash

mkdir -p build/{CMake,include,lib}

cd build/CMake
cmake -G Ninja ../../
ninja -j 6



# Copy headers
# ----------------------------------------------------------------------------------------------
cd ../

# Copy all source files
cp -R ../src/* ./include/.

# Delete everything except for headers
find ./include/ -name "*.cpp" -type f -delete
find ./include/ -name "*.txt" -type f -delete
# ----------------------------------------------------------------------------------------------
