/**
 * @file version.h
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#ifndef __MY_VERSION_HEADER_FILE__
#define __MY_VERSION_HEADER_FILE__
////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif
    ////////////////////////////////////////////////////

#include <gen/git_version.h>

#ifndef _VERSION_HELPER_MAKE_ULONG64
#define _VERSION_HELPER_MAKE_ULONG64(low, high)                                                                        \
    ((ULONG64)(((ULONG)((ULONG64)(low)&0xffffffff)) | ((ULONG64)((ULONG)((ULONG64)(high)&0xffffffff))) << 32))
#endif // #ifndef _VERSION_HELPER_MAKE_ULONG64

#ifndef _VERSION_HELPER_MAKE_ULONG
#define _VERSION_HELPER_MAKE_ULONG(low, high)                                                                          \
    ((ULONG)(((USHORT)((ULONG_PTR)(low)&0xffff)) | ((ULONG)((USHORT)((ULONG_PTR)(high)&0xffff))) << 16))
#endif // #ifndef _VERSION_HELPER_MAKE_ULONG

#ifndef _VERSION_HELPER_MAKE_USHORT
#define _VERSION_HELPER_MAKE_USHORT(low, high) ((USHORT)(((UCHAR)(low)) | ((USHORT)((UCHAR)(high))) << 8))
#endif // #ifndef _VERSION_HELPER_MAKE_USHORT

#ifndef _VERSION_HELPER_MAKE_VERSION
#define _VERSION_HELPER_MAKE_VERSION(v1, v2, v3, v4)                                                                   \
    _VERSION_HELPER_MAKE_ULONG64(_VERSION_HELPER_MAKE_ULONG(v4, v3), _VERSION_HELPER_MAKE_ULONG(v2, v1))
#endif // #ifndef _VERSION_HELPER_MAKE_VERSION

// Version
#ifndef _VERSION_HELPER_MARCO_STRING_2
#define _VERSION_HELPER_MARCO_STRING_2(x) #x
#endif // _VERSION_HELPER_MARCO_STRING_2

#ifndef _VERSION_HELPER_MARCO_STRING
#define _VERSION_HELPER_MARCO_STRING(x) _VERSION_HELPER_MARCO_STRING_2(x)
#endif // _VERSION_HELPER_MARCO_STRING

    //////////////////////////////////////////////////////////////////////////

#define MY_VERSION_MAJOR 0

#define MY_VERSION_MINOR 0

#define MY_BANNER   "Windbg javascript extension for hacker , a gift from tinysec.\n"

#define MY_VERSION_PART_1 MY_VERSION_MAJOR

#define MY_VERSION_PART_2 MY_VERSION_MINOR

#define MY_VERSION_PART_3 0

#define MY_VERSION_PART_4 1001

    //////////////////////////////////////////////////////////////////////////

#define MY_VERSION_NUMBER                                                                                              \
    _VERSION_HELPER_MAKE_VERSION(MY_VERSION_PART_1, MY_VERSION_PART_2, MY_VERSION_PART_3, MY_VERSION_PART_4)

#define MY_VERSION_DOT_STRING                                                                                          \
    _VERSION_HELPER_MARCO_STRING(MY_VERSION_PART_1.MY_VERSION_PART_2.MY_VERSION_PART_3.MY_VERSION_PART_4)

#define MY_VERSION_COMMA_STRING MY_VERSION_PART_1, MY_VERSION_PART_2, MY_VERSION_PART_3, MY_VERSION_PART_4

#define MY_VERSION_INTERNALNAME "jswd.dll\0"

#if defined _WIN64

#ifdef _DEBUG
#define MY_VERSION_COMMENTS "jswd (amd64) (debug)\0"
#else
#define MY_VERSION_COMMENTS "jswd (amd64)\0"
#endif

#elif defined _ARM64_

#ifdef _DEBUG
#define MY_VERSION_COMMENTS "js (arm64) (debug)\0"
#else
#define MY_VERSION_COMMENTS "jswd (arm64)\0"
#endif

#else

#ifdef _DEBUG
#define MY_VERSION_COMMENTS "jswd (i386) (debug)\0"
#else
#define MY_VERSION_COMMENTS "jswd\0"
#endif

#endif // #ifdef _WIN64

#define MY_VERSION_COMPANYNAME "github.com/tinysec\0"

#define MY_VERSION_FILEDESCRIPTION MY_VERSION_COMMENTS

#define MY_VERSION_LEGALCOPYRIGHT "tinysec.net. All Rights Reserved\0"

#define MY_VERSION_LEGALTRADEMARKS "Powered by TinySec!\0"

#define MY_VERSION_PRODUCTNAME "jswd\0"

#define MY_VERSION_FILEVERSION MY_VERSION_DOT_STRING

#define MY_VERSION_ORIGINALFILENAME MY_VERSION_INTERNALNAME
#define MY_VERSION_PRIVATEBUILD MY_VERSION_DOT_STRING

#define MY_VERSION_PRODUCTVERSION MY_VERSION_DOT_STRING
#define MY_VERSION_SPECIALBUILD MY_VERSION_DOT_STRING

////////////////////////////////////////////////////
#ifdef __cplusplus
} // extern "C"
#endif
////////////////////////////////////////////////////
#endif //__MY_VERSION_HEADER_FILE__
