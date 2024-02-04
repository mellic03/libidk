#pragma once

#include <vector>

namespace idk
{
    template <typename T>
    class stack;
};


template <typename T>
class idk::stack
{
private:
    idk::vector<T> m_vector;

public:

    stack() {  };

    stack( size_t reserve )
    {
        m_vector.reserve(reserve);
    };

    void    push ( const T& data ) {  m_vector.push_back(data);  };
    T&      top  (               ) {  return m_vector.back();    };
    void    pop  (               ) {  m_vector.pop_back();       };

    size_t  size() { return m_vector.size(); };

};



// template <>
// idk::stack<int>::stack( int reserve )
// :   m_vector(reserve)
// {
//     for (int i=0; i<reserve; i++)
//     {
//         m_vector[i] = reserve-1 - i;
//     }
// }



// namespace idk { template <typename T> class stack; };


// template <typename T>
// class idk::stack: idk::vector<T>
// {
// public:
//     void    push( const T& );
//     T       pop();
//     T &     top();
// };



// template <typename T>
// void
// idk::stack<T>::push( const T &data )
// {
//     push_back(data);
// }


// template <typename T>
// T
// idk::stack<T>::pop()
// {
//     T data = back();
//     pop_back();
//     return data;
// }


// template <typename T>
// T &
// idk::stack<T>::top()
// {
//     return back();
// }