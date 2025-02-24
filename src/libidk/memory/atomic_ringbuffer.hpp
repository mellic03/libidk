#pragma once

#include <atomic>
#include <array>
#include <functional>
#include "../idk_log.hpp"

namespace idk
{
    class atomic_ringbuffer;
}


class idk::atomic_ringbuffer
{
public:
    struct Task
    {
        std::function<void()> work = [](){};
        std::function<void()> callback = [](){};
    };

    struct private_type
    {
        std::atomic_bool waitingForWorker;
        Task task;
    };

private:
    std::atomic_uint8_t m_head;
    std::atomic_uint8_t m_tail;
    private_type *m_data;

public:
    atomic_ringbuffer()
    {
        m_data = new private_type[256];
    
        for (int i=0; i<256; i++)
        {
            m_data[i].waitingForWorker.store(false);
        }

        m_head.store(0);
        m_tail.store(0);
    }

    void enqueue( const Task &task )
    {
        size_t tail = m_tail.fetch_add(1);

        m_data[tail].task = task;
        m_data[tail].waitingForWorker.store(true);
    }

    bool dequeue( Task &out )
    {
        size_t head = m_head.fetch_add(1);

        if (m_data[head].waitingForWorker.load() == false)
        {
            m_head.fetch_sub(1);
            return false;
        }

        out = m_data[head].task;
        m_data[head].waitingForWorker.store(false);
        return true;
    }

};
