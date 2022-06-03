#if defined(T_K) && defined(T_V) && defined(T_K_INSPECTABLE) && defined(T_V_INSPECTABLE)

#include "templates.h"

#if T_K_INSPECTABLE
#define PT_K T_K*
#else
#define PT_K T_K
#endif

#if T_V_INSPECTABLE
#define PT_V T_V*
#else
#define PT_V T_V
#endif

#define KEY_VALUE_CONTAINER_T TEMPLATE2(key_value_container, T_K, T_V)
#define IKEYVALUEPAIR_TK_TV TEMPLATE2(IKeyValuePair, T_K, T_V)
#define IID_IKEYVALUEPAIR_TK_TV IID_##IKEYVALUEPAIR_TK_TV
#define impl_from_IKEYVALUEPAIR_TK_TV impl_from_##IKEYVALUEPAIR_TK_TV

struct KEY_VALUE_CONTAINER_T
{
    IKEYVALUEPAIR_TK_TV IKeyValuePair_iface;
    struct rb_entry entry;
    PT_K key;
    PT_V value;
};

static inline struct KEY_VALUE_CONTAINER_T impl_from_IKEYVALUEPAIR_TK_TV(IKEYVALUEPAIR_TK_TV *iface) 
{
    return CONTAINING_RECORD( iface, struct KEY_VALUE_CONTAINER_T, IKeyValuePair_iface );
}

static HRESULT WINAPI key_value_container_QueryInterface( IITERATOR_IKEYVALUEPAIR_TK_TV *iface, REFIID iid, void **out )
{
    struct KEY_VALUE_CONTAINER_T *impl = impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV(iface);

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

static ULONG WINAPI key_value_container_AddRef( IITERATOR_IKEYVALUEPAIR_TK_TV *iface )
{
    struct KEY_VALUE_CONTAINER_T *impl = impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV(iface);
    ULONG ref = InterlockedIncrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);
    return ref;
}

static ULONG WINAPI key_value_container_Release( IITERATOR_IKEYVALUEPAIR_TK_TV *iface )
{
    struct KEY_VALUE_CONTAINER_T *impl = impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV(iface);

    ULONG ref = InterlockedDecrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);

    if (!ref)
    {
        if (impl->key)
            IInspectable_Release(impl->key);
        if (impl->value)
            IInspectable_Release(impl->value);
        free(impl);
    }

    return ref;
}

static HRESULT WINAPI key_value_container_GetIids( IITERATOR_IKEYVALUEPAIR_TK_TV *iface, ULONG *iid_count, IID **iids )
{
    FIXME("iface %p, iid_count %p, iids %p stub!\n", iface, iid_count, iids);
    return E_NOTIMPL;
}

static HRESULT WINAPI key_value_container_GetRuntimeClassName( IITERATOR_IKEYVALUEPAIR_TK_TV *iface, HSTRING *class_name )
{
    FIXME("iface %p, class_name %p stub!\n", iface, class_name);
    return E_NOTIMPL;
}

static HRESULT WINAPI key_value_container_GetTrustLevel( IITERATOR_IKEYVALUEPAIR_TK_TV *iface, TrustLevel *trust_level )
{
    FIXME("iface %p, trust_level %p stub!\n", iface, trust_level);
    return E_NOTIMPL;
}

static HRESULT WINAPI key_value_container_get_Key( IKeyValuePair_IInspectable_IInspectable* iface, PT_K* key ) 
{
    struct KEY_VALUE_CONTAINER_T *impl = impl_from_IKEYVALUEPAIR_TK_TV(iface);
#if T_K_INSPECTABLE
    IInspectable_AddRef((*key = impl->key));
#endif
    return S_OK;
}
static HRESULT WINAPI key_value_container_get_Value( IKeyValuePair_IInspectable_IInspectable* iface, PT_V* value ) 
{
    struct KEY_VALUE_CONTAINER_T *impl = impl_from_IKEYVALUEPAIR_TK_TV(iface);
#if T_V_INSPECTABLE
    IInspectable_AddRef((*value = impl->value));
#endif
    return S_OK;
}

#define KEY_VALUE_CONTAINER_ITERATOR_T TEMPLATE2(key_value_container_iterator, T_K, T_V)
#define IITERATOR_IKEYVALUEPAIR_TK_TV TEMPLATE2(IIterator_IKeyValuePair, T_K, T_V)
#define IID_IITERATOR_IKEYVALUEPAIR_TK_TV IID_##IITERATOR_IKEYVALUEPAIR_TK_TV
#define impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV impl_from_##IITERATOR_IKEYVALUEPAIR_TK_TV

struct KEY_VALUE_CONTAINER_ITERATOR_T
{
    IITERATOR_IKEYVALUEPAIR_TK_TV IIterator_IKeyValuePair_iface;
    LONG ref;

    IMap* map;
    struct rb_entry* current;
}

static inline struct KEY_VALUE_CONTAINER_ITERATOR_T impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV(IITERATOR_IKEYVALUEPAIR_TK_TV *iface) 
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
        if (impl->map_view)
            IInspectable_Release(impl->map_view);
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

static HRESULT WINAPI key_value_container_iterator_get_Current( IITERATOR_IKEYVALUEPAIR_TK_TV* iface, IKEYVALUEPAIR_TK_TV* value )
{
    struct KEY_VALUE_CONTAINER_ITERATOR_T *impl = impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV(iface);

    if (!impl->current)
        value = NULL;
#if T_V_INSPECTABLE   
    IInspectable_AddRef(
        (*value = RB_ENTRY_VALUE(impl->current, struct KEY_VALUE_CONTAINER_ITERATOR_T, entry)->IIterator_IKeyValuePair_iface)
    );
#endif
    return S_OK;
}

static HRESULT WINAPI key_value_container_iterator_get_HasCurrent( IITERATOR_IKEYVALUEPAIR_TK_TV* iface, BOOLEAN* value )
{
    struct KEY_VALUE_CONTAINER_ITERATOR_T *impl = impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV(iface);

    *value = impl->current != NULL;
    return S_OK;
}

static HRESULT WINAPI key_value_container_iterator_MoveNext( IITERATOR_IKEYVALUEPAIR_TK_TV* iface, BOOLEAN* value )
{
    struct KEY_VALUE_CONTAINER_ITERATOR_T *impl = impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV(iface);
    
    if (!impl->current)
        return E_BOUNDS;

    impl->current = rb_next(impl->current);

    return S_OK;
}

static HRESULT WINAPI key_value_container_iterator_GetMany( IITERATOR_IKEYVALUEPAIR_TK_TV* iface, UINT32 items_size, IKEYVALUEPAIR_TK_TV* items, UINT32* value )
{
    struct KEY_VALUE_CONTAINER_ITERATOR_T *impl = impl_from_IITERATOR_IKEYVALUEPAIR_TK_TV(iface);
    // should i allocate memory for that?
    *value = 0;
    for (UINT32 i = 0; i < items_size; i++) {
        if (!impl->current)
            break;
        
        IInspectable_AddRef(
            (*(items + i) = RB_ENTRY_VALUE(impl->current, struct KEY_VALUE_CONTAINER_T, entry)->IKeyValuePair_iface) 
        );
        *value += 1;

        impl->current = rb_next(impl->current);
    }
    
    return S_OK;
}

#define MAP_T TEMPLATE2(map, T_K, T_V)
#define IMAP_TK_TV TEMPLATE2(IMap, T_K, T_V)
#define IMAPVIEW_TK_TV TEMPLATE2(IMapView, T_K, T_V)
#define IITERABLE_IKEYVALUEPAIR_TK_TV TEMPLATE3(IIterable, IKeyValuePair, T_K, T_V)
#define IID_IMAP_TK_TV IID_##IMAP_TK_TV
#define IID_IMAPVIEW_TK_TV IID_##IMAPVIEW_TK_TV
#define IID_IITERABLE_IKEYVALUEPAIR_TK_TV IID_##IITERABLE_IKEYVALUEPAIR_TK_TV
#define impl_from_IMAP_TK_TV impl_from_##IMAP_TK_TV

struct MAP_T 
{
    IMAP_TK_TV IMap_iface;
    IITERABLE_IKEYVALUEPAIR_TK_TV IIterable_IKeyValuePair_iface;
    IMAPVIEW_TK_TV IMapView_iface;

    struct rb_tree tree;
}

static inline struct MAP_T impl_from_IMAP_TK_TV(IMAP_TK_TV *iface) 
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
    struct uri *impl = impl_from_IMAP_TK_TV(iface);
    ULONG ref = InterlockedIncrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);
    return ref;
}

static ULONG WINAPI map_Release( IMAP_TK_TV *iface )
{
    struct uri *impl = impl_from_IMAP_TK_TV(iface);

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

static HRESULT WINAPI map_GetView(IMAP_TK_TV* iface, IMAPVIEW_TK_TV** value) 
{
    struct MAP_T* impl;
    struct MAP_T* view;
    struct rb_tree* tree;
    struct rb_entry* cursor;
    struct KEY_VALUE_CONTAINER_T* cursor_container;
    struct KEY_VALUE_CONTAINER_T* copy_container;

    impl = impl_from_IMAP_TK_TV(iface);
    tree = impl->tree;

    if (!(view = calloc( 1, sizeof(struct MAP_T) ))) return E_OUTOFMEMORY;

    view->IMap_iface.lpVtbl = ; // TODO
    view->IIterable_IKeyValuePair_iface.lpVtbl = ; // TODO
    view->IMapView_iface.lpVtbl = ; // TODO
    view->ref = 1;
    rb_init(view->tree, tree->compare);

    RB_FOR_EACH(cursor, tree) {
        cursor_container = RB_ENTRY_VALUE(cursor, struct KEY_VALUE_CONTAINER_T, entry);
        copy_container = malloc(sizeof(struct KEY_VALUE_CONTAINER_T));
        *copy_container = *cursor_container;
        rb_put(view->tree, cursor_container->key, &copy_container->entry);
#if T_K_INSPECTABLE
        IInspectable_AddRef(cursor_container->key);
#endif
#if T_V_INSPECTABLE
        IInspectable_AddRef(cursor_container->value);
#endif
    }

    *value = &view->IMapView_iface;

    return S_OK;
}

static HRESULT WINAPI map_get_Size( IMAP_TK_TV* iface, UINT32* value ) 
{
    struct MAP_T *impl;
    struct rb_tree* tree;
    struct rb_entry* cursor;

    impl = impl_from_IMAP_TK_TV(iface);
    tree = impl->tree;

    *value = 0;
    RB_FOR_EACH(cursor, tree) {
        *value += 1;
    }

    return S_OK;
} 

static HRESULT WINAPI map_HasKey( IMAP_TK_TV* iface, T_K* key, BOOLEAN* value ) 
{
    struct MAP_T *impl;
    struct rb_tree* tree;
    struct rb_entry* found_entry;

    impl = impl_from_IMAP_TK_TV(iface);
    tree = impl->tree;

    found_entry = rb_get(tree, key);
    *value = found_entry != NULL;

    return S_OK;
}

static HRESULT WINAPI map_Insert(IMAP_TK_TV* iface, PT_K key, PT_V value) 
{
    struct KEY_VALUE_CONTAINER_T* new_container;
    struct MAP_T *impl;
    struct rb_tree* tree;
    int res;

    impl = impl_from_IMAP_TK_TV(iface);
    tree = impl->tree;

    new_container = malloc(sizeof(struct KEY_VALUE_CONTAINER_T))
    if (!new_container) {
        return E_OUTOFMEMORY;
    }

    res = rb_put(tree, key, &container->entry);
    if (res != 0) {
        free(new_container);
        return E_FAIL;
    }
    
#ifdef T_K_INSPECTABLE
    IInspectable_AddRef(key);
#endif
#ifdef T_V_INSPECTABLE
    IInspectable_AddRef(value);
#endif

    return S_OK;
}

static HRESULT WINAPI map_Lookup(IMAP_TK_TV* iface, PT_K key, PT_V* value) 
{
    struct KEY_VALUE_CONTAINER_T* found_container;
    struct MAP_T *impl;
    struct rb_tree* tree;
    struct rb_entry* found_entry;

    impl = impl_from_IMAP_TK_TV(iface);
    tree = impl->tree;

    *value = NULL;
    found_entry = rb_get(tree, key);
    if (!found_entry)
        return E_BOUNDS;

    found_container = RB_ENTRY_VALUE(found_entry, struct KEY_VALUE_CONTAINER_T, entry);
#ifdef T_V_INSPECTABLE
    IInspectable_AddRef( (*value = found_container->value) );
#endif

    return S_OK;
}

static HRESULT WINAPI map_Remove(IMAP_TK_TV* iface, PT_K key) 
{
    struct KEY_VALUE_CONTAINER_T* found_container;
    struct MAP_T *impl;
    struct rb_tree* tree;
    struct rb_entry* found_entry;
    
    impl = impl_from_IMAP_TK_TV(iface);
    tree = impl->tree;

    found_entry = rb_get(tree, key);
    if (!found_entry)
        return S_OK;

    rb_remove(tree, found_entry);
    found_container = RB_ENTRY_VALUE(found_entry, struct KEY_VALUE_CONTAINER_T, entry);
#ifdef T_K_INSPECTABLE
    IInspectable_Release(found_container->key);
#endif
#ifdef T_V_INSPECTABLE
    IInspectable_Release(found_container->value);
#endif
    free(found_container);
    
    return S_OK;
}

static void map_delete_traverse_func(struct rb_entry* entry, void* context)
{
    struct KEY_VALUE_CONTAINER_T* found_container;

    found_container = RB_ENTRY_VALUE(entry, struct KEY_VALUE_CONTAINER_T, entry);
#ifdef T_K_INSPECTABLE
    IInspectable_Release(found_container->key);
#endif
#ifdef T_V_INSPECTABLE
    IInspectable_Release(found_container->value);
#endif
    free(found_container);
}

static HRESULT WINAPI map_Clear(IMAP_TK_TV* iface) 
{
    struct MAP_T *impl;
    struct rb_tree* tree;

    impl = impl_from_IMAP_TK_TV(iface);
    tree = impl->tree;

    rb_destroy(tree, map_delete_traverse_func, NULL);

    return S_OK;
}

DEFINE_IINSPECTABLE(map_iterable, IITERABLE_IKEYVALUEPAIR_TK_TV, struct MAP_T, IMap_iface)
#define impl_from_IITERABLE_IKEYVALUEPAIR_TK_TV impl_from_##IITERABLE_IKEYVALUEPAIR_TK_TV

static HRESULT WINAPI map_iterable_First(IITERABLE_IKEYVALUEPAIR_TK_TV* iface, IITERATOR_IKEYVALUEPAIR_TK_TV* iterator) 
{
    struct MAP_T* impl;
    struct KEY_VALUE_CONTAINER_ITERATOR_T *new_iterator;

    impl = impl_from_IMAP_TK_TV(iface);
    *new_iterator = NULL;

    if (!(new_iterator = calloc(1, sizeof(struct KEY_VALUE_CONTAINER_ITERATOR_T)))) return E_OUTOFMEMORY;

    new_iterator->IIterator_IKeyValuePair_iface.lpVtbl = ;//TODO
    new_iterator->ref = 1; 
    new_iterator->map = &impl->IMap_iface;
    new_iterator->current = impl->tree.root;

    *iterator = &new_iterator->IIterator_IKeyValuePair_iface;
    return S_OK;
}

DEFINE_IINSPECTABLE(map_view, IMAPVIEW_TK_TV, struct MAP_T, IMap_iface)
#define impl_from_IMAPVIEW_TK_TV impl_from_##IMAPVIEW_TK_TV

static HRESULT WINAPI map_view_get_Size( IMAPVIEW_TK_TV* iface, UINT32* value ) 
{
    struct MAP_T *impl;
    impl = impl_from_IMAPVIEW_TK_TV(iface);
    return map_get_Size(impl->IMap_iface, value);
} 

static HRESULT WINAPI map_view_HasKey( IMAPVIEW_TK_TV* iface, PT_K key, BOOLEAN* value ) 
{
    struct MAP_T *impl;
    impl = impl_from_IMAPVIEW_TK_TV(iface);
    return map_view_HasKey(impl->IMap_iface, key, value);
}

static HRESULT WINAPI map_view_Lookup( IMAPVIEW_TK_TV* iface, PT_K key, PT_V* value ) 
{
    struct MAP_T *impl;
    impl = impl_from_IMAPVIEW_TK_TV(iface);
    return map_view_Lookup(impl->IMap_iface, key, value);
}

static HRESULT WINAPI map_view_Split( IMAPVIEW_TK_TV* iface, IMAPVIEW_TK_TV** first, IMAPVIEW_TK_TV** second) 
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static int rbtree_map_cmp_func(const void* key, const struct rb_entry* entry) 
{
    return T_K_CMP_FUNC(key, RB_ENTRY_VALUE(entry, struct KEY_VALUE_CONTAINER_T, entry)->key);
}

HRESULT TEMPLATE2(rbtree_map_create, T_K, T_V)(IMAP_TK_TV** value) 
{
    struct MAP_T *map;

    *value = NULL;

    if (!(map = calloc(1, sizeof(struct MAP_T)))) return E_OUTOFMEMORY;

    map->IMap_iface.lpVtbl = ; // TODO
    map->IIterable_IKeyValuePair_iface = ; // TODO
    map->IMapView_iface = ; // TODO
    map->ref = 1;
    
    rb_init(map->tree, rbtree_map_cmp_func) // TODO compare function

    *value = &map->IMap_iface;

    return S_OK;
}

#endif