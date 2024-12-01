# Especifica las fuentes y los encabezados de tu librería
set(LIBRARY_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/funciones.cpp"
)

set(LIBRARY_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/funciones.h"
)

# Especifica los directorios de inclusión
set(LIBRARY_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}/"  # Incluir la carpeta actual
)

# Crear la librería estática
add_library("Libfunciones" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})

# Especificar los directorios de inclusión
target_include_directories("Libfunciones" PUBLIC ${LIBRARY_INCLUDES})

# Vincular dependencias (como nlohmann_json, fmt, spdlog, cxxopts, etc.)
target_link_libraries("Libfunciones"
    PRIVATE
        nlohmann_json::nlohmann_json
        fmt::fmt
        spdlog::spdlog
        cxxopts::cxxopts
)

# Agregar advertencias si está habilitado
if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET "Libfunciones"
        ENABLE ${ENABLE_WARNINGS}
        AS_ERRORS ${ENABLE_WARNINGS_AS_ERRORS}
    )
endif()

# Habilitar Link Time Optimization (LTO) si está habilitado
if(${ENABLE_LTO})
    target_enable_lto(
        TARGET "Libfunciones"
        ENABLE ON
    )
endif()

# Agregar soporte de Clang Tidy si está habilitado
if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target(funciones)
endif()