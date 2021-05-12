#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(no_value_added) {
   dynmem_t dynmem;
   intmax_t length;

   ck_assert_int_eq(DynMemGetLength(NULL, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetLength(NULL, &length), DYNMEM_FAILED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemGetLength(&dynmem, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetLength(&dynmem, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(length, 0);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(appended) {
   dynmem_t dynmem;
   intmax_t length;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemGetLength(&dynmem, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(length, 5);

   for (int i = 5; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemGetLength(&dynmem, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(length, 10);

   for (int i = 10; i < 20; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemGetLength(&dynmem, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(length, 20);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(prepended) {
   dynmem_t dynmem;
   intmax_t length;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 4; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemGetLength(&dynmem, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(length, 5);

   for (int i = 9; i >= 5; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemGetLength(&dynmem, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(length, 10);

   for (int i = 19; i >= 10; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemGetLength(&dynmem, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(length, 20);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemGetLength\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, no_value_added);
   tcase_add_test(test_cases, appended);
   tcase_add_test(test_cases, prepended);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
