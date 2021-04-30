#include <stdint.h>

#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(append_null_value) {
   dynmem_t dynmem;
   intmax_t es = sizeof(int);

   ck_assert_int_eq(DynMemAllocate(&dynmem, es, 4, NULL), DYNMEM_SUCCEED);

   intmax_t cs = dynmem.cs;
   intmax_t ei = dynmem.ei;
   intmax_t eis = dynmem.eis;

   ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);
   ei += es;
   ck_assert_int_eq(dynmem.ei, ei);
   ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);
   ei += es;
   ck_assert_int_eq(dynmem.ei, ei);
   ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);
   ei += es;
   ck_assert_int_eq(dynmem.ei, ei);
   ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);
   ei += es;
   ck_assert_int_eq(dynmem.ei, ei);
   ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);
   ei += es;
   cs += eis;
   eis *= 2;
   ck_assert_int_eq(dynmem.cs, cs);
   ck_assert_int_eq(dynmem.ei, ei);
   ck_assert_int_eq(dynmem.eis, eis);

   ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);
   ei += es;
   ck_assert_int_eq(dynmem.ei, ei);
   ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);
   ei += es;
   ck_assert_int_eq(dynmem.ei, ei);
   ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);
   ei += es;
   ck_assert_int_eq(dynmem.ei, ei);
   ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);
   ei += es;
   cs += eis;
   eis *= 2;
   ck_assert_int_eq(dynmem.cs, cs);
   ck_assert_int_eq(dynmem.ei, ei);
   ck_assert_int_eq(dynmem.eis, eis);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(append_nonnull_value) {
   dynmem_t dynmem;
   int value = 0, temp;

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), 64, NULL), DYNMEM_SUCCEED);

   value++;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);
   temp = *(int *)(dynmem.m + dynmem.ei);
   ck_assert_int_eq(temp, value);
   value++;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);
   temp = *(int *)(dynmem.m + dynmem.ei);
   ck_assert_int_eq(temp, value);
   value++;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);
   temp = *(int *)(dynmem.m + dynmem.ei);
   ck_assert_int_eq(temp, value);
   value++;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);
   temp = *(int *)(dynmem.m + dynmem.ei);
   ck_assert_int_eq(temp, value);
   value++;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);
   temp = *(int *)(dynmem.m + dynmem.ei);
   ck_assert_int_eq(temp, value);
   value++;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);
   temp = *(int *)(dynmem.m + dynmem.ei);
   ck_assert_int_eq(temp, value);
   value++;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);
   temp = *(int *)(dynmem.m + dynmem.ei);
   ck_assert_int_eq(temp, value);
   value++;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);
   temp = *(int *)(dynmem.m + dynmem.ei);
   ck_assert_int_eq(temp, value);
   value++;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);
   temp = *(int *)(dynmem.m + dynmem.ei);
   ck_assert_int_eq(temp, value);
   value++;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);
   temp = *(int *)(dynmem.m + dynmem.ei);
   ck_assert_int_eq(temp, value);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemAppend\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, append_null_value);
   tcase_add_test(test_cases, append_nonnull_value);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
