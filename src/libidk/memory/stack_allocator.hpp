#pragma once

#include <cstdint>
#include <cstddef>
#include <stack>

namespace idk
{
    class stack_allocator;
}


class idk::stack_allocator
{
private:
    size_t   m_capacity;
    uint8_t *m_base;
    uint8_t *m_tail;
    uint8_t *m_end;

    struct private_type {
        uint8_t *tail;
        void    *usr;
    };

    std::stack<private_type> m_stack;

    uint8_t *align_ptr( uint8_t *ptr, size_t align )
    {
        size_t p = reinterpret_cast<size_t>(ptr);
        return reinterpret_cast<uint8_t*>((p + align - 1) & ~(align - 1));
    }

public:
    stack_allocator( size_t capacity );
    ~stack_allocator();

    void *alloc( size_t nbytes, size_t alignment );
    void  free( void *ptr );

    template <typename T>
    T *alloc( size_t n )
    {
        return static_cast<T*>(this->alloc(n*sizeof(T), alignof(T)));
    }

};



// template <typename T>
// class idk::stack_allocator
// {
// public:
//     using value_type = T;
//     inline static stack_allocator m_memblock;

// private:
//     T *m_base;
//     T *m_tail;

// public:
//     stack_allocator();
//     T *allocate( size_t n );
//     void deallocate( T*, size_t );
// };



// template <typename T>
// idk::stack_allocator<T>::stack_allocator()
// {

// }



// template <typename T>
// T*
// idk::stack_allocator<T>::allocate( size_t n )
// {
//     void *ptr = m_memblock.Allocate(n*sizeof(T), alignof(T));
//     return static_cast<T*>(ptr);
// }


// template <typename T>
// void
// idk::stack_allocator<T>::deallocate( T *ptr, size_t n )
// {
//     m_memblock.Free(static_cast<void*>(ptr));
// }



