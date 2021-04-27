add_executable(
    "DynMem_utility_tester_DynMemUtilitySetMemoryBlocks" 
    "DynMemUtilitySetMemoryBlocks.c"
)
target_link_libraries("DynMem_utility_tester_DynMemUtilitySetMemoryBlocks" PRIVATE DynMem::dynmem)

add_test(
    NAME    "DynMem_utility_test0001_DynMemUtilitySetMemoryBlocks"
    COMMAND "DynMem_utility_tester_DynMemUtilitySetMemoryBlocks"
)

add_executable(
    "DynMem_utility_tester_DynMemUtilitySetMemory" 
    "DynMemUtilitySetMemory.c"
)
target_link_libraries("DynMem_utility_tester_DynMemUtilitySetMemory" PRIVATE DynMem::dynmem)

add_test(
    NAME    "DynMem_utility_test0001_DynMemUtilitySetMemory"
    COMMAND "DynMem_utility_tester_DynMemUtilitySetMemory"
)
