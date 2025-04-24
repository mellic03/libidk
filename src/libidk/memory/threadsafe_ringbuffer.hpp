#pragma once

#include <thread>
#include <atomic>
#include <mutex>
#include <deque>


namespace idk
{
    template <typename T, size_t capacity>
    class threadsafe_RingBuffer;
}



template <typename T, size_t capacity>
class idk::threadsafe_RingBuffer
{
private:
    T data[capacity];
    size_t head = 0;
    size_t tail = 0;
    std::mutex m_mutex;

public:
	inline bool push_back(const T& item)
	{
	    std::scoped_lock<std::mutex> lock(m_mutex);

		size_t next = (head + 1) % capacity;

		if (next == tail)
		{
		    return false;
		}

        data[head] = item;
        head = next;

        return true;
	}

	inline bool pop_front( T& item )
	{
	    std::scoped_lock<std::mutex> lock(m_mutex);

		if (tail == head)
		{
            return false;
		}

        item = data[tail];
        tail = (tail + 1) % capacity;

        return true;
	}
};


