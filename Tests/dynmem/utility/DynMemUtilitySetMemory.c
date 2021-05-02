#include "check.h"

#ifndef DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#define DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#define DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#endif

#include "dynmem/utility/defines.h"
#include "dynmem/utility/utility.h"

START_TEST(with_1_byte) {
   uint8_t array[5], value = 12;

   DynMemUtilitySetMemory(array, sizeof(array), &value, sizeof(value));

   ck_assert_int_eq(array[0], value);
   ck_assert_int_eq(array[1], value);
   ck_assert_int_eq(array[2], value);
   ck_assert_int_eq(array[3], value);
   ck_assert_int_eq(array[4], value);
}
END_TEST

START_TEST(with_2_bytes) {
   uint16_t array[5], value = 1234;

   DynMemUtilitySetMemory(array, sizeof(array), &value, sizeof(value));

   ck_assert_int_eq(array[0], value);
   ck_assert_int_eq(array[1], value);
   ck_assert_int_eq(array[2], value);
   ck_assert_int_eq(array[3], value);
   ck_assert_int_eq(array[4], value);
}
END_TEST

START_TEST(with_3_bytes) {
   uint8_t array1[3], array2[6];

   *(uint16_t *)array1 = 5678;
   *(uint8_t *)(array1 + sizeof(uint16_t)) = 9;

   DynMemUtilitySetMemory(array2, sizeof(array2), array1, sizeof(array1));

   ck_assert_int_eq(*(uint16_t *)array1, *(uint16_t *)array2);
   ck_assert_int_eq(*(uint8_t *)(array1 + sizeof(uint16_t)), *(uint8_t *)(array2 + sizeof(uint16_t)));

   uint8_t *temp_array2 = array2 + 3;
   ck_assert_int_eq(*(uint16_t *)array1, *(uint16_t *)temp_array2);
   ck_assert_int_eq(*(uint8_t *)(array1 + sizeof(uint16_t)), *(temp_array2 + sizeof(uint16_t)));
}
END_TEST

START_TEST(with_4_bytes) {
   uint32_t array[5], value = 101112;

   DynMemUtilitySetMemory(array, sizeof(array), &value, sizeof(value));

   ck_assert_int_eq(array[0], value);
   ck_assert_int_eq(array[1], value);
   ck_assert_int_eq(array[2], value);
   ck_assert_int_eq(array[3], value);
   ck_assert_int_eq(array[4], value);
}
END_TEST

START_TEST(with_5_bytes) {
   uint8_t array1[5], array2[10];

   *(uint32_t *)array1 = 131415;
   *(uint8_t *)(array1 + sizeof(uint32_t)) = 16;

   DynMemUtilitySetMemory(array2, sizeof(array2), array1, sizeof(array1));

   ck_assert_int_eq(*(uint32_t *)array1, *(uint32_t *)array2);
   ck_assert_int_eq(*(uint8_t *)(array1 + sizeof(uint32_t)), *(uint8_t *)(array2 + sizeof(uint32_t)));

   uint8_t *temp_array2 = array2 + 5;
   ck_assert_int_eq(*(uint32_t *)array1, *(uint32_t *)temp_array2);
   ck_assert_int_eq(*(uint8_t *)(array1 + sizeof(uint32_t)), *(temp_array2 + sizeof(uint32_t)));
}
END_TEST

START_TEST(with_6_bytes) {
   uint8_t array1[6], array2[12];

   *(uint32_t *)array1 = 171819;
   *(uint16_t *)(array1 + sizeof(uint32_t)) = 2021;

   DynMemUtilitySetMemory(array2, sizeof(array2), array1, sizeof(array1));

   ck_assert_int_eq(*(uint32_t *)array1, *(uint32_t *)array2);
   ck_assert_int_eq(*(uint16_t *)(array1 + sizeof(uint32_t)), *(uint16_t *)(array2 + sizeof(uint32_t)));

   uint8_t *temp_array2 = array2 + 6;
   ck_assert_int_eq(*(uint32_t *)array1, *(uint32_t *)temp_array2);
   ck_assert_int_eq(*(uint16_t *)(array1 + sizeof(uint32_t)), *(uint16_t *)(temp_array2 + sizeof(uint32_t)));
}
END_TEST

START_TEST(with_7_bytes) {
   const size_t size = sizeof(uint32_t) + sizeof(uint16_t) + sizeof(uint8_t);
   uint8_t array1[7], array2[14];

   *(uint32_t *)array1 = 222324;
   *(uint16_t *)(array1 + sizeof(uint32_t)) = 2526;
   *(uint8_t *)(array1 + sizeof(uint32_t) + sizeof(uint16_t)) = 27;

   DynMemUtilitySetMemory(array2, sizeof(array2), array1, sizeof(array1));

   ck_assert_int_eq(*(uint32_t *)array1, *(uint32_t *)array2);
   ck_assert_int_eq(*(uint16_t *)(array1 + sizeof(uint32_t)), *(uint16_t *)(array2 + sizeof(uint32_t)));
   ck_assert_int_eq(*(uint8_t *)(array1 + sizeof(uint32_t) + sizeof(uint16_t)),
                    *(uint8_t *)(array2 + sizeof(uint32_t) + sizeof(uint16_t)));

   uint8_t *temp_array2 = array2 + 7;
   ck_assert_int_eq(*(uint32_t *)array1, *(uint32_t *)temp_array2);
   ck_assert_int_eq(*(uint16_t *)(array1 + sizeof(uint32_t)), *(uint16_t *)(temp_array2 + sizeof(uint32_t)));
   ck_assert_int_eq(*(uint8_t *)(array1 + sizeof(uint32_t) + sizeof(uint16_t)),
                    *(temp_array2 + sizeof(uint32_t) + sizeof(uint16_t)));
}
END_TEST

START_TEST(with_3_7_bytes) {
   uint8_t array1[3], array2[7];

   *(uint16_t *)array1 = 2829;
   *(uint8_t *)(array1 + sizeof(uint16_t)) = 30;

   DynMemUtilitySetMemory(array2, sizeof(array2), array1, sizeof(array1));

   ck_assert_int_eq(*(uint16_t *)array1, *(uint16_t *)array2);
   ck_assert_int_eq(*(uint8_t *)(array1 + sizeof(uint16_t)), *(uint8_t *)(array2 + sizeof(uint16_t)));

   uint8_t *temp_array2 = array2 + 3;
   ck_assert_int_eq(*(uint16_t *)array1, *(uint16_t *)temp_array2);
   ck_assert_int_eq(*(uint8_t *)(array1 + sizeof(uint16_t)), *(temp_array2 + sizeof(uint16_t)));

   ck_assert_int_eq(*array1, *(temp_array2 + sizeof(uint16_t) + sizeof(uint8_t)));
}
END_TEST

#ifdef INT64_MAX
START_TEST(with_8_bytes) {
   uint64_t array[5], value = 31323334;

   DynMemUtilitySetMemory(array, sizeof(array), &value, sizeof(value));

   ck_assert_int_eq(array[0], value);
   ck_assert_int_eq(array[1], value);
   ck_assert_int_eq(array[2], value);
   ck_assert_int_eq(array[3], value);
   ck_assert_int_eq(array[4], value);
}
END_TEST
#endif  // INT64_MAX

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemUtilitySetMemory\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, with_1_byte);
   tcase_add_test(test_cases, with_2_bytes);
   tcase_add_test(test_cases, with_3_bytes);
   tcase_add_test(test_cases, with_4_bytes);
   tcase_add_test(test_cases, with_5_bytes);
   tcase_add_test(test_cases, with_6_bytes);
   tcase_add_test(test_cases, with_7_bytes);
   tcase_add_test(test_cases, with_3_7_bytes);
#ifdef INT64_MAX
   tcase_add_test(test_cases, with_8_bytes);
// tcase_add_test(test_cases, with_13_bytes);
// tcase_add_test(test_cases, with_16_bytes);
// tcase_add_test(test_cases, with_21_bytes);
// tcase_add_test(test_cases, with_25_bytes);
#endif  // INT64_MAX

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
