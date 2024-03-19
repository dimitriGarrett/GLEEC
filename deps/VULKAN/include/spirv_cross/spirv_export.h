#pragma once

#ifdef _WIN32
#ifdef SPIRV_API_EXPORT
#define SPIRV_EXPORT_API __declspec(dllexport)
#else
#define SPIRV_EXPORT_API __declspec(dllimport)
#endif
#else
#define SPIRV_EXPORT_API
#endif