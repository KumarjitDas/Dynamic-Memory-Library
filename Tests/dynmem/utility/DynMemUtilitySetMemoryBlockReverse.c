#include "check.h"

#ifndef DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#define DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#define DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#endif

#include "dynmem/utility/defines.h"
#include "dynmem/utility/utility.h"

#ifdef INT64_MAX
START_TEST(with_only_64_bit) {
   uint64_t array1[5] = {12345678, 90101112, 13141516, 17181920, 21222324};
   uint64_t array2[5];

   DynMemUtilitySetMemoryBlockReverse((uint8_t *)array2, (uint8_t *)array1, sizeof(array1));

   ck_assert_int_eq(array1[0], array2[0]);
   ck_assert_int_eq(array1[1], array2[1]);
   ck_assert_int_eq(array1[2], array2[2]);
   ck_assert_int_eq(array1[3], array2[3]);
   ck_assert_int_eq(array1[4], array2[4]);
}
END_TEST

START_TEST(with_64_and_32_bit) {
   uint8_t array1[12], array2[12];

   *(uint32_t *)array1 = 252627;
   *(uint64_t *)(array1 + sizeof(uint32_t)) = 28293031;

   DynMemUtilitySetMemoryBlockReverse(array2, array1, sizeof(array1));

   ck_assert_int_eq(*(uint32_t *)array1, *(uint32_t *)array2);
   ck_assert_int_eq(*(uint64_t *)(array1 + sizeof(uint32_t)), *(uint64_t *)(array2 + sizeof(uint32_t)));
}
END_TEST

START_TEST(with_64_and_16_bit) {
   uint8_t array1[10], array2[10];

   *(uint16_t *)array1 = 3233;
   *(uint64_t *)(array1 + sizeof(uint16_t)) = 34353637;

   DynMemUtilitySetMemoryBlockReverse(array2, array1, sizeof(array1));

   ck_assert_int_eq(*(uint16_t *)array1, *(uint16_t *)array2);
   ck_assert_int_eq(*(uint64_t *)(array1 + sizeof(uint16_t)), *(uint64_t *)(array2 + sizeof(uint16_t)));
}
END_TEST

START_TEST(with_64_and_8_bit) {
   uint8_t array1[9], array2[9];

   *(uint8_t *)array1 = 38;
   *(uint64_t *)(array1 + sizeof(uint8_t)) = 39404142;

   DynMemUtilitySetMemoryBlockReverse(array2, array1, sizeof(array1));

   ck_assert_int_eq(*(uint8_t *)array1, *(uint8_t *)array2);
   ck_assert_int_eq(*(uint64_t *)(array1 + sizeof(uint8_t)), *(uint64_t *)(array2 + sizeof(uint8_t)));
}
END_TEST

START_TEST(with_64_32_and_16_bit) {
   uint8_t array1[14], array2[14];

   *(uint16_t *)array1 = 4344;
   *(uint32_t *)(array1 + sizeof(uint16_t)) = 454647;
   *(uint64_t *)(array1 + sizeof(uint16_t) + sizeof(uint32_t)) = 48495051;

   DynMemUtilitySetMemoryBlockReverse(array2, array1, sizeof(array1));

   ck_assert_int_eq(*(uint16_t *)array1, *(uint16_t *)array2);
   ck_assert_int_eq(*(uint32_t *)(array1 + sizeof(uint16_t)), *(uint32_t *)(array2 + sizeof(uint16_t)));
   ck_assert_int_eq(*(uint64_t *)(array1 + sizeof(uint16_t) + sizeof(uint32_t)),
                    *(uint64_t *)(array2 + sizeof(uint16_t) + sizeof(uint32_t)));
}
END_TEST

START_TEST(with_64_32_and_8_bit) {
   uint8_t array1[13], array2[13];

   *(uint8_t *)array1 = 52;
   *(uint32_t *)(array1 + sizeof(uint8_t)) = 535455;
   *(uint64_t *)(array1 + sizeof(uint8_t) + sizeof(uint32_t)) = 56575859;

   DynMemUtilitySetMemoryBlockReverse(array2, array1, sizeof(array1));

   ck_assert_int_eq(*(uint8_t *)array1, *(uint8_t *)array2);
   ck_assert_int_eq(*(uint32_t *)(array1 + sizeof(uint8_t)), *(uint32_t *)(array2 + sizeof(uint8_t)));
   ck_assert_int_eq(*(uint64_t *)(array1 + sizeof(uint8_t) + sizeof(uint32_t)),
                    *(uint64_t *)(array2 + sizeof(uint8_t) + sizeof(uint32_t)));
}
END_TEST

START_TEST(with_64_16_and_8_bit) {
   uint8_t array1[11], array2[11];

   *(uint8_t *)array1 = 60;
   *(uint16_t *)(array1 + sizeof(uint8_t)) = 6162;
   *(uint64_t *)(array1 + sizeof(uint8_t) + sizeof(uint16_t)) = 63646566;

   DynMemUtilitySetMemoryBlockReverse(array2, array1, sizeof(array1));

   ck_assert_int_eq(*(uint8_t *)array1, *(uint8_t *)array2);
   ck_assert_int_eq(*(uint16_t *)(array1 + sizeof(uint8_t)), *(uint16_t *)(array2 + sizeof(uint8_t)));
   ck_assert_int_eq(*(uint64_t *)(array1 + sizeof(uint8_t) + sizeof(uint16_t)),
                    *(uint64_t *)(array2 + sizeof(uint8_t) + sizeof(uint16_t)));
}
END_TEST

START_TEST(with_64_32_16_and_8_bit) {
   uint8_t array1[15], array2[15];

   *(uint8_t *)array1 = 67;
   *(uint16_t *)(array1 + sizeof(uint8_t)) = 6869;
   *(uint32_t *)(array1 + sizeof(uint8_t) + sizeof(uint16_t)) = 707172;
   *(uint64_t *)(array1 + sizeof(uint8_t) + sizeof(uint16_t) + sizeof(uint32_t)) = 73747576;

   DynMemUtilitySetMemoryBlockReverse(array2, array1, sizeof(array1));

   ck_assert_int_eq(*(uint8_t *)array1, *(uint8_t *)array2);
   ck_assert_int_eq(*(uint16_t *)(array1 + sizeof(uint8_t)), *(uint16_t *)(array2 + sizeof(uint8_t)));
   ck_assert_int_eq(*(uint32_t *)(array1 + sizeof(uint8_t) + sizeof(uint16_t)),
                    *(uint32_t *)(array2 + sizeof(uint8_t) + sizeof(uint16_t)));
   ck_assert_int_eq(*(uint64_t *)(array1 + sizeof(uint8_t) + sizeof(uint16_t) + sizeof(uint32_t)),
                    *(uint64_t *)(array2 + sizeof(uint8_t) + sizeof(uint16_t) + sizeof(uint32_t)));
}
END_TEST
#endif  // INT64_MAX

START_TEST(with_only_32_bit) {
   uint32_t value1 = 777879;
   uint32_t value2;

   DynMemUtilitySetMemoryBlockReverse((uint8_t *)&value2, (uint8_t *)&value1, sizeof(value1));

   ck_assert_int_eq(value1, value2);
}
END_TEST

START_TEST(with_only_16_bit) {
   uint16_t value1 = 8081;
   uint16_t value2 = 0;

   DynMemUtilitySetMemoryBlockReverse((uint8_t *)&value2, (uint8_t *)&value1, sizeof(value1));

   ck_assert_int_eq(value1, value2);
}
END_TEST

START_TEST(with_only_8_bit) {
   uint8_t value1 = 82;
   uint8_t value2 = 0;

   DynMemUtilitySetMemoryBlockReverse(&value2, &value1, sizeof(value1));

   ck_assert_int_eq(value1, value2);
}
END_TEST

START_TEST(with_32_and_16_bit) {
   uint8_t array1[6], array2[6];

   *(uint16_t *)array1 = 8384;
   *(uint32_t *)(array1 + sizeof(uint16_t)) = 858687;

   DynMemUtilitySetMemoryBlockReverse(array2, array1, sizeof(array1));

   ck_assert_int_eq(*(uint16_t *)array1, *(uint16_t *)array2);
   ck_assert_int_eq(*(uint32_t *)(array1 + sizeof(uint16_t)), *(uint32_t *)(array2 + sizeof(uint16_t)));
}
END_TEST

START_TEST(with_32_and_8_bit) {
   uint8_t array1[5], array2[5];

   *(uint8_t *)array1 = 88;
   *(uint32_t *)(array1 + sizeof(uint8_t)) = 899091;

   DynMemUtilitySetMemoryBlockReverse(array2, array1, sizeof(array1));

   ck_assert_int_eq(*(uint8_t *)array1, *(uint8_t *)array2);
   ck_assert_int_eq(*(uint32_t *)(array1 + sizeof(uint8_t)), *(uint32_t *)(array2 + sizeof(uint8_t)));
}
END_TEST

START_TEST(with_16_and_8_bit) {
   uint8_t array1[3], array2[3];

   *(uint8_t *)array1 = 92;
   *(uint16_t *)(array1 + sizeof(uint8_t)) = 9394;

   DynMemUtilitySetMemoryBlockReverse(array2, array1, sizeof(array1));

   ck_assert_int_eq(*(uint8_t *)array1, *(uint8_t *)array2);
   ck_assert_int_eq(*(uint16_t *)(array1 + sizeof(uint8_t)), *(uint16_t *)(array2 + sizeof(uint8_t)));
}
END_TEST

START_TEST(with_32_16_and_8_bit) {
   uint8_t array1[7], array2[7];

   *(uint8_t *)array1 = 95;
   *(uint16_t *)(array1 + sizeof(uint8_t)) = 9697;
   *(uint32_t *)(array1 + sizeof(uint8_t) + sizeof(uint16_t)) = 9899100;

   DynMemUtilitySetMemoryBlockReverse(array2, array1, sizeof(array1));

   ck_assert_int_eq(*(uint8_t *)array1, *(uint8_t *)array2);
   ck_assert_int_eq(*(uint16_t *)(array1 + sizeof(uint8_t)), *(uint16_t *)(array2 + sizeof(uint8_t)));
   ck_assert_int_eq(*(uint32_t *)(array1 + sizeof(uint8_t) + sizeof(uint16_t)),
                    *(uint32_t *)(array2 + sizeof(uint8_t) + sizeof(uint16_t)));
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemUtilitySetMemoryBlockReverse\" function");
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
