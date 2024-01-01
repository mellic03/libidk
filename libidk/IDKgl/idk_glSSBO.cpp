// #include "idk_glSSBO.hpp"


// void
// idk::glSSBO::init( GLuint index )
// {
//     gl::createBuffers(1, &m_buffer);
//     gl::bindBufferBase(GL_SHADER_STORAGE_BUFFER, index, m_buffer);
// }


// void
// idk::glSSBO::bufferData( size_t nbytes, void *data, GLenum usage )
// {
//     gl::namedBufferData(m_buffer, nbytes, data, usage);
// }


// void
// idk::glSSBO::bufferSubData( size_t offset, size_t nbytes, void *data )
// {
//     gl::namedBufferSubData(m_buffer, offset, nbytes, data);
// }


// void *
// idk::glSSBO::mapBuffer( GLenum access )
// {
//     return gl::mapNamedBuffer(m_buffer, access);
// }


// void
// idk::glSSBO::unmapBuffer()
// {
//     gl::unmapNamedBuffer(m_buffer);
// }
