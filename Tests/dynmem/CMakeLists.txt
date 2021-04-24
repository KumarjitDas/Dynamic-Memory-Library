add_executable("DynMem_dynmem_tester_DynMemAllocate" "test01_DynMemAllocate.c")
target_link_libraries("DynMem_dynmem_tester_DynMemAllocate" PRIVATE DynMem::dynmem)

add_test(
    NAME    "DynMem_dynmem_test01_DynMemAllocate"
    COMMAND "DynMem_dynmem_tester_DynMemAllocate"
)
