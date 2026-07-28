# toolchain-arm.cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR armv7l)

set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

set(CMAKE_CXX_FLAGS "-O3 -march=native -mfloat-abi=hard -fomit-frame-pointer -flto -funroll-loops")
# set(CMAKE_CXX_FLAGS "-O3 -march=native -mfpu=neon -mfloat-abi=hard")
