# dir: root/src
# file: CMakeLists.txt


# Add the source files to the library
set(
  SRC_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/util.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/util.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/mem.c"
)
target_sources(${PROJECT_NAME} PRIVATE "${SRC_FILES}")

# Install rules for the source files
install(FILES ${SRC_FILES} DESTINATION "src/${PROJECT_NAME}")