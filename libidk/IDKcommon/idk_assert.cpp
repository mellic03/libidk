#include "idk_assert.hpp"

#include <cstdio>
#include <cassert>


void
idk::internal::assert_msg( const char *msg, const bool expression )
{
    if (expression == false)
    {
        printf("Assertion failed: \"%s\"", msg);
    }

    assert(expression);
}
