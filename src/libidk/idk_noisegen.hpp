#pragma once

#include <cstdint>
#include <cstddef>

#include "forward_declarations.hpp"

namespace idk::noisegen3D
{
    // GLuint worley( int w );
    // GLuint worleyvec( int w );
    // GLuint white( int w, int h, int d );
};


namespace idk::noisegen2D
{
    std::unique_ptr<uint8_t[]> u8_whitenoise( size_t w, size_t h );
};