#include "private.h"

#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(system_profile);

/*
 *
 * AnalyticsVersionInfo
 *
 */

struct analytics_version_info
{
    IAnalyticsVersionInfo IAnalyticsVersionInfo_iface;
    LONG ref;
};

/*
 *
 * IAnalyticsVersionInfo
 *
 */

static inline struct analytics_version_info *impl_from_IAnalyticsVersionInfo( IAnalyticsVersionInfo *iface )
{
    return CONTAINING_RECORD(iface, struct analytics_version_info, IAnalyticsVersionInfo_iface);
}

static HRESULT WINAPI analytics_version_info_QueryInterface( IAnalyticsVersionInfo *iface, REFIID iid, void **out )
{
    struct analytics_version_info *impl = impl_from_IAnalyticsVersionInfo(iface);

    TRACE("iface %p, iid %s, out %p.\n", iface, debugstr_guid(iid), out);

    if (IsEqualGUID(iid, &IID_IUnknown) ||
        IsEqualGUID(iid, &IID_IInspectable) ||
        IsEqualGUID(iid, &IID_IAnalyticsVersionInfo))
    {
        IInspectable_AddRef((*out = &impl->IAnalyticsVersionInfo_iface));
        return S_OK;
    }

    WARN("%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid(iid));
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI analytics_version_info_AddRef( IAnalyticsVersionInfo *iface )
{
    struct analytics_version_info *impl = impl_from_IAnalyticsVersionInfo(iface);
    ULONG ref = InterlockedIncrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);
    return ref;
}

static ULONG WINAPI analytics_version_info_Release( IAnalyticsVersionInfo *iface )
{
    struct analytics_version_info *impl = impl_from_IAnalyticsVersionInfo(iface);
    ULONG ref = InterlockedDecrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);
    return ref;
}

static HRESULT WINAPI analytics_version_info_GetIids( IAnalyticsVersionInfo *iface, ULONG *iid_count, IID **iids )
{
    FIXME("iface %p, iid_count %p, iids %p stub!\n", iface, iid_count, iids);
    return E_NOTIMPL;
}

static HRESULT WINAPI analytics_version_info_GetRuntimeClassName( IAnalyticsVersionInfo *iface, HSTRING *class_name )
{
    FIXME("iface %p, class_name %p stub!\n", iface, class_name);
    return E_NOTIMPL;
}

static HRESULT WINAPI analytics_version_info_GetTrustLevel( IAnalyticsVersionInfo *iface, TrustLevel *trust_level )
{
    FIXME("iface %p, trust_level %p stub!\n", iface, trust_level);
    return E_NOTIMPL;
}

static HRESULT WINAPI analytics_version_info_get_DeviceFamily ( IAnalyticsVersionInfo *iface, HSTRING *value )
{
    WCHAR device_family[64];
    DWORD buf_size = ARRAY_SIZE(device_family);

    RtlConvertDeviceFamilyInfoToString(&buf_size, NULL, device_family, NULL);

    if (buf_size <= 0) return E_FAIL;

    TRACE("Return device family %ls\n", device_family);

    return WindowsCreateString(device_family, wcslen(device_family), value);
}

static HRESULT WINAPI analytics_version_info_get_DeviceFamilyVersion ( IAnalyticsVersionInfo *iface, HSTRING *value )
{
    UINT64 uap_info;
    WCHAR uap_info_str[21];

    RtlGetDeviceFamilyInfoEnum(&uap_info, NULL, NULL);
    swprintf(uap_info_str, ARRAY_SIZE(uap_info_str), L"%d", uap_info);

    return WindowsCreateString(uap_info_str, wcslen(uap_info_str), value);
}

static const struct IAnalyticsVersionInfoVtbl analytics_version_info_vtbl =
{
    /* IUnknown methods */
    analytics_version_info_QueryInterface,
    analytics_version_info_AddRef,
    analytics_version_info_Release,
    /* IInspectable methods */
    analytics_version_info_GetIids,
    analytics_version_info_GetRuntimeClassName,
    analytics_version_info_GetTrustLevel,
    /* IAnalyticsVersionInfo methods */
    analytics_version_info_get_DeviceFamily,
    analytics_version_info_get_DeviceFamilyVersion
};

/*
 *
 * AnalyticsInfo
 *
 */

struct analytics_info
{
    IInspectable IInspectable_iface;
    LONG ref;
};

/*
 *
 * IInspectable for AnalyticsInfo
 *
 */

static inline struct analytics_info *impl_from_IInspectable( IInspectable *iface )
{
    return CONTAINING_RECORD(iface, struct analytics_info, IInspectable_iface);
}

static HRESULT WINAPI analytics_info_QueryInterface( IInspectable *iface, REFIID iid, void **out )
{
    struct analytics_info *impl = impl_from_IInspectable(iface);

    TRACE("iface %p, iid %s, out %p.\n", iface, debugstr_guid(iid), out);

    if (IsEqualGUID(iid, &IID_IUnknown) ||
        IsEqualGUID(iid, &IID_IInspectable))
    {
        IInspectable_AddRef((*out = &impl->IInspectable_iface));
        return S_OK;
    }

    WARN("%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid(iid));
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI analytics_info_AddRef( IInspectable *iface )
{
    struct analytics_info *impl = impl_from_IInspectable(iface);
    ULONG ref = InterlockedIncrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);
    return ref;
}

static ULONG WINAPI analytics_info_Release( IInspectable *iface )
{
    struct analytics_info *impl = impl_from_IInspectable(iface);
    ULONG ref = InterlockedDecrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);
    return ref;
}

static HRESULT WINAPI analytics_info_GetIids( IInspectable *iface, ULONG *iid_count, IID **iids )
{
    FIXME("iface %p, iid_count %p, iids %p stub!\n", iface, iid_count, iids);
    return E_NOTIMPL;
}

static HRESULT WINAPI analytics_info_GetRuntimeClassName( IInspectable *iface, HSTRING *class_name )
{
    FIXME("iface %p, class_name %p stub!\n", iface, class_name);
    return E_NOTIMPL;
}

static HRESULT WINAPI analytics_info_GetTrustLevel( IInspectable *iface, TrustLevel *trust_level )
{
    FIXME("iface %p, trust_level %p stub!\n", iface, trust_level);
    return E_NOTIMPL;
}

static const struct IInspectableVtbl analytics_info_vtbl = 
{
    /* IUnknown methods */
    analytics_info_QueryInterface,
    analytics_info_AddRef,
    analytics_info_Release,
    /* IInspectable methods */
    analytics_info_GetIids,
    analytics_info_GetRuntimeClassName,
    analytics_info_GetTrustLevel,
};

/*
 *
 * Statics for AnalyticsInfo
 *
 */

struct analytics_info_statics
{
    IActivationFactory IActivationFactory_iface;
    IAnalyticsInfoStatics IAnalyticsInfoStatics_iface;
    IAnalyticsInfoStatics2 IAnalyticsInfoStatics2_iface;
    LONG ref;
};

/*
 *
 * IActivationFactory
 *
 */

static inline struct analytics_info_statics *impl_from_IActivationFactory( IActivationFactory *iface )
{
    return CONTAINING_RECORD(iface, struct analytics_info_statics, IActivationFactory_iface);
}

static HRESULT WINAPI activation_factory_QueryInterface( IActivationFactory *iface, REFIID iid, void **out )
{
    struct analytics_info_statics *impl = impl_from_IActivationFactory(iface);

    TRACE("iface %p, iid %s, out %p stub!\n", iface, debugstr_guid(iid), out);

    if (IsEqualGUID(iid, &IID_IUnknown) ||
        IsEqualGUID(iid, &IID_IInspectable) ||
        IsEqualGUID(iid, &IID_IAgileObject) ||
        IsEqualGUID(iid, &IID_IActivationFactory))
    {
        IInspectable_AddRef((*out = &impl->IActivationFactory_iface));
        return S_OK;
    }

    if (IsEqualGUID(iid, &IID_IAnalyticsInfoStatics)) {
        IInspectable_AddRef((*out = &impl->IAnalyticsInfoStatics_iface));
        return S_OK;
    }

    if (IsEqualGUID(iid, &IID_IAnalyticsInfoStatics2)) {
        IInspectable_AddRef((*out = &impl->IAnalyticsInfoStatics2_iface));
        return S_OK;
    }

    FIXME("%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid(iid));
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI activation_factory_AddRef( IActivationFactory *iface )
{
    struct analytics_info_statics *impl = impl_from_IActivationFactory(iface);
    ULONG ref = InterlockedIncrement(&impl->ref);
    TRACE("iface %p, ref %lu.\n", iface, ref);
    return ref;
}

static ULONG WINAPI activation_factory_Release( IActivationFactory *iface )
{
    struct analytics_info_statics *impl = impl_from_IActivationFactory(iface);
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
    FIXME( "iface %p, instance %p stub!\n", iface, instance );
    return E_NOTIMPL;
}

static const struct IActivationFactoryVtbl activation_factory_vtbl =
{
    activation_factory_QueryInterface,
    activation_factory_AddRef,
    activation_factory_Release,
    /* IInspectable methods */
    activation_factory_GetIids,
    activation_factory_GetRuntimeClassName,
    activation_factory_GetTrustLevel,
    /* IActivationFactory methods */
    activation_factory_ActivateInstance
};

/*
 *
 * IAnalyticsInfoStatics
 *
 */

DEFINE_IINSPECTABLE(statics, IAnalyticsInfoStatics, struct analytics_info_statics, IActivationFactory_iface)

static HRESULT WINAPI statics_get_VersionInfo ( IAnalyticsInfoStatics *iface, IAnalyticsVersionInfo **infos ) 
{
    struct analytics_version_info *impl;

    TRACE("iface %p, infos %p.\n", iface, infos);

    *infos = NULL;

    if (!(impl = calloc(1, sizeof(*impl)))) return E_OUTOFMEMORY;

    impl->IAnalyticsVersionInfo_iface.lpVtbl = &analytics_version_info_vtbl;
    impl->ref = 1;

    TRACE("created AnalyticsVersionInfo %p.\n", impl);

    *infos = &impl->IAnalyticsVersionInfo_iface;
    return S_OK;
}

static HRESULT WINAPI statics_get_DeviceForm ( IAnalyticsInfoStatics *iface, HSTRING *value ) 
{

    WCHAR device_form[64];
    DWORD buf_size = ARRAY_SIZE(device_form);

    RtlConvertDeviceFamilyInfoToString(NULL, &buf_size, NULL, device_form);

    if (buf_size <= 0) return E_FAIL;

    TRACE("Return device form %ls\n", device_form);

    return WindowsCreateString(device_form, wcslen(device_form), value);
}

static const struct IAnalyticsInfoStaticsVtbl analytics_info_statics_vtbl = 
{
    /* IUnknown methods */
    statics_QueryInterface,
    statics_AddRef,
    statics_Release,
    /* IInspectable methods */
    statics_GetIids,
    statics_GetRuntimeClassName,
    statics_GetTrustLevel,
    /* IAnalyticsInfoStatics methods */
    statics_get_VersionInfo,
    statics_get_DeviceForm
};

/*
 *
 * IAnalyticsInfoStatics2
 *
 */

DEFINE_IINSPECTABLE(statics2, IAnalyticsInfoStatics2, struct analytics_info_statics, IActivationFactory_iface)

static HRESULT WINAPI statics2_GetSystemPropertiesAsync( IAnalyticsInfoStatics2 *iface, IIterable_HSTRING* attribute_names, IAsyncOperation_IMapView_HSTRING_HSTRING** operation ) 
{
    FIXME("iface %p, attribute_names %p operation %p stub!\n", iface, attribute_names, operation);
    return E_NOTIMPL;
}

static const struct IAnalyticsInfoStatics2Vtbl analytics_info_statics2_vtbl = 
{
    /* IUnknown methods */
    statics2_QueryInterface,
    statics2_AddRef,
    statics2_Release,
    /* IInspectable methods */
    statics2_GetIids,
    statics2_GetRuntimeClassName,
    statics2_GetTrustLevel,
    /* IAnalyticsInfoStatics2 methods */
    statics2_GetSystemPropertiesAsync
};

static struct analytics_info_statics analytics_info_statics =
{
    .IActivationFactory_iface = {&activation_factory_vtbl},
    .IAnalyticsInfoStatics_iface = {&analytics_info_statics_vtbl},
    .IAnalyticsInfoStatics2_iface = {&analytics_info_statics2_vtbl},
    .ref = 1 
};

IActivationFactory *analytics_info_factory = &analytics_info_statics.IActivationFactory_iface;
