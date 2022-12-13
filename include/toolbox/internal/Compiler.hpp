#pragma once

#if defined(__MINGW32__) || defined(__MINGW64__)
#define PROJECT_DLL_COMPILER "MinGW"
#define PROJECT_DLL_COMPILER_MINGW
#elif defined(__GNUC__)
#define PROJECT_DLL_COMPILER "GNU"
#define PROJECT_DLL_COMPILER_GNU
#define PROJECT_DLL_COMPILER_GNU_VERSION_MAJOR __GNUC__
#define PROJECT_DLL_COMPILER_GNU_VERSION_MINOR __GNUC_MINOR__
#define PROJECT_DLL_COMPILER_GNU_VERSION_PATCH __GNUC_PATCHLEVEL__
#elif defined(__clang__)
#define PROJECT_DLL_COMPILER "Clang"
#define PROJECT_DLL_COMPILER_CLANG
#elif defined(_MSC_VER)
#define PROJECT_DLL_COMPILER "Microsoft Visual C++"
#define PROJECT_DLL_COMPILER_MICROSOFT
#elif defined(__BORLANDC__)
#define PROJECT_DLL_COMPILER "Borland C++ Builder"
#define PROJECT_DLL_COMPILER_BORLAND
#elif defined(__CODEGEARC__)
#define PROJECT_DLL_COMPILER "CodeGear C++ Builder"
#define PROJECT_DLL_COMPILER_CODEGEAR
#elif defined(__INTEL_COMPILER) || defined(__ICL)
#define PROJECT_DLL_COMPILER "Intel C++"
#define PROJECT_DLL_COMPILER_INTEL
#elif defined(__xlC__) || defined(__IBMCPP__)
#define PROJECT_DLL_COMPILER "IBM XL C++"
#define PROJECT_DLL_COMPILER_IBM
#elif defined(__HP_aCC)
#define PROJECT_DLL_COMPILER "HP aC++"
#define PROJECT_DLL_COMPILER_HP
#elif defined(__WATCOMC__)
#define PROJECT_DLL_COMPILER "Watcom C++"
#define PROJECT_DLL_COMPILER_WATCOM
#endif

#ifndef PROJECT_DLL_COMPILER
#error "Current compiler is not supported."
#endif
