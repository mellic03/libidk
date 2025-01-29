#pragma once
#include <cstdint>
#include <cstddef>

namespace idk
{
    template <typename T>
    class vector2;
};



template <typename T>
class idk::vector2
{
private:
    T *m_data;
    uint64_t m_size;
    uint64_t m_capacity;

public:
    struct Iterator;

    vector2( uint64_t size );
    vector2(): vector2(0) {  };
    vector2( const vector2<T>& );
    vector2( vector2<T>&& );
    ~vector2();

    vector2 &operator= ( const vector2& );
    vector2 &operator= ( vector2&& );

    const void *data()       { return reinterpret_cast<const void*>(m_data); }
    const void *data() const { return reinterpret_cast<const void*>(m_data); }
    uint64_t    size()       { return m_size; }
    uint64_t    size() const { return m_size; }
    uint64_t    capacity() { return m_capacity; }
    uint64_t    nbytes()   { return m_capacity*sizeof(T); }

    void push_back( const T& );
    void pop_back();

    T &operator[] ( int i ) { return m_data[i]; }
    T &operator[] ( int i ) const { return m_data[i]; }

    T &front() { return m_data[0]; }
    T &back()  { return m_data[m_size-1]; }

    Iterator begin() { return Iterator(m_data); }
    Iterator end()   { return Iterator(m_data + m_size); }

    const T &front() const { return m_data[0]; }
    const T &back()  const { return m_data[m_size-1]; }

};


template <typename T>
struct idk::vector2<T>::Iterator
{
    T *ptr;

    Iterator( T *p )                 : ptr(p)         {  };
    Iterator( const Iterator &other ): ptr(other.ptr) {  };

    Iterator &operator ++ ()
    {
        ptr++;
        return *this;
    };

    Iterator operator ++ (int)
    {
        return Iterator(ptr++);
    };

    bool operator == ( const Iterator &rhs ) { return ptr == rhs.ptr; };
    bool operator != ( const Iterator &rhs ) { return ptr != rhs.ptr; };
    T &operator * () { return *ptr; };

};



template <typename T>
idk::vector2<T>::vector2( uint64_t size )
{
    m_size     = size;
    m_capacity = (2*size > 8) ? 2*size : 8;
    m_data     = new T[m_capacity];
}



template <typename T>
idk::vector2<T>::vector2( const vector2<T> &other )
:   vector2(other.m_size)
{
    for (uint64_t i=0; i<other.m_size; i++)
    {
        m_data[i] = other.m_data[i];
    }
}


template <typename T>
idk::vector2<T>::vector2( vector2<T> &&other )
:   m_size     (other.m_size),
    m_capacity (other.m_capacity),
    m_data     (other.m_data)
{
    other.m_size     = 0;
    other.m_capacity = 0;
    other.m_data     = nullptr;
}



template <typename T>
idk::vector2<T>&
idk::vector2<T>::operator=( const vector2<T> &other )
{
    *this = vector2<T>(other.m_size);

    for (uint64_t i=0; i<other.m_size; i++)
    {
        m_data[i] = other.m_data[i];
    }

    return *this;
}


template <typename T>
idk::vector2<T>&
idk::vector2<T>::operator=( vector2<T> &&other )
{
    m_size     = other.m_size;
    m_capacity = other.m_capacity;
    m_data     = other.m_data;

    other.m_size     = 0;
    other.m_capacity = 0;
    other.m_data     = nullptr;

    return *this;
}



template <typename T>
idk::vector2<T>::~vector2()
{
    if (m_data)
    {
        for (uint64_t i=0; i<m_size; i++)
        {
            m_data[i].~T();
        }

        delete m_data;
    }
}


template <typename T>
void
idk::vector2<T>::push_back( const T &data )
{
    if (m_size+1 >= m_capacity)
    {
        m_capacity = (m_capacity == 0) ? 8 : 2*m_capacity;
        T *new_data = new T[m_capacity];
        
        for (uint64_t i=0; i<m_size; i++)
        {
            new_data[i] = T(m_data[i]);
            m_data[i].~T();
        }

        delete m_data;
        m_data = new_data;
    }

    m_data[m_size] = data;
    m_size += 1;
}


template <typename T>
void
idk::vector2<T>::pop_back()
{
    m_size -= 1;
    m_data[m_size].~T();
}



