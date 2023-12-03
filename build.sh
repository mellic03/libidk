#!/bin/bash
cd "$(dirname "$0")"

mkdir -p build/CMake

cd build/CMake
cmake -G Ninja ../../
ninja -j 6


cd ..

mkdir -p {include,lib}/
mkdir -p include/libidk

cp ./CMake/libidk.so ./lib/.
cp -R ../src/libidk ./include/.

# Delete everything but header files
find ./include/libidk/ -name "*.cpp" -type f -delete
find ./include/libidk/ -name "*.txt" -type f -delete
