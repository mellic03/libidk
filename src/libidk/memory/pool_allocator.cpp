#include "pool_allocator.hpp"
#include "../idk_assert.hpp"
#include "../idk_log.hpp"



// idk::pool_allocator::pool_allocator( size_t count, size_t stride, size_t alignment,
//                                      base_allocator *A )
// :   m_freelist(count, A)
// {
//     m_cap  = count;
//     m_base = static_cast<uint8_t*>(A->alloc(count*stride, alignment));

//     for (int i=0; i<count; i++)
//     {
//         m_freelist.push(i);
//     }
// }


// idk::pool_allocator::~pool_allocator()
// {
//     delete[] m_base;
// }


// void*
// idk::pool_allocator::alloc( size_t nbytes, size_t alignment )
// {
//     IDK_ASSERT("Capacity exceeded", m_freelist.empty() == false);

//     int idx = m_freelist.top();
//               m_freelist.pop();

//     return static_cast<void*>(m_base + idx);

//     // m_tail = align_ptr(m_tail, alignment) + nbytes;
//     // return static_cast<void*>(m_tail - nbytes);
// }


// void
// idk::pool_allocator::free( void *ptr )
// {
    
// }