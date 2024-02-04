#pragma once

#include "common.hpp"

namespace idk::gl
{
    inline void enable(GLenum cap)      { IDK_GLCALL( glEnable(cap);  ) };
    inline void disable(GLenum cap)     { IDK_GLCALL( glDisable(cap); ) };
    inline void enable()  {  };
    inline void disable() {  };

    template <typename... GLenums> inline void     enable( GLenum, GLenums... );
    template <typename... GLenums> inline void     disable( GLenum, GLenums... );

    void dispatchCompute( GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z );
    void memoryBarrier( GLbitfield barriers );

    void getFloatv( GLenum pname, GLfloat *params );


    void genVertexArrays  ( GLsizei n, GLuint *arrays );
    void genBuffers       ( GLsizei n, GLuint *buffers );
    void genTextures      ( GLsizei n, GLuint *textures );
    void genFramebuffers  ( GLsizei n, GLuint *framebuffers );
    void genRenderbuffers ( GLsizei n, GLuint *renderbuffers );

    void createVertexArrays ( GLsizei n, GLuint *arrays );
    void createBuffers      ( GLsizei n, GLuint *buffers );
    void createTextures     ( GLenum target, GLsizei n, GLuint *textures );

    GLuint createProgram    ();
    GLuint createShader     ( GLenum type );

    void   shaderSource     ( GLuint shader, GLsizei count, const GLchar *const *string,
                              const GLint *length );

    void   compileShader    ( GLuint shader );
    void   getShaderiv      ( GLuint shader, GLenum pname, GLint *param );
    void   getShaderInfoLog ( GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog );
    void   attachShader     ( GLuint program, GLuint shader );
    void   deleteShader     ( GLuint shader );
    void   validateProgram  ( GLuint program );
    void   linkProgram      ( GLuint program );


    void deleteVertexArrays  ( GLsizei n, GLuint *arrays );
    void deleteBuffers       ( GLsizei n, GLuint *buffers );
    void deleteTextures      ( GLsizei n, GLuint *textures );
    void deleteFramebuffers  ( GLsizei n, GLuint *framebuffers );
    void deleteRenderbuffers ( GLsizei n, GLuint *renderbuffers );

    void bindVertexArray( GLuint VAO );
    void bindBuffer( GLenum type, GLuint buf );
    void bindBufferBase( GLenum target, GLuint index, GLuint buffer );
    void bindFramebuffer( GLenum target, GLuint framebuffer );
    void bindRenderbuffer( GLenum target, GLuint renderbuffer );
    void bindTexture( GLenum target, GLuint texture );
    void bindTextureUnit( GLuint unit, GLuint texture );

    void bindImageTexture( GLuint unit, GLuint texture, GLint level, GLboolean layered,
                           GLint layer, GLenum access, GLenum format );

    void drawArrays( GLenum mode, GLint first, GLsizei count );
    void drawElements( GLenum mode, GLsizei count, GLenum type, const void *indices );
    void drawElementsInstanced( GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount );
    void multiDrawElements( GLenum mode, const GLsizei *count, GLenum type, const void *const *indices, GLsizei drawcount );
    void multiDrawElementsIndirect( GLenum mode, GLenum type, const void *indirect, GLsizei primcount, GLsizei stride );

    void bufferData( GLenum target, GLsizeiptr size, const void *data, GLenum usage );
    void bufferSubData( GLenum target, GLintptr offset, GLsizeiptr size, const void *data);

    void namedBufferData( GLuint buffer, GLsizeiptr size, const void *data, GLenum usage );
    void namedBufferSubData( GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data );
    void namedBufferStorage( GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags );


    void *mapBuffer( GLenum target, GLenum access );
    void unmapBuffer( GLenum target );

    void *mapNamedBuffer( GLuint buffer, GLenum access );
    void  unmapNamedBuffer( GLuint buffer );


    // glActiveXXX -----------------------------------------------------------------------------
    /**/
    void activeTexture( GLenum texture );
    // -----------------------------------------------------------------------------------------


    // glTexXXX --------------------------------------------------------------------------------
    /**/
    void texImage2D( GLenum target, GLint level, GLint internalformat, GLsizei w, GLsizei h,
                     GLint border, GLenum format, GLenum type, const void *data );

    void texSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
                        GLsizei height, GLenum format, GLenum type, const void *pixels );

    void texImage3D( GLenum target, GLint level, GLint internalformat, GLsizei w, GLsizei h,
                     GLsizei d, GLint border, GLenum format, GLenum type, const void *data );

    void texParameteri( GLenum target, GLenum pname, GLint param );

    // -----------------------------------------------------------------------------------------


    // glTextureXXX ----------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------
    void textureStorage2D( GLuint texture, GLsizei levels, GLenum internalformat,
                           GLsizei width, GLsizei height );

    void textureSubImage2D( GLenum texture, GLint level, GLint xoffset, GLint yoffset,
                            GLsizei width, GLsizei height, GLenum format, GLenum type,
                            const void *pixels );

    void textureStorage3D( GLuint texture, GLsizei levels, GLenum internalformat,
                           GLsizei width, GLsizei height, GLsizei depth );

    void textureSubImage3D( GLuint texture, GLint level, GLint xoffset, GLint yoffset,
                            GLint zoffset, GLsizei width, GLsizei height, GLsizei depth,
                            GLenum format, GLenum type, const void *pixels );

    void textureParameteri( GLuint texture, GLenum pname, GLint param );
    void textureParameterf( GLuint texture, GLenum pname, GLfloat param );
    // -----------------------------------------------------------------------------------------

    GLuint64 getTextureHandleARB( GLuint texture );
    void     makeTextureHandleResidentARB( GLuint64 handle );
    void     makeTextureHandleNonResidentARB( GLuint64 handle );

    void generateTextureMipmap( GLuint texture );
    void generateMipmap( GLenum target );
    void pixelStorei( GLenum pname, GLint param );


    // Framebuffer stuff  --------------------------------------------------------------------
    /**/
    void framebufferTexture( GLenum target, GLenum attachment, GLuint texture, GLint level );

    void framebufferTexture2D( GLenum target, GLenum attachment, GLenum textarget,
                                GLuint texture, GLint level );

    void framebufferTextureLayer( GLenum target, GLenum attachment, GLuint texture,
                                  GLint level, GLint layer );

    void namedFramebufferTextureLayer( GLuint framebuffer, GLenum attachment, GLuint texture,
                                       GLint level, GLint layer );
    // ---------------------------------------------------------------------------------------

    // Uniforms ------------------------------------------------------------------------------
    /**/
    GLint getUniformLocation( GLuint program, const char *name );
    void  uniform1i( GLint loc, int i );
    void  uniform1f( GLint loc, float f );
    void  uniform2fv( GLint loc, GLsizei count, float *value );
    void  uniform3fv( GLint loc, GLsizei count, float *value );
    void  uniform4fv( GLint loc, GLsizei count, float *value );
    void  uniformMatrix3fv( GLint loc, GLsizei count, GLboolean transpose, float *value );
    void  uniformMatrix4fv( GLint loc, GLsizei count, GLboolean transpose, float *value );

    void  uniformHandleui64ARB( GLint location, GLuint64 value );
    // ---------------------------------------------------------------------------------------

    void vertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized,
                              GLsizei stride, GLuint offset );

    void enableVertexAttribArray( GLuint index );


    void vertexArrayVertexBuffer( GLuint vaobj, GLuint bindingindex, GLuint buffer,
                                  GLintptr offset, GLsizei stride );

    void vertexArrayElementBuffer( GLuint vaobj, GLuint buffer );

    void enableVertexArrayAttrib( GLuint vaobj, GLuint index );

    void vertexArrayAttribFormat( GLuint vaobj, GLuint attribindex, GLint size, GLenum type,
                                  GLboolean normalized, GLuint relativeoffset );

    void vertexArrayAttribBinding( GLuint vaobj, GLuint attribindex, GLuint bindingindex );




    void useProgram( GLuint program );
    void deleteProgram( GLuint program );
    void clearColor( float r, float g, float b, float a );
    void clear( GLbitfield mask );
    void viewport( GLint x, GLint y, GLsizei w, GLsizei h );
    void cullFace( GLenum mode );
};


template <typename... GLenums>
inline void
idk::gl::enable( GLenum cap, GLenums... rest )
{
    enable(cap);
    enable(rest...);
}


template <typename... GLenums>
inline void
idk::gl::disable( GLenum cap, GLenums... rest )
{
    disable(cap);
    disable(rest...);
}
