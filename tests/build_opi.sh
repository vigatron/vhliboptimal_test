#!/bin/sh

cd ..
mkdir -p build-opi
cd build-opi
cmake .. -DBUILD_TARGET=native -DCMAKE_TOOLCHAIN_FILE=../toolchains/toolchain-opi.cmake -DCMAKE_BUILD_TYPE=Release
make
