add_executable(
    "DynMem_utility_tester_DynMemUtilitySetMemoryBlock" 
    "DynMemUtilitySetMemoryBlock.c"
)
target_link_libraries(
    "DynMem_utility_tester_DynMemUtilitySetMemoryBlock" PRIVATE
    DynMem::dynmem Check::check
)
add_test(
    NAME    "DynMem_utility_test0001_DynMemUtilitySetMemoryBlock"
    COMMAND "DynMem_utility_tester_DynMemUtilitySetMemoryBlock"
)

add_executable(
    "DynMem_utility_tester_DynMemUtilitySetMemory" 
    "DynMemUtilitySetMemory.c"
)
target_link_libraries(
    "DynMem_utility_tester_DynMemUtilitySetMemory" PRIVATE
    DynMem::dynmem Check::check
)
add_test(
    NAME    "DynMem_utility_test0002_DynMemUtilitySetMemory"
    COMMAND "DynMem_utility_tester_DynMemUtilitySetMemory"
)
