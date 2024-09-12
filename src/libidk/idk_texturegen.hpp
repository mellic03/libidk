#pragma once

#include <cstdint>
#include <cstddef>
#include "idk_glm.hpp"

#include "forward_declarations.hpp"


namespace idk::texturegen
{
    template <typename T>
    std::unique_ptr<T[]> genRGBA( size_t w, size_t h, T r, T g, T b, T a );

    template <typename T>
    std::unique_ptr<T[]> genRGB( size_t w, size_t h, T r, T g, T b );

    template <typename T>
    std::unique_ptr<T[]> genRA( size_t w, size_t h, T r, T a );

    std::unique_ptr<uint8_t[]> u8_RGBA( size_t w, size_t h, uint8_t r, uint8_t g, uint8_t b, uint8_t a );
    std::unique_ptr<float[]>   f32_RGBA( size_t w, size_t h, float r, float g, float b, float a );

    std::unique_ptr<glm::vec4[]> RGBA16F_CubemapStars( size_t w, float density );

};


#include "idk_texturegen.inl"

