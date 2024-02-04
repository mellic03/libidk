#pragma once

#include <cstdint>
#include <cstddef>
#include <stack>

#include "idk_assert.hpp"
#include "idk_memory.hpp"
#include "idk_vector.hpp"


namespace idk
{
    template <typename T, size_t capacity>
    class block_allocator;
};


template <typename T, size_t capacity>
class idk::block_allocator
{
public:
    using value_type = T;


private:
    size_t              m_capacity = capacity;
    idk::vector<size_t> m_free_blocks;
    idk::vector<T>      m_data;
    bool                m_unloaded = false;


public:

    block_allocator()
    {
        m_data.resize(m_capacity);

        for (size_t i=0; i<m_capacity; i++)
        {
            m_free_blocks.push_back(i);
        }
    };

    T*      allocate( size_t n );
    void    deallocate( T*, size_t );

};




template <typename T, size_t capacity>
T *
idk::block_allocator<T, capacity>::allocate( size_t n )
{
    IDK_ASSERT("[idk::block_allocator] Out of memory!", m_free_blocks.size() > 0);

    T *baseptr = m_data.data();

    size_t idx = m_free_blocks.back();
                 m_free_blocks.pop_back();

    return new (&baseptr[idx]) T();
}



template <typename T, size_t capacity>
void
idk::block_allocator<T, capacity>::deallocate( T *data, size_t n )
{
    T *ptr = data;
    size_t idx = ptr - m_data.data();

    for (size_t i=0; i<n; i++)
    {
        m_free_blocks.push_back(idx + i);
    }
}

