#pragma once

#include <iostream>
#include <functional>
#include <stack>
#include <vector>

#include <libidk/IDKcommon/idk_assert.hpp>


namespace idk { template <typename T> class Allocator; };


template <typename T>
class idk::Allocator
{
private:
    std::stack<int>         m_available_ids;
    std::vector<int>        m_reverse_indirection;
    std::vector<int>        m_indirection;
    std::vector<T>          m_data;


public:
    static const size_t INITIAL_ALLOCATION_SIZE = 1;

    int                     create  (          );
    int                     create  ( const T& );
    T &                     get     ( int id   );
    void                    destroy ( int id   );

    std::vector<T> &        vector   ()       { return m_data;        };
    T *                     data     ()       { return m_data.data(); };
    size_t                  size     () const { return m_data.size(); };
    size_t                  bytesize () const { return size()*sizeof(T);    };

    typename std::vector<T>::iterator begin() { return m_data.begin(); };
    typename std::vector<T>::iterator end()   { return m_data.end();   };

    typename std::vector<T>::const_iterator begin() const { return m_data.begin(); };
    typename std::vector<T>::const_iterator end()   const { return m_data.end();   };

    void print() const;

};


template <typename T>
int
idk::Allocator<T>::create()
{
    return create(T());
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
        id = m_indirection.size();
        m_indirection.push_back(data_idx);
    }

    else
    {
        id = m_available_ids.top();
             m_available_ids.pop();
    }
    // ------------------------------------------------------------------------

    m_reverse_indirection.push_back(id);

    return id;
}


template <typename T>
T &
idk::Allocator<T>::get( int id )
{
    IDK_ASSERT("Attemped access of non-existant object", id < m_indirection.size());

    int data_idx = m_indirection[id];
    IDK_ASSERT("Attempted access of deleted object", data_idx != -1);

    return m_data[data_idx];
}


template <typename T>
void
idk::Allocator<T>::destroy( int id )
{
    int data_idx = m_indirection[id];
    int back_idx = m_reverse_indirection.back();

    std::cout
        << "ID:       " << id << "\n"
        << "data_idx: " << data_idx << "\n"
        << "back_idx: " << back_idx << "\n"
        << "Moving idx " << m_data.size()-1 << " into idx " << data_idx << "\n";


    m_data[data_idx]  = std::move(m_data.back());
    m_indirection[back_idx] = std::move(m_indirection[id]);

    m_data.pop_back();
    m_reverse_indirection.pop_back();

    m_available_ids.push(id);
}


// Data:     A  B  C  D  E
// Reverse:  0  1  2  3  4
// Forward:  0  1  2  3  4
// ID:       0  1  2  3  4


template <typename T>
void
idk::Allocator<T>::print() const
{
    std::cout << "\nData:    ";
    for (int i=0; i<m_data.size(); i++)
    {
        std::cout << m_data[i] << " ";
    }

    std::cout << "\nReverse: ";
    for (int i=0; i<m_reverse_indirection.size(); i++)
    {
        std::cout << m_reverse_indirection[i] << " ";
    }

    std::cout << "\nForward: ";
    for (int i=0; i<m_indirection.size(); i++)
    {
        std::cout << m_indirection[i] << " ";
    }

    std::cout << "\nID:      ";
    for (int i=0; i<m_indirection.size(); i++)
    {
        std::cout << i << " ";
    }

    std::cout << "\n";

}