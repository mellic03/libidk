#pragma once

#include "idk_texturegen.hpp"


template <typename T>
std::unique_ptr<T[]>
idk::texturegen::genRGBA( size_t w, size_t h, T r, T g, T b, T a )
{
    auto data = std::unique_ptr<T[]>(new T[4*w*h]);

    for (size_t i=0; i<w*h; i++)
    {
        data[4*i+0] = r;
        data[4*i+1] = g;
        data[4*i+2] = b;
        data[4*i+3] = a;
    }

    return data;
}

template <typename T>
std::unique_ptr<T[]>
idk::texturegen::genRA( size_t w, size_t h, T r, T a )
{
    return idk::texturegen::genRGBA<T>(w, h, r, r, r, a);
}
