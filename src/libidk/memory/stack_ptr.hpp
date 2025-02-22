#pragma once
#include "stack_allocator.hpp"

namespace idk
{
    class stack_ptr;
}



class idk::stack_ptr
{
private:
    inline static idk::stack_allocator *m_allocator = nullptr;
    void *m_data;

public:
    static void init( size_t stack_capacity );

    // stack_ptr() {  };
    stack_ptr( size_t nbytes, size_t alignment );
    ~stack_ptr();
    void *get();
    // template <typename T>
    // const T *get()
    // {
    //     return static_cast<T*>(m_data);
    // }
};