#pragma once

#include <vector>

namespace idk
{
    class iBuffer;

    template <typename T>
    class Buffer;
};


class idk::iBuffer
{
public:
    virtual        ~iBuffer() = default;

    virtual void *  data   (        ) = 0;
    virtual size_t  size   (        ) = 0;
    virtual size_t  nbytes (        ) = 0;
    virtual void    resize ( size_t ) = 0;   
};


template <typename T>
class idk::Buffer: public idk::iBuffer
{
public:
    std::vector<T> m_data;

    virtual void   *data   (          ) final;
    virtual size_t  size   (          ) final { return m_data.size(); };
    virtual size_t  nbytes (          ) final;
    virtual void    resize ( size_t s ) final;

    void    push_back( const T &data ) { m_data.push_back(data); };

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

