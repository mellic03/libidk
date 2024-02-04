#pragma once

// #include <stack>
// #include <vector>
#include <algorithm>

#include "idk_assert.hpp"
#include "idk_memory.hpp"
#include "idk_io.hpp"

#include "idk_vector.hpp"


namespace idk
{
    template <typename T, typename A>
    class Allocator;

    template <typename T>
    using tAllocator = idk::Allocator<T, idk::frame_allocator<T>>;

    template <typename T>
    using pAllocator = idk::Allocator<T, idk::linear_allocator<T>>;

    template <typename T, typename A = std::allocator<T>>
    using convector = idk::Allocator<T, A>;

};



template <typename T, typename A = std::allocator<T>>
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

    std::vector<T> &        vector   ()       { return m_data;           };
    T *                     data     ()       { return m_data.data();    };
    size_t                  size     () const { return m_data.size();    };
    size_t                  nbytes   () const { return size()*sizeof(T); };

    T &                     operator [] ( int i ) { return m_data.get(i); };


    typename idk::vector<T, A>::iterator begin() { return m_data.begin(); };
    typename idk::vector<T, A>::iterator end()   { return m_data.end();   };

    typename idk::vector<T, A>::const_iterator begin() const { return m_data.begin(); };
    typename idk::vector<T, A>::const_iterator end()   const { return m_data.end();   };


    friend std::ofstream &operator << ( std::ofstream &stream, idk::Allocator<T, A> &v )
    {
        stream << v.m_data;
        stream << v.m_forward;
        stream << v.m_reverse;
        stream << v.m_available_ids;
        return stream;
    };

    friend std::ifstream &operator >> ( std::ifstream &stream, idk::Allocator<T, A> &v )
    {
        stream >> v.m_data;
        stream >> v.m_forward;
        stream >> v.m_reverse;
        stream >> v.m_available_ids;
        return stream;
    };

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



// template <typename T, typename A>
// void
// idk::Allocator<T, A>::serialize( std::ofstream &stream )
// {
//     idk::streamWrite(stream, m_data);
//     idk::streamWrite(stream, m_forward);
//     idk::streamWrite(stream, m_reverse);
//     idk::streamWrite(stream, m_available_ids);
// }


// template <typename T, typename A>
// void
// idk::Allocator<T, A>::deserialize( std::ifstream &stream )
// {
//     m_data    = idk::streamRead<std::vector< T >>(stream);
//     m_forward = idk::streamRead<std::vector<int>>(stream);
//     m_reverse = idk::streamRead<std::vector<int>>(stream);
//     m_available_ids = idk::streamRead<std::vector<int>>(stream);
// }



