#define COBJMACROS
#include <stdarg.h>

#include "windef.h"
#include "winbase.h"
#include "winerror.h"
#include "winstring.h"

#include "initguid.h"
#include "roapi.h"

#define WIDL_using_Windows_Foundation
#define WIDL_using_Windows_Foundation_Collections
#include "windows.foundation.h"
#include "windows.foundation.collections.h"
#include "windows.foundation.collections.map.h"

#include "map_inspectable_inspectable.h"
#include "map_hstring_hstring.h"

#include "wine/test.h"

static void test_MapReadWrite(void) 
{
    static const WCHAR *some_key = L"somekey";
    static const WCHAR *other_key = L"otherkey";
    static const WCHAR *another_key = L"anotherkey";
    static const WCHAR *and_another_key = L"andanotherkey";
    static const WCHAR *some_value = L"somevalue";
    static const WCHAR *other_value = L"othervalue";
    static const WCHAR *another_value = L"anothervalue";
    static const WCHAR *and_another_value = L"andanothervalue";
    IMap_HSTRING_HSTRING *iface;
    HRESULT hr;
    HSTRING key1, key2, key3, key4, value1, value2, value3, value4;
    HSTRING rvalue = NULL;
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
    hr = rbtree_map_create_HSTRING_HSTRING(&iface, NULL);
    ok(hr == S_OK, "IMap constructor failed, hr %#lx.\n", hr);

    hr = IMap_HSTRING_HSTRING_get_Size(iface, &size);
    ok(hr == S_OK, "get_Size failed, hr %#lx.\n", hr);
    ok(size == 0, "Newly created map not empty, size: %d.\n", size);

    // Insert
    hr = IMap_HSTRING_HSTRING_Insert(iface, key1, value1, &replaced);
    ok(hr == S_OK, "Insert of (key1, value1): failed, hr %#lx.\n", hr);
    ok(!replaced, "Insert of (key1, value1): replacement reported.\n", hr);

    hr = IMap_HSTRING_HSTRING_Insert(iface, key2, value2, &replaced);
    ok(hr == S_OK, "Insert of (key2, value2): failed, hr %#lx.\n", hr);
    ok(!replaced, "Insert of (key2, value2): replacement reported.\n", hr);

    hr = IMap_HSTRING_HSTRING_Insert(iface, key4, value4, &replaced);
    ok(hr == S_OK, "Insert of (key4, value4): failed, hr %#lx.\n", hr);
    ok(!replaced, "Insert of (key4, value4): replacement reported.\n", hr);

    // Insert + replace
    hr = IMap_HSTRING_HSTRING_Insert(iface, key4, value3, &replaced);
    ok(hr == S_OK, "Insert of (key4, value3): failed, hr %#lx.\n", hr);
    ok(replaced, "Insert of (key4, value3): replacement not reported.\n", hr);
    
    // HasKey
    hr = IMap_HSTRING_HSTRING_HasKey(iface, key1, &exist);
    ok(hr == S_OK, "HasKey of (key1): failed, hr %#lx.\n", hr);
    ok(exist, "key1 not in map, but should be.\n", hr);

    hr = IMap_HSTRING_HSTRING_HasKey(iface, key2, &exist);
    ok(hr == S_OK, "HasKey of (key2): failed, hr %#lx.\n", hr);
    ok(exist, "key2 not in map, but should be.\n", hr);

    hr = IMap_HSTRING_HSTRING_HasKey(iface, key4, &exist);
    ok(hr == S_OK, "HasKey of (key4): failed, hr %#lx.\n", hr);
    ok(exist, "key2 not in map, but should be.\n", hr);

    hr = IMap_HSTRING_HSTRING_HasKey(iface, key3, &exist);
    ok(hr == S_OK, "HasKey of (key3): failed, hr %#lx.\n", hr);
    ok(!exist, "key3 in map, but should not be.\n", hr);

    hr = IMap_HSTRING_HSTRING_get_Size(iface, &size);
    ok(hr == S_OK, "get_Size failed, hr %#lx.\n", hr);
    ok(size == 3, "Map with presumed 2 keys has invalid size, size: %d.\n", size);

    // Lookup
    hr = IMap_HSTRING_HSTRING_Lookup(iface, key1, &rvalue);
    ok(hr == S_OK, "Lookup of (key1): failed, hr %#lx.\n", hr);
    ok(rvalue != NULL, "Lookup of (key1): rvalue is NULL.\n", hr);
    WindowsCompareStringOrdinal(rvalue, value1, &eq);
    ok(eq == 0, "Lookup of (key1): rvalue not equal value1.\n", hr);
    WindowsDeleteString(rvalue);

    hr = IMap_HSTRING_HSTRING_Lookup(iface, key2, &rvalue);
    ok(hr == S_OK, "Lookup of (key2): failed, hr %#lx.\n", hr);
    ok(rvalue != NULL, "Lookup of (key2): rvalue is NULL.\n", hr);
    WindowsCompareStringOrdinal(rvalue, value2, &eq);
    ok(eq == 0, "Lookup of (key2): rvalue not equal value1.\n", hr);
    WindowsDeleteString(rvalue);
    
    hr = IMap_HSTRING_HSTRING_Lookup(iface, key3, &rvalue);
    ok(hr == E_BOUNDS, "Lookup of (key3): failed, hr %#lx.\n", hr);

    // Remove
    hr = IMap_HSTRING_HSTRING_Remove(iface, key4);
    ok(hr == S_OK, "Remove of (key4) failed, hr %#lx.\n", hr);

    hr = IMap_HSTRING_HSTRING_HasKey(iface, key4, &exist);
    ok(hr == S_OK, "HasKey of (key4): failed, hr %#lx.\n", hr);
    ok(!exist, "key4 in map, but should not be.\n", hr);

    hr = IMap_HSTRING_HSTRING_get_Size(iface, &size);
    ok(hr == S_OK, "get_Size failed, hr %#lx.\n", hr);
    ok(size == 2, "Invalid size after key removal, size: %d.\n", size);

    // Clear
    hr = IMap_HSTRING_HSTRING_Clear(iface);
    ok(hr == S_OK, "Clear failed, hr %#lx.\n", hr);

    hr = IMap_HSTRING_HSTRING_get_Size(iface, &size);
    ok(hr == S_OK, "get_Size failed, hr %#lx.\n", hr);
    ok(size == 0, "Cleared map not empty, size: %d.\n", size);

    IInspectable_Release(iface);
    HSTRING all_declared[] = {key1, key2, key3, value1, value2, value3};
    for (int i = 0; i < sizeof(all_declared) / sizeof(HSTRING); i++) {
        WindowsDeleteString(all_declared[i]);
    }
}

static void test_MapIterable(void) 
{
    static const WCHAR *some_key = L"somekey";
    static const WCHAR *other_key = L"otherkey";
    static const WCHAR *another_key = L"anotherkey";
    static const WCHAR *some_value = L"somevalue";
    static const WCHAR *other_value = L"othervalue";
    static const WCHAR *another_value = L"anothervalue";
    IMap_HSTRING_HSTRING* iface;
    IIterable_IKeyValuePair_HSTRING_HSTRING *iterable_iface;
    IIterator_IKeyValuePair_HSTRING_HSTRING *iterator_iface;
    IKeyValuePair_HSTRING_HSTRING *keyvaluepair_iface;
    IKeyValuePair_HSTRING_HSTRING *multi_keyvaluepair_iface[3];
    HRESULT hr;
    HSTRING key1, key2, key3, value1, value2, value3;
    UINT32 size; 
    BOOLEAN replaced;
    BOOL has_current;

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
    hr = rbtree_map_create_HSTRING_HSTRING(&iface, NULL);
    ok(hr == S_OK, "IMap constructor failed, hr %#lx.\n", hr);

    hr = IInspectable_QueryInterface(iface, &IID_IIterable_IKeyValuePair_HSTRING_HSTRING, (void**) &iterable_iface);
    ok(hr == S_OK, "IIterable interface query failed, hr %#lx.\n", hr);

    hr = IMap_HSTRING_HSTRING_Insert(iface, key1, value1, &replaced);
    ok(hr == S_OK, "Insert of (key1, value1): failed, hr %#lx.\n", hr);

    hr = IMap_HSTRING_HSTRING_Insert(iface, key2, value2, &replaced);
    ok(hr == S_OK, "Insert of (key2, value2): failed, hr %#lx.\n", hr);

    hr = IMap_HSTRING_HSTRING_Insert(iface, key3, value3, &replaced);
    ok(hr == S_OK, "Insert of (key3, value3): failed, hr %#lx.\n", hr);

    // IIterable
    hr = IIterable_IKeyValuePair_HSTRING_HSTRING_First(iterable_iface, &iterator_iface);
    ok(hr == S_OK, "First failed, hr %#lx.\n", hr);
    ok(iterator_iface != NULL, "IIterator is null.'n");

    // IIterator 

    for (int i = 0; i < 3; i++) {
        hr = IIterator_IKeyValuePair_HSTRING_HSTRING_get_HasCurrent(iterator_iface, &has_current);
        ok(hr == S_OK, "HasCurrent failed, hr %#lx.\n", hr);
        ok(has_current, "HasCurrent returns false, but should true.\n");

        hr = IIterator_IKeyValuePair_HSTRING_HSTRING_get_Current(iterator_iface, &keyvaluepair_iface);
        ok(hr == S_OK, "get_Current failed, hr %#lx.\n", hr);

        hr = IIterator_IKeyValuePair_HSTRING_HSTRING_MoveNext(iterator_iface, &has_current);
        ok(hr == S_OK, "MoveNext failed, hr %#lx.\n", hr);
        ok(i >= 2 || has_current, "MoveNext reported there's no more values.\n");

        IInspectable_Release(keyvaluepair_iface);
    }

    // IIterator GetMany

    IInspectable_Release(iterator_iface);
    hr = IIterable_IKeyValuePair_HSTRING_HSTRING_First(iterable_iface, &iterator_iface);
    ok(hr == S_OK, "First failed, hr %#lx.\n", hr);
    ok(iterator_iface != NULL, "IIterator is null.'n");

    hr = IIterator_IKeyValuePair_HSTRING_HSTRING_GetMany(iterator_iface, 3, &multi_keyvaluepair_iface, &size);
    ok(hr == S_OK, "GetMany failed, hr %#lx.\n", hr);
    ok(size == 3, "Get Many invalid reported size, %d.\n", size);

    // Cleanup
    for (int i = 0; i < size; i++) {
        IInspectable_Release(multi_keyvaluepair_iface[i]);
    }
    IInspectable_Release(iface);
    IInspectable_Release(iterable_iface);
    IInspectable_Release(iterator_iface);

    HSTRING all_declared[] = {key1, key2, key3, value1, value2, value3};
    for (int i = 0; i < sizeof(all_declared) / sizeof(HSTRING); i++) {
        WindowsDeleteString(all_declared[i]);
    }
}

static void test_MapView(void) 
{
    static const WCHAR *some_key = L"somekey";
    static const WCHAR *other_key = L"otherkey";
    static const WCHAR *another_key = L"anotherkey";
    static const WCHAR *some_value = L"somevalue";
    static const WCHAR *other_value = L"othervalue";
    static const WCHAR *another_value = L"anothervalue";
    IMap_HSTRING_HSTRING* iface;
    IMapView_HSTRING_HSTRING *view_iface;
    HRESULT hr;
    HSTRING key1, key2, key3, value1, value2, value3;
    HSTRING rvalue = NULL;
    UINT32 size;
    INT32 eq;
    BOOLEAN replaced, exist;

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

    /* Prepare IMap */
    hr = rbtree_map_create_HSTRING_HSTRING(&iface, NULL);
    ok(hr == S_OK, "IMap constructor failed, hr %#lx.\n", hr);

    hr = IInspectable_QueryInterface(iface, &IID_IMapView_HSTRING_HSTRING, (void**) &view_iface);
    ok(hr == S_OK, "IIterable interface query failed, hr %#lx.\n", hr);

    hr = IMap_HSTRING_HSTRING_Insert(iface, key1, value1, &replaced);
    ok(hr == S_OK, "Insert of (key1, value1): failed, hr %#lx.\n", hr);

    hr = IMap_HSTRING_HSTRING_Insert(iface, key2, value2, &replaced);
    ok(hr == S_OK, "Insert of (key2, value2): failed, hr %#lx.\n", hr);

    hr = IMap_HSTRING_HSTRING_Insert(iface, key3, value3, &replaced);
    ok(hr == S_OK, "Insert of (key3, value3): failed, hr %#lx.\n", hr);

    /* IMapView */
    hr = IMap_HSTRING_HSTRING_GetView(iface, &view_iface);
    ok(hr == S_OK, "First failed, hr %#lx.\n", hr);
    ok(view_iface != NULL, "IIterator is null.'n");

    hr = IMapView_HSTRING_HSTRING_HasKey(view_iface, key1, &exist);
    ok(hr == S_OK, "HasKey of (key1): failed, hr %#lx.\n", hr);
    ok(exist, "key1 not in map, but should be.\n", hr);

    hr = IMapView_HSTRING_HSTRING_HasKey(view_iface, key2, &exist);
    ok(hr == S_OK, "HasKey of (key2): failed, hr %#lx.\n", hr);
    ok(exist, "key2 not in map, but should be.\n", hr);

    hr = IMapView_HSTRING_HSTRING_HasKey(view_iface, key3, &exist);
    ok(hr == S_OK, "HasKey of (key3): failed, hr %#lx.\n", hr);
    ok(exist, "key3 not in map, but should be.\n", hr);

    hr = IMapView_HSTRING_HSTRING_Lookup(view_iface, key1, &rvalue);
    ok(hr == S_OK, "Lookup of (key1): failed, hr %#lx.\n", hr);
    ok(rvalue != NULL, "Lookup of (key1): rvalue is NULL.\n", hr);
    WindowsCompareStringOrdinal(rvalue, value1, &eq);
    ok(eq == 0, "Lookup of (key1): rvalue not equal value1.\n", hr);
    WindowsDeleteString(rvalue);

    hr = IMapView_HSTRING_HSTRING_Lookup(view_iface, key2, &rvalue);
    ok(hr == S_OK, "Lookup of (key2): failed, hr %#lx.\n", hr);
    ok(rvalue != NULL, "Lookup of (key2): rvalue is NULL.\n", hr);
    WindowsCompareStringOrdinal(rvalue, value2, &eq);
    ok(eq == 0, "Lookup of (key2): rvalue not equal value1.\n", hr);
    WindowsDeleteString(rvalue);
    
    hr = IMapView_HSTRING_HSTRING_Lookup(view_iface, key3, &rvalue);
    ok(hr == S_OK, "Lookup of (key3): failed, hr %#lx.\n", hr);
    ok(rvalue != NULL, "Lookup of (key3): rvalue is NULL.\n", hr);
    WindowsCompareStringOrdinal(rvalue, value3, &eq);
    ok(eq == 0, "Lookup of (key3): rvalue not equal value1.\n", hr);
    WindowsDeleteString(rvalue);

    /* Cleanup */
    IInspectable_Release(iface);
    IInspectable_Release(view_iface);

    HSTRING all_declared[] = {key1, key2, key3, value1, value2, value3};
    for (int i = 0; i < sizeof(all_declared) / sizeof(HSTRING); i++) {
        WindowsDeleteString(all_declared[i]);
    }
}

START_TEST(map)
{
    test_MapReadWrite();
    test_MapIterable();
    test_MapView();
}
