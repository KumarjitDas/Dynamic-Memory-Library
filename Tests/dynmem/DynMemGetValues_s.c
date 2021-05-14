#include "check.h"
#include "dynmem/dynmem.h"

#include <stdlib.h>

START_TEST(null_test__null_size) {
   dynmem_t dynmem;
   int32_t *memory = malloc(40);

   ck_assert_int_eq(DynMemGetValues_s(NULL, 0, 16, NULL, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 4, 12, NULL, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 8, 8, NULL, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 0, -4, NULL, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 4, -8, NULL, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 8, -12, NULL, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -20, 16, NULL, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -16, 12, NULL, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -12, 8, NULL, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -20, -4, NULL, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -16, -8, NULL, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -12, -12, NULL, 4, NULL), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemGetValues_s(NULL, 0, 16, memory, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 4, 12, memory, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 8, 8, memory, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 0, -4, memory, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 4, -8, memory, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 8, -12, memory, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -20, 16, memory, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -16, 12, memory, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -12, 8, memory, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -20, -4, memory, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -16, -8, memory, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -12, -12, memory, 4, NULL), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 0, 16, NULL, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 4, 12, NULL, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 8, 8, NULL, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 0, -4, NULL, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 4, -8, NULL, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 8, -12, NULL, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -20, 16, NULL, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -16, 12, NULL, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -12, 8, NULL, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -20, -4, NULL, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -16, -8, NULL, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -12, -12, NULL, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);

   free(memory);
}
END_TEST

START_TEST(null_test__nonnull_size) {
   dynmem_t dynmem;
   int32_t *memory = malloc(40);
   intmax_t size;

   ck_assert_int_eq(DynMemGetValues_s(NULL, 0, 16, NULL, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 4, 12, NULL, 12, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 8, 8, NULL, 4, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 0, -4, NULL, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 4, -8, NULL, 12, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 8, -12, NULL, 4, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -20, 16, NULL, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -16, 12, NULL, 12, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -12, 8, NULL, 4, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -20, -4, NULL, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -16, -8, NULL, 12, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -12, -12, NULL, 4, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);

   ck_assert_int_eq(DynMemGetValues_s(NULL, 0, 16, memory, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 4, 12, memory, 12, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 8, 8, memory, 4, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 0, -4, memory, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 4, -8, memory, 12, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, 8, -12, memory, 4, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -20, 16, memory, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -16, 12, memory, 12, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -12, 8, memory, 4, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -20, -4, memory, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -16, -8, memory, 12, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(NULL, -12, -12, memory, 4, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 0, 16, NULL, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 4, 12, NULL, 12, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 8, 8, NULL, 4, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 0, -4, NULL, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 4, -8, NULL, 12, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 8, -12, NULL, 4, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -20, 16, NULL, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -16, 12, NULL, 12, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -12, 8, NULL, 4, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -20, -4, NULL, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -16, -8, NULL, 12, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -12, -12, NULL, 4, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);

   free(memory);
}
END_TEST

START_TEST(value_not_added__null_size) {
   dynmem_t dynmem;
   int32_t *memory = malloc(40);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 0, 16, memory, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 4, 12, memory, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 8, 8, memory, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 0, -4, memory, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 4, -8, memory, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 8, -12, memory, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -20, 16, memory, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -16, 12, memory, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -12, 8, memory, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -20, -4, memory, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -16, -8, memory, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -12, -12, memory, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);

   free(memory);
}
END_TEST

START_TEST(value_not_added__nonnull_size) {
   dynmem_t dynmem;
   int32_t *memory = malloc(40);
   intmax_t size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 0, 16, memory, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 4, 12, memory, 12, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 8, 8, memory, 4, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 0, -4, memory, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 4, -8, memory, 12, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 8, -12, memory, 4, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -20, 16, memory, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -16, 12, memory, 12, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -12, 8, memory, 4, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -20, -4, memory, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -16, -8, memory, 12, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -12, -12, memory, 4, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);

   free(memory);
}
END_TEST

START_TEST(value_added__null_size) {
   dynmem_t dynmem;
   int32_t *memory = malloc(20);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   int32_t *array = (int32_t *)(dynmem.m + dynmem.bi);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 0, 16, memory, -20, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], memory[i]);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 4, 12, memory, 20, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], memory[i - 1]);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 8, 8, memory, 20, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], memory[0]);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 8, 20, memory, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 24, 8, memory, 20, NULL), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 0, -4, memory, 0, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], memory[i]);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 4, -8, memory, 20, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], memory[i - 1]);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 8, -12, memory, 20, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], memory[0]);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 8, -24, memory, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 24, -12, memory, 20, NULL), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -20, 16, memory, 20, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], memory[i]);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -16, 12, memory, 20, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], memory[i - 1]);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -12, 8, memory, 20, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], memory[0]);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -12, 24, memory, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -24, 8, memory, 20, NULL), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -20, -4, memory, 40, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], memory[i]);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -16, -8, memory, 20, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], memory[i - 1]);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -12, -12, memory, 20, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], memory[0]);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -12, -24, memory, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -24, -12, memory, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);

   free(memory);
}
END_TEST

START_TEST(value_added__nonnull_size) {
   dynmem_t dynmem;
   int32_t *memory = malloc(20);
   intmax_t size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   int32_t *array = (int32_t *)(dynmem.m + dynmem.bi);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 0, 16, memory, -20, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(size, 20);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], memory[i]);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 4, 12, memory, 20, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(size, 12);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], memory[i - 1]);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 8, 8, memory, 20, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], memory[0]);
   ck_assert_int_eq(size, 4);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 8, 20, memory, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 24, 8, memory, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 0, -4, memory, 0, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(size, 20);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], memory[i]);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 4, -8, memory, 20, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(size, 12);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], memory[i - 1]);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 8, -12, memory, 20, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], memory[0]);
   ck_assert_int_eq(size, 4);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 8, -24, memory, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, 24, -12, memory, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -20, 16, memory, 20, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(size, 20);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], memory[i]);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -16, 12, memory, 20, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(size, 12);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], memory[i - 1]);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -12, 8, memory, 20, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], memory[0]);
   ck_assert_int_eq(size, 4);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -12, 24, memory, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -24, 8, memory, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -20, -4, memory, 40, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(size, 20);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], memory[i]);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -16, -8, memory, 20, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(size, 12);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], memory[i - 1]);

   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -12, -12, memory, 20, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], memory[0]);
   ck_assert_int_eq(size, 4);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -12, -24, memory, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues_s(&dynmem, -24, -12, memory, 20, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);

   free(memory);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemGetValues_s\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_test__null_size);
   tcase_add_test(test_cases, null_test__nonnull_size);
   tcase_add_test(test_cases, value_not_added__null_size);
   tcase_add_test(test_cases, value_not_added__nonnull_size);
   tcase_add_test(test_cases, value_added__null_size);
   tcase_add_test(test_cases, value_added__nonnull_size);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
