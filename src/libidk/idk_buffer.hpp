#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>


namespace idk
{
    class byte_buffer;
};



class idk::byte_buffer
{
private:
    // std::shared_ptr<void> m_data;
    void  *m_data = nullptr;
    size_t m_size = 0;
    size_t m_cap  = 0;

    void _init( size_t cap_nbytes = 32 );
    void _deinit();

public:

    byte_buffer();
    ~byte_buffer();

    byte_buffer( size_t reserve_nbytes );
    byte_buffer( const byte_buffer& );
    byte_buffer( byte_buffer&& );

    /**
     * @return Size of buffer after copy.
    */
    size_t append( const void *src, size_t nbytes );

    const void *data() const { return m_data; };
};