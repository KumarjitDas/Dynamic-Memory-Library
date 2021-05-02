#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_dynmem) {
   ck_assert_int_eq(DynMemReset(NULL), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t initial_size = sizeof(int) * length;

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), length, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemReset(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, sizeof(int));
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, initial_size * 2);
   ck_assert_int_eq(dynmem.bi, initial_size);
   ck_assert_int_eq(dynmem.ei, initial_size - sizeof(int));
   ck_assert_ptr_nonnull(dynmem.m);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_appended_not_size_changed) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t initial_size = sizeof(int) * length;

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReset(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, sizeof(int));
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, initial_size * 2);
   ck_assert_int_eq(dynmem.bi, initial_size);
   ck_assert_int_eq(dynmem.ei, initial_size - sizeof(int));
   ck_assert_ptr_nonnull(dynmem.m);

   ck_assert_int_eq(((int *)(dynmem.m))[0], (int)0);
   ck_assert_int_eq(((int *)(dynmem.m))[2], (int)0);
   ck_assert_int_eq(((int *)(dynmem.m))[4], (int)0);
   ck_assert_int_eq(((int *)(dynmem.m))[6], (int)0);
   ck_assert_int_eq(((int *)(dynmem.m))[8], (int)0);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_appended_size_changed) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t initial_size = sizeof(int) * length;

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, NULL), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReset(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, sizeof(int));
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, initial_size * 2);
   ck_assert_int_eq(dynmem.bi, initial_size);
   ck_assert_int_eq(dynmem.ei, initial_size - sizeof(int));
   ck_assert_ptr_nonnull(dynmem.m);

   ck_assert_int_eq(((int *)(dynmem.m))[0], (int)0);
   ck_assert_int_eq(((int *)(dynmem.m))[2], (int)0);
   ck_assert_int_eq(((int *)(dynmem.m))[4], (int)0);
   ck_assert_int_eq(((int *)(dynmem.m))[6], (int)0);
   ck_assert_int_eq(((int *)(dynmem.m))[8], (int)0);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_prepended_not_size_changed) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t initial_size = sizeof(int) * length;

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReset(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, sizeof(int));
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, initial_size * 2);
   ck_assert_int_eq(dynmem.bi, initial_size);
   ck_assert_int_eq(dynmem.ei, initial_size - sizeof(int));
   ck_assert_ptr_nonnull(dynmem.m);

   ck_assert_int_eq(((int *)(dynmem.m))[0], (int)0);
   ck_assert_int_eq(((int *)(dynmem.m))[2], (int)0);
   ck_assert_int_eq(((int *)(dynmem.m))[4], (int)0);
   ck_assert_int_eq(((int *)(dynmem.m))[6], (int)0);
   ck_assert_int_eq(((int *)(dynmem.m))[8], (int)0);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem_prepended_size_changed) {
   dynmem_t dynmem;
   intmax_t length = 5;
   intmax_t initial_size = sizeof(int) * length;

   ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), length, NULL), DYNMEM_SUCCEED);

   for (intmax_t i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReset(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, sizeof(int));
   ck_assert_int_eq(dynmem.is, initial_size);
   ck_assert_int_eq(dynmem.cs, initial_size * 2);
   ck_assert_int_eq(dynmem.bi, initial_size);
   ck_assert_int_eq(dynmem.ei, initial_size - sizeof(int));
   ck_assert_ptr_nonnull(dynmem.m);

   ck_assert_int_eq(((int *)(dynmem.m))[0], (int)0);
   ck_assert_int_eq(((int *)(dynmem.m))[2], (int)0);
   ck_assert_int_eq(((int *)(dynmem.m))[4], (int)0);
   ck_assert_int_eq(((int *)(dynmem.m))[6], (int)0);
   ck_assert_int_eq(((int *)(dynmem.m))[8], (int)0);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemReset\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_dynmem);
   tcase_add_test(test_cases, nonnull_dynmem);
   tcase_add_test(test_cases, nonnull_dynmem_appended_not_size_changed);
   tcase_add_test(test_cases, nonnull_dynmem_appended_size_changed);
   tcase_add_test(test_cases, nonnull_dynmem_prepended_not_size_changed);
   tcase_add_test(test_cases, nonnull_dynmem_prepended_size_changed);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
