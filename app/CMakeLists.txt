# Especifica las fuentes del ejecutable
set(APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

# Crea el ejecutable a partir de los archivos fuente especificados
add_executable(${EXECUTABLE_NAME} ${APP_SOURCES})

# Vincula las librerías necesarias
target_link_libraries(${EXECUTABLE_NAME}
    PRIVATE
        funciones   # La librería creada en src
        nlohmann_json::nlohmann_json
        fmt::fmt
        spdlog::spdlog
        cxxopts::cxxopts
)

# Si las advertencias están habilitadas, agregar advertencias al ejecutable
if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET ${EXECUTABLE_NAME}
        ENABLE ${ENABLE_WARNINGS}
        AS_ERRORS ${ENABLE_WARNINGS_AS_ERRORS}
    )
endif()

# Habilitar Link Time Optimization (LTO) si está habilitado
if(${ENABLE_LTO})
    target_enable_lto(
        TARGET ${EXECUTABLE_NAME}
        ENABLE ON
    )
endif()

# Agregar soporte de Clang Tidy si está habilitado
if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target(${EXECUTABLE_NAME})
endif()