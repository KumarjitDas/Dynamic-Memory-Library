#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_dynmem) {
   int *pointer;

   ck_assert_int_eq(DynMemGetHeapPointer(NULL, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetHeapPointer(NULL, &pointer), DYNMEM_FAILED);
   ck_assert_ptr_null(pointer);
}
END_TEST

START_TEST(nonnull_dynmem) {
   dynmem_t dynmem;
   int *pointer;

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), 10, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemGetHeapPointer(&dynmem, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetHeapPointer(&dynmem, &pointer), DYNMEM_SUCCEED);
   ck_assert_ptr_nonnull(pointer);
   ck_assert_ptr_eq(pointer, dynmem.m);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemGetHeapPointer\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_dynmem);
   tcase_add_test(test_cases, nonnull_dynmem);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
