#pragma once

#include "common.hpp"
#include "idk_glBindings.hpp"

namespace idk { class glShader; };



class idk::glShader
{
public:
    struct Loc { GLint value = -1; };
    struct Def { std::string value = "NONE"; };

private:
    static GLuint current_bound_id;

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

    std::string parse_shader_include ( std::string root, std::string includeline  );
    std::string parse_shader_source  ( std::string root, std::stringstream source );

    static GLuint compileShader ( std::string name, std::string &src, GLenum type );
    GLuint        compile_vf    ( const std::string &defines );
    GLuint        compile_vgf   ( const std::string &defines );

    void        reset();

public:

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
    void        popTextureUnits() { m_texture_unit = GL_TEXTURE0; };


    GLint       uniformLoc    ( const std::string &name );

    void        set_int             ( const std::string &, int       );
    void        set_float           ( const std::string &, float     );
    void        set_vec2            ( const std::string &, glm::vec2 );
    void        set_vec3            ( const std::string &, glm::vec3 );
    void        set_vec4            ( const std::string &, glm::vec4 );
    void        set_mat3            ( const std::string &, glm::mat3 );
    void        set_mat4            ( const std::string &, glm::mat4 );
    void        set_mat4Array       ( const std::string &, glm::mat4 *, size_t );
    void        set_sampler2D       ( const std::string &, GLuint    );
    void        set_sampler2DArray  ( const std::string &, GLuint    );
    void        set_sampler3D       ( const std::string &, GLuint    );
    void        set_samplerCube     ( const std::string &, GLuint    );
};

