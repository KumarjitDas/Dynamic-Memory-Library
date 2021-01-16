# dir: root/include/mem
# file: CMakeLists.txt


# Add the header files to the library
set(HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/mem.h")
target_sources(${PROJECT_NAME} PRIVATE "${HEADER_FILES}")

# Install rules for the header files
install(FILES ${HEADER_FILES} DESTINATION "include/${PROJECT_NAME}")