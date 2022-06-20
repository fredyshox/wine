/*
 *
 * IHttpConnectionOptionHeaderValueCollection
 *
 */

struct http_header_value_collection {
    IHttpConnectionOptionHeaderValueCollection IHttpConnectionOptionHeaderValueCollection_iface;
    
    WCHAR** values;
    IHttpRequestHeaderCollection* parent_collection;
}

static WCHAR* wcstrim(WCHAR* str, size_t* rlength) 
{
    WCHAR* substr_start = str;
    size_t substr_len = 0;
    size_t str_len = wcslen(str);
    bool found_start = false;

    for (int i = 0; i < str_len; i++) {
        if (!found_start) {
            if (iswspace(str[i]))
                continue
            found_start = true;
            substr_start = str+i;
        } else {
            if (iswspace(str[i]))
                break
            str_len += 1;
        }
    }

    *rlength = str_len;
    return substr_start;
}

static HRESULT WINAPI http_header_value_connection_ParseAdd ( IHttpConnectionOptionHeaderValueCollection* iface, HSTRING input )
{
    HRESULT hr;
    HSTRING input_copy;
    WCHAR* input_raw;
    size_t input_length;
    size_t token_length;
    WCHAR* token;
    WCHAR* state;

    WindowsDuplicateString(input, &input_copy);
    input_raw = WindowsGetStringRawBuffer(input_copy);
    input_length = wcslen(input_raw);


    token = wcstok(input_raw, L",", &state);
    while (token != NULL) 
    {
        token = wcstrim(token, &token_length);
        

        token = wcstok(NULL, L",", &state);
    }

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
 * IHttpRequestHeaderCollection
 *
 */

struct http_request_headers {
    IHttpRequestHeaderCollection IHttpRequestHeaderCollection_iface;
    IStringable IStringable_iface
    LONG ref;

    IMap_HSTRING_HSTRING* map_impl_iface;
    IIterable_IKeyValuePair_HSTRING_HSTRING* iterable_impl_iface;
};

static inline struct http_request_headers* impl_from_IHttpRequestHeaderCollection( IHttpRequestHeaderCollection* iface ) 
{
    return CONTAINING_RECORD(iface, struct http_request_headers, IHttpRequestHeaderCollection_iface);
}

static HRESULT WINAPI http_request_headers_QueryInterface( IHttpRequestHeaderCollection *iface, REFIID iid, void **out ) {
    struct http_request_headers *impl = impl_from_IHttpRequestHeaderCollection(iface);

    TRACE("iface %p, iid %s, out %p.\n", iface, debugstr_guid(iid), out);

    if (IsEqualGUID(iid, &IID_IUnknown) ||
        IsEqualGUID(iid, &IID_IInspectable) ||
        IsEqualGUID(iid, &IID_IAgileObject) ||
        IsEqualGUID(iid, &IID_IHttpRequestHeaderCollection))
    {
        IInspectable_AddRef((*out = &impl->IHttpRequestHeaderCollection_iface));
        return S_OK;
    }

    if (IsEqualGUID(iid, &IID_IMap_HSTRING_HSTRING))
    {
        //IInspectable_AddRef((*out = &impl->IUriRuntimeClassWithAbsoluteCanonicalUri_iface));
        // TODO
        return S_OK;
    }

    if (IsEqualGUID(iid, &IID_IIterable_IKeyValuePair_HSTRING_HSTRING))
    {
        // IInspectable_AddRef((*out = &impl->IUriRuntimeClassWithAbsoluteCanonicalUri_iface));
        // TODO
        return S_OK;
    }


    if (IsEqualGUID(iid, &IID_IStringable))
    {
        IInspectable_AddRef((*out = &impl->IStringable_iface));
        return S_OK;
    }

    WARN("%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid(iid));
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI http_request_headers_AddRef( IHttpRequestHeaderCollection *iface )
{
    struct http_request_headers *impl = impl_from_IHttpRequestHeaderCollection(iface);
    ULONG ref = InterlockedIncrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);
    return ref;
}

static ULONG WINAPI http_request_headers_Release( IHttpRequestHeaderCollection *iface )
{
    struct http_request_headers *impl = impl_from_IHttpRequestHeaderCollection(iface);

    ULONG ref = InterlockedDecrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);

    if (!ref)
    {
        IInspectable_Release(impl->map_impl_iface);
        free(impl);
    }

    return ref;
}

static HRESULT WINAPI http_request_headers_GetIids( IHttpRequestHeaderCollection *iface, ULONG *iid_count, IID **iids )
{
    FIXME("iface %p, iid_count %p, iids %p stub!\n", iface, iid_count, iids);
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_GetRuntimeClassName( IHttpRequestHeaderCollection *iface, HSTRING *class_name )
{
    FIXME("iface %p, class_name %p stub!\n", iface, class_name);
    return E_NOTIMPL;
}

static HRESULT WINAPI http_request_headers_GetTrustLevel( IHttpRequestHeaderCollection *iface, TrustLevel *trust_level )
{
    FIXME("iface %p, trust_level %p stub!\n", iface, trust_level);
    return E_NOTIMPL;
}

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
    BOOLEAN replaced;
    struct http_request_headers *impl = impl_from_IHttpRequestHeaderCollection(iface);

    return IMap_HSTRING_HSTRING_Insert(impl->map_impl_iface, name, value, &replaced);
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
