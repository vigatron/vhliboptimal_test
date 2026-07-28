# toolchain-intel.cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CMAKE_CXX_FLAGS "-O3 -march=native -mavx2 -mbmi")
