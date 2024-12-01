# Especifica las fuentes y los encabezados de tu librería
set(LIBRARY_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/functions.cpp"
)

set(LIBRARY_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/functions.h"
)

# Especifica los directorios de inclusión
set(LIBRARY_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}/"  # Incluir la carpeta actual
)

# Crear la librería estática
add_library("Libfunctions" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})

# Especificar los directorios de inclusión
target_include_directories("Libfunctions" PUBLIC ${LIBRARY_INCLUDES})

# Vincular dependencias (como nlohmann_json, fmt, spdlog, cxxopts, etc.)
target_link_libraries("Libfunctions"
    PRIVATE
        nlohmann_json::nlohmann_json
        fmt::fmt
        spdlog::spdlog
        cxxopts::cxxopts
)

# Agregar advertencias si está habilitado
if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET "Libfunctions"
        ENABLE ${ENABLE_WARNINGS}
        AS_ERRORS ${ENABLE_WARNINGS_AS_ERRORS}
    )
endif()

# Habilitar Link Time Optimization (LTO) si está habilitado
if(${ENABLE_LTO})
    target_enable_lto(
        TARGET "Libfunctions"
        ENABLE ON
    )
endif()

# Agregar soporte de Clang Tidy si está habilitado
if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target(functions)
endif()
