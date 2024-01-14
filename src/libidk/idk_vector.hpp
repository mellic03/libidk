#pragma once

#include <cstdint>
#include <cstddef>
#include <memory>

#include "idk_buffer.hpp"


namespace idk
{
    template <typename T>
    class vector;

};



template <typename T>
class idk::vector: public idk::iBuffer
{
protected:
    std::unique_ptr<T[]> m_data;

private:
    static constexpr size_t DEFAULT_CAP = 4;
    size_t      m_size;
    size_t      m_cap;

    void        _realloc( size_t size );


public:
                vector();
                vector( size_t size );
                vector( size_t size, const T &data );

    size_t      capacity() const { return m_cap; };


    // idk::iBuffer compliance
    // -----------------------------------------------------------------------------------------
    virtual void *  data()      final { return m_data.get();     };
    virtual size_t  size()      final { return m_size;           };
    virtual size_t  typesize()  final { return sizeof(T);        };
    virtual size_t  nbytes()    final { return size()*sizeof(T); };
    virtual void    resize( size_t s ) final;
    // -----------------------------------------------------------------------------------------

    void        push_back( const T &data );
    void        pop_back();

    const T&    front() const { return m_data[0];        };
    const T&    back()  const { return m_data[m_size-1]; };

    T&          operator [] ( int i ) { return m_data[i]; };
    const T&    operator [] ( int i ) const { return m_data[i]; };


    struct iterator;

    iterator begin() { return iterator(&m_data[0]);          };
    iterator end()   { return iterator(&m_data[0] + size()); };

};



template <typename T>
struct idk::vector<T>::iterator
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



#include "idk_vector.inl"


