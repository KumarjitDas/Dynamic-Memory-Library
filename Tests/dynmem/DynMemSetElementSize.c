#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_dynmem) {
   ck_assert_int_eq(DynMemSetElementSize(NULL, 8), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetElementSize(NULL, 0), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetElementSize(NULL, -8), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 10, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemSetElementSize(&dynmem, 8), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 8);
   ck_assert_int_eq(DynMemSetElementSize(&dynmem, 0), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSetElementSize(&dynmem, -8), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemSetElementSize\" function");
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
