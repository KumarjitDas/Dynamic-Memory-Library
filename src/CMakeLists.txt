# dir: root/src
# file: CMakeLists.txt


# Add all the subdirectories of this directory
set(INCDIRS "util")
set(SUBDIRS "${INCDIRS}" "mem")
foreach(SUBDIR ${SUBDIRS})

   add_subdirectory(${SUBDIR})

endforeach()

# Include the "util.h" header file
target_include_directories(${PROJECT_NAME} PRIVATE "${INCDIRS}")