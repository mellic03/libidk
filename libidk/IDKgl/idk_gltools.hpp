#pragma once

#include <string>

#include "idk_glFramebuffer.hpp"
#include "idk_glBindings.hpp"
#include <memory>


namespace idk::gltools
{
    GLuint  loadTexture( size_t w, size_t h, void *data, const glTextureConfig &config );
    // GLuint  loadTexture( std::string filepath, const glTextureConfig &config );

    idk::glTexture loadTexture( const std::string &, const glTextureConfig &config );


    GLuint loadTextureArray( size_t w, size_t h, size_t d, void **data, const glTextureConfig &config );

    glm::vec4 textureQuery( float u, float v, size_t w, size_t h,
                            std::unique_ptr<uint8_t[]> &data );

    // GLuint  loadTexture( size_t w, size_t h, void *data, bool srgb, GLint minfilter, GLint magfilter );
    // GLuint  loadTexture( std::string filepath, bool srgb, GLint minfilter, GLint magfilter );


    GLuint  loadCubemap( std::string              root,
                         std::vector<std::string> filenames,
                         glTextureConfig          config );

    void    loadCubemapMip( std::string              directory,
                            std::vector<std::string> filenames,
                            glTextureConfig          config,
                            GLuint                   cubemap,
                            GLint                    level );


};

