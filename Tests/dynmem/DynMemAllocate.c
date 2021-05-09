#include "check.h"
#include "dynmem/dynmem.h"

#include <stdlib.h>

START_TEST(null_dynmem__without_preallocated_memory) {
   ck_assert_int_eq(DynMemAllocate(NULL, 0, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(NULL, 0, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(NULL, 4, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(NULL, 4, 5, NULL), DYNMEM_FAILED);
}
END_TEST

START_TEST(null_dynmem__with_preallocated_memory) {
   int *memory = malloc(4);

   ck_assert_int_eq(DynMemAllocate(NULL, 0, 0, &memory), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(NULL, 0, 5, &memory), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(NULL, 4, 0, &memory), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(NULL, 4, 5, &memory), DYNMEM_FAILED);

   if (memory != NULL) free(memory);
}
END_TEST

START_TEST(nonnull_dynmem__without_preallocated_memory) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 0, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(&dynmem, 0, 5, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 4);
   ck_assert_int_eq(dynmem.is, 20);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 20);
   ck_assert_int_eq(dynmem.ei, 16);
   ck_assert_ptr_nonnull(dynmem.m);

   free(dynmem.m);
}
END_TEST

START_TEST(nonnull_dynmem__without_preallocated_memory__smaller_size) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 1, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 4);

#ifdef INT64_MAX
   ck_assert_int_eq(dynmem.is, 12);
   ck_assert_int_eq(dynmem.cs, 24);
   ck_assert_int_eq(dynmem.bi, 12);
   ck_assert_int_eq(dynmem.ei, 8);
#else  // INT64_MAX
   ck_assert_int_eq(dynmem.is, 8);
   ck_assert_int_eq(dynmem.cs, 16);
   ck_assert_int_eq(dynmem.bi, 8);
   ck_assert_int_eq(dynmem.ei, 4);
#endif  // INT64_MAX

   ck_assert_ptr_nonnull(dynmem.m);
   free(dynmem.m);
}
END_TEST

START_TEST(nonnull_dynmem__with_null_memory) {
   dynmem_t dynmem;
   int *memory = NULL;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, &memory), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 4);
   ck_assert_int_eq(dynmem.is, 20);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 20);
   ck_assert_int_eq(dynmem.ei, 16);
   ck_assert_ptr_nonnull(dynmem.m);

   free(dynmem.m);
}
END_TEST

START_TEST(nonnull_dynmem__with_preallocated_memory) {
   dynmem_t dynmem;
   int *memory = malloc(20);
   int *temporary_memory = memory;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 0, 0, &memory), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(&dynmem, 0, 5, &memory), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 0, &memory), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, &memory), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 4);
   ck_assert_int_eq(dynmem.is, 8);
   ck_assert_int_eq(dynmem.cs, 16);
   ck_assert_int_eq(dynmem.bi, 8);
   ck_assert_int_eq(dynmem.ei, 4);
   ck_assert_ptr_nonnull(dynmem.m);
   ck_assert_ptr_null(memory);
   ck_assert_ptr_eq(dynmem.m, temporary_memory);

   free(dynmem.m);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemAllocate\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_dynmem__without_preallocated_memory);
   tcase_add_test(test_cases, null_dynmem__with_preallocated_memory);
   tcase_add_test(test_cases, nonnull_dynmem__without_preallocated_memory);
   tcase_add_test(test_cases, nonnull_dynmem__without_preallocated_memory__smaller_size);
   tcase_add_test(test_cases, nonnull_dynmem__with_null_memory);
   tcase_add_test(test_cases, nonnull_dynmem__with_preallocated_memory);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
