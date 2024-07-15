#include "idk_transform.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>



glm::mat4
idk::Transform::toGLM( const Transform &t )
{
    static constexpr glm::mat4 I = glm::mat4(1.0f);

    glm::mat4 T = glm::translate(I, t.position);
    glm::mat4 R = glm::mat4_cast(t.rotation);
    glm::mat4 S = glm::scale(I, t.scale.w * glm::vec3(t.scale));

    return T * R * S;
}


glm::mat4
idk::Transform::toGLM( const Transform &t, float pitch, float roll, float yaw )
{
    static constexpr glm::mat4 I = glm::mat4(1.0f);

    glm::mat4 Rroll  = glm::mat4_cast(glm::angleAxis(roll,  glm::vec3(0.0f, 0.0f, -1.0f)));
    glm::mat4 Rpitch = glm::mat4_cast(glm::angleAxis(pitch, glm::vec3(1.0f, 0.0f, 0.0f)));
    glm::mat4 Ryaw   = glm::mat4_cast(glm::angleAxis(yaw,   glm::vec3(0.0f, 1.0f, 0.0f)));

    glm::mat4 T = glm::translate(I, t.position);
    glm::mat4 R = glm::mat4_cast(t.rotation) * Ryaw * Rroll * Rpitch;
    glm::mat4 S = glm::scale(I, t.scale.w * glm::vec3(t.scale));

    return T * R * S;
}



idk::Transform
idk::Transform::fromGLM( const glm::mat4 &T )
{
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 position;
    glm::vec3 skew;
    glm::vec4 persp;
    glm::decompose(T, scale, rotation, position, skew, persp);

    idk::Transform t = {
        .position = position,
        .rotation = rotation,
        .scale    = glm::vec4(scale, 1.0f)
    };

    if (t.position == glm::vec3(0.0f))
    {
        t.position += glm::vec3(0.00001f);
    }

    return t;
}
