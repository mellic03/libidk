#pragma once

#include "idk_log2.hpp"
#include "idk_assert.hpp"
#include "idk_memory.hpp"
#include "idk_io.hpp"
#include "idk_serialize.hpp"
#include "idk_vector.hpp"


#include <cstring>
#include <algorithm>
#include <memory>




#define IDK_ALLOCATOR_ACCESS( name, type, instance ) \
int         create##name  (                  ) { return instance.create();     }; \
int         create##name  ( const type &data ) { return instance.create(data); }; \
type&       get##name     ( int id           ) { return instance.get(id);      }; \
void        destroy##name ( int id           ) { instance.destroy(id);         }; \
idk::Allocator<type> &get##name##Allocator()   { return instance; };



namespace idk
{
    template <typename T, typename A = std::allocator<T>>
    class Allocator;

    template <typename T>
    using tAllocator = idk::Allocator<T, idk::frame_allocator<T>>;

    template <typename T>
    using pAllocator = idk::Allocator<T, idk::linear_allocator<T>>;

};



template <typename T, typename A>
class idk::Allocator
{
private:
    idk::vector<int>        m_freelist;
    idk::vector<int>        m_reverse;
    idk::vector<int>        m_forward;
    idk::vector<T>          m_data;


public:
    using value_type = T;
    using class_type = idk::Allocator<T, A>;

    static const size_t INITIAL_ALLOCATION_SIZE = 1;

                            Allocator() {  };
                            Allocator( const Allocator & );
                            Allocator( Allocator && );
                           ~Allocator();




    int                     create  (          );
    int                     create  ( const T& );
    int                     create  ( T&&      );
    T &                     get     ( int id   );
    void                    destroy ( int id   );
    void                    clear   (          );

    bool                    contains( int id   );

    std::vector<T> &        vector   (       )       { return m_data;        };
    T *                     data     (       )       { return m_data.data(); };
    size_t                  size     (       ) const { return m_data.size(); };
    void                    reserve  ( int n )       { m_data.reserve(n);    };

    T &                     operator [] ( int i ) { return m_data.get(i); };


    typename idk::vector<T, A>::iterator begin() { return m_data.begin(); };
    typename idk::vector<T, A>::iterator end()   { return m_data.end();   };

    typename idk::vector<T, A>::const_iterator begin() const { return m_data.begin(); };
    typename idk::vector<T, A>::const_iterator end()   const { return m_data.end();   };

    size_t serialize( std::ofstream &stream ) const;
    size_t deserialize( std::ifstream &stream );

};



template <typename T, typename A>
idk::Allocator<T, A>::Allocator( const idk::Allocator<T, A> &a )
:   m_data (std::move(a.m_data))
{

}


template <typename T, typename A>
idk::Allocator<T, A>::Allocator( idk::Allocator<T, A> &&a )
:   m_data (std::move(a.m_data))
{

}


template <typename T, typename A>
idk::Allocator<T, A>::~Allocator()
{
    m_data.clear();
}



template <typename T, typename A>
int
idk::Allocator<T, A>::create()
{
    int id  = -1;

    int data_idx = m_data.size();
    m_data.emplace_back(T());


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

    // if (m_reverse.size() <= data_idx)
    // {
    //     m_reverse.resize(data_idx+1);
    // }
    // m_reverse[data_idx] = id;

    return id;
}


template <typename T, typename A>
int
idk::Allocator<T, A>::create( const T &data )
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

    // if (m_reverse.size() <= data_idx)
    // {
    //     m_reverse.resize(data_idx+1);
    // }
    // m_reverse[data_idx] = id;

    return id;
}


template <typename T, typename A>
int
idk::Allocator<T, A>::create( T &&data )
{
    int id  = -1;

    int data_idx = m_data.size();
    m_data.emplace_back(std::move(data));

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

    // if (m_reverse.size() <= data_idx)
    // {
    //     m_reverse.resize(data_idx+1);
    // }
    // m_reverse[data_idx] = id;

    return id;
}


template <typename T, typename A>
T &
idk::Allocator<T, A>::get( int id )
{
    IDK_ASSERT("Attempted access of non-existant object", id < m_forward.size());

    int data_idx = m_forward[id];
    IDK_ASSERT("Attempted access of deleted object", data_idx != -1);

    return m_data[data_idx];
}


template <typename T, typename A>
void
idk::Allocator<T, A>::destroy( int id )
{
    int data_idx = m_forward[id];

    if (data_idx == -1)
    {
        LOG_WARN(
            "idk::WAllocator2",
            std::format("Attempted to delete object {} which is already deleted", id)
        );
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
idk::Allocator<T, A>::clear()
{
    m_data     = std::vector<T>();
    m_forward  = std::vector<int>();
    m_freelist = std::vector<int>();
}




template <typename T, typename A>
bool
idk::Allocator<T, A>::contains( int id )
{
    if (id < 0 || id >= m_forward.size())
    {
        return false;
    }

    return m_forward[id] != -1;
}





template <typename T, typename A>
size_t
idk::Allocator<T, A>::serialize( std::ofstream &stream ) const
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
idk::Allocator<T, A>::deserialize( std::ifstream &stream )
{
    this->clear();

    size_t n = 0;
    n += idk::streamread(stream, m_data);
    n += idk::streamread(stream, m_forward);
    n += idk::streamread(stream, m_reverse);
    n += idk::streamread(stream, m_freelist);
    return n;
}

