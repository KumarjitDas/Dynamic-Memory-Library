#include "check.h"

#ifndef DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#define DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_STACK_QUEUE_H
#define DYNMEM_INTERNAL_USE_UTILITY_STACK_QUEUE_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_SET_GET_H
#define DYNMEM_INTERNAL_USE_UTILITY_SET_GET_H
#endif

#include "dynmem/dynmem.h"
#include "dynmem/utility/defines.h"
#include "dynmem/utility/stack-queue.h"

#include <stdlib.h>

START_TEST(null_memory__minimum_size) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemUtilityPrepend(&dynmem, NULL, 4), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 20);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(null_memory__edged_size) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemUtilityPrepend(&dynmem, NULL, 20), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 20);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(null_memory__extended_size) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemUtilityPrepend(&dynmem, NULL, 40), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 80);
   ck_assert_int_eq(dynmem.bi, 40);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(null_memory__more_extended_size) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemUtilityPrepend(&dynmem, NULL, 80), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 160);
   ck_assert_int_eq(dynmem.bi, 80);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_memory__minimum_size) {
   dynmem_t dynmem;
   uint8_t *memory = malloc(4);

   ck_assert_ptr_nonnull(memory);

   for (intmax_t i = 0; i < 4; i++)
      memory[i] = (uint8_t)(i + 1);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemUtilityPrepend(&dynmem, memory, 4), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 20);

   uint8_t *temporary_memory = dynmem.m + dynmem.bi - 4;

   for (intmax_t i = 0; i < 4; i++)
      ck_assert_int_eq(temporary_memory[i], memory[i]);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);

   free(memory);
}
END_TEST

START_TEST(nonnull_memory__edged_size) {
   dynmem_t dynmem;
   uint8_t *memory = malloc(20);

   for (intmax_t i = 0; i < 20; i++)
      memory[i] = (uint8_t)(i + 1);

   ck_assert_ptr_nonnull(memory);
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemUtilityPrepend(&dynmem, memory, 20), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 20);

   uint8_t *temporary_memory = dynmem.m + dynmem.bi - 20;

   for (intmax_t i = 0; i < 20; i++)
      ck_assert_int_eq(temporary_memory[i], memory[i]);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);

   free(memory);
}
END_TEST

START_TEST(nonnull_memory__extended_size) {
   dynmem_t dynmem;
   uint8_t *memory = malloc(40);

   for (intmax_t i = 0; i < 40; i++)
      memory[i] = (uint8_t)(i + 1);

   ck_assert_ptr_nonnull(memory);
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemUtilityPrepend(&dynmem, memory, 40), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 80);
   ck_assert_int_eq(dynmem.bi, 40);

   uint8_t *temporary_memory = dynmem.m + dynmem.bi - 40;

   for (intmax_t i = 0; i < 40; i++)
      ck_assert_int_eq(temporary_memory[i], memory[i]);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);

   free(memory);
}
END_TEST

START_TEST(nonnull_memory__more_extended_size) {
   dynmem_t dynmem;
   uint8_t *memory = malloc(80);

   for (intmax_t i = 0; i < 80; i++)
      memory[i] = (uint8_t)(i + 1);

   ck_assert_ptr_nonnull(memory);
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemUtilityPrepend(&dynmem, memory, 80), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 160);
   ck_assert_int_eq(dynmem.bi, 80);

   uint8_t *temporary_memory = dynmem.m + dynmem.bi - 80;

   for (intmax_t i = 0; i < 80; i++)
      ck_assert_int_eq(temporary_memory[i], memory[i]);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);

   free(memory);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemUtilityPrepend\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_memory__minimum_size);
   tcase_add_test(test_cases, null_memory__edged_size);
   tcase_add_test(test_cases, null_memory__extended_size);
   tcase_add_test(test_cases, null_memory__more_extended_size);
   tcase_add_test(test_cases, nonnull_memory__minimum_size);
   tcase_add_test(test_cases, nonnull_memory__edged_size);
   tcase_add_test(test_cases, nonnull_memory__extended_size);
   tcase_add_test(test_cases, nonnull_memory__more_extended_size);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
