#pragma once

#include "idk_log.hpp"
#include "idk_io.hpp"
#include "idk_serialize.hpp"
#include "idk_vector.hpp"

#include "memory/fixed_array.hpp"
#include "memory/fixed_vector.hpp"

#include <type_traits>
#include <cstring>
#include <algorithm>


namespace idk
{
    template <typename T>
    class fixed_Allocator;
};


#ifndef IDK_ALLOCATOR_ACCESS
    #define IDK_ALLOCATOR_ACCESS( name, type, instance ) \
    int   create##name() { return instance.create(); }; \
    int   create##name( const type &data ) { return instance.create(data); }; \
    type& get##name( int id ) { return instance.get(id); }; \
    void  destroy##name ( int id ) { instance.destroy(id); }; \
    idk::fixed_Allocator<type> &get##name##Allocator() { return instance; };
#endif




template <typename T>
class idk::fixed_Allocator
{
private:
    struct wrapper_type
    {
        int id;
        T *data;
    };

    int m_maxid = -1;

    idk::fixed_vector<int> m_freelist;
    idk::fixed_array<int>  m_reverse;
    idk::fixed_array<int>  m_forward;
    idk::fixed_vector<T>   m_data;

    int _create();

public:
    using value_type = T;
    using class_type = idk::fixed_Allocator<T>;

    fixed_Allocator( size_t capacity, idk::base_allocator* );
    ~fixed_Allocator();

    
    int create  ( T&& );
    int create  ( const T &data );
    int create  ( );
    
    T&          get     ( int id   );
    void        destroy ( int id   );
    void        clear   (          );

    void *      data    ()       { return m_data.data(); };
    size_t      size    () const { return m_data.size(); };
    bool        contains( int id ) { return (0<=id && id<m_maxid) && (m_forward[id] != -1);}

    typename idk::fixed_vector<T>::iterator begin() { return m_data.begin(); };
    typename idk::fixed_vector<T>::iterator end()   { return m_data.end();   };

    // typename idk::fixed_vector<wrapper>::const_iterator begin() const { return m_data.begin(); };
    // typename idk::fixed_vector<wrapper>::const_iterator end()   const { return m_data.end();   };

    size_t serialize( std::ofstream &stream ) const;
    size_t deserialize( std::ifstream &stream );

};



template <typename T>
idk::fixed_Allocator<T>::fixed_Allocator( size_t capacity, idk::base_allocator *A )
:   m_freelist(capacity, A),
    m_reverse(capacity, -1, A),
    m_forward(capacity, -1, A),
    m_data(capacity, A)
{

}



template <typename T>
idk::fixed_Allocator<T>::~fixed_Allocator()
{
    m_data.clear();
}




template <typename T>
int
idk::fixed_Allocator<T>::_create()
{
    int id, idx;

    if (m_freelist.empty())
    {
        m_maxid += 1;
        id = m_maxid;
        // m_maxid += 1;
    }

    else
    {
        id = m_freelist.back();
             m_freelist.pop_back();
    }

    idx = m_data.size();
    m_forward[id]  = idx;
    m_reverse[idx] = id;

    return id;
}


template <typename T>
int
idk::fixed_Allocator<T>::create()
{
    int id = _create();
    m_data.push_back(T());
    return id;
}


template <typename T>
int
idk::fixed_Allocator<T>::create( const T &data )
{
    int id = _create();
    m_data.push_back(data);
    return id;
}


template <typename T>
int
idk::fixed_Allocator<T>::create( T &&data )
{
    int id = _create();
    m_data.push_back(data);
    return id;
}


template <typename T>
T&
idk::fixed_Allocator<T>::get( int id )
{
    LOG_ASSERT(
        0 <= id && id <= m_maxid,
        "Attempted access of non-existant object {}. Reason: 0<={} && {}<={}", id, id, id, m_maxid
    );

    int idx = m_forward[id];

    LOG_ASSERT(
        idx != -1,
        "Attempted access of deleted object {}", id
    );

    return m_data[idx];
}


template <typename T>
void
idk::fixed_Allocator<T>::destroy( int id )
{
    int idx = m_forward[id];

    // Public id of element currently stored at data.back()
    int back_id = m_reverse[m_data.size() - 1];
    LOG_ASSERT(back_id != -1, "Programmer error exists if this assertion has failed");

    // Swap elements "id" and "back_id" and pop
    std::swap(m_data[idx], m_data.back());
    m_data.pop_back();

    // The internal id of element "back_id" now needs to point to where element "id" used to be.
    m_forward[back_id] = idx;

    // Reset
    m_reverse[idx] = -1;
    m_forward[id]  = -1;

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

