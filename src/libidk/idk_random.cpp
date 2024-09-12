#include "idk_random.hpp"



float idk::randf()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}


float idk::randf( float min, float max )
{
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(max-min)));
}


float idk::randf_guassian( float scale, int n )
{
    // 1.0   --> 1.0
    // 1.5   --> 1.0 + 0.5
    // 1.75  --> 1.0 + 0.5 + 0.25
    // 1.875 --> 1.0 + 0.5 + 0.25 + 0.125

    float result  = 0.0f;
    float width   = scale;
    float maximum = 0.0f;


    for (int i=1; i<=n; i++)
    {
        result  += width * randf(-1.0f, +1.0f);
        maximum += width;
        width   /= 2.0f;
    }

    return scale * (result / maximum);
}


glm::vec2 idk::randvec2( float min, float max )
{
    return glm::vec2(idk::randf(min, max), idk::randf(min, max));
}


glm::vec3 idk::randvec3( float min, float max )
{
    return glm::vec3(idk::randf(min, max), idk::randf(min, max), idk::randf(min, max));
}
