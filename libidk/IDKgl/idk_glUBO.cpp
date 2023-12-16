#include "idk_glUBO.hpp"


int
round_up( int n, int multipleof )
{
    if (n % multipleof == 0)
        return n;
    return n + (multipleof - (n % multipleof));
};


idk::glUBO::glUBO( GLuint location, GLsizeiptr size )
{
    m_offset = 0;

    gl::createBuffers(1, &m_UBO);
    gl::namedBufferData(m_UBO, size, NULL, GL_DYNAMIC_DRAW);
    gl::bindBufferBase(GL_UNIFORM_BUFFER, location, m_UBO);
}


void
idk::glUBO::bind()
{
    m_offset = 0;
};


void
idk::glUBO::bind( GLint location )
{
    gl::bindBufferBase(GL_UNIFORM_BUFFER, location, m_UBO);
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
    gl::namedBufferSubData(m_UBO, m_offset, size, data);
    m_offset += round_up(size, 16);
}

