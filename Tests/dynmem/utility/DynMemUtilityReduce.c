#include "check.h"

#ifndef DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#define DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_ALLOCATE_H
#define DYNMEM_INTERNAL_USE_UTILITY_ALLOCATE_H
#endif

#include "dynmem/dynmem.h"
#include "dynmem/utility/defines.h"
#include "dynmem/utility/allocate.h"

START_TEST(value_not_added) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 20);
   ck_assert_int_eq(dynmem.ei, 16);
   ck_assert_ptr_nonnull(dynmem.m);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(appended__size_not_changed) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 6, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 3; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 48);
   ck_assert_int_eq(dynmem.bi, 16);
   ck_assert_int_eq(dynmem.ei, 24);
   ck_assert_ptr_nonnull(dynmem.m);

   int *memory = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 3; i++)
      ck_assert_int_eq(memory[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(appended__edge_size) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 8);
   ck_assert_int_eq(dynmem.ei, 24);
   ck_assert_ptr_nonnull(dynmem.m);

   int *memory = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(memory[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(appended__extended_size) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 8; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 4);
   ck_assert_int_eq(dynmem.ei, 32);
   ck_assert_ptr_nonnull(dynmem.m);

   int *memory = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 8; i++)
      ck_assert_int_eq(memory[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(appended__extended_size__cannot_reduce) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 12; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 80);
   ck_assert_int_eq(dynmem.bi, 16);
   ck_assert_int_eq(dynmem.ei, 60);
   ck_assert_ptr_nonnull(dynmem.m);

   int *memory = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 12; i++)
      ck_assert_int_eq(memory[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(appended__more_extended_size) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 18; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 80);
   ck_assert_int_eq(dynmem.bi, 4);
   ck_assert_int_eq(dynmem.ei, 72);
   ck_assert_ptr_nonnull(dynmem.m);

   int *memory = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 18; i++)
      ck_assert_int_eq(memory[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(appended__more_extended_size__cannot_reduce) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 24; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 160);
   ck_assert_int_eq(dynmem.bi, 32);
   ck_assert_int_eq(dynmem.ei, 124);
   ck_assert_ptr_nonnull(dynmem.m);

   int *memory = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 24; i++)
      ck_assert_int_eq(memory[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(prepended__size_not_changed) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 6, NULL), DYNMEM_SUCCEED);

   for (int i = 2; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 48);
   ck_assert_int_eq(dynmem.bi, 16);
   ck_assert_int_eq(dynmem.ei, 24);
   ck_assert_ptr_nonnull(dynmem.m);

   int *memory = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 3; i++)
      ck_assert_int_eq(memory[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(prepended__edge_size) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 4; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 8);
   ck_assert_int_eq(dynmem.ei, 24);
   ck_assert_ptr_nonnull(dynmem.m);

   int *memory = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(memory[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(prepended__extended_size) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 7; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 4);
   ck_assert_int_eq(dynmem.ei, 32);
   ck_assert_ptr_nonnull(dynmem.m);

   int *memory = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 8; i++)
      ck_assert_int_eq(memory[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(prepended__extended_size__cannot_reduce) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 11; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 80);
   ck_assert_int_eq(dynmem.bi, 16);
   ck_assert_int_eq(dynmem.ei, 60);
   ck_assert_ptr_nonnull(dynmem.m);

   int *memory = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 12; i++)
      ck_assert_int_eq(memory[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(prepended__more_extended_size) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 17; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 80);
   ck_assert_int_eq(dynmem.bi, 4);
   ck_assert_int_eq(dynmem.ei, 72);
   ck_assert_ptr_nonnull(dynmem.m);

   int *memory = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 18; i++)
      ck_assert_int_eq(memory[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(prepended__more_extended_size__cannot_reduce) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 23; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 160);
   ck_assert_int_eq(dynmem.bi, 32);
   ck_assert_int_eq(dynmem.ei, 124);
   ck_assert_ptr_nonnull(dynmem.m);

   int *memory = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 24; i++)
      ck_assert_int_eq(memory[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(value_added__edge_to_edge__size_not_changed) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 4; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   for (int i = 5; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 36);
   ck_assert_ptr_nonnull(dynmem.m);

   int *memory = (int *)(dynmem.m);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(memory[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(value_added__edge_to_edge__extended_size) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 4; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   for (int i = 5; i < 20; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 80);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 76);
   ck_assert_ptr_nonnull(dynmem.m);

   int *memory = (int *)(dynmem.m);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(memory[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(value_added__edge_to_edge__more_extended_size) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 34; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   for (int i = 35; i < 40; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityReduce(&dynmem), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 160);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 156);
   ck_assert_ptr_nonnull(dynmem.m);

   int *memory = (int *)(dynmem.m);

   for (int i = 0; i < 40; i++)
      ck_assert_int_eq(memory[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemUtilityReduce\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, value_not_added);
   tcase_add_test(test_cases, appended__size_not_changed);
   tcase_add_test(test_cases, appended__edge_size);
   tcase_add_test(test_cases, appended__extended_size);
   tcase_add_test(test_cases, appended__extended_size__cannot_reduce);
   tcase_add_test(test_cases, appended__more_extended_size);
   tcase_add_test(test_cases, appended__more_extended_size__cannot_reduce);
   tcase_add_test(test_cases, prepended__size_not_changed);
   tcase_add_test(test_cases, prepended__edge_size);
   tcase_add_test(test_cases, prepended__extended_size);
   tcase_add_test(test_cases, prepended__extended_size__cannot_reduce);
   tcase_add_test(test_cases, prepended__more_extended_size);
   tcase_add_test(test_cases, prepended__more_extended_size__cannot_reduce);
   tcase_add_test(test_cases, value_added__edge_to_edge__size_not_changed);
   tcase_add_test(test_cases, value_added__edge_to_edge__extended_size);
   tcase_add_test(test_cases, value_added__edge_to_edge__more_extended_size);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
