#include "idk_assert.hpp"
#include "idk_log2.hpp"

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

        LOG_ERROR("idk::internal::assert_msg", msg);
        idk::Logger2::print();
        idk::Logger2::writeFile();

        assert(false);
    }

}
