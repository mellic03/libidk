#include "idk_threadpool.hpp"
#include <iostream>


idk::Threadpool::Threadpool( size_t threads, idk::base_allocator *A )
{
    m_master_running.store(true);
    m_workers_running.store(0);

    for (int i=0; i<threads; i++)
    {
        m_threads.push_back(std::thread(&idk::Threadpool::worker_fn, this, i));
        m_threads[i].detach();
        m_workers_running++;
    }
}


idk::Threadpool::~Threadpool()
{
    m_master_running.store(false);

    while (m_workers_running.load() > 0)
    {
        // std::cout << "m_workers_running: " << m_threads_running.load() << "\n";
    }
}



void
idk::Threadpool::worker_fn( int idx )
{
    Task task;

    while (m_master_running.load() == true)
    {
        if (m_inbuffer.pop_front(task))
        {
            task.work();
            m_outbuffer.push_back(task);
        }

        else
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cond.wait(lock);
            // std::this_thread::sleep_for(std::chrono::milliseconds(4));
        }
    }

    m_workers_running--;
}


uint64_t
idk::Threadpool::createTask( const std::function<void()> &work,
                             const std::function<void()> &callback )
{
    LOG_ADV(log_flag::EVERYTHING, "Entered function");

    uint64_t taskid;

    if (m_taskid_freelist.empty() == false)
    {
        taskid = m_taskid_freelist.top();
                 m_taskid_freelist.pop();
    }

    else
    {
        taskid = m_taskid_counter;
                 m_taskid_counter++;
    }
    
    if (m_threads.size() > 0)
    {
        m_inbuffer.push_back({taskid, work, callback});
        m_cond.notify_one();
    }

    else
    {
        work();
        callback();
    }

    LOG_ADV(log_flag::EVERYTHING, "Created Task[{}]", taskid);

    return taskid;
}


bool
idk::Threadpool::taskFinished( uint64_t taskid )
{
    if (m_taskid_finished.contains(taskid))
    {
        m_taskid_finished.erase(taskid);
        m_taskid_freelist.push(taskid);
        return true;
    }

    return false;
}


void
idk::Threadpool::join( uint64_t taskid )
{
    while (taskFinished(taskid) == false)
    {
        this->update();
    }
}



void
idk::Threadpool::update()
{
    LOG_ADV(log_flag::EVERYTHING, "Entered function");

    Task task;

    while (m_outbuffer.empty() == false)
    {
        if (m_outbuffer.pop_front(task))
        {
            LOG_ADV(log_flag::EVERYTHING, "Task[{}].callback()", task.id);
            task.callback();
            m_taskid_finished.insert(task.id);
        }
    }

    LOG_ADV(log_flag::EVERYTHING, "Return");
}



// void
// idk::Threadpool::workgroup_fn( int start_x, int start_y, int group_x, int group_y,
//                                const std::function<void(int, int)> &work )
// {
//     for (int x=start_x; x<start_x+group_x; x++)
//     {
//         for (int y=start_y; y<start_y+group_y; y++)
//         {
//             work(x, y);
//         }
//     }
// }


// void
// idk::Threadpool::dispatch( int threads_x, int threads_y, int group_x, int group_y,
//                            const std::function<void(int, int)> &work )
// {
//     for (int x=0; x<threads_x; x++)
//     {
//         for (int y=0; y<threads_y; y++)
//         {
//             workgroup_fn(x*group_x, y*group_y, group_x, group_y, work);
//         }
//     }

// }
