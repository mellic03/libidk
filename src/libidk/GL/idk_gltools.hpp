#pragma once

#include <string>

#include "idk_glFramebuffer.hpp"
#include "idk_glBindings.hpp"
#include <memory>

#include <cstddef>
#include <cstdint>


namespace idk::gltools
{
    GLuint  loadTexture2D( uint32_t w, uint32_t h, void *data, const glTextureConfig &config );
    GLuint  loadTexture3D( uint32_t w, uint32_t h, uint32_t d, void *data, const glTextureConfig &config );
    GLuint  allocateTextureCube( uint32_t w, uint32_t h, const glTextureConfig &config );
    GLuint  allocateTextureCubeArray( uint32_t w, uint32_t h, uint32_t d, const glTextureConfig &config );

    void *loadPixels( const std::string&, uint32_t *w, uint32_t *h );

    GLuint loadTexture( const std::string &, const glTextureConfig &config,
                        idk::TextureWrapper *wrapper = nullptr );

    // GLuint loadTexture( const std::string &, const glTextureConfig &config,
    //                     idk::TextureRef *wrapper = nullptr );

    idk::TextureRef loadTextureWrapper( const std::string&, const glTextureConfig &config );


    glm::vec4 textureQuery( float u, float v, uint32_t w, uint32_t h,
                            std::unique_ptr<uint8_t[]> &data );


    GLuint  loadCubemap( std::string              root,
                         std::vector<std::string> filenames,
                         glTextureConfig          config );

    void    loadCubemapMip( std::string              directory,
                            std::vector<std::string> filenames,
                            glTextureConfig          config,
                            GLuint                   cubemap,
                            GLint                    level );


    GLuint  loadCubemap2( uint32_t w, void *data, const idk::glTextureConfig & );

};

