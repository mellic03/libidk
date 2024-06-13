#pragma once

#include "idk_glBindings.hpp"
#include <memory>


namespace idk
{
    struct glTextureConfig;
    struct TextureRef;
}


struct idk::glTextureConfig
{
    GLenum target         = GL_TEXTURE_2D;
    GLint  internalformat = GL_RGBA16F;
    GLenum format         = GL_RGBA;
    GLenum minfilter      = GL_NEAREST;
    GLenum magfilter      = GL_LINEAR;
    GLenum wrap_s         = GL_CLAMP_TO_EDGE;
    GLenum wrap_t         = GL_CLAMP_TO_EDGE;
    GLenum wrap_r         = GL_CLAMP_TO_EDGE;
    GLint  comp_fn        = GL_LEQUAL;
    GLint  comp_mode      = GL_COMPARE_REF_TO_TEXTURE;
    GLenum datatype       = GL_FLOAT;
    bool   anisotropic    = GL_FALSE;
    bool   genmipmap      = GL_TRUE;
    bool   setmipmap      = GL_FALSE;
    GLint  texbaselevel   = 0;
    GLint  texmaxlevel    = 4;
    bool   bindless       = GL_FALSE;
};


struct idk::TextureRef
{
private:
    std::shared_ptr<uint32_t> m_texture;

public:
    size_t   width;
    size_t   height;

    TextureRef();
    TextureRef( uint32_t texture, size_t w, size_t h );

    uint32_t ID();
};

