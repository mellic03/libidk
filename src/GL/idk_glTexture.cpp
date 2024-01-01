#include "idk_glTexture.hpp"

#include "../idk_assert.hpp"
#include "../idk_math.hpp"


static size_t
gl_format_num_elements( GLenum format )
{
    switch (format)
    {
        case GL_RED:
        case GL_GREEN:
        case GL_BLUE:
        case GL_ALPHA:
        case GL_LUMINANCE:
        case GL_DEPTH_COMPONENT:
            return 1;

        case GL_RG:
        case GL_LUMINANCE_ALPHA:
            return 2;

        case GL_RGB:
        case GL_BGR:
            return 3;

        case GL_RGBA:
        case GL_BGRA:
            return 4;

        default:
            IDK_ASSERT("Unsupported texture format", false);
            return -1;
    }
} 



idk::glTexture::glTexture( const idk::glTexture &other )
: m_id      (other.m_id),
  m_handle  (other.m_handle),
  m_size    (other.m_size),
  m_nbytes  (other.m_nbytes),
  m_config  (other.m_config),
  m_mips    (other.m_mips.size())
{
    size_t epp      = gl_format_num_elements(m_config.format);
    size_t typesize = (m_config.datatype == GL_FLOAT) ? sizeof(float) : sizeof(uint8_t);

    for (int i=0; i<m_mips.size(); i++)
    {
        glm::ivec2 mipsize = m_size / int(glm::pow(2, i));
        size_t     nbytes  = mipsize.x * mipsize.y * epp * typesize;

        m_mips[i] = std::unique_ptr<uint8_t[]>(new uint8_t[nbytes]);
        std::memcpy(m_mips[i].get(), other.m_mips[i].get(), nbytes);
    }
}


idk::glTexture::glTexture( const idk::glTexture &&other )
: m_id      (other.m_id),
  m_handle  (other.m_handle),
  m_size    (other.m_size),
  m_nbytes  (other.m_nbytes),
  m_config  (other.m_config),
  m_mips    (other.m_mips.size())
{
    size_t epp      = gl_format_num_elements(m_config.format);
    size_t typesize = (m_config.datatype == GL_FLOAT) ? sizeof(float) : sizeof(uint8_t);

    for (int i=0; i<m_mips.size(); i++)
    {
        glm::ivec2 mipsize = m_size / int(glm::pow(2, i));
        size_t     nbytes  = mipsize.x * mipsize.y * epp * typesize;

        m_mips[i] = std::unique_ptr<uint8_t[]>(new uint8_t[nbytes]);
        std::memcpy(m_mips[i].get(), other.m_mips[i].get(), nbytes);
    }
}


idk::glTexture::glTexture( GLuint id, const glm::ivec2 &size, const glTextureConfig &config )
: m_id(id),
  m_size(size),
  m_config(config)
{
    size_t epp      = gl_format_num_elements(config.format);
    size_t typesize = (config.datatype == GL_FLOAT) ? sizeof(float) : sizeof(uint8_t);

    if (config.genmipmap)
    {
        GLsizei levels = 1 + floor(log2(std::max(size.x, size.y)));
        m_mips.resize(levels);
    }

    for (int i=0; i<m_mips.size(); i++)
    {
        glm::ivec2 mipsize = size / int(glm::pow(2, i));
        size_t     nbytes  = mipsize.x * mipsize.y * epp * typesize;

        m_mips[i] = std::unique_ptr<uint8_t[]>(new uint8_t[nbytes]);

        IDK_GLCALL(
            glGetTextureImage(
                m_id, i, GL_RGBA, GL_UNSIGNED_BYTE, nbytes, m_mips[i].get()
            );
        )
    }

    if (m_config.bindless)
    {
        m_handle = gl::getTextureHandleARB(m_id);
        gl::makeTextureHandleResidentARB(m_handle);
    }
}


const float &
idk::glTexture::sample1f( float u, float v, int l ) const
{
    int iu = int(u);
    int iv = int(v);

    int w = m_size.x / int(glm::pow(2, l));
    int h = m_size.y / int(glm::pow(2, l));

    int x = int(w*u) % w;
    int y = int(h*v) % h;

    return *(&this->_data1f(l)[1*w*iv + 1*iu + 0]);
}


const uint8_t &
idk::glTexture::sample1u( float u, float v, int l ) const
{
    int iu = int(u);
    int iv = int(v);

    int w = m_size.x / int(glm::pow(2, l));
    int h = m_size.y / int(glm::pow(2, l));

    int x = int(w*u) % w;
    int y = int(h*v) % h;

    return *(&this->_data1u(l)[1*w*iv + 1*iu + 0]);
}


const uint8_t *
idk::glTexture::sample4u( float u, float v, int l ) const
{
    return &sample1u(u, v, l);
}



glm::vec4
idk::glTexture::isample4f( int x, int y, int l ) const
{
    int w = m_size.x / int(glm::pow(2, l));
    int h = m_size.y / int(glm::pow(2, l));

    x %= w; 
    y %= h; 

    uint8_t *data = this->_data1u(l);

    glm::vec4 sample = glm::vec4(
        float(data[4*w*y + 4*x + 0]),
        float(data[4*w*y + 4*x + 1]),
        float(data[4*w*y + 4*x + 2]),
        float(data[4*w*y + 4*x + 3])
    );

    return sample / 255.0f;
}


glm::vec4
idk::glTexture::sample4f( float u, float v, int l ) const
{
    int w = m_size.x / int(glm::pow(2, l));
    int h = m_size.y / int(glm::pow(2, l));

    int x = int(w*u) % w;
    int y = int(h*v) % h;

    uint8_t *data = this->_data1u(l);

    glm::vec4 sample = glm::vec4(
        float(data[4*w*y + 4*x + 0]),
        float(data[4*w*y + 4*x + 1]),
        float(data[4*w*y + 4*x + 2]),
        float(data[4*w*y + 4*x + 3])
    );

    return sample / 255.0f;
}


glm::vec4
idk::glTexture::bisample4f( float u, float v, int l ) const
{
    int w = m_size.x / int(glm::pow(2, l));
    int h = m_size.y / int(glm::pow(2, l));

    int x = int(w*u) % w;
    int y = int(h*v) % h;

    glm::vec4 h00 = isample4f(x,   y,   l);
    glm::vec4 h01 = isample4f(x,   y+1, l);
    glm::vec4 h10 = isample4f(x+1, y,   l);
    glm::vec4 h11 = isample4f(x+1, y+1, l);

    glm::vec3 weights_A = idk::calculate_barycentric(
        float(w)*u, float(h)*v,
        glm::vec2(x,   y  ),
        glm::vec2(x,   y+1),
        glm::vec2(x+1, y  )
    );

    glm::vec3 weights_B = idk::calculate_barycentric(
        float(w)*u, float(h)*v,
        glm::vec2(x+1, y+1),
        glm::vec2(x,   y+1),
        glm::vec2(x+1, y  )
    );

    if (weights_A[0] >= 0.0f && weights_A[1] >= 0.0f && weights_A[2] >= 0.0f)
    {
        return h00*weights_A[0] + h01*weights_A[1] + h10*weights_A[2];
    }

    else
    {
        return h11*weights_B[0] + h01*weights_B[1] + h10*weights_B[2];
    }
}


