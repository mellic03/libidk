#pragma once
#include "base_allocator.hpp"

namespace idk
{
    template <typename T>
    class cringe_ptr;
}


template <typename T>
class idk::cringe_ptr
{
private:
    base_allocator *m_allocator;
    T *m_data;

public:
    cringe_ptr( size_t count, base_allocator *A )
    :   m_allocator(A)
    {
        // std::cout << "[cringe_ptr::cringe_ptr]" << std::endl;
        m_data = static_cast<T*>(m_allocator->alloc(count*sizeof(T), alignof(T)));
        // std::construct_at(m_data);
        m_data = new (m_data) T();
    }

    ~cringe_ptr()
    {
        // std::cout << "[cringe_ptr::~cringe_ptr]" << std::endl;
        m_allocator->free(m_data);
    }

    constexpr T *get()
    {
        return m_data;
    };

};
