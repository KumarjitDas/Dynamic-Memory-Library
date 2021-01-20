# dir: root/src/mem
# file: CMakeLists.txt


# Add the source files to the library
set(SRC_FILES "mem.c" "_mem.c")
foreach(SRC_FILE ${SRC_FILES})

   target_sources(
      ${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_FILE}"
   )

endforeach()

# Install rules for the source files
install(FILES ${SRC_FILES} DESTINATION "src/mem")