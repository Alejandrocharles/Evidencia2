# Incluir Catch2 correctamente
find_package(Catch2 REQUIRED)

# Crear el ejecutable para los tests
add_executable("UnitTestFunctions" "test.cpp")

# Incluir el directorio fuente de tu proyecto (si es necesario)
# include_directories(${CMAKE_SOURCE_DIR}/src)  # Esto puede no ser necesario si las bibliotecas están bien vinculadas

# Vincular Catch2 y otras bibliotecas necesarias
target_link_libraries("UnitTestFunctions"
    PUBLIC
        Libfunctions
    PRIVATE
        Catch2::Catch2WithMain
)

# Configurar advertencias si están habilitadas
if(ENABLE_WARNINGS)
    target_compile_options("UnitTestFunctions"
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )
endif()

if(ENABLE_WARNINGS_AS_ERRORS)
    target_compile_options("UnitTestFunctions" PRIVATE -Werror)
endif()

# Configurar cobertura si está habilitada
if(ENABLE_COVERAGE)
    set(COVERAGE_EXCLUDES
        "${PROJECT_SOURCE_DIR}/app/*"
        "${PROJECT_SOURCE_DIR}/cmake/*"
        "${PROJECT_SOURCE_DIR}/docs/*"
        "${PROJECT_SOURCE_DIR}/external/*"
        "${PROJECT_SOURCE_DIR}/tests/*"
        "${PROJECT_SOURCE_DIR}/build/*"
    )

    set(COVERAGE_DEPENDENCIES "UnitTestFunctions")

    setup_target_for_coverage_gcovr_html(
        NAME ${COVERAGE_MAIN}
        EXECUTABLE ctest
        DEPENDENCIES ${COVERAGE_DEPENDENCIES}
        BASE_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

# Descubrir y registrar pruebas con Catch2
catch_discover_tests("UnitTestFunctions")
