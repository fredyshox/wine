#define RB_DEFINE_IKEY_VALUE_PAIR(key_type, value_type, key_inspectable, value_inspectable)            \
#define IFACE_TYPE IKeyValuePair_##key_type##_##value_type
#define STRUCT_TYPE key_value_container_##key_type##_##value_type##_t 

#define (key_type, value_type, key_inspectable, value_inspectable, iface_type, struct_type)
struct struct_type
{
    iface_type iface_type##_iface;
    struct rb_entry entry;
    key_type key;
    value_type value;
};

DEFINE_IINSPECTABLE(struct_type, iface_type, struct struct_type, iface_type##_iface)

static HRESULT WINAPI struct_type##_get_Key( iface_type* iface, key_type* key ) 
{
    struct struct_type *impl = impl_from_##iface_type(iface);
#if key_inspectable
    IInspectable_AddRef((*key = impl->key));
#endif
    return S_OK;
}
static HRESULT WINAPI struct_type##_get_Value( iface_type* iface, value_type* value ) 
{
    struct struct_type *impl = impl_from_##iface_type(iface);
#if value_inspectable
    IInspectable_AddRef((*value = impl->value));
#endif
    return S_OK;
}

#define RB_DEFINE_IKEY_VALUE_PAIR_ITERATOR(key_type, value_type, key_inspectable, value_inspectable)            \
#define PAIR_IFACE_TYPE IFACE_TYPE IKeyValuePair_##key_type##_##value_type
#define PAIR_STRUCT_TYPE key_value_container_##key_type##_##value_type##_t 
#define IFACE_TYPE IIterator_IKeyValuePair_##key_type##_##value_type
#define STRUCT_TYPE key_value_container_iterator_##key_type##_##value_type##_t 
struct STRUCT_TYPE
{
    IFACE_TYPE IFACE_TYPE##_iface;
    LONG ref;

    IMapView map_view;
    struct rb_entry* current;
}

static HRESULT WINAPI key_value_container_iterator_get_Current( IFACE_TYPE* iface, PAIR_IFACE_TYPE* value )
{
    struct STRUCT_TYPE *impl = impl_from_##IFACE_TYPE(iface);

    if (!impl->current)
        value = NULL;
    
    IInspectable_AddRef(
        (*value = RB_ENTRY_VALUE(impl->current, struct PAIR_STRUCT_TYPE, entry)->PAIR_IFACE_TYPE##_iface)
    );
    return S_OK;
}

static HRESULT WINAPI key_value_container_iterator_get_HasCurrent( IFACE_TYPE* iface, BOOLEAN* value )
{
    struct STRUCT_TYPE *impl = impl_from_##IFACE_TYPE(iface);

    *value = impl->current != NULL;
    return S_OK;
}

static HRESULT WINAPI key_value_container_iterator_MoveNext( IFACE_TYPE* iface, BOOLEAN* value )
{
    struct STRUCT_TYPE *impl = impl_from_##IFACE_TYPE(iface);
    
    if (!impl->current)
        return E_BOUNDS;

    impl->current = rb_next(impl->current);

    return S_OK;
}

static HRESULT WINAPI key_value_container_iterator_GetMany( IFACE_TYPE* iface, UINT32 items_size, PAIR_IFACE_TYPE* items, UINT32* value )
{
    struct STRUCT_TYPE *impl = impl_from_##IFACE_TYPE(iface);
    // should i allocate memory for that?
    *value = 0;
    for (UINT32 i = 0; i < items_size; i++) {
        if (!impl->current)
            break;
        
        IInspectable_AddRef(
            (*(items + i) = RB_ENTRY_VALUE(impl->current, struct PAIR_STRUCT_TYPE, entry)->PAIR_IFACE_TYPE##_iface) 
        );
        *value += 1;

        impl->current = rb_next(impl->current);
    }
    
    return S_OK;
}

#define RB_DEFINE_IMAP_IINSPECTABLE(key_type, value_type, impl_type, impl_from, tree_field, container_type, container_key_field, container_value_field, container_entry_field)

static HRESULT WINAPI name_container_type_get_Key( IKeyValuePair* iface, key_type* key ) 
{
    impl_type *impl = impl_from_IKeyValuePair(iface);
    IInspectable_AddRef((*key = impl->key));
    return S_OK;
}

static HRESULT WINAPI name_container_type_get_Value( IKeyValuePair* iface, value_type* value ) 
{
    impl_type *impl = impl_from_IKeyValuePair(iface);
    IInspectable_AddRef((*value = impl->value));
    return S_OK;
}

static HRESULT WINAPI name_First(IIterable_IKeyValuePair_##key_type##_##value_type* iface, IIterator_IKeyValuePair_##key_type##_##value_type *iterator) 
{
    struct key_value_container_iterator_##key_type##_##value_type##_t *impl;

    *iterator = NULL;

    if (!(impl = calloc(1, sizeof(*impl)))) return E_OUTOFMEMORY;

    //impl->IFACE_TYPE
    impl->ref = 1; 
    impl->
}

static HRESULT WINAPI name_GetView(IMap_##key_type##_ ##value_type* iface, IMapView_##key_type##_ ##value_type** value) 
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI name_HasKey(IMap_##key_type##_ ##value_type* iface, key_type key, BOOLEAN* value ) 
{
    impl_type *impl;
    struct rb_tree* tree;
    struct rb_entry* found_entry;

    impl = impl_from(iface);
    tree = impl->##tree_field;

    found_entry = rb_get(tree, key);
    *value = found_entry != NULL;

    return S_OK;
}

static HRESULT WINAPI name_Insert(IMap_##key_type* iface, key_type key, value_type value) 
{
    container_type* new_container;
    impl_type *impl;
    struct rb_tree* tree;
    int res;

    impl = impl_from(iface);
    tree = impl->##tree_field;

    new_container = malloc(sizeof(container_type))
    if (!new_container) {
        return E_OUTOFMEMORY;
    }

    new_container->##container_key_field = key;
    new_container->##container_value_field = vlaue;
    res = rb_put(tree, key, &container->##container_entry_field);
    if (res != 0) {
        return E_FAIL;
    }

    IInspectable_AddRef(key);
    IInspectable_AddRef(value);

    return S_OK;
}

static HRESULT WINAPI name_Lookup(IMap_##key_type* iface, key_type key, value_type* value) 
{
    container_type* found_container;
    impl_type *impl;
    struct rb_tree* tree;
    struct rb_entry* found_entry;

    impl = impl_from(iface);
    tree = impl->##tree_field;

    *value = NULL;
    found_entry = rb_get(tree, key);
    if (!found_entry)
        return E_BOUNDS;

    found_container = RB_ENTRY_VALUE(found_entry, container_type, container_entry_field)

    IInspectable_AddRef( (*value = found_container->##container_value_field) );
    return S_OK;
}

static HRESULT WINAPI name_Remove(IMap_##key_type* iface, key_type key) 
{
    container_type* found_container;
    impl_type *impl;
    struct rb_tree* tree;
    struct rb_entry* found_entry;

    impl = impl_from(iface);
    tree = impl->##tree_field;

    found_entry = rb_get(tree, key);
    if (!found_entry)
        return S_OK;

    rb_remove(tree, found_entry);
    found_container = RB_ENTRY_VALUE(found_entry, container_type, container_entry_field);
    IInspectable_Release(found_container->##container_key_field);
    IInspectable_Release(found_container->##container_value_field);
    free(found_container);
    
    return S_OK;
}

static void name_delete_traverse_func(struct rb_entry* entry, void* context)
{
    container_type* found_container;

    found_container = RB_ENTRY_VALUE(entry, container_type, container_entry_field);
    IInspectable_Release(found_container->##container_key_field);
    IInspectable_Release(found_container->##container_value_field);
    free(found_container);
}

static HRESULT WINAPI name_Clear(IMap_##key_type* iface, key_type key) 
{
    impl_type *impl;
    struct rb_tree* tree;

    impl = impl_from(iface);
    tree = impl->##tree_field;

    rb_destroy(tree, name_delete_traverse_func, NULL);

    return S_OK;
}
