#pragma once


#ifdef __unix__
    #define IDK_UNIX
    #define IDK_ENTRY main

#elif defined(_WIN32) || defined(WIN32)
    #define IDK_WINDOWS
    #define IDK_ENTRY WinMain

#endif





