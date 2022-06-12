#if defined(T_K) && \
    defined(T_V) && \
    defined(T_K_CMP_FUNC)

#include "map_t.h"
#include "private.h"
#include "wine/rbtree.h"
#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(winrt_coll);

#ifndef PT_K
#define PT_K T_K
#endif

#ifndef PT_V
#define PT_V T_V
#endif

#ifdef T_K_RETAIN_FUNC
#define T_K_RETAIN_IF_NEEDED(in, out) T_K_RETAIN_FUNC(in, out)
#else
#define T_K_RETAIN_IF_NEEDED *out = in
#endif

#ifdef T_V_RETAIN_FUNC
#define T_V_RETAIN_IF_NEEDED(in, out) T_V_RETAIN_FUNC(in, out)
#else
#define T_V_RETAIN_IF_NEEDED *out = in
#endif

#ifdef T_K_RELEASE_FUNC
#define T_K_RELEASE_IF_NEEDED(value) T_K_RELEASE_FUNC(value)
#else
#define T_K_RELEASE_IF_NEEDED(value)
#endif

#ifdef T_V_RELEASE_FUNC
#define T_V_RELEASE_IF_NEEDED(value) T_V_RELEASE_FUNC(value)
#else
#define T_V_RELEASE_IF_NEEDED(value)
#endif

/**
* Forward declarations
*/

#define KEY_VALUE_CONTAINER_T TEMPLATE2(key_value_container, T_K, T_V)
#define IKEYVALUEPAIR_TK_TV TEMPLATE2(IKeyValuePair, T_K, T_V)
#define IID_IKEYVALUEPAIR_TK_TV DEFINE_IID(IKEYVALUEPAIR_TK_TV)
#define VTBL_IKEYVALUEPAIR_TK_TV DEFINE_VTBL(IKEYVALUEPAIR_TK_TV)
#define impl_from_IKEYVALUEPAIR_TK_TV TEMPLATE(impl_from, IKEYVALUEPAIR_TK_TV)

#define KEY_VALUE_CONTAINER_ITERATOR_T TEMPLATE2(key_value_container_iterator, T_K, T_V)
#define IITERATOR_IKEYVALUEPAIR_TK_TV TEMPLATE2(IIterator_IKeyValuePair, T_K, T_V)
#define IID_IITERATOR_IKEYVALUEPAIR_TK_TV DEFINE_IID(IITERATOR_IKEYVALUEPAIR_TK_TV)
#define VTBL_ITERATOR_IKEYVALUEPAIR_TK_TV DEFINE_VTBL(IITERATOR_IKEYVALUEPAIR_TK_TV)
#define impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV TEMPLATE(impl_from, IITERATOR_IKEYVALUEPAIR_TK_TV)

#define MAP_T TEMPLATE2(map, T_K, T_V)
#define IID_IMAP_TK_TV DEFINE_IID(IMAP_TK_TV)
#define VTBL_IMAP_TK_TV DEFINE_VTBL(IMAP_TK_TV)
#define impl_from_IMAP_TK_TV TEMPLATE(impl_from, IMAP_TK_TV)

#define IMAPVIEW_TK_TV TEMPLATE2(IMapView, T_K, T_V)
#define IID_IMAPVIEW_TK_TV DEFINE_IID(IMAPVIEW_TK_TV)
#define VTBL_IMAPVIEW_TK_TV DEFINE_VTBL(IMAPVIEW_TK_TV)
#define impl_from_IMAPVIEW_TK_TV TEMPLATE(impl_from, IMAPVIEW_TK_TV)

#define IID_IITERABLE_IKEYVALUEPAIR_TK_TV DEFINE_IID(IITERABLE_IKEYVALUEPAIR_TK_TV)
#define VTBL_IITERABLE_IKEYVALUEPAIR_TK_TV DEFINE_VTBL(IITERABLE_IKEYVALUEPAIR_TK_TV)
#define impl_from_IITERABLE_IKEYVALUEPAIR_TK_TV TEMPLATE(impl_from, IITERABLE_IKEYVALUEPAIR_TK_TV)

static const struct VTBL_IKEYVALUEPAIR_TK_TV key_value_container_vtbl;
static const struct VTBL_ITERATOR_IKEYVALUEPAIR_TK_TV key_value_container_iterator_vtbl;
static const struct VTBL_IMAP_TK_TV map_vtbl;
static const struct VTBL_IITERABLE_IKEYVALUEPAIR_TK_TV map_iterable_vtbl;
static const struct VTBL_IMAPVIEW_TK_TV map_view_vtbl;

static HRESULT WINAPI map_Lookup(IMAP_TK_TV* iface, PT_K key, PT_V* value);
static HRESULT WINAPI map_get_Size( IMAP_TK_TV* iface, UINT32* value );
static HRESULT WINAPI map_HasKey( IMAP_TK_TV* iface, PT_K key, BOOLEAN* value);
static HRESULT WINAPI map_GetView(IMAP_TK_TV* iface, IMAPVIEW_TK_TV** value);
static HRESULT WINAPI map_Insert(IMAP_TK_TV* iface, PT_K key, PT_V value, BOOLEAN* replaced);
static HRESULT WINAPI map_Remove(IMAP_TK_TV* iface, PT_K key);
static HRESULT WINAPI map_Clear(IMAP_TK_TV* iface);

/**
* KeyValueContainer
*/

struct KEY_VALUE_CONTAINER_T
{
    IKEYVALUEPAIR_TK_TV IKeyValuePair_iface;
    LONG ref;

    struct rb_entry entry;
    PT_K key;
    PT_V value;
};

static inline struct KEY_VALUE_CONTAINER_T* impl_from_IKEYVALUEPAIR_TK_TV(IKEYVALUEPAIR_TK_TV *iface) 
{
    return CONTAINING_RECORD( iface, struct KEY_VALUE_CONTAINER_T, IKeyValuePair_iface );
}

static HRESULT WINAPI key_value_container_QueryInterface( IKEYVALUEPAIR_TK_TV *iface, REFIID iid, void **out )
{
    struct KEY_VALUE_CONTAINER_T *impl = impl_from_IKEYVALUEPAIR_TK_TV(iface);

    TRACE("iface %p, iid %s, out %p.\n", iface, debugstr_guid(iid), out);

    if (IsEqualGUID(iid, &IID_IUnknown) ||
        IsEqualGUID(iid, &IID_IInspectable) ||
        IsEqualGUID(iid, &IID_IAgileObject) ||
        IsEqualGUID(iid, &IID_IKEYVALUEPAIR_TK_TV))
    {
        IInspectable_AddRef((*out = &impl->IKeyValuePair_iface));
        return S_OK;
    }

    WARN("%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid(iid));
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI key_value_container_AddRef( IKEYVALUEPAIR_TK_TV *iface )
{
    struct KEY_VALUE_CONTAINER_T *impl = impl_from_IKEYVALUEPAIR_TK_TV(iface);
    ULONG ref = InterlockedIncrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);
    return ref;
}

static ULONG WINAPI key_value_container_Release( IKEYVALUEPAIR_TK_TV *iface )
{
    struct KEY_VALUE_CONTAINER_T *impl = impl_from_IKEYVALUEPAIR_TK_TV(iface);

    ULONG ref = InterlockedDecrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);

    if (!ref)
    {
        T_K_RELEASE_IF_NEEDED(impl->key);
        T_V_RELEASE_IF_NEEDED(impl->value);
        
        free(impl);
    }

    return ref;
}

static HRESULT WINAPI key_value_container_GetIids( IKEYVALUEPAIR_TK_TV *iface, ULONG *iid_count, IID **iids )
{
    FIXME("iface %p, iid_count %p, iids %p stub!\n", iface, iid_count, iids);
    return E_NOTIMPL;
}

static HRESULT WINAPI key_value_container_GetRuntimeClassName( IKEYVALUEPAIR_TK_TV *iface, HSTRING *class_name )
{
    FIXME("iface %p, class_name %p stub!\n", iface, class_name);
    return E_NOTIMPL;
}

static HRESULT WINAPI key_value_container_GetTrustLevel( IKEYVALUEPAIR_TK_TV *iface, TrustLevel *trust_level )
{
    FIXME("iface %p, trust_level %p stub!\n", iface, trust_level);
    return E_NOTIMPL;
}

static HRESULT WINAPI key_value_container_get_Key( IKEYVALUEPAIR_TK_TV* iface, PT_K* key ) 
{
    struct KEY_VALUE_CONTAINER_T *impl = impl_from_IKEYVALUEPAIR_TK_TV(iface);
    T_K_RETAIN_IF_NEEDED(impl->key, key);

    return S_OK;
}
static HRESULT WINAPI key_value_container_get_Value( IKEYVALUEPAIR_TK_TV* iface, PT_V* value ) 
{
    struct KEY_VALUE_CONTAINER_T *impl = impl_from_IKEYVALUEPAIR_TK_TV(iface);
    T_V_RETAIN_IF_NEEDED(impl->value, value);

    return S_OK;
}

static const struct VTBL_IKEYVALUEPAIR_TK_TV key_value_container_vtbl =
{
    /* IUnknown methods */
    key_value_container_QueryInterface,
    key_value_container_AddRef,
    key_value_container_Release,
    /* IInspectable methods */
    key_value_container_GetIids,
    key_value_container_GetRuntimeClassName,
    key_value_container_GetTrustLevel,
    /* IKeyValuePair_TK_TV */
    key_value_container_get_Key,
    key_value_container_get_Value
};

/**
* KeyValueContainerIterator
*/

struct KEY_VALUE_CONTAINER_ITERATOR_T
{
    IITERATOR_IKEYVALUEPAIR_TK_TV IIterator_IKeyValuePair_iface;
    LONG ref;

    IMAP_TK_TV* map;
    struct rb_entry* current;
};

static inline struct KEY_VALUE_CONTAINER_ITERATOR_T* impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV(IITERATOR_IKEYVALUEPAIR_TK_TV *iface) 
{
    return CONTAINING_RECORD( iface, struct KEY_VALUE_CONTAINER_ITERATOR_T, IIterator_IKeyValuePair_iface );
}

static HRESULT WINAPI key_value_container_iterator_QueryInterface( IITERATOR_IKEYVALUEPAIR_TK_TV *iface, REFIID iid, void **out )
{
    struct KEY_VALUE_CONTAINER_ITERATOR_T *impl = impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV(iface);

    TRACE("iface %p, iid %s, out %p.\n", iface, debugstr_guid(iid), out);

    if (IsEqualGUID(iid, &IID_IUnknown) ||
        IsEqualGUID(iid, &IID_IInspectable) ||
        IsEqualGUID(iid, &IID_IAgileObject) ||
        IsEqualGUID(iid, &IID_IITERATOR_IKEYVALUEPAIR_TK_TV))
    {
        IInspectable_AddRef((*out = &impl->IIterator_IKeyValuePair_iface));
        return S_OK;
    }

    WARN("%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid(iid));
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI key_value_container_iterator_AddRef( IITERATOR_IKEYVALUEPAIR_TK_TV *iface )
{
    struct KEY_VALUE_CONTAINER_ITERATOR_T *impl = impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV(iface);
    ULONG ref = InterlockedIncrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);
    return ref;
}

static ULONG WINAPI key_value_container_iterator_Release( IITERATOR_IKEYVALUEPAIR_TK_TV *iface )
{
    struct KEY_VALUE_CONTAINER_ITERATOR_T *impl = impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV(iface);

    ULONG ref = InterlockedDecrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);

    if (!ref)
    {
        if (impl->map)
            IInspectable_Release((IInspectable*) impl->map);
        free(impl);
    }

    return ref;
}

static HRESULT WINAPI key_value_container_iterator_GetIids( IITERATOR_IKEYVALUEPAIR_TK_TV *iface, ULONG *iid_count, IID **iids )
{
    FIXME("iface %p, iid_count %p, iids %p stub!\n", iface, iid_count, iids);
    return E_NOTIMPL;
}

static HRESULT WINAPI key_value_container_iterator_GetRuntimeClassName( IITERATOR_IKEYVALUEPAIR_TK_TV *iface, HSTRING *class_name )
{
    FIXME("iface %p, class_name %p stub!\n", iface, class_name);
    return E_NOTIMPL;
}

static HRESULT WINAPI key_value_container_iterator_GetTrustLevel( IITERATOR_IKEYVALUEPAIR_TK_TV *iface, TrustLevel *trust_level )
{
    FIXME("iface %p, trust_level %p stub!\n", iface, trust_level);
    return E_NOTIMPL;
}

static HRESULT WINAPI key_value_container_iterator_get_Current( IITERATOR_IKEYVALUEPAIR_TK_TV* iface, IKEYVALUEPAIR_TK_TV** value )
{
    struct KEY_VALUE_CONTAINER_ITERATOR_T *impl = impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV(iface);

    if (!impl->current)
        value = NULL;
    else 
        IInspectable_AddRef(
            (IInspectable*)
            (*value = &RB_ENTRY_VALUE(impl->current, struct KEY_VALUE_CONTAINER_T, entry)->IKeyValuePair_iface)
        );
    return S_OK;
}

static HRESULT WINAPI key_value_container_iterator_get_HasCurrent( IITERATOR_IKEYVALUEPAIR_TK_TV* iface, BOOL* value )
{
    struct KEY_VALUE_CONTAINER_ITERATOR_T *impl = impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV(iface);

    *value = impl->current != NULL;
    return S_OK;
}

static HRESULT WINAPI key_value_container_iterator_MoveNext( IITERATOR_IKEYVALUEPAIR_TK_TV* iface, BOOL* value )
{
    struct KEY_VALUE_CONTAINER_ITERATOR_T *impl = impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV(iface);
    
    if (!impl->current)
        return E_BOUNDS;

    impl->current = rb_next(impl->current);
    *value = impl->current != NULL;
    return S_OK;
}

static HRESULT WINAPI key_value_container_iterator_GetMany( IITERATOR_IKEYVALUEPAIR_TK_TV* iface, UINT32 items_size, IKEYVALUEPAIR_TK_TV** items, UINT32* value )
{
    struct KEY_VALUE_CONTAINER_ITERATOR_T *impl = impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV(iface);
    // should i allocate memory for that?
    *value = 0;
    for (UINT32 i = 0; i < items_size; i++) {
        if (!impl->current)
            break;
        
        IInspectable_AddRef(
            (IInspectable*)
            (*(items + i) = &RB_ENTRY_VALUE(impl->current, struct KEY_VALUE_CONTAINER_T, entry)->IKeyValuePair_iface) 
        );
        *value += 1;

        impl->current = rb_next(impl->current);
    }
    
    return S_OK;
}

static const struct VTBL_ITERATOR_IKEYVALUEPAIR_TK_TV key_value_container_iterator_vtbl =
{
    /* IUnknown methods */
    key_value_container_iterator_QueryInterface,
    key_value_container_iterator_AddRef,
    key_value_container_iterator_Release,
    /* IInspectable methods */
    key_value_container_iterator_GetIids,
    key_value_container_iterator_GetRuntimeClassName,
    key_value_container_iterator_GetTrustLevel,
    /* IIterator_IKeyValuePair_TK_TV */
    key_value_container_iterator_get_Current,
    key_value_container_iterator_get_HasCurrent,
    key_value_container_iterator_MoveNext,
    key_value_container_iterator_GetMany
};

/**
* Map
*/

struct MAP_T 
{
    IMAP_TK_TV IMap_iface;
    IITERABLE_IKEYVALUEPAIR_TK_TV IIterable_IKeyValuePair_iface;
    IMAPVIEW_TK_TV IMapView_iface;
    LONG ref;

    struct rb_tree tree;
};

static inline struct MAP_T* impl_from_IMAP_TK_TV(IMAP_TK_TV *iface) 
{
    return CONTAINING_RECORD( iface, struct MAP_T, IMap_iface );
}

static HRESULT WINAPI map_QueryInterface( IMAP_TK_TV *iface, REFIID iid, void **out )
{
    struct MAP_T *impl = impl_from_IMAP_TK_TV(iface);

    TRACE("iface %p, iid %s, out %p.\n", iface, debugstr_guid(iid), out);

    if (IsEqualGUID(iid, &IID_IUnknown) ||
        IsEqualGUID(iid, &IID_IInspectable) ||
        IsEqualGUID(iid, &IID_IAgileObject) ||
        IsEqualGUID(iid, &IID_IMAP_TK_TV))
    {
        IInspectable_AddRef((*out = &impl->IMap_iface));
        return S_OK;
    }

    if (IsEqualGUID(iid, &IID_IITERABLE_IKEYVALUEPAIR_TK_TV))
    {
        IInspectable_AddRef((*out = &impl->IIterable_IKeyValuePair_iface));
        return S_OK;
    }

    if (IsEqualGUID(iid, &IID_IMAPVIEW_TK_TV))
    {
        IInspectable_AddRef((*out = &impl->IMapView_iface));
        return S_OK;
    }

    WARN("%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid(iid));
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI map_AddRef( IMAP_TK_TV *iface )
{
    struct MAP_T *impl = impl_from_IMAP_TK_TV(iface);
    ULONG ref = InterlockedIncrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);
    return ref;
}

static ULONG WINAPI map_Release( IMAP_TK_TV *iface )
{
    struct MAP_T *impl = impl_from_IMAP_TK_TV(iface);

    ULONG ref = InterlockedDecrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);

    if (!ref)
    {
        map_Clear(iface);
        free(impl);
    }

    return ref;
}

static HRESULT WINAPI map_GetIids( IMAP_TK_TV *iface, ULONG *iid_count, IID **iids )
{
    FIXME("iface %p, iid_count %p, iids %p stub!\n", iface, iid_count, iids);
    return E_NOTIMPL;
}

static HRESULT WINAPI map_GetRuntimeClassName( IMAP_TK_TV *iface, HSTRING *class_name )
{
    FIXME("iface %p, class_name %p stub!\n", iface, class_name);
    return E_NOTIMPL;
}

static HRESULT WINAPI map_GetTrustLevel( IMAP_TK_TV *iface, TrustLevel *trust_level )
{
    FIXME("iface %p, trust_level %p stub!\n", iface, trust_level);
    return E_NOTIMPL;
}

static HRESULT WINAPI map_Lookup(IMAP_TK_TV* iface, PT_K key, PT_V* value) 
{
    struct KEY_VALUE_CONTAINER_T* found_container;
    struct MAP_T *impl;
    struct rb_tree* tree;
    struct rb_entry* found_entry;

    impl = impl_from_IMAP_TK_TV(iface);
    tree = &impl->tree;

    *value = NULL;
    found_entry = rb_get(tree, key);
    if (!found_entry)
        return E_BOUNDS;

    found_container = RB_ENTRY_VALUE(found_entry, struct KEY_VALUE_CONTAINER_T, entry);
    T_V_RETAIN_IF_NEEDED(found_container->value, value);

    return S_OK;
}

static HRESULT WINAPI map_get_Size( IMAP_TK_TV* iface, UINT32* value ) 
{
    struct MAP_T *impl;
    struct rb_tree* tree;
    struct rb_entry* cursor;

    impl = impl_from_IMAP_TK_TV(iface);
    tree = &impl->tree;

    *value = 0;
    RB_FOR_EACH(cursor, tree) {
        *value += 1;
    }

    return S_OK;
} 

static HRESULT WINAPI map_HasKey( IMAP_TK_TV* iface, PT_K key, BOOLEAN* value)
{
    struct MAP_T *impl;
    struct rb_tree* tree;
    struct rb_entry* found_entry;

    impl = impl_from_IMAP_TK_TV(iface);
    tree = &impl->tree;

    found_entry = rb_get(tree, key);
    *value = found_entry != NULL;

    return S_OK;
}

static HRESULT WINAPI map_GetView(IMAP_TK_TV* iface, IMAPVIEW_TK_TV** value) 
{
    struct MAP_T* impl;
    struct MAP_T* view;
    struct rb_tree* tree;
    struct rb_entry* cursor;
    struct KEY_VALUE_CONTAINER_T* cursor_container;
    struct KEY_VALUE_CONTAINER_T* copy_container;

    impl = impl_from_IMAP_TK_TV(iface);
    tree = &impl->tree;

    if (!(view = calloc( 1, sizeof(struct MAP_T) ))) return E_OUTOFMEMORY;

    view->IMap_iface.lpVtbl = &map_vtbl;
    view->IIterable_IKeyValuePair_iface.lpVtbl = &map_iterable_vtbl;
    view->IMapView_iface.lpVtbl = &map_view_vtbl;
    view->ref = 1;
    rb_init(&view->tree, tree->compare);

    RB_FOR_EACH(cursor, tree) {
        cursor_container = RB_ENTRY_VALUE(cursor, struct KEY_VALUE_CONTAINER_T, entry);
        copy_container = malloc(sizeof(struct KEY_VALUE_CONTAINER_T));
        *copy_container = *cursor_container;
        T_K_RETAIN_IF_NEEDED(cursor_container->key, &copy_container->key);
        T_V_RETAIN_IF_NEEDED(cursor_container->value, &copy_container->value);

        rb_put(&view->tree, cursor_container->key, &copy_container->entry);
    }

    *value = &view->IMapView_iface;

    return S_OK;
}

static HRESULT WINAPI map_Insert(IMAP_TK_TV* iface, PT_K key, PT_V value, BOOLEAN* replaced) 
{
    struct KEY_VALUE_CONTAINER_T* new_container;
    struct MAP_T *impl;
    struct rb_tree* tree;
    struct rb_entry* existing_entry;
    int res;

    impl = impl_from_IMAP_TK_TV(iface);
    tree = &impl->tree;

    existing_entry = rb_get(tree, key);
    if (existing_entry != NULL) {
        new_container = RB_ENTRY_VALUE(existing_entry, struct KEY_VALUE_CONTAINER_T, entry);
        *replaced = (BOOLEAN) true;

        T_V_RETAIN_IF_NEEDED(value, &new_container->value);
    } else {
        new_container = malloc(sizeof(struct KEY_VALUE_CONTAINER_T));
        *replaced = (BOOLEAN) false; 

        if (!new_container)
            return E_OUTOFMEMORY;

        res = rb_put(tree, key, &new_container->entry);
        if (res != 0) {
            free(new_container);
            return E_FAIL;
        }

        new_container->IKeyValuePair_iface.lpVtbl = &key_value_container_vtbl;
        new_container->ref = 1;

        T_K_RETAIN_IF_NEEDED(key, &new_container->key);
        T_V_RETAIN_IF_NEEDED(value, &new_container->value);
    }

    return S_OK;
}

static HRESULT WINAPI map_Remove(IMAP_TK_TV* iface, PT_K key) 
{
    struct KEY_VALUE_CONTAINER_T* found_container;
    struct MAP_T *impl;
    struct rb_tree* tree;
    struct rb_entry* found_entry;
    
    impl = impl_from_IMAP_TK_TV(iface);
    tree = &impl->tree;

    found_entry = rb_get(tree, key);
    if (!found_entry)
        return S_OK;

    rb_remove(tree, found_entry);
    found_container = RB_ENTRY_VALUE(found_entry, struct KEY_VALUE_CONTAINER_T, entry);
    T_K_RELEASE_IF_NEEDED(found_container->key);
    T_V_RELEASE_IF_NEEDED(found_container->value);
    free(found_container);
    
    return S_OK;
}

static void map_delete_traverse_func(struct rb_entry* entry, void* context)
{
    struct KEY_VALUE_CONTAINER_T* found_container;

    found_container = RB_ENTRY_VALUE(entry, struct KEY_VALUE_CONTAINER_T, entry);
    T_K_RELEASE_IF_NEEDED(found_container->key);
    T_V_RELEASE_IF_NEEDED(found_container->value);
    free(found_container);
}

static HRESULT WINAPI map_Clear(IMAP_TK_TV* iface) 
{
    struct MAP_T *impl;
    struct rb_tree* tree;

    impl = impl_from_IMAP_TK_TV(iface);
    tree = &impl->tree;

    rb_destroy(tree, map_delete_traverse_func, NULL);

    return S_OK;
}

static const struct VTBL_IMAP_TK_TV map_vtbl =
{
    /* IUnknown methods */
    map_QueryInterface,
    map_AddRef,
    map_Release,
    /* IInspectable methods */
    map_GetIids,
    map_GetRuntimeClassName,
    map_GetTrustLevel,
    /* IMap_TK_TV */
    map_Lookup,
    map_get_Size,
    map_HasKey,
    map_GetView,
    map_Insert,
    map_Remove,
    map_Clear
};

/**
* IIterable_KeyValuePair_TK_TV
*/

DEFINE_IINSPECTABLE_T(map_iterable, IITERABLE_IKEYVALUEPAIR_TK_TV, IIterable_IKeyValuePair_iface, struct MAP_T, impl_from_IITERABLE_IKEYVALUEPAIR_TK_TV, IMap_iface)

static HRESULT WINAPI map_iterable_First(IITERABLE_IKEYVALUEPAIR_TK_TV* iface, IITERATOR_IKEYVALUEPAIR_TK_TV** iterator) 
{
    struct MAP_T* impl;
    struct KEY_VALUE_CONTAINER_ITERATOR_T *new_iterator;

    impl = impl_from_IITERABLE_IKEYVALUEPAIR_TK_TV(iface);
    *iterator = NULL;

    if (!(new_iterator = calloc(1, sizeof(struct KEY_VALUE_CONTAINER_ITERATOR_T)))) return E_OUTOFMEMORY;

    new_iterator->IIterator_IKeyValuePair_iface.lpVtbl = &key_value_container_iterator_vtbl;
    new_iterator->map = &impl->IMap_iface;
    new_iterator->current = rb_head(impl->tree.root);
    new_iterator->ref = 1; 

    IInspectable_AddRef((IInspectable*) &impl->IMap_iface);

    *iterator = &new_iterator->IIterator_IKeyValuePair_iface;
    return S_OK;
}

static const struct VTBL_IITERABLE_IKEYVALUEPAIR_TK_TV map_iterable_vtbl =
{
    /* IUnknown methods */
    map_iterable_QueryInterface,
    map_iterable_AddRef,
    map_iterable_Release,
    /* IInspectable methods */
    map_iterable_GetIids,
    map_iterable_GetRuntimeClassName,
    map_iterable_GetTrustLevel,
    /* IIterable_IKeyValuePair_TK_TV */
    map_iterable_First
};

/**
* IMapView_TK_TV
*/

DEFINE_IINSPECTABLE_T(map_view, IMAPVIEW_TK_TV, IMapView_iface, struct MAP_T, impl_from_IMAPVIEW_TK_TV, IMap_iface)

static HRESULT WINAPI map_view_Lookup( IMAPVIEW_TK_TV* iface, PT_K key, PT_V* value ) 
{
    struct MAP_T *impl;
    impl = impl_from_IMAPVIEW_TK_TV(iface);
    return map_Lookup(&impl->IMap_iface, key, value);
}

static HRESULT WINAPI map_view_get_Size( IMAPVIEW_TK_TV* iface, UINT32* value ) 
{
    struct MAP_T *impl;
    impl = impl_from_IMAPVIEW_TK_TV(iface);
    return map_get_Size(&impl->IMap_iface, value);
} 

static HRESULT WINAPI map_view_HasKey( IMAPVIEW_TK_TV* iface, PT_K key, BOOLEAN* value ) 
{
    struct MAP_T *impl;
    impl = impl_from_IMAPVIEW_TK_TV(iface);
    return map_HasKey(&impl->IMap_iface, key, value);
}

static HRESULT WINAPI map_view_Split( IMAPVIEW_TK_TV* iface, IMAPVIEW_TK_TV** first, IMAPVIEW_TK_TV** second) 
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static const struct VTBL_IMAPVIEW_TK_TV map_view_vtbl =
{
    /* IUnknown methods */
    map_view_QueryInterface,
    map_view_AddRef,
    map_view_Release,
    /* IInspectable methods */
    map_view_GetIids,
    map_view_GetRuntimeClassName,
    map_view_GetTrustLevel,
    /* IMapView_TK_TV */
    map_view_Lookup,
    map_view_get_Size,
    map_view_HasKey,
    map_view_Split
};

/**
* Public constructor API
*/

static int rbtree_map_cmp_func(const void* key, const struct rb_entry* entry) 
{
    return T_K_CMP_FUNC(key, RB_ENTRY_VALUE(entry, struct KEY_VALUE_CONTAINER_T, entry)->key);
}

HRESULT TEMPLATE2(rbtree_map_create, T_K, T_V)(IMAP_TK_TV** map,  IITERABLE_IKEYVALUEPAIR_TK_TV** iterable) 
{
    struct MAP_T *map;

    *value = NULL;

    if (!(map = calloc(1, sizeof(struct MAP_T)))) return E_OUTOFMEMORY;

    map->IMap_iface.lpVtbl = &map_vtbl;
    map->IIterable_IKeyValuePair_iface.lpVtbl = &map_iterable_vtbl;
    map->IMapView_iface.lpVtbl = &map_view_vtbl;
    map->ref = 1;
    
    rb_init(&map->tree, rbtree_map_cmp_func);

    *map = &map->IMap_iface;
    if (iterable)
        *iterable = &map->IIterable_IKeyValuePair_iface;

    return S_OK;
}

#else
#error "Missing definitions"
#endif