#include "private.h"
#include "winstring.h"
#include "map_hstring_hstring.h"
#include <string.h>

int hstring_compare_func(const void* a, const void* b) 
{
    INT32 order;
    HRESULT hres;
    hres = WindowsCompareStringOrdinal((HSTRING) a, (HSTRING) b, &order);
    if (hres != S_OK)
        return -1;

    return (int) order;
}

#define T_K_CMP_FUNC hstring_compare_func

#define T_K_RELEASE_FUNC(value) WindowsDeleteString(value)
#define T_V_RELEASE_FUNC(value) WindowsDeleteString(value)

#define T_K_RETAIN_FUNC(in, out) WindowsDuplicateString(in, out)
#define T_V_RETAIN_FUNC(in, out) WindowsDuplicateString(in, out)

#include "impl/map_t.c"