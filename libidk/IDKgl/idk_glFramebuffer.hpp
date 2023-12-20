#pragma once

#include "common.hpp"
#include <vector>

namespace idk
{
    struct glTextureConfig;
    struct DepthAttachmentConfig;
    class  glFramebuffer;
};



struct idk::glTextureConfig
{
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
    GLint  texmaxlevel    = 0;
};


struct idk::DepthAttachmentConfig
{
    GLint  internalformat = GL_DEPTH_COMPONENT;
    GLenum format         = GL_DEPTH_COMPONENT;
    GLenum datatype       = GL_FLOAT;
};


class idk::glFramebuffer
{
private:
    bool m_first = true;
    bool m_bound = false;
    glm::ivec2 m_size;
    std::vector<GLuint> m_gl_attachments;

protected:
    void    f_reset( int w, int h, size_t num_attachments );

public:
    GLuint              m_FBO;
    GLuint              m_RBO;
    std::vector<GLuint> attachments;
    GLuint              cubemap_attachment;
    GLuint              depth_attachment;

    void    reset( int w, int h, size_t num_attachments );
    void    cubemapColorAttachment( const idk::glTextureConfig &config );
    void    colorAttachment( int idx, const idk::glTextureConfig &config );
    void    depthAttachment( int idx, const idk::DepthAttachmentConfig &config );
    void    depthArrayAttachment( GLsizei depth, const idk::DepthAttachmentConfig &config );
    void    generateMipmap( int idx );
    void    generateMipmapCube();
    void    viewport(int x, int y, int w, int h);
    void    bind();
    void    unbind();
    bool    isBound() { return m_bound; };
    void    clear( GLbitfield mask );

    const glm::ivec2 &size() { return m_size; };

};

