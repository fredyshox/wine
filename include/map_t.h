#if !defined(T_K) || !defined(T_V)
#error "Missing T_K and T_V definitions"
#endif

#include "templates.h"

#define IMAP_TK_TV TEMPLATE2(IMap, T_K, T_V)
#define IITERABLE_IKEYVALUEPAIR_TK_TV TEMPLATE3(IIterable, IKeyValuePair, T_K, T_V)

HRESULT TEMPLATE2(rbtree_map_create, T_K, T_V)(IMAP_TK_TV** map, IITERABLE_IKEYVALUEPAIR_TK_TV** iterable);

#define DEFINE_IMAP_CONFORMANCE(pfx, impl_type, key_type, value_type, impl_from, iface_field)             \
static HRESULT WINAPI pfx##_Lookup(iface_type *iface, key_type key, value_type value)                     \
{                                                                                                         \
    impl_type *impl = impl_from(iface);
    return TEMPLATE2(IMap, key_type, value_type)##_Lookup(impl->iface_field, key, value);
}
static HRESULT WINAPI pfx##_get_Size(iface_type *iface, UINT32* value) 
{
    impl_type *impl = impl_from(iface);
    return TEMPLATE2(IMap, key_type, value_type)##_get_Size(impl->iface_field, value);
}
static HRESULT WINAPI pfx##_HasKey(iface_type *iface, key_type key, BOOLEAN* value) 
{
    impl_type *impl = impl_from(iface);
    return TEMPLATE2(IMap, key_type, value_type)##_HasKey(impl->iface_field, key, value);
}
static HRESULT WINAPI pfx##_GetView(iface_type *iface, TEMPLATE2(IMapView, key_type, value_type)** value) 
{
    impl_type *impl = impl_from(iface);
    return TEMPLATE2(IMap, key_type, value_type)##_GetView(impl->iface_field, value);
}
static HRESULT WINAPI pfx##_Insert(iface_type *iface, key_type key, value_type value, BOOLEAN* replaced) 
{
    impl_type *impl = impl_from(iface);
    return TEMPLATE2(IMap, key_type, value_type)##_Insert(impl->iface_field, key, value, replaced);
}
static HRESULT WINAPI pfx##_Remove(iface_type *iface, key_type key) 
{
    impl_type *impl = impl_from(iface);
    return TEMPLATE2(IMap, key_type, value_type)##_Remove(impl->iface_field, key);
}
static HRESULT WINAPI pfx##_Clear(iface_type *iface) 
{
    impl_type *impl = impl_from(iface);
    return TEMPLATE2(IMap, key_type, value_type)##_Clear(impl->iface_field);
}

#define DEFINE_IITERABLE_TK_TV_CONFORMANCE(pfx, impl_type, impl_from, iface_type, iface_field)    \ 
static HRESULT WINAPI pfx##_First(iface_type *iface, iface_type* value)                                                           \
{                                                                                                                                 \                                                                                            \
    impl_type *impl = impl_from(iface);                                                                                           \
    return iface_type##_First(value);
}