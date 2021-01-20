# dir: root/tests/t01_MemLibVersion
# file: CMakeLists.txt


# Add the executable for testing
set(EXE_NAME "t02_AllocMem")
add_executable(${EXE_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/main.c")
target_link_libraries(${EXE_NAME} PRIVATE ${PROJECT_NAME})


# Add the tests
set(TOT_TESTS 9)
foreach(COUNT RANGE 1 ${TOT_TESTS})

   if(${COUNT} LESS 10)
      set(ZERO "0")
   else()
      set(ZERO "")
   endif()

   set(TEST_NAME "${EXE_NAME}_test${ZERO}${COUNT}")
   string(
      SUBSTRING ${TEST_NAME} 4 -1 TEST_NAME
   )
   add_test(
      NAME ${TEST_NAME}
      COMMAND ${EXE_NAME} ${COUNT}
      WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
   )

endforeach()