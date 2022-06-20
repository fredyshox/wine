/*
 * Unit test suite for Rtl* Version API functions
 *
 * Copyright 2022 Kacper Rączy
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "ntdll_test.h"
#include "wine/test.h"

static const WCHAR DeviceForms[][32] = {
    L"Unknown", L"Phone", L"Tablet", L"Desktop", L"Notebook", 
    L"Convertible", L"Detachable", L"All-in-One", L"Stick PC", L"Puck", 
    L"Surface Hub", L"Head-mounted display", L"Industry handheld", L"Industry tablet", L"Banking", 
    L"Building automation", L"Digital signage", L"Gaming", L"Home automation", L"Industrial automation",
    L"Kiosk", L"Maker board", L"Medical", L"Networking", L"Point of Service", 
    L"Printing", L"Thin client", L"Toy", L"Vending", L"Industry other"
};

static void test_RtlGetDeviceFamilyInfoEnum(void) 
{
    DWORD family, form;
    ULONGLONG uap;
    RTL_OSVERSIONINFOEXW version;
    
    RtlGetVersion(&version);
    RtlGetDeviceFamilyInfoEnum(&uap, &family, &form);
    ok( ((uap >> 48) & 0xffff) == version.dwMajorVersion, 
        "First 16-bit chunk of UAP does not match major system version %llx\n", uap );
    ok( ((uap >> 32) & 0xffff) == version.dwMinorVersion, 
        "Second 16-bit chunk of UAP does not match minor system version %llx\n", uap );
    ok( ((uap >> 16) & 0xffff) == version.dwBuildNumber, 
        "Third 16-bit chunk of UAP does not match build number %llx\n", uap );
    ok( family <= DEVICEFAMILYINFOENUM_MAX, 
        "Device family is not valid: %lx\n", family );
    ok( form <= DEVICEFAMILYDEVICEFORM_MAX, 
        "Device form is not valid: %lx\n", form );
}

static void test_RtlConvertDeviceFamilyInfoToString(void) 
{
    DWORD family_bufsize = 0, form_bufsize = 0;
    WCHAR *family, *form;
    BOOL form_valid = FALSE;

    RtlConvertDeviceFamilyInfoToString(&family_bufsize, &form_bufsize, NULL, NULL);
    ok( family_bufsize == sizeof(WCHAR) * 16, /* Windows.Desktop length */
        "Device family bufsize does not match: %lu\n", family_bufsize );
    ok( form_bufsize > 0, "Device form bufsize is invalid: %lu\n", form_bufsize );

    family = (WCHAR*)malloc(family_bufsize);
    form = (WCHAR*)malloc(form_bufsize);
    RtlConvertDeviceFamilyInfoToString(&family_bufsize, &form_bufsize, family, form);
    ok( wcscmp(family, L"Windows.Desktop") == 0,
        "Device family string is not equal to Windows.Desktop: %ls\n", family );
    /* Device form depends on OEM setting in registry, 
     * lets check all possible values to make it work on Windows */
    for (int i = 0; i < sizeof(DeviceForms) / sizeof(WCHAR*); i++) {
        if (wcscmp(form, DeviceForms[i]) == 0) {
            form_valid = TRUE;
            break;
        }
    }
    ok( form_valid, "Device form string is not valid or known: %ls\n", form);

    free(family);
    free(form);
}

START_TEST(version) 
{
    test_RtlGetDeviceFamilyInfoEnum();
    test_RtlConvertDeviceFamilyInfoToString();
}
