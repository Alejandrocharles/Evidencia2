include(Catch)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories("${CMAKE_SOURCE_DIR}")

# Crear el ejecutable para los tests
add_executable(UnitTestFunctions test.cpp)

# Vincular la biblioteca principal y Catch2
target_link_libraries(UnitTestFunctions
    PUBLIC
        Libfunctions
    PRIVATE
        Catch2::Catch2WithMain
)

# Configurar advertencias si están habilitadas
if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        UnitTestFunctions
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS}
    )
endif()

# Configurar cobertura de código si está habilitada
if(ENABLE_COVERAGE)
    set(COVERAGE_MAIN "coverage")
    set(COVERAGE_EXCLUDES
        "${PROJECT_SOURCE_DIR}/app/*"
        "${PROJECT_SOURCE_DIR}/cmake/*"
        "${PROJECT_SOURCE_DIR}/docs/*"
        "${PROJECT_SOURCE_DIR}/external/*"
        "${PROJECT_SOURCE_DIR}/tests/*"
        "${PROJECT_SOURCE_DIR}/build/*"
        "/usr/include/*"
    )
    set(COVERAGE_EXTRA_FLAGS)
    set(COVERAGE_DEPENDENCIES UnitTestFunctions)

    setup_target_for_coverage_gcovr_html(
        NAME
        ${COVERAGE_MAIN}
        EXECUTABLE
        ctest
        DEPENDENCIES
        ${COVERAGE_DEPENDENCIES}
        BASE_DIRECTORY
        ${CMAKE_SOURCE_DIR}
    )
endif()

# Descubrir y registrar tests con Catch2
catch_discover_tests(UnitTestFunctions)
