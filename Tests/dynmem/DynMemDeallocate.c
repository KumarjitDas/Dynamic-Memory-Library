#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_deallocation) {
   ck_assert_int_eq(DynMemDeallocate(NULL), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_deallocation) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemDeallocate\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_deallocation);
   tcase_add_test(test_cases, nonnull_deallocation);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
