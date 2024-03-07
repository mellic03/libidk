#include <memory>
#include <iostream>

#include "idk_texturegen.hpp"
#include "idk_random.hpp"


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



static int yeahboye( glm::vec3 dir )
{
    const glm::vec3 directions[6]
    {
        glm::vec3( -1.0f,  0.0f,  0.0f ),
        glm::vec3( +1.0f,  0.0f,  0.0f ),
        glm::vec3(  0.0f, -1.0f,  0.0f ),
        glm::vec3(  0.0f, +1.0f,  0.0f ),
        glm::vec3(  0.0f,  0.0f, -1.0f ),
        glm::vec3(  0.0f,  0.0f, +1.0f )
    };


    int best_idx = -1;
    int best_dot = -1.0f;

    for (int i=0; i<6; i++)
    {
        float dot = glm::dot(dir, directions[i]);

        if (dot > best_dot)
        {
            best_dot = dot;
            best_idx = i;
        }
    }

    return best_idx;
}


static glm::vec2 yeahboye2( int face, glm::vec3 dir )
{
    dir = glm::abs(dir);
    glm::vec2 texcoord;

    // X-axis
    if (face < 2)
    {
        texcoord = glm::vec2(dir.z, dir.y);
    }

    // Y-axis
    else if (face < 4)
    {
        texcoord = glm::vec2(dir.x, dir.z);
    }

    // Z-axis
    else
    {
        texcoord = glm::vec2(dir.x, dir.y);
    }

    texcoord = glm::mod(texcoord * 2.0f, 1.0f);

    return texcoord;
}




std::unique_ptr<glm::vec4[]>
idk::texturegen::RGBA16F_CubemapStars( size_t w, float density )
{
    size_t face_size    = w*w;
    size_t cubemap_size = 6*face_size;
    size_t num_stars    = size_t(density * float(face_size));

    auto data = std::unique_ptr<glm::vec4[]>(new glm::vec4[cubemap_size]);

    for (size_t i=0; i<cubemap_size; i++)
    {
        data[i] = glm::vec4(0.0f);
    }

    for (size_t i=0; i<num_stars; i++)
    {
        glm::vec3 dir = glm::vec3(
            idk::randf() * 2.0f - 1.0f,
            idk::randf() * 2.0f - 1.0f,
            idk::randf() * 2.0f - 1.0f
        );

        dir = glm::normalize(dir);

        int        face  = yeahboye(dir);
        glm::vec2  uv    = yeahboye2(face, dir);
        glm::ivec2 texel = glm::ivec2(float(w) * uv);

        int idx = w*texel.y + texel.x;
        data[idx] = glm::vec4(2.0f);
    }

    return data;
}

