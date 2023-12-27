#pragma once

#include <cstdint>


namespace idk { struct glDrawElementsIndirectCommand; };

struct idk::glDrawElementsIndirectCommand
{
    GLuint count;
    GLuint instanceCount;
    GLuint firstIndex;
    GLuint baseVertex;
    GLuint baseInstance;
};




