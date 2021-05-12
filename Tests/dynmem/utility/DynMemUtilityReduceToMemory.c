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

START_TEST(value_not_added) {
   dynmem_t dynmem;
   int *array;
   intmax_t size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_null(array);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
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

START_TEST(appended__null_size__size_not_changed) {
   dynmem_t dynmem;
   int *array;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(appended__null_size__extended_size) {
   dynmem_t dynmem;
   int *array;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(appended__null_size__more_extended_size) {
   dynmem_t dynmem;
   int *array;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(appended__nonnull_size__size_not_changed) {
   dynmem_t dynmem;
   int *array;
   intmax_t size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);
   ck_assert_int_eq(size, 20);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(appended__nonnull_size__extended_size) {
   dynmem_t dynmem;
   int *array;
   intmax_t size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);
   ck_assert_int_eq(size, 40);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(appended__nonnull_size__more_extended_size) {
   dynmem_t dynmem;
   int *array;
   intmax_t size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);
   ck_assert_int_eq(size, 80);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(prepended__null_size__size_not_changed) {
   dynmem_t dynmem;
   int *array;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 4; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(prepended__null_size__extended_size) {
   dynmem_t dynmem;
   int *array;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 9; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(prepended__null_size__more_extended_size) {
   dynmem_t dynmem;
   int *array;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 19; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(prepended__nonnull_size__size_not_changed) {
   dynmem_t dynmem;
   int *array;
   intmax_t size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 4; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);
   ck_assert_int_eq(size, 20);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(prepended__nonnull_size__extended_size) {
   dynmem_t dynmem;
   int *array;
   intmax_t size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 9; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);
   ck_assert_int_eq(size, 40);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(prepended__nonnull_size__more_extended_size) {
   dynmem_t dynmem;
   int *array;
   intmax_t size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 19; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduceToMemory(&dynmem, &array, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);
   ck_assert_int_eq(size, 80);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemUtilityReduceToMemory\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, value_not_added);
   tcase_add_test(test_cases, appended__null_size__size_not_changed);
   tcase_add_test(test_cases, appended__null_size__extended_size);
   tcase_add_test(test_cases, appended__null_size__more_extended_size);
   tcase_add_test(test_cases, appended__nonnull_size__size_not_changed);
   tcase_add_test(test_cases, appended__nonnull_size__extended_size);
   tcase_add_test(test_cases, appended__nonnull_size__more_extended_size);
   tcase_add_test(test_cases, prepended__null_size__size_not_changed);
   tcase_add_test(test_cases, prepended__null_size__extended_size);
   tcase_add_test(test_cases, prepended__null_size__more_extended_size);
   tcase_add_test(test_cases, prepended__nonnull_size__size_not_changed);
   tcase_add_test(test_cases, prepended__nonnull_size__extended_size);
   tcase_add_test(test_cases, prepended__nonnull_size__more_extended_size);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
