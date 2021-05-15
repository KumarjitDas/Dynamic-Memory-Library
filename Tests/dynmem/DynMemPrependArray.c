#include "check.h"
#include "dynmem/dynmem.h"

#include <stdlib.h>

START_TEST(Null_dynmem) {
   int32_t *array1 = malloc(4);

   ck_assert_int_eq(DynMemPrependArray(NULL, NULL, 0), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemPrependArray(NULL, NULL, 1), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemPrependArray(NULL, array1, 0), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemPrependArray(NULL, array1, 1), DYNMEM_FAILED);
   free(array1);
}
END_TEST

START_TEST(Nonnull_dynmem) {
   dynmem_t dynmem;
   int32_t *array1 = malloc(4);
   *array1 = -69;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemPrependArray(&dynmem, NULL, 0), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemPrependArray(&dynmem, NULL, 1), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemPrependArray(&dynmem, array1, 0), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemPrependArray(&dynmem, array1, 1), DYNMEM_SUCCEED);
   ck_assert_int_eq(*(int32_t *)(dynmem.m + 16), -69);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
   free(array1);
}
END_TEST

START_TEST(Size_not_changed) {
   dynmem_t dynmem;
   int32_t *array1 = malloc(20);

   for (int32_t i = 0; i < 5; i++)
      array1[i] = i;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemPrependArray(&dynmem, array1, 5), DYNMEM_SUCCEED);

   int32_t *array2 = (int32_t *)(dynmem.m);

   for (int32_t i = 0; i < 5; i++)
      ck_assert_int_eq(array1[i], array2[i]);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
   free(array1);
}
END_TEST

START_TEST(Extended_size) {
   dynmem_t dynmem;
   int32_t *array1 = malloc(40);

   for (int32_t i = 0; i < 10; i++)
      array1[i] = i;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemPrependArray(&dynmem, array1, 10), DYNMEM_SUCCEED);

   int32_t *array2 = (int32_t *)(dynmem.m + 20);

   for (int32_t i = 0; i < 10; i++)
      ck_assert_int_eq(array1[i], array2[i]);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
   free(array1);
}
END_TEST

START_TEST(More_extended_size) {
   dynmem_t dynmem;
   int32_t *array1 = malloc(80);

   for (int32_t i = 0; i < 20; i++)
      array1[i] = i;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemPrependArray(&dynmem, array1, 20), DYNMEM_SUCCEED);

   int32_t *array2 = (int32_t *)(dynmem.m + 60);

   for (int32_t i = 0; i < 20; i++)
      ck_assert_int_eq(array1[i], array2[i]);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
   free(array1);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemPrependArray\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, Null_dynmem);
   tcase_add_test(test_cases, Nonnull_dynmem);
   tcase_add_test(test_cases, Size_not_changed);
   tcase_add_test(test_cases, Extended_size);
   tcase_add_test(test_cases, More_extended_size);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
