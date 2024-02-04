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
        view( T *base, size_t length );
        view( T *base, T *end );
        view( T &base, size_t length ) : view(&base, length) {  };

    const T &operator [] ( int i ) const { return m_base[i]; };

    struct iterator
    {
        const T *ptr;

        iterator( const T *data ): ptr(data) {  };

        iterator( const iterator &it ): ptr(it.ptr) {  };
    
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
            return ptr == rhs.ptr;
        };

        bool operator != ( const iterator &rhs )
        {
            return ptr != rhs.ptr;
        };

        const T &operator * ()
        {
            return *ptr;
        };
    };

    iterator begin() { return iterator(m_base); };
    iterator end()   { return iterator(m_end);  };

};



template <typename T>
idk::view<T>::view( T *base, size_t length )
{
    m_base = base;
    m_end  = base + length;
}

template <typename T>
idk::view<T>::view( T *base, T *end )
{
    m_base = base;
    m_end  = end;
}

// template <typename T>
// idk::view<T>::view( T &base, size_t length )
// {
//     m_base = (&base);
//     m_end  = (&base) + length;
// }

// template <typename T>
// idk::view<T>::view( T &base, T &end )
// {
//     m_base = &base;
//     m_end  = &end;
// }
