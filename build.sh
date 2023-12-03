#!/bin/bash

mkdir -p build output output/include output/lib

cd build
cmake -G Ninja ..
ninja -j 6
cd ..


# Copy source code to output directory
cp -R libidk/. output/include/.

# Delete .cpp files
find .output/include/ -name "*.cpp" -type f -delete


cp build/liblibidk.a  output/libidk.a




