#pragma once

#include <cmath>
#include <glm/glm.hpp>


namespace idk
{
    // Generate a pseudo-random float between 0.0 and 1.0 inclusive.
    float randf();

    // Generate a pseudo-random float between min and max inclusive.
    float randf( float min, float max );

    float randf_guassian( float scale, int n );

    glm::vec2 randvec2( float min, float max );
    glm::vec3 randvec3( float min, float max );

};

