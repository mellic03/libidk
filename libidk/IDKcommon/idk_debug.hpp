#pragma once

#include <cassert>
#include <string>
#include <stdio.h>


namespace idk
{
    void idk_assert( const char *msg, const bool expression );
};


#ifdef IDK_DEBUG
    #define IDK_ASSERT( msg, expression ) (idk::idk_assert(msg, expression))
#else
    #define IDK_ASSERT( msg, expression ) ((void)(0))
#endif

