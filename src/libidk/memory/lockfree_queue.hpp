#pragma once

#include <atomic>
#include <memory>
#include "../idk_log.hpp"


namespace idk
{
    // template<typename T>
    class lockfree_queue;
}



// template<typename T>

struct Task { int x, y; };
using T = Task;


class idk::lockfree_queue
{
public:
    struct Node
    {
        T *data;
        std::atomic<Node*> next;

        Node( T *D=nullptr )
        :   data(D)
        {
            next.store(nullptr);
        }
    };

    std::atomic<Node*> m_head;
    std::atomic<Node*> m_tail;


public:
    lockfree_queue()
    {
        m_head.store(nullptr);
        m_tail.store(nullptr);
    }

    /*
        ... --> tail --> nullptr
        ... --> tail --> next --> nullptr

    */
    void enqueue( T *data )
    {
        Node *newNode = new Node(data);
        Node *tail = m_tail.load();
        Node *dummy = nullptr;
    
        auto oldNode = m_tail.exchange(newNode);

        while (!tail->next.compare_exchange_weak(dummy, newNode))
        {
            tail->next.store(newNode);
        }

        while (!tail->next.compare_exchange_weak(dummy, newNode))
        {
            tail->next.store(newNode);
        }

        // tail.compare_exchange_weak(old_tail, new_node);
    }


    bool dequeue( Task &out )
    {

    }

};
