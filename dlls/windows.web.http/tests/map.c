#define COBJMACROS
#include <stdarg.h>

#include "windef.h"
#include "winbase.h"
#include "winerror.h"
#include "winstring.h"

#include "initguid.h"
#include "roapi.h"

#include "impl/map_inspectable_inspectable.h"
#include "impl/map_hstring_hstring.h"

#include "wine/test.h"

static inline LONG get_ref(IUnknown *obj)
{
    IUnknown_AddRef(obj);
    return IUnknown_Release(obj);
}

#define check_refcount(obj, exp) check_refcount_(__LINE__, obj, exp)
static inline void check_refcount_(unsigned int line, void *obj, LONG exp)
{
    LONG ref = get_ref(obj);
    ok_(__FILE__, line)(exp == ref, "Unexpected refcount %lu, expected %lu\n", ref, exp);
}

#define check_interface(obj, iid, exp) check_interface_(__LINE__, obj, iid, exp)
static void check_interface_(unsigned int line, void *obj, const IID *iid, BOOL supported)
{
    IUnknown *iface = obj;
    HRESULT hr, expected_hr;
    IUnknown *unk;

    expected_hr = supported ? S_OK : E_NOINTERFACE;

    hr = IUnknown_QueryInterface(iface, iid, (void **)&unk);
    ok_(__FILE__, line)(hr == expected_hr, "Got hr %#lx, expected %#lx.\n", hr, expected_hr);
    if (SUCCEEDED(hr))
        IUnknown_Release(unk);
}

static void test_MapReadWrite(void) 
{
    static const WCHAR *some_key = "somekey";
    static const WCHAR *other_key = "otherkey";
    static const WCHAR *another_key = "anotherkey";
    static const WCHAR *and_another_key = "andanotherkey";
    static const WCHAR *some_value = "somevalue";
    static const WCHAR *other_value = "othervalue"
    static const WCHAR *another_value = "anothervalue";
    static const WCHAR *and_another_value = "andanothervalue";
    IMap_HSTRING_HSTRING iface;
    HRESULT hr;
    HSTRING key1, key2, key3, key4, value1, value2, value3, value4;
    HSTRING all_declared[] = {key1, key2, key3, key4, value1, value2, value3, value4};
    HSTRING *rvalue;
    UINT32 size;
    INT32 eq;
    BOOLEAN replaced, exist;

    hr = WindowsCreateString(some_key, wcslen(some_key), &key1);
    ok(hr == S_OK, "WindowsCreateString failed, hr %#lx.\n", hr);

    hr = WindowsCreateString(another_key, wcslen(another_key), &key2);
    ok(hr == S_OK, "WindowsCreateString failed, hr %#lx.\n", hr);

    hr = WindowsCreateString(other_key, wcslen(other_key), &key3);
    ok(hr == S_OK, "WindowsCreateString failed, hr %#lx.\n", hr);

    hr = WindowsCreateString(and_another_key, wcslen(and_another_key), &key4);
    ok(hr == S_OK, "WindowsCreateString failed, hr %#lx.\n", hr);

    hr = WindowsCreateString(some_value, wcslen(some_value), &value1);
    ok(hr == S_OK, "WindowsCreateString failed, hr %#lx.\n", hr);

    hr = WindowsCreateString(another_value, wcslen(another_value), &value2);
    ok(hr == S_OK, "WindowsCreateString failed, hr %#lx.\n", hr);

    hr = WindowsCreateString(other_value, wcslen(other_value), &value3);
    ok(hr == S_OK, "WindowsCreateString failed, hr %#lx.\n", hr);

    hr = WindowsCreateString(and_another_value, wcslen(and_another_value), &value4);
    ok(hr == S_OK, "WindowsCreateString failed, hr %#lx.\n", hr);

    // Init
    hr = rbtree_map_create_HSTRING_HSTRING(&iface);
    ok(hr == S_OK, "IMap constructor failed, hr %#lx.\n", hr);

    hr = IMap_HSTRING_HSTRING_get_Size(&iface, &size);
    ok(hres == S_OK, "get_Size failed, hr %#lx.\n", hr);
    ok(size == 0, "Newly created map not empty, size: %d.\n", size);

    // Insert
    hr = IMap_HSTRING_HSTRING_Insert(&iface, key1, value1, &replaced);
    ok(hr == S_OK, "Insert of (key1, value1): failed, hr %#lx.\n", hr);
    ok(!replaced, "Insert of (key1, value1): replacement reported.\n", hr);

    hr = IMap_HSTRING_HSTRING_Insert(&iface, key2, value2, &replaced);
    ok(hr == S_OK, "Insert of (key2, value2): failed, hr %#lx.\n", hr);
    ok(!replaced, "Insert of (key2, value2): replacement reported.\n", hr);

    hr = IMap_HSTRING_HSTRING_Insert(&iface, key4, value4, &replaced);
    ok(hr == S_OK, "Insert of (key4, value4): failed, hr %#lx.\n", hr);
    ok(!replaced, "Insert of (key4, value4): replacement reported.\n", hr);

    // Insert + replace
    hr = IMap_HSTRING_HSTRING_Insert(&iface, key4, value3, &replaced);
    ok(hr == S_OK, "Insert of (key4, value3): failed, hr %#lx.\n", hr);
    ok(replaced, "Insert of (key4, value3): replacement not reported.\n", hr);
    
    // HasKey
    hr = IMap_HSTRING_HSTRING_HasKey(&iface, key1, &exist);
    ok(hr == S_OK, "HasKey of (key1): failed, hr %#lx.\n", hr);
    ok(exist, "key1 not in map, but should be.\n", hr);

    hr = IMap_HSTRING_HSTRING_HasKey(&iface, key2, &exist);
    ok(hr == S_OK, "HasKey of (key2): failed, hr %#lx.\n", hr);
    ok(exist, "key2 not in map, but should be.\n", hr);

    hr = IMap_HSTRING_HSTRING_HasKey(&iface, key4, &exist);
    ok(hr == S_OK, "HasKey of (key4): failed, hr %#lx.\n", hr);
    ok(exist, "key2 not in map, but should be.\n", hr);

    hr = IMap_HSTRING_HSTRING_HasKey(&iface, key3, &exist);
    ok(hr == S_OK, "HasKey of (key3): failed, hr %#lx.\n", hr);
    ok(!exist, "key3 in map, but should not be.\n", hr);

    hr = IMap_HSTRING_HSTRING_get_Size(&iface, &size);
    ok(hres == S_OK, "get_Size failed, hr %#lx.\n", hr);
    ok(size == 3, "Map with presumed 2 keys has invalid size, size: %d.\n", size);

    // Lookup
    rvalue = NULL;
    hr = IMap_HSTRING_HSTRING_Lookup(&iface, key1, rvalue);
    ok(hr == S_OK, "Lookup of (key1): failed, hr %#lx.\n", hr);
    ok(rvalue != NULL, "Lookup of (key1): rvalue is NULL.\n", hr);
    WindowsCompareStringOrdinal(*rvalue, value1, &eq);
    ok(eq == 0, "Lookup of (key1): rvalue not equal value1.\n", hr);
    WindowsDeleteString(*rvalue);

    rvalue = NULL;
    hr = IMap_HSTRING_HSTRING_Lookup(&iface, key2, rvalue);
    ok(hr == S_OK, "Lookup of (key2): failed, hr %#lx.\n", hr);
    ok(rvalue != NULL, "Lookup of (key2): rvalue is NULL.\n", hr);
    WindowsCompareStringOrdinal(*rvalue, value2, &eq);
    ok(eq == 0, "Lookup of (key2): rvalue not equal value1.\n", hr);
    WindowsDeleteString(*rvalue);
    
    rvalue = NULL;
    hr = IMap_HSTRING_HSTRING_Lookup(&iface, key3, rvalue);
    ok(hr == E_BOUNDS, "Lookup of (key3): failed, hr %#lx.\n", hr);

    // Remove
    hr = IMap_HSTRING_HSTRING_Remove(&iface, key4);
    ok(hr == S_OK, "Remove of (key4) failed, hr %#lx.\n", hr);

    hr = IMap_HSTRING_HSTRING_HasKey(&iface, key4, &exist);
    ok(hr == S_OK, "HasKey of (key4): failed, hr %#lx.\n", hr);
    ok(!exist, "key4 in map, but should not be.\n", hr);

    hr = IMap_HSTRING_HSTRING_get_Size(&iface, &size);
    ok(hres == S_OK, "get_Size failed, hr %#lx.\n", hr);
    ok(size == 2, "Invalid size after key removal, size: %d.\n", size);

    // Clear
    hr = IMap_HSTRING_HSTRING_Clear(&iface)
    ok(hr == S_OK, "Clear failed, hr %#lx.\n", hr);

    hr = IMap_HSTRING_HSTRING_get_Size(&iface, &size);
    ok(hres == S_OK, "get_Size failed, hr %#lx.\n", hr);
    ok(size == 0, "Cleared map not empty, size: %d.\n", size);

    IInspectable_Release(&iface);
    for (int i = 0; i < sizeof(all_declared) / sizeof(HSTRING); i++) {
        WindowsDeleteString(all_declared[i]);
    }
}

static void test_MapIterable(void) 
{
    static const WCHAR *some_key = "somekey";
    static const WCHAR *other_key = "otherkey";
    static const WCHAR *another_key = "anotherkey";
    static const WCHAR *some_value = "somevalue";
    static const WCHAR *other_value = "othervalue";
    static const WCHAR *another_value = "anothervalue";
    IMap_HSTRING_HSTRING iface;
    IIterable_IKeyValuePair_HSTRING_HSTRING *iterable_iface;
    IIterator_IKeyValuePair_HSTIRNG_HSTRING *iterator_iface;
    HRESULT hr;
    HSTRING key1, key2, key3, value1, value2, value3;
    HSTRING all_declared[] = {key1, key2, key3, value1, value2, value3};
    BOOLEAN replaced;

    hr = WindowsCreateString(some_key, wcslen(some_key), &key1);
    ok(hr == S_OK, "WindowsCreateString failed, hr %#lx.\n", hr);

    hr = WindowsCreateString(another_key, wcslen(another_key), &key2);
    ok(hr == S_OK, "WindowsCreateString failed, hr %#lx.\n", hr);

    hr = WindowsCreateString(other_key, wcslen(other_key), &key3);
    ok(hr == S_OK, "WindowsCreateString failed, hr %#lx.\n", hr);

    hr = WindowsCreateString(some_value, wcslen(some_value), &value1);
    ok(hr == S_OK, "WindowsCreateString failed, hr %#lx.\n", hr);

    hr = WindowsCreateString(another_value, wcslen(another_value), &value2);
    ok(hr == S_OK, "WindowsCreateString failed, hr %#lx.\n", hr);

    hr = WindowsCreateString(other_value, wcslen(other_value), &value3);
    ok(hr == S_OK, "WindowsCreateString failed, hr %#lx.\n", hr);

    // Prepare IMap
    hr = rbtree_map_create_HSTRING_HSTRING(&iface);
    ok(hr == S_OK, "IMap constructor failed, hr %#lx.\n", hr);

    hr = IInspectable_QueryInterface(&iface, IID_IIterable_IKeyValuePair_HSTRING_HSTRING, (void**) &iterable_iface);
    ok(hr == S_OK, "IIterable interface query failed, hr %#lx.\n", hr);

    hr = IMap_HSTRING_HSTRING_Insert(&iface, key1, value1, &replaced);
    ok(hr == S_OK, "Insert of (key1, value1): failed, hr %#lx.\n", hr);

    hr = IMap_HSTRING_HSTRING_Insert(&iface, key2, value2, &replaced);
    ok(hr == S_OK, "Insert of (key2, value2): failed, hr %#lx.\n", hr);

    hr = IMap_HSTRING_HSTRING_Insert(&iface, key4, value4, &replaced);
    ok(hr == S_OK, "Insert of (key3, value3): failed, hr %#lx.\n", hr);

    // Iterable
    hr = IIterable_IKeyValuePair_HSTRING_HSTRING_First(iterable_iface, &iiterator_iface);
    ok(hr == S_OK, "First failed, hr %#lx.\n", hr);

    IInspectable_Release(&iface);
    IInspectable_Release(&iterable_iface);
    IInspectable_Release(&iiterator_iface);
    for (int i = 0; i < sizeof(all_declared) / sizeof(HSTRING); i++) {
        WindowsDeleteString(all_declared[i]);
    }
}

static void test_MapView(void) 
{
    // TODO
}