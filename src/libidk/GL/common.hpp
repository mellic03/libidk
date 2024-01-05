#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <GL/glew.h>
#include <GL/glu.h>
#include <assert.h>

#include "idk_glm.hpp"

#include <set>
#include <map>
#include <vector>


namespace idk
{
    uint8_t glVersionFlags( int major, int minor );
    int glVersionMajor( uint8_t version );
    int glVersionMinor( uint8_t version );
};


#define GLClearError() \
{ \
    while (glGetError() != GL_NO_ERROR); \
}

#ifdef IDK_DEBUG
    #define IDK_GLCALL(glFunc) \
    { \
        GLClearError(); \
        glFunc \
        GLenum err = glGetError(); \
        if (err != GL_NO_ERROR) \
        { \
            printf("OpenGL Error: %s\n", gluErrorString(err)); \
            fflush(stdout); \
            assert(err == GL_NO_ERROR); \
        } \
    }
#else
    #define IDK_GLCALL(glFunc) \
    { \
        glFunc \
    }
#endif


