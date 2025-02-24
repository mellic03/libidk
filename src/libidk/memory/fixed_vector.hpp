#pragma once
#include "base_allocator.hpp"
#include "../idk_log.hpp"

namespace idk
{
    template <typename T>
    class fixed_vector;
}


template <typename T>
class idk::fixed_vector
{
private:
    base_allocator *m_allocator;
    size_t m_cap;
    T *m_base;
    T *m_top;
    T *m_end;

public:
    fixed_vector( size_t capacity, base_allocator *A )
    :   m_allocator(A)
    {
        m_cap  = capacity;
        m_base = static_cast<T*>(A->alloc(capacity*sizeof(T), alignof(T)));
        m_top  = m_base;
        m_end  = m_base + capacity;
        // std::cout << "---------------fixed_vector-------------------\n"
        //           << "base, cap, end:  " << uint64_t(m_base) << ", " << uint64_t(capacity) << ", " << uint64_t(m_top)
        //           << "\n----------------------------------------------\n"; 
        // LOG_INFO("base={}, cap={}", m_base, capacity);
    }

    fixed_vector( size_t capacity, const T &value, base_allocator *A )
    :   fixed_vector(capacity, A)
    {
        for (size_t i=0; i<capacity; i++)
        {
            m_base[i] = value;
        }
    }

    ~fixed_vector()
    {
        // m_allocator->free(m_base);
    }

    fixed_vector(const fixed_vector &) = delete; // Disable copy constructor
    fixed_vector &operator=(const fixed_vector &) = delete; // Disable assignment

    void push( const T &data )
    {
        // LOG_ASSERT(m_top < m_end, "Stack overflow");
        *(m_top++) = data;
    }

    void pop()
    {
        // LOG_ASSERT(m_top >= m_base, "Stack underflow");
        m_top--;
            
        if (!std::is_pointer_v<T>)
        {
            (*m_top).~T();
        }
    }

    T &top()
    {
        // LOG_ASSERT(!empty(), "Stack is empty");
        return *(m_top - 1);
    }
    
    const T &top() const
    {
        // LOG_ASSERT(!empty(), "Stack is empty");
        return *(m_top - 1);
    }


    void push_back( const T &data ) { push(data); }
    void pop_back()                 { pop();      }

    void emplace_back( T &&data )
    {
        // std::cout << "---------------emplace_back(T&&)----------------\n"
        //           << "base, cap, end:  " << uint64_t(m_base) << ", " << uint64_t(m_cap) << ", " << uint64_t(m_end)
        //           << "\n----------------------------------------------\n"; 
        *m_top = data;
        m_top++;
    }

    void emplace_back()
    {
        // std::cout << "---------------emplace_back()-----------------\n"
        //           << "base, cap, end:  " << uint64_t(m_base) << ", " << uint64_t(m_cap) << ", " << uint64_t(m_end)
        //           << "\n----------------------------------------------\n";
        std::construct_at(m_top);
        m_top++;
    }

    T&       front()       { return m_base[0];   }
    const T& front() const { return m_base[0];   }
    T&       back()        { return this->top(); }
    const T& back()  const { return this->top(); }

    T*       data()        { return m_base; }
    const T* data()  const { return m_base; }

    size_t   size()  const { return static_cast<size_t>(m_top - m_base); }
    bool     empty() const { return m_top == m_base; }
    void     clear()       { this->resize(0); }

    void resize( size_t s )
    {
        while (size() > 0) { pop();     }
        while (size() < s) { push(T()); }
    }


    T &operator[] ( size_t i ) { return *(m_base+i); }
    const T &operator[] ( size_t i ) const { return *(m_base+i); }

    struct iterator;
    iterator begin() { return iterator(m_base); };
    iterator end()   { return iterator(m_top);  };
};



template <typename T>
struct idk::fixed_vector<T>::iterator
{
    T *ptr;

    iterator( T *p )                 : ptr(p)         {  };
    iterator( const iterator &other ): ptr(other.ptr) {  };

    iterator &operator ++ ()
    {
        ptr++;
        return *this;
    };

    iterator operator ++ (int)
    {
        return iterator(ptr++);
    };

    bool operator == ( const iterator &rhs ) { return ptr == rhs.ptr; };
    bool operator != ( const iterator &rhs ) { return ptr != rhs.ptr; };
    T &operator * () { return *ptr; };

};