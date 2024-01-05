#include "idk_glShaderTools.hpp"
#include "idk_glBindings.hpp"
#include "../idk_assert.hpp"

#include <string>
#include <memory>

#include <fstream>
#include <sstream>
#include <iostream>


void
idk::shadertools::checkError( GLuint shader )
{
    GLint length;
    gl::getShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

    if (length > 1)
    {
        auto message = std::make_unique<char>(length);
        gl::getShaderInfoLog(shader, length, &length, message.get());
        std::cout << message.get() << "\n";
    }
}



GLuint
idk::shadertools::compileShader( GLenum type, const char *filepath )
{ 
    std::stringstream buffer;
    buffer << std::ifstream(filepath).rdbuf();
    std::string str = buffer.str();
    const char *source = str.c_str();

    GLuint shader_id = gl::createShader(type);
    gl::shaderSource(shader_id, 1, &source, nullptr);
    gl::compileShader(shader_id);
    shadertools::checkError(shader_id);

    GLint result;
    gl::getShaderiv(shader_id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        std::cout << "Failed to compile ";
        switch (type)
        {
            case GL_VERTEX_SHADER:          std::cout << "vertex";          break;
            case GL_FRAGMENT_SHADER:        std::cout << "fragment";        break;
            case GL_GEOMETRY_SHADER:        std::cout << "geometry";        break;
            case GL_COMPUTE_SHADER:         std::cout << "compute";         break;
            case GL_TESS_EVALUATION_SHADER: std::cout << "tess evaluation"; break;
        }
        std::cout << " shader, file: " << filepath << "\n";
    
        shadertools::checkError(shader_id);
        IDK_ASSERT("Shader compilation failure", false);
    }

    return shader_id;
}
