#include "idk_bytes.hpp"


const bool idk::ProcessorInfo::ENDIANNESS = idk::ProcessorInfo::get_endiannes();


void
idk::readbytes( std::ifstream &stream, uint32_t *data, uint32_t n )
{
    static uint8_t *temp = new uint8_t[4];

    for (uint32_t i=0; i<n; i++)
    {
        stream.read(reinterpret_cast<char *>(&temp), sizeof(uint32_t));
        data[i] = temp[0]<<0 | temp[1]<<8 | temp[2]<<16 | temp[3]<<24;
    }
}



