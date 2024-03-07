#pragma once

#include "common.hpp"
#include "idk_glBindings.hpp"
#include "idk_glShaderStage.hpp"


#include <string>

namespace idk
{
    class glShaderStage;
    class glShaderProgram;
};


class idk::glShaderProgram
{
public:
    static GLuint compileShader( GLenum type, const char *filepath );

    struct Loc { GLint value = -1; };
    struct Def { std::string value = "NONE"; };

private:
    inline static GLuint current_bound_id = 0;

    std::string                 m_version;
    std::string                 m_vert_src;
    std::string                 m_geom_src;
    std::string                 m_frag_src;

    std::string                 m_vert_name;
    std::string                 m_geom_name;
    std::string                 m_frag_name;

    std::set<std::string>       m_uniforms;
    std::map<std::string, Loc>  m_locations;
    std::map<std::string, Def>  m_definitions;
    GLuint                      m_texture_unit = GL_TEXTURE0;
    GLuint                      m_program_id   = 0;

    std::string parse_shader_include ( const std::string &, const std::string & );
    std::string parse_shader_source  ( std::string root, std::stringstream source );

    static GLuint compileShader ( std::string name, std::string &src, GLenum type );
    GLuint        compile_vf    ( const std::string &defines );
    GLuint        compile_vgf   ( const std::string &defines );

    void          _link_validate();

    void          _attach_shader( idk::glShaderStage first );

    template <typename ...Args>
    void          _attach_shader( idk::glShaderStage first, Args ...rest );


    void          reset();

    int m_refcount = 0;

public:
            glShaderProgram() {  };

    template <typename ...Args>
    glShaderProgram( idk::glShaderStage first, Args... rest )
    {
        m_refcount += 1;

        m_program_id = gl::createProgram();
        _attach_shader(first, rest...);
        _link_validate();
    }



    GLuint      ID() const { return m_program_id; };


    void        loadFile  ( std::string root, std::string vert, std::string frag );
    GLuint      loadFileC ( std::string root, std::string vert, std::string frag );

    void        loadFile_vgf  ( std::string root, std::string vert, std::string geom, std::string frag );
    GLuint      loadFileC_vgf ( std::string root, std::string vert, std::string geom, std::string frag );

    void        loadString  ( const std::string &vert, const std::string &frag );
    GLuint      loadStringC ( const std::string &vert, const std::string &frag );


    bool        setDefinition( std::string name, std::string value );
    auto &      getDefinitions() { return m_definitions; };

    GLuint      compile();
    void        bind();
    static void unbind();

    void        dispatch( GLuint size );
    void        dispatch( GLuint x, GLuint y, GLuint z );

    void        popTextureUnits() { m_texture_unit = GL_TEXTURE0; };


    GLint       uniformLoc    ( const std::string &name );

    void        set_int             ( const std::string &, int       );
    void        set_float           ( const std::string &, float     );

    void        set_ivec2           ( const std::string &, const glm::ivec2 & );
    void        set_ivec3           ( const std::string &, const glm::ivec3 & );

    void        set_vec2            ( const std::string &, glm::vec2 );
    void        set_vec3            ( const std::string &, glm::vec3 );
    void        set_vec4            ( const std::string &, glm::vec4 );
    void        set_mat3            ( const std::string &, glm::mat3 );
    void        set_mat4            ( const std::string &, glm::mat4 );
    void        set_mat4            ( const std::string &, size_t n, glm::mat4 * );
    void        set_mat4Array       ( const std::string &, glm::mat4 *, size_t );
    void        set_sampler2D       ( const std::string &, GLuint    );
    void        set_sampler2DArray  ( const std::string &, GLuint    );
    void        set_sampler3D       ( const std::string &, GLuint    );
    void        set_samplerCube     ( const std::string &, GLuint    );

    void        set_Handleui64ARB   ( const std::string &, GLuint64  );

};



template <typename ...Args>
void
idk::glShaderProgram::_attach_shader( idk::glShaderStage first, Args ...rest )
{
    gl::attachShader(m_program_id, first.m_shader_id);
    _attach_shader(rest...);
}
