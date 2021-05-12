#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_dynmem) {
   int value;
   ck_assert_int_eq(DynMemPrepend(NULL, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemPrepend(NULL, &value), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem__null_value) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__nonnull_value__minimum_size) {
   dynmem_t dynmem;
   int value = 42069;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(*(int *)(dynmem.m + dynmem.bi), value);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__nonnull_value__edged_size) {
   dynmem_t dynmem;
   int value = 420;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 5; i++) {
      ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
      ck_assert_int_eq(*(int *)(dynmem.m + dynmem.bi), value);
      value++;
   }

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__nonnull_value__extended_size) {
   dynmem_t dynmem;
   int value = 69;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 10; i++) {
      ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
      ck_assert_int_eq(*(int *)(dynmem.m + dynmem.bi), value);
      value++;
   }

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__nonnull_value__more_extended_size) {
   dynmem_t dynmem;
   int value = -42069;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 20; i++) {
      ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
      ck_assert_int_eq(*(int *)(dynmem.m + dynmem.bi), value);
      value++;
   }

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemPrepend\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_dynmem);
   tcase_add_test(test_cases, nonnull_dynmem__null_value);
   tcase_add_test(test_cases, nonnull_dynmem__nonnull_value__minimum_size);
   tcase_add_test(test_cases, nonnull_dynmem__nonnull_value__edged_size);
   tcase_add_test(test_cases, nonnull_dynmem__nonnull_value__extended_size);
   tcase_add_test(test_cases, nonnull_dynmem__nonnull_value__more_extended_size);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
