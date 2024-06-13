#pragma once

#include "GL/idk_glm.hpp"


namespace idk
{
    struct Transform
    {
        glm::vec3 position = glm::vec3(0.0f);
        glm::quat rotation = glm::quat(glm::vec3(0.0f));
        glm::vec4 scale    = glm::vec4(1.0f);
    };
};

