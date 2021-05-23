set(
   TEST_FUNCTION_NAMES
   "DynMemAllocate" "DynMemDeallocate" "DynMemReduce_s" "DynMemReduce" "DynMemAppend" "DynMemPrepend" "DynMemDeduct"
   "DynMemDeductFront" "DynMemAppendValues" "DynMemPrependValues" "DynMemDeductValues_s"
   "DynMemAppendArray" "DynMemPrependArray" "DynMemSetElementSize" "DynMemGetElementSize" "DynMemGetSize"
   "DynMemGetLength" "DynMemGetEndIndex_s" "DynMemGetEndIndex" "DynMemSetForAppending" "DynMemSetForPrepending"
   "DynMemGetBegin" "DynMemGetEnd" "DynMemGetHeapSize" "DynMemGetHeapPointer" "DynMemReset" "DynMemResetMemory"
   "DynMemSet_s" "DynMemSet" "DynMemGet_s" "DynMemGet" "DynMemSetValues_s" "DynMemSetValues" "DynMemGetValues_s"
   "DynMemGetValues" "DynMemCopy" "DynMemCopyExceptValues" "DynMemCopyInitial"
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

   set(EXECUTABLE_NAME  "DynMem_dynmem_tester_${TEST_FUNCTION_NAME}")

   add_executable("${EXECUTABLE_NAME}" "${TEST_FUNCTION_NAME}.c")
   target_link_libraries("${EXECUTABLE_NAME}" PRIVATE DynMem::dynmem Check::check)

   add_test(
      NAME "DynMem_dynmem_test${LEADING_ZEROS}${TEST_COUNTER}_${TEST_FUNCTION_NAME}"
      COMMAND "${EXECUTABLE_NAME}"
   )
endforeach()

set(SUBDIRECTORIES "utility")

foreach(VAR ${SUBDIRECTORIES})
   add_subdirectory(${VAR})
endforeach()