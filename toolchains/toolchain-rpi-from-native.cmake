# Raspbery Pi Model B+ V1.2

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Задаем компиляторы (убедитесь, что они установлены в Ubuntu)
set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

# Флаги архитектуры нужно передавать И в C, И в C++ компилятор
set(ARMV6_FLAGS "-marm -march=armv6 -mfloat-abi=hard -mfpu=vfp")

# Используем CACHE, чтобы CMake не затирал флаги при инициализации проекта
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ARMV6_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ARMV6_FLAGS}")

# кастомная переменная (используется дальше в логике)
set(VH_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# Защита от поиска библиотек на хост-машине Ubuntu (x86_64)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
