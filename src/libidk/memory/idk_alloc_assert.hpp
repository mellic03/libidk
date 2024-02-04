#pragma once

#include "../idk_export.hpp"

#include <cstdint>
#include <cstddef>


namespace idk::internal
{
    IDK_VISIBLE
    void alloc_assert_msg( const char *file, size_t nbytes, size_t capacity );
};


#ifdef IDK_DEBUG
    #define IDK_ALLOC_ASSERT( file, nbytes, capacity ) \
    idk::internal::alloc_assert_msg(file, nbytes, capacity)

#else
    #define IDK_ALLOC_ASSERT( file, nbytes, capacity )
#endif

