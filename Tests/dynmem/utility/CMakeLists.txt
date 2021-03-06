set(
   TEST_FUNCTION_NAMES
   "DynMemUtilitySetMemoryBlock" "DynMemUtilitySetMemory" "DynMemUtilityResetMemory" "DynMemUtilityReduce"
   "DynMemUtilityReduceToMemory" "DynMemUtilitySetMemoryBlockReverse" "DynMemUtilityAppend" "DynMemUtilityPrepend"
)
set(TEST_COUNTER 0)

foreach(TEST_FUNCTION_NAME ${TEST_FUNCTION_NAMES})
   math(EXPR TEST_COUNTER "${TEST_COUNTER} + 1" OUTPUT_FORMAT DECIMAL)

   if(${TEST_COUNTER} LESS 10)
      set(LEADING_ZEROS "000")
   elseif(${TEST_COUNTER} LESS 100)
      set(LEADING_ZEROS "00")
   elseif(${TEST_COUNTER} LESS 1000)
      set(LEADING_ZEROS "0")
   else()
      set(LEADING_ZEROS "")
   endif()

   set(EXECUTABLE_NAME  "DynMem_utility_tester_${TEST_FUNCTION_NAME}")

   add_executable("${EXECUTABLE_NAME}" "${TEST_FUNCTION_NAME}.c")
   target_link_libraries("${EXECUTABLE_NAME}" PRIVATE DynMem::dynmem Check::check)

   add_test(
      NAME "DynMem_utility_test${LEADING_ZEROS}${TEST_COUNTER}_${TEST_FUNCTION_NAME}"
      COMMAND "${EXECUTABLE_NAME}"
   )
endforeach()
