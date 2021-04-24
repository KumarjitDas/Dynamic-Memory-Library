add_executable("DynMem_utility_tester" "test.c")
target_link_libraries("DynMem_utility_tester" PRIVATE DynMem::dynmem)

add_test(
    NAME    "DynMem_utility_test_01"
    COMMAND "DynMem_utility_tester"
)
