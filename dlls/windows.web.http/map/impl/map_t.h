#if defined(T_K) && defined(T_V)

#include "private.h"
#include "templates.h"

#define IMAP_TK_TV TEMPLATE2(IMap, T_K, T_V)

HRESULT TEMPLATE2(rbtree_map_create, T_K, T_V)(IMAP_TK_TV** value);

#endif