#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_dynmem) {
   int32_t *pointer;

   ck_assert_int_eq(DynMemGetEnd(NULL, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetEnd(NULL, &pointer), DYNMEM_FAILED);
   ck_assert_ptr_null(pointer);
}
END_TEST

START_TEST(nonnull_dynmem) {
   dynmem_t dynmem;
   int32_t *pointer;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemGetEnd(&dynmem, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetEnd(&dynmem, &pointer), DYNMEM_FAILED);
   ck_assert_ptr_null(pointer);

   for (int32_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemGetEnd(&dynmem, &pointer), DYNMEM_SUCCEED);
   ck_assert_ptr_eq(pointer, dynmem.m + 36);

   for (int32_t i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemGetEnd(&dynmem, &pointer), DYNMEM_SUCCEED);
   ck_assert_ptr_eq(pointer, dynmem.m + 56);

   for (int32_t i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemGetEnd(&dynmem, &pointer), DYNMEM_SUCCEED);
   ck_assert_ptr_eq(pointer, dynmem.m + 96);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemGetEnd\" function");
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
