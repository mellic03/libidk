#!/bin/bash

mkdir -p build

cd build
cmake -G Ninja ..
ninja -j 6
cd ..


# Create output directory structure
mkdir -p output/{include,lib}/libidk/

# Copy source code to output directory
cp -R libidk/. output/include/libidk/.

# Delete everything but header files
find ./output/include/libidk/ -name "*.cpp" -type f -delete
find ./output/include/libidk/ -name "*.txt" -type f -delete

# Copy library file to output directory
cp build/libidk.a  output/lib/libidk/libidk.a

