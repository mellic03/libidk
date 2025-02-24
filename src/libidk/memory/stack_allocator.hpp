#pragma once
#include "linear_allocator.hpp"

namespace idk
{
    class stack_allocator: public idk::linear_allocator
    {
    private:
        struct node_type {
            void *tailptr;
            void *usrptr;
        } *m_top;

    public:
        using linear_allocator::linear_allocator;
        stack_allocator( size_t nbytes, void *baseptr=nullptr );

        virtual void *alloc( size_t nbytes, size_t alignment ) final;
        virtual void  free( void* ) final;
    };
}
