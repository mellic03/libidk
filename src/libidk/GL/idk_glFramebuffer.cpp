#include "idk_glFramebuffer.hpp"
#include "idk_glBindings.hpp"
#include "idk_gltools.hpp"

#include "../idk_assert.hpp"


void
idk::glFramebuffer::_reset( int w, int h, size_t num_attachments )
{
    m_size = glm::ivec2(w, h);

    gl::deleteTextures(attachments.size(), &attachments[0]);

    m_gl_attachments.resize(0);
    attachments.resize(num_attachments);

    if (m_first == false)
    {
        gl::deleteFramebuffers(1, &m_FBO);
    }

    gl::createFramebuffers(1, &m_FBO);

    m_first = false;
}


void
idk::glFramebuffer::reset( int w, int h, size_t num_attachments )
{
    _reset(w, h, num_attachments);
}


void
idk::glFramebuffer::cubeColorAttachment( int idx, const idk::glTextureConfig &config )
{
    gl::deleteTextures(1, &attachments[idx]);

    attachments[idx] = gltools::allocateTextureCube(m_size.x, m_size.y, config);
    m_gl_attachments.push_back(GL_COLOR_ATTACHMENT0 + idx);

    gl::namedFramebufferTexture(m_FBO, m_gl_attachments.back(), attachments[idx], 0);
    gl::namedFramebufferDrawBuffers(m_FBO, m_gl_attachments.size(), m_gl_attachments.data());

    gl::clearTexImage(attachments[idx], 0, config.format, config.datatype, nullptr);

    uint32_t status;
    IDK_GLCALL( status = glCheckNamedFramebufferStatus(m_FBO, GL_FRAMEBUFFER); )
    IDK_ASSERT("Incomplete framebuffer", status == GL_FRAMEBUFFER_COMPLETE);
}


void
idk::glFramebuffer::cubeArrayColorAttachment( int idx, uint32_t layers, const idk::glTextureConfig &config )
{
    gl::deleteTextures(1, &attachments[idx]);

    attachments[idx] = gltools::allocateTextureCubeArray(m_size.x, m_size.y, layers, config);
    m_gl_attachments.push_back(GL_COLOR_ATTACHMENT0 + idx);

    gl::namedFramebufferTexture(m_FBO, m_gl_attachments.back(), attachments[idx], 0);
    gl::namedFramebufferDrawBuffers(m_FBO, m_gl_attachments.size(), m_gl_attachments.data());

    gl::clearTexImage(attachments[idx], 0, config.format, config.datatype, nullptr);

    uint32_t status;
    IDK_GLCALL( status = glCheckNamedFramebufferStatus(m_FBO, GL_FRAMEBUFFER); )
    IDK_ASSERT("Incomplete framebuffer", status == GL_FRAMEBUFFER_COMPLETE);
}





void
idk::glFramebuffer::colorAttachment( int idx, const idk::glTextureConfig &config )
{
    gl::deleteTextures(1, &attachments[idx]);

    attachments[idx] = gltools::loadTexture2D(m_size.x, m_size.y, nullptr, config);
    m_gl_attachments.push_back(GL_COLOR_ATTACHMENT0 + idx);

    gl::namedFramebufferTexture(m_FBO, m_gl_attachments.back(), attachments[idx], 0);
    gl::namedFramebufferDrawBuffers(m_FBO, m_gl_attachments.size(), m_gl_attachments.data());

    uint32_t status;
    IDK_GLCALL( status = glCheckNamedFramebufferStatus(m_FBO, GL_FRAMEBUFFER); )
    IDK_ASSERT("Incomplete framebuffer", status == GL_FRAMEBUFFER_COMPLETE);
}



void
idk::glFramebuffer::depthAttachment( int idx, const idk::DepthAttachmentConfig &config )
{
    gl::deleteTextures(1, &attachments[idx]);
    gl::createTextures(GL_TEXTURE_2D, 1, &attachments[idx]);

    gl::textureStorage2D(
        attachments[idx],
        1,
        config.internalformat,
        m_size.x, m_size.y
    );

    gl::textureParameteri(attachments[idx], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl::textureParameteri(attachments[idx], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gl::textureParameterf(attachments[idx], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    gl::textureParameterf(attachments[idx], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // gl::textureParameteri(depth_attachment, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    // gl::textureParameteri(depth_attachment, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);

    gl::namedFramebufferTexture(m_FBO, GL_DEPTH_ATTACHMENT, attachments[idx], 0);
}



void
idk::glFramebuffer::cubeArrayDepthAttachment( uint32_t layers, const idk::DepthAttachmentConfig &config )
{
    gl::deleteTextures(1, &depth_attachment);
    gl::createTextures(GL_TEXTURE_CUBE_MAP_ARRAY, 1, &depth_attachment);

    gl::textureStorage3D(
        depth_attachment,
        1,
        config.internalformat,
        m_size.x, m_size.y,
        6*layers
    );

    for (uint32_t layer=0; layer<layers; ++layer)
    {
        for (uint32_t face=0; face<6; ++face)
        {
            gl::textureSubImage3D(
                depth_attachment,
                0,
                0, 0, 6*layer + face,
                m_size.x, m_size.y, 1,
                config.format,
                config.datatype,
                nullptr
            );
        }
    }

    gl::textureParameteri(depth_attachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl::textureParameteri(depth_attachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gl::textureParameterf(depth_attachment, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    gl::textureParameterf(depth_attachment, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    gl::textureParameterf(depth_attachment, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

    gl::textureParameteri(depth_attachment, GL_TEXTURE_COMPARE_FUNC, config.compare_func);

    gl::namedFramebufferTexture(m_FBO, GL_DEPTH_ATTACHMENT, depth_attachment, 0);

    uint32_t status;
    IDK_GLCALL( status = glCheckNamedFramebufferStatus(m_FBO, GL_FRAMEBUFFER); )
    IDK_ASSERT("Incomplete framebuffer", status == GL_FRAMEBUFFER_COMPLETE);
}



void
idk::glFramebuffer::cubeDepthAttachment( const idk::DepthAttachmentConfig &config )
{
    gl::deleteTextures(1, &depth_attachment);
    gl::createTextures(GL_TEXTURE_CUBE_MAP, 1, &depth_attachment);

    gl::textureStorage2D(
        depth_attachment,
        1,
        GL_DEPTH_COMPONENT24,
        m_size.x, m_size.y
    );

    for (uint32_t face=0; face<6; face++)
    {
        gl::textureSubImage3D(
            depth_attachment, 0,
            0, 0, face,
            m_size.x, m_size.y, 1,
            GL_DEPTH_COMPONENT,
            GL_FLOAT,
            nullptr
        );
    }

    gl::textureParameteri(depth_attachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl::textureParameteri(depth_attachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gl::textureParameterf(depth_attachment, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    gl::textureParameterf(depth_attachment, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    gl::textureParameterf(depth_attachment, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

    gl::namedFramebufferTexture(m_FBO, GL_DEPTH_ATTACHMENT, depth_attachment, 0);

    uint32_t status;
    IDK_GLCALL( status = glCheckNamedFramebufferStatus(m_FBO, GL_FRAMEBUFFER); )
    IDK_ASSERT("Incomplete framebuffer", status == GL_FRAMEBUFFER_COMPLETE);
}





void
idk::glFramebuffer::depthArrayAttachment( uint32_t layers, const idk::DepthAttachmentConfig &config )
{
    gl::deleteTextures(1, &depth_attachment);
    gl::createTextures(GL_TEXTURE_2D_ARRAY, 1, &depth_attachment);

    gl::textureStorage3D(
        depth_attachment,
        1,
        config.internalformat,
        m_size.x, m_size.y, layers
    );

    for (uint32_t layer=0; layer<layers; layer++)
    {
        gl::textureSubImage3D(
            depth_attachment,
            0,
            0, 0, layer,
            m_size.x, m_size.y, 1,
            GL_DEPTH_COMPONENT,
            config.datatype,
            nullptr
        );
    }


    gl::textureParameteri(depth_attachment, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl::textureParameteri(depth_attachment, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl::textureParameterf(depth_attachment, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    gl::textureParameterf(depth_attachment, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // gl::textureParameteri(depth_attachment, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    // gl::textureParameteri(depth_attachment, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);

    gl::namedFramebufferTexture(m_FBO, GL_DEPTH_ATTACHMENT, depth_attachment, 0);

    uint32_t status;
    IDK_GLCALL( status = glCheckNamedFramebufferStatus(m_FBO, GL_FRAMEBUFFER); )
    IDK_ASSERT("Incomplete framebuffer", status == GL_FRAMEBUFFER_COMPLETE);
}


void
idk::glFramebuffer::generateMipmap( int idx )
{
    gl::generateTextureMipmap(attachments[idx]);
}


void
idk::glFramebuffer::generateMipmapCube()
{
    gl::generateTextureMipmap(attachments[0]);
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

