#pragma once

#include "idk_glBindings.hpp"
#include <memory>


namespace idk { struct glTextureConfig; class glTexture; };


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
    GLenum datatype       = GL_FLOAT;
    bool   anisotropic    = GL_FALSE;
    bool   genmipmap      = GL_TRUE;
    bool   setmipmap      = GL_FALSE;
    GLint  texbaselevel   = 0;
    GLint  texmaxlevel    = 4;
    bool   bindless       = GL_FALSE;
};


class idk::glTexture
{
private:
    GLuint                      m_id;
    GLuint64                    m_handle;
    glm::ivec2                  m_size;
    size_t                      m_nbytes;
    glTextureConfig             m_config;

    std::vector<std::unique_ptr<uint8_t[]>> m_mips;

    float     *_data1f( int l ) const { return reinterpret_cast<float *>     (m_mips[l].get()); };
    glm::vec4 *_data4f( int l ) const { return reinterpret_cast<glm::vec4 *> (m_mips[l].get()); };
    uint8_t   *_data1u( int l ) const { return reinterpret_cast<uint8_t *>   (m_mips[l].get()); };


public:
            // glTexture( const idk::glTexture &  );
            // glTexture( const idk::glTexture && );
            glTexture( GLuint, const glm::ivec2 &, const glTextureConfig & );

    // glTexture &operator = ( const glTexture &  );
    // glTexture &operator = ( const glTexture && );

    GLuint   ID()     const { return m_id;     };
    GLuint64 handle() const { return m_handle; };

    // const float     &sample1f ( float u, float v, int l=0 ) const;
    // const uint8_t   &sample1u ( float u, float v, int l=0 ) const;
    // const uint8_t   *sample4u ( float u, float v, int l=0 ) const;

    // glm::vec4  isample4f  ( int   x, int   y, int l=0 ) const;
    // glm::vec4  sample4f   ( float u, float v, int l=0 ) const;
    // glm::vec4  bisample4f ( float u, float v, int l=0 ) const;

    // glm::ivec2 size( int level=0 ) const { return m_size / int(glm::pow(2, level)); };

    // const glTextureConfig &config()  const { return m_config; };
};


