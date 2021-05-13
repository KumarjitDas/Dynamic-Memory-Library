#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_test) {
   int32_t value;
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemSetValues(NULL, 0, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(NULL, 1, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(NULL, 2, 2, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(NULL, 0, -1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(NULL, 1, -2, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(NULL, 2, -3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(NULL, -5, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(NULL, -4, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(NULL, -3, 2, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(NULL, -5, -1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(NULL, -4, -2, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(NULL, -3, -3, NULL), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, 0, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, 1, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, 2, 2, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, 0, -1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, 1, -2, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, 2, -3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, -5, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, -4, 3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, -3, 2, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, -5, -1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, -4, -2, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, -3, -3, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(value_not_added) {
   dynmem_t dynmem;
   int32_t value = 420;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, 0, 4, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, 1, 3, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, 2, 2, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, 0, -1, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, 1, -2, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, 2, -3, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, -5, 4, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, -4, 3, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, -3, 2, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, -5, -1, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, -4, -2, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, -3, -3, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(value_added) {
   dynmem_t dynmem;
   int32_t value = 69;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   int32_t *array = (int32_t *)(dynmem.m + dynmem.bi);

   value++;
   ck_assert_int_eq(DynMemSetValues(&dynmem, 0, 4, &value), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], value);

   value++;
   ck_assert_int_eq(DynMemSetValues(&dynmem, 1, 3, &value), DYNMEM_SUCCEED);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], value);

   value++;
   ck_assert_int_eq(DynMemSetValues(&dynmem, 2, 2, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], value);
   ck_assert_int_eq(DynMemSetValues(&dynmem, 2, 5, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, 24, 2, &value), DYNMEM_FAILED);

   value++;
   ck_assert_int_eq(DynMemSetValues(&dynmem, 0, -1, &value), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], value);

   value++;
   ck_assert_int_eq(DynMemSetValues(&dynmem, 1, -2, &value), DYNMEM_SUCCEED);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], value);

   value++;
   ck_assert_int_eq(DynMemSetValues(&dynmem, 2, -3, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], value);
   ck_assert_int_eq(DynMemSetValues(&dynmem, 2, -24, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, 24, -3, &value), DYNMEM_FAILED);

   value++;
   ck_assert_int_eq(DynMemSetValues(&dynmem, -5, 4, &value), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], value);

   value++;
   ck_assert_int_eq(DynMemSetValues(&dynmem, -4, 3, &value), DYNMEM_SUCCEED);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], value);

   value++;
   ck_assert_int_eq(DynMemSetValues(&dynmem, -3, 2, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], value);
   ck_assert_int_eq(DynMemSetValues(&dynmem, -3, 24, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, -24, 2, &value), DYNMEM_FAILED);

   value++;
   ck_assert_int_eq(DynMemSetValues(&dynmem, -5, -1, &value), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i <= 4; i++)
      ck_assert_int_eq(array[i], value);

   value++;
   ck_assert_int_eq(DynMemSetValues(&dynmem, -4, -2, &value), DYNMEM_SUCCEED);

   for (intmax_t i = 1; i <= 3; i++)
      ck_assert_int_eq(array[i], value);

   value++;
   ck_assert_int_eq(DynMemSetValues(&dynmem, -3, -3, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], value);
   ck_assert_int_eq(DynMemSetValues(&dynmem, -3, -24, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetValues(&dynmem, -24, -3, &value), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemSetValues\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_test);
   tcase_add_test(test_cases, value_not_added);
   tcase_add_test(test_cases, value_added);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
