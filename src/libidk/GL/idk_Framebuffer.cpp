#include "idk_Framebuffer.hpp"
#include "idk_glBindings.hpp"
#include "idk_gltools.hpp"

#include "../idk_assert.hpp"



uint32_t
idk::FramebufferAttachment::reset( Framebuffer &fb )
{
    auto size = fb.size();

    gl::deleteTextures(1, &texture);
    texture = gltools::loadTexture2D(size.x, size.y, nullptr, config);

    gl::clearTexImage(texture, 0, config.format, config.datatype, nullptr);

    return texture;
}





void
idk::Framebuffer::init( int w, int h, size_t num_attachments )
{
    m_size = glm::ivec2(w, h);

    m_gl_attachments.resize(num_attachments);
    m_textures.resize(num_attachments);
    m_attachments.resize(num_attachments, nullptr);

    gl::createFramebuffers(1, &m_FBO);
}


void
idk::Framebuffer::resize( int w, int h )
{
    gl::deleteTextures(m_textures.size(), &m_textures[0]);
    gl::deleteFramebuffers(1, &m_FBO);

    init(w, h, m_textures.size());

    for (int idx=0; idx<m_attachments.size(); idx++)
    {
        auto *A = m_attachments[idx];

        if (A != nullptr)
        {
            addAttachment(idx, A);
        }
    }
}


void
idk::Framebuffer::addAttachment( int idx, idk::FramebufferAttachment *A )
{
    m_attachments[idx] = A;
    m_textures[idx] = A->reset(*this);
    m_gl_attachments[idx]  = GL_COLOR_ATTACHMENT0 + idx;

    gl::namedFramebufferTexture(m_FBO, m_gl_attachments.back(), m_textures[idx], 0);
    gl::namedFramebufferDrawBuffers(m_FBO, m_gl_attachments.size(), m_gl_attachments.data());

    uint32_t status;
    IDK_GLCALL( status = glCheckNamedFramebufferStatus(m_FBO, GL_FRAMEBUFFER); )
    IDK_ASSERT("Incomplete framebuffer", status == GL_FRAMEBUFFER_COMPLETE);
}


void
idk::Framebuffer::bind()
{
    gl::bindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    gl::viewport(0, 0, m_size.x, m_size.y);
}

void
idk::Framebuffer::bindClear( GLbitfield mask )
{
    bind();
    clear(mask);
}

void
idk::Framebuffer::clear( GLbitfield mask )
{
    gl::clearColor(0.0f, 0.0f, 0.0f, 0.0f);
    gl::clear(mask); 
}

