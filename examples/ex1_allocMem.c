#include "mem/mem.h"


#include <stdio.h>


int main()
{
  printf("\nex1\n\n");

  int maj, min;
  memLibVersion(&maj, &min, NULL);
  printf("version %d.%d\n\n", maj, min);

  int *arr = NULL;
  int val = 42069;
  int len = 5;
  int ret = allocMem(
    &arr, len * sizeof(int),
    &val, sizeof(int),
    NULL, 0
  );
  printf("ret: %d\n\n", ret);

  printf("arr content:\n\n> ");
  for(int i = 0; i < len; i++) printf("%d, ", arr[i]);
  printf("\n\n");

  ret = freeMem(&arr);
  printf("ret: %d\n\n", ret);

  if(!arr) printf("arr is NULL\n\n");

  return 0;
}