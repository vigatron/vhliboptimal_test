#!/bin/sh

cd ..
mkdir -p build-rpi
cd build-rpi
cmake .. -DBUILD_TARGET=native -DCMAKE_TOOLCHAIN_FILE=../toolchains/toolchain-rpi.cmake -DCMAKE_BUILD_TYPE=Release
make
