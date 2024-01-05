#pragma once

#include "common.hpp"
#include <string>

// Store individual functions in various files for shader generation maybe?

namespace idk
{
    std::string genVersion( GLuint version );
    GLuint genVertexShader( GLuint version, GLuint ree );
    GLuint genFragmentShader( GLuint version, GLuint ree );

};

