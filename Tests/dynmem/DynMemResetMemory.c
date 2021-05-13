#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(value_not_added) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemResetMemory(NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemResetMemory(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 20);
   ck_assert_int_eq(dynmem.ei, 16);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(appended) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemResetMemory(NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemResetMemory(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 20);
   ck_assert_int_eq(dynmem.ei, 16);

   for (int32_t i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemResetMemory(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 20);
   ck_assert_int_eq(dynmem.ei, 16);

   for (int32_t i = 0; i < 20; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemResetMemory(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 20);
   ck_assert_int_eq(dynmem.ei, 16);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(prepended) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemResetMemory(NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemResetMemory(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 20);
   ck_assert_int_eq(dynmem.ei, 16);

   for (int32_t i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemResetMemory(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 20);
   ck_assert_int_eq(dynmem.ei, 16);

   for (int32_t i = 0; i < 20; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemResetMemory(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 20);
   ck_assert_int_eq(dynmem.ei, 16);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemResetMemory\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, value_not_added);
   tcase_add_test(test_cases, appended);
   tcase_add_test(test_cases, prepended);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
