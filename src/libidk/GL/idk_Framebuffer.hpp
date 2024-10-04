#pragma once

#include "common.hpp"
#include "idk_glTexture.hpp"
#include <vector>

namespace idk
{
    struct FramebufferAttachment;
    class  Framebuffer;
};




class idk::Framebuffer
{
private:
    glm::ivec2 m_size;
    std::vector<GLenum> m_gl_attachments;

protected:


public:
    GLuint                              m_FBO;
    std::vector<GLuint>                 m_textures;
    std::vector<FramebufferAttachment*> m_attachments;

    void    init( int w, int h, size_t num_attachments );
    void    resize( int w, int h );
    void    addAttachment( int idx, idk::FramebufferAttachment* );

    void    bind();
    void    bindClear( GLbitfield mask );
    void    clear( GLbitfield mask );

    uint32_t getFBO() const { return m_FBO; }
    const glm::ivec2 &size() const { return m_size; };

};




class idk::FramebufferAttachment
{
protected:
    glTextureConfig config;
    uint32_t texture;

public:

    FramebufferAttachment( const idk::glTextureConfig &conf )
    :   config(conf)
    {

    }

    virtual uint32_t reset( Framebuffer &fb );

};



