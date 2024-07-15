#pragma once

#include <cstdint>
#include <cstddef>
#include <memory>

namespace idk::noisegen3D
{
    // GLuint worley( int w );
    // GLuint worleyvec( int w );
    std::unique_ptr<uint8_t[]> white( size_t w, size_t h, size_t d );
};


namespace idk::noisegen2D
{
    std::unique_ptr<uint8_t[]> u8_whitenoise( size_t w, size_t h );
    std::unique_ptr<uint8_t[]> white_u8( size_t w, size_t h, size_t stride );

};