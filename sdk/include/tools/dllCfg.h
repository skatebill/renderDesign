//导入dll和导出dll用
#ifndef __MP_COMPLIE_CONFIGURE_H__
#define __MP_COMPLIE_CONFIGURE_H__

#ifdef DLL_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif 

// Declare the calling convention.
#if defined(_STDCALL_SUPPORTED)
#define DLLCALLCONV __stdcall
#else
#define DLLCALLCONV __cdecl
#endif

#endif