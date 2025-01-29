#include "idk_glm.hpp"


glm::mat4
translate( const glm::vec3 &v )
{
    return glm::translate(glm::mat4(1.0f), v);
}


