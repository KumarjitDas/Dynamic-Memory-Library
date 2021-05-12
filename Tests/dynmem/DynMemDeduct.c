#include "check.h"
#include "dynmem/dynmem.h"

START_TEST(null_dynmem) {
   int value;
   ck_assert_int_eq(DynMemDeduct(NULL, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeduct(NULL, &value), DYNMEM_FAILED);
}
END_TEST

START_TEST(nonnull_dynmem__no_value_added) {
   dynmem_t dynmem;
   int value;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeduct(&dynmem, &value), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__appended__size_not_changed__null_value) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 3; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   intmax_t index = 28;

   for (int i = 0; i < 3; i++) {
      index -= 4;
      ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_SUCCEED);
      ck_assert_int_eq(dynmem.ei, index);
   }

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__appended__extended_size__null_value) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   intmax_t index = 56;

   for (int i = 0; i < 10; i++) {
      index -= 4;
      ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_SUCCEED);
      ck_assert_int_eq(dynmem.ei, index);
   }

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__appended__more_extended_size__null_value) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   intmax_t index = 96;

   for (int i = 0; i < 20; i++) {
      index -= 4;
      ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_SUCCEED);
      ck_assert_int_eq(dynmem.ei, index);
   }

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__appended__size_not_changed__nonnull_value) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 3; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   for (int i = 2; i >= 0; i--) {
      int value;
      ck_assert_int_eq(DynMemDeduct(&dynmem, &value), DYNMEM_SUCCEED);
      ck_assert_int_eq(value, i);
   }

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__appended__extended_size__nonnull_value) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   for (int i = 9; i >= 0; i--) {
      int value;
      ck_assert_int_eq(DynMemDeduct(&dynmem, &value), DYNMEM_SUCCEED);
      ck_assert_int_eq(value, i);
   }

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__appended__more_extended_size__nonnull_value) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   for (int i = 19; i >= 0; i--) {
      int value;
      ck_assert_int_eq(DynMemDeduct(&dynmem, &value), DYNMEM_SUCCEED);
      ck_assert_int_eq(value, i);
   }

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__prepended__size_not_changed__null_value) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 3; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   intmax_t index = 16;

   for (int i = 0; i < 3; i++) {
      ck_assert_int_eq(dynmem.ei, index);
      ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_SUCCEED);
      index -= 4;
   }

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__prepended__extended_size__null_value) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   intmax_t index = 56;

   for (int i = 0; i < 10; i++) {
      ck_assert_int_eq(dynmem.ei, index);
      ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_SUCCEED);
      index -= 4;
   }

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__prepended__more_extended_size__null_value) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   intmax_t index = 136;

   for (int i = 0; i < 20; i++) {
      index -= 4;
      ck_assert_int_eq(DynMemDeduct(&dynmem, NULL), DYNMEM_SUCCEED);
      ck_assert_int_eq(dynmem.ei, index);
   }

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__prepended__size_not_changed__nonnull_value) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 3; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   for (int i = 0; i < 3; i++) {
      int value;
      ck_assert_int_eq(DynMemDeduct(&dynmem, &value), DYNMEM_SUCCEED);
      ck_assert_int_eq(value, i);
   }

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__prepended__extended_size__nonnull_value) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   for (int i = 0; i < 10; i++) {
      int value;
      ck_assert_int_eq(DynMemDeduct(&dynmem, &value), DYNMEM_SUCCEED);
      ck_assert_int_eq(value, i);
   }

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(nonnull_dynmem__prepended__more_extended_size__nonnull_value) {
   dynmem_t dynmem;
   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   for (int i = 0; i < 20; i++) {
      int value;
      ck_assert_int_eq(DynMemDeduct(&dynmem, &value), DYNMEM_SUCCEED);
      ck_assert_int_eq(value, i);
   }

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemDeduct\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_dynmem);
   tcase_add_test(test_cases, nonnull_dynmem__no_value_added);
   tcase_add_test(test_cases, nonnull_dynmem__appended__size_not_changed__null_value);
   tcase_add_test(test_cases, nonnull_dynmem__appended__extended_size__null_value);
   tcase_add_test(test_cases, nonnull_dynmem__appended__more_extended_size__null_value);
   tcase_add_test(test_cases, nonnull_dynmem__appended__size_not_changed__nonnull_value);
   tcase_add_test(test_cases, nonnull_dynmem__appended__extended_size__nonnull_value);
   tcase_add_test(test_cases, nonnull_dynmem__appended__more_extended_size__nonnull_value);
   tcase_add_test(test_cases, nonnull_dynmem__prepended__size_not_changed__null_value);
   tcase_add_test(test_cases, nonnull_dynmem__prepended__extended_size__null_value);
   tcase_add_test(test_cases, nonnull_dynmem__prepended__more_extended_size__null_value);
   tcase_add_test(test_cases, nonnull_dynmem__prepended__size_not_changed__nonnull_value);
   tcase_add_test(test_cases, nonnull_dynmem__prepended__extended_size__nonnull_value);
   tcase_add_test(test_cases, nonnull_dynmem__prepended__more_extended_size__nonnull_value);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
