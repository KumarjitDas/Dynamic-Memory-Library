add_executable("DynMem_dynmem_tester_DynMemAllocate" "test01_DynMemAllocate.c")
target_link_libraries("DynMem_dynmem_tester_DynMemAllocate" PRIVATE DynMem::dynmem)

add_test(
    NAME    "DynMem_dynmem_test01_DynMemAllocate"
    COMMAND "DynMem_dynmem_tester_DynMemAllocate"
)

add_executable("DynMem_dynmem_tester_DynMemDeallocate" "test02_DynMemDeallocate.c")
target_link_libraries("DynMem_dynmem_tester_DynMemDeallocate" PRIVATE DynMem::dynmem)

add_test(
    NAME    "DynMem_dynmem_test02_DynMemDeallocate"
    COMMAND "DynMem_dynmem_tester_DynMemDeallocate"
)

add_executable("DynMem_dynmem_tester_DynMemSet" "test03_DynMemSet.c")
target_link_libraries("DynMem_dynmem_tester_DynMemSet" PRIVATE DynMem::dynmem)

add_test(
    NAME    "DynMem_dynmem_test03_DynMemSet"
    COMMAND "DynMem_dynmem_tester_DynMemSet"
)
