#pragma once

#include "base_allocator.hpp"
#include "../idk_allocator_fixed.hpp"

#include <thread>
#include <atomic>
#include <mutex>
#include <deque>


namespace idk
{
    template<typename T>
    class threadsafe_Queue;
}


template<typename T>
class idk::threadsafe_Queue
{
private:
    std::mutex    m_mutex;
    std::deque<T> m_deque;
    std::atomic_int m_size;


public:
    threadsafe_Queue()
    {
        m_size.store(0);
    }

    bool empty()
    {
        return m_size.load() == 0;
    }

    bool push_back( const T &data )
    {
        std::scoped_lock<std::mutex> lock(m_mutex);
        m_deque.push_back(data);
        m_size++;
        return true;
    }

    bool pop_front( T &out )
    {
        std::scoped_lock<std::mutex> lock(m_mutex);

        if (m_deque.empty())
        {
            return false;
        }

        out = m_deque.front();
        m_deque.pop_front();
        m_size--;

        return true;
    }

};
