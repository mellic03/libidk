#pragma once

#include "common.hpp"
#include "idk_glBindings.hpp"


namespace idk { class glInstancedTransforms; };


class idk::glInstancedTransforms
{
private:
    GLuint m_VBO;

public:
    size_t instancecount = 0;

    void         init( GLuint index, const std::vector<glm::mat4> &data );
    void         update( const std::vector<glm::mat4> &data );
    void         bind();
    void         unbind();

};
