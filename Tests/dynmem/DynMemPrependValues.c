#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(Null_dynmem) {
   int32_t value;
   ck_assert_int_eq(DynMemPrependValues(NULL, NULL, 0), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemPrependValues(NULL, NULL, 1), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemPrependValues(NULL, &value, 0), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemPrependValues(NULL, &value, 1), DYNMEM_FAILED);
}
END_TEST

START_TEST(Nonnull_dynmem) {
   dynmem_t dynmem;
   int32_t value = -69;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemPrependValues(&dynmem, NULL, 0), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemPrependValues(&dynmem, NULL, 1), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemPrependValues(&dynmem, &value, 0), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemPrependValues(&dynmem, &value, 1), DYNMEM_SUCCEED);
   ck_assert_int_eq(*(int32_t *)(dynmem.m + 16), -69);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(Size_not_changed) {
   dynmem_t dynmem;
   int32_t value = 69;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemPrependValues(&dynmem, &value, 5), DYNMEM_SUCCEED);

   int32_t *array = (int32_t *)(dynmem.m);

   for (int32_t i = 0; i < 5; i++)
      ck_assert_int_eq(array[i], 69);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(Extended_size) {
   dynmem_t dynmem;
   int32_t value = 420;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemPrependValues(&dynmem, &value, 10), DYNMEM_SUCCEED);

   int32_t *array = (int32_t *)(dynmem.m + 20);

   for (int32_t i = 0; i < 10; i++)
      ck_assert_int_eq(array[i], 420);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(More_extended_size) {
   dynmem_t dynmem;
   int32_t value = 42069;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemPrependValues(&dynmem, &value, 20), DYNMEM_SUCCEED);

   int32_t *array = (int32_t *)(dynmem.m + 60);

   for (int32_t i = 0; i < 20; i++)
      ck_assert_int_eq(array[i], 42069);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemPrependValues\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, Null_dynmem);
   tcase_add_test(test_cases, Nonnull_dynmem);
   tcase_add_test(test_cases, Size_not_changed);
   tcase_add_test(test_cases, Extended_size);
   tcase_add_test(test_cases, More_extended_size);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
