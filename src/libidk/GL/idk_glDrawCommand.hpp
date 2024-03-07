#pragma once

#include <cstdint>


namespace idk { struct glDrawCmd; };

struct idk::glDrawCmd
{
    GLuint count;
    GLuint instanceCount;
    GLuint firstIndex;
    GLuint baseVertex;
    GLuint baseInstance;
};




