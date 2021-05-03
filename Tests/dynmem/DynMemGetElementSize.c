#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_dynmem) {
   intmax_t size;
   ck_assert_int_eq(DynMemGetElementSize(NULL, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetElementSize(NULL, &size), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem) {
   dynmem_t dynmem;
   intmax_t size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 10, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemGetElementSize(&dynmem, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetElementSize(&dynmem, &size), DYNMEM_SUCCEED);
   ck_assert_int_eq(size, 4);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemGetElementSize\" function");
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
