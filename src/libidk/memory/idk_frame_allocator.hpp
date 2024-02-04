#pragma once

#include "common.hpp"
#include "../idk_assert.hpp"


namespace idk
{
    class internal_frame_allocator;

    template <typename T>
    class frame_allocator;
}


template <typename T>
class idk::frame_allocator
{
public:
    using value_type = T;

private:
    static constexpr size_t CAPACITY = 128 * idk::KILO;
    uint32_t idk_alloc_type = idk::internal::ALLOC_FRAME;

    uint8_t *&baseptr;
    size_t   &tail;
    size_t    capacity;

public:
    frame_allocator()
    :   baseptr (idk::internal::memory_baseptr(idk_alloc_type)),
        tail    (idk::internal::memory_tail(idk_alloc_type)),
        capacity(idk::internal::memory_capacity(idk_alloc_type))
    {
        
    };

    T*    allocate   ( size_t n );
    void  deallocate ( T*, size_t ) {  };
    void  reset() { tail = 0; };
};




template <typename T>
T *
idk::frame_allocator<T>::allocate( size_t n )
{
    size_t nbytes = n * sizeof(T);

    IDK_ALLOC_ASSERT(__FILE__, nbytes, capacity);

    if (tail + nbytes >= capacity)
    {
        tail = 0;
    }

    return reinterpret_cast<T *>(baseptr + tail);

}

