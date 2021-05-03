#include "check.h"

#ifndef DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#define DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_ALLOCATE_H
#define DYNMEM_INTERNAL_USE_UTILITY_ALLOCATE_H
#endif

#include "dynmem/dynmem.h"
#include "dynmem/utility/defines.h"
#include "dynmem/utility/allocate.h"

START_TEST(nonnull_dynmem_not_value_added) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t initial_size = length * element_size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, initial_size * 2);
   ck_assert_int_eq(dynmem.bi, initial_size);
   ck_assert_int_eq(dynmem.ei, initial_size - element_size);
   ck_assert_ptr_nonnull(dynmem.m);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_appended_not_size_changed) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t initial_size = length * element_size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, initial_size * 2);
   ck_assert_int_eq(dynmem.bi, initial_size);
   ck_assert_int_eq(dynmem.ei, initial_size + (5 * element_size) - element_size);
   ck_assert_ptr_nonnull(dynmem.m);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_appended_size_changed) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t initial_size = length * element_size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, initial_size * 2);
   ck_assert_int_eq(dynmem.bi, 8);
   ck_assert_int_eq(dynmem.ei, 8 + (5 * element_size) - element_size);
   ck_assert_ptr_nonnull(dynmem.m);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_prepended_not_size_changed) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t initial_size = length * element_size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, initial_size * 2);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, initial_size - element_size);
   ck_assert_ptr_nonnull(dynmem.m);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_prepended_size_changed) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t initial_size = length * element_size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemDeductFront(&dynmem, NULL), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, initial_size * 2);
   ck_assert_int_eq(dynmem.bi, 8);
   ck_assert_int_eq(dynmem.ei, 8 + (5 * element_size) - element_size);
   ck_assert_ptr_nonnull(dynmem.m);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemUtilityReduce\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, nonnull_dynmem_not_value_added);
   tcase_add_test(test_cases, nonnull_dynmem_appended_not_size_changed);
   tcase_add_test(test_cases, nonnull_dynmem_appended_size_changed);
   tcase_add_test(test_cases, nonnull_dynmem_prepended_not_size_changed);
   tcase_add_test(test_cases, nonnull_dynmem_prepended_size_changed);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
