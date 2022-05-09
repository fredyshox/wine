#include "private.h"

#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(iertutil);

/*
 *
 * Windows.Foundation.Uri
 *
 */

struct uri 
{
    IUriRuntimeClass IUriRuntimeClass_iface;
    IUriRuntimeClassWithAbsoluteCanonicalUri IUriRuntimeClassWithAbsoluteCanonicalUri_iface;
    IStringable IStringable_iface;
    LONG ref;

    IUri *wrapped_uri;
};

static inline HRESULT bstr_to_hstring(BSTR source, HSTRING* dest) 
{
    // TODO what about embedded null characters, does length cover for them
    return WindowsCreateString(source, SysStringLen(source), dest);
}

static inline HRESULT WINAPI _call_iuri_method(struct uri *uri, HRESULT(*iurl_method)(IUri*, BSTR*), HSTRING* value) {
    HRESULT hres;
    BSTR b_value;         
    hres = iurl_method(uri->wrapped_uri, &b_value);
    if (FAILED(hres))
        return hres;
    return bstr_to_hstring(b_value, value);
}

#define CALL_IURI_METHOD(uri_struct, method_name, value) _call_iuri_method(uri_struct, IUri_##method_name, value)

/*
 *
 * IUriRuntimeClass
 *
 */

static inline struct uri *impl_from_IUriRuntimeClass(IUriRuntimeClass *iface)
{
    return CONTAINING_RECORD(iface, struct uri, IUriRuntimeClass_iface);
}

static HRESULT WINAPI uri_QueryInterface( IUriRuntimeClass *iface, REFIID iid, void **out ) {
    struct uri *impl = impl_from_IUriRuntimeClass(iface);

    TRACE("iface %p, iid %s, out %p.\n", iface, debugstr_guid(iid), out);

    if (IsEqualGUID(iid, &IID_IUnknown) ||
        IsEqualGUID(iid, &IID_IInspectable) ||
        IsEqualGUID(iid, &IID_IAgileObject) ||
        IsEqualGUID(iid, &IID_IUriRuntimeClass))
    {
        IInspectable_AddRef((*out = &impl->IUriRuntimeClass_iface));
        return S_OK;
    }

    if (IsEqualGUID(iid, &IID_IUriRuntimeClassWithAbsoluteCanonicalUri))
    {
        IInspectable_AddRef((*out = &impl->IUriRuntimeClassWithAbsoluteCanonicalUri_iface));
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

static ULONG WINAPI uri_AddRef( IUriRuntimeClass *iface )
{
    struct uri *impl = impl_from_IUriRuntimeClass(iface);
    ULONG ref = InterlockedIncrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);
    return ref;
}

static ULONG WINAPI uri_Release( IUriRuntimeClass *iface )
{
    struct uri *impl = impl_from_IUriRuntimeClass(iface);

    ULONG ref = InterlockedDecrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);

    if (!ref)
    {
        if (impl->wrapped_uri)
            IUri_Release(impl->wrapped_uri);
        free(impl);
    }

    return ref;
}

static HRESULT WINAPI uri_GetIids( IUriRuntimeClass *iface, ULONG *iid_count, IID **iids )
{
    FIXME("iface %p, iid_count %p, iids %p stub!\n", iface, iid_count, iids);
    return E_NOTIMPL;
}

static HRESULT WINAPI uri_GetRuntimeClassName( IUriRuntimeClass *iface, HSTRING *class_name )
{
    FIXME("iface %p, class_name %p stub!\n", iface, class_name);
    return E_NOTIMPL;
}

static HRESULT WINAPI uri_GetTrustLevel( IUriRuntimeClass *iface, TrustLevel *trust_level )
{
    FIXME("iface %p, trust_level %p stub!\n", iface, trust_level);
    return E_NOTIMPL;
}

static HRESULT WINAPI uri_get_AbsoluteUri(IUriRuntimeClass *iface, HSTRING *value)
{
    struct uri *uri = impl_from_IUriRuntimeClass(iface);
    TRACE("iface %p, value %p.\n", iface, value);
    return CALL_IURI_METHOD(uri, GetAbsoluteUri, value);
}

static HRESULT WINAPI uri_get_DisplayUri(IUriRuntimeClass *iface, HSTRING *value)
{
    struct uri *uri = impl_from_IUriRuntimeClass(iface);
    TRACE("iface %p, value %p.\n", iface, value);
    return CALL_IURI_METHOD(uri, GetDisplayUri, value);
}

static HRESULT WINAPI uri_get_Domain(IUriRuntimeClass *iface, HSTRING *value)
{
    struct uri *uri = impl_from_IUriRuntimeClass(iface);
    TRACE("iface %p, value %p.\n", iface, value);
    return CALL_IURI_METHOD(uri, GetDomain, value);
}                                                         \

static HRESULT WINAPI uri_get_Extension(IUriRuntimeClass *iface, HSTRING *value) 
{
    struct uri *uri = impl_from_IUriRuntimeClass(iface);
    TRACE("iface %p, value %p.\n", iface, value);
    return CALL_IURI_METHOD(uri, GetExtension, value);
}

static HRESULT WINAPI uri_get_Fragment(IUriRuntimeClass *iface, HSTRING *value)
{
    struct uri *uri = impl_from_IUriRuntimeClass(iface);
    TRACE("iface %p, value %p.\n", iface, value);
    return CALL_IURI_METHOD(uri, GetFragment, value);
}

static HRESULT WINAPI uri_get_Host(IUriRuntimeClass *iface, HSTRING *value)
{
    struct uri *uri = impl_from_IUriRuntimeClass(iface);
    TRACE("iface %p, value %p.\n", iface, value);
    return CALL_IURI_METHOD(uri, GetHost, value);
}

static HRESULT WINAPI uri_get_Password(IUriRuntimeClass *iface, HSTRING *value)
{
    struct uri *uri = impl_from_IUriRuntimeClass(iface);
    TRACE("iface %p, value %p.\n", iface, value);
    return CALL_IURI_METHOD(uri, GetPassword, value);
}

static HRESULT WINAPI uri_get_Path(IUriRuntimeClass *iface, HSTRING *value)
{
    struct uri *uri = impl_from_IUriRuntimeClass(iface);
    TRACE("iface %p, value %p.\n", iface, value);
    return CALL_IURI_METHOD(uri, GetPath, value);
}

static HRESULT WINAPI uri_get_Query(IUriRuntimeClass *iface, HSTRING *value)
{
    struct uri *uri = impl_from_IUriRuntimeClass(iface);
    TRACE("iface %p, value %p.\n", iface, value);
    return CALL_IURI_METHOD(uri, GetQuery, value);
}

static HRESULT WINAPI uri_get_QueryParsed(IUriRuntimeClass *iface, IWwwFormUrlDecoderRuntimeClass** ppWwwFormUrlDecoder)
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI uri_get_RawUri(IUriRuntimeClass *iface, HSTRING *value)
{
    struct uri *uri = impl_from_IUriRuntimeClass(iface);
    TRACE("iface %p, value %p.\n", iface, value);
    return CALL_IURI_METHOD(uri, GetRawUri, value);
}

static HRESULT WINAPI uri_get_SchemeName(IUriRuntimeClass *iface, HSTRING *value)
{
    struct uri *uri = impl_from_IUriRuntimeClass(iface);
    TRACE("iface %p, value %p.\n", iface, value);
    return CALL_IURI_METHOD(uri, GetSchemeName, value);
}

static HRESULT WINAPI uri_get_UserName(IUriRuntimeClass *iface, HSTRING *value)
{
    struct uri *uri = impl_from_IUriRuntimeClass(iface);
    TRACE("iface %p, value %p.\n", iface, value);
    return CALL_IURI_METHOD(uri, GetUserName, value);
}

static HRESULT WINAPI uri_get_Port(IUriRuntimeClass *iface, INT32 *value)
{
    struct uri *uri = impl_from_IUriRuntimeClass(iface);

    UINT32 port;
    HRESULT hres;

    TRACE("iface %p, value %p.\n", iface, value);

    hres = IUri_GetPort(uri->wrapped_uri, &port);
    *value = (INT32)port;

    return hres;
}

static HRESULT WINAPI uri_get_Suspicious(IUriRuntimeClass *iface, BOOLEAN *value)
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI uri_Equals(IUriRuntimeClass *iface, IUriRuntimeClass* pUri, BOOLEAN *value)
{
    struct uri *first_uri = impl_from_IUriRuntimeClass(iface);
    struct uri *second_uri = impl_from_IUriRuntimeClass(pUri);
    BOOL bValue;
    HRESULT hres;

    TRACE("iface %p, pUri %p, value %p.\n", iface, pUri, value);
    
    hres = IUri_IsEqual(first_uri->wrapped_uri, second_uri->wrapped_uri, &bValue);
    *value = (BOOLEAN) bValue;

    return hres;
}

static HRESULT WINAPI uri_CombineUri(IUriRuntimeClass *iface, HSTRING relativeUri, IUriRuntimeClass **instance)
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static const struct IUriRuntimeClassVtbl uri_vtbl =
{
    uri_QueryInterface,
    uri_AddRef,
    uri_Release,
    /* IInspectable methods */
    uri_GetIids,
    uri_GetRuntimeClassName,
    uri_GetTrustLevel,
    /* IUriRuntimeClass methods */
    uri_get_AbsoluteUri,
    uri_get_DisplayUri,
    uri_get_Domain,
    uri_get_Extension,
    uri_get_Fragment,
    uri_get_Host,
    uri_get_Password,
    uri_get_Path,
    uri_get_Query,
    uri_get_QueryParsed,
    uri_get_RawUri,
    uri_get_SchemeName,
    uri_get_UserName,
    uri_get_Port,
    uri_get_Suspicious,
    uri_Equals,
    uri_CombineUri
};

/*
 *
 * IUriRuntimeClassWithAbsoluteCanonicalUri
 *
 */

DEFINE_IINSPECTABLE(uri_absolute_canonical, IUriRuntimeClassWithAbsoluteCanonicalUri, struct uri, IUriRuntimeClass_iface)

static HRESULT WINAPI uri_absolute_canonical_get_AbsoluteCanonicalUri(IUriRuntimeClassWithAbsoluteCanonicalUri *iface, HSTRING *value)
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI uri_absolute_canonical_get_DisplayIri(IUriRuntimeClassWithAbsoluteCanonicalUri *iface, HSTRING *value)
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static const struct IUriRuntimeClassWithAbsoluteCanonicalUriVtbl uri_absolute_canonical_vtbl =
{
    uri_absolute_canonical_QueryInterface,
    uri_absolute_canonical_AddRef,
    uri_absolute_canonical_Release,
    /* IInspectable methods */
    uri_absolute_canonical_GetIids,
    uri_absolute_canonical_GetRuntimeClassName,
    uri_absolute_canonical_GetTrustLevel,
    /* IUriRuntimeClassWithAbsoluteCanonicalUri methods */
    uri_absolute_canonical_get_AbsoluteCanonicalUri,
    uri_absolute_canonical_get_DisplayIri
};

/*
 *
 * IStringable
 *
 */

DEFINE_IINSPECTABLE(uri_stringable, IStringable, struct uri, IUriRuntimeClass_iface)

static HRESULT WINAPI uri_stringable_ToString( IStringable *iface, HSTRING *value )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static const struct IStringableVtbl uri_stringable_vtbl =
{
    uri_stringable_QueryInterface,
    uri_stringable_AddRef,
    uri_stringable_Release,
    /* IInspectable methods */
    uri_stringable_GetIids,
    uri_stringable_GetRuntimeClassName,
    uri_stringable_GetTrustLevel,
    /* IStringable methods */
    uri_stringable_ToString
};

/*
 *
 * Statics for Windows.Foundation.Uri
 *
 */

struct uri_statics
{
    IActivationFactory IActivationFactory_iface;
    IUriRuntimeClassFactory IUriRuntimeClassFactory_iface;
    IUriEscapeStatics IUriEscapeStatics_iface;
    LONG ref;
};

/*
 *
 * IActivationFactory
 *
 */

static inline struct uri_statics *impl_from_IActivationFactory( IActivationFactory *iface )
{
    return CONTAINING_RECORD(iface, struct uri_statics, IActivationFactory_iface);
}

static HRESULT WINAPI activation_factory_QueryInterface( IActivationFactory *iface, REFIID iid, void **out )
{
    struct uri_statics *impl = impl_from_IActivationFactory(iface);

    TRACE("iface %p, iid %s, out %p stub!\n", iface, debugstr_guid(iid), out);

    if (IsEqualGUID(iid, &IID_IUnknown) ||
        IsEqualGUID(iid, &IID_IInspectable) ||
        IsEqualGUID(iid, &IID_IAgileObject) ||
        IsEqualGUID(iid, &IID_IActivationFactory))
    {
        IInspectable_AddRef((*out = &impl->IActivationFactory_iface));
        return S_OK;
    }

    if (IsEqualGUID(iid, &IID_IUriRuntimeClassFactory))
    {
        IInspectable_AddRef((*out = &impl->IUriRuntimeClassFactory_iface));
        return S_OK;
    }

    if (IsEqualGUID(iid, &IID_IUriEscapeStatics))
    {
        IInspectable_AddRef((*out = &impl->IUriEscapeStatics_iface));
        return S_OK;
    }

    FIXME("%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid(iid));
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI activation_factory_AddRef( IActivationFactory *iface )
{
    struct uri_statics *impl = impl_from_IActivationFactory(iface);
    ULONG ref = InterlockedIncrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);
    return ref;
}

static ULONG WINAPI activation_factory_Release( IActivationFactory *iface )
{
    struct uri_statics *impl = impl_from_IActivationFactory(iface);
    ULONG ref = InterlockedDecrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);
    return ref;
}

static HRESULT WINAPI activation_factory_GetIids( IActivationFactory *iface, ULONG *iid_count, IID **iids )
{
    FIXME("iface %p, iid_count %p, iids %p stub!\n", iface, iid_count, iids);
    return E_NOTIMPL;
}

static HRESULT WINAPI activation_factory_GetRuntimeClassName( IActivationFactory *iface, HSTRING *class_name )
{
    FIXME("iface %p, class_name %p stub!\n", iface, class_name);
    return E_NOTIMPL;
}

static HRESULT WINAPI activation_factory_GetTrustLevel( IActivationFactory *iface, TrustLevel *trust_level )
{
    FIXME("iface %p, trust_level %p stub!\n", iface, trust_level);
    return E_NOTIMPL;
}

static HRESULT WINAPI activation_factory_ActivateInstance( IActivationFactory *iface, IInspectable **instance )
{
    struct uri_statics *impl = impl_from_IActivationFactory(iface);
    TRACE("iface %p, instance %p.\n", iface, instance);
    return IUriRuntimeClassFactory_CreateUri(&impl->IUriRuntimeClassFactory_iface, NULL, (IUriRuntimeClass **)instance);
}

static const struct IActivationFactoryVtbl activation_factory_vtbl =
{
    /* IUnknown methods */
    activation_factory_QueryInterface,
    activation_factory_AddRef,
    activation_factory_Release,
    /* IInspectable methods */
    activation_factory_GetIids,
    activation_factory_GetRuntimeClassName,
    activation_factory_GetTrustLevel,
    /* IActivationFactory methods */
    activation_factory_ActivateInstance,
};

/*
 *
 * IUriRuntimeClassFactory
 *
 */

DEFINE_IINSPECTABLE(uri_factory, IUriRuntimeClassFactory, struct uri_statics, IActivationFactory_iface)

static HRESULT WINAPI uri_factory_CreateUri(IUriRuntimeClassFactory *iface, HSTRING uri, IUriRuntimeClass **instance)
{
    struct uri *impl;
    IUri *wrapped_uri;
    HRESULT hres;

    TRACE("iface %p, uri %p, instance %p.\n", iface, uri, instance);

    if (!(impl = calloc(1, sizeof(*impl)))) return E_OUTOFMEMORY;

    WCHAR* buf_ptr;
    UINT32 buf_len;
    buf_ptr = WindowsGetStringRawBuffer(uri, &buf_len);

    WCHAR* raw_uri = calloc(buf_len + 1, sizeof(WCHAR));
    memcpy(raw_uri, buf_ptr, sizeof(WCHAR)*buf_len);

    if (FAILED(hres = CreateUri(raw_uri, Uri_CREATE_CANONICALIZE, 0, &wrapped_uri)))
    {
        WARN("failed to create wrapped IUri, hres %#lx.\n", hres);
        free(impl);
        free(raw_uri);
        return hres;
    }

    free(raw_uri);

    impl->IUriRuntimeClass_iface.lpVtbl = &uri_vtbl;
    impl->IUriRuntimeClassWithAbsoluteCanonicalUri_iface.lpVtbl = &uri_absolute_canonical_vtbl;
    impl->IStringable_iface.lpVtbl = &uri_stringable_vtbl;
    impl->wrapped_uri = wrapped_uri;
    IUri_AddRef(impl->wrapped_uri);
    impl->ref = 1;

    TRACE("created Uri %p.\n", impl);

    *instance = &impl->IUriRuntimeClass_iface;
    return S_OK;
}

static HRESULT WINAPI uri_factory_CreateWithRelativeUri(IUriRuntimeClassFactory *iface, HSTRING base_uri, HSTRING relative_uri, IUriRuntimeClass **instance)
{
    FIXME( "iface %p, base %p, relative %p, instance %p stub!\n", iface, base_uri, relative_uri, instance);
    return E_NOTIMPL;
}

static const struct IUriRuntimeClassFactoryVtbl uri_factory_vtbl =
{
    uri_factory_QueryInterface,
    uri_factory_AddRef,
    uri_factory_Release,
    /* IInspectable methods */
    uri_factory_GetIids,
    uri_factory_GetRuntimeClassName,
    uri_factory_GetTrustLevel,
    /* IUriRuntimeClassFactory methods */
    uri_factory_CreateUri,
    uri_factory_CreateWithRelativeUri
};

/*
 *
 * IUriEscapeStatics
 *
 */

DEFINE_IINSPECTABLE(statics, IUriEscapeStatics, struct uri_statics, IActivationFactory_iface)

static HRESULT WINAPI statics_get_UnescapeComponent(IUriEscapeStatics *iface, HSTRING toUnescape, HSTRING *value)
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI statics_get_EscapeComponent(IUriEscapeStatics *iface, HSTRING toEscape, HSTRING *value)
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static const struct IUriEscapeStaticsVtbl statics_vtbl =
{
    statics_QueryInterface,
    statics_AddRef,
    statics_Release,
    /* IInspectable methods */
    statics_GetIids,
    statics_GetRuntimeClassName,
    statics_GetTrustLevel,
    /* IUriEscapeStatics methods */
    statics_get_UnescapeComponent,
    statics_get_EscapeComponent
};

static struct uri_statics uri_statics =
{
    .IActivationFactory_iface = {&activation_factory_vtbl},
    .IUriRuntimeClassFactory_iface = {&uri_factory_vtbl},
    .IUriEscapeStatics_iface = {&statics_vtbl},
    .ref = 1
};

IActivationFactory *uri_activation_factory = &uri_statics.IActivationFactory_iface;