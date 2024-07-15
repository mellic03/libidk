#include <ctime>
#include <vector>
#include <random>

#include "idk_noisegen.hpp"


std::unique_ptr<uint8_t[]>
idk::noisegen2D::u8_whitenoise( size_t w, size_t h )
{
    auto data = std::unique_ptr<uint8_t[]>(new uint8_t[4*w*h]);

    for (size_t i=0; i<4*w*h; i++)
    {
        data[i] = rand() % 255;
    }

    return data;
}



std::unique_ptr<uint8_t[]>
idk::noisegen2D::white_u8( size_t w, size_t h, size_t stride )
{
    auto data = std::unique_ptr<uint8_t[]>(new uint8_t[stride*w*h]);

    for (size_t i=0; i<stride*w*h; i++)
    {
        data[i] = rand() % 255;
    }

    return data;
}




std::unique_ptr<uint8_t[]>
idk::noisegen3D::white( size_t w, size_t h, size_t d )
{
    auto data = std::unique_ptr<uint8_t[]>(new uint8_t[4*w*h*d]);

    for (size_t i=0; i<4*w*h*d; i++)
    {
        data[i] = rand() % 255;
    }

    return data;
}

