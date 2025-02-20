#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>


namespace idk
{
    class byte_buffer;
};


class idk::byte_buffer
{
private:

public:
    std::vector<uint32_t> m_data;
    byte_buffer();
    byte_buffer( size_t reserve_nbytes );
    ~byte_buffer();

    size_t write( const void *src, size_t nbytes );
    size_t read( void *dst, size_t offset, size_t nbytes );
    size_t writeFile( const char *path );
    size_t readFile( const char *path );

    template <typename T>
    size_t writeT( const T &src )
    {
        return write(reinterpret_cast<const void*>(&src), sizeof(T));
    }

    template <typename T>
    size_t readT( const T &src, size_t offset )
    {
        return read(reinterpret_cast<void*>(&src), offset, sizeof(T));
    }


};