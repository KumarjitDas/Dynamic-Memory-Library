add_executable("tester" "test.c")
target_link_libraries("tester" PRIVATE DynMem::dynmem)

# Arguments: start, end, step, size, array_size
add_test(
    NAME    "Test_01"
    COMMAND "tester"
)
