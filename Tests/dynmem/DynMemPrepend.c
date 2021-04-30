#include "check.h"
#include "dynmem/dynmem.h"


START_TEST(prepend_null_value) {
    dynmem_t dynmem;
    intmax_t es = sizeof(int);

    ck_assert_int_eq(DynMemAllocate(&dynmem, es, 4, NULL), DYNMEM_SUCCEED);

    intmax_t cs  = dynmem.cs;
    intmax_t bi  = dynmem.bi;
    intmax_t bis = dynmem.bis;

    ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
    ck_assert_int_eq(dynmem.bi, (bi -= es));
    ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
    ck_assert_int_eq(dynmem.bi, (bi -= es));
    ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
    ck_assert_int_eq(dynmem.bi, (bi -= es));
    ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
    ck_assert_int_eq(dynmem.bi, (bi -= es));
    ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
    ck_assert_int_eq(dynmem.cs, (cs += bis)); bi -= es;
    ck_assert_int_eq(dynmem.bi, (bi += bis));
    ck_assert_int_eq(dynmem.bis, (bis *= 2));

    ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
    ck_assert_int_eq(dynmem.bi, (bi -= es));
    ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
    ck_assert_int_eq(dynmem.bi, (bi -= es));
    ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
    ck_assert_int_eq(dynmem.bi, (bi -= es));
    ck_assert_int_eq(DynMemPrepend(&dynmem, NULL), DYNMEM_SUCCEED);
    ck_assert_int_eq(dynmem.cs, (cs += bis)); bi -= es;
    ck_assert_int_eq(dynmem.bi, (bi += bis));
    ck_assert_int_eq(dynmem.bis, (bis *= 2));

    (void)DynMemDeallocate(&dynmem);
}
END_TEST


START_TEST(prepend_nonnull_value) {
    dynmem_t dynmem;
    int value = 1;

    ck_assert_int_eq(DynMemAllocate(&dynmem, sizeof(int), 4, NULL), DYNMEM_SUCCEED);

    ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
    ck_assert_int_eq(*((int*)(dynmem.m + dynmem.bi)), value);
    value++;
    ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
    ck_assert_int_eq(*((int*)(dynmem.m + dynmem.bi)), value);
    value++;
    ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
    ck_assert_int_eq(*((int*)(dynmem.m + dynmem.bi)), value);
    value++;
    ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
    ck_assert_int_eq(*((int*)(dynmem.m + dynmem.bi)), value);
    value++;
    ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
    ck_assert_int_eq(*((int*)(dynmem.m + dynmem.bi)), value);
    value++;
    ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
    ck_assert_int_eq(*((int*)(dynmem.m + dynmem.bi)), value);
    value++;
    ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
    ck_assert_int_eq(*((int*)(dynmem.m + dynmem.bi)), value);
    value++;
    ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
    ck_assert_int_eq(*((int*)(dynmem.m + dynmem.bi)), value);
    value++;
    ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
    ck_assert_int_eq(*((int*)(dynmem.m + dynmem.bi)), value);
    value++;
    ck_assert_int_eq(DynMemPrepend(&dynmem, &value), DYNMEM_SUCCEED);
    ck_assert_int_eq(*((int*)(dynmem.m + dynmem.bi)), value);

    (void)DynMemDeallocate(&dynmem);
}
END_TEST


int main() {
    Suite *suite = suite_create("Test suite for \"DynMemPrepend\" function");
    TCase *test_cases = tcase_create("Test case");

    tcase_add_test(test_cases, prepend_null_value);
    tcase_add_test(test_cases, prepend_nonnull_value);

    suite_add_tcase(suite, test_cases);

    SRunner *suite_runner = srunner_create(suite);
    srunner_run_all(suite_runner, CK_VERBOSE);

    int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);

    return failed_test_case_numbers;
}
