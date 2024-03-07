#include "idk_image.hpp"

#include <fstream>


uint32_t
idk::RawImage_sizeof_format( uint32_t format )
{
    switch (format)
    {
        using enum RawImageFormat;

        case IDK_IMAGEFORMAT_U8:  return sizeof(uint8_t);
        case IDK_IMAGEFORMAT_U16: return sizeof(uint16_t);
        case IDK_IMAGEFORMAT_U32: return sizeof(uint32_t);
        case IDK_IMAGEFORMAT_F32: return sizeof(float);
        case IDK_IMAGEFORMAT_F64: return sizeof(double);
    }

    return 0;
}


uint32_t
idk::RawImage_sizeof_layout( uint32_t layout )
{
    switch (layout)
    {
        using enum RawImageLayout;

        case IDK_IMAGELAYOUT_R:    return 1;
        case IDK_IMAGELAYOUT_RG:   return 2;
        case IDK_IMAGELAYOUT_RGB:  return 3;
        case IDK_IMAGELAYOUT_RGBA: return 4;
    }

    return 0;
}


uint32_t
idk::RawImage_nbytes( const idk::RawImageHeader &header )
{
    return header.w * header.h * RawImage_sizeof_layout(header.layout) * RawImage_sizeof_format(header.format);
}


void
idk::RawImage_write( const char *filepath, idk::RawImageHeader &header, void *data )
{
    std::ofstream stream(filepath, std::ios::binary);

    header.nbytes = RawImage_nbytes(header);
    stream.write(reinterpret_cast<const char *>(&header), sizeof(idk::RawImageHeader));
    stream.write(reinterpret_cast<const char *>(data), header.nbytes);
}


std::unique_ptr<uint8_t[]> 
idk::RawImage_read( const char *filepath, idk::RawImageHeader &header )
{
    std::ifstream stream(filepath, std::ios::binary);

    stream.read(reinterpret_cast<char *>(&header), sizeof(idk::RawImageHeader));

    auto data = std::make_unique<uint8_t[]>(header.nbytes);
    stream.read(reinterpret_cast<char *>(data.get()), header.nbytes);

    return data;
}
