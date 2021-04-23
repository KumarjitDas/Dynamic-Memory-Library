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

    if (dynmem.memory)
        free(dynmem.memory);

    ClearDynMem(&dynmem);

    return 0;
}
