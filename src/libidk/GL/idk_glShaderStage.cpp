#include "idk_glShaderStage.hpp"
#include "idk_glShaderTools.hpp"
#include "../idk_assert.hpp"

#include <iostream>
#include <filesystem>


idk::glShaderStage::glShaderStage( const char *filepath )
{
    m_refcount += 1;

    std::string ext = std::filesystem::path(filepath).extension();    

    m_type = GL_NONE;

    if      (ext == ".vs")      m_type = GL_VERTEX_SHADER;
    else if (ext == ".fs")      m_type = GL_FRAGMENT_SHADER;
    else if (ext == ".gs")      m_type = GL_GEOMETRY_SHADER;
    else if (ext == ".comp")    m_type = GL_COMPUTE_SHADER;

    IDK_ASSERT("Could not deduce shader stage from file extension", m_type != GL_NONE);

    m_shader_id = idk::shadertools::compileShader(m_type, filepath);
}


idk::glShaderStage::glShaderStage( GLenum type, const char *filepath )
{
    m_refcount += 1;

    m_type      = type;
    m_shader_id = idk::shadertools::compileShader(m_type, filepath);
}


idk::glShaderStage::glShaderStage( idk::glShaderStage &other )
{
    other.m_refcount += 1;

    m_refcount  = other.m_refcount;
    m_type      = other.m_type;
    m_shader_id = other.m_shader_id;
}


idk::glShaderStage::glShaderStage( idk::glShaderStage &&other )
{
    m_refcount  = other.m_refcount;
    m_type      = other.m_type;
    m_shader_id = other.m_shader_id;
}



idk::glShaderStage::~glShaderStage()
{
    m_refcount -= 1;

    if (m_refcount <= 0)
    {
        gl::deleteShader(m_shader_id);
    }
}




idk::glShaderStage &
idk::glShaderStage::operator = ( idk::glShaderStage &&other )
{
    if (this == &other)
    {
        return *this;
    }

    m_refcount  = other.m_refcount;
    m_type      = other.m_type;
    m_shader_id = other.m_shader_id;

    return *this;
}


