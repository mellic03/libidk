#include "idk_utility.hpp"

int
idk::roundup( int n, int multipleof )
{
    if (n % multipleof == 0)
        return n;
    return n + (multipleof - (n % multipleof));
};

#define SQ(a) ((a)*(a))
float
idk::distanceSq( glm::vec3 a, glm::vec3 b )
{
    return SQ(a.x-b.x) + SQ(a.y-b.y) + SQ(a.z-b.z);
}
#undef SQ



void
idk::print( std::string sep )
{
    std::cout << "\n";
}




glm::vec3
idk::calculate_barycentric( float x, float y, glm::vec2 v1, glm::vec2 v2, glm::vec2 v3 )
{
    float denom = (v2.y-v3.y)*(v1.x-v3.x) + (v3.x-v2.x)*(v1.y-v3.y);

    glm::vec3 weights;
    weights.x = ((v2.y-v3.y)*(x-v3.x) + (v3.x-v2.x)*(y-v3.y)) / denom;
    weights.y = ((v3.y-v1.y)*(x-v3.x) + (v1.x-v3.x)*(y-v3.y)) / denom;
    weights.z = 1 - weights.x - weights.y;

    return weights;
}
