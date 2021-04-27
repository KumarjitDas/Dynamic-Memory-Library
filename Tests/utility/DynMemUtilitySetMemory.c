#ifndef DYNMEM_INTERNAL_USE_utility_defines_h
#   define DYNMEM_INTERNAL_USE_utility_defines_h
#endif
#include "utility/defines.h"

#ifndef DYNMEM_INTERNAL_USE_utility_utility_h
#   define DYNMEM_INTERNAL_USE_utility_utility_h
#endif
#include "utility/utility.h"

int main() {
    int result = 1;
    int start, end;


    int16_t value16   = 0;
    int16_t array16[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    value16 = 420;
    DynMemUtilitySetMemory(array16, sizeof(array16), &value16, sizeof(value16));
    for (int i = 0; i < sizeof(array16) / sizeof(*array16); i++)
        result &= array16[i] == value16;

    if (!result) return 1;

    value16 = 123;
    DynMemUtilitySetMemory(array16 + 0, sizeof(value16), &value16, sizeof(value16));
    result &= array16[0] == value16;

    value16 = 456;
    DynMemUtilitySetMemory(array16 + 4, sizeof(value16), &value16, sizeof(value16));
    result &= array16[4] == value16;

    value16 = 789;
    DynMemUtilitySetMemory(array16 + 9, sizeof(value16), &value16, sizeof(value16));
    result &= array16[9] == value16;

    if (!result) return 1;


    start = 0; end = 5; value16 = 111;
    DynMemUtilitySetMemory(array16 + start, sizeof(value16) * (end - start), &value16, sizeof(value16));
    for (int i = start; i < end; i++)
        result &= array16[i] == value16;

    if (!result) return 1;


    start = 2; end = 7; value16 = 222;
    DynMemUtilitySetMemory(array16 + start, sizeof(value16) * (end - start), &value16, sizeof(value16));
    for (int i = start; i < end; i++)
        result &= array16[i] == value16;

    if (!result) return 1;


    start = 5; end = 10; value16 = 333;
    DynMemUtilitySetMemory(array16 + start, sizeof(value16) * (end - start), &value16, sizeof(value16));
    for (int i = start; i < end; i++)
        result &= array16[i] == value16;

    if (!result) return 1;


    int32_t value32 = 0;
    int32_t array32[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    value32 = 42069;
    DynMemUtilitySetMemory(array32, sizeof(array32), &value32, sizeof(value32));
    for (int i = 0; i < sizeof(array32) / sizeof(*array32); i++)
        result &= array32[i] == value32;

    if (!result) return 1;


    value32 = 123456;
    DynMemUtilitySetMemory(array32 + 0, sizeof(value32), &value32, sizeof(value32));
    result &= array32[0] == value32;

    value32 = 789123;
    DynMemUtilitySetMemory(array32 + 4, sizeof(value32), &value32, sizeof(value32));
    result &= array32[4] == value32;

    value32 = 456789;
    DynMemUtilitySetMemory(array32 + 9, sizeof(value32), &value32, sizeof(value32));
    result &= array32[9] == value32;

    if (!result) return 1;


    start = 0; end = 5; value32 = 444;
    DynMemUtilitySetMemory(array32 + start, sizeof(value32) * (end - start), &value32, sizeof(value32));
    for (int i = start; i < end; i++)
        result &= array32[i] == value32;

    if (!result) return 1;


    start = 2; end = 7; value32 = 555;
    DynMemUtilitySetMemory(array32 + start, sizeof(value32) * (end - start), &value32, sizeof(value32));
    for (int i = start; i < end; i++)
        result &= array32[i] == value32;

    if (!result) return 1;


    start = 5; end = 10; value32 = 666;
    DynMemUtilitySetMemory(array32 + start, sizeof(value32) * (end - start), &value32, sizeof(value32));
    for (int i = start; i < end; i++)
        result &= array32[i] == value32;

    return !result;
}
