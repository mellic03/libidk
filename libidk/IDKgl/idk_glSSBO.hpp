#pragma once

#include "idk_glBindings.hpp"
#include "idk_glXXBO.hpp"

namespace idk
{
    // class glSSBO;
    using glSSBO = idk::glBufferObject<GL_SHADER_STORAGE_BUFFER>;

};



// class idk::glSSBO: public idk::glBufferObject<GL_SHADER_STORAGE_BUFFER>
// {
// private:
//     GLuint  m_buffer;
//     GLuint  m_index;

// public:

//     void    init( GLuint index );
//     void    bufferData( size_t nbytes, void *data, GLenum usage = GL_DYNAMIC_READ );
//     void    bufferSubData( size_t offset, size_t nbytes, void *data );

//     void *  mapBuffer( GLenum access = GL_READ_WRITE );
//     void    unmapBuffer();

// };


