#include "check.h"

#ifndef DYNMEM_INTERNAL_USE_utility_defines_h
#define DYNMEM_INTERNAL_USE_utility_defines_h
#endif
#ifndef DYNMEM_INTERNAL_USE_utility_utility_h
#define DYNMEM_INTERNAL_USE_utility_utility_h
#endif

#include "utility/defines.h"
#include "utility/utility.h"

#ifdef INT64_MAX
START_TEST(with_only_64_bit) {
   uint64_t array1[5] = {123, 456, 789, 101112, 131415};

   DynMemUtilityResetMemory((uint8_t *)array1, sizeof(array1));

   ck_assert_int_eq(array1[0], (uint64_t)(0));
   ck_assert_int_eq(array1[1], (uint64_t)(0));
   ck_assert_int_eq(array1[2], (uint64_t)(0));
   ck_assert_int_eq(array1[3], (uint64_t)(0));
   ck_assert_int_eq(array1[4], (uint64_t)(0));
}
END_TEST

START_TEST(with_64_and_32_bit) {
   uint8_t array1[12];

   *(uint64_t *)array1 = 22232425;
   *(uint32_t *)(array1 + sizeof(uint64_t)) = 262728;

   DynMemUtilityResetMemory(array1, sizeof(array1));

   ck_assert_int_eq(*(uint64_t *)array1, (uint64_t)(0));
   ck_assert_int_eq(*(uint32_t *)(array1 + sizeof(uint64_t)), (uint32_t)(0));
}
END_TEST

START_TEST(with_64_and_16_bit) {
   uint8_t array1[10];

   *(uint64_t *)array1 = 29303132;
   *(uint16_t *)(array1 + sizeof(uint64_t)) = 3334;

   DynMemUtilityResetMemory(array1, sizeof(array1));

   ck_assert_int_eq(*(uint64_t *)array1, (uint64_t)(0));
   ck_assert_int_eq(*(uint16_t *)(array1 + sizeof(uint64_t)), (uint16_t)(0));
}
END_TEST

START_TEST(with_64_and_8_bit) {
   uint8_t array1[9];

   *(uint64_t *)array1 = 35363738;
   *(uint8_t *)(array1 + sizeof(uint64_t)) = 39;

   DynMemUtilityResetMemory(array1, sizeof(array1));

   ck_assert_int_eq(*(uint64_t *)array1, (uint64_t)(0));
   ck_assert_int_eq(*(uint8_t *)(array1 + sizeof(uint64_t)), (uint8_t)(0));
}
END_TEST

START_TEST(with_64_32_and_16_bit) {
   uint8_t array1[14];

   *(uint64_t *)array1 = 52535455;
   *(uint32_t *)(array1 + sizeof(uint64_t)) = 565758;
   *(uint16_t *)(array1 + sizeof(uint64_t) + sizeof(uint32_t)) = 5960;

   DynMemUtilityResetMemory(array1, sizeof(array1));

   ck_assert_int_eq(*(uint64_t *)array1, (uint64_t)(0));
   ck_assert_int_eq(*(uint32_t *)(array1 + sizeof(uint64_t)), (uint32_t)(0));
   ck_assert_int_eq(*(uint16_t *)(array1 + sizeof(uint64_t) + sizeof(uint32_t)), (uint16_t)(0));
}
END_TEST

START_TEST(with_64_32_and_8_bit) {
   uint8_t array1[13];

   *(uint64_t *)array1 = 61626364;
   *(uint32_t *)(array1 + sizeof(uint64_t)) = 656667;
   *(uint8_t *)(array1 + sizeof(uint64_t) + sizeof(uint32_t)) = 68;

   DynMemUtilityResetMemory(array1, sizeof(array1));

   ck_assert_int_eq(*(uint64_t *)array1, (uint64_t)(0));
   ck_assert_int_eq(*(uint32_t *)(array1 + sizeof(uint64_t)), (uint32_t)(0));
   ck_assert_int_eq(*(uint8_t *)(array1 + sizeof(uint64_t) + sizeof(uint32_t)), (uint8_t)(0));
}
END_TEST

START_TEST(with_64_16_and_8_bit) {
   uint8_t array1[11];

   *(uint64_t *)array1 = 69707172;
   *(uint16_t *)(array1 + sizeof(uint64_t)) = 7374;
   *(uint8_t *)(array1 + sizeof(uint64_t) + sizeof(uint16_t)) = 75;

   DynMemUtilityResetMemory(array1, sizeof(array1));

   ck_assert_int_eq(*(uint64_t *)array1, (uint64_t)(0));
   ck_assert_int_eq(*(uint16_t *)(array1 + sizeof(uint64_t)), (uint16_t)(0));
   ck_assert_int_eq(*(uint8_t *)(array1 + sizeof(uint64_t) + sizeof(uint16_t)), (uint8_t)(0));
}
END_TEST

START_TEST(with_64_32_16_and_8_bit) {
   uint8_t array1[15];

   *(uint64_t *)array1 = 83848586;
   *(uint32_t *)(array1 + sizeof(uint64_t)) = 878889;
   *(uint16_t *)(array1 + sizeof(uint64_t) + sizeof(uint32_t)) = 9091;
   *(uint8_t *)(array1 + sizeof(uint64_t) + sizeof(uint32_t) + sizeof(uint16_t)) = 92;

   DynMemUtilityResetMemory(array1, sizeof(array1));

   ck_assert_int_eq(*(uint64_t *)array1, (uint64_t)(0));
   ck_assert_int_eq(*(uint32_t *)(array1 + sizeof(uint64_t)), (uint32_t)(0));
   ck_assert_int_eq(*(uint16_t *)(array1 + sizeof(uint64_t) + sizeof(uint32_t)), (uint16_t)(0));
   ck_assert_int_eq(*(uint8_t *)(array1 + sizeof(uint64_t) + sizeof(uint32_t) + sizeof(uint16_t)), (uint8_t)(0));
}
END_TEST
#endif  // INT64_MAX

START_TEST(with_only_32_bit) {
   uint32_t value = 161718;
   DynMemUtilityResetMemory((uint8_t *)(&value), sizeof(value));
   ck_assert_int_eq(value, (uint32_t)(0));
}
END_TEST

START_TEST(with_only_16_bit) {
   uint16_t value = 1920;
   DynMemUtilityResetMemory((uint8_t *)(&value), sizeof(value));
   ck_assert_int_eq(value, (uint16_t)(0));
}
END_TEST

START_TEST(with_only_8_bit) {
   uint8_t value = 21;
   DynMemUtilityResetMemory(&value, sizeof(value));
   ck_assert_int_eq(value, (uint8_t)(0));
}
END_TEST

START_TEST(with_32_and_16_bit) {
   uint8_t array1[6];

   *(uint32_t *)array1 = 404142;
   *(uint16_t *)(array1 + sizeof(uint32_t)) = 4344;

   DynMemUtilityResetMemory(array1, sizeof(array1));

   ck_assert_int_eq(*(uint32_t *)array1, (uint32_t)(0));
   ck_assert_int_eq(*(uint16_t *)(array1 + sizeof(uint32_t)), (uint16_t)(0));
}
END_TEST

START_TEST(with_32_and_8_bit) {
   uint8_t array1[5];

   *(uint32_t *)array1 = 454647;
   *(uint8_t *)(array1 + sizeof(uint32_t)) = 48;

   DynMemUtilityResetMemory(array1, sizeof(array1));

   ck_assert_int_eq(*(uint32_t *)array1, (uint32_t)(0));
   ck_assert_int_eq(*(uint8_t *)(array1 + sizeof(uint32_t)), (uint8_t)(0));
}
END_TEST

START_TEST(with_16_and_8_bit) {
   uint8_t array1[3];

   *(uint16_t *)array1 = 4950;
   *(uint8_t *)(array1 + sizeof(uint16_t)) = 51;

   DynMemUtilityResetMemory(array1, sizeof(array1));

   ck_assert_int_eq(*(uint16_t *)array1, (uint16_t)(0));
   ck_assert_int_eq(*(uint8_t *)(array1 + sizeof(uint16_t)), (uint8_t)(0));
}
END_TEST

START_TEST(with_32_16_and_8_bit) {
   uint8_t array1[7];

   *(uint32_t *)array1 = 76777879;
   *(uint16_t *)(array1 + sizeof(uint32_t)) = 8081;
   *(uint8_t *)(array1 + sizeof(uint32_t) + sizeof(uint16_t)) = 82;

   DynMemUtilityResetMemory(array1, sizeof(array1));

   ck_assert_int_eq(*(uint32_t *)array1, (uint32_t)(0));
   ck_assert_int_eq(*(uint16_t *)(array1 + sizeof(uint32_t)), (uint16_t)(0));
   ck_assert_int_eq(*(uint8_t *)(array1 + sizeof(uint32_t) + sizeof(uint16_t)), (uint8_t)(0));
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemUtilityResetMemory\" function");
   TCase *test_cases = tcase_create("Test case");

#ifdef INT64_MAX
   tcase_add_test(test_cases, with_only_64_bit);
   tcase_add_test(test_cases, with_64_and_32_bit);
   tcase_add_test(test_cases, with_64_and_16_bit);
   tcase_add_test(test_cases, with_64_and_8_bit);
   tcase_add_test(test_cases, with_64_32_and_16_bit);
   tcase_add_test(test_cases, with_64_32_and_8_bit);
   tcase_add_test(test_cases, with_64_16_and_8_bit);
   tcase_add_test(test_cases, with_64_32_16_and_8_bit);
#endif  // INT64_MAX
   tcase_add_test(test_cases, with_only_32_bit);
   tcase_add_test(test_cases, with_only_16_bit);
   tcase_add_test(test_cases, with_only_8_bit);
   tcase_add_test(test_cases, with_32_and_16_bit);
   tcase_add_test(test_cases, with_32_and_8_bit);
   tcase_add_test(test_cases, with_16_and_8_bit);
   tcase_add_test(test_cases, with_32_16_and_8_bit);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
