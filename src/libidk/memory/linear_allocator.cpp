#include "linear_allocator.hpp"
#include "../idk_assert.hpp"
#include "../idk_bitmanip.hpp"
#include "../idk_log.hpp"

idk::linear_allocator::linear_allocator( size_t nbytes, base_allocator *A )
:   linear_allocator(nbytes, A->alloc(nbytes, 8))
{

}


idk::linear_allocator::linear_allocator( size_t nbytes, void *baseptr )
{
    IDK_ASSERT("Capacity must be > 0", nbytes > 0);

    m_capacity = nbytes;
    m_base     = (baseptr) ? (uint8_t*)baseptr : new uint8_t[nbytes + 16];
    m_tail     = m_base;
    m_end      = m_base + nbytes;

    // m_top.store(reinterpret_cast<size_t>(m_base));

}


idk::linear_allocator::~linear_allocator()
{
    // delete[] m_base;
}


void*
idk::linear_allocator::alloc( size_t nbytes, size_t alignment )
{
    // uint8_t *top = reinterpret_cast<uint8_t*>(m_top.fetch_add(nbytes));
    //          top = align_ptr(top, alignment);
    // return static_cast<void*>(top);

    m_tail = idk::ptr_align(m_tail, alignment) + nbytes;

    LOG_ASSERT(
        m_tail < m_end,
        "Out of memory ({} / {} bytes)",
        static_cast<size_t>(m_tail-m_base),
        static_cast<size_t>(m_end-m_base)
    );

    return static_cast<void*>(m_tail - nbytes);
}


void
idk::linear_allocator::free( void *ptr )
{

}


void
idk::linear_allocator::clear()
{
    m_tail = m_base;
}