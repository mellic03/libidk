#pragma once
#include "linear_allocator.hpp"


namespace idk
{
    class ring_allocator: public idk::linear_allocator
    {
    public:
        using linear_allocator::linear_allocator;
        virtual void *alloc( size_t nbytes, size_t alignment ) final;
    };
}

