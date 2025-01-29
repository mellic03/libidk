#pragma once

#include "idk_assert.hpp"
#include "idk_log.hpp"
#include "idk_memory.hpp"
#include "idk_io.hpp"
#include "idk_serialize.hpp"
#include "idk_vector.hpp"

#include <type_traits>
#include <cstring>
#include <algorithm>
#include <memory>


namespace idk
{
    template <typename T, typename A = std::allocator<T>>
    class WAllocator2;
};



template <typename T, typename A>
class idk::WAllocator2
{
private:
    struct wrapper
    {
        int id;
        T *data;

        wrapper( int i, T *d )
        :   id(i), data(d) {  }

        // ~wrapper() { delete data; }
    };

    idk::vector<int>        m_freelist;
    idk::vector<int>        m_reverse;
    idk::vector<int>        m_forward;
    idk::vector<wrapper>    m_data;


public:
    using value_type = wrapper;
    using class_type = idk::WAllocator2<T, A>;

                WAllocator2() {  };
                WAllocator2( const WAllocator2& );
                WAllocator2( WAllocator2&& );
               ~WAllocator2();

    int         create  ( T*  );
    T*          get     ( int );
    void        destroy ( int );

    void *      data    ()       { return m_data.data(); };
    size_t      size    () const { return m_data.size(); };

    typename idk::vector<wrapper>::iterator begin() { return m_data.begin(); };
    typename idk::vector<wrapper>::iterator end()   { return m_data.end();   };

    typename idk::vector<wrapper>::const_iterator begin() const { return m_data.begin(); };
    typename idk::vector<wrapper>::const_iterator end()   const { return m_data.end();   };
};



template <typename T, typename A>
idk::WAllocator2<T, A>::WAllocator2( const idk::WAllocator2<T, A> &a )
:   m_data (std::move(a.m_data))
{

}


template <typename T, typename A>
idk::WAllocator2<T, A>::WAllocator2( idk::WAllocator2<T, A> &&a )
:   m_data (std::move(a.m_data))
{

}


template <typename T, typename A>
idk::WAllocator2<T, A>::~WAllocator2()
{
    m_data.clear();
}


template <typename T, typename A>
int
idk::WAllocator2<T, A>::create( T *data )
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
T*
idk::WAllocator2<T, A>::get( int id )
{
    IDK_ASSERT("Attempted access of non-existant object", id < m_forward.size());

    int data_idx = m_forward[id];
    IDK_ASSERT("Attempted access of deleted object", data_idx != -1);

    return m_data[data_idx].data;
}


template <typename T, typename A>
void
idk::WAllocator2<T, A>::destroy( int id )
{
    int data_idx = m_forward[id];

    if (data_idx == -1)
    {
        LOG_WARN() << "[WAllocator2<T, A>] Object " << id << " already deleted";
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
    delete m_data.back().data;
    m_data.pop_back();

    m_forward[back_idx] = data_idx;
    m_forward[id] = -1;

    m_freelist.push_back(id);
}

