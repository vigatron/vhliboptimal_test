#!/bin/sh

cd ..
mkdir -p build-release
cd build-release
cmake .. -DBUILD_TARGET=native -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/toolchain-native.cmake -DCMAKE_BUILD_TYPE=Release
make
