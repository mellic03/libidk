#pragma once

#include "common.hpp"
#include "idk_glTexture.hpp"
#include <vector>

namespace idk
{

    struct DepthAttachmentConfig;
    class  glFramebuffer;
};


struct idk::DepthAttachmentConfig
{
    GLint  internalformat = GL_DEPTH_COMPONENT24;
    GLenum format         = GL_DEPTH_COMPONENT;
    GLenum datatype       = GL_FLOAT;
    GLenum compare_func   = GL_LESS;
};


class idk::glFramebuffer
{
private:
    bool m_first = true;
    bool m_bound = false;
    glm::ivec2 m_size;
    std::vector<GLenum> m_gl_attachments;

protected:
    void   _reset( int w, int h, size_t num_attachments );

public:
    GLuint              m_FBO;
    std::vector<GLuint> attachments;
    GLuint              cubemap_attachment;
    GLuint              depth_attachment;

    void    reset( int w, int h, size_t num_attachments );

    void    cubeColorAttachment( int idx, const idk::glTextureConfig &config );
    void    cubeDepthAttachment( const idk::DepthAttachmentConfig& );

    void    cubeArrayColorAttachment( int idx, uint32_t layers, const idk::glTextureConfig &config );
    void    cubeArrayDepthAttachment( uint32_t layers, const idk::DepthAttachmentConfig& );

    void    colorAttachment( int idx, const idk::glTextureConfig &config );

    void    depthAttachment( const idk::DepthAttachmentConfig &config );
    void    depthArrayAttachment( uint32_t layers, const idk::DepthAttachmentConfig &config );

    void    generateMipmap( int idx );
    void    generateMipmapCube();
    void    viewport(int x, int y, int w, int h);
    void    bind();
    void    unbind();
    bool    isBound() { return m_bound; };
    void    clear( GLbitfield mask );

    const glm::ivec2 &size() { return m_size; };

};

