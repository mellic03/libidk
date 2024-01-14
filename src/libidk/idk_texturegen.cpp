#include <memory>
#include "idk_texturegen.hpp"


std::unique_ptr<uint8_t[]>
idk::texturegen::u8_RGBA( size_t w, size_t h, uint8_t r, uint8_t g, uint8_t b, uint8_t a )
{
    auto data = std::unique_ptr<uint8_t[]>(new uint8_t[4*w*h]);

    for (size_t i=0; i<w*h; i++)
    {
        data[4*i+0] = r;
        data[4*i+1] = g;
        data[4*i+2] = b;
        data[4*i+3] = a;
    }

    return data;
}


std::unique_ptr<float[]>
idk::texturegen::f32_RGBA( size_t w, size_t h, float r, float g, float b, float a )
{
    auto data = std::unique_ptr<float[]>(new float[4*w*h]);

    for (size_t i=0; i<w*h; i++)
    {
        data[4*i+0] = r;
        data[4*i+1] = g;
        data[4*i+2] = b;
        data[4*i+3] = a;
    }

    return data;
}
