#pragma once

#include <cstddef>
#include <cstdint>

#include <functional>
#include <vector>
#include <deque>

#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <stack>
#include <set>

#include "memory/threadsafe_queue.hpp"
#include "memory/threadsafe_ringbuffer.hpp"


namespace idk
{
    class Threadpool;
}



class idk::Threadpool
{
private:
    struct Task
    {
        uint64_t id;
        std::function<void()> work = [](){};
        std::function<void()> callback = [](){};
    };

    template <typename U>
    using queue_type = idk::threadsafe_Queue<U>;

    std::vector<std::thread>        m_threads;
    queue_type<Task>                m_inbuffer;
    queue_type<Task>                m_outbuffer;

    std::atomic_bool                m_master_running;
    std::atomic_int                 m_workers_running;
    std::condition_variable         m_cond;
    std::mutex                      m_mutex;

    uint64_t             m_taskid_counter = 0;
    std::stack<uint64_t> m_taskid_freelist;
    std::set<uint64_t>   m_taskid_finished;

    void worker_fn( int idx );
    // void workgroup_fn( int, int, int, int, const std::function<void(int, int)>& );

public:
    Threadpool( size_t threads, idk::base_allocator* );
    ~Threadpool();

    void update();

    uint64_t createTask( const std::function<void()> &work,
                         const std::function<void()> &callback = [](){} );

    bool taskFinished( uint64_t );
    void join( uint64_t task );

    // void dispatch( int threads_x, int threads_y, int group_x, int group_y,
    //                const std::function<void(int, int)>& );
};





