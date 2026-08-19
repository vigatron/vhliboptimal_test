# toolchain-amd.cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR armv7l)

set(CMAKE_CXX_FLAGS "-O3 -march=native -flto=auto")

set(VH_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
