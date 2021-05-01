#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_dynmem) {
   int *memory;
   intmax_t size;
   ck_assert_int_eq(DynMemReduce(NULL, NULL, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemReduce(NULL, NULL, &size), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemReduce(NULL, &memory, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemReduce(NULL, &memory, &size), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem_nonnull_memory_null_size_appended) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   int *array = NULL;

   ck_assert_int_eq(DynMemReduce(&dynmem, &array, NULL), DYNMEM_SUCCEED);
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

START_TEST(nonnull_dynmem_nonnull_memory_nonnull_size_appended) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   intmax_t size = 10;

   for (intmax_t i = 0; i < size; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   size = 0;
   int *array = NULL;

   ck_assert_int_eq(DynMemReduce(&dynmem, &array, &size), DYNMEM_SUCCEED);
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

START_TEST(nonnull_dynmem_nonnull_memory_null_size_prepended) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);

   int *array = NULL;

   ck_assert_int_eq(DynMemReduce(&dynmem, &array, NULL), DYNMEM_SUCCEED);
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

START_TEST(nonnull_dynmem_nonnull_memory_nonnull_size_prepended) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   intmax_t size = 10;

   for (intmax_t i = 0; i < size; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);

   size = 0;
   int *array = NULL;

   ck_assert_int_eq(DynMemReduce(&dynmem, &array, &size), DYNMEM_SUCCEED);
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

START_TEST(nonnull_dynmem_null_memory_size_not_value_added) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t initial_size = length * element_size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, initial_size * 2);
   ck_assert_int_eq(dynmem.bi, initial_size);
   ck_assert_int_eq(dynmem.ei, initial_size - element_size);
   ck_assert_ptr_nonnull(dynmem.m);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_null_memory_nonnull_size_not_value_added) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t initial_size = length * element_size;
   intmax_t size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, initial_size * 2);
   ck_assert_int_eq(dynmem.bi, initial_size);
   ck_assert_int_eq(dynmem.ei, initial_size - element_size);
   ck_assert_ptr_nonnull(dynmem.m);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_null_memory_size_appended_not_size_changed) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t initial_size = length * element_size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, initial_size * 2);
   ck_assert_int_eq(dynmem.bi, initial_size);
   ck_assert_int_eq(dynmem.ei, initial_size + (5 * element_size) - element_size);
   ck_assert_ptr_nonnull(dynmem.m);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_null_memory_size_appended_size_changed) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t initial_size = length * element_size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, initial_size * 2);
   ck_assert_int_eq(dynmem.bi, 8);
   ck_assert_int_eq(dynmem.ei, 8 + (5 * element_size) - element_size);
   ck_assert_ptr_nonnull(dynmem.m);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_null_memory_size_prepended_not_size_changed) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t initial_size = length * element_size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, initial_size * 2);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, initial_size - element_size);
   ck_assert_ptr_nonnull(dynmem.m);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_null_memory_size_prepended_size_changed) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t initial_size = length * element_size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemDeductFront(&dynmem, NULL), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
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
   Suite *suite = suite_create("Test suite for \"DynMemReduce\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_dynmem);
   tcase_add_test(test_cases, nonnull_dynmem_nonnull_memory_null_size_appended);
   tcase_add_test(test_cases, nonnull_dynmem_nonnull_memory_nonnull_size_appended);
   tcase_add_test(test_cases, nonnull_dynmem_nonnull_memory_null_size_prepended);
   tcase_add_test(test_cases, nonnull_dynmem_nonnull_memory_nonnull_size_prepended);
   tcase_add_test(test_cases, nonnull_dynmem_null_memory_size_not_value_added);
   tcase_add_test(test_cases, nonnull_dynmem_null_memory_nonnull_size_not_value_added);
   tcase_add_test(test_cases, nonnull_dynmem_null_memory_size_appended_not_size_changed);
   tcase_add_test(test_cases, nonnull_dynmem_null_memory_size_appended_size_changed);
   tcase_add_test(test_cases, nonnull_dynmem_null_memory_size_prepended_not_size_changed);
   tcase_add_test(test_cases, nonnull_dynmem_null_memory_size_prepended_size_changed);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
