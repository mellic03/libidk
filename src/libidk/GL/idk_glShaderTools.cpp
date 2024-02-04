#include "idk_glShaderTools.hpp"
#include "idk_glBindings.hpp"
#include "../idk_assert.hpp"

#include <string>
#include <memory>

#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>


bool
idk::shadertools::checkError( GLuint shader )
{
    GLint length;
    gl::getShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

    if (length > 0)
    {
        auto message = std::make_unique<char>(length);
        gl::getShaderInfoLog(shader, length, &length, message.get());
        std::cout << message.get() << "\n";
        return true;
    }

    return false;
}



static std::string
idk_shadertools_include( const std::string &current_path, const std::string &include_line )
{
    namespace fs = std::filesystem;

    std::string relpath = include_line;
    size_t pos;
    
    pos     = relpath.find("\"");
    relpath = relpath.substr(pos+1);
    pos     = relpath.find("\"");
    relpath = relpath.substr(0, pos);


    fs::path include_path = fs::path(current_path).parent_path() / fs::path(relpath);

    std::string src;

    std::ifstream stream(include_path);
    std::string line;

    while (std::getline(stream, line))
    {
        src += line + "\n";
    }

    return src;
}


static std::string
idk_shadertools_parse( const char *filepath )
{
    std::string src = "";

    std::stringstream stream;
    stream << std::ifstream(filepath).rdbuf();
    std::string line;

    while (std::getline(stream, line))
    {
        if (line.find("include") != std::string::npos)
        {
            src += idk_shadertools_include(filepath, line) + "\n";
        }

        else
        {
            src += line + "\n";
        }
    }

    return src;
}


GLuint
idk::shadertools::compileShader( GLenum type, const char *filepath )
{
    IDK_ASSERT("File does not exist", std::filesystem::exists(std::string(filepath)));

    std::string str = idk_shadertools_parse(filepath);
    // std::string str = buffer.str();
    const char *source = str.c_str();

    GLuint shader_id = gl::createShader(type);
    gl::shaderSource(shader_id, 1, &source, nullptr);
    gl::compileShader(shader_id);

    if (shadertools::checkError(shader_id))
    {
        std::cout << source << "\n";
    }

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
