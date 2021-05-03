#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_dynmem) {
   ck_assert_int_eq(DynMemSetForAppending(NULL), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem_no_value_added) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemSetForAppending(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, -((intmax_t)sizeof(int)));
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_appended_size_not_changed) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 4; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemSetForAppending(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 3 * sizeof(int));

   for (int i = 0; i < 4; i++)
      ck_assert_int_eq(*(int *)(dynmem.m + i * sizeof(int)), i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_appended_size_changed) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemSetForAppending(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 9 * sizeof(int));

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(*(int *)(dynmem.m + i * sizeof(int)), i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_prepended_size_not_changed) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), 5, NULL), DYNMEM_SUCCEED);

   for (int i = 3; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemSetForAppending(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 3 * sizeof(int));

   for (int i = 3; i >= 0; i--)
      ck_assert_int_eq(*(int *)(dynmem.m + i * sizeof(int)), i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_prepended_size_changed) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), 5, NULL), DYNMEM_SUCCEED);

   for (int i = 9; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemSetForAppending(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 9 * sizeof(int));

   for (int i = 9; i >= 0; i--)
      ck_assert_int_eq(*(int *)(dynmem.m + i * sizeof(int)), i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemSetForAppending\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_dynmem);
   tcase_add_test(test_cases, nonnull_dynmem_no_value_added);
   tcase_add_test(test_cases, nonnull_dynmem_appended_size_not_changed);
   tcase_add_test(test_cases, nonnull_dynmem_appended_size_changed);
   tcase_add_test(test_cases, nonnull_dynmem_prepended_size_not_changed);
   tcase_add_test(test_cases, nonnull_dynmem_prepended_size_changed);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
