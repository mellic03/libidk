#pragma once

#include "./idk_glm.hpp"


namespace idk
{
    struct Transform
    {
        glm::vec3 position = glm::vec3(0.0001f);
        glm::quat rotation = glm::quat(glm::vec3(0.0f));
        glm::vec4 scale    = glm::vec4(1.0f);

        static glm::mat4 toGLM   ( const Transform&);
        static glm::mat4 toGLM   ( const Transform&, float pitch, float roll, float yaw );

        static glm::mat4 toGLM_noscale ( const Transform& );
        static glm::mat4 toGLM_noscale ( const Transform&, float pitch, float roll, float yaw );

        static Transform fromGLM ( const glm::mat4&, float s = 1.0f );

        static Transform mix( const Transform &A, const Transform &B, float alpha );
    };



    /** Translate by some vec3 */
    Transform operator  +  ( const Transform&, const glm::vec3& );
    Transform operator  -  ( const Transform&, const glm::vec3& );
    Transform &operator += ( Transform&, const glm::vec3& );
    Transform &operator -= ( Transform&, const glm::vec3& );

    Transform operator  +  ( const Transform&, const Transform& );
    Transform operator  -  ( const Transform&, const Transform& );
    Transform &operator += ( Transform&, const Transform& );
    Transform &operator -= ( Transform&, const Transform& );


    /** Equivalent to matrix multiplication */
    Transform operator * ( const Transform&, const Transform& );

};
