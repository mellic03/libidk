#include "idk_buffer.hpp"
#include <fstream>



idk::byte_buffer::byte_buffer()
{

}


idk::byte_buffer::~byte_buffer()
{

}


size_t
idk::byte_buffer::write( const void *ptr, size_t nbytes )
{
    const uint32_t *src = reinterpret_cast<const uint32_t*>(ptr);
    const size_t nwords = nbytes/4;

    for (size_t i=0; i<nwords; i++)
    {
        m_data.push_back(src[i]);
    }

    return nbytes;
}



size_t
idk::byte_buffer::read( void *ptr, size_t offset, size_t nbytes )
{
    uint32_t *dst = reinterpret_cast<uint32_t*>(ptr);
    const size_t nwords = nbytes/4;

    for (size_t i=0; i<nwords; i++)
    {
        dst[i] = m_data[offset+i];
    }

    return nbytes;
}



size_t
idk::byte_buffer::writeFile( const char *path )
{
    std::ofstream stream(path, std::ios::binary);

    uint32_t nwords = m_data.size();
    stream.write(reinterpret_cast<const char*>(&nwords), sizeof(uint32_t));
    stream.write(reinterpret_cast<const char*>(m_data.data()), m_data.size());
    stream.close();

    return nwords;
}


size_t
idk::byte_buffer::readFile( const char *path )
{
    std::ifstream stream(path, std::ios::binary);

    uint32_t nwords;
    stream.read(reinterpret_cast<char*>(&nwords), sizeof(uint32_t));
    m_data.resize(nwords);

    stream.read(reinterpret_cast<char*>(m_data.data()), 4*nwords);
    stream.close();

    return nwords;
}

