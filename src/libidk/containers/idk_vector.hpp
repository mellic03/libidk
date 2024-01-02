#pragma once

#include <cstdint>
#include <memory>

#include <libidk/idk_assert.hpp>
#include "idk_buffer.hpp"


namespace idk
{
    template <typename T>
    class vector;
};


template <typename T>
class idk::vector: public idk::iBuffer
{
private:
    static constexpr size_t INITIAL_CAPACITY = 1;

    std::unique_ptr<T[]> m_data;
    size_t               m_capacity;
    size_t               m_size;

    void    _realloc( size_t capacity );

public:

            vector();
            vector( size_t size );
            vector( size_t reserve, size_t size );

    void    push_back( const T &data );
    void    pop_back() { m_size -= 1; };

    constexpr T &front() { return m_data[0]; };
    constexpr T &back()  { return m_data[m_size-1]; };

    virtual void   *data     (          ) final { return m_data.get();     };
    virtual size_t  size     (          ) final { return m_size;           };
    virtual size_t  typesize (          ) final { return sizeof(T);        };
    virtual size_t  nbytes   (          ) final { return m_size*sizeof(T); };
    virtual void    resize   ( size_t s ) final;

    // constexpr size_t size()      { return m_size; };
    constexpr size_t capacity()  { return m_capacity; };

};


template <typename T>
void
idk::vector<T>::_realloc( size_t capacity)
{
    std::unique_ptr<T[]> new_data(new T[capacity]);

    T *start = m_data.get();
    T *end   = m_data.get() + std::min(m_capacity, capacity);
    T *dest  = new_data.get();
    std::copy(start, end, dest);

    m_data     = std::move(new_data);
    m_capacity = capacity;
}



template <typename T>
idk::vector<T>::vector()
: m_data(new T[INITIAL_CAPACITY]), m_capacity(INITIAL_CAPACITY), m_size(0) 
{

}



template <typename T>
idk::vector<T>::vector( size_t size )
: m_data(new T[2*size]), m_capacity(2*size), m_size(size)
{

}



template <typename T>
idk::vector<T>::vector( size_t reserve, size_t size )
: m_data(new T[reserve]), m_capacity(reserve), m_size(size)
{
    IDK_ASSERT("[reserve] must be >= [size]", reserve >= size);
}



template <typename T>
void
idk::vector<T>::push_back( const T &data )
{
    if (m_size+1 >= m_capacity)
    {
        this->_realloc(2*m_capacity);
    }

    m_data[m_size-1] = data;
    m_size += 1;
}



template <typename T>
void
idk::vector<T>::resize( size_t s )
{
    if (s < m_size)
    {
        m_size = s;
    }

    else
    {
        this->_realloc(s);
    }
}

