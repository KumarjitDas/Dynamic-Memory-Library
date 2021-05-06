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

#include <stdlib.h>

START_TEST(test) {
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

   begin = 0;
   end = 10;
   ck_assert_int_eq(DynMemUtilityGetValues(&dynmem, begin * element_size, end * element_size,
                                           array, length * element_size * 2, &size),
                    DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(i + 1, array[i - begin]);

   ck_assert_int_eq(size, (end - begin) * element_size);

   begin = 1;
   end = 10;
   ck_assert_int_eq(DynMemUtilityGetValues(&dynmem, begin * element_size, end * element_size,
                                           array, length * element_size * 2, &size),
                    DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(i + 1, array[i - begin]);

   ck_assert_int_eq(size, (end - begin) * element_size);

   begin = 0;
   end = 9;
   ck_assert_int_eq(DynMemUtilityGetValues(&dynmem, begin * element_size, end * element_size,
                                           array, length * element_size * 2, &size),
                    DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(i + 1, array[i - begin]);

   ck_assert_int_eq(size, (end - begin) * element_size);

   begin = 1;
   end = 9;
   ck_assert_int_eq(DynMemUtilityGetValues(&dynmem, begin * element_size, end * element_size,
                                           array, length * element_size * 2, &size),
                    DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(i + 1, array[i - begin]);

   ck_assert_int_eq(size, (end - begin) * element_size);

   begin = 4;
   end = 5;
   ck_assert_int_eq(DynMemUtilityGetValues(&dynmem, begin * element_size, end * element_size,
                                           array, length * element_size * 2, &size),
                    DYNMEM_SUCCEED);
   for (int i = begin; i < end; i++)
      ck_assert_int_eq(i + 1, array[i - begin]);

   ck_assert_int_eq(size, (end - begin) * element_size);

   begin = 5;
   end = 5;
   ck_assert_int_eq(DynMemUtilityGetValues(&dynmem, begin * element_size, end * element_size,
                                           array, length * element_size * 2, &size),
                    DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);
   ck_assert_int_eq(DynMemUtilityGetValues(&dynmem, 0 * element_size, 999 * element_size,
                                           array, length * element_size * 2, &size),
                    DYNMEM_FAILED);
   ck_assert_int_eq(size, 0);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);

   free(array);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemUtilityGetValues\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, test);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
