#pragma once

#include "common.hpp"


namespace idk
{
    template <typename T>
    class linear_allocator;
}


template <typename T>
class idk::linear_allocator
{
public:
    using value_type = T;

private:
    static constexpr size_t CAPACITY = 128 * idk::KILO;
    uint32_t idk_alloc_type = idk::internal::ALLOC_LINEAR;

    uint8_t *&baseptr;
    size_t   &tail;
    size_t   capacity;

public:
    linear_allocator()
    :   baseptr (idk::internal::memory_baseptr(idk_alloc_type)),
        tail    (idk::internal::memory_tail(idk_alloc_type)),
        capacity(idk::internal::memory_capacity(idk_alloc_type))
    {

    }

    T*    allocate   ( size_t n );
    void  deallocate ( T*, size_t ) {  };

};


template <typename T>
T *
idk::linear_allocator<T>::allocate( size_t n )
{
    size_t nbytes = n * sizeof(T);

    IDK_ALLOC_ASSERT(__FILE__, nbytes, capacity);

    if (tail >= capacity)
    {
        return nullptr;
    }

    tail += nbytes;

    return reinterpret_cast<T *>(baseptr + tail);

}

