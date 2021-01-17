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
  int val = -69;
  int ret = allocMem(&arr, len * sizeof(int), &val, sizeof(int), NULL, 0);
  printf("ret: %d\n\n", ret);
  if(ret)
  {
    printf("Unable to allocate memory.\n\n");

    return 1;
  }

  arr[0] = 111; arr[2] = 222; arr[4] = 333;

  size_t size = memSize(arr);
  printf("arr size: %llu\n\n", size);

  printf("arr content:\n\n> ");
  for(size_t i = 0; i < size / sizeof(int); i++) printf("%d, ", arr[i]);
  printf("\n\n");

  int *arrcpy = NULL;
  ret = cpyMem(&arrcpy, arr, MEM_IDX_S, MEM_IDX_E);
  printf("ret: %d\n\n", ret);
  if(ret)
  {
    printf("Unable to copy memory.\n\n");

    ret = freeMem(&arr);
    printf("ret: %d\n\n", ret);

    return 1;
  }

  ret = freeMem(&arr);
  printf("ret: %d\n\n", ret);

  if(!arr) printf("arr is NULL\n\n");

  size = memSize(arrcpy);
  printf("arrcpy size: %llu\n\n", size);

  printf("arrcpy content:\n\n> ");
  for(size_t i = 0; i < size / sizeof(int); i++) printf("%d, ", arrcpy[i]);
  printf("\n\n");

  ret = freeMem(&arrcpy);
  printf("ret: %d\n\n", ret);

  if(!arrcpy) printf("arrcpy is NULL\n\n");

  return 0;
}