#pragma once
#include "common.hpp"
#include "base_allocator.hpp"
#include <atomic>


namespace idk
{
    class linear_allocator: public base_allocator
    {
    protected:
        size_t   m_capacity;
        uint8_t *m_base;
        uint8_t *m_tail;
        uint8_t *m_end;

        // std::atomic_size_t m_top;

    public:
        linear_allocator( size_t nbytes, base_allocator* );
        linear_allocator( size_t nbytes, void *baseptr=nullptr );
        ~linear_allocator();

        virtual void *alloc( size_t nbytes, size_t alignment ) override;
        virtual void  free( void* ) override;
        virtual void  clear() override;

    };
}


