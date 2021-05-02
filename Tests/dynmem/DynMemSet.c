#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_dynmem_null_value) {
   ck_assert_int_eq(DynMemSet(NULL, 0, 10, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet(NULL, 2, 8, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet(NULL, 0, 999, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet(NULL, 0, -1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet(NULL, -9, -1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet(NULL, -9, -999, NULL), DYNMEM_FAILED);
}
END_TEST

START_TEST(null_dynmem_nonnull_value) {
   int value = 123;

   ck_assert_int_eq(DynMemSet(NULL, 0, 10, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet(NULL, 2, 8, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet(NULL, 0, 999, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet(NULL, 0, -1, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet(NULL, -9, -1, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet(NULL, -9, -999, &value), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem_null_value) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemSet(&dynmem, 0, 10, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet(&dynmem, 2, 8, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet(&dynmem, 0, 999, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet(&dynmem, 0, -1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet(&dynmem, -9, -1, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet(&dynmem, -9, -999, NULL), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem_nonnull_value) {
   dynmem_t dynmem;
   int value = -69;
   intmax_t begin, end;

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   value++; begin = 0; end = 10;
   ck_assert_int_eq(DynMemSet(&dynmem, begin, end, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * sizeof(int))), value);

   value++; begin = 1; end = 10;
   ck_assert_int_eq(DynMemSet(&dynmem, begin, end, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * sizeof(int))), value);

   value++; begin = 0; end = 9;
   ck_assert_int_eq(DynMemSet(&dynmem, begin, end, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * sizeof(int))), value);

   value++; begin = 1; end = 9;
   ck_assert_int_eq(DynMemSet(&dynmem, begin, end, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * sizeof(int))), value);

   value++; begin = 4; end = 5;
   ck_assert_int_eq(DynMemSet(&dynmem, begin, end, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * sizeof(int))), value);

   value++; begin = 5; end = 5;
   ck_assert_int_eq(DynMemSet(&dynmem, begin, end, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet(&dynmem, 0, 999, &value), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_nonnull_value_negative_end_index) {
   dynmem_t dynmem;
   int value = -69;
   intmax_t begin, end;

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   value++; begin = 0; end = -1;
   ck_assert_int_eq(DynMemSet(&dynmem, begin, end, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < 10; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * sizeof(int))), value);

   value++; begin = 1; end = -1;
   ck_assert_int_eq(DynMemSet(&dynmem, begin, end, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < 10; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * sizeof(int))), value);

   value++; begin = 0; end = -2;
   ck_assert_int_eq(DynMemSet(&dynmem, begin, end, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < 9; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * sizeof(int))), value);

   value++; begin = 1; end = -2;
   ck_assert_int_eq(DynMemSet(&dynmem, begin, end, &value), DYNMEM_SUCCEED);
   for (int i = begin; i < 9; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * sizeof(int))), value);

   value++; begin = -6; end = -5;
   ck_assert_int_eq(DynMemSet(&dynmem, begin, end, &value), DYNMEM_SUCCEED);
   for (int i = 4; i < 6; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * sizeof(int))), value);

   value++; begin = -5; end = -5;
   ck_assert_int_eq(DynMemSet(&dynmem, begin, end, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(*((int *)(dynmem.m + 5 * sizeof(int))), value);

   ck_assert_int_eq(DynMemSet(&dynmem, 0, -999, &value), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_nonnull_value_negative_begin_index) {
   dynmem_t dynmem;
   int value = 420;
   intmax_t begin, end;

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   value++; begin = -10; end = 10;
   ck_assert_int_eq(DynMemSet(&dynmem, begin, end, &value), DYNMEM_SUCCEED);
   for (int i = 0; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * sizeof(int))), value);

   value++; begin = -9; end = 10;
   ck_assert_int_eq(DynMemSet(&dynmem, begin, end, &value), DYNMEM_SUCCEED);
   for (int i = 1; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * sizeof(int))), value);

   value++; begin = -10; end = 9;
   ck_assert_int_eq(DynMemSet(&dynmem, begin, end, &value), DYNMEM_SUCCEED);
   for (int i = 0; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * sizeof(int))), value);

   value++; begin = -9; end = 9;
   ck_assert_int_eq(DynMemSet(&dynmem, begin, end, &value), DYNMEM_SUCCEED);
   for (int i = 1; i < end; i++)
      ck_assert_int_eq(*((int *)(dynmem.m + i * sizeof(int))), value);


   ck_assert_int_eq(DynMemSet(&dynmem, -4, -4, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(*((int *)(dynmem.m + 6 * sizeof(int))), value);

   ck_assert_int_eq(DynMemSet(&dynmem, -5, -6, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemSet(&dynmem, -999, 10, &value), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemSet\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_dynmem_null_value);
   tcase_add_test(test_cases, null_dynmem_nonnull_value);
   tcase_add_test(test_cases, nonnull_dynmem_null_value);
   tcase_add_test(test_cases, nonnull_dynmem_nonnull_value);
   tcase_add_test(test_cases, nonnull_dynmem_nonnull_value_negative_end_index);
   tcase_add_test(test_cases, nonnull_dynmem_nonnull_value_negative_begin_index);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
