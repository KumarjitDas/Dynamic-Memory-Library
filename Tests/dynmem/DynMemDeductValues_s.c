#include "check.h"
#include "dynmem/dynmem.h"

#include <stdlib.h>

START_TEST(Null_dynmem) {
   int32_t *memory = malloc(20);
   intmax_t got_size;

   ck_assert_int_eq(DynMemDeductValues_s(NULL, 0, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(NULL, 0, NULL, 0, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(NULL, 0, NULL, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(NULL, 0, NULL, 20, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(NULL, 0, memory, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(NULL, 0, memory, 0, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(NULL, 0, memory, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(NULL, 0, memory, 20, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(NULL, 5, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(NULL, 5, NULL, 0, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(NULL, 5, NULL, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(NULL, 5, NULL, 20, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(NULL, 5, memory, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(NULL, 5, memory, 0, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(NULL, 5, memory, 20, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(NULL, 5, memory, 20, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   free(memory);
}
END_TEST

START_TEST(Nonnull_dynmem__Null_memory__Value_not_added) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, -3, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 0, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 3, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 5, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(Nonnull_dynmem__Null_memory__Appended__Size_not_changed) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 1; i <= 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, -3, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 0, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 3, NULL, 0, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 24);

   for (int32_t i = 3; i <= 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 5, NULL, 0, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 16);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(Nonnull_dynmem__Null_memory__Appended__Extended_size) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 1; i <= 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, -3, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 0, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 5, NULL, 0, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 36);

   for (int32_t i = 6; i <= 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 10, NULL, 0, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 16);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(Nonnull_dynmem__Null_memory__Appended__More_extended_size) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 1; i <= 20; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, -3, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 0, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 10, NULL, 0, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 56);

   for (int32_t i = 11; i <= 20; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 20, NULL, 0, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 16);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(Nonnull_dynmem__Null_memory__Prepended__Size_not_changed) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 5; i >= 1; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, -3, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 0, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 3, NULL, 0, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 4);

   for (int32_t i = 3; i <= 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 5, NULL, 0, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, -4);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(Nonnull_dynmem__Null_memory__Prepended__Extended_size) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 10; i >= 1; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, -3, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 0, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 5, NULL, 0, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 36);

   for (int32_t i = 6; i <= 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 10, NULL, 0, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 16);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(Nonnull_dynmem__Null_memory__Prepended__More_extended_size) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int32_t i = 20; i >= 1; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, -3, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 0, NULL, 0, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 10, NULL, 0, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 96);

   for (int32_t i = 11; i <= 20; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 20, NULL, 0, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 56);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(Nonnull_dynmem__Nonnull_memory__Value_not_added) {
   dynmem_t dynmem;
   intmax_t got_size;
   int32_t *memory = malloc(20);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, -3, memory, 20, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 0, memory, 20, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 3, memory, 20, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 5, memory, 20, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 3, memory, 0, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 5, memory, 40, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
   free(memory);
}
END_TEST

START_TEST(Nonnull_dynmem__Nonnull_memory__Appended__Size_not_changed) {
   dynmem_t dynmem;
   intmax_t got_size;
   int32_t *memory = malloc(20);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, -3, memory, 0, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 0, memory, 0, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);

   for (int32_t i = 1; i <= 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 3, memory, 20, &got_size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 24);
   ck_assert_int_eq(got_size, 12);

   for (int32_t i = 3; i <= 5; i++)
      ck_assert_int_eq(memory[i - 3], i);

   for (int32_t i = 3; i <= 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 5, memory, 0, &got_size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 16);
   ck_assert_int_eq(got_size, 20);

   for (int32_t i = 1; i <= 5; i++)
      ck_assert_int_eq(memory[i - 1], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(Nonnull_dynmem__Nonnull_memory__Appended__Extended_size) {
   dynmem_t dynmem;
   intmax_t got_size;
   int32_t *memory = malloc(40);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, -3, memory, 0, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 0, memory, 0, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);

   for (int32_t i = 1; i <= 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 5, memory, 40, &got_size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 36);
   ck_assert_int_eq(got_size, 20);

   for (int32_t i = 6; i <= 10; i++)
      ck_assert_int_eq(memory[i - 6], i);

   for (int32_t i = 6; i <= 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 10, memory, 0, &got_size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 16);
   ck_assert_int_eq(got_size, 40);

   for (int32_t i = 1; i <= 10; i++)
      ck_assert_int_eq(memory[i - 1], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(Nonnull_dynmem__Nonnull_memory__Appended__More_extended_size) {
   dynmem_t dynmem;
   intmax_t got_size;
   int32_t *memory = malloc(80);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, -3, memory, 0, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 0, memory, 0, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);

   for (int32_t i = 1; i <= 20; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 10, memory, 80, &got_size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 56);
   ck_assert_int_eq(got_size, 40);

   for (int32_t i = 11; i <= 20; i++)
      ck_assert_int_eq(memory[i - 11], i);

   for (int32_t i = 11; i <= 20; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 20, memory, 0, &got_size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 16);
   ck_assert_int_eq(got_size, 80);

   for (int32_t i = 1; i <= 20; i++)
      ck_assert_int_eq(memory[i - 1], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(Nonnull_dynmem__Nonnull_memory__Prepended__Size_not_changed) {
   dynmem_t dynmem;
   intmax_t got_size;
   int32_t *memory = malloc(20);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, -3, memory, 0, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 0, memory, 0, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);

   for (int32_t i = 5; i >= 1; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 3, memory, 20, &got_size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 4);
   ck_assert_int_eq(got_size, 12);

   for (int32_t i = 3; i <= 5; i++)
      ck_assert_int_eq(memory[i - 3], i);

   for (int32_t i = 3; i <= 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 5, memory, 0, &got_size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, -4);
   ck_assert_int_eq(got_size, 20);

   for (int32_t i = 1; i <= 5; i++)
      ck_assert_int_eq(memory[i - 1], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(Nonnull_dynmem__Nonnull_memory__Prepended__Extended_size) {
   dynmem_t dynmem;
   intmax_t got_size;
   int32_t *memory = malloc(40);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, -3, memory, 0, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 0, memory, 0, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);

   for (int32_t i = 10; i >= 1; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 5, memory, 40, &got_size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 36);
   ck_assert_int_eq(got_size, 20);

   for (int32_t i = 6; i <= 10; i++)
      ck_assert_int_eq(memory[i - 6], i);

   for (int32_t i = 6; i <= 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 10, memory, 0, &got_size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 16);
   ck_assert_int_eq(got_size, 40);

   for (int32_t i = 1; i <= 10; i++)
      ck_assert_int_eq(memory[i - 1], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(Nonnull_dynmem__Nonnull_memory__Prepended__More_extended_size) {
   dynmem_t dynmem;
   intmax_t got_size;
   int32_t *memory = malloc(80);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, -3, memory, 0, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);
   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 0, memory, 0, &got_size), DYNMEM_FAILED);
   ck_assert_int_eq(got_size, 0);

   for (int32_t i = 20; i >= 1; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 10, memory, 80, &got_size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 96);
   ck_assert_int_eq(got_size, 40);

   for (int32_t i = 11; i <= 20; i++)
      ck_assert_int_eq(memory[i - 11], i);

   for (int32_t i = 11; i <= 20; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemDeductValues_s(&dynmem, 20, memory, 0, &got_size), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.ei, 56);
   ck_assert_int_eq(got_size, 80);

   for (int32_t i = 1; i <= 20; i++)
      ck_assert_int_eq(memory[i - 1], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemDeduct\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, Null_dynmem);
   tcase_add_test(test_cases, Nonnull_dynmem__Null_memory__Value_not_added);
   tcase_add_test(test_cases, Nonnull_dynmem__Null_memory__Appended__Size_not_changed);
   tcase_add_test(test_cases, Nonnull_dynmem__Null_memory__Appended__Extended_size);
   tcase_add_test(test_cases, Nonnull_dynmem__Null_memory__Appended__More_extended_size);
   tcase_add_test(test_cases, Nonnull_dynmem__Null_memory__Prepended__Size_not_changed);
   tcase_add_test(test_cases, Nonnull_dynmem__Null_memory__Prepended__Extended_size);
   tcase_add_test(test_cases, Nonnull_dynmem__Null_memory__Prepended__More_extended_size);
   tcase_add_test(test_cases, Nonnull_dynmem__Nonnull_memory__Value_not_added);
   tcase_add_test(test_cases, Nonnull_dynmem__Nonnull_memory__Appended__Size_not_changed);
   tcase_add_test(test_cases, Nonnull_dynmem__Nonnull_memory__Appended__Extended_size);
   tcase_add_test(test_cases, Nonnull_dynmem__Nonnull_memory__Appended__More_extended_size);
   tcase_add_test(test_cases, Nonnull_dynmem__Nonnull_memory__Prepended__Size_not_changed);
   tcase_add_test(test_cases, Nonnull_dynmem__Nonnull_memory__Prepended__Extended_size);
   tcase_add_test(test_cases, Nonnull_dynmem__Nonnull_memory__Prepended__More_extended_size);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
