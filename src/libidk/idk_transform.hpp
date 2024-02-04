#pragma once

#include "GL/idk_glm.hpp"


namespace idk
{
    struct Transform
    {
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scale;
    };
};

