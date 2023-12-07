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
    virtual size_t  nbytes (        ) = 0;
    virtual void    resize ( size_t ) = 0;   
};


template <typename T>
class idk::Buffer: public idk::iBuffer
{
public:
    std::vector<T> m_data;

    virtual void   *data   (          ) final; // { return reinterpret_cast<void *>(&m_data[0]); };
    virtual size_t  nbytes (          ) final; // { return sizeof(T) * m_data.size(); };
    virtual void    resize ( size_t s ) final; // { m_data.resize(s); };   
};



template <typename T>
void *
idk::Buffer<T>::data()
{

}


template <typename T>
size_t
idk::Buffer<T>::nbytes()
{

}


template <typename T>
void
idk::Buffer<T>::resize( size_t s )
{

}

