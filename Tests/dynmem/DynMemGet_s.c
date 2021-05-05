#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_dynmem_null_value) {
   int value;
   intmax_t element_size = sizeof(value);

   ck_assert_int_eq(DynMemGet_s(NULL, 0 * element_size, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGet_s(NULL, 50 * element_size, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGet_s(NULL, 999 * element_size, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGet_s(NULL, -1 * element_size, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGet_s(NULL, -50 * element_size, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGet_s(NULL, -999 * element_size, NULL), DYNMEM_FAILED);
}
END_TEST

START_TEST(null_dynmem_nonnull_value) {
   int value = 123;
   intmax_t element_size = sizeof(value);

   ck_assert_int_eq(DynMemGet_s(NULL, 0 * element_size, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGet_s(NULL, 50 * element_size, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGet_s(NULL, 999 * element_size, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGet_s(NULL, -1 * element_size, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGet_s(NULL, -50 * element_size, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGet_s(NULL, -999 * element_size, &value), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem_null_value) {
   dynmem_t dynmem;
   int value;
   intmax_t element_size = sizeof(value);

   ck_assert_int_eq(DynMemGet_s(&dynmem, 0 * element_size, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGet_s(&dynmem, 50 * element_size, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGet_s(&dynmem, 999 * element_size, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGet_s(&dynmem, -1 * element_size, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGet_s(&dynmem, -50 * element_size, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGet_s(&dynmem, -999 * element_size, NULL), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem_nonnull_value_positive_index) {
   dynmem_t dynmem;
   int value;
   intmax_t element_size = sizeof(value);

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), 2, NULL), DYNMEM_SUCCEED);

   value = 22;
   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   value = 11;
   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   value = 33;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);
   value = 44;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemGet_s(&dynmem, 0 * element_size, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(value, 11);
   ck_assert_int_eq(DynMemGet_s(&dynmem, 1 * element_size, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(value, 22);
   ck_assert_int_eq(DynMemGet_s(&dynmem, 3 * element_size, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(value, 44);
   ck_assert_int_eq(DynMemGet_s(&dynmem, 999 * element_size, &value), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_nonnull_value_negative_index) {
   dynmem_t dynmem;
   int value;
   intmax_t element_size = sizeof(value);

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), 2, NULL), DYNMEM_SUCCEED);

   value = 22;
   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   value = 11;
   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   value = 33;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);
   value = 44;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemGet_s(&dynmem, -4 * element_size, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(value, 11);
   ck_assert_int_eq(DynMemGet_s(&dynmem, -3 * element_size, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(value, 22);
   ck_assert_int_eq(DynMemGet_s(&dynmem, -1 * element_size, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(value, 44);
   ck_assert_int_eq(DynMemGet_s(&dynmem, -999 * element_size, &value), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemGet_s\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_dynmem_null_value);
   tcase_add_test(test_cases, null_dynmem_nonnull_value);
   tcase_add_test(test_cases, nonnull_dynmem_null_value);
   tcase_add_test(test_cases, nonnull_dynmem_nonnull_value_positive_index);
   tcase_add_test(test_cases, nonnull_dynmem_nonnull_value_negative_index);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
