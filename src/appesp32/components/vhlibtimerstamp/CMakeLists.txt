# 1. Определяем абсолютный путь к корню с общими исходниками
set(VH_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)

# 2. Собираем списки файлов и директорий
set(VH_TIMERSTAMP_SRCS
    ${VH_ROOT_DIR}/extmods/vhlibtimerstamp/src/vhtimerstamp.cpp
    # Добавь сюда остальные .cpp файлы, если они есть в этой папке
)

set(VH_TIMERSTAMP_INCS
    ${VH_ROOT_DIR}/extmods/vhlibtimerstamp/src
    # ${VH_ROOT_DIR}/extmods/vhlibtimerstamp/include (если есть отдельная папка include)
)

# 3. Регистрируем компонент, сразу скармливая ему внешние исходники
idf_component_register(
    SRCS ${VH_TIMERSTAMP_SRCS}
    INCLUDE_DIRS "." ${VH_TIMERSTAMP_INCS}
    REQUIRES esp_timer
)

# 4. Применяем флаги компиляции к созданному таргету компонента
target_compile_options(${COMPONENT_LIB} PRIVATE
    "-O2" "-flto" "-funroll-loops" "-ffast-math" "-fno-exceptions" "-fno-rtti"
)

# 5. Настройки линковки (LTO требует совпадения флагов на этапе линковки)
target_link_options(${COMPONENT_LIB} INTERFACE "-flto")