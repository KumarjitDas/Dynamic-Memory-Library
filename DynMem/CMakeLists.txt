add_library("${PROJECT_NAME}" "")
add_library(DynMem::dynmem ALIAS "${PROJECT_NAME}")

include_directories("Headers")

target_include_directories(
    "${PROJECT_NAME}"   PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Headers>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    "$<INSTALL_INTERFACE:include>"
)

if(NOT BUILD_SHARED_LIBS)
    set(STATIC_POSTFIX "-s")
    set_target_properties(
        "${PROJECT_NAME}"   PROPERTIES
        COMPILE_FLAGS       -DDYNMEM_STATIC_DEFINE
    )
endif()

set_target_properties(
    "${PROJECT_NAME}"       PROPERTIES
    OUTPUT_NAME             "dynmem"
    DEBUG_POSTFIX           "${STATIC_POSTFIX}-d"
    RELEASE_POSTFIX         "${STATIC_POSTFIX}"
    MINSIZEREL_POSTFIX      "${STATIC_POSTFIX}-mr"
    RELWITHDEBINFO_POSTFIX  "${STATIC_POSTFIX}-rd"
)

include("GenerateExportHeader")
generate_export_header("${PROJECT_NAME}")

file(
    RENAME "${CMAKE_CURRENT_BINARY_DIR}/dynmem_export.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Headers/common/export.h"
)

install(
    FILES       "${CMAKE_CURRENT_SOURCE_DIR}/Headers/common/export.h"
    DESTINATION "include"
)

add_subdirectory("Headers")
add_subdirectory("Sources")
