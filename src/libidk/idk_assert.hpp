#pragma once

#include <iostream>
#include "idk_export.hpp"


namespace idk::internal
{
    IDK_VISIBLE
    void assert_msg( const char *msg, const bool expression );
};


// #ifdef IDK_DEBUG
    #define IDK_ASSERT( msg, expression ) idk::internal::assert_msg(msg, expression)

// #else
//     #define IDK_ASSERT( msg, expression )
// #endif



#define idk_printvalue(v) std::cout << #v << ": " << v << "\n"

