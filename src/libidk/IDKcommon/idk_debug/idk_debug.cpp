#include "idk_debug.hpp"


void idk::idk_assert( const char *msg, const bool expression )
{
    if (expression == false)
    {
        printf("Assertion failed: \"%s\"\n", msg);
    }

    assert(expression);
}

