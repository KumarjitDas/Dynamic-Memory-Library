#include <stdlib.h>

#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_dynmem_without_preallocated_memory) {
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);

   ck_assert_int_eq(DynMemAllocate(NULL, 0, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(NULL, 0, length, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(NULL, element_size, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(NULL, element_size, length, NULL), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem_zero_size_without_preallocated_memory) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 0, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(&dynmem, 0, length, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, 0, NULL), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem_nonzero_size_without_preallocated_memory) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t size = length * element_size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, size);
   ck_assert_int_eq(dynmem.cs, size * 2);
   ck_assert_int_eq(dynmem.csh, size);
   ck_assert_int_eq(dynmem.bi, size);
   ck_assert_int_eq(dynmem.ei, size - element_size);
   ck_assert_ptr_nonnull(dynmem.m);

   free(dynmem.m);
}
END_TEST

START_TEST(nonnull_dynmem_small_size_without_preallocated_memory) {
   dynmem_t dynmem;
   intmax_t length = 1;
   intmax_t element_size = 3;
   intmax_t size = ((sizeof(intmax_t) + element_size) / element_size) * element_size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, size);
   ck_assert_int_eq(dynmem.cs, size * 2);
   ck_assert_int_eq(dynmem.csh, size);
   ck_assert_int_eq(dynmem.bi, size);
   ck_assert_int_eq(dynmem.ei, size - element_size);
   ck_assert_ptr_nonnull(dynmem.m);

   free(dynmem.m);
}
END_TEST

START_TEST(null_dynmem_with_allocated_memory) {
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t size = length * element_size;
   int *memory = malloc(size);

   ck_assert_int_eq(DynMemAllocate(NULL, 0, 0, &memory), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(NULL, 0, length, &memory), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(NULL, element_size, 0, &memory), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(NULL, element_size, length, &memory), DYNMEM_FAILED);

   if (memory != NULL) free(memory);
}
END_TEST

START_TEST(nonnull_dynmem_zero_size_with_allocated_memory) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t size = length * element_size;
   int *memory = malloc(size);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 0, 0, &memory), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(&dynmem, 0, length, &memory), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, 0, &memory), DYNMEM_FAILED);

   if (memory != NULL) free(memory);
}
END_TEST

START_TEST(nonnull_dynmem_nonzero_size_with_allocated_memory) {
   dynmem_t dynmem;
   intmax_t length = 2;
   intmax_t element_size = 3;
   intmax_t size = length * element_size;
   int *memory = malloc(size);
   int *temporary_memory = memory;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, &memory), DYNMEM_SUCCEED);

   size /= 2;
   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, size);
   ck_assert_int_eq(dynmem.cs, size * 2);
   ck_assert_int_eq(dynmem.csh, size);
   ck_assert_int_eq(dynmem.bi, size);
   ck_assert_int_eq(dynmem.ei, size - element_size);
   ck_assert_ptr_nonnull(dynmem.m);
   ck_assert_ptr_eq(dynmem.m, temporary_memory);
   ck_assert_ptr_null(memory);

   free(dynmem.m);
}
END_TEST

START_TEST(nonnull_dynmem_small_size_with_null_memory) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t size = length * element_size;
   int *memory = NULL;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, &memory), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, element_size);
   ck_assert_int_eq(dynmem.is, size);
   ck_assert_int_eq(dynmem.cs, size * 2);
   ck_assert_int_eq(dynmem.csh, size);
   ck_assert_int_eq(dynmem.bi, size);
   ck_assert_int_eq(dynmem.ei, size - element_size);
   ck_assert_ptr_nonnull(dynmem.m);

   free(dynmem.m);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemAllocate\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_dynmem_without_preallocated_memory);
   tcase_add_test(test_cases, nonnull_dynmem_zero_size_without_preallocated_memory);
   tcase_add_test(test_cases, nonnull_dynmem_nonzero_size_without_preallocated_memory);
   tcase_add_test(test_cases, nonnull_dynmem_small_size_without_preallocated_memory);

   tcase_add_test(test_cases, null_dynmem_with_allocated_memory);
   tcase_add_test(test_cases, nonnull_dynmem_zero_size_with_allocated_memory);
   tcase_add_test(test_cases, nonnull_dynmem_nonzero_size_with_allocated_memory);
   tcase_add_test(test_cases, nonnull_dynmem_small_size_with_null_memory);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
