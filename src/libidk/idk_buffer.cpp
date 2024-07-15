#include "idk_buffer.hpp"

#include <cstdlib>
#include <cstring>



void
idk::byte_buffer::_init( size_t cap_nbytes )
{
    m_size = 0;
    m_cap  = cap_nbytes;
    m_data = std::malloc(m_cap);

}


void
idk::byte_buffer::_deinit()
{
    std::free(m_data);
}



idk::byte_buffer::byte_buffer()
{
    _init();
}


idk::byte_buffer::~byte_buffer()
{
    _deinit();

}


idk::byte_buffer::byte_buffer( size_t reserve_nbytes )
{
    _init(reserve_nbytes);
}


idk::byte_buffer::byte_buffer( const byte_buffer &other )
{
    m_data = other.m_data;
    m_size = other.m_size;
    m_cap  = other.m_cap;

    std::memcpy(m_data, other.m_data, other.m_size);
}


idk::byte_buffer::byte_buffer( byte_buffer &&other )
{
    m_data = other.m_data;
    m_size = other.m_size;
    m_cap  = other.m_cap;

    other.m_data = nullptr;
    other.m_size = 0;
    other.m_cap  = 0;
}



size_t
idk::byte_buffer::append( const void *src, size_t nbytes )
{
    if (m_size + nbytes >= m_cap)
    {
        m_cap *= 2;
        m_data = std::realloc(m_data, m_cap);
    }

    std::memcpy(m_data, src, nbytes);
    m_size += nbytes;

    return nbytes;
}

