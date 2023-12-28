#include "idk_assert.hpp"

#include <iostream>
#include <cassert>


void
idk::internal::assert_msg( const char *msg, const bool expression )
{
    if (!(expression))
    {
        std::cerr
            << "Assertion failed: " << "\"" << msg << "\"\n"
            << __FILE__ << ":" << __LINE__ << "\n";

        assert(false);
    }

}
