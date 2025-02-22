#include "stack_allocator.hpp"
#include "../idk_assert.hpp"
#include "../idk_log.hpp"


idk::stack_allocator::stack_allocator( size_t capacity )
{
    if (capacity == 0)
    {
        LOG_FATAL("Capacity cannot be zero bytes!");
    }

    LOG_INFO("Capacity: {} bytes", capacity);

    m_capacity = capacity;
    m_base     = new uint8_t[capacity];
    m_tail     = m_base;
    m_end      = m_base + capacity;
}


idk::stack_allocator::~stack_allocator()
{
    LOG_INFO("");
    delete[] m_base;
}


void*
idk::stack_allocator::alloc( size_t nbytes, size_t alignment )
{
    uint8_t *tailptr = m_tail;
    uint8_t *aligned = align_ptr(m_tail, alignment);

    LOG_INFO(
        "nbytes={}, tail={}, aligned={}",
        nbytes, (void *)(tailptr), (void *)(aligned)
    );

    if (aligned+nbytes > m_end)
    {
        size_t A = reinterpret_cast<size_t>(aligned+nbytes);
        LOG_FATAL("Out of memory: {}b / {}b", A, m_capacity);
    }

    LOG_INFO("Allocated {} bytes", nbytes);

    void *usrptr = static_cast<void*>(aligned);
    m_tail = aligned + nbytes;
    m_stack.push({tailptr, usrptr});

    return usrptr; 
}


void
idk::stack_allocator::free( void *usrptr )
{
    IDK_ASSERT("Cannot free, stack is already empty", m_stack.empty() == false);
    IDK_ASSERT("Memory must be freed in LIFO order", usrptr == m_stack.top().usr);

    m_tail = m_stack.top().tail;
    m_stack.pop();
}


