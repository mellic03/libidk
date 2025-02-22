#pragma once

#include "stack_ptr.hpp"
#include "../idk_log.hpp"

namespace idk
{
    template <typename T>
    class tmp_vector;
}


template <typename T>
class idk::tmp_vector
{
private:
    size_t m_size, m_cap;
    idk::stack_ptr m_stack;
    T *m_data;

public:

    tmp_vector( size_t size, size_t capacity )
    :   m_size  (size),
        m_cap   (capacity),
        m_stack (idk::stack_ptr(capacity*sizeof(T), alignof(T)))
    {
        m_data = static_cast<T*>(m_stack.get());
    }

    void push( const T &data )
    {
        m_data[m_size++] = data;
    }

    void pop()
    {
        this->back().~T();
        m_size--;
    }

    constexpr T &front() noexcept { return m_data[0]; }
    constexpr T &back() noexcept { return m_data[m_size-1]; }
    constexpr T &front() const noexcept { return front(); }
    constexpr T &back() const noexcept { return back(); }

    constexpr size_t size() const { return m_size; } 

    T &operator[] ( int i ) { return m_data[i]; }
    const T &operator[] ( int i ) const { return m_data[i]; }
};

