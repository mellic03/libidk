#include "common.hpp"



uint8_t
idk::glVersionFlags( int major, int minor )
{
    return (uint8_t(major) << 4) + uint8_t(minor);
}


int
idk::glVersionMajor( uint8_t version )
{
    return int(version) >> 4;
}


int
idk::glVersionMinor( uint8_t version )
{
    return int(version & 0b00001111);
}


