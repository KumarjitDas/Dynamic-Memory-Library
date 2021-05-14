#include "check.h"
#include "dynmem/dynmem.h"

#include <stdlib.h>

START_TEST(null_test__null_size) {
   dynmem_t dynmem;
   int32_t *memory = malloc(40);

   ck_assert_int_eq(DynMemGetValues(NULL, 0, 4, NULL, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, 1, 3, NULL, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, 2, 2, NULL, 1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, 0, -1, NULL, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, 1, -2, NULL, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, 2, -3, NULL, 1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, -5, 4, NULL, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, -4, 3, NULL, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, -3, 2, NULL, 1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, -5, -1, NULL, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, -4, -2, NULL, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, -3, -3, NULL, 1, NULL), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemGetValues(NULL, 0, 4, memory, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, 1, 3, memory, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, 2, 2, memory, 1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, 0, -1, memory, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, 1, -2, memory, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, 2, -3, memory, 1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, -5, 4, memory, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, -4, 3, memory, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, -3, 2, memory, 1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, -5, -1, memory, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, -4, -2, memory, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, -3, -3, memory, 1, NULL), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 0, 4, NULL, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 1, 3, NULL, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 2, 2, NULL, 1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 0, -1, NULL, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 1, -2, NULL, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 2, -3, NULL, 1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -5, 4, NULL, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -4, 3, NULL, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -3, 2, NULL, 1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -5, -1, NULL, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -4, -2, NULL, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -3, -3, NULL, 1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);

   free(memory);
}
END_TEST

START_TEST(null_test__nonnull_size) {
   dynmem_t dynmem;
   int32_t *memory = malloc(40);
   intmax_t length;

   ck_assert_int_eq(DynMemGetValues(NULL, 0, 4, NULL, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, 1, 3, NULL, 3, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, 2, 2, NULL, 1, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, 0, -1, NULL, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, 1, -2, NULL, 3, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, 2, -3, NULL, 1, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, -5, 4, NULL, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, -4, 3, NULL, 3, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, -3, 2, NULL, 1, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, -5, -1, NULL, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, -4, -2, NULL, 3, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, -3, -3, NULL, 1, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);

   ck_assert_int_eq(DynMemGetValues(NULL, 0, 4, memory, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, 1, 3, memory, 3, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, 2, 2, memory, 1, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, 0, -1, memory, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, 1, -2, memory, 3, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, 2, -3, memory, 1, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, -5, 4, memory, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, -4, 3, memory, 3, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, -3, 2, memory, 1, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, -5, -1, memory, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, -4, -2, memory, 3, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(NULL, -3, -3, memory, 1, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 0, 4, NULL, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 1, 3, NULL, 3, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 2, 2, NULL, 1, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 0, -1, NULL, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 1, -2, NULL, 3, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 2, -3, NULL, 1, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -5, 4, NULL, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -4, 3, NULL, 3, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -3, 2, NULL, 1, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -5, -1, NULL, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -4, -2, NULL, 3, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -3, -3, NULL, 1, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);

   free(memory);
}
END_TEST

START_TEST(value_not_added__null_size) {
   dynmem_t dynmem;
   int32_t *memory = malloc(40);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 0, 4, memory, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 1, 3, memory, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 2, 2, memory, 1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 0, -1, memory, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 1, -2, memory, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 2, -3, memory, 1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -5, 4, memory, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -4, 3, memory, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -3, 2, memory, 1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -5, -1, memory, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -4, -2, memory, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -3, -3, memory, 1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);

   free(memory);
}
END_TEST

START_TEST(value_not_added__nonnull_size) {
   dynmem_t dynmem;
   int32_t *memory = malloc(40);
   intmax_t length;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 0, 4, memory, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 1, 3, memory, 3, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 2, 2, memory, 1, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 0, -1, memory, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 1, -2, memory, 3, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 2, -3, memory, 1, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -5, 4, memory, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -4, 3, memory, 3, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -3, 2, memory, 1, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -5, -1, memory, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -4, -2, memory, 3, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -3, -3, memory, 1, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
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

   ck_assert_int_eq(DynMemGetValues(&dynmem, 0, 4, memory, -5, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], memory[i]);

   ck_assert_int_eq(DynMemGetValues(&dynmem, 1, 3, memory, 5, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], memory[i - 1]);

   ck_assert_int_eq(DynMemGetValues(&dynmem, 2, 2, memory, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], memory[0]);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 2, 5, memory, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 24, 2, memory, 5, NULL), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemGetValues(&dynmem, 0, -1, memory, 0, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], memory[i]);

   ck_assert_int_eq(DynMemGetValues(&dynmem, 1, -2, memory, 5, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], memory[i - 1]);

   ck_assert_int_eq(DynMemGetValues(&dynmem, 2, -3, memory, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], memory[0]);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 2, -24, memory, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 24, -3, memory, 5, NULL), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemGetValues(&dynmem, -5, 4, memory, 5, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], memory[i]);

   ck_assert_int_eq(DynMemGetValues(&dynmem, -4, 3, memory, 5, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], memory[i - 1]);

   ck_assert_int_eq(DynMemGetValues(&dynmem, -3, 2, memory, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], memory[0]);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -3, 24, memory, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -24, 2, memory, 5, NULL), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemGetValues(&dynmem, -5, -1, memory, 40, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], memory[i]);

   ck_assert_int_eq(DynMemGetValues(&dynmem, -4, -2, memory, 5, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], memory[i - 1]);

   ck_assert_int_eq(DynMemGetValues(&dynmem, -3, -3, memory, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], memory[0]);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -3, -24, memory, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -24, -3, memory, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);

   free(memory);
}
END_TEST

START_TEST(value_added__nonnull_size) {
   dynmem_t dynmem;
   int32_t *memory = malloc(20);
   intmax_t length;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   int32_t *array = (int32_t *)(dynmem.m + dynmem.bi);

   ck_assert_int_eq(DynMemGetValues(&dynmem, 0, 4, memory, -5, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(length, 5);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], memory[i]);

   ck_assert_int_eq(DynMemGetValues(&dynmem, 1, 3, memory, 5, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(length, 3);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], memory[i - 1]);

   ck_assert_int_eq(DynMemGetValues(&dynmem, 2, 2, memory, 5, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], memory[0]);
   ck_assert_int_eq(length, 1);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 2, 5, memory, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 24, 2, memory, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);

   ck_assert_int_eq(DynMemGetValues(&dynmem, 0, -1, memory, 0, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(length, 5);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], memory[i]);

   ck_assert_int_eq(DynMemGetValues(&dynmem, 1, -2, memory, 5, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(length, 3);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], memory[i - 1]);

   ck_assert_int_eq(DynMemGetValues(&dynmem, 2, -3, memory, 5, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], memory[0]);
   ck_assert_int_eq(length, 1);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 2, -24, memory, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 24, -3, memory, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);

   ck_assert_int_eq(DynMemGetValues(&dynmem, -5, 4, memory, 5, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(length, 5);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], memory[i]);

   ck_assert_int_eq(DynMemGetValues(&dynmem, -4, 3, memory, 5, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(length, 3);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], memory[i - 1]);

   ck_assert_int_eq(DynMemGetValues(&dynmem, -3, 2, memory, 5, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], memory[0]);
   ck_assert_int_eq(length, 1);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -3, 24, memory, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -24, 2, memory, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);

   ck_assert_int_eq(DynMemGetValues(&dynmem, -5, -1, memory, 40, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(length, 5);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], memory[i]);

   ck_assert_int_eq(DynMemGetValues(&dynmem, -4, -2, memory, 5, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(length, 3);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], memory[i - 1]);

   ck_assert_int_eq(DynMemGetValues(&dynmem, -3, -3, memory, 5, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], memory[0]);
   ck_assert_int_eq(length, 1);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -3, -24, memory, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -24, -3, memory, 5, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);

   free(memory);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemGetValues\" function");
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
