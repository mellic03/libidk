#include "idk_glFramebuffer.hpp"
#include "idk_glBindings.hpp"


void
idk::glFramebuffer::reset( int w, int h, size_t num_attachments )
{
    m_size.x = w;  m_size.y = h;
    m_gl_attachments.resize(0);
    attachments.resize(num_attachments);

    if (m_first == false)
    {
        gl::deleteFramebuffers(1, &m_FBO);
        gl::deleteRenderbuffers(1, &m_RBO);
    }

    gl::genFramebuffers(1, &m_FBO);
    gl::genRenderbuffers(1, &m_RBO);

    if (num_attachments > 0)
    {
        gl::bindFramebuffer(GL_FRAMEBUFFER, m_RBO);
        gl::bindRenderbuffer(GL_RENDERBUFFER, m_FBO);

        GLCALL( glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, w, h); )
        GLCALL( glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBO); )

        gl::bindRenderbuffer(GL_RENDERBUFFER, 0);
        gl::bindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    m_first = false;
}


void
idk::glFramebuffer::cubemapColorAttachment( const idk::glColorConfig &config )
{
    gl::bindFramebuffer(GL_FRAMEBUFFER, m_FBO);

    gl::deleteTextures(1, &cubemap_attachment);
    gl::genTextures(1, &cubemap_attachment);
    gl::bindTexture(GL_TEXTURE_CUBE_MAP, cubemap_attachment);

    for (uint i=0; i<6; ++i)
    {
        gl::texImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA16F, m_size.x, m_size.y, 0, 
                        GL_RGBA, GL_FLOAT, nullptr );
    }

    gl::texParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, config.minfilter);
    gl::texParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, config.magfilter);
    gl::texParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl::texParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    gl::texParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // gl::bindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    // gl::bindRenderbuffer(GL_RENDERBUFFER, m_RBO);
    // GLCALL( glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_size.x, m_size.y); )
    // GLCALL( glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBO); )

    gl::bindFramebuffer(GL_FRAMEBUFFER, 0);
    // gl::bindRenderbuffer(GL_RENDERBUFFER, 0);
    gl::bindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


void
idk::glFramebuffer::colorAttachment( int idx, const idk::glColorConfig &config )
{
    gl::bindFramebuffer(GL_FRAMEBUFFER, m_FBO);

    gl::deleteTextures(1, &attachments[idx]);
    gl::genTextures(1, &attachments[idx]);
    gl::bindTexture(GL_TEXTURE_2D, attachments[idx]);

    // if (config.format != GL_RGBA_INTEGER)
    {
        gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, config.minfilter);
        gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, config.magfilter);
        gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     config.wrap_s);
        gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     config.wrap_t);
    }

    gl::texImage2D(
        GL_TEXTURE_2D, 0, config.internalformat,
        m_size.x, m_size.y, 0, config.format, config.datatype, NULL
    );


    if (config.genmipmap)
    {
        gl::generateMipmap(GL_TEXTURE_2D);
    }

    else if (config.setmipmap)
    {
        gl::texParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, config.texbaselevel);
        gl::texParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL,  config.texmaxlevel);
    }

    gl::framebufferTexture2D(
        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+idx, GL_TEXTURE_2D, attachments[idx], 0
    );

    m_gl_attachments.push_back(GL_COLOR_ATTACHMENT0 + idx);
    GLCALL( glDrawBuffers(m_gl_attachments.size(), &(m_gl_attachments[0])); )

    gl::bindFramebuffer(GL_FRAMEBUFFER, 0);
    gl::bindTexture(GL_TEXTURE_2D, 0);
}


void
idk::glFramebuffer::depthAttachment( const idk::DepthAttachmentConfig &config )
{
    gl::deleteTextures(1, &depth_attachment);
    gl::genTextures(1, &depth_attachment);
    gl::bindTexture(GL_TEXTURE_2D, depth_attachment);

    gl::texImage2D(
        GL_TEXTURE_2D, 0, config.internalformat,
        m_size.x, m_size.y, 0, config.format, config.datatype, NULL
    );

    gl::bindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    gl::framebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_attachment, 0);

    GLCALL( glDrawBuffer(GL_NONE); )
    GLCALL( glReadBuffer(GL_NONE); )

    gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    gl::bindFramebuffer(GL_FRAMEBUFFER, 0);
    gl::bindTexture(GL_TEXTURE_2D, 0);
}


void
idk::glFramebuffer::generateMipmap( int idx )
{
    gl::bindTexture(GL_TEXTURE_2D, attachments[idx]);
    gl::generateMipmap(GL_TEXTURE_2D);
    gl::bindTexture(GL_TEXTURE_2D, 0);
}


void
idk::glFramebuffer::generateMipmapCube()
{
    gl::bindTexture(GL_TEXTURE_CUBE_MAP, cubemap_attachment);
    gl::generateMipmap(GL_TEXTURE_CUBE_MAP);
    gl::bindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


void
idk::glFramebuffer::viewport( int x, int y, int w, int h )
{
    gl::viewport(x, y, w, h);
}


void
idk::glFramebuffer::bind()
{
    gl::bindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    gl::viewport(0, 0, m_size.x, m_size.y);
}


void
idk::glFramebuffer::unbind()
{
    gl::bindFramebuffer(GL_FRAMEBUFFER, 0);
}


void
idk::glFramebuffer::clear( GLbitfield mask )
{
    this->bind();
    gl::clearColor(0.0f, 0.0f, 0.0f, 0.0f);
    gl::clear(mask); 
}


