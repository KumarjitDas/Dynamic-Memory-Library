cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Libraries")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Libraries")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Binaries")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

option(BUILD_SHARED_LIBS "Build the project with shared libraries." ON)

project("DynMem" VERSION 0.2.3 LANGUAGES C)

set(VALID_BUILD_TYPES "Release" "Debug" "MinSizeRel" "RelWithDebInfo")

if(NOT CMAKE_CONFIGURATION_TYPES)
    if("${CMAKE_BUILD_TYPE}" STREQUAL "")
        set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build configuration" FORCE)
    endif()

    list(FIND VALID_BUILD_TYPES "${CMAKE_BUILD_TYPE}" INDEX)

    if(${INDEX} MATCHES -1)
        message(FATAL_ERROR "Invalid build type. Valid build types are: ${VALID_BUILD_TYPES}")
    endif()

    if(DEFINED CMAKE_BUILD_TYPE)
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${VALID_BUILD_TYPES})
    endif()
endif()

add_subdirectory("DynMem")
add_subdirectory("Examples")

if("${CMAKE_PROJECT_NAME}" STREQUAL "${PROJECT_NAME}")
    enable_testing()
    add_subdirectory("Tests")
endif()
