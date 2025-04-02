#pragma once

#ifdef LG_DLL_EXPORTS
#define LG_DLL_API __declspec(dllexport)
#else
#define LG_DLL_API __declspec(dllimport)
#endif // LG_DLL_EXPORTS