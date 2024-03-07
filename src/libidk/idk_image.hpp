#pragma once

#include <cstdint>
#include <cstddef>
#include <memory>

namespace idk
{

    enum RawImageFormat: uint32_t
    {
        IDK_IMAGEFORMAT_U8  = 0,
        IDK_IMAGEFORMAT_U16 = 1,
        IDK_IMAGEFORMAT_U32 = 2,
        IDK_IMAGEFORMAT_F32 = 3,
        IDK_IMAGEFORMAT_F64 = 4
    };

    enum RawImageLayout: uint32_t
    {
        IDK_IMAGELAYOUT_R    = 0,
        IDK_IMAGELAYOUT_RG   = 1,
        IDK_IMAGELAYOUT_RGB  = 2,
        IDK_IMAGELAYOUT_RGBA = 3,
    };


    struct RawImageHeader
    {
        uint32_t major;
        uint32_t minor;

        uint32_t format;
        uint32_t layout;
        uint32_t w, h;

        uint32_t nbytes;
    };


    uint32_t RawImage_sizeof_format( uint32_t format );
    uint32_t RawImage_sizeof_layout( uint32_t layout );
    uint32_t RawImage_nbytes( const idk::RawImageHeader &header );
    void     RawImage_write( const char *filepath, idk::RawImageHeader &header, void *data );
    std::unique_ptr<uint8_t[]> RawImage_read( const char *filepath, idk::RawImageHeader &header );


};

