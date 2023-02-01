#pragma once

#if defined(__CYGWIN__) || defined(__CYGWIN32__)
#define PROJECT_DLL_PLATFORM "Cygwin"
#define PROJECT_DLL_PLATFORM_CYGWIN
#define PROJECT_DLL_PLATFORM_UNIX
#define PROJECT_DLL_PLATFORM_WINDOWS
#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || \
    defined(__TOS_WIN__) || defined(__WINDOWS__)
#define PROJECT_DLL_PLATFORM "Windows"
#define PROJECT_DLL_PLATFORM_WINDOWS
#elif defined(macintosh) || defined(Macintosh) || defined(__TOS_MACOS__) || \
    (defined(__APPLE__) && defined(__MACH__))
#define PROJECT_DLL_PLATFORM "Mac"
#define PROJECT_DLL_PLATFORM_MAC
#define PROJECT_DLL_PLATFORM_UNIX
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__TOS_LINUX__)
#define PROJECT_DLL_PLATFORM "Linux"
#define PROJECT_DLL_PLATFORM_LINUX
#define PROJECT_DLL_PLATFORM_UNIX
#elif defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__bsdi__) || \
    defined(__DragonFly__)
#define PROJECT_DLL_PLATFORM "BSD"
#define PROJECT_DLL_PLATFORM_BSD
#define PROJECT_DLL_PLATFORM_UNIX
#elif defined(sun) || defined(__sun)
#define PROJECT_DLL_PLATFORM "Solaris"
#define PROJECT_DLL_PLATFORM_SOLARIS
#define PROJECT_DLL_PLATFORM_UNIX
#elif defined(_AIX) || defined(__TOS_AIX__)
#define PROJECT_DLL_PLATFORM "AIX"
#define PROJECT_DLL_PLATFORM_AIX
#define PROJECT_DLL_PLATFORM_UNIX
#elif defined(hpux) || defined(_hpux) || defined(__hpux)
#define PROJECT_DLL_PLATFORM "HPUX"
#define PROJECT_DLL_PLATFORM_HPUX
#define PROJECT_DLL_PLATFORM_UNIX
#elif defined(__QNX__)
#define PROJECT_DLL_PLATFORM "QNX"
#define PROJECT_DLL_PLATFORM_QNX
#define PROJECT_DLL_PLATFORM_UNIX
#elif defined(unix) || defined(__unix) || defined(__unix__)
#define PROJECT_DLL_PLATFORM "Unix"
#define PROJECT_DLL_PLATFORM_UNIX
#endif

#ifndef PROJECT_DLL_PLATFORM
#error "Current platform is not supported."
#endif
