#include "idk_glUBO.hpp"


int
round_up( int n, int multipleof )
{
    if (n % multipleof == 0)
        return n;
    return n + (multipleof - (n % multipleof));
};


void
idk::glUBO::bind( GLuint index )
{
    gl::bindBufferBase(GL_UNIFORM_BUFFER, index, m_buffer);
    m_offset = 0;
};


void
idk::glUBO::bind()
{
    m_offset = 0;
};


void
idk::glUBO::unbind()
{
    m_offset = 0;
};


void
idk::glUBO::add(GLintptr size, const void *data)
{
    gl::namedBufferSubData(m_buffer, m_offset, size, data);
    m_offset += round_up(size, 16);
}

