#pragma once

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

    template <typename T, typename A = std::allocator<T>>
    using convector = idk::Allocator<T, A>;

};



template <typename T, typename A>
class idk::Allocator
{
private:
    idk::vector<int>        m_available_ids;
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

    std::vector<T> &        vector   ()       { return m_data;           };
    T *                     data     ()       { return m_data.data();    };
    size_t                  size     () const { return m_data.size();    };

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
    m_data.emplace_back(std::move(T()));


    // Determine user-facing id
    // ------------------------------------------------------------------------
    if (m_available_ids.empty())
    {
        id = m_forward.size();
        m_forward.push_back(data_idx);
    }

    else
    {
        id = m_available_ids.back();
             m_available_ids.pop_back();
    }
    // ------------------------------------------------------------------------

    m_reverse.push_back(id);

    return id;
}


template <typename T, typename A>
int
idk::Allocator<T, A>::create( const T &data )
{
    int id  = -1;

    int data_idx = m_data.size();
    m_data.emplace_back(std::move(data));


    // Determine user-facing id
    // ------------------------------------------------------------------------
    if (m_available_ids.empty())
    {
        id = m_forward.size();
        m_forward.push_back(data_idx);
    }

    else
    {
        id = m_available_ids.back();
             m_available_ids.pop_back();
    }
    // ------------------------------------------------------------------------

    m_reverse.push_back(id);

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
    if (m_available_ids.empty())
    {
        id = m_forward.size();
        m_forward.push_back(data_idx);
    }

    else
    {
        id = m_available_ids.back();
             m_available_ids.pop_back();
    }
    // ------------------------------------------------------------------------

    m_reverse.push_back(id);

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
    int back_idx = m_reverse.back();

    std::swap(m_data[data_idx], m_data.back());
    std::swap(m_forward[back_idx], m_forward[id]);
    std::swap(m_reverse[data_idx], m_reverse.back());

    m_data.pop_back();
    m_reverse.pop_back();

    m_available_ids.push_back(id);
}


template <typename T, typename A>
void
idk::Allocator<T, A>::clear()
{
    m_data.clear();
    m_forward.clear();
    m_reverse.clear();

    while (m_available_ids.empty() == false)
    {
        m_available_ids.pop_back();
    }

}




template <typename T, typename A>
bool
idk::Allocator<T, A>::contains( int id )
{
    if (id < 0)
    {
        return false;
    }

    if (id >= m_forward.size())
    {
        return false;
    }

    for (int i: m_available_ids)
    {
        if (i == id)
        {
            return false;
        }
    }

    return true;
}







template <typename T, typename A>
size_t
idk::Allocator<T, A>::serialize( std::ofstream &stream ) const
{
    size_t n = 0;
    n += idk::streamwrite<idk::vector<T>>(stream, m_data);
    n += idk::streamwrite<idk::vector<int>>(stream, m_forward);
    n += idk::streamwrite<idk::vector<int>>(stream, m_reverse);
    n += idk::streamwrite<idk::vector<int>>(stream, m_available_ids);
    return n;
}


template <typename T, typename A>
size_t
idk::Allocator<T, A>::deserialize( std::ifstream &stream )
{
    size_t n = 0;
    n += idk::streamread(stream, m_data);
    n += idk::streamread(stream, m_forward);
    n += idk::streamread(stream, m_reverse);
    n += idk::streamread(stream, m_available_ids);
    return n;
}

