#pragma once

#include <string>

#include "idk_glFramebuffer.hpp"
#include "idk_glBindings.hpp"
#include <memory>


namespace idk::gltools
{
    GLuint  loadTexture2D( size_t w, size_t h, void *data, const glTextureConfig &config );

    GLuint  loadTexture3D( size_t w, size_t h, size_t d, void *data, const glTextureConfig &config );

    GLuint loadTexture( const std::string &, const glTextureConfig &config,
                        idk::TextureWrapper *wrapper = nullptr );

    // GLuint loadTexture( const std::string &, const glTextureConfig &config,
    //                     idk::TextureRef *wrapper = nullptr );

    idk::TextureRef loadTextureWrapper( const std::string&, const glTextureConfig &config );


    glm::vec4 textureQuery( float u, float v, size_t w, size_t h,
                            std::unique_ptr<uint8_t[]> &data );


    GLuint  loadCubemap( std::string              root,
                         std::vector<std::string> filenames,
                         glTextureConfig          config );

    void    loadCubemapMip( std::string              directory,
                            std::vector<std::string> filenames,
                            glTextureConfig          config,
                            GLuint                   cubemap,
                            GLint                    level );


    GLuint  loadCubemap2( size_t w, void *data, const idk::glTextureConfig & );

};

