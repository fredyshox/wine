#include "private.h"
#include "map_inspectable_inspectable.h"

#define _INSPECTABLE_ADD_REF(invalue, outvalue) \
    do { \
        IInspectable_AddRef((IInspectable*) (*outvalue = invalue)); \
    } while (0)

int iinspectable_compare_func(const void* a, const void* b) 
{
    return a == b;
}

#define T_K_CMP_FUNC iinspectable_compare_func

#define T_K_RELEASE_FUNC(value) IInspectable_Release((IInspectable*) value)
#define T_V_RELEASE_FUNC(value) IInspectable_Release((IInspectable*) value)

#define T_K_RETAIN_FUNC(in, out) _INSPECTABLE_ADD_REF(in, out)
#define T_V_RETAIN_FUNC(in, out) _INSPECTABLE_ADD_REF(in, out)

#define PT_K T_K*
#define PT_V T_V*

#include "impl/map_t.c"