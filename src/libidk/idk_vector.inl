#pragma once

#include "idk_vector.hpp"
#include "idk_assert.hpp"


template <typename T>
void
idk::vector<T>::_realloc( size_t capacity )
{
    std::unique_ptr<T[]> new_data(new T[capacity]);

    T *start = m_data.get();
    T *end   = m_data.get() + std::min(m_cap, capacity);
    T *dest  = new_data.get();
    std::copy(start, end, dest);

    m_data = std::move(new_data);
    m_cap  = capacity;
}




template <typename T>
idk::vector<T>::vector()
:   m_size(0),
    m_cap(DEFAULT_CAP)
{
    m_data = std::make_unique<T[]>(DEFAULT_CAP);
}



template <typename T>
idk::vector<T>::vector( size_t size )
:   m_size(size),
    m_cap(size)
{
    m_data = std::make_unique<T[]>(size);
}



template <typename T>
idk::vector<T>::vector( size_t size, const T &data )
:   m_size(size),
    m_cap(size)
{
    m_data = std::make_unique<T[]>(size);

    for (size_t i=0; i<size; i++)
    {
        m_data[i] = data;
    }
}




template <typename T>
void
idk::vector<T>::resize( size_t sz )
{
    m_size = sz;

    if (m_size >= m_cap)
    {
        this->_realloc(sz);
    }
}



template <typename T>
void
idk::vector<T>::push_back( const T &data )
{
    if (m_size + 1 >= m_cap)
    {
        this->_realloc(2*m_size);
    }

    m_data[m_size] = data;
    m_size += 1;
}


template <typename T>
void
idk::vector<T>::pop_back()
{
    m_size -= 1;
    IDK_ASSERT("RUH ROH", m_size >= 0);
}

