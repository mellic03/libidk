#pragma once

#include "idk_glBindings.hpp"
#include "idk_glXXBO.hpp"


namespace idk
{
    class glUBO;
};


int round_up( int n, int multipleof );


class idk::glUBO: public idk::glBufferObject<GL_UNIFORM_BUFFER>
{
private:
    GLintptr    m_offset;

public:
    void        bind( GLuint index );
    void        bind();
    void        unbind();

    void        add(GLintptr size, const void *data);

    template <typename data_t>
    void        add(const void *data);

};



template <typename T>
void
idk::glUBO::add(const void *data)
{
    gl::namedBufferSubData(m_buffer, m_offset, sizeof(T), data);
    m_offset += round_up(sizeof(T), 16);
}

