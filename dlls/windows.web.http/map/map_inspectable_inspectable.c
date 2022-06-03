#include "map_inspectable_inspectable.h"

#define T_K_CMP_FUNC map_compare_func_pointer_eq

#define T_K_RELEASE_FUNC IInspectable_Release
#define T_V_RELEASE_FUNC IInspectable_Release

#define T_K_RETAIN_FUNC IInspectable_AddRef
#define T_V_RETAIN_FUNC IInspectable_AddRef

#include "map_t.c"