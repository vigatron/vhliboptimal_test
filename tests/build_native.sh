#!/bin/sh

cd ..
mkdir -p build
cd build
cmake .. -DBUILD_TARGET=native -DCMAKE_TOOLCHAIN_FILE=../toolchains/toolchain-native.cmake -DCMAKE_BUILD_TYPE=Release
make
