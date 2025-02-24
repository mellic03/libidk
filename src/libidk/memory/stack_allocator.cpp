#include "stack_allocator.hpp"
#include "../idk_assert.hpp"
#include "../idk_bitmanip.hpp"
#include "../idk_log.hpp"


idk::stack_allocator::stack_allocator( size_t nbytes, void *baseptr )
:   linear_allocator(nbytes, baseptr)
{
    m_tail = m_base + sizeof(node_type);
}


void*
idk::stack_allocator::alloc( size_t nbytes, size_t alignment )
{
    uint8_t *tailptr = m_tail;
    uint8_t *aligned = idk::ptr_align(m_tail+sizeof(node_type), alignment);
    m_tail = aligned + nbytes;

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
    
    m_top = reinterpret_cast<node_type*>(aligned - sizeof(node_type));

    std::cout << "m_base: " << (void *)(m_base) << std::endl;
    std::cout << "m_end: " << (void *)(m_end) << std::endl;
    std::cout << "m_top: " << (void *)(m_top) << std::endl;
    
    m_top->tailptr = tailptr;
    m_top->usrptr  = static_cast<void*>(aligned);

    return m_top->usrptr;
}


void
idk::stack_allocator::free( void *ptr )
{
    if (ptr != m_top->usrptr)
    {
        LOG_INFO("usrptr={} m_top->usrptr={}", ptr, m_top->usrptr);
        LOG_FATAL("Memory must be freed in LIFO order");
    }

    m_tail = static_cast<uint8_t*>(m_top->tailptr);
    ptr = nullptr;
}


