#include "mem/mem.h"

#include <stdio.h>

void printLibName(void)
{
  printf("\n Dynamic-Memory-Library %d.%d",
    mem_VERSION_MAJOR, mem_VERSION_MINOR);
}