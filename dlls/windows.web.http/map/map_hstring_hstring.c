#include "map_inspectable_inspectable.h"
#include <string.h>

#define T_K_CMP_FUNC wcscmp

#define T_K_RELEASE_FUNC WindowsDeleteString
#define T_V_RELEASE_FUNC WindowsDeleteString

#define T_K_RETAIN_FUNC IInspectable_AddRef
#define T_V_RETAIN_FUNC IInspectable_AddRef

#include "map_t.c"