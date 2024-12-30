#pragma once

#include "common.hpp"
#include <string>
#include <vector>

namespace idk::shadertools
{
    bool   checkError( GLuint shader );
    void   checkCompilation( GLuint shader );

    GLuint compileShader( GLenum type, const char *filepath,
                          const std::vector<std::string> &defines = {} );
};


