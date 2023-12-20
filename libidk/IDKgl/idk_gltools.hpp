#pragma once

#include <string>

#include "idk_glFramebuffer.hpp"
#include "idk_glBindings.hpp"


namespace idk::gltools
{
    GLuint  loadTexture( size_t w, size_t h, void *data, const glTextureConfig &config );
    GLuint  loadTexture( std::string filepath, const glTextureConfig &config );



    // GLuint  loadTexture( size_t w, size_t h, void *data, bool srgb, GLint minfilter, GLint magfilter );
    // GLuint  loadTexture( std::string filepath, bool srgb, GLint minfilter, GLint magfilter );


    GLuint  loadCubemap( std::string              root,
                         std::vector<std::string> filenames,
                         glTextureConfig            config );

    void    loadCubemapMip( std::string              directory,
                            std::vector<std::string> filenames,
                            glTextureConfig            config,
                            GLuint                   cubemap,
                            GLint                    level );

};

