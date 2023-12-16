// #include "idk_bytes.hpp"

// const IDK_ENDIANNESS idk::ProcessorInfo::ENDIANNESS = idk::ProcessorInfo::get_endiannes();


// constexpr void
// idk_readbytes_BIG_ENDIAN( std::ifstream &stream, uint32_t *data, uint32_t nbytes )
// {
//     stream.read(reinterpret_cast<char *>(data), nbytes*sizeof(uint8_t));

//     uint32_t nwords = nbytes/4;
//     for (uint32_t i=0; i<nwords; i++)
//     {
//         uint8_t *temp = (uint8_t *)(&data[i]);
//         data[i] = temp[0]<<0 | temp[1]<<8 | temp[2]<<16 | temp[3]<<24;
//     }
// }


// constexpr void
// idk_readbytes_LITTLE_ENDIAN( std::ifstream &stream, uint32_t *data, uint32_t nbytes )
// {
//     stream.read(reinterpret_cast<char *>(&data), nbytes*sizeof(uint32_t));
// }


// void
// idk::readbytes( std::ifstream &stream, uint32_t *data, uint32_t nbytes )
// {
//     if (idk::ProcessorInfo::ENDIANNESS == IDK_LITTLE_ENDIAN)
//     {
//         idk_readbytes_LITTLE_ENDIAN(stream, data, nbytes);
//     }

//     else
//     {
//         idk_readbytes_BIG_ENDIAN(stream, data, nbytes);
//     }
// }




// constexpr void
// idk_writebytes_BIG_ENDIAN( std::ofstream &stream, uint8_t *data, uint32_t nwords )
// {
//     uint8_t temp[4];

//     for (uint32_t i=0; i<nwords; i++)
//     {
//         temp[i] = data[0]<<0 | data[1]<<8 | data[2]<<16 | data[3]<<24;
//         stream.write(reinterpret_cast<const char *>(&temp[0]), sizeof(uint32_t));
//     }
// }


// constexpr void
// idk_writebytes_LITTLE_ENDIAN( std::ofstream &stream, uint8_t *data, uint32_t nwords )
// {
//     uint8_t temp[4];

//     for (uint32_t i=0; i<nwords; i++)
//     {
//         temp[i] = data[3]<<0 | data[2]<<8 | data[1]<<16 | data[0]<<24;
//         stream.write(reinterpret_cast<const char *>(&temp), sizeof(uint32_t));
//     }
// }



// void
// idk::writebytes( std::ofstream &stream, uint8_t *data, uint32_t nbytes )
// {
//     if (idk::ProcessorInfo::ENDIANNESS == IDK_LITTLE_ENDIAN)
//     {
//         idk_writebytes_LITTLE_ENDIAN(stream, data, nbytes/4);
//     }

//     else
//     {
//         idk_writebytes_BIG_ENDIAN(stream, data, nbytes/4);
//     }
// }



