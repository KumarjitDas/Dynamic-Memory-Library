#include "check.h"
#include "dynmem/dynmem.h"

#include <stdlib.h>

START_TEST(null_test) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemCopy(NULL, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemCopy(NULL, &dynmem), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemCopy(&dynmem, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(value_not_added) {
   dynmem_t destination, source;

   ck_assert_int_eq(DynMemAllocate(&source, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemCopy(&destination, &source), DYNMEM_SUCCEED);
   ck_assert_int_eq(destination.es, 4);
   ck_assert_int_eq(destination.is, 20);
   ck_assert_int_eq(destination.cs, 40);
   ck_assert_int_eq(destination.bi, 20);
   ck_assert_int_eq(destination.ei, 16);
   ck_assert_ptr_nonnull(destination.m);
   ck_assert_int_eq(DynMemDeallocate(&source), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeallocate(&destination), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(appended__size_not_changed) {
   dynmem_t destination, source;

   ck_assert_int_eq(DynMemAllocate(&source, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 1; i <= 5; i++)
      ck_assert_int_eq(DynMemAppend(&source, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemCopy(&destination, &source), DYNMEM_SUCCEED);
   ck_assert_int_eq(destination.es, 4);
   ck_assert_int_eq(destination.is, 20);
   ck_assert_int_eq(destination.cs, 40);
   ck_assert_int_eq(destination.bi, 20);
   ck_assert_int_eq(destination.ei, 36);
   ck_assert_ptr_nonnull(destination.m);

   int32_t *array1 = (int32_t *)(destination.m + destination.bi);
   int32_t *array2 = (int32_t *)(source.m + source.bi);

   for (int32_t i = 0; i < 5; i++)
      ck_assert_int_eq(array1[i], array2[i]);

   ck_assert_int_eq(DynMemDeallocate(&source), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeallocate(&destination), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(appended__extended_size) {
   dynmem_t destination, source;

   ck_assert_int_eq(DynMemAllocate(&source, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 1; i <= 10; i++)
      ck_assert_int_eq(DynMemAppend(&source, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemCopy(&destination, &source), DYNMEM_SUCCEED);
   ck_assert_int_eq(destination.es, 4);
   ck_assert_int_eq(destination.is, 20);
   ck_assert_int_eq(destination.cs, 80);
   ck_assert_int_eq(destination.bi, 20);
   ck_assert_int_eq(destination.ei, 56);
   ck_assert_ptr_nonnull(destination.m);

   int32_t *array1 = (int32_t *)(destination.m + destination.bi);
   int32_t *array2 = (int32_t *)(source.m + source.bi);

   for (int32_t i = 0; i < 10; i++)
      ck_assert_int_eq(array1[i], array2[i]);

   ck_assert_int_eq(DynMemDeallocate(&source), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeallocate(&destination), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(appended__more_extended_size) {
   dynmem_t destination, source;

   ck_assert_int_eq(DynMemAllocate(&source, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 1; i <= 20; i++)
      ck_assert_int_eq(DynMemAppend(&source, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemCopy(&destination, &source), DYNMEM_SUCCEED);
   ck_assert_int_eq(destination.es, 4);
   ck_assert_int_eq(destination.is, 20);
   ck_assert_int_eq(destination.cs, 160);
   ck_assert_int_eq(destination.bi, 20);
   ck_assert_int_eq(destination.ei, 96);
   ck_assert_ptr_nonnull(destination.m);

   int32_t *array1 = (int32_t *)(destination.m + destination.bi);
   int32_t *array2 = (int32_t *)(source.m + source.bi);

   for (int32_t i = 0; i < 20; i++)
      ck_assert_int_eq(array1[i], array2[i]);

   ck_assert_int_eq(DynMemDeallocate(&source), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeallocate(&destination), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(prepended__size_not_changed) {
   dynmem_t destination, source;

   ck_assert_int_eq(DynMemAllocate(&source, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 1; i <= 5; i++)
      ck_assert_int_eq(DynMemPrepend(&source, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemCopy(&destination, &source), DYNMEM_SUCCEED);
   ck_assert_int_eq(destination.es, 4);
   ck_assert_int_eq(destination.is, 20);
   ck_assert_int_eq(destination.cs, 40);
   ck_assert_int_eq(destination.bi, 0);
   ck_assert_int_eq(destination.ei, 16);
   ck_assert_ptr_nonnull(destination.m);

   int32_t *array1 = (int32_t *)(destination.m + destination.bi);
   int32_t *array2 = (int32_t *)(source.m + source.bi);

   for (int32_t i = 0; i < 5; i++)
      ck_assert_int_eq(array1[i], array2[i]);

   ck_assert_int_eq(DynMemDeallocate(&source), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeallocate(&destination), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(prepended__extended_size) {
   dynmem_t destination, source;

   ck_assert_int_eq(DynMemAllocate(&source, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 1; i <= 10; i++)
      ck_assert_int_eq(DynMemPrepend(&source, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemCopy(&destination, &source), DYNMEM_SUCCEED);
   ck_assert_int_eq(destination.es, 4);
   ck_assert_int_eq(destination.is, 20);
   ck_assert_int_eq(destination.cs, 80);
   ck_assert_int_eq(destination.bi, 20);
   ck_assert_int_eq(destination.ei, 56);
   ck_assert_ptr_nonnull(destination.m);

   int32_t *array1 = (int32_t *)(destination.m + destination.bi);
   int32_t *array2 = (int32_t *)(source.m + source.bi);

   for (int32_t i = 0; i < 10; i++)
      ck_assert_int_eq(array1[i], array2[i]);

   ck_assert_int_eq(DynMemDeallocate(&source), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeallocate(&destination), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(prepended__more_extended_size) {
   dynmem_t destination, source;

   ck_assert_int_eq(DynMemAllocate(&source, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 1; i <= 20; i++)
      ck_assert_int_eq(DynMemPrepend(&source, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemCopy(&destination, &source), DYNMEM_SUCCEED);
   ck_assert_int_eq(destination.es, 4);
   ck_assert_int_eq(destination.is, 20);
   ck_assert_int_eq(destination.cs, 160);
   ck_assert_int_eq(destination.bi, 60);
   ck_assert_int_eq(destination.ei, 136);
   ck_assert_ptr_nonnull(destination.m);

   int32_t *array1 = (int32_t *)(destination.m + destination.bi);
   int32_t *array2 = (int32_t *)(source.m + source.bi);

   for (int32_t i = 0; i < 20; i++)
      ck_assert_int_eq(array1[i], array2[i]);

   ck_assert_int_eq(DynMemDeallocate(&source), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeallocate(&destination), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemCopy\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_test);
   tcase_add_test(test_cases, value_not_added);
   tcase_add_test(test_cases, appended__size_not_changed);
   tcase_add_test(test_cases, appended__extended_size);
   tcase_add_test(test_cases, appended__more_extended_size);
   tcase_add_test(test_cases, prepended__size_not_changed);
   tcase_add_test(test_cases, prepended__extended_size);
   tcase_add_test(test_cases, prepended__more_extended_size);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
