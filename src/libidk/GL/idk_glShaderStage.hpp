#pragma once

#include "common.hpp"
#include "idk_glBindings.hpp"


namespace idk
{
    GLuint compileShader( GLenum type, const char *filepath );

    class glShaderStage;
    class glShaderProgram;
};


class idk::glShaderStage
{
private:
    int m_refcount = 0;

public:
    GLenum m_type = GL_VERTEX_SHADER;
    GLuint m_shader_id;

    glShaderStage( const char *filepath );
    glShaderStage( GLenum type, const char *filepath );
    glShaderStage( glShaderStage & );
    glShaderStage( glShaderStage && );
    ~glShaderStage();

    glShaderStage &operator = ( glShaderStage && ); 

};

