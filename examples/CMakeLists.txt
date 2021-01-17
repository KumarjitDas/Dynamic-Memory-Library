# dir: root/examples
# file: CMakeLists.txt


# Add all the examples in the directory
set(
  EXAMPLES
  "ex01_allocMem" "ex02_setMem" "ex03_getMemExtraInfo" "ex04_cpyMem"
)
foreach(EXAMPLE ${EXAMPLES})

  add_executable(${EXAMPLE} "${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE}.c")
  target_link_libraries(${EXAMPLE} PRIVATE "${PROJECT_NAME}::${PROJECT_NAME}")

endforeach()