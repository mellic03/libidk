#pragma once

#include <cstddef>

namespace idk { template <typename T> class view; };


template <typename T>
class idk::view
{
private:
    const T *m_base;
    const T *m_end;

public:
        view( const T *base, size_t length );

    const T &operator [] ( int i ) const { return m_base[i]; };

    struct iterator
    {
        const T *ptr;
        iterator( const iterator &rhs ): ptr(rhs.ptr) {  };
    
        iterator &operator ++ ()
        {
            ptr++;
            return *this;
        };
    
        iterator operator ++ (int)
        {
            iterator temp(*this);
            return temp++;
        };

        bool operator == ( const iterator &rhs )
        {
            return m_base == rhs.m_base && m_end == rhs.m_end;
        };

        bool operator != ( const iterator &rhs )
        {
            return m_base != rhs.m_base || m_end != rhs.m_end;
        };

        const T &operator * ()
        {
            return *ptr;
        };
    };

    iterator begin() { return iterator(m_base); };
    iterator end() { return iterator(m_base + m_end); };

};


template <typename T>
idk::view<T>::view( const T *base, size_t length )
{
    m_base = base;
    m_end  = base + length;
}
