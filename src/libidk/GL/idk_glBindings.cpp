#include "idk_glBindings.hpp"



void
idk::gl::getFloatv( GLenum pname, GLfloat *params )
{
    IDK_GLCALL( glGetFloatv(pname, params); )
}



// glGenXXX ------------------------------------------------------------------------------
/**/
void idk::gl::genVertexArrays( GLsizei n, GLuint *arrays )
{
    IDK_GLCALL( glGenVertexArrays(n, arrays); )
}

void idk::gl::genBuffers( GLsizei n, GLuint *buffers )
{
    IDK_GLCALL( glGenBuffers(n, buffers); )
}

void idk::gl::genTextures( GLsizei n, GLuint *textures )
{
    IDK_GLCALL( glGenTextures(n, textures); )
}

void idk::gl::genFramebuffers( GLsizei n, GLuint *framebuffers )
{
    IDK_GLCALL( glGenFramebuffers(n, framebuffers); )
}

void idk::gl::genRenderbuffers( GLsizei n, GLuint *renderbuffers )
{
    IDK_GLCALL( glGenRenderbuffers(n, renderbuffers); )
}
// ---------------------------------------------------------------------------------------


void idk::gl::createTextures ( GLenum target, GLsizei n, GLuint *textures )
{
    IDK_GLCALL( glCreateTextures(target, n, textures); )
}



// glDeleteXXX ---------------------------------------------------------------------------
/**/
void idk::gl::deleteVertexArrays( GLsizei n, GLuint *arrays )
{
    IDK_GLCALL( glDeleteVertexArrays(n, arrays); )
}

void idk::gl::deleteBuffers( GLsizei n, GLuint *buffers )
{
    IDK_GLCALL( glDeleteBuffers(n, buffers); )
}

void idk::gl::deleteTextures( GLsizei n, GLuint *textures )
{
    IDK_GLCALL( glDeleteTextures(n, textures); )
}

void idk::gl::deleteFramebuffers( GLsizei n, GLuint *framebuffers )
{
    IDK_GLCALL( glDeleteFramebuffers(n, framebuffers); )
}

void idk::gl::deleteRenderbuffers( GLsizei n, GLuint *renderbuffers )
{
    IDK_GLCALL( glDeleteRenderbuffers(n, renderbuffers); )
}
// ---------------------------------------------------------------------------------------


// glBindXXX -----------------------------------------------------------------------------
/**/
void idk::gl::bindVertexArray( GLuint VAO )
{
    IDK_GLCALL( glBindVertexArray(VAO); )
}

void idk::gl::bindBuffer( GLenum type, GLuint buf )
{
    IDK_GLCALL( glBindBuffer(type, buf); )
}

void idk::gl::bindBufferBase( GLenum target, GLuint index, GLuint buffer )
{
    glBindBufferBase(target, index, buffer);
}

void idk::gl::bindFramebuffer( GLenum target, GLuint framebuffer )
{
    IDK_GLCALL( glBindFramebuffer(target, framebuffer); )
}

void idk::gl::bindRenderbuffer( GLenum target, GLuint renderbuffer )
{
    IDK_GLCALL( glBindRenderbuffer(target, renderbuffer); )
}

void idk::gl::bindTexture( GLenum target, GLuint texture )
{
    IDK_GLCALL( glBindTexture(target, texture); )
}

void idk::gl::bindTextureUnit( GLuint unit, GLuint texture )
{
    IDK_GLCALL( glBindTextureUnit(unit, texture); )
}

// ---------------------------------------------------------------------------------------


// glDrawXXX -----------------------------------------------------------------------------
/**/
void
idk::gl::drawArrays( GLenum mode, GLint first, GLsizei count )
{
    IDK_GLCALL( glDrawArrays(mode, first, count); )
}

void
idk::gl::drawElements( GLenum mode, GLsizei count, GLenum type, const void *indices )
{
    IDK_GLCALL( glDrawElements(mode, count, type, indices); )
}

void
idk::gl::drawElementsInstanced( GLenum mode, GLsizei count, GLenum type,
                                     const void *indices, GLsizei instancecount )
{
    IDK_GLCALL( glDrawElementsInstanced(mode, count, type, indices, instancecount); )
}

void
idk::gl::multiDrawElements( GLenum mode, const GLsizei *count, GLenum type,
                            const void *const *indices, GLsizei drawcount )
{
    IDK_GLCALL( glMultiDrawElements(mode, count, type, indices, drawcount); )
}

void
idk::gl::multiDrawElementsIndirect( GLenum mode, GLenum type, const void *indirect,
                                    GLsizei primcount, GLsizei stride )
{
    IDK_GLCALL( glMultiDrawElementsIndirect(mode, type, indirect, primcount, stride); )
}
// ---------------------------------------------------------------------------------------


// glBufferXXX ---------------------------------------------------------------------------
/**/
void
idk::gl::bufferData( GLenum target, GLsizeiptr size, const void *data, GLenum usage )
{
    IDK_GLCALL( glBufferData(target, size, data, usage); )
}

void
idk::gl::bufferSubData( GLenum target, GLintptr offset, GLsizeiptr size, const void *data)
{
    IDK_GLCALL( glBufferSubData(target, offset, size, data); )
}

void
idk::gl::createVertexArrays( GLsizei n, GLuint *arrays )
{
    IDK_GLCALL( glCreateVertexArrays(n, arrays); )
}


void
idk::gl::createBuffers( GLsizei n, GLuint *buffers )
{
    IDK_GLCALL( glCreateBuffers(n, buffers); )
}

void
idk::gl::namedBufferData( GLuint buffer, GLsizeiptr size, const void *data, GLenum usage )
{
    IDK_GLCALL( glNamedBufferData(buffer, size, data, usage); )
}

void
idk::gl::namedBufferSubData( GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data )
{
    IDK_GLCALL( glNamedBufferSubData(buffer, offset, size, data); )
}


void
idk::gl::namedBufferStorage( GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags )
{
    IDK_GLCALL( glNamedBufferStorage(buffer, size, data, flags); )
}



void *
idk::gl::mapBuffer( GLenum target, GLenum access )
{
    void *data;
    IDK_GLCALL( data = glMapBuffer(target, access); )
    return data;
}

void
idk::gl::unmapBuffer( GLenum target )
{
    IDK_GLCALL( glUnmapBuffer(target); )
}

void *
idk::gl::mapNamedBuffer( GLuint buffer, GLenum access )
{
    void *data;
    IDK_GLCALL( data = glMapNamedBuffer(buffer, access); )
    return data;
}

void 
idk::gl::unmapNamedBuffer( GLuint buffer )
{
    IDK_GLCALL( glUnmapNamedBuffer(buffer); )
}
// ---------------------------------------------------------------------------------------


// glActiveXXX ---------------------------------------------------------------------------
/**/
/**/
void
idk::gl::activeTexture( GLenum texture )
{
    IDK_GLCALL( glActiveTexture(texture); )
}
// ---------------------------------------------------------------------------------------


// glTexXXX ------------------------------------------------------------------------------
/**/
void
idk::gl::texImage2D( GLenum target, GLint level, GLint internalformat, GLsizei w, GLsizei h,
                     GLint border, GLenum format, GLenum type, const void *data )
{
    IDK_GLCALL( glTexImage2D(target, level, internalformat, w, h, border, format, type, data); )
}

void
idk::gl::texSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
                        GLsizei height, GLenum format, GLenum type, const void *pixels )
{
    glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void
idk::gl::texImage3D( GLenum target, GLint level, GLint internalformat, GLsizei w, GLsizei h,
                     GLsizei d, GLint border, GLenum format, GLenum type, const void *data )
{
    IDK_GLCALL( glTexImage3D(target, level, internalformat, w, h, d, border, format, type, data); )
}

void
idk::gl::texParameteri( GLenum target, GLenum pname, GLint param )
{
    IDK_GLCALL( glTexParameteri(target, pname, param); )
}


GLuint64
idk::gl::getTextureHandleARB( GLuint texture )
{
    GLuint64 handle;
    IDK_GLCALL( handle = glGetTextureHandleARB(texture); )

    return handle;
}

void
idk::gl::makeTextureHandleResidentARB( GLuint64 handle )
{
    IDK_GLCALL( glMakeTextureHandleResidentARB(handle); )
}

void
idk::gl::makeTextureHandleNonResidentARB( GLuint64 handle )
{
    IDK_GLCALL( glMakeTextureHandleNonResidentARB(handle); )
}


void
idk::gl::generateTextureMipmap( GLuint texture )
{
    IDK_GLCALL( glGenerateTextureMipmap(texture); )
}


void
idk::gl::generateMipmap( GLenum target )
{
    IDK_GLCALL( glGenerateMipmap(target); )
}

void
idk::gl::pixelStorei( GLenum pname, GLint param )
{
    IDK_GLCALL( glPixelStorei(pname, param); )
}
// ---------------------------------------------------------------------------------------------



// glTextureXXX
// ---------------------------------------------------------------------------------------------
void
idk::gl::textureStorage2D( GLuint texture, GLsizei levels, GLenum internalformat,
                                GLsizei width, GLsizei height )
{
    IDK_GLCALL( glTextureStorage2D(texture, levels, internalformat, width, height); )
}

void
idk::gl::textureSubImage2D( GLenum texture, GLint level, GLint xoffset, GLint yoffset,
                                 GLsizei width, GLsizei height, GLenum format, GLenum type,
                                 const void *pixels )
{
    IDK_GLCALL(
        glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
    )
}


void
idk::gl::textureStorage3D( GLuint texture, GLsizei levels, GLenum internalformat,
                           GLsizei width, GLsizei height, GLsizei depth )
{
    IDK_GLCALL( glTextureStorage3D(texture, levels, internalformat, width, height, depth); )
}


void
idk::gl::textureSubImage3D( GLuint texture, GLint level, GLint xoffset, GLint yoffset,
                            GLint zoffset, GLsizei width, GLsizei height, GLsizei depth,
                            GLenum format, GLenum type, const void *pixels )
{
    IDK_GLCALL(
        glTextureSubImage3D(
            texture,
            level,
            xoffset, yoffset, zoffset,
            width, height, depth,
            format,
            type,
            pixels
        );
    )
}



void
idk::gl::textureParameteri( GLuint texture, GLenum pname, GLint param )
{
    IDK_GLCALL( glTextureParameteri(texture, pname, param); )
}

void
idk::gl::textureParameterf( GLuint texture, GLenum pname, GLfloat param )
{
    IDK_GLCALL( glTextureParameterf(texture, pname, param); )
}
// ---------------------------------------------------------------------------------------------



// glFramebufferXXX ---------------------------------------------------------------------
void
idk::gl::framebufferTexture( GLenum target, GLenum attachment, GLuint texture, GLint level )
{
    IDK_GLCALL( glFramebufferTexture(target, attachment, texture, level); )
}

void
idk::gl::framebufferTexture2D( GLenum target, GLenum attachment, GLenum textarget,
                               GLuint texture, GLint level )
{
    IDK_GLCALL( glFramebufferTexture2D(target, attachment, textarget, texture, level); )
}

void
idk::gl::framebufferTextureLayer( GLenum target, GLenum attachment, GLuint texture,
                                  GLint level, GLint layer )
{
    IDK_GLCALL( glFramebufferTextureLayer(target, attachment, texture, level, layer); )
}

void
idk::gl::namedFramebufferTextureLayer( GLuint framebuffer, GLenum attachment, GLuint texture,
                                       GLint level, GLint layer )
{
    IDK_GLCALL( glNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer); )
}
// ---------------------------------------------------------------------------------------



// Uniforms ------------------------------------------------------------------------------
/**/
GLint
idk::gl::getUniformLocation( GLuint program, std::string name )
{
    return glGetUniformLocation(program, name.c_str());
}

void
idk::gl::uniform1i( GLint loc, int i )
{
    IDK_GLCALL( glUniform1i(loc, i); )
}

void idk::gl::uniform1f( GLint loc, float f )
{
    IDK_GLCALL( glUniform1f(loc, f); )
}

void
idk::gl::uniform2fv( GLint loc, GLsizei count, float *value )
{
    IDK_GLCALL( glUniform2fv(loc, count, value); )
}

void
idk::gl::uniform3fv( GLint loc, GLsizei count, float *value )
{
    IDK_GLCALL( glUniform3fv(loc, count, value); )
}

void
idk::gl::uniform4fv( GLint loc, GLsizei count, float *value )
{
    IDK_GLCALL( glUniform4fv(loc, count, value); )
}

void
idk::gl::uniformMatrix3fv( GLint loc, GLsizei count, GLboolean transpose, float *value )
{
    IDK_GLCALL( glUniformMatrix3fv(loc, count, transpose, value); )
}

void
idk::gl::uniformMatrix4fv( GLint loc, GLsizei count, GLboolean transpose, float *value )
{
    IDK_GLCALL( glUniformMatrix4fv(loc, count, transpose, value); )
}


void
idk::gl::uniformHandleui64ARB( GLint location, GLuint64 value )
{
    IDK_GLCALL( glUniformHandleui64ARB(location, value); )
}
// ---------------------------------------------------------------------------------------


void
idk::gl::vertexAttribPointer( GLuint index, GLint size,
                              GLenum type, GLboolean normalized,
                              GLsizei stride, GLuint offset )
{
    IDK_GLCALL(
        glVertexAttribPointer(
            index, size, type, normalized,
            stride, reinterpret_cast<void *>(offset)
        );
    )
}


void
idk::gl::enableVertexAttribArray( GLuint index )
{
    IDK_GLCALL( glEnableVertexAttribArray(index); )
}


void
idk::gl::vertexArrayVertexBuffer( GLuint vaobj, GLuint bindingindex, GLuint buffer,
                                  GLintptr offset, GLsizei stride )
{
    IDK_GLCALL( glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride); )
}

void
idk::gl::vertexArrayElementBuffer( GLuint vaobj, GLuint buffer )
{
    IDK_GLCALL( glVertexArrayElementBuffer(vaobj, buffer); )
}


void
idk::gl::enableVertexArrayAttrib( GLuint vaobj, GLuint index )
{
    IDK_GLCALL( glEnableVertexArrayAttrib(vaobj, index); )
}

void
idk::gl::vertexArrayAttribFormat( GLuint vaobj, GLuint attribindex, GLint size, GLenum type,
                                  GLboolean normalized, GLuint relativeoffset )
{
    IDK_GLCALL(
        glVertexArrayAttribFormat(
            vaobj, attribindex, size, type, normalized, relativeoffset
        );
    )
}

void
idk::gl::vertexArrayAttribBinding( GLuint vaobj, GLuint attribindex, GLuint bindingindex )
{
    IDK_GLCALL( glVertexArrayAttribBinding(vaobj, attribindex, bindingindex); )
}


void
idk::gl::useProgram( GLuint program )
{
    IDK_GLCALL( glUseProgram(program); )
}

void
idk::gl::deleteProgram( GLuint program )
{
    IDK_GLCALL( glDeleteProgram(program); )
}


void
idk::gl::clearColor( float r, float g, float b, float a )
{
    IDK_GLCALL( glClearColor(r, g, b, a); )
}


void
idk::gl::clear( GLbitfield mask )
{
    IDK_GLCALL( glClear(mask); )
}


void
idk::gl::viewport( GLint x, GLint y, GLsizei w, GLsizei h )
{
    IDK_GLCALL( glViewport(x, y, w, h); )
}


void
idk::gl::cullFace( GLenum mode )
{
    IDK_GLCALL( glCullFace(mode); )
}
