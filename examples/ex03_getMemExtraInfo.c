#include "mem/mem.h"


#include <stdio.h>


typedef struct
{
  short s;
  int i;
  long long ll;
}
ex_inf_t;



void printExInfT(ex_inf_t *ptr)
{
  printf("s: %hd\ni: %d\nll: %lld\n\n", ptr->s, ptr->i, ptr->ll);
}



int main()
{
  printf("\nex1\n\n");

  int maj, min;
  memLibVersion(&maj, &min, NULL);
  printf("version %d.%d\n\n", maj, min);

  ex_inf_t ex_inf = {
    .s = 69, .i = 420, .ll = -42069
  };
  printExInfT(&ex_inf);

  int *arr = NULL;
  int len  = 5;
  int ret  = allocMem(
    &arr, len * sizeof(int), NULL, 0,
    &ex_inf, sizeof(ex_inf_t)
  );
  printf("ret: %d\n\n", ret);

  if(ret)
  {
    printf("Unable to allocate memory.\n\n");

    return 1;
  }

  printf("mem size: %llu\n\n", memSize(arr));

  printf("extra info size: %llu\n\n", memExtraInfoSize(arr));

  ex_inf_t *tmp_ex_inf = NULL;
  ret = getMemExtraInfo(&tmp_ex_inf, arr);
  printf("ret: %d\n\n", ret);

  if(!ret)
  {
    printf("extra info content:\n\n");
    printExInfT(tmp_ex_inf);
  }

  ret = freeMem(&arr);
  printf("ret: %d\n\n", ret);

  if(!arr) printf("arr is NULL\n\n");

  return 0;
}