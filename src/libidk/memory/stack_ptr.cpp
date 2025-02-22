#include "stack_ptr.hpp"
#include "../idk_log.hpp"


void
idk::stack_ptr::init( size_t nbytes )
{
    LOG_INFO("nbytes: {}", nbytes);
    m_allocator = new idk::stack_allocator(nbytes);
}


idk::stack_ptr::stack_ptr( size_t nbytes, size_t alignment )
// :   m_data(m_allocator->alloc(nbytes, alignment))
{
    LOG_INFO("nbytes: {}", nbytes);
    m_data = m_allocator->alloc(nbytes, alignment);
}


idk::stack_ptr::~stack_ptr()
{
    m_allocator->free(m_data);
}


void*
idk::stack_ptr::get()
{
    return m_data;
}