#include "dynmem/dynmem.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc <= 1)
        return 0;

    size_t count = strtoull(argv[1], NULL, 10);
    int *array = malloc(sizeof(int) * count);
    if (!array) {
        printf("Error occured while allocating memory!\n");
        return 1;
    }

    dynmem_t dynmem;
    CreateDynMem(&dynmem, &array, sizeof(int), count);

    printf("element_size:  %zu\n"
           "element_count: %zu\n"
           "initial_size:  %zu\n"
           "current_size:  %zu\n"
           "array %s NULL\n",
           dynmem.element_size, dynmem.element_count, dynmem.initial_size, dynmem.current_size,
           !array ? "is" : "is not"
          );

    if (dynmem.memory) {
        free(dynmem.memory);

        printf("Memory cleared.\n");
    }

    ClearDynMem(&dynmem);

    printf("After clearing dynmem...\n"
           "element_size:  %zu\n"
           "element_count: %zu\n"
           "initial_size:  %zu\n"
           "current_size:  %zu\n"
           "memory %s cleared\n",
           dynmem.element_size, dynmem.element_count, dynmem.initial_size, dynmem.current_size,
           !dynmem.memory ? "is" : "is not"
          );

    return 0;
}
