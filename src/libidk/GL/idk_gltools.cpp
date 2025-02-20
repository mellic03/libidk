#include "idk_gltools.hpp"
#include "../idk_math.hpp"

#include "../idk_assert.hpp"
#include <libidk/idk_log2.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;


GLuint
idk::gltools::loadTexture2D( uint32_t w, uint32_t h, void *data, const glTextureConfig &config )
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

    return texture_id;
}


GLuint
idk::gltools::loadTexture3D( uint32_t w, uint32_t h, uint32_t d, void *data, const glTextureConfig &config )
{
    GLuint texture_id;
    gl::createTextures(config.target, 1, &texture_id);

    GLsizei levels = 1 + floor(log2(idk::max(w, idk::max(h, d))));
            levels = config.genmipmap ? levels : 1;

    gl::textureStorage3D(texture_id, levels, config.internalformat, w, h, d);
    gl::textureSubImage3D(texture_id, 0, 0, 0, 0, w, h, d, config.format, config.datatype, data);

    gl::textureParameteri(texture_id, GL_TEXTURE_MIN_FILTER, config.minfilter);
    gl::textureParameteri(texture_id, GL_TEXTURE_MAG_FILTER, config.magfilter);
    gl::textureParameteri(texture_id, GL_TEXTURE_WRAP_S, config.wrap_s);
    gl::textureParameteri(texture_id, GL_TEXTURE_WRAP_T, config.wrap_t);


    if (config.comp_fn != 0 && config.comp_mode != 0)
    {
        gl::textureParameteri(texture_id, GL_TEXTURE_COMPARE_FUNC, config.comp_fn);
        gl::textureParameteri(texture_id, GL_TEXTURE_COMPARE_MODE, config.comp_mode);
    }

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

    return texture_id;
}



GLuint
idk::gltools::allocateTexture2DArray( uint32_t w, uint32_t h, uint32_t layers, void *data,
                                      const glTextureConfig &config )
{
    GLuint texture_id;
    gl::createTextures(GL_TEXTURE_2D_ARRAY, 1, &texture_id);

    GLsizei levels = 1 + floor(log2(idk::max(w, h)));
            levels = config.genmipmap ? levels : 1;

    gl::textureStorage3D(texture_id, levels, config.internalformat, w, h, layers);
    // gl::textureSubImage2D(texture_id, 0, 0, 0, w, h, config.format, config.datatype, data);

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

    return texture_id;
}


GLuint
idk::gltools::loadTexture2DArray( uint32_t w, uint32_t h, const std::vector<std::string> &textures,
                                  const glTextureConfig &config )
{
    GLuint texture = allocateTexture2DArray(w, h, textures.size(), nullptr, config);

    for (int i=0; i<textures.size(); i++)
    {
        void *pixels = loadPixels(textures[i], nullptr, nullptr, true);

        gl::textureSubImage3D(
            texture,
            0,
            0, 0, i,
            w, h, 1,
            config.format,
            config.datatype,
            pixels
        );

        std::free(pixels);
    }

    if (config.genmipmap)
    {
        gl::generateTextureMipmap(texture);
    }

    return texture;
}





GLuint
idk::gltools::allocateTextureCube( uint32_t w, uint32_t h, const glTextureConfig &config )
{
    GLuint texture;
    gl::createTextures(GL_TEXTURE_CUBE_MAP, 1, &texture);

    GLsizei levels = 1 + floor(log2(idk::max(w, h)));
            levels = config.genmipmap ? levels : 1;

    gl::textureStorage2D(texture, levels, config.internalformat, w, h);

    for (uint32_t i=0; i<6; i++)
    {
        gl::textureSubImage3D(
            texture, 0,
            0, 0, i,
            w, h, 1,
            config.format,
            config.datatype,
            nullptr
        );
    }

    gl::textureParameteri(texture, GL_TEXTURE_MIN_FILTER, config.minfilter);
    gl::textureParameteri(texture, GL_TEXTURE_MAG_FILTER, config.magfilter);
    gl::textureParameteri(texture, GL_TEXTURE_WRAP_S, config.wrap_s);
    gl::textureParameteri(texture, GL_TEXTURE_WRAP_T, config.wrap_t);

    if (config.anisotropic)
    {
        float anisotropy;
        gl::getFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &anisotropy);
        gl::textureParameterf(texture, GL_TEXTURE_MAX_ANISOTROPY, anisotropy);
    }

    if (config.genmipmap)
    {
        gl::generateTextureMipmap(texture);
    }

    return texture;
}



GLuint
idk::gltools::allocateTextureCubeArray( uint32_t w, uint32_t h, uint32_t layers,
                                        const glTextureConfig &config )
{
    GLuint texture;
    gl::createTextures(GL_TEXTURE_CUBE_MAP_ARRAY, 1, &texture);

    GLsizei levels = 1 + floor(log2(idk::max(w, h)));
            levels = config.genmipmap ? levels : 1;

    gl::textureStorage3D(texture, levels, config.internalformat, w, h, 6*layers);

    for (uint32_t layer=0; layer<layers; layer++)
    {
        for (uint32_t face=0; face<6; face++)
        {
            gl::textureSubImage3D(
                texture,
                0,
                0, 0, 6*layer + face,
                w, h, 1,
                config.format,
                config.datatype,
                nullptr
            );
        }
    }

    gl::textureParameteri(texture, GL_TEXTURE_MIN_FILTER, config.minfilter);
    gl::textureParameteri(texture, GL_TEXTURE_MAG_FILTER, config.magfilter);
    gl::textureParameteri(texture, GL_TEXTURE_WRAP_S, config.wrap_s);
    gl::textureParameteri(texture, GL_TEXTURE_WRAP_T, config.wrap_t);
    gl::textureParameteri(texture, GL_TEXTURE_WRAP_R, config.wrap_r);

    if (config.anisotropic)
    {
        float anisotropy;
        gl::getFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &anisotropy);
        gl::textureParameterf(texture, GL_TEXTURE_MAX_ANISOTROPY, anisotropy);
    }

    if (config.genmipmap)
    {
        gl::generateTextureMipmap(texture);
    }

    return texture;
}



static glm::vec4
t_query( int u, int v, uint32_t w, uint32_t h, std::unique_ptr<uint8_t[]> &data )
{
    u %= w;
    v &= h;

    glm::vec4 result = glm::vec4(
        float(data[4*w*v + 4*u + 0]),
        float(data[4*w*v + 4*u + 1]),
        float(data[4*w*v + 4*u + 2]),
        float(data[4*w*v + 4*u + 3])
    );

    return result;
}



glm::vec4
idk::gltools::textureQuery( float u, float v, uint32_t w, uint32_t h,
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
idk::gltools::loadCubemap2( uint32_t w, void *data, const idk::glTextureConfig &config )
{
    GLuint texture_id;

    gl::genTextures(1, &texture_id);
    gl::bindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

    for (int i=0; i<6; i++)
    {
        gl::texImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
            0, config.internalformat, w, w, 0, config.format,
            config.datatype, data
        );
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




// GLuint
// idk::gltools::loadCubemap( std::string root, std::vector<std::string> filenames, glTextureConfig config )
// {
//     GLuint texture;

//     gl::createTextures(GL_TEXTURE_CUBE_MAP, 1, &texture);

//     {
//         std::string       tmp_filepath = root + filenames[0];
//         SDL_Surface      *tmp_tmp      = IMG_Load(tmp_filepath.c_str());
//         SDL_PixelFormat  *tmp_target   = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
//         SDL_Surface      *tmp_img      = SDL_ConvertSurface(tmp_tmp, tmp_target, 0);

//         gl::textureStorage2D(texture, config.texmaxlevel+1, GL_RGBA8, tmp_img->w, tmp_img->h);

//         SDL_FreeFormat(tmp_target);
//         SDL_FreeSurface(tmp_tmp);
//         SDL_FreeSurface(tmp_img);
//     }


//     for (int face=0; face<6; face++)
//     {
//         std::string       filepath = root + filenames[face];
//         SDL_Surface      *tmp      = IMG_Load(filepath.c_str());
//         SDL_PixelFormat  *target   = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
//         SDL_Surface      *img      = SDL_ConvertSurface(tmp, target, 0);

//         gl::textureSubImage3D(
//             texture, 0,
//             0, 0, face,
//             img->w, img->h, 1,
//             config.format, config.datatype,
//             img->pixels
//         );
    
//         SDL_FreeFormat(target);
//         SDL_FreeSurface(tmp);
//         SDL_FreeSurface(img);
//     }

//     gl::textureParameteri(texture, GL_TEXTURE_MIN_FILTER, config.minfilter);
//     gl::textureParameteri(texture, GL_TEXTURE_MAG_FILTER, config.magfilter);
//     gl::textureParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//     gl::textureParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//     gl::textureParameteri(texture, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

//     if (config.genmipmap)
//     {
//         gl::generateTextureMipmap(texture);
//     }

//     else if (config.setmipmap)
//     {
//         gl::textureParameteri(texture, GL_TEXTURE_BASE_LEVEL, config.texbaselevel);
//         gl::textureParameteri(texture, GL_TEXTURE_MAX_LEVEL,  config.texmaxlevel);
//     }

//     return texture;
// }


// void
// idk::gltools::loadCubemapMip( std::string directory, std::vector<std::string> filenames,
//                               glTextureConfig config, GLuint cubemap, GLint level )
// {
//     for (GLuint face=0; face<6; face++)
//     {
//         std::string       filepath = directory + std::to_string(level) + filenames[face];
//         SDL_Surface      *tmp      = IMG_Load(filepath.c_str());
//         SDL_PixelFormat  *target   = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
//         SDL_Surface      *img      = SDL_ConvertSurface(tmp, target, 0);

//         gl::textureSubImage3D(
//             cubemap, level,
//             0, 0, face,
//             img->w, img->h, 1,
//             config.format, config.datatype,
//             img->pixels
//         );

//         SDL_FreeFormat(target);
//         SDL_FreeSurface(tmp);
//         SDL_FreeSurface(img);
//     }

// }






GLuint
idk::gltools::loadTexture( const std::string &filepath, const glTextureConfig &config,
                           idk::TextureWrapper *wrapper )
{
    if (fs::exists(filepath) == false)
    {
        std::string msg = "File does not exist: \"" + filepath + "\"\n";
        IDK_ASSERT(msg.c_str(), false);
    }

    SDL_Surface      *tmp    = IMG_Load(filepath.c_str());
    SDL_PixelFormat  *target = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    SDL_Surface      *img    = SDL_ConvertSurface(tmp, target, 0);

    GLuint texture_id = gltools::loadTexture2D(img->w, img->h, (uint32_t *)(img->pixels), config);

    if (wrapper)
    {
        (*wrapper) = idk::TextureWrapper((uint32_t *)(img->pixels), img->w, img->h);
    }

    SDL_FreeFormat(target);
    SDL_FreeSurface(tmp);
    SDL_FreeSurface(img);

    return texture_id;
}




void *
idk::gltools::loadPixels( const std::string &filepath, uint32_t *w, uint32_t *h, bool alpha )
{
    if (fs::exists(filepath) == false)
    {
        LOG_ERROR(
            "idk::gltools::loadPixels",
            std::format("File does not exist: \"{}\"", filepath)
        );
    }

    SDL_Surface      *tmp = IMG_Load(filepath.c_str());
    SDL_PixelFormat  *target;

    if (alpha)
    {
        target = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    }

    else
    {
        target = SDL_AllocFormat(SDL_PIXELFORMAT_RGB24);
    }

    SDL_Surface *img = SDL_ConvertSurface(tmp, target, 0);

    if (w && h)
    {
        *w = img->w;
        *h = img->h;
    }

    size_t nbytes = img->w * img->h * (alpha ? 4 : 3);
    void  *pixels = std::malloc(nbytes);

    std::memcpy(pixels, img->pixels, nbytes);

    SDL_FreeFormat(target);
    SDL_FreeSurface(tmp);
    SDL_FreeSurface(img);

    return pixels;
}



idk::TextureRef
idk::gltools::loadTextureWrapper( const std::string &filepath, const glTextureConfig &config )
{
    if (fs::exists(filepath) == false)
    {
        LOG_ERROR(
            "idk::gltools::loadTextureWrapper",
            std::format("File does not exist: \"{}\"", filepath)
        );
    }

    SDL_Surface      *tmp    = IMG_Load(filepath.c_str());
    SDL_PixelFormat  *target = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    SDL_Surface      *img    = SDL_ConvertSurface(tmp, target, 0);

    GLuint texture_id = gltools::loadTexture2D(img->w, img->h, (uint32_t *)(img->pixels), config);
    idk::TextureRef texture(texture_id, img->w, img->h);

    SDL_FreeFormat(target);
    SDL_FreeSurface(tmp);
    SDL_FreeSurface(img);

    return texture;
}


// idk::glTexture
// idk::gltools::loadTexture2( uint32_t w, uint32_t h, void *data, const glTextureConfig &config )
// {
//     GLuint texture_id = gltools::loadTexture2D(w, h, (uint32_t *)(data), config);

//     idk::glTexture texture(
//         texture_id,
//         glm::ivec2(w, h),
//         config
//     );

//     return texture;
// }
