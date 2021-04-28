#include "check.h"

#ifndef DYNMEM_INTERNAL_USE_utility_defines_h
#   define DYNMEM_INTERNAL_USE_utility_defines_h
#endif
#ifndef DYNMEM_INTERNAL_USE_utility_utility_h
#   define DYNMEM_INTERNAL_USE_utility_utility_h
#endif

#include "utility/defines.h"
#include "utility/utility.h"


START_TEST(with_1_byte) {
    const size_t size = 5;
    uint8_t array[size], value = 12;

    DynMemUtilitySetMemory(array, sizeof(array), &value, sizeof(value));

    ck_assert_int_eq(array[0], value);
    ck_assert_int_eq(array[1], value);
    ck_assert_int_eq(array[2], value);
    ck_assert_int_eq(array[3], value);
    ck_assert_int_eq(array[4], value);
}
END_TEST


START_TEST(with_2_bytes) {
    const size_t size = 5;
    uint16_t array[size], value = 1234;

    DynMemUtilitySetMemory(array, sizeof(array), &value, sizeof(value));

    ck_assert_int_eq(array[0], value);
    ck_assert_int_eq(array[1], value);
    ck_assert_int_eq(array[2], value);
    ck_assert_int_eq(array[3], value);
    ck_assert_int_eq(array[4], value);
}
END_TEST


START_TEST(with_3_bytes) {
    const size_t size = sizeof(uint16_t) + sizeof(uint8_t);
    uint8_t array1[size], array2[size * 2];

    *(uint16_t*)array1 = 5678;
    *(uint8_t*)(array1 + sizeof(uint16_t)) = 9;

    DynMemUtilitySetMemory(array2, sizeof(array2), array1, sizeof(array1));

    ck_assert_int_eq(*(uint16_t*)array1, *(uint16_t*)array2);
    ck_assert_int_eq(*(uint8_t*)(array1 + sizeof(uint16_t)), *(uint8_t*)(array2 + sizeof(uint16_t)));

    uint8_t *temp_array2 = array2 + size;
    ck_assert_int_eq(*(uint16_t*)array1, *(uint16_t*)temp_array2);
    ck_assert_int_eq(*(uint8_t*)(array1 + sizeof(uint16_t)), *(temp_array2 + sizeof(uint16_t)));
}
END_TEST


START_TEST(with_4_bytes) {
    const size_t size = 5;
    uint32_t array[size], value = 101112;

    DynMemUtilitySetMemory(array, sizeof(array), &value, sizeof(value));

    ck_assert_int_eq(array[0], value);
    ck_assert_int_eq(array[1], value);
    ck_assert_int_eq(array[2], value);
    ck_assert_int_eq(array[3], value);
    ck_assert_int_eq(array[4], value);
}
END_TEST


START_TEST(with_5_bytes) {
    const size_t size = sizeof(uint32_t) + sizeof(uint8_t);
    uint8_t array1[size], array2[size * 2];

    *(uint32_t*)array1 = 131415;
    *(uint8_t*)(array1 + sizeof(uint32_t)) = 16;

    DynMemUtilitySetMemory(array2, sizeof(array2), array1, sizeof(array1));

    ck_assert_int_eq(*(uint32_t*)array1, *(uint32_t*)array2);
    ck_assert_int_eq(*(uint8_t*)(array1 + sizeof(uint32_t)), *(uint8_t*)(array2 + sizeof(uint32_t)));

    uint8_t *temp_array2 = array2 + size;
    ck_assert_int_eq(*(uint32_t*)array1, *(uint32_t*)temp_array2);
    ck_assert_int_eq(*(uint8_t*)(array1 + sizeof(uint32_t)), *(temp_array2 + sizeof(uint32_t)));
}
END_TEST


START_TEST(with_6_bytes) {
    const size_t size = sizeof(uint32_t) + sizeof(uint16_t);
    uint8_t array1[size], array2[size * 2];

    *(uint32_t*)array1 = 171819;
    *(uint16_t*)(array1 + sizeof(uint32_t)) = 2021;

    DynMemUtilitySetMemory(array2, sizeof(array2), array1, sizeof(array1));

    ck_assert_int_eq(*(uint32_t*)array1, *(uint32_t*)array2);
    ck_assert_int_eq(*(uint16_t*)(array1 + sizeof(uint32_t)), *(uint16_t*)(array2 + sizeof(uint32_t)));

    uint8_t *temp_array2 = array2 + size;
    ck_assert_int_eq(*(uint32_t*)array1, *(uint32_t*)temp_array2);
    ck_assert_int_eq(*(uint16_t*)(array1 + sizeof(uint32_t)), *(uint16_t*)(temp_array2 + sizeof(uint32_t)));
}
END_TEST


START_TEST(with_7_bytes) {
    const size_t size = sizeof(uint32_t) + sizeof(uint16_t) + sizeof(uint8_t);
    uint8_t array1[size], array2[size * 2];

    *(uint32_t*)array1 = 222324;
    *(uint16_t*)(array1 + sizeof(uint32_t)) = 2526;
    *(uint8_t*)(array1 + sizeof(uint32_t) + sizeof(uint16_t)) = 27;

    DynMemUtilitySetMemory(array2, sizeof(array2), array1, sizeof(array1));

    ck_assert_int_eq(*(uint32_t*)array1, *(uint32_t*)array2);
    ck_assert_int_eq(*(uint16_t*)(array1 + sizeof(uint32_t)), *(uint16_t*)(array2 + sizeof(uint32_t)));
    ck_assert_int_eq(*(uint8_t*)(array1 + sizeof(uint32_t) + sizeof(uint16_t)),
                     *(uint8_t*)(array2 + sizeof(uint32_t) + sizeof(uint16_t))
                    );

    uint8_t *temp_array2 = array2 + size;
    ck_assert_int_eq(*(uint32_t*)array1, *(uint32_t*)temp_array2);
    ck_assert_int_eq(*(uint16_t*)(array1 + sizeof(uint32_t)), *(uint16_t*)(temp_array2 + sizeof(uint32_t)));
    ck_assert_int_eq(*(uint8_t*)(array1 + sizeof(uint32_t) + sizeof(uint16_t)),
                     *(temp_array2 + sizeof(uint32_t) + sizeof(uint16_t))
                    );
}
END_TEST


START_TEST(with_3_7_bytes) {
    const size_t size = sizeof(uint16_t) + sizeof(uint8_t);
    uint8_t array1[size], array2[size * 2 + 1];

    *(uint16_t*)array1 = 2829;
    *(uint8_t*)(array1 + sizeof(uint16_t)) = 30;

    DynMemUtilitySetMemory(array2, sizeof(array2), array1, sizeof(array1));

    ck_assert_int_eq(*(uint16_t*)array1, *(uint16_t*)array2);
    ck_assert_int_eq(*(uint8_t*)(array1 + sizeof(uint16_t)), *(uint8_t*)(array2 + sizeof(uint16_t)));

    uint8_t *temp_array2 = array2 + size;
    ck_assert_int_eq(*(uint16_t*)array1, *(uint16_t*)temp_array2);
    ck_assert_int_eq(*(uint8_t*)(array1 + sizeof(uint16_t)), *(temp_array2 + sizeof(uint16_t)));

    ck_assert_int_eq(*array1, *(temp_array2 + sizeof(uint16_t) + sizeof(uint8_t)));
}
END_TEST


#ifdef INT64_MAX
START_TEST(with_8_bytes) {
    const size_t size = 5;
    uint64_t array[size], value = 31323334;

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
