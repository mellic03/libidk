#include "idk_gltools.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <libidk/IDKcore/libidk.hpp>

// void
// idk::glFramebuffer::depthArrayAttachment( GLsizei depth, const idk::DepthAttachmentConfig &config )
// {
//     gl::deleteTextures(1, &depth_attachment);
//     gl::genTextures(1, &depth_attachment);
//     gl::bindTexture(GL_TEXTURE_2D_ARRAY, depth_attachment);

//     gl::texImage3D(
//         GL_TEXTURE_2D_ARRAY,
//         0,
//         config.internalformat,
//         m_size.x, m_size.y,
//         depth,
//         0,
//         GL_DEPTH_COMPONENT,
//         config.datatype,
//         nullptr
//     );

//     gl::texParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     gl::texParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     gl::texParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//     gl::texParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

//     gl::texParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
//     gl::texParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);

//     gl::bindFramebuffer(GL_FRAMEBUFFER, m_FBO);
//     gl::framebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_attachment, 0);

//     IDK_GLCALL( glDrawBuffer(GL_NONE); )
//     IDK_GLCALL( glReadBuffer(GL_NONE); )

//     gl::bindFramebuffer(GL_FRAMEBUFFER, 0);
// }



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

    gl::createTextures(GL_TEXTURE_2D, 1, &texture_id);


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



GLuint
idk::gltools::loadTexture( std::string filepath, const glTextureConfig &config )
{
    SDL_Surface      *tmp    = IMG_Load(filepath.c_str());
    SDL_PixelFormat  *target = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    SDL_Surface      *img    = SDL_ConvertSurface(tmp, target, 0);

    GLuint texture_id = gltools::loadTexture(img->w, img->h, (uint32_t *)(img->pixels), config);

    SDL_FreeFormat(target);
    SDL_FreeSurface(tmp);
    SDL_FreeSurface(img);

    return texture_id;
}




// GLuint
// idk::gltools::loadTexture( size_t w, size_t h, void *data, bool srgb, GLint minfilter, GLint magfilter )
// {
//     GLuint texture_id;

//     gl::createTextures(GL_TEXTURE_2D, 1, &texture_id);

//     gl::textureParameteri(texture_id, GL_TEXTURE_MIN_FILTER, minfilter);
//     gl::textureParameteri(texture_id, GL_TEXTURE_MIN_FILTER, magfilter);
//     gl::textureParameteri(texture_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
//     gl::textureParameteri(texture_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

//     GLint internalformat = (srgb) ? GL_SRGB8_ALPHA8 : GL_RGBA16;

//     gl::textureStorage2D(texture_id, 1, internalformat, w, h);
//     gl::textureSubImage2D(texture_id, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);

//     IDK_GLCALL( glGenerateTextureMipmap(texture_id); )

    
//     float value;
//     float max_anisotropy = 8.0f;

//     IDK_GLCALL( glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &value); )
//     // value = (value > max_anisotropy) ? max_anisotropy : value;
//     // std::cout << "Max Anisotropy: " << value << "\n";
//     IDK_GLCALL( glTextureParameterf(texture_id, GL_TEXTURE_MAX_ANISOTROPY_EXT, value); )


//     return texture_id;
// }



// GLuint
// idk::gltools::loadTexture( std::string filepath, bool srgb, GLint minfilter, GLint magfilter )
// {
//     SDL_Surface      *tmp    = IMG_Load(filepath.c_str());
//     SDL_PixelFormat  *target = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
//     SDL_Surface      *img    = SDL_ConvertSurface(tmp, target, 0);

//     GLuint texture_id = gltools::loadTexture(img->w, img->h, (uint32_t *)(img->pixels), srgb, minfilter, magfilter);

//     SDL_FreeFormat(target);
//     SDL_FreeSurface(tmp);
//     SDL_FreeSurface(img);

//     return texture_id;
// }



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


