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

public:
    GLenum m_type = GL_VERTEX_SHADER;
    GLuint m_shader_id;

    glShaderStage( GLenum type, const char *filepath );

};

