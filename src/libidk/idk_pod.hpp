#pragma once


#include "idk_platform.hpp"
#include "idk_vector.hpp"



#ifdef IDK_CPP20
    #include <concepts>

    namespace idk
    {
        template <typename T>
        concept IsPOD = std::is_trivial_v<T> && std::is_standard_layout_v<T>;
    };
#endif


namespace idk
{
    #ifdef IDK_CPP20
        #define requires_IsPOD(T) requires idk::IsPOD<T>
    #else
        #define requires_IsPOD(T)
    #endif


    template <typename T>
    T pod_ctor() { return T(); };

    template <typename T, typename ...Args>
    T pod_ctor( Args ...args ) { return T(); };

    template <typename T>
    void pod_dtor(T&) {  };
};

