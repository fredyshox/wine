struct key_value_container_t
{
    IKeyValuePair_IInspectable_IInspectable IKeyValuePair_IInspectable_IInspectable_iface;
    struct rb_entry entry;
    IInspectable* key;
    IInspectable* value;
};

DEFINE_IINSPECTABLE(key_value_container, IKeyValuePair_IInspectable_IInspectable, struct key_value_container_t, IKeyValuePair_IInspectable_IInspectable_iface)

static HRESULT WINAPI key_value_container_get_Key( IKeyValuePair_IInspectable_IInspectable* iface, IInspectable** key ) 
{
    struct key_value_container_t *impl = impl_from_IKeyValuePair_IInspectable_IInspectable(iface);
    IInspectable_AddRef((*key = impl->key));
    return S_OK;
}
static HRESULT WINAPI key_value_container_get_Value( IKeyValuePair_IInspectable_IInspectable* iface, IInspectable** value ) 
{
    struct key_value_container_t *impl = impl_from_IKeyValuePair_IInspectable_IInspectable(iface);
    IInspectable_AddRef((*value = impl->value));
    return S_OK;
}

struct key_value_container_iterator_t
{
    IIterator_IKeyValuePair_IInspectable_IInspectable IIterator_IKeyValuePair_IInspectable_IInspectable_iface;
    LONG ref;

    IMapView map_view;
    struct rb_entry* current;
}

DEFINE_IINSPECTABLE(key_value_container_iterator, IIterator_IKeyValuePair_IInspectable_IInspectable, struct key_value_container_iterator_t, IIterator_IKeyValuePair_IInspectable_IInspectable_iface)

static HRESULT WINAPI key_value_container_iterator_get_Current( IIterator_IKeyValuePair_IInspectable_IInspectable* iface, IKeyValuePair_IInspectable_IInspectable* value )
{
    struct key_value_container_iterator_t *impl = impl_from_IIterator_IKeyValuePair_IInspectable_IInspectable(iface);

    if (!impl->current)
        value = NULL;
    
    IInspectable_AddRef(
        (*value = RB_ENTRY_VALUE(impl->current, struct PAIR_key_value_container_iterator_t, entry)->IKeyValuePair_IInspectable_IInspectable_iface)
    );
    return S_OK;
}

static HRESULT WINAPI key_value_container_iterator_get_HasCurrent( IIterator_IKeyValuePair_IInspectable_IInspectable* iface, BOOLEAN* value )
{
    struct key_value_container_iterator_t *impl = impl_from_IIterator_IKeyValuePair_IInspectable_IInspectable(iface);

    *value = impl->current != NULL;
    return S_OK;
}

static HRESULT WINAPI key_value_container_iterator_MoveNext( IIterator_IKeyValuePair_IInspectable_IInspectable* iface, BOOLEAN* value )
{
    struct key_value_container_iterator_t *impl = impl_from_IIterator_IKeyValuePair_IInspectable_IInspectable(iface);
    
    if (!impl->current)
        return E_BOUNDS;

    impl->current = rb_next(impl->current);

    return S_OK;
}

static HRESULT WINAPI key_value_container_iterator_GetMany( IIterator_IKeyValuePair_IInspectable_IInspectable* iface, UINT32 items_size, IKeyValuePair_IInspectable_IInspectable* items, UINT32* value )
{
    struct key_value_container_iterator_t *impl = impl_from_IIterator_IKeyValuePair_IInspectable_IInspectable(iface);
    // should i allocate memory for that?
    *value = 0;
    for (UINT32 i = 0; i < items_size; i++) {
        if (!impl->current)
            break;
        
        IInspectable_AddRef(
            (*(items + i) = RB_ENTRY_VALUE(impl->current, struct key_value_container_t, entry)->IKeyValuePair_IInspectable_IInspectable_iface##_iface) 
        );
        *value += 1;

        impl->current = rb_next(impl->current);
    }
    
    return S_OK;
}

struct map {
    IMap_IInspectable_IInspectable* IMap_IInspectable_IInspectable_iface;
    IIterable_IKeyValuePair_IInspectable_IInspectable* IIterable_IKeyValuePair_IInspectable_IInspectable_iface;
    IMapView_IInspectable_IInspectable* IMapView_IInspectable_IInspectable_iface;

    struct rb_tree tree;
}

DEFINE_IINSPECTABLE(map, IMap_IInspectable_IInspectable, struct map, IMap_IInspectable_IInspectable_iface)

static HRESULT WINAPI map_GetView(IMap_IInspectable_IInspectable* iface, IMapView_IInspectable_IInspectable** value) 
{
    struct map *impl;
    struct map* view;
    struct rb_tree* tree;
    struct rb_entry* cursor;
    struct key_value_container_t* cursor_container;
    struct key_value_container_t* copy_container;

    impl = impl_from_IMap_IInspectable_IInspectable(iface);
    tree = impl->tree;

    if (!(view = calloc( 1, sizeof(struct map) ))) return E_OUTOFMEMORY;

    view->IMap_IInspectable_IInspectable_iface.lpVtbl = ;
    view->IIterable_IKeyValuePair_IInspectable_IInspectable_iface.lpVtbl = ;
    view->IMapView_IInspectable_IInspectable_iface.lpVtbl = ;
    view->ref = 1;
    rb_init(view->tree, tree->compare);

    RB_FOR_EACH(cursor, tree) {
        cursor_container = RB_ENTRY_VALUE(cursor, struct key_value_container_t, entry);
        copy_container = malloc(sizeof(struct key_value_container_t));
        *copy_container = *cursor_container;
        rb_put(view->tree, cursor_container->key, &copy_container->entry);
        IInspectable_AddRef(cursor_container->key);
        IInspectable_AddRef(cursor_container->value);
    }

    *value = &view->IMapView_IInspectable_IInspectable_iface;

    return S_OK;
}


static HRESULT WINAPI map_get_Size( IMap_IInspectable_IInspectable* iface, UINT32* value ) 
{
    struct map *impl;
    struct rb_tree* tree;
    struct rb_entry* cursor;

    impl = impl_from_IMap_IInspectable_IInspectable(iface);
    tree = impl->tree;

    *value = 0;
    RB_FOR_EACH(cursor, tree) {
        *value += 1;
    }

    return S_OK;
} 

static HRESULT WINAPI map_HasKey( IMap_IInspectable_IInspectable* iface, IInspectable* key, BOOLEAN* value ) 
{
    struct map *impl;
    struct rb_tree* tree;
    struct rb_entry* found_entry;

    impl = impl_from_IMap_IInspectable_IInspectable(iface);
    tree = impl->tree;

    found_entry = rb_get(tree, key);
    *value = found_entry != NULL;

    return S_OK;
}

static HRESULT WINAPI map_Insert(IMap_IInspectable_IInspectable* iface, IInspectable* key, IInspectable* value) 
{
    struct key_value_container_t* new_container;
    struct map *impl;
    struct rb_tree* tree;
    int res;

    impl = impl_from_IMap_IInspectable_IInspectable(iface);
    tree = impl->tree;

    new_container = malloc(sizeof(container_type))
    if (!new_container) {
        return E_OUTOFMEMORY;
    }

    new_container-key = key;
    new_container->value = vlaue;
    res = rb_put(tree, key, &container->entry);
    if (res != 0) {
        free(new_container);
        return E_FAIL;
    }

    IInspectable_AddRef(key);
    IInspectable_AddRef(value);

    return S_OK;
}

static HRESULT WINAPI map_Lookup(IMap_IInspectable_IInspectable* iface, IInspectable* key, IInspectable* value) 
{
    struct key_value_container_t* found_container;
    struct map *impl;
    struct rb_tree* tree;
    struct rb_entry* found_entry;

    impl = impl_from_IMap_IInspectable_IInspectable(iface);
    tree = impl->tree;

    *value = NULL;
    found_entry = rb_get(tree, key);
    if (!found_entry)
        return E_BOUNDS;

    found_container = RB_ENTRY_VALUE(found_entry, struct key_value_container_t, entry);

    IInspectable_AddRef( (*value = found_container->value) );
    return S_OK;
}

static HRESULT WINAPI map_Remove(IMap_IInspectable_IInspectable* iface, IInspectable* key) 
{
    struct key_value_container_t* found_container;
    struct map *impl;
    struct rb_tree* tree;
    struct rb_entry* found_entry;
    
    impl = impl_from_IMap_IInspectable_IInspectable(iface);
    tree = impl->tree;

    found_entry = rb_get(tree, key);
    if (!found_entry)
        return S_OK;

    rb_remove(tree, found_entry);
    found_container = RB_ENTRY_VALUE(found_entry, struct key_value_container_t, entry);
    IInspectable_Release(found_container->key);
    IInspectable_Release(found_container->value);
    free(found_container);
    
    return S_OK;
}

static void map_delete_traverse_func(struct rb_entry* entry, void* context)
{
    struct key_value_container_t* found_container;

    found_container = RB_ENTRY_VALUE(entry, struct key_value_container_t, entry);
    IInspectable_Release(found_container->key);
    IInspectable_Release(found_container->value);
    free(found_container);
}

static HRESULT WINAPI amp_Clear(IMap_IInspectable_IInspectable* iface, IInspectable* key) 
{
    struct key_value_container_t *impl;
    struct rb_tree* tree;

    impl = impl_from_IMap_IInspectable_IInspectable(iface);
    tree = impl->tree;

    rb_destroy(tree, name_delete_traverse_func, NULL);

    return S_OK;
}

DEFINE_IINSPECTABLE(map_iterable, IIterable_IKeyValuePair_IInspectable_IInspectable, struct map, IIterable_IKeyValuePair_IInspectable_IInspectable_iface)

static HRESULT WINAPI map_iterable_First(IIterable_IKeyValuePair_IInspectable_IInspectable* iface, IIterator_IKeyValuePair_IInspectable_IInspectable *iterator) 
{
    struct key_value_container_iterator_t *impl;

    *iterator = NULL;

    if (!(impl = calloc(1, sizeof(*impl)))) return E_OUTOFMEMORY;

    impl-IIterator_IKeyValuePair_IInspectable_IInspectable_iface.lpVtbl = ;//TODO
    impl->ref = 1; 
    impl->map_view = ;
    impl->current = ;

    *iterator = &impl->IIterator_IKeyValuePair_IInspectable_IInspectable;
    return S_OK;
}

DEFINE_IINSPECTABLE(map_view, IMapView_IInspectable_IInspectable, struct map, IMapView_IInspectable_IInspectable_iface)

static HRESULT WINAPI map_view_get_Size( IMapView_IInspectable_IInspectable* iface, UINT32* value ) 
{
    struct map *impl;
    impl = impl_from_IMapView_IInspectable_IInspectable(iface);
    return map_get_Size(impl->IMap_IInspectable_IInspectable_iface, value);
} 

static HRESULT WINAPI map_view_HasKey( IMapView_IInspectable_IInspectable* iface, IInspectable* key, BOOLEAN* value ) 
{
    struct map *impl;
    impl = impl_from_IMapView_IInspectable_IInspectable(iface);
    return map_view_HasKey(impl->IMap_IInspectable_IInspectable_iface, key, value);
}

static HRESULT WINAPI map_view_Lookup( IMapView_IInspectable_IInspectable* iface, IInspectable* key, IInspectable* value ) 
{
    struct map *impl;
    impl = impl_from_IMapView_IInspectable_IInspectable(iface);
    return map_view_Lookup(impl->IMap_IInspectable_IInspectable_iface, key, value);
}

static HRESULT WINAPI map_view_Split( IMapView_IInspectable_IInspectable* iface, IMapView_IInspectable_IInspectable** first, IMapView_IInspectable_IInspectable** second) 
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}