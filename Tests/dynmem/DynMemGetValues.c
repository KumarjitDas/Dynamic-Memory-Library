#include "check.h"
#include "dynmem/dynmem.h"

#include <stdlib.h>

START_TEST(null_dynmem_null_array) {
   ck_assert_int_eq(DynMemGetValues(NULL, 0, 4, NULL, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, 0, -1, NULL, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, -4, 4, NULL, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, -4, -1, NULL, 4, NULL), DYNMEM_FAILED);
}
END_TEST

START_TEST(null_dynmem_nonnull_array) {
   int *array = malloc(sizeof(int));

   ck_assert_ptr_nonnull(array);
   ck_assert_int_eq(DynMemGetValues(NULL, 0, 4, array, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, 0, -1, array, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, -4, 4, array, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(NULL, -4, -1, array, 4, NULL), DYNMEM_FAILED);

   free(array);
}
END_TEST

START_TEST(nonnull_dynmem_null_array) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemGetValues(&dynmem, 0, 4, NULL, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 0, -1, NULL, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -4, 4, NULL, 4, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemGetValues(&dynmem, -4, -1, NULL, 4, NULL), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem_nonnull_array) {
   dynmem_t dynmem;
   intmax_t begin, end;
   intmax_t length = 5;
   intmax_t element_size = sizeof(int);
   intmax_t size;

   ck_assert_int_eq(DynMemAllocate(&dynmem, element_size, length, NULL), DYNMEM_SUCCEED);

   for (int i = 5; i >= 1; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   for (int i = 6; i <= 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   int *array = malloc(length * element_size * 2);
   ck_assert_ptr_nonnull(array);

   length *= 2;

   begin = 0;
   end = 10;
   ck_assert_int_eq(DynMemGetValues(&dynmem, begin, end, array, length, &size), DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(i + 1, array[i - begin]);

   ck_assert_int_eq(size, end - begin);

   begin = 1;
   end = 10;
   ck_assert_int_eq(DynMemGetValues(&dynmem, begin, end, array, length, &size), DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(i + 1, array[i - begin]);

   ck_assert_int_eq(size, end - begin);

   begin = 0;
   end = 9;
   ck_assert_int_eq(DynMemGetValues(&dynmem, begin, end, array, length, &size), DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(i + 1, array[i - begin]);

   ck_assert_int_eq(size, end - begin);

   begin = 1;
   end = 9;
   ck_assert_int_eq(DynMemGetValues(&dynmem, begin, end, array, length, &size), DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(i + 1, array[i - begin]);

   ck_assert_int_eq(size, end - begin);

   begin = 4;
   end = 5;
   ck_assert_int_eq(DynMemGetValues(&dynmem, begin, end, array, length, &size), DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(i + 1, array[i - begin]);

   ck_assert_int_eq(size, end - begin);

   begin = 5;
   end = 5;
   ck_assert_int_eq(DynMemGetValues(&dynmem, begin, end, array, length, &size), DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemGetValues(&dynmem, 0 * element_size, 999 * element_size, array, length, &size),
                    DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);

   free(array);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemGetValues\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_dynmem_null_array);
   tcase_add_test(test_cases, null_dynmem_nonnull_array);
   tcase_add_test(test_cases, nonnull_dynmem_null_array);
   tcase_add_test(test_cases, nonnull_dynmem_nonnull_array);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
