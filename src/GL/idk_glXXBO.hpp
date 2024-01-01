#pragma once

#include "idk_glBindings.hpp"

namespace idk { template <GLenum gl_target> class glBufferObject; };


template <GLenum gl_target>
class idk::glBufferObject
{
protected:
    GLuint  m_buffer;
    GLuint  m_index;

public:
    void    init();
    void    init( GLuint index );

    void    bind( GLuint index );

    void    bufferData( size_t nbytes, void *data, GLenum usage = GL_DYNAMIC_READ );
    void    bufferSubData( size_t offset, size_t nbytes, void *data );

    void *  mapBuffer( GLenum access = GL_READ_WRITE );
    void    unmapBuffer();

};


template <GLenum gl_target>
void
idk::glBufferObject<gl_target>::init( GLuint index )
{
    gl::createBuffers(1, &m_buffer);
    this->bind(index);
}


template <GLenum gl_target>
void
idk::glBufferObject<gl_target>::init()
{
    gl::createBuffers(1, &m_buffer);
}


template <GLenum gl_target>
void
idk::glBufferObject<gl_target>::bind( GLuint index )
{
    gl::bindBufferBase(gl_target, index, m_buffer);
}


template <GLenum gl_target>
void
idk::glBufferObject<gl_target>::bufferData( size_t nbytes, void *data, GLenum usage )
{
    gl::namedBufferData(m_buffer, nbytes, data, usage);
}


template <GLenum gl_target>
void
idk::glBufferObject<gl_target>::bufferSubData( size_t offset, size_t nbytes, void *data )
{
    gl::namedBufferSubData(m_buffer, offset, nbytes, data);
}


template <GLenum gl_target>
void *
idk::glBufferObject<gl_target>::mapBuffer( GLenum access )
{
    return gl::mapNamedBuffer(m_buffer, access);
}


template <GLenum gl_target>
void
idk::glBufferObject<gl_target>::unmapBuffer()
{
    gl::unmapNamedBuffer(m_buffer);
}

