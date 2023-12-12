#pragma once

#include <fstream>
#include <cstdint>



namespace idk { struct ProcessorInfo; };


struct idk::ProcessorInfo
{
    enum IDK_ENDIANNESS { IDK_LITTLE_ENDIAN, IDK_BIG_ENDIAN };

    static IDK_ENDIANNESS get_endiannes()
    {
        const uint32_t n = 1;

        if (reinterpret_cast<const char *>(&n)[0] == 1)
        {
            return IDK_LITTLE_ENDIAN;
        }

        return IDK_BIG_ENDIAN;
    }

    static const bool ENDIANNESS;
};


const bool idk::ProcessorInfo::ENDIANNESS = idk::ProcessorInfo::get_endiannes();



namespace idk
{
    void readbytes( std::ifstream &, uint32_t *, uint32_t n );
};



