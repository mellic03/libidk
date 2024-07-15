#pragma once

#include "GL/idk_glm.hpp"


namespace idk
{
    struct Transform
    {
        glm::vec3 position = glm::vec3(0.0001f);
        glm::quat rotation = glm::quat(glm::vec3(0.0f));
        glm::vec4 scale    = glm::vec4(1.0f);

        static glm::mat4 toGLM   ( const Transform& );
        static glm::mat4 toGLM   ( const Transform&, float pitch, float roll, float yaw );
        static Transform fromGLM ( const glm::mat4& );
    };

};

