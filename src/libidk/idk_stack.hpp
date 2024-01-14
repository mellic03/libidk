#pragma once
#include "idk_vector.hpp"


namespace idk { template <typename T> class stack; };


template <typename T>
class idk::stack: idk::vector<T>
{
public:
    void    push( const T& );
    T       pop();
    T &     top();
};



template <typename T>
void
idk::stack<T>::push( const T &data )
{
    push_back(data);
}


template <typename T>
T
idk::stack<T>::pop()
{
    T data = back();
    pop_back();
    return data;
}


template <typename T>
T &
idk::stack<T>::top()
{
    return back();
}