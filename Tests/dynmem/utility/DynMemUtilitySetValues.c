#include "check.h"

#ifndef DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#define DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_SET_GET_H
#define DYNMEM_INTERNAL_USE_UTILITY_SET_GET_H
#endif

#include "dynmem/dynmem.h"
#include "dynmem/utility/defines.h"
#include "dynmem/utility/set-get.h"

START_TEST(all_positive_index) {
   dynmem_t dynmem;
   int value = -69;
   intmax_t begin, end;
   intmax_t element_size = sizeof(value);

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   value++; begin = 0; end = 10;
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, begin * element_size, end * element_size, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * element_size)), value);

   value++; begin = 1; end = 10;
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, begin * element_size, end * element_size, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * element_size)), value);

   value++; begin = 0; end = 9;
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, begin * element_size, end * element_size, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * element_size)), value);

   value++; begin = 1; end = 9;
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, begin * element_size, end * element_size, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * element_size)), value);

   value++; begin = 4; end = 5;
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, begin * element_size, end * element_size, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * element_size)), value);

   value++; begin = 5; end = 5;
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, begin * element_size, end * element_size, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, 0 * element_size, 999 * element_size, &value), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(negative_end_index) {
   dynmem_t dynmem;
   int value = -69;
   intmax_t begin, end;
   intmax_t element_size = sizeof(value);

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   value++; begin = 0; end = -1;
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, begin * element_size, end * element_size, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < 10; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * element_size)), value);

   value++; begin = 1; end = -1;
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, begin * element_size, end * element_size, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < 10; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * element_size)), value);

   value++; begin = 0; end = -2;
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, begin * element_size, end * element_size, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < 9; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * element_size)), value);

   value++; begin = 1; end = -2;
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, begin * element_size, end * element_size, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < 9; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * element_size)), value);

   value++; begin = -6; end = -5;
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, begin * element_size, end * element_size, &value), DYNMEM_SUCCEED);
   for (int i = 4; i < 6; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * element_size)), value);

   value++; begin = -5; end = -5;
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, begin * element_size, end * element_size, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(*((int *)(dynmem.m + 5 * element_size)), value);

   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, 0 * element_size, -999 * element_size, &value), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(negative_begin_index) {
   dynmem_t dynmem;
   int value = 420;
   intmax_t begin, end;
   intmax_t element_size = sizeof(value);

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   value++; begin = -10; end = 10;
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, begin * element_size, end * element_size, &value), DYNMEM_SUCCEED);
   for (int i = 0; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * element_size)), value);

   value++; begin = -9; end = 10;
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, begin * element_size, end * element_size, &value), DYNMEM_SUCCEED);
   for (int i = 1; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * element_size)), value);

   value++; begin = -10; end = 9;
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, begin * element_size, end * element_size, &value), DYNMEM_SUCCEED);
   for (int i = 0; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * element_size)), value);

   value++; begin = -9; end = 9;
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, begin * element_size, end * element_size, &value), DYNMEM_SUCCEED);
   for (int i = 1; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * element_size)), value);

   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, -4 * element_size, -4 * element_size, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(*((int *)(dynmem.m + 6 * element_size)), value);

   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, -5 * element_size, -6 * element_size, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemUtilitySetValues(&dynmem, -999 * element_size, 10 * element_size, &value), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemUtilitySetValues\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, all_positive_index);
   tcase_add_test(test_cases, negative_end_index);
   tcase_add_test(test_cases, negative_begin_index);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
