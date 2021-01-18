# dir: root
# file: CMakeLists.txt


# Setting the cmake minimum version
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)


# Project setup
set(
  proj_desc
  "A simple C library for dynamic memory allocation and reallocation."
)
project(
  mem
  VERSION 0.1.1
  DESCRIPTION "${proj_desc}"
  HOMEPAGE_URL "https://github.com/KumarjitDas/Dynamic-Memory-Library"
  LANGUAGES C
)


# Executable and library directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


# Include directories of the project
include_directories("include")


# An option to build shared library in the CMake GUI
option(BUILD_SHARED_LIBS "Build shared library" ON)


# If the build type does not have multiple configuration
set(VALID_BUILD_TYPES  "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
if(NOT CMAKE_CONFIGURATION_TYPES)

  # Validate CMake build type

  # If the given build type string is empty, set it to "Debug"
  if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(
      CMAKE_BUILD_TYPE "Debug" CACHE
      STRING "Build configuration" FORCE
    )
  endif()

  # If the given build type is not valid, output an error message
  list(FIND VALID_BUILD_TYPES "${CMAKE_BUILD_TYPE}" INDEX)
  if(${INDEX} MATCHES -1)

    string(
      CONCAT STAT_MSG
      "{PROJECT_NAME} -- Invalid build type."
      "Valid Types are: [${VALID_BUILD_TYPES}]"
    )
    message(FATAL_ERROR "${STAT_MSG}")

  endif()


  # Add drop down list of valid build types in the CMake GUI
  if(DEFINED CMAKE_BUILD_TYPE)

    set_property(
      CACHE CMAKE_BUILD_TYPE PROPERTY
      STRINGS "${VALID_BUILD_TYPES}"
    )

  endif()


endif()


# The main library
add_library(${PROJECT_NAME} "")


# Generate the shared library export header
include("GenerateExportHeader")
generate_export_header(${PROJECT_NAME})

# Add the export header to the library
target_sources(
  ${PROJECT_NAME} PRIVATE
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_export.h"
)

# Install rule for the export header
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_export.h"
  DESTINATION "include"
)


# If the project is not building shared library
if(NOT BUILD_SHARED_LIBS)

  # Add "_s" postfix at the library name
  set(STATIC_POSTFIX "_s")


  # Set compiler flags for the export header
  set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    COMPILE_FLAGS -DMEM_STATIC_DEFINE
  )


endif()


# Add postfixes according to selected build type
set_target_properties(
  ${PROJECT_NAME} PROPERTIES
  DEBUG_POSTFIX          "${STATIC_POSTFIX}_d"
  RELEASE_POSTFIX        "${STATIC_POSTFIX}"
  MINSIZEREL_POSTFIX     "${STATIC_POSTFIX}_mr"
  RELWITHDEBINFO_POSTFIX "${STATIC_POSTFIX}_rd"
)


# Use the C - 2011 Standard
target_compile_features(${PROJECT_NAME} PUBLIC c_std_11)


# Change the compiler warning flags according to the compiler provider
if(MSVC)

  # Use "/W4" - warning level 4 option for MSVC
  if(CMAKE_C_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
  endif()


elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

  # Use Wall Wextra pedantic and Werror for GCC
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Werror")


endif()


# Add projects library alias ::
add_library("${PROJECT_NAME}::${PROJECT_NAME}" ALIAS ${PROJECT_NAME})


# Configure the project config file
add_subdirectory("config")


# Add include directories for the library for both build and install interface
target_include_directories(
  ${PROJECT_NAME} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
  "$<INSTALL_INTERFACE:include>"
)


# Add the project subdirectories
add_subdirectory("include")
add_subdirectory("src")
add_subdirectory("examples")
add_subdirectory("tests")


# Create an export target for the library
install(
  TARGETS ${PROJECT_NAME}
  DESTINATION "lib"
  EXPORT "${PROJECT_NAME}Targets"
)

# Install the project cmake target to {PREFIX}/lib/cmake
install(
  EXPORT "${PROJECT_NAME}Targets"
  FILE "${PROJECT_NAME}Targets.cmake"
  DESTINATION "lib/cmake/${PROJECT_NAME}"
)

# Export the project target
export(
  EXPORT "${PROJECT_NAME}Targets"
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
  NAMESPACE "${PROJECT_NAME}"
)


# Configure the project for packaging
include("CmakePackageConfigHelpers")

# Version macros for the package configuration
set(CONF_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set(CONF_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
set(CONF_VERSION_PATCH "${${PROJECT_NAME}_VERSION_PATCH}")

# Include directories macro for the package configuration for build interface
set(
  CONF_INCLUDE_DIRS
  "${CMAKE_CURRENT_BINARY_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Configure the project config file for build interface
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}"
  PATH_VARS CONF_INCLUDE_DIRS
  CONF_VERSION_MAJOR CONF_VERSION_MINOR CONF_VERSION_PATCH
)

# Include directories macro for the package configuration for install interface
set(CONF_INCLUDE_DIRS "include")

# Configure the project config file for install interface
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/install/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}"
  PATH_VARS CONF_INCLUDE_DIRS
  CONF_VERSION_MAJOR CONF_VERSION_MINOR CONF_VERSION_PATCH
)

# Configure the project version config file
string(
  CONCAT FULL_VERSION
  "${${PROJECT_NAME}_VERSION_MAJOR}."
  "${${PROJECT_NAME}_VERSION_MINOR}."
  "${${PROJECT_NAME}_VERSION_PATCH}"
)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION "${FULL_VERSION}"
  COMPATIBILITY AnyNewerVersion
)

# Install rules for the project config and version config files
install(
  FILES
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/install/${PROJECT_NAME}Config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION "lib/cmake/${PROJECT_NAME}"
)