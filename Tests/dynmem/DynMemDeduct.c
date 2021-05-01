#include <stdint.h>

#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_dynmem_null_value) {
   ck_assert_int_eq(DynMemDeduct(NULL, NULL), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem_null_value_cannot_deduct) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 1, 1, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_nonnull_value_cannot_deduct) {
   dynmem_t dynmem;
   int value;

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(value), 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeduct(&dynmem, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeduct(&dynmem, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeduct(&dynmem, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_null_value) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t current_size_half = length * element_size;
   intmax_t initial_size = current_size_half;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < length; i++) {
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);
   }

   intmax_t end_index = dynmem.ei;

   ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, (end_index -= element_size));
   ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, (end_index -= element_size));
   ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, (end_index -= element_size));
   ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, (end_index -= element_size));
   ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, (end_index -= element_size));

   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, current_size_half * 2);
   ck_assert_int_eq(dynmem.csh, current_size_half);
   ck_assert_int_eq(dynmem.bi, initial_size);
   ck_assert_int_eq(dynmem.ei, initial_size - element_size);
   ck_assert_ptr_nonnull(dynmem.m);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_null_value_increase_size) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t current_size_half = length * element_size;
   intmax_t initial_size = current_size_half;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   length *= 2;

   for (intmax_t i = 0; i < length; i++) {
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);
   }

   intmax_t end_index = dynmem.ei;

   for (intmax_t i = 0; i < length; i++) {
      ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_SUCCEED);
      ck_assert_int_eq(dynmem.ei, (end_index -= element_size));
   }

   intmax_t new_current_size_half = current_size_half * 2;

   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, new_current_size_half * 2);
   ck_assert_int_eq(dynmem.csh, new_current_size_half);
   ck_assert_int_eq(dynmem.bi, initial_size);
   ck_assert_int_eq(dynmem.ei, initial_size - element_size);
   ck_assert_ptr_nonnull(dynmem.m);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(null_dynmem_nonnull_value) {
   int value;
   ck_assert_int_eq(DynMemDeduct(NULL, &value), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem_nonnull_value) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t current_size_half = length * element_size;
   intmax_t initial_size = current_size_half;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   length *= 2;
   int value = 0;

   for (intmax_t i = 0; i < length; i++) {
      value += i;
      ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);
   }

   intmax_t end_index = dynmem.ei;

   for (intmax_t i = length - 1; i >= 0; i--) {
      int deduct_value;
      ck_assert_int_eq(DynMemDeduct(&dynmem, &deduct_value), DYNMEM_SUCCEED);
      ck_assert_int_eq(value, deduct_value);
      value -= i;
   }

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemDeduct\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_dynmem_null_value);
   tcase_add_test(test_cases, nonnull_dynmem_null_value_cannot_deduct);
   tcase_add_test(test_cases, nonnull_dynmem_nonnull_value_cannot_deduct);
   tcase_add_test(test_cases, nonnull_dynmem_null_value);
   tcase_add_test(test_cases, nonnull_dynmem_null_value_increase_size);
   tcase_add_test(test_cases, null_dynmem_nonnull_value);
   tcase_add_test(test_cases, nonnull_dynmem_nonnull_value);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
