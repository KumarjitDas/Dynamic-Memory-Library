#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_dynmem_null_value) {
   ck_assert_int_eq(DynMemPrepend(NULL, NULL), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem_null_value) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t current_size_half = length * element_size;
   intmax_t initial_size = current_size_half;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   intmax_t begin_index = dynmem.bi;

   ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, (begin_index -= element_size));
   ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, (begin_index -= element_size));
   ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, (begin_index -= element_size));
   ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, (begin_index -= element_size));
   ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, (begin_index -= element_size));

   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, current_size_half * 2);
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

   intmax_t begin_index = dynmem.bi;

   ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, (begin_index -= element_size));
   ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, (begin_index -= element_size));
   ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, (begin_index -= element_size));
   ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, (begin_index -= element_size));
   ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, (begin_index -= element_size));

   intmax_t new_current_size_half = current_size_half * 2;
   begin_index += new_current_size_half;

   ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, (begin_index -= element_size));
   ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, (begin_index -= element_size));
   ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, (begin_index -= element_size));
   ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, (begin_index -= element_size));
   ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.bi, (begin_index -= element_size));

   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, new_current_size_half * 2);
   ck_assert_int_eq(dynmem.ei, initial_size - element_size + new_current_size_half);
   ck_assert_ptr_nonnull(dynmem.m);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(null_dynmem_nonnull_value) {
   int value;
   ck_assert_int_eq(DynMemPrepend(NULL, &value), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem_nonnull_value) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t current_size_half = length * element_size;
   intmax_t initial_size = current_size_half;
   int value;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   intmax_t begin_index = dynmem.bi;

   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(*(int *)(dynmem.m + (begin_index -= element_size)), value);
   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(*(int *)(dynmem.m + (begin_index -= element_size)), value);
   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(*(int *)(dynmem.m + (begin_index -= element_size)), value);
   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(*(int *)(dynmem.m + (begin_index -= element_size)), value);
   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(*(int *)(dynmem.m + (begin_index -= element_size)), value);

   begin_index += (current_size_half * 2);

   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(*(int *)(dynmem.m + (begin_index -= element_size)), value);
   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(*(int *)(dynmem.m + (begin_index -= element_size)), value);
   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(*(int *)(dynmem.m + (begin_index -= element_size)), value);
   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(*(int *)(dynmem.m + (begin_index -= element_size)), value);
   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(*(int *)(dynmem.m + (begin_index -= element_size)), value);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemPrepend\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_dynmem_null_value);
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
