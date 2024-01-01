#pragma once

#include <iostream>
#include <functional>
#include <stack>
#include <vector>

#include <libidk/IDKcommon/idk_assert.hpp>


namespace idk
{
    template <typename T> class Allocator;
};


template <typename T>
class idk::Allocator
{
private:
    std::stack<int>         m_available_ids;
    std::vector<int>        m_reverse;
    std::vector<int>        m_forward;
    std::vector<T>          m_data;


public:
    static const size_t INITIAL_ALLOCATION_SIZE = 1;

    int                     create  (          );
    int                     create  ( const T& );
    int                     create  ( const T&& );
    T &                     get     ( int id   );
    void                    destroy ( int id   );

    std::vector<T> &        vector   ()       { return m_data;           };
    T *                     data     ()       { return m_data.data();    };
    size_t                  size     () const { return m_data.size();    };
    size_t                  nbytes   () const { return size()*sizeof(T); };

    typename std::vector<T>::iterator begin() { return m_data.begin(); };
    typename std::vector<T>::iterator end()   { return m_data.end();   };

    typename std::vector<T>::const_iterator begin() const { return m_data.begin(); };
    typename std::vector<T>::const_iterator end()   const { return m_data.end();   };

};



template <typename T>
int
idk::Allocator<T>::create()
{
    int id  = -1;

    int data_idx = m_data.size();
    m_data.push_back(T());


    // Determine user-facing id
    // ------------------------------------------------------------------------
    if (m_available_ids.empty())
    {
        id = m_forward.size();
        m_forward.push_back(data_idx);
    }

    else
    {
        id = m_available_ids.top();
             m_available_ids.pop();
    }
    // ------------------------------------------------------------------------

    m_reverse.push_back(id);

    return id;
}


template <typename T>
int
idk::Allocator<T>::create( const T &data )
{
    int id  = -1;

    int data_idx = m_data.size();
    m_data.push_back(data);


    // Determine user-facing id
    // ------------------------------------------------------------------------
    if (m_available_ids.empty())
    {
        id = m_forward.size();
        m_forward.push_back(data_idx);
    }

    else
    {
        id = m_available_ids.top();
             m_available_ids.pop();
    }
    // ------------------------------------------------------------------------

    m_reverse.push_back(id);

    return id;
}


template <typename T>
int
idk::Allocator<T>::create( const T &&data )
{
    int id  = -1;

    int data_idx = m_data.size();
    m_data.push_back(std::move(data));


    // Determine user-facing id
    // ------------------------------------------------------------------------
    if (m_available_ids.empty())
    {
        id = m_forward.size();
        m_forward.push_back(data_idx);
    }

    else
    {
        id = m_available_ids.top();
             m_available_ids.pop();
    }
    // ------------------------------------------------------------------------

    m_reverse.push_back(id);

    return id;
}


template <typename T>
T &
idk::Allocator<T>::get( int id )
{
    IDK_ASSERT("Attempted access of non-existant object", id < m_forward.size());

    int data_idx = m_forward[id];
    IDK_ASSERT("Attempted access of deleted object", data_idx != -1);

    return m_data[data_idx];
}


template <typename T>
void
idk::Allocator<T>::destroy( int id )
{
    int data_idx = m_forward[id];
    int back_idx = m_reverse.back();

    m_data[data_idx] = std::move(m_data.back());
    m_forward[back_idx] = std::move(m_forward[id]);

    m_data.pop_back();
    m_reverse.pop_back();

    m_available_ids.push(id);
}
