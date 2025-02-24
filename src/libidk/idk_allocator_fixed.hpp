#pragma once

#include "idk_assert.hpp"
#include "idk_log.hpp"
#include "idk_io.hpp"
#include "idk_serialize.hpp"
#include "idk_vector.hpp"

#include "memory/fixed_vector.hpp"

#include <type_traits>
#include <cstring>
#include <algorithm>


namespace idk
{
    template <typename T>
    class fixed_Allocator;
};


template <typename T>
class idk::fixed_Allocator
{
private:
    idk::fixed_vector<int> m_freelist;
    idk::fixed_vector<int> m_reverse;
    idk::fixed_vector<int> m_forward;
    idk::fixed_vector<T>   m_data;


public:
    using value_type = T;
    using class_type = idk::fixed_Allocator<T>;

                fixed_Allocator( size_t capacity, idk::base_allocator* );
                // fixed_Allocator( const fixed_Allocator & );
                // fixed_Allocator( fixed_Allocator && );
               ~fixed_Allocator();

    int         create  (          );
    int         create  ( const T& );
    int         create  ( T&&      );
    T&          get     ( int id   );
    void        destroy ( int id   );
    void        clear   (          );

    void *      data    ()       { return m_data.data(); };
    size_t      size    () const { return m_data.size(); };


    typename idk::fixed_vector<T>::iterator begin() { return m_data.begin(); };
    typename idk::fixed_vector<T>::iterator end()   { return m_data.end();   };

    // typename idk::vector<wrapper>::const_iterator begin() const { return m_data.begin(); };
    // typename idk::vector<wrapper>::const_iterator end()   const { return m_data.end();   };

    size_t serialize( std::ofstream &stream ) const;
    size_t deserialize( std::ifstream &stream );

};



// template <typename T>
// idk::fixed_Allocator<T>::fixed_Allocator( const idk::fixed_Allocator<T> &a )
// :   m_data (std::move(a.m_data))
// {

// }


// template <typename T>
// idk::fixed_Allocator<T>::fixed_Allocator( idk::fixed_Allocator<T> &&a )
// :   m_data (std::move(a.m_data))
// {

// }

template <typename T>
idk::fixed_Allocator<T>::fixed_Allocator( size_t capacity, idk::base_allocator *A )
:   m_freelist(capacity, A),
    m_reverse(capacity, A),
    m_forward(capacity, A),
    m_data(capacity, A)
{
    std::cout << "---------------fixed_Allocator-------------------\n";
}



template <typename T>
idk::fixed_Allocator<T>::~fixed_Allocator()
{
    m_data.clear();
}



template <typename T>
int
idk::fixed_Allocator<T>::create()
{
    int id  = -1;
    int data_idx = m_data.size();
    m_data.emplace_back();

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

    return id;
}


template <typename T>
int
idk::fixed_Allocator<T>::create( const T &data )
{
    int id  = -1;
    int data_idx = m_data.size();
    m_data.emplace_back(data);

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

    return id;
}


template <typename T>
int
idk::fixed_Allocator<T>::create( T &&data )
{
    int id = -1;
    int data_idx = m_data.size();
    m_data.emplace_back(data);

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

    return id;
}


template <typename T>
T&
idk::fixed_Allocator<T>::get( int id )
{
    IDK_ASSERT("Attempted access of non-existant object", id < m_forward.size());

    int data_idx = m_forward[id];
    IDK_ASSERT("Attempted access of deleted object", data_idx != -1);

    return m_data[data_idx];
}


template <typename T>
void
idk::fixed_Allocator<T>::destroy( int id )
{
    int data_idx = m_forward[id];

    if (data_idx == -1)
    {
        LOG_WARN("Attempted to delete object {} which is already deleted", id);
        return;
    }

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


template <typename T>
void
idk::fixed_Allocator<T>::clear()
{

}




template <typename T>
size_t
idk::fixed_Allocator<T>::serialize( std::ofstream &stream ) const
{
    size_t n = 0;
    // n += idk::streamwrite<idk::vector<T>>(stream, m_data);
    // n += idk::streamwrite<idk::vector<int>>(stream, m_forward);
    // n += idk::streamwrite<idk::vector<int>>(stream, m_reverse);
    // n += idk::streamwrite<idk::vector<int>>(stream, m_freelist);
    return n;
}


template <typename T>
size_t
idk::fixed_Allocator<T>::deserialize( std::ifstream &stream )
{
    this->clear();

    size_t n = 0;
    // n += idk::streamread(stream, m_data);
    // n += idk::streamread(stream, m_forward);
    // n += idk::streamread(stream, m_reverse);
    // n += idk::streamread(stream, m_freelist);
    return n;
}

