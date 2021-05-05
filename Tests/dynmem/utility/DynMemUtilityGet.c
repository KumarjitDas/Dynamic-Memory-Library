#include "check.h"

#ifndef DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#define DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_SET_GET_H
#define DYNMEM_INTERNAL_USE_UTILITY_SET_GET_H
#endif

#include "dynmem/dynmem.h"
#include "dynmem/utility/defines.h"
#include "dynmem/utility/set-get.h"

START_TEST(positive_index) {
   dynmem_t dynmem;
   int value;
   intmax_t element_size = sizeof(value);

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, 2, NULL), DYNMEM_SUCCEED);

   value = 22;
   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   value = 11;
   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   value = 33;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);
   value = 44;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityGet(&dynmem, 0 * element_size, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(value, 11);
   ck_assert_int_eq(DynMemUtilityGet(&dynmem, 1 * element_size, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(value, 22);
   ck_assert_int_eq(DynMemUtilityGet(&dynmem, 3 * element_size, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(value, 44);
   ck_assert_int_eq(DynMemUtilityGet(&dynmem, 999 * element_size, &value), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(negative_index) {
   dynmem_t dynmem;
   int value;
   intmax_t element_size = sizeof(value);

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, 2, NULL), DYNMEM_SUCCEED);

   value = 22;
   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   value = 11;
   ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
   value = 33;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);
   value = 44;
   ck_assert_int_eq(DynMemAppend(&dynmem, &value), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemUtilityGet(&dynmem, -4 * element_size, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(value, 11);
   ck_assert_int_eq(DynMemUtilityGet(&dynmem, -3 * element_size, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(value, 22);
   ck_assert_int_eq(DynMemUtilityGet(&dynmem, -1 * element_size, &value), DYNMEM_SUCCEED);
   ck_assert_int_eq(value, 44);
   ck_assert_int_eq(DynMemUtilityGet(&dynmem, -999 * element_size, &value), DYNMEM_FAILED);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemUtilityGet\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, positive_index);
   tcase_add_test(test_cases, negative_index);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
