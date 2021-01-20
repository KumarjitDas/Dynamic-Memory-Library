# dir: root/examples
# file: CMakeLists.txt


# Add all the examples in the directory
set(
  EXAMPLES
  # mem.h examples
  "ex01_MemLibVersion" "ex02_AllocMem"    "ex03_ResizeMem"  "ex04_FreeMem"
  "ex05_MemSize"       "ex06_ClrMem"      "ex07_SetMem"     "ex08_CpyMem"
  "ex09_ApnMem"        "ex10_MemInfoSize" "ex11_GetMemInfo"
  # _fast.h examples "ex12_FastFuncs"
)
foreach(EXAMPLE ${EXAMPLES})

  add_executable(${EXAMPLE} "${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE}.c")
  target_link_libraries(${EXAMPLE} PRIVATE "${PROJECT_NAME}::${PROJECT_NAME}")

endforeach()