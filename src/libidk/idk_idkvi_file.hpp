#pragma once

#include <cstddef>
#include "idk_vertex.hpp"
#include "idk_buffer.hpp"

#include "forward_declarations.hpp"


namespace idk
{
    struct idkvi_material;
    struct idkvi_mesh;
    struct idkvi_file;

    enum class idkvi_TextureIndex: uint32_t
    {
        ALBEDO_IDX,
        NORMAL_IDX,
        AO_R_M_IDX,
        NUM_IDX
    };

    enum class idkvi_TextureBit: uint32_t
    {
        ALBEDO_BIT = 1<<0,
        NORMAL_BIT = 1<<1,
        AO_R_M_BIT = 1<<2
    };

}


struct idk::idkvi_material
{
    uint32_t    bitmask;
    std::string textures[4];
};


struct idk::idkvi_mesh
{
    uint32_t material;
    uint32_t basevertex;
    uint32_t baseindex;
};
