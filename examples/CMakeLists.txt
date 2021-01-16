# dir: root/examples
# file: CMakeLists.txt


# Add all the examples in the directory
set(
  EXAMPLE_FILES
  "ex1_allocMem"
)
foreach(FILE "${EXAMPLE_FILES}")

  add_executable(${FILE} "${CMAKE_CURRENT_SOURCE_DIR}/${FILE}.c")
  target_link_libraries(${FILE} PRIVATE "${PROJECT_NAME}::${PROJECT_NAME}")

endforeach()