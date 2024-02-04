#include "idk_alloc_assert.hpp"

#include <iostream>
#include <cassert>
#include <filesystem>


void idk::internal::alloc_assert_msg( const char *file, size_t nbytes, size_t capacity )
{
    std::string path = std::filesystem::path(file).stem();

    std::string msg  = "Allocation error in " + path + ".\n";
                msg += "Requested " + std::to_string(nbytes) + " bytes "; \
                msg += "of " + std::to_string(capacity) + " available"; \

    if (nbytes >= capacity)
    {
        std::cerr << msg << "\n";

        assert(false);
    }
}
