#!/bin/sh

#
BUILD_DIR="build-wavesharecore7xxi"

#
TARGET="WAVESHARECORE7XXI"

#
TOOLCHAIN="../cmake/toolchains/toolchain-stm32f746.cmake"

# Путь к репозиторию STM32Cube
CUBEMX_PATH="$HOME/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.4"

# Остановка скрипта при любой ошибке
set -e

#
cd ..

#
mkdir -p $BUILD_DIR

#
cd $BUILD_DIR

#
cmake .. \
    -DBUILD_TARGET="$TARGET" \
    -DCUBEMX_PATH="$CUBEMX_PATH" \
    -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN" \
    -DCMAKE_BUILD_TYPE=Release

#
make
