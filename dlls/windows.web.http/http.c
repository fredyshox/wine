/*
 *
 * IHttpContentHeaderCollection
 *
 */

static HRESULT WINAPI http_content_headers_get_ContentDisposition( IHttpContentHeaderCollection* iface, IHttpContentDispositionHeaderValue** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_put_ContentDisposition( IHttpContentHeaderCollection* iface, IHttpContentDispositionHeaderValue* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_get_ContentEncoding( IHttpContentHeaderCollection* iface, IHttpContentCodingHeaderValueCollection** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_get_ContentLanguage( IHttpContentHeaderCollection* iface, IHttpContentCodingHeaderValueCollection** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_get_ContentLength( IHttpContentHeaderCollection* iface, IReference_UINT64** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_put_ContentLength( IHttpContentHeaderCollection* iface, IReference_UINT64* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_get_ContentLocation( IHttpContentHeaderCollection* iface, IUriRuntimeClass** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_put_ContentLocation( IHttpContentHeaderCollection* iface, IUriRuntimeClass* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_get_ContentMD5( IHttpContentHeaderCollection* iface, IBuffer** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_put_ContentMD5( IHttpContentHeaderCollection* iface, IBuffer* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_get_ContentRange( IHttpContentHeaderCollection* iface, IHttpContentRangeHeaderValue** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_put_ContentRange( IHttpContentHeaderCollection* iface, IHttpContentRangeHeaderValue* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_get_ContentType( IHttpContentHeaderCollection* iface, IHttpMediaTypeHeaderValue** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_put_ContentType( IHttpContentHeaderCollection* iface, IHttpMediaTypeHeaderValue* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_get_Expires( IHttpContentHeaderCollection* iface, IReference_DateTime** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_put_Expires( IHttpContentHeaderCollection* iface, IReference_DateTime* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_get_LastModified( IHttpContentHeaderCollection* iface, IReference_DateTime** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_put_LastModified( IHttpContentHeaderCollection* iface, IReference_DateTime* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_Append ( IHttpContentHeaderCollection* iface, HSTRING name, HSTRING value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_headers_TryAppendWithoutValidation ( IHttpContentHeaderCollection* iface, HSTRING name, HSTRING value, BOOLEAN* result )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static const struct IHttpContentHeaderCollectionVtbl http_content_headers_vtbl =
{
    http_content_headers_QueryInterface,
    http_content_headers_AddRef,
    http_content_headers_Release,
    /* IInspectable methods */
    http_content_headers_GetIids,
    http_content_headers_GetRuntimeClassName,
    http_content_headers_GetTrustLevel,
    /* IHttpContentHeaderCollection methods */
    http_content_headers_get_ContentDisposition,
    http_content_headers_put_ContentDisposition,
    http_content_headers_get_ContentEncoding,
    http_content_headers_get_ContentLanguage,
    http_content_headers_get_ContentLength,
    http_content_headers_put_ContentLength,
    http_content_headers_get_ContentLocation,
    http_content_headers_put_ContentLocation,
    http_content_headers_get_ContentMD5,
    http_content_headers_put_ContentMD5,
    http_content_headers_get_ContentRange,
    http_content_headers_put_ContentRange,
    http_content_headers_get_ContentType,
    http_content_headers_put_ContentType,
    http_content_headers_get_Expires,
    http_content_headers_put_Expires,
    http_content_headers_get_LastModified,
    http_content_headers_put_LastModified,
    http_content_headers_Append ,
    http_content_headers_TryAppendWithoutValidation 
};


/*
 *
 * IHttpContent
 *
 */

static HRESULT WINAPI http_content_get_Headers( IHttpContent* iface, IHttpRequestHeaderCollection** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_BufferAllAsync( IHttpContent* iface, IAsyncOperationWithProgress_UINT64_UINT64** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_ReadAsBufferAsync( IHttpContent* iface, IAsyncOperationWithProgress_IBuffer_UINT64** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_ReadAsInputStreamAsync( IHttpContent* iface, IAsyncOperationWithProgress_IInputStream_UINT64** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_ReadAsStringAsync( IHttpContent* iface, IAsyncOperationWithProgress_HSTRING_UINT64** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_TryComputeLength( IHttpContent* iface, UINT64* length, BOOLEAN* succeeded )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_content_WriteToStreamAsync( IHttpContent* iface, IOutputStream* outputStream, IAsyncOperationWithProgress_UINT64_UINT64** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static const struct IHttpContentVtbl http_content_vtbl =
{
    http_content_QueryInterface,
    http_content_AddRef,
    http_content_Release,
    /* IInspectable methods */
    http_content_GetIids,
    http_content_GetRuntimeClassName,
    http_content_GetTrustLevel,
    /* IHttpContent methods */
    http_content_get_Headers,
    http_content_BufferAllAsync,
    http_content_ReadAsBufferAsync,
    http_content_ReadAsInputStreamAsync,
    http_content_ReadAsStringAsync,
    http_content_TryComputeLength,
    http_content_WriteToStreamAsync
};


/*
 *
 * IHttpConnectionOptionHeaderValueCollection
 *
 */


static HRESULT WINAPI http_header_value_connection_ParseAdd ( IHttpConnectionOptionHeaderValueCollection* iface, HSTRING input )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_header_value_connection_TryParseAdd ( IHttpConnectionOptionHeaderValueCollection* iface, HSTRING input, BOOLEAN* result )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static const struct IHttpConnectionOptionHeaderValueCollectionVtbl http_header_value_connection_vtbl =
{
    http_header_value_connection_QueryInterface,
    http_header_value_connection_AddRef,
    http_header_value_connection_Release,
    /* IInspectable methods */
    http_header_value_connection_GetIids,
    http_header_value_connection_GetRuntimeClassName,
    http_header_value_connection_GetTrustLevel,
    /* IHttpConnectionOptionHeaderValueCollection methods */
    http_header_value_connection_ParseAdd ,
    http_header_value_connection_TryParseAdd 
};


/*
 *
 * IHttpRequestMessage
 *
 */

static HRESULT WINAPI http_request_get_Content( IHttpRequestMessage* iface, IHttpContent** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_put_Content( IHttpRequestMessage* iface, IHttpContent* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_get_Headers( IHttpRequestMessage* iface, IHttpRequestHeaderCollection** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_get_Method( IHttpRequestMessage* iface, IHttpMethod** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_put_Method( IHttpRequestMessage* iface, IHttpMethod* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_get_Properties( IHttpRequestMessage* iface, IMap_HSTRING_IInspectable** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_get_RequestUri( IHttpRequestMessage* iface, IUriRuntimeClass** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_put_RequestUri( IHttpRequestMessage* iface, IUriRuntimeClass* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_get_TransportInformation( IHttpRequestMessage* iface, IHttpTransportInformation** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}


static const struct IHttpRequestMessageVtbl http_request_vtbl =
{
    http_request_QueryInterface,
    http_request_AddRef,
    http_request_Release,
    /* IInspectable methods */
    http_request_GetIids,
    http_request_GetRuntimeClassName,
    http_request_GetTrustLevel,
    /* IHttpRequestMessage methods */
    http_request_get_Content,
    http_request_put_Content,
    http_request_get_Headers,
    http_request_get_Method,
    http_request_put_Method,
    http_request_get_Properties,
    http_request_get_RequestUri,
    http_request_put_RequestUri,
    http_request_get_TransportInformation
};


/*
 *
 * IHttpClient2
 *
 */


static HRESULT WINAPI http_client2_TryDeleteAsync( IHttpClient2* iface, IUriRuntimeClass* uri, IAsyncOperationWithProgress_IHttpRequestResult_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client2_TryGetAsync( IHttpClient2* iface, IUriRuntimeClass* uri, IAsyncOperationWithProgress_IHttpRequestResult_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client2_TryGetAsync2( IHttpClient2* iface, IUriRuntimeClass* uri, HttpCompletionOption completionOption, IAsyncOperationWithProgress_IHttpRequestResult_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client2_TryGetBufferAsync( IHttpClient2* iface, IUriRuntimeClass* uri, IAsyncOperationWithProgress_IHttpGetBufferResult_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client2_TryGetInputStreamAsync( IHttpClient2* iface, IUriRuntimeClass* uri, IAsyncOperationWithProgress_IHttpGetInputStreamResult_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client2_TryGetStringAsync( IHttpClient2* iface, IUriRuntimeClass* uri, IAsyncOperationWithProgress_IHttpGetStringResult_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client2_TryPostAsync( IHttpClient2* iface, IUriRuntimeClass* uri, IHttpContent* content, IAsyncOperationWithProgress_IHttpRequestResult_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client2_TryPutAsync( IHttpClient2* iface, IUriRuntimeClass* uri, IHttpContent* content, IAsyncOperationWithProgress_WIHttpRequestResult_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client2_TrySendRequestAsync( IHttpClient2* iface, IHttpRequestMessage* request, IAsyncOperationWithProgress_IHttpRequestResult_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client2_TrySendRequestAsync2( IHttpClient2* iface, IHttpRequestMessage* request, HttpCompletionOption completionOption, IAsyncOperationWithProgress_IHttpRequestResult_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static const struct IHttpClient2Vtbl http_client2_vtbl =
{
    http_client2_QueryInterface,
    http_client2_AddRef,
    http_client2_Release,
    /* IInspectable methods */
    http_client2_GetIids,
    http_client2_GetRuntimeClassName,
    http_client2_GetTrustLevel,
    /* IHttpClient2 methods */
    http_client2_TryDeleteAsync,
    http_client2_TryGetAsync,
    http_client2_TryGetAsync2,
    http_client2_TryGetBufferAsync,
    http_client2_TryGetInputStreamAsync,
    http_client2_TryGetStringAsync,
    http_client2_TryPostAsync,
    http_client2_TryPutAsync,
    http_client2_TrySendRequestAsync,
    http_client2_TrySendRequestAsync2
};


/*
 *
 * IHttpResponseMessage
 *
 */

static HRESULT WINAPI http_response_get_Content( IHttpResponseMessage* iface, IHttpContent** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_response_put_Content( IHttpResponseMessage* iface, IHttpContent* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_response_get_Headers( IHttpResponseMessage* iface, IHttpRequestHeaderCollection** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_response_get_IsSuccessStatusCode( IHttpResponseMessage* iface, BOOLEAN* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_response_get_ReasonPhrase( IHttpResponseMessage* iface, HSTRING* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_response_put_ReasonPhrase( IHttpResponseMessage* iface, HSTRING value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_response_get_RequestMessage( IHttpResponseMessage* iface, IHttpRequestMessage** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_response_put_RequestMessage( IHttpResponseMessage* iface, IHttpRequestMessage* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_response_get_Source( IHttpResponseMessage* iface, HttpResponseMessageSource* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_response_put_Source( IHttpResponseMessage* iface, HttpResponseMessageSource value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_response_get_StatusCode( IHttpResponseMessage* iface, HttpStatusCode* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_response_put_StatusCode( IHttpResponseMessage* iface, HttpStatusCode value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_response_get_Version( IHttpResponseMessage* iface, HttpVersion* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_response_put_Version( IHttpResponseMessage* iface, HttpVersion value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_response_EnsureSuccessStatusCode( IHttpResponseMessage* iface, IHttpResponseMessage** result )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static const struct IHttpResponseMessageVtbl http_response_vtbl =
{
    http_response_QueryInterface,
    http_response_AddRef,
    http_response_Release,
    /* IInspectable methods */
    http_response_GetIids,
    http_response_GetRuntimeClassName,
    http_response_GetTrustLevel,
    /* IHttpResponseMessage methods */
    http_response_get_Content,
    http_response_put_Content,
    http_response_get_Headers,
    http_response_get_IsSuccessStatusCode,
    http_response_get_ReasonPhrase,
    http_response_put_ReasonPhrase,
    http_response_get_RequestMessage,
    http_response_put_RequestMessage,
    http_response_get_Source,
    http_response_put_Source,
    http_response_get_StatusCode,
    http_response_put_StatusCode,
    http_response_get_Version,
    http_response_put_Version,
    http_response_EnsureSuccessStatusCode
};

struct http_header_container {
    struct rb_entry entry;
    WCHAR* name;
    WCHAR* value;
}

static int http_header_container_cmp(const void *key, const struct rb_entry *entry) 
{
    return wcscmp(key, RB_ENTRY_VALUE(entry, struct http_header_container, entry)->name);
}

struct http_request_headers {
    struct rb_tree header_map;
};

static void http_request_headers_init(struct http_request_headers* instance) 
{
    rb_init(&instance->header_map, http_header_cmp)
}

static WCHAR* http_request_headers_get(struct http_request_headers* instance, const WCHAR* key) 
{
    if (!key) 
        return NULL;
    
    struct rb_entry *entry;

    entry = rb_get(&instance->header_map, key);
    if (entry) 
        return RB_ENTRY_VALUE(entry, struct http_header_container, entry)->value;
    else
        return NULL;
}

static int http_request_headers_put(struct http_request_headers* instance, const WCHAR* key, const WCHAR* value) 
{
    if (!key || !value)
        return -1;

    size_t value_size;
    size_t key_size;
    WCHAR* value_cpy;
    WCHAR* key_cpy;
    struct http_header_container *container;

    value_size = (wcslen(value) + 1) * sizeof(WCHAR);
    key_size = (wcslen(key) + 1) * sizeof(WCHAR);

    value_cpy = malloc(value_size);
    memcpy(value_cpy, value, value_size);
    key_cpy = malloc(key_size);
    memcpy(key_cpy, key, key_size);
    
    container = malloc(sizeof(struct container));
    container->name = name_cpy;
    container->value = value_cpy;

    return rb_put(&instance->header_map, name_cpy, &container->entry);
}

static int http_request_headers_rm(struct http_request_headers* instance, const WCHAR* key) 
{
    if (!key) 
        return -1;

    struct rb_entry *entry;

    entry = rb_get(&instance->header_map, key);
    rb_remove(&instance->header_map, entry);
    free(RB_ENTRY_VALUE(entry, struct http_header_container, entry));
    
    return 0;
}

static void http_request_headers_free(struct http_request_headers* instance) 
{
    // TODO
}

struct http_client {
    IHttpClient IHttpClient_iface;
    IHttpClient2 IHttpClient2_iface;
    LONG ref;

    HINTERNET session;
    struct http_request_headers default_headers;
};


static HRESULT WINAPI http_client_factory_Create(IHttpClientFactory* iface, IHttpFilter* filter, IHttpClient** instance)
{
    struct http_client *impl;
    HINTERNET hSession = NULL;

    TRACE("iface %p, filter %p, instance %p.\n", iface, filter, instance);

    if (!(impl = calloc(1, sizeof(*impl)))) return E_OUTOFMEMORY;
    
    hSession = WinHttpOpen(
        NULL,
        WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0
    )
    if (!hSession) 
    {
        WARN("failed to create WinHTTP session with error %u", GetLastError());
        free(impl);
        return E_FAIL;
    }

    impl->session = hSession;
    impl->IHttpClient_iface.lpVtbl = &http_client_vtbl;
    impl->IHttpClient2_iface.lpVtbl = &http_client2_vtbl;
    impl->ref = 1;

    TRACE("created HttpClient %p.\n", impl);

    *instance = &impl->IHttpClient_iface;
    return S_OK;
}

#define RB_DEFINE_IMAP_IINSPECTABLE(key_type, value_type, impl_type, impl_from, tree_field, container_type, container_key_field, container_value_field, container_entry_field)
struct name_container_type_t {
    IKeyValuePair IKeyValuePair_iface;

    struct rb_entry entry;
    key_type key;
    value_type value;
};

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


static int http_request_headers_rm(struct http_request_headers* instance, const WCHAR* key) 
{
    if (!key) 
        return -1;

    struct rb_entry *entry;

    entry = rb_get(&instance->header_map, key);
    rb_remove(&instance->header_map, entry);
    free(RB_ENTRY_VALUE(entry, struct http_header_container, entry));
    
    return 0;
}

/*
 *
 * IHttpClient
 *
 */

static HRESULT WINAPI http_client_get_DefaultRequestHeaders( IHttpClient* iface, IHttpRequestHeaderCollection** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client_DeleteAsync( IHttpClient* iface, IUriRuntimeClass* uri, IAsyncOperationWithProgress_IHttpResponseMessage_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client_GetAsync( IHttpClient* iface, IUriRuntimeClass* uri, IAsyncOperationWithProgress_IHttpResponseMessage_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client_GetWithOptionAsync( IHttpClient* iface, IUriRuntimeClass* uri, HttpCompletionOption completionOption, IAsyncOperationWithProgress_IHttpResponseMessage_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client_GetBufferAsync( IHttpClient* iface, IUriRuntimeClass* uri, IAsyncOperationWithProgress_IBuffer_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client_GetInputStreamAsync( IHttpClient* iface, IUriRuntimeClass* uri, IAsyncOperationWithProgress_IInputStream_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client_GetStringAsync( IHttpClient* iface, IUriRuntimeClass* uri, IAsyncOperationWithProgress_HSTRING_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client_PostAsync( IHttpClient* iface, IUriRuntimeClass* uri, IHttpContent* content, IAsyncOperationWithProgress_IHttpResponseMessage_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client_PutAsync( IHttpClient* iface, IUriRuntimeClass* uri, IHttpContent* content, IAsyncOperationWithProgress_IHttpResponseMessage_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client_SendRequestAsync( IHttpClient* iface, IHttpRequestMessage* request, IAsyncOperationWithProgress_IHttpResponseMessage_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_client_SendRequestWithOptionAsync( IHttpClient* iface, IHttpRequestMessage* request, HttpCompletionOption completionOption, IAsyncOperationWithProgress_IHttpResponseMessage_HttpProgress** operation )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static const struct IHttpClientVtbl http_client_vtbl =
{
    http_client_QueryInterface,
    http_client_AddRef,
    http_client_Release,
    /* IInspectable methods */
    http_client_GetIids,
    http_client_GetRuntimeClassName,
    http_client_GetTrustLevel,
    /* IHttpClient methods */
    http_client_get_DefaultRequestHeaders,
    http_client_DeleteAsync,
    http_client_GetAsync,
    http_client_GetWithOptionAsync,
    http_client_GetBufferAsync,
    http_client_GetInputStreamAsync,
    http_client_GetStringAsync,
    http_client_PostAsync,
    http_client_PutAsync,
    http_client_SendRequestAsync,
    http_client_SendRequestWithOptionAsync
};


/*
 *
 * IHttpRequestHeaderCollection
 *
 */

static HRESULT WINAPI http_request_headers_get_Accept( IHttpRequestHeaderCollection* iface, IHttpMediaTypeWithQualityHeaderValueCollection** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_get_AcceptEncoding( IHttpRequestHeaderCollection* iface, IHttpContentCodingWithQualityHeaderValueCollection** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_get_AcceptLanguage( IHttpRequestHeaderCollection* iface, IHttpLanguageRangeWithQualityHeaderValueCollection** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_get_Authorization( IHttpRequestHeaderCollection* iface, IHttpCredentialsHeaderValue** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_put_Authorization( IHttpRequestHeaderCollection* iface, IHttpCredentialsHeaderValue* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_get_CacheControl( IHttpRequestHeaderCollection* iface, IHttpCacheDirectiveHeaderValueCollection** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_get_Connection( IHttpRequestHeaderCollection* iface, IHttpConnectionOptionHeaderValueCollection** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_get_Cookie( IHttpRequestHeaderCollection* iface, IHttpCookiePairHeaderValueCollection** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_get_Date( IHttpRequestHeaderCollection* iface, IReference_DateTime** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_put_Date( IHttpRequestHeaderCollection* iface, IReference_DateTime* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_get_Expect( IHttpRequestHeaderCollection* iface, IHttpExpectationHeaderValueCollection** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_get_From( IHttpRequestHeaderCollection* iface, HSTRING* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_put_From( IHttpRequestHeaderCollection* iface, HSTRING value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_get_Host( IHttpRequestHeaderCollection* iface, Windows.Networking.HostName** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_put_Host( IHttpRequestHeaderCollection* iface, Windows.Networking.HostName* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_get_IfModifiedSince( IHttpRequestHeaderCollection* iface, IReference_DateTime** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_put_IfModifiedSince( IHttpRequestHeaderCollection* iface, IReference_DateTime* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_get_IfUnmodifiedSince( IHttpRequestHeaderCollection* iface, IReference_DateTime** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_put_IfUnmodifiedSince( IHttpRequestHeaderCollection* iface, IReference_DateTime* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_get_MaxForwards( IHttpRequestHeaderCollection* iface, IReference_UINT32** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_put_MaxForwards( IHttpRequestHeaderCollection* iface, IReference_UINT32* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_get_ProxyAuthorization( IHttpRequestHeaderCollection* iface, IHttpCredentialsHeaderValue** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_put_ProxyAuthorization( IHttpRequestHeaderCollection* iface, IHttpCredentialsHeaderValue* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_get_Referer( IHttpRequestHeaderCollection* iface, IUriRuntimeClass** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_put_Referer( IHttpRequestHeaderCollection* iface, IUriRuntimeClass* value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_get_TransferEncoding( IHttpRequestHeaderCollection* iface, IHttpTransferCodingHeaderValueCollection** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_get_UserAgent( IHttpRequestHeaderCollection* iface, IHttpProductInfoHeaderValueCollection** value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_Append( IHttpRequestHeaderCollection* iface, HSTRING name, HSTRING value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_TryAppendWithoutValidation( IHttpRequestHeaderCollection* iface, HSTRING name, HSTRING value, BOOLEAN* result )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static const struct IHttpRequestHeaderCollectionVtbl http_request_headers_vtbl =
{
    http_request_headers_QueryInterface,
    http_request_headers_AddRef,
    http_request_headers_Release,
    /* IInspectable methods */
    http_request_headers_GetIids,
    http_request_headers_GetRuntimeClassName,
    http_request_headers_GetTrustLevel,
    /* IHttpRequestHeaderCollection methods */
    http_request_headers_get_Accept,
    http_request_headers_get_AcceptEncoding,
    http_request_headers_get_AcceptLanguage,
    http_request_headers_get_Authorization,
    http_request_headers_put_Authorization,
    http_request_headers_get_CacheControl,
    http_request_headers_get_Connection,
    http_request_headers_get_Cookie,
    http_request_headers_get_Date,
    http_request_headers_put_Date,
    http_request_headers_get_Expect,
    http_request_headers_get_From,
    http_request_headers_put_From,
    http_request_headers_get_Host,
    http_request_headers_put_Host,
    http_request_headers_get_IfModifiedSince,
    http_request_headers_put_IfModifiedSince,
    http_request_headers_get_IfUnmodifiedSince,
    http_request_headers_put_IfUnmodifiedSince,
    http_request_headers_get_MaxForwards,
    http_request_headers_put_MaxForwards,
    http_request_headers_get_ProxyAuthorization,
    http_request_headers_put_ProxyAuthorization,
    http_request_headers_get_Referer,
    http_request_headers_put_Referer,
    http_request_headers_get_TransferEncoding,
    http_request_headers_get_UserAgent,
    http_request_headers_Append,
    http_request_headers_TryAppendWithoutValidation
};
