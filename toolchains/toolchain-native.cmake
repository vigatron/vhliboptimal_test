# toolchain-amd.cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Transfer PC/PC: -O3 -msse4.2 -mpclmul -maes -mavx2 -mfma -flto=auto

set(CMAKE_CXX_FLAGS "-O3 -march=native -flto=auto")
# set(CMAKE_CXX_FLAGS "-O3 -march=native -mavx2 -mbmi")
# set(CMAKE_CXX_FLAGS "-O3 -march=native -mavx -mbmi")
