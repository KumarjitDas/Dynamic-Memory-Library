#include "mem/mem.h"


#include <stdio.h>


int main()
{
  printf("\nex1\n\n");

  int maj, min;
  memLibVersion(&maj, &min, NULL);
  printf("version %d.%d\n\n", maj, min);

  int *arr = NULL;
  int len = 5;
  int ret = allocMem(&arr, len * sizeof(int), NULL, 0, NULL, 0);
  printf("ret: %d\n\n", ret);

  if(ret)
  {
    printf("Unable to allocate memory.\n\n");

    return 1;
  }

  size_t size = memSize(arr);
  printf("size: %llu\n\n", size);

  int val = -69;
  setMem(arr + 1, 3 * sizeof(int), &val, sizeof(int));

  printf("arr content:\n\n> ");
  for(int i = 0; i < len; i++) printf("%d, ", arr[i]);
  printf("\n\n");

  ret = freeMem(&arr);
  printf("ret: %d\n\n", ret);

  if(!arr) printf("arr is NULL\n\n");

  return 0;
}