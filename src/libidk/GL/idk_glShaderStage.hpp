#pragma once

#include "common.hpp"
#include "idk_glBindings.hpp"

#include <string>
#include <vector>
#include <set>


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
    std::set<std::string> m_defines;
    void init( const char *filepath, const std::vector<std::string> &defines );

public:
    GLenum m_type = GL_VERTEX_SHADER;
    GLuint m_shader_id;
    std::string m_path;

    glShaderStage( const char *filepath );
    glShaderStage( const char *filepath, const std::vector<std::string> &defines );
    glShaderStage( GLenum type, const char *filepath );
    glShaderStage( glShaderStage & );
    glShaderStage( glShaderStage && );
    ~glShaderStage();

    glShaderStage &operator = ( glShaderStage && ); 

};

