#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_test) {
   int32_t value;

   ck_assert_int_eq(DynMemSet_s(NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(NULL, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(NULL, 64, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(NULL, -1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(NULL, -12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(NULL, -64, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(NULL, 0, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(NULL, 12, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(NULL, 64, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(NULL, -1, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(NULL, -12, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(NULL, -64, &value), DYNMEM_FAILED);

   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemSet_s(&dynmem, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(&dynmem, 12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(&dynmem, 64, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(&dynmem, -1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(&dynmem, -12, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(&dynmem, -64, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(value_not_added) {
   dynmem_t dynmem;
   int32_t value = -69;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemSet_s(&dynmem, 0, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(&dynmem, 12, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(&dynmem, 64, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(&dynmem, -1, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(&dynmem, -12, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet_s(&dynmem, -64, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(value_added) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   int32_t value = 69;
   int32_t *array = (int *)(dynmem.m + dynmem.bi);

   value++;
   ck_assert_int_eq(DynMemSet_s(&dynmem, 0, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[0], value);
   value++;
   ck_assert_int_eq(DynMemSet_s(&dynmem, 12, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[3], value);
   ck_assert_int_eq(DynMemSet_s(&dynmem, 64, &value), DYNMEM_FAILED);
   value++;
   ck_assert_int_eq(DynMemSet_s(&dynmem, -4, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[4], value);
   value++;
   ck_assert_int_eq(DynMemSet_s(&dynmem, -12, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(array[2], value);
   ck_assert_int_eq(DynMemSet_s(&dynmem, -64, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemSet_s\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_test);
   tcase_add_test(test_cases, value_not_added);
   tcase_add_test(test_cases, value_added);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
