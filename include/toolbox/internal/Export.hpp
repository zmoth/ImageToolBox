#pragma once

#include "Compiler.hpp"
#include "OperatingSystem.hpp"

#ifdef PROJECT_DLL_PLATFORM_WINDOWS
#define PROJECT_DLL_EXPORT __declspec(dllexport)
#define PROJECT_DLL_IMPORT __declspec(dllimport)
#define PROJECT_DLL_LOCAL
#elif PROJECT_DLL_COMPILER_GNU_VERSION_MAJOR >= 4 || \
    defined(PROJECT_DLL_COMPILER_CLANG)
#define PROJECT_DLL_EXPORT __attribute__((visibility("default")))
#define PROJECT_DLL_IMPORT __attribute__((visibility("default")))
#define PROJECT_DLL_LOCAL __attribute__((visibility("hidden")))
#else
#define PROJECT_DLL_EXPORT
#define PROJECT_DLL_IMPORT
#define PROJECT_DLL_LOCAL
#endif

#ifdef __cplusplus
#define PROJECT_DLL_DEMANGLED extern "C"
#else
#define PROJECT_DLL_DEMANGLED
#endif

#if defined(PROJECT_DLL_SHARED) && !defined(PROJECT_DLL_STATIC)
#ifdef PROJECT_DLL_EXPORTS
#define PROJECT_DLL_PUBLIC PROJECT_DLL_EXPORT
#else
#define PROJECT_DLL_PUBLIC PROJECT_DLL_IMPORT
#endif
#define PROJECT_DLL_PRIVATE PROJECT_DLL_LOCAL
#elif !defined(PROJECT_DLL_SHARED) && defined(PROJECT_DLL_STATIC)
#define PROJECT_DLL_PUBLIC
#define PROJECT_DLL_PRIVATE
#elif defined(PROJECT_DLL_SHARED) && defined(PROJECT_DLL_STATIC)
#ifdef PROJECT_DLL_EXPORTS
#error "Cannot build as shared and static simultaneously."
#else
#error "Cannot link against shared and static simultaneously."
#endif
#else
#ifdef PROJECT_DLL_EXPORTS
#error "Choose whether to build as shared or static."
#else
#error "Choose whether to link against shared or static."
#endif
#endif
