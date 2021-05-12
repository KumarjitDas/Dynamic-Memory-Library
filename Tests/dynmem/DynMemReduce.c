#include "check.h"
#include "dynmem/dynmem.h"

#include <stdlib.h>

START_TEST(null_dynmem) {
   int *array;
   intmax_t length;

   ck_assert_int_eq(DynMemReduce(NULL, NULL, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemReduce(NULL, NULL, &length), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemReduce(NULL, &array, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(DynMemReduce(NULL, &array, &length), DYNMEM_FAILED);
}
END_TEST

START_TEST(value_not_added__null_array) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 20);
   ck_assert_int_eq(dynmem.ei, 16);
   ck_assert_ptr_nonnull(dynmem.m);
   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(appended__null_array__length_not_changed) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 6, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 3; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 48);
   ck_assert_int_eq(dynmem.bi, 16);
   ck_assert_int_eq(dynmem.ei, 24);
   ck_assert_ptr_nonnull(dynmem.m);

   int *array = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 3; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(appended__null_array__edge_length) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 8);
   ck_assert_int_eq(dynmem.ei, 24);
   ck_assert_ptr_nonnull(dynmem.m);

   int *array = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(appended__null_array__extended_length) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 8; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 4);
   ck_assert_int_eq(dynmem.ei, 32);
   ck_assert_ptr_nonnull(dynmem.m);

   int *array = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 8; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(appended__null_array__extended_length__cannot_reduce) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 12; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 80);
   ck_assert_int_eq(dynmem.bi, 16);
   ck_assert_int_eq(dynmem.ei, 60);
   ck_assert_ptr_nonnull(dynmem.m);

   int *array = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 12; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(appended__null_array__more_extended_length) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 18; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 80);
   ck_assert_int_eq(dynmem.bi, 4);
   ck_assert_int_eq(dynmem.ei, 72);
   ck_assert_ptr_nonnull(dynmem.m);

   int *array = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 18; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(appended__null_array__more_extended_length__cannot_reduce) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 24; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 160);
   ck_assert_int_eq(dynmem.bi, 32);
   ck_assert_int_eq(dynmem.ei, 124);
   ck_assert_ptr_nonnull(dynmem.m);

   int *array = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 24; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(prepended__null_array__length_not_changed) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 6, NULL), DYNMEM_SUCCEED);

   for (int i = 2; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 48);
   ck_assert_int_eq(dynmem.bi, 16);
   ck_assert_int_eq(dynmem.ei, 24);
   ck_assert_ptr_nonnull(dynmem.m);

   int *array = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 3; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(prepended__null_array__edge_length) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 4; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 8);
   ck_assert_int_eq(dynmem.ei, 24);
   ck_assert_ptr_nonnull(dynmem.m);

   int *array = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(prepended__null_array__extended_length) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 7; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 4);
   ck_assert_int_eq(dynmem.ei, 32);
   ck_assert_ptr_nonnull(dynmem.m);

   int *array = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 8; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(prepended__null_array__extended_length__cannot_reduce) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 11; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 80);
   ck_assert_int_eq(dynmem.bi, 16);
   ck_assert_int_eq(dynmem.ei, 60);
   ck_assert_ptr_nonnull(dynmem.m);

   int *array = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 12; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(prepended__null_array__more_extended_length) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 17; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 80);
   ck_assert_int_eq(dynmem.bi, 4);
   ck_assert_int_eq(dynmem.ei, 72);
   ck_assert_ptr_nonnull(dynmem.m);

   int *array = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 18; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(prepended__null_array__more_extended_length__cannot_reduce) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 23; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 160);
   ck_assert_int_eq(dynmem.bi, 32);
   ck_assert_int_eq(dynmem.ei, 124);
   ck_assert_ptr_nonnull(dynmem.m);

   int *array = (int *)(dynmem.m + dynmem.bi);

   for (int i = 0; i < 24; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(value_added__edge_to_edge__length_not_changed) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 4; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   for (int i = 5; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 40);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 36);
   ck_assert_ptr_nonnull(dynmem.m);

   int *array = (int *)(dynmem.m);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(value_added__edge_to_edge__extended_length) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 4; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   for (int i = 5; i < 20; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 80);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 76);
   ck_assert_ptr_nonnull(dynmem.m);

   int *array = (int *)(dynmem.m);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(value_added__edge_to_edge__more_extended_length) {
   dynmem_t dynmem;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 34; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   for (int i = 35; i < 40; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, NULL, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.cs, 160);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 156);
   ck_assert_ptr_nonnull(dynmem.m);

   int *array = (int *)(dynmem.m);

   for (int i = 0; i < 40; i++)
      ck_assert_int_eq(array[i], i);

   ck_assert_int_eq(DynMemDeallocate(&dynmem), DYNMEM_SUCCEED);
}
END_TEST

START_TEST(value_not_added__nonnull_array) {
   dynmem_t dynmem;
   int *array;
   intmax_t length;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemReduce(&dynmem, &array, NULL), DYNMEM_FAILED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_null(array);

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(DynMemReduce(&dynmem, &array, &length), DYNMEM_FAILED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_null(array);
   ck_assert_int_eq(length, 0);
}
END_TEST

START_TEST(appended__nonnull_array__null_length__length_not_changed) {
   dynmem_t dynmem;
   int *array;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, &array, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(appended__nonnull_array__null_length__extended_length) {
   dynmem_t dynmem;
   int *array;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, &array, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(appended__nonnull_array__null_length__more_extended_length) {
   dynmem_t dynmem;
   int *array;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, &array, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(appended__nonnull_array__nonnull_length__length_not_changed) {
   dynmem_t dynmem;
   int *array;
   intmax_t length;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, &array, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);
   ck_assert_int_eq(length, 5);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(appended__nonnull_array__nonnull_length__extended_length) {
   dynmem_t dynmem;
   int *array;
   intmax_t length;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, &array, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);
   ck_assert_int_eq(length, 10);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(appended__nonnull_array__nonnull_length__more_extended_length) {
   dynmem_t dynmem;
   int *array;
   intmax_t length;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(DynMemAppend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, &array, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);
   ck_assert_int_eq(length, 20);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(prepended__nonnull_array__null_length__length_not_changed) {
   dynmem_t dynmem;
   int *array;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 4; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, &array, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(prepended__nonnull_array__null_length__extended_length) {
   dynmem_t dynmem;
   int *array;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 9; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, &array, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(prepended__nonnull_array__null_length__more_extended_length) {
   dynmem_t dynmem;
   int *array;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 19; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, &array, NULL), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(prepended__nonnull_array__nonnull_length__length_not_changed) {
   dynmem_t dynmem;
   int *array;
   intmax_t length;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 4; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, &array, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);
   ck_assert_int_eq(length, 5);

   for (int i = 0; i < 5; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(prepended__nonnull_array__nonnull_length__extended_length) {
   dynmem_t dynmem;
   int *array;
   intmax_t length;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 9; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, &array, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);
   ck_assert_int_eq(length, 10);

   for (int i = 0; i < 10; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

START_TEST(prepended__nonnull_array__nonnull_length__more_extended_length) {
   dynmem_t dynmem;
   int *array;
   intmax_t length;

   ck_assert_int_eq(DynMemAllocate(&dynmem, 4, 5, NULL), DYNMEM_SUCCEED);

   for (int i = 19; i >= 0; i--)
      ck_assert_int_eq(DynMemPrepend(&dynmem, &i), DYNMEM_SUCCEED);

   ck_assert_int_eq(DynMemReduce(&dynmem, &array, &length), DYNMEM_SUCCEED);
   ck_assert_int_eq(dynmem.es, 0);
   ck_assert_int_eq(dynmem.is, 0);
   ck_assert_int_eq(dynmem.cs, 0);
   ck_assert_int_eq(dynmem.bi, 0);
   ck_assert_int_eq(dynmem.ei, 0);
   ck_assert_ptr_null(dynmem.m);
   ck_assert_ptr_nonnull(array);
   ck_assert_int_eq(length, 20);

   for (int i = 0; i < 20; i++)
      ck_assert_int_eq(array[i], i);

   free(array);
}
END_TEST

int main() {
   Suite *suite = suite_create("Test suite for \"DynMemReduce\" function");
   TCase *test_cases = tcase_create("Test case");

   tcase_add_test(test_cases, null_dynmem);
   tcase_add_test(test_cases, value_not_added__null_array);
   tcase_add_test(test_cases, appended__null_array__length_not_changed);
   tcase_add_test(test_cases, appended__null_array__edge_length);
   tcase_add_test(test_cases, appended__null_array__extended_length);
   tcase_add_test(test_cases, appended__null_array__extended_length__cannot_reduce);
   tcase_add_test(test_cases, appended__null_array__more_extended_length);
   tcase_add_test(test_cases, appended__null_array__more_extended_length__cannot_reduce);
   tcase_add_test(test_cases, prepended__null_array__length_not_changed);
   tcase_add_test(test_cases, prepended__null_array__edge_length);
   tcase_add_test(test_cases, prepended__null_array__extended_length);
   tcase_add_test(test_cases, prepended__null_array__extended_length__cannot_reduce);
   tcase_add_test(test_cases, prepended__null_array__more_extended_length);
   tcase_add_test(test_cases, prepended__null_array__more_extended_length__cannot_reduce);
   tcase_add_test(test_cases, value_added__edge_to_edge__length_not_changed);
   tcase_add_test(test_cases, value_added__edge_to_edge__extended_length);
   tcase_add_test(test_cases, value_added__edge_to_edge__more_extended_length);
   tcase_add_test(test_cases, value_not_added__nonnull_array);
   tcase_add_test(test_cases, appended__nonnull_array__null_length__length_not_changed);
   tcase_add_test(test_cases, appended__nonnull_array__null_length__extended_length);
   tcase_add_test(test_cases, appended__nonnull_array__null_length__more_extended_length);
   tcase_add_test(test_cases, appended__nonnull_array__nonnull_length__length_not_changed);
   tcase_add_test(test_cases, appended__nonnull_array__nonnull_length__extended_length);
   tcase_add_test(test_cases, appended__nonnull_array__nonnull_length__more_extended_length);
   tcase_add_test(test_cases, prepended__nonnull_array__null_length__length_not_changed);
   tcase_add_test(test_cases, prepended__nonnull_array__null_length__extended_length);
   tcase_add_test(test_cases, prepended__nonnull_array__null_length__more_extended_length);
   tcase_add_test(test_cases, prepended__nonnull_array__nonnull_length__length_not_changed);
   tcase_add_test(test_cases, prepended__nonnull_array__nonnull_length__extended_length);
   tcase_add_test(test_cases, prepended__nonnull_array__nonnull_length__more_extended_length);

   suite_add_tcase(suite, test_cases);

   SRunner *suite_runner = srunner_create(suite);
   srunner_run_all(suite_runner, CK_VERBOSE);

   int failed_test_case_numbers = srunner_ntests_failed(suite_runner);
   srunner_free(suite_runner);

   return failed_test_case_numbers;
}
