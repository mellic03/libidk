#pragma once

#include "idk_pod.hpp"


namespace idk
{
    template <typename T> requires_IsPOD(T)
    class pod_vector;
};


template <typename T> requires_IsPOD(T)
class pod_vector
{
private:
    idk::vector<T> m_data;


public:

    ~pod_vector()
    {
        for (T &E: m_data)
        {
            idk::pod_dtor(E);
        }
    };

    constexpr void push_back()
    {
        m_data.push_back( idk::pod_ctor<T>() );
    };

    constexpr void push_back( const T &data )
    {
        m_data.push_back( data );
    };

    constexpr void pop_back()
    {
        idk::pod_dtor( m_data.back() );
    };

    constexpr T &back()
    {
        return m_data.back();
    };

};



