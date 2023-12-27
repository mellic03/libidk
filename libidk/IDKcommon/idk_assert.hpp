#pragma once


namespace idk::internal
{
    void assert_msg( const char *msg, const bool expression );
};


#ifdef IDK_DEBUG
    #define IDK_ASSERT( msg, expression ) idk::internal::assert_msg(msg, expression)

#else
    #define IDK_ASSERT( msg, expression )
#endif

