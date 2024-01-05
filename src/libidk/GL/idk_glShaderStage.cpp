#include "idk_glShaderStage.hpp"
#include "idk_glShaderTools.hpp"


idk::glShaderStage::glShaderStage( GLenum type, const char *filepath )
{
    m_type      = type;
    m_shader_id = idk::shadertools::compileShader(type, filepath);
}

