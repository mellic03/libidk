#include "idk_glFramebuffer.hpp"
#include "idk_glBindings.hpp"
#include "idk_gltools.hpp"


void
idk::glFramebuffer::f_reset( int w, int h, size_t num_attachments )
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

        IDK_GLCALL( glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, w, h); )
        IDK_GLCALL( glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBO); )

        gl::bindRenderbuffer(GL_RENDERBUFFER, 0);
        gl::bindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    m_first = false;
}



void
idk::glFramebuffer::reset( int w, int h, size_t num_attachments )
{
    f_reset(w, h, num_attachments);
}


void
idk::glFramebuffer::cubemapColorAttachment( const idk::glTextureConfig &config )
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
    // IDK_GLCALL( glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_size.x, m_size.y); )
    // IDK_GLCALL( glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBO); )

    gl::bindFramebuffer(GL_FRAMEBUFFER, 0);
    // gl::bindRenderbuffer(GL_RENDERBUFFER, 0);
    gl::bindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


void
idk::glFramebuffer::colorAttachment( int idx, const idk::glTextureConfig &config )
{
//     gl::deleteTextures(1, &attachments[idx]);

//     attachments[idx] = gltools::loadTexture2D(m_size.x, m_size.y, nullptr, config);
//     m_gl_attachments.push_back(GL_COLOR_ATTACHMENT0 + idx);

//     gl::namedFramebufferTexture(m_FBO, m_gl_attachments.back(), attachments[idx], 0);
//     gl::namedFramebufferDrawBuffers(m_FBO, m_gl_attachments.size(), m_gl_attachments.data());

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
    IDK_GLCALL( glDrawBuffers(m_gl_attachments.size(), &(m_gl_attachments[0])); )

    gl::bindFramebuffer(GL_FRAMEBUFFER, 0);
    gl::bindTexture(GL_TEXTURE_2D, 0);
}




void
idk::glFramebuffer::depthAttachment( const idk::DepthAttachmentConfig &ree )
// {
//     static constexpr idk::glTextureConfig config = {
//         .target         = GL_TEXTURE_2D,
//         .internalformat = GL_DEPTH_COMPONENT24,
//         .format         = GL_DEPTH_COMPONENT,
//         .minfilter      = GL_NEAREST,
//         .magfilter      = GL_LINEAR,
//         .wrap_s         = GL_CLAMP_TO_BORDER,
//         .wrap_t         = GL_CLAMP_TO_BORDER,
//         .comp_fn        = 0,
//         .comp_mode      = 0,
//         .genmipmap      = GL_FALSE
//     };

//     gl::deleteTextures(1, &depth_attachment);
//     depth_attachment = gltools::loadTexture2D(m_size.x, m_size.y, nullptr, config);
//     gl::namedFramebufferTexture(m_FBO, GL_DEPTH_ATTACHMENT, depth_attachment, 0);

// }
{
    gl::deleteTextures(1, &depth_attachment);
    gl::genTextures(1, &depth_attachment);
    gl::bindTexture(GL_TEXTURE_2D, depth_attachment);

    gl::texImage2D(
        GL_TEXTURE_2D,
        0,
        ree.internalformat,
        m_size.x, m_size.y,
        0,
        GL_DEPTH_COMPONENT,
        ree.datatype,
        nullptr
    );

    gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);

    gl::bindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    gl::framebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_attachment, 0);

    // IDK_GLCALL( glDrawBuffer(GL_NONE); )
    // IDK_GLCALL( glReadBuffer(GL_NONE); )

    gl::bindFramebuffer(GL_FRAMEBUFFER, 0);
}



void
idk::glFramebuffer::depthArrayAttachment( GLsizei depth, const idk::DepthAttachmentConfig &ree )
// {
//     static constexpr idk::glTextureConfig config = {
//         .target         = GL_TEXTURE_2D_ARRAY,
//         .internalformat = GL_DEPTH_COMPONENT24,
//         .format         = GL_DEPTH_COMPONENT,
//         .minfilter      = GL_NEAREST,
//         .magfilter      = GL_LINEAR,
//         .wrap_s         = GL_CLAMP_TO_BORDER,
//         .wrap_t         = GL_CLAMP_TO_BORDER,
//         .comp_fn        = GL_LEQUAL,
//         .comp_mode      = GL_COMPARE_REF_TO_TEXTURE,
//         .genmipmap      = GL_FALSE
//     };

//     gl::deleteTextures(1, &depth_attachment);
//     depth_attachment = gltools::loadTexture3D(m_size.x, m_size.y, depth, nullptr, config);
//     gl::namedFramebufferTexture(m_FBO, GL_DEPTH_ATTACHMENT, depth_attachment, 0);
// }
{
    gl::deleteTextures(1, &depth_attachment);
    gl::genTextures(1, &depth_attachment);
    gl::bindTexture(GL_TEXTURE_2D_ARRAY, depth_attachment);

    gl::texImage3D(
        GL_TEXTURE_2D_ARRAY,
        0,
        ree.internalformat,
        m_size.x, m_size.y,
        depth,
        0,
        GL_DEPTH_COMPONENT,
        ree.datatype,
        nullptr
    );

    gl::texParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl::texParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gl::texParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    gl::texParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    gl::texParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    gl::texParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);

    gl::bindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    gl::framebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_attachment, 0);

    IDK_GLCALL( glDrawBuffer(GL_NONE); )
    IDK_GLCALL( glReadBuffer(GL_NONE); )

    gl::bindFramebuffer(GL_FRAMEBUFFER, 0);
}



void
idk::glFramebuffer::generateMipmap( int idx )
{
    gl::generateTextureMipmap(attachments[idx]);
}


void
idk::glFramebuffer::generateMipmapCube()
{
    gl::generateTextureMipmap(cubemap_attachment);
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
    m_bound = true;
}


void
idk::glFramebuffer::unbind()
{
    gl::bindFramebuffer(GL_FRAMEBUFFER, 0);
    m_bound = false;
}


void
idk::glFramebuffer::clear( GLbitfield mask )
{
    this->bind();
    gl::clearColor(0.0f, 0.0f, 0.0f, 0.0f);
    gl::clear(mask); 
}

