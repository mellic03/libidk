#include "idk_glFramebuffer.hpp"
#include "idk_glBindings.hpp"
#include "idk_gltools.hpp"

#include "../idk_assert.hpp"



// uint32_t
// idk::FramebufferAttachment::reset( glFramebuffer &fb )
// {
//     auto size = fb.size();

//     gl::deleteTextures(1, &texture);
//     texture = gltools::loadTexture2D(size.x, size.y, nullptr, config);

//     gl::clearTexImage(texture, 0, config.format, config.datatype, nullptr);

//     return texture;
// }




void
idk::glFramebuffer::_reset( int w, int h, size_t num_attachments )
{
    IDK_ASSERT(
        "Cannot allocate zero textures to a framebuffer!",
        num_attachments > 0
    );

    m_size = glm::ivec2(w, h);

    m_gl_attachments.resize(0);
    attachments.resize(num_attachments);
    configs.resize(num_attachments);
    // m_ptr_attachments.resize(num_attachments, nullptr);

    gl::deleteTextures(attachments.size(), &attachments[0]);

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


// void
// idk::glFramebuffer::resize( int w, int h )
// {
//     for (int idx=0; idx<m_ptr_attachments.size(); idx++)
//     {
//         auto *A = m_ptr_attachments[idx];

//         if (A != nullptr)
//         {
//             init_attachment(idx, A->reset(*this));
//         }
//     }
// }


// void
// idk::glFramebuffer::addAttachment( int idx, idk::FramebufferAttachment *A )
// {
//     uint32_t texture = A->reset(*this);
//     m_ptr_attachments[idx] = A;
//     init_attachment(idx, texture);
// }



// void
// idk::glFramebuffer::init_attachment( int idx, uint32_t texture )
// {
//     this->attachments[idx] = texture;
//     m_gl_attachments[idx]  = GL_COLOR_ATTACHMENT0 + idx;

//     gl::namedFramebufferTexture(m_FBO, m_gl_attachments.back(), attachments[idx], 0);
//     gl::namedFramebufferDrawBuffers(m_FBO, m_gl_attachments.size(), m_gl_attachments.data());

//     uint32_t status;
//     IDK_GLCALL( status = glCheckNamedFramebufferStatus(m_FBO, GL_FRAMEBUFFER); )
//     IDK_ASSERT("Incomplete framebuffer", status == GL_FRAMEBUFFER_COMPLETE);
    
// }





void
idk::glFramebuffer::cubeColorAttachment( int idx, const idk::glTextureConfig &config )
{
    gl::deleteTextures(1, &attachments[idx]);

    attachments[idx] = gltools::allocateTextureCube(m_size.x, m_size.y, config);
    configs[idx]     = config;
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
    configs[idx]     = config;
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
    configs[idx]     = config;
    m_gl_attachments.push_back(GL_COLOR_ATTACHMENT0 + idx);

    gl::namedFramebufferTexture(m_FBO, m_gl_attachments.back(), attachments[idx], 0);
    gl::namedFramebufferDrawBuffers(m_FBO, m_gl_attachments.size(), m_gl_attachments.data());

    uint32_t status;
    IDK_GLCALL( status = glCheckNamedFramebufferStatus(m_FBO, GL_FRAMEBUFFER); )
    IDK_ASSERT("Incomplete framebuffer", status == GL_FRAMEBUFFER_COMPLETE);
}



void
idk::glFramebuffer::depthAttachment( int idx, const idk::glTextureConfig &config )
{
    gl::deleteTextures(1, &attachments[idx]);
    gl::createTextures(GL_TEXTURE_2D, 1, &attachments[idx]);
    configs[idx] = config;

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
idk::glFramebuffer::cubeArrayDepthAttachment( uint32_t layers, const idk::glTextureConfig &config )
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

    gl::textureParameteri(depth_attachment, GL_TEXTURE_COMPARE_FUNC, config.comp_fn);

    gl::namedFramebufferTexture(m_FBO, GL_DEPTH_ATTACHMENT, depth_attachment, 0);

    uint32_t status;
    IDK_GLCALL( status = glCheckNamedFramebufferStatus(m_FBO, GL_FRAMEBUFFER); )
    IDK_ASSERT("Incomplete framebuffer", status == GL_FRAMEBUFFER_COMPLETE);
}



void
idk::glFramebuffer::cubeDepthAttachment( const idk::glTextureConfig &config )
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
idk::glFramebuffer::depthArrayAttachment( uint32_t layers, const idk::glTextureConfig &config )
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

    float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    IDK_GLCALL( glTextureParameterfv(depth_attachment, GL_TEXTURE_BORDER_COLOR, color); )

    gl::textureParameteri(depth_attachment, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    gl::textureParameteri(depth_attachment, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);

    gl::namedFramebufferTexture(m_FBO, GL_DEPTH_ATTACHMENT, depth_attachment, 0);

    uint32_t status;
    IDK_GLCALL( status = glCheckNamedFramebufferStatus(m_FBO, GL_FRAMEBUFFER); )
    IDK_ASSERT("Incomplete framebuffer", status == GL_FRAMEBUFFER_COMPLETE);
}


void
idk::glFramebuffer::generateMipmap( int idx )
{
    IDK_ASSERT(
        "Called generateMipmap on non mip mapped texture",
        configs[idx].genmipmap == true
    );

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

