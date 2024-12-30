#pragma once


#ifdef __unix__
    #define IDK_UNIX
    #define IDK_DLIB_EXT ".so"
    #define IDK_ENTRY main

#elif defined(_WIN32) || defined(WIN32)
    #define IDK_WINDOWS
    #define IDK_DLIB_EXT ".dll"
    #define IDK_ENTRY WinMain

#endif




#if __cplusplus >= 201103L
    #define IDK_CPP11
#endif

#if __cplusplus >= 201402L
    #define IDK_CPP14
#endif

#if __cplusplus >= 201703L
    #define IDK_CPP17
#endif

#if __cplusplus >= 202002L
    #define IDK_CPP20
#endif

#if __cplusplus >= 202302L
    #define IDK_CPP23
#endif


