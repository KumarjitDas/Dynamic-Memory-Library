#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_dynmem) {
   ck_assert_int_eq(DynMemSetForPrepending(NULL), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem__value_not_added) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemSetForPrepending(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, 40);
   ck_assert_int_eq(dynmem.ei, 36);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__appended__size_not_changed) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemSetForPrepending(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, 20);
   ck_assert_int_eq(dynmem.ei, 36);

   int *array = (int *)(dynmem.m + dynmem.bi);

   for (int32_t i = 0; i < 5; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__appended__extended_size) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemSetForPrepending(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, 40);
   ck_assert_int_eq(dynmem.ei, 76);

   int *array = (int *)(dynmem.m + dynmem.bi);

   for (int32_t i = 0; i < 10; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__appended__more_extended_size) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 0; i < 20; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemSetForPrepending(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, 80);
   ck_assert_int_eq(dynmem.ei, 156);

   int *array = (int *)(dynmem.m + dynmem.bi);

   for (int32_t i = 0; i < 20; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__prepended__size_not_changed) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemSetForPrepending(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, 20);
   ck_assert_int_eq(dynmem.ei, 36);

   int *array = (int *)(dynmem.m + dynmem.bi);
   int value = 4;

   for (int32_t i = 0; i < 5; i++, value--)
      ck_assert_int_eq(array[i], value);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__prepended__extended_size) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemSetForPrepending(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, 40);
   ck_assert_int_eq(dynmem.ei, 76);

   int *array = (int *)(dynmem.m + dynmem.bi);
   int value = 9;

   for (int32_t i = 0; i < 10; i++, value--)
      ck_assert_int_eq(array[i], value);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__prepended__more_extended_size) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 0; i < 20; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemSetForPrepending(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, 80);
   ck_assert_int_eq(dynmem.ei, 156);

   int *array = (int *)(dynmem.m + dynmem.bi);
   int value = 19;

   for (int32_t i = 0; i < 20; i++, value--)
      ck_assert_int_eq(array[i], value);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemSetForPrepending\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_dynmem);
   tcase_add_test(test_cases, nonnull_dynmem__value_not_added);
   tcase_add_test(test_cases, nonnull_dynmem__appended__size_not_changed);
   tcase_add_test(test_cases, nonnull_dynmem__appended__extended_size);
   tcase_add_test(test_cases, nonnull_dynmem__appended__more_extended_size);
   tcase_add_test(test_cases, nonnull_dynmem__prepended__size_not_changed);
   tcase_add_test(test_cases, nonnull_dynmem__prepended__extended_size);
   tcase_add_test(test_cases, nonnull_dynmem__prepended__more_extended_size);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
