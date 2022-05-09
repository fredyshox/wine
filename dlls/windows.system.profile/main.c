#include "initguid.h"
#include "private.h"

#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(system_profile);

HRESULT WINAPI DllCanUnloadNow(void)
{
    return S_FALSE;
}

HRESULT WINAPI DllGetClassObject(REFCLSID clsid, REFIID riid, void **out) 
{
    FIXME("clsid %s, riid %s, out %p stub!\n", debugstr_guid(clsid), debugstr_guid(riid), out);
    return CLASS_E_CLASSNOTAVAILABLE;
}

HRESULT WINAPI DllGetActivationFactory(HSTRING classid, IActivationFactory **factory)
{
    const WCHAR *buffer = WindowsGetStringRawBuffer(classid, NULL);

    TRACE("classid %s, factory %p.\n", debugstr_w(buffer), factory);

    *factory = NULL;

    if (!wcscmp(buffer, L"Windows.System.Profile.AnalyticsInfo"))
        IActivationFactory_AddRef((*factory = analytics_info_factory));

    if (*factory) return S_OK;
    return CLASS_E_CLASSNOTAVAILABLE;
}