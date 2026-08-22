set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# Orange Pi PC Plus
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Задаем компиляторы (убедитесь, что они установлены в Ubuntu)
set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

# Флаги архитектуры нужно передавать И в C, И в C++ компилятор
set(ARMA7_FLAGS "-mcpu=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard")

# Используем CACHE, чтобы CMake не затирал флаги при инициализации проекта
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ARMA7_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ARMA7_FLAGS} -fdevirtualize-at-ltrans" CACHE STRING "" FORCE)

# кастомная переменная (используется дальше в логике)
set(VH_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# Защита от поиска библиотек на хост-машине Ubuntu (x86_64)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
