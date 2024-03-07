#pragma once

#include <cmath>


namespace idk
{
    // Generate a pseudo-random float between 0.0 and 1.0 inclusive.
    float randf()
    {
        return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }

    // Generate a pseudo-random float between min and max inclusive.
    float randf( float min, float max )
    {
        return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(max-min)));
    }
};

