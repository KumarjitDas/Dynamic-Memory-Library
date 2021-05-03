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

START_TEST(nonnull_memory_null_size_not_size_changed) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   int *array = NULL;

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_null(array);
}
END_TEST

START_TEST(nonnull_memory_nonnull_size_not_size_changed) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   int *array;
   intmax_t size;

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, &size), DYNMEM_FAILED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_null(array);
   ck_assert_int_eq(size, 0);
}
END_TEST

START_TEST(nonnull_memory_null_size_size_changed) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   int *array;

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);

   if (array != NULL) free(array);
}
END_TEST

START_TEST(nonnull_memory_nonnull_size_size_changed) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   int *array;
   intmax_t size;

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);
   ck_assert_int_eq(size, 5 * element_size);

   if (array != NULL) free(array);
}
END_TEST

START_TEST(nonnull_memory_null_size_appended) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   int *array = NULL;

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);

   if (array != NULL) free(array);
}
END_TEST

START_TEST(nonnull_memory_nonnull_size_appended) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   intmax_t size = 0;
   int *array = NULL;

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);
   ck_assert_int_eq(size, 10 * element_size);

   if (array != NULL) free(array);
}
END_TEST

START_TEST(nonnull_memory_null_size_prepended) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);

   int *array = NULL;

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);

   if (array != NULL) free(array);
}
END_TEST

START_TEST(nonnull_memory_nonnull_size_prepended) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   intmax_t size = 10;

   for (intmax_t i = 0; i < size; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);

   size = 0;
   int *array = NULL;

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);
   ck_assert_int_eq(size, 10 * element_size);

   if (array != NULL) free(array);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemUtilityReduceToMemory\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, nonnull_memory_null_size_not_size_changed);
   tcase_add_test(test_cases, nonnull_memory_nonnull_size_not_size_changed);
   tcase_add_test(test_cases, nonnull_memory_null_size_size_changed);
   tcase_add_test(test_cases, nonnull_memory_nonnull_size_size_changed);
   tcase_add_test(test_cases, nonnull_memory_null_size_appended);
   tcase_add_test(test_cases, nonnull_memory_nonnull_size_appended);
   tcase_add_test(test_cases, nonnull_memory_null_size_prepended);
   tcase_add_test(test_cases, nonnull_memory_nonnull_size_prepended);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
