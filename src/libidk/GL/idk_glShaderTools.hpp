#pragma once

#include "common.hpp"


namespace idk::shadertools
{
    bool   checkError( GLuint shader );
    void   checkCompilation( GLuint shader );

    GLuint compileShader( GLenum type, const char *filepath );
};


