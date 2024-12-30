#pragma once

#include "idk_assert.hpp"
#include "idk_log.hpp"
#include "idk_memory.hpp"
#include "idk_io.hpp"
#include "idk_serialize.hpp"
#include "idk_vector.hpp"


#include <cstring>
#include <algorithm>
#include <memory>


namespace idk
{
    template <typename T, typename A = std::allocator<T>>
    class WAllocator;
};



template <typename T, typename A>
class idk::WAllocator
{
private:
    struct wrapper
    {
        int id;
        T data;
        wrapper( int i, const T &d ): id(i), data(d) {  };
    };

    idk::vector<int>        m_freelist;
    idk::vector<int>        m_reverse;
    idk::vector<int>        m_forward;
    idk::vector<wrapper>    m_data;


public:
    using value_type = wrapper;
    using class_type = idk::WAllocator<T, A>;

                WAllocator() {  };
                WAllocator( const WAllocator & );
                WAllocator( WAllocator && );
               ~WAllocator();

    int         create  (          );
    int         create  ( const T& );
    int         create  ( T&&      );
    T&          get     ( int id   );
    void        destroy ( int id   );
    void        clear   (          );

    void *      data    ()       { return m_data.data(); };
    size_t      size    () const { return m_data.size(); };


    typename idk::vector<wrapper>::iterator begin() { return m_data.begin(); };
    typename idk::vector<wrapper>::iterator end()   { return m_data.end();   };

    typename idk::vector<wrapper>::const_iterator begin() const { return m_data.begin(); };
    typename idk::vector<wrapper>::const_iterator end()   const { return m_data.end();   };

    size_t serialize( std::ofstream &stream ) const;
    size_t deserialize( std::ifstream &stream );

};



template <typename T, typename A>
idk::WAllocator<T, A>::WAllocator( const idk::WAllocator<T, A> &a )
:   m_data (std::move(a.m_data))
{

}


template <typename T, typename A>
idk::WAllocator<T, A>::WAllocator( idk::WAllocator<T, A> &&a )
:   m_data (std::move(a.m_data))
{

}


template <typename T, typename A>
idk::WAllocator<T, A>::~WAllocator()
{
    m_data.clear();
}



template <typename T, typename A>
int
idk::WAllocator<T, A>::create()
{
    int id  = -1;
    int data_idx = m_data.size();

    // Determine user-facing id
    // ------------------------------------------------------------------------
    if (m_freelist.empty())
    {
        id = m_forward.size();
        m_forward.push_back(data_idx);
    }

    else
    {
        id = m_freelist.back();
             m_freelist.pop_back();
    }
    // ------------------------------------------------------------------------

    m_forward[id] = data_idx;
    m_data.emplace_back(wrapper(id, T()));

    return id;
}


template <typename T, typename A>
int
idk::WAllocator<T, A>::create( const T &data )
{
    int id  = -1;
    int data_idx = m_data.size();

    // Determine user-facing id
    // ------------------------------------------------------------------------
    if (m_freelist.empty())
    {
        id = m_forward.size();
        m_forward.push_back(data_idx);
    }

    else
    {
        id = m_freelist.back();
             m_freelist.pop_back();
    }
    // ------------------------------------------------------------------------

    m_forward[id] = data_idx;
    m_data.emplace_back(wrapper(id, data));

    return id;
}


template <typename T, typename A>
int
idk::WAllocator<T, A>::create( T &&data )
{
    int id = -1;
    int data_idx = m_data.size();

    // Determine user-facing id
    // ------------------------------------------------------------------------
    if (m_freelist.empty())
    {
        id = m_forward.size();
        m_forward.push_back(data_idx);
    }

    else
    {
        id = m_freelist.back();
             m_freelist.pop_back();
    }
    // ------------------------------------------------------------------------

    m_forward[id] = data_idx;
    m_data.emplace_back(wrapper(id, std::move(data)));

    return id;
}


template <typename T, typename A>
T&
idk::WAllocator<T, A>::get( int id )
{
    IDK_ASSERT("Attempted access of non-existant object", id < m_forward.size());

    int data_idx = m_forward[id];
    IDK_ASSERT("Attempted access of deleted object", data_idx != -1);

    return m_data[data_idx].data;
}


template <typename T, typename A>
void
idk::WAllocator<T, A>::destroy( int id )
{
    int data_idx = m_forward[id];

    if (data_idx == -1)
    {
        LOG_WARN() << "[WAllocator<T, A>] Object " << id << " already deleted";
        return;
    }
    // IDK_ASSERT("Attempted access of deleted object", data_idx != -1);


    // Find id of object which points to end of m_data
    int back_idx = -1;

    for (int i=0; i<m_forward.size(); i++)
    {
        if (m_forward[i] == m_data.size()-1)
        {
            back_idx = i;
        }
    }

    IDK_ASSERT("Ruh roh", back_idx != -1);

    std::swap(m_data[data_idx], m_data.back());
    m_data.pop_back();

    m_forward[back_idx] = data_idx;
    m_forward[id] = -1;

    m_freelist.push_back(id);
}


template <typename T, typename A>
void
idk::WAllocator<T, A>::clear()
{
    m_data     = std::vector<T>();
    m_forward  = std::vector<int>();
    m_freelist = std::vector<int>();
}




template <typename T, typename A>
size_t
idk::WAllocator<T, A>::serialize( std::ofstream &stream ) const
{
    size_t n = 0;
    n += idk::streamwrite<idk::vector<T>>(stream, m_data);
    n += idk::streamwrite<idk::vector<int>>(stream, m_forward);
    n += idk::streamwrite<idk::vector<int>>(stream, m_reverse);
    n += idk::streamwrite<idk::vector<int>>(stream, m_freelist);
    return n;
}


template <typename T, typename A>
size_t
idk::WAllocator<T, A>::deserialize( std::ifstream &stream )
{
    this->clear();

    size_t n = 0;
    n += idk::streamread(stream, m_data);
    n += idk::streamread(stream, m_forward);
    n += idk::streamread(stream, m_reverse);
    n += idk::streamread(stream, m_freelist);
    return n;
}

