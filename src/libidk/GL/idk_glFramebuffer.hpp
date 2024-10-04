#pragma once

#include "common.hpp"
#include "idk_glTexture.hpp"
#include <vector>

namespace idk
{
    // struct DepthAttachmentConfig;
    // struct FramebufferAttachment;
    // struct FramebufferArrayAttachment;
    // struct FramebufferCubeAttachment;
    // struct FramebufferCubeArrayAttachment;

    class  glFramebuffer;
};




class idk::glFramebuffer
{
private:
    bool m_first = true;
    bool m_bound = false;
    glm::ivec2 m_size;
    std::vector<GLenum> m_gl_attachments;
    // std::vector<FramebufferAttachment*> m_ptr_attachments;

protected:
    void   _reset( int w, int h, size_t num_attachments );
    // void   init_attachment( int idx, uint32_t texture );

public:
    GLuint                       m_FBO;
    std::vector<GLuint>          attachments;
    std::vector<glTextureConfig> configs;
    std::vector<GLuint64>        handles;
    std::vector<GLuint>          depth_attachments;
    GLuint                       cubemap_attachment;
    GLuint                       depth_attachment;

    void    reset( int w, int h, size_t num_attachments );
    // void    resize( int w, int h );

    // void    addAttachment( int idx, idk::FramebufferAttachment* );

    void    cubeColorAttachment( int idx, const idk::glTextureConfig& );
    void    cubeDepthAttachment( const idk::glTextureConfig& );

    void    cubeArrayColorAttachment( int idx, uint32_t layers, const idk::glTextureConfig& );
    void    cubeArrayDepthAttachment( uint32_t layers, const idk::glTextureConfig& );

    void    colorAttachment( int idx, const idk::glTextureConfig& );

    void    depthAttachment( int idx, const idk::glTextureConfig& );
    void    depthArrayAttachment( uint32_t layers, const idk::glTextureConfig& );

    void    generateMipmap( int idx );
    void    generateMipmapCube();
    void    viewport(int x, int y, int w, int h);

    uint32_t getFBO() const { return m_FBO; }
    void     bind();
    void     unbind();
    bool     isBound() { return m_bound; };
    void     clear( GLbitfield mask );

    const glm::ivec2 &size() { return m_size; };

};






// class idk::FramebufferAttachment
// {
// protected:
//     glTextureConfig config;
//     uint32_t texture;

// public:

//     FramebufferAttachment( const idk::glTextureConfig &conf )
//     :   config(conf)
//     {

//     }

//     virtual uint32_t reset( glFramebuffer &fb );

// };



