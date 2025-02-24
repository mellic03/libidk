#include "ring_allocator.hpp"
#include "../idk_assert.hpp"
#include "../idk_bitmanip.hpp"
#include "../idk_log.hpp"


void*
idk::ring_allocator::alloc( size_t nbytes, size_t alignment )
{
    IDK_ASSERT(
        "Requested size must be smaller than ring buffer",
        nbytes < m_capacity
    );

    m_tail = idk::ptr_align(m_tail, alignment) + nbytes;

    if (m_tail > m_end)
    {
        m_tail = 0;
        m_tail = idk::ptr_align(m_tail, alignment) + nbytes;
    }

    return static_cast<void*>(m_tail - nbytes);
}

