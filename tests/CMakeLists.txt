include(Catch)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories("${CMAKE_SOURCE_DIR}")


# Crear el ejecutable para los tests
add_executable("UnitTestFunctions" "test.cpp")


# Vincular la biblioteca principal y Catch2
target_link_libraries("UnitTestFunctions"
    PUBLIC
        Libfunctions # Cambiado a "functions" para coincidir con el nombre de la biblioteca
    PRIVATE
        Catch2::Catch2WithMain
)

# Configurar advertencias si están habilitadas
if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "UnitTestFunctions"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS}
    )
endif()

# Descubrir y registrar tests con Catch2
catch_discover_tests("UnitTestFunctions")
