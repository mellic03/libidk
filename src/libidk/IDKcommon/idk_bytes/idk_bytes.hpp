// #pragma once

// #include <fstream>
// #include <cstdint>


// enum IDK_ENDIANNESS { IDK_LITTLE_ENDIAN, IDK_BIG_ENDIAN };

// namespace idk { struct ProcessorInfo; };


// struct idk::ProcessorInfo
// {
//     static IDK_ENDIANNESS get_endiannes()
//     {
//         const uint32_t n = 1;

//         if (reinterpret_cast<const char *>(&n)[0] == 1)
//         {
//             return IDK_LITTLE_ENDIAN;
//         }

//         return IDK_BIG_ENDIAN;
//     }

//     static const IDK_ENDIANNESS ENDIANNESS;
// };


// namespace idk
// {
//     void readbytes  ( std::ifstream &stream, uint32_t *data, uint32_t nbytes );
//     void writebytes ( std::ofstream &stream, uint8_t  *data, uint32_t nbytes );
// };

