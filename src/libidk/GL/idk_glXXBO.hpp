#pragma once

#include "idk_glBindings.hpp"

namespace idk
{
    template <GLenum gl_target>
    class glBufferObject;

    template <GLenum gl_target, typename T>
    class glTemplatedBufferObject;

    template <GLenum gl_target, typename T>
    class glStreamedBufferObject;
};


template <GLenum gl_target>
class idk::glBufferObject
{
protected:
    GLuint  m_buffer;
    GLuint  m_index;

public:

    GLuint ID() { return m_buffer; };

    void    init();
    void    init( GLuint index );

    void    bind();
    void    bind( GLuint index );

    void    bufferData( size_t nbytes, void *data, GLenum usage = GL_DYNAMIC_READ );
    void    bufferSubData( size_t offset, size_t nbytes, const void *data );

    void   *mapBuffer( GLenum access = GL_READ_WRITE );
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
idk::glBufferObject<gl_target>::bind()
{
    gl::bindBuffer(gl_target, m_buffer);
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
idk::glBufferObject<gl_target>::bufferSubData( size_t offset, size_t nbytes, const void *data )
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






template <GLenum gl_target, typename T>
class idk::glTemplatedBufferObject
{
private:
    GLuint  m_buffer;

public:

    void init( GLuint index )
    {
        size_t nbytes = sizeof(T);

        gl::createBuffers(1, &m_buffer);
        gl::bindBufferBase(gl_target, index, m_buffer);
        gl::namedBufferData(m_buffer, nbytes, nullptr, GL_DYNAMIC_COPY);
        // gl::namedBufferStorage(m_buffer, nbytes, nullptr, GL_MAP_WRITE_BIT);
    };


    void update( const T &data )
    {
        gl::namedBufferSubData(m_buffer, 0, sizeof(T), &data);

        // T *dest = reinterpret_cast<T *>(gl::mapNamedBuffer(m_buffer, GL_WRITE_ONLY));
        // std::memcpy(dest, &data, sizeof(T));
        // gl::unmapNamedBuffer(m_buffer);
    };

};






template <GLenum gl_target, typename T>
class idk::glStreamedBufferObject
{
private:
    GLuint  m_buffer;
    T      *m_data;

public:

    void init( GLuint index )
    {
        size_t nbytes = 3 * sizeof(T);

        gl::createBuffers(1, &m_buffer);
        gl::bindBufferBase(gl_target, index, m_buffer);

        GLbitfield flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
        gl::namedBufferStorage(m_buffer, nbytes, nullptr, flags);

        void *ptr = gl::mapNamedBufferRange(m_buffer, 0, nbytes, flags);
        m_data = reinterpret_cast<T *>(ptr);
    };


    uint32_t update( uint32_t index, const T &data )
    {
        std::memcpy(m_data+index, &data, sizeof(T));
        return (index + 1) % 3;
    };

};







