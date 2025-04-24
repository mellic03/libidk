#pragma once
#include "base_allocator.hpp"
#include "../idk_log.hpp"

namespace idk
{
    template <typename T>
    class fixed_array;
}


template <typename T>
class idk::fixed_array
{
private:
    base_allocator *m_allocator;
    T *m_base, *m_end;

public:
    fixed_array( size_t size, base_allocator *A )
    :   m_allocator(A)
    {
        m_base = static_cast<T*>(A->alloc(size*sizeof(T), alignof(T)));
        m_end  = m_base + size;
    }

    fixed_array( size_t capacity, const T &value, base_allocator *A )
    :   fixed_array(capacity, A)
    {
        for (size_t i=0; i<capacity; i++)
        {
            m_base[i] = value;
        }
    }

    ~fixed_array()
    {
        // m_allocator->free(m_base);
    }

    fixed_array(const fixed_array &) = delete; // Disable copy constructor
    fixed_array &operator=(const fixed_array &) = delete; // Disable assignment

    T*       data()        { return m_base; }
    const T* data()  const { return m_base; }
    size_t   size()  const { return static_cast<size_t>(m_end - m_base); }

    T &operator[] ( size_t i ) { return *(m_base+i); }
    const T &operator[] ( size_t i ) const { return *(m_base+i); }

    struct iterator;
    iterator begin() { return iterator(m_base); };
    iterator end()   { return iterator(m_end);  };
};



template <typename T>
struct idk::fixed_array<T>::iterator
{
    T *ptr;

    iterator( T *p )                 : ptr(p)         {  };
    iterator( const iterator &other ): ptr(other.ptr) {  };

    iterator &operator ++ ()
    {
        ptr++;
        return *this;
    };

    iterator operator ++ (int)
    {
        return iterator(ptr++);
    };

    bool operator == ( const iterator &rhs ) { return ptr == rhs.ptr; };
    bool operator != ( const iterator &rhs ) { return ptr != rhs.ptr; };
    T &operator * () { return *ptr; };

};