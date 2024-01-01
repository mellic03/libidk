#include "idk_gltools.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <libidk/IDKcore/libidk.hpp>

#include "../IDKcore/idk_utility.hpp"



// GLuint
// idk::gltools::loadTextureArray( size_t w, size_t h, size_t d, void **data, const glTextureConfig &config )
// {
//     GLuint texture_id;

//     gl::createTextures(GL_TEXTURE_2D_ARRAY, 1, &texture_id);

//     gl::textureStorage3D(texture_id, 0, config.internalformat, w, h, d);
//     gl::textureSubImage3D(texture_id, 0, 0, 0, 0, w, h, d, config.format, config.datatype, data[1]);

//     gl::textureStorage2D(texture_id, 1, config.internalformat, w, h);
//     gl::textureSubImage2D(texture_id, 0, 0, 0, w, h, config.format, config.datatype, data);

//     gl::textureParameteri(texture_id, GL_TEXTURE_MIN_FILTER, config.minfilter);
//     gl::textureParameteri(texture_id, GL_TEXTURE_MAG_FILTER, config.magfilter);
//     gl::textureParameteri(texture_id, GL_TEXTURE_WRAP_S, config.wrap_s);
//     gl::textureParameteri(texture_id, GL_TEXTURE_WRAP_T, config.wrap_t);


//     if (config.anisotropic)
//     {
//         float anisotropy;
//         gl::getFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &anisotropy);
//         gl::textureParameterf(texture_id, GL_TEXTURE_MAX_ANISOTROPY, anisotropy);
//     }

//     if (config.genmipmap)
//     {
//         gl::generateTextureMipmap(texture_id);
//     }

//     else if (config.setmipmap)
//     {
//         gl::textureParameteri(texture_id, GL_TEXTURE_BASE_LEVEL, config.texbaselevel);
//         gl::textureParameteri(texture_id, GL_TEXTURE_MAX_LEVEL,  config.texmaxlevel);
//     }

//     return texture_id;
// }



GLuint
idk::gltools::loadTexture( size_t w, size_t h, void *data, const glTextureConfig &config )
{
    GLuint texture_id;
    gl::createTextures(config.target, 1, &texture_id);

    GLsizei levels = 1 + floor(log2(idk::max(w, h)));
            levels = config.genmipmap ? levels : 1;

    gl::textureStorage2D(texture_id, levels, config.internalformat, w, h);
    gl::textureSubImage2D(texture_id, 0, 0, 0, w, h, config.format, config.datatype, data);

    gl::textureParameteri(texture_id, GL_TEXTURE_MIN_FILTER, config.minfilter);
    gl::textureParameteri(texture_id, GL_TEXTURE_MAG_FILTER, config.magfilter);
    gl::textureParameteri(texture_id, GL_TEXTURE_WRAP_S, config.wrap_s);
    gl::textureParameteri(texture_id, GL_TEXTURE_WRAP_T, config.wrap_t);

    if (config.anisotropic)
    {
        float anisotropy;
        gl::getFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &anisotropy);
        gl::textureParameterf(texture_id, GL_TEXTURE_MAX_ANISOTROPY, anisotropy);
    }

    if (config.genmipmap)
    {
        gl::generateTextureMipmap(texture_id);
    }

    // else if (config.setmipmap)
    // {
    //     gl::textureParameteri(texture_id, GL_TEXTURE_BASE_LEVEL, config.texbaselevel);
    //     gl::textureParameteri(texture_id, GL_TEXTURE_MAX_LEVEL,  config.texmaxlevel);
    // }

    return texture_id;
}



// GLuint
// idk::gltools::loadTexture( std::string filepath, const glTextureConfig &config )
// {
//     SDL_Surface      *tmp    = IMG_Load(filepath.c_str());
//     SDL_PixelFormat  *target = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
//     SDL_Surface      *img    = SDL_ConvertSurface(tmp, target, 0);

//     GLuint texture_id = gltools::loadTexture(img->w, img->h, (uint32_t *)(img->pixels), config);

//     SDL_FreeFormat(target);
//     SDL_FreeSurface(tmp);
//     SDL_FreeSurface(img);

//     return texture_id;
// }



static glm::vec4
interpolate(glm::vec4 p00, glm::vec4 p10, glm::vec4 p01, glm::vec4 p11, float u, float v)
{
    float factor_u = u - floor(u);
    float factor_v = v - floor(v);

    glm::vec4 bottom = (p10 - p00) * factor_u + p00;
    glm::vec4 top    = (p11 - p01) * factor_u + p01;

    return (top - bottom) * factor_v + bottom;
}


static glm::vec4
t_query( int u, int v, size_t w, size_t h, std::unique_ptr<uint8_t[]> &data )
{
    glm::vec4 result = glm::vec4(
        float(data[4*w*v + 4*u + 0]),
        float(data[4*w*v + 4*u + 1]),
        float(data[4*w*v + 4*u + 2]),
        float(data[4*w*v + 4*u + 3])
    );

    return result;
}



glm::vec4
idk::gltools::textureQuery( float u, float v, size_t w, size_t h,
                            std::unique_ptr<uint8_t[]> &data )
{
    u = u * 0.5f + 0.5f;
    v = v * 0.5f + 0.5f;

    int x = int(w*u) % w;
    int y = int(h*v) % h;


    glm::vec4 h00 = t_query(x,   y,   w, h, data);
    glm::vec4 h01 = t_query(x,   y+1, w, h, data);
    glm::vec4 h10 = t_query(x+1, y,   w, h, data);
    glm::vec4 h11 = t_query(x+1, y+1, w, h, data);

    glm::vec3 weights = idk::calculate_barycentric(
        float(w)*u, float(h)*v,
        glm::vec2(x,   y  ),
        glm::vec2(x,   y+1),
        glm::vec2(x+1, y  )
    );


    if (weights[0] >= 0.0f && weights[1] >= 0.0f && weights[2] >= 0.0f)
    {
        return weights[0]*h00 + weights[1]*h01 + weights[2]*h10;
    }

    weights = idk::calculate_barycentric(
        float(w)*u, float(h)*v,
        glm::vec2(x+1, y+1),
        glm::vec2(x,   y+1),
        glm::vec2(x+1, y  )
    );

    return weights[0]*h11 + weights[1]*h01 + weights[2]*h10;

}




GLuint
idk::gltools::loadCubemap( std::string root, std::vector<std::string> filenames, glTextureConfig config )
{
    GLuint texture_id;

    gl::genTextures(1, &texture_id);
    gl::bindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

    for (int i=0; i<6; i++)
    {
        std::string       filepath = root + filenames[i];
        SDL_Surface      *tmp      = IMG_Load(filepath.c_str());
        SDL_PixelFormat  *target   = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
        SDL_Surface      *img      = SDL_ConvertSurface(tmp, target, 0);

        gl::texImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
            0, config.internalformat, img->w, img->h, 0, config.format,
            config.datatype, (void *)(img->pixels)
        );

        SDL_FreeFormat(target);
        SDL_FreeSurface(tmp);
        SDL_FreeSurface(img);
    }

    gl::texParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, config.minfilter);
    gl::texParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, config.magfilter);
    gl::texParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl::texParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    gl::texParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    if (config.genmipmap)
    {
        gl::generateMipmap(GL_TEXTURE_CUBE_MAP);
    }

    else if (config.setmipmap)
    {
        gl::texParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, config.texbaselevel);
        gl::texParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL,  config.texmaxlevel);
    }

    return texture_id;
}


void
idk::gltools::loadCubemapMip( std::string directory, std::vector<std::string> filenames,
                              glTextureConfig config, GLuint cubemap, GLint level )
{
    gl::bindTexture(GL_TEXTURE_CUBE_MAP, cubemap);

    for (GLuint face=0; face<6; face++)
    {
        std::string       filepath = directory + std::to_string(level) + filenames[face];
        // std::cout << "loading level " << level << ": " << filepath << "\n";

        SDL_Surface      *tmp    = IMG_Load(filepath.c_str());
        SDL_PixelFormat  *target = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
        SDL_Surface      *img    = SDL_ConvertSurface(tmp, target, 0);

        gl::texImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, 
            level, config.internalformat, img->w, img->h, 0, config.format,
            config.datatype, (void *)(img->pixels)
        );

        SDL_FreeFormat(target);
        SDL_FreeSurface(tmp);
        SDL_FreeSurface(img);
    }

}


idk::glTexture
idk::gltools::loadTexture( const std::string &filepath, const glTextureConfig &config )
{
    SDL_Surface      *tmp    = IMG_Load(filepath.c_str());
    SDL_PixelFormat  *target = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    SDL_Surface      *img    = SDL_ConvertSurface(tmp, target, 0);

    GLuint texture_id = gltools::loadTexture(img->w, img->h, (uint32_t *)(img->pixels), config);

    SDL_FreeFormat(target);
    SDL_FreeSurface(tmp);
    SDL_FreeSurface(img);

    idk::glTexture texture(
        texture_id,
        glm::ivec2(img->w, img->h),
        config
    );

    return texture;
}


idk::glTexture
idk::gltools::loadTexture2( size_t w, size_t h, void *data, const glTextureConfig &config )
{
    GLuint texture_id = gltools::loadTexture(w, h, (uint32_t *)(data), config);

    idk::glTexture texture(
        texture_id,
        glm::ivec2(w, h),
        config
    );

    return texture;
}
