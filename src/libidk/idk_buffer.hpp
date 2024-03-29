#pragma once

#include "idk_ibuffer.hpp"
#include <vector>

namespace idk
{
    template <typename T>
    class Buffer;
};


template <typename T>
class idk::Buffer: public idk::iBuffer
{
public:
    std::vector<T> m_data;

    virtual void   *data     (          ) final;
    virtual size_t  size     (          ) final { return m_data.size(); };
    virtual size_t  typesize (          ) final { return sizeof(T);     };
    virtual size_t  nbytes   (          ) final;
    virtual void    resize   ( size_t s ) final;

    void    push_back( const T &data ) { m_data.push_back(data); };

    T &     operator[] ( int i ) { return m_data[i]; };

    typename std::vector<T>::iterator begin() { return m_data.begin(); };
    typename std::vector<T>::iterator end()   { return m_data.end();   };
};



template <typename T>
void *
idk::Buffer<T>::data()
{
    return reinterpret_cast<void *>(&m_data[0]);
}


template <typename T>
size_t
idk::Buffer<T>::nbytes()
{
    return sizeof(T) * m_data.size();
}


template <typename T>
void
idk::Buffer<T>::resize( size_t s )
{
    m_data.resize(s);
}

