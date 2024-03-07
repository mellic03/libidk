#include "idk_geometry.hpp"

#include "idk_assert.hpp"




float
idk::geometry::distPlanePoint( const glm::vec3 &plane, const glm::vec3 &N, const glm::vec3 &point )
{
    glm::vec3 PS  = (point - plane);
    float     A   = length(PS);
    glm::vec3 dir = PS / A;

    float cosTheta   = glm::dot(N, dir);
    float theta      = glm::acos(glm::abs(cosTheta));
    float alpha      = (glm::pi<float>() / 2.0f) - theta;
    float dist       = A*glm::sin(alpha);
    float distSigned = glm::sign(cosTheta) * dist;

    return distSigned;
}


float
idk::geometry::distPlaneSphere( const glm::vec3 &plane, const glm::vec3 &N, const glm::vec3 &sphere, float r )
{
    float distCenter = distPlanePoint(plane, N, sphere);
    return distCenter - glm::sign(distCenter)*r;
}



idk::geometry::CameraFrustum
idk::geometry::createCameraFrustum( float near, float far, float vfov, float aspect,
                                    const glm::vec3 &position,
                                    const glm::vec3 &front,
                                    const glm::vec3 &up,
                                    const glm::vec3 &right )
{
    idk::geometry::CameraFrustum frustum;

    const float halfVSide = far * tanf(vfov * .5f);
    const float halfHSide = halfVSide * aspect;
    const glm::vec3 frontMultFar = far * front;


    frustum.positions[0]  = position + near*front;
    frustum.directions[0] = front;

    frustum.positions[1]  = position + far*front;
    frustum.directions[1] = -front;

    frustum.positions[2]  = position;
    frustum.directions[2] = glm::cross(far*front - halfHSide*right, up);

    frustum.positions[3]  = position;
    frustum.directions[3] = glm::cross(far*front + halfHSide*right, up);

    frustum.positions[4]  = position;
    frustum.directions[4] = glm::cross(far*front + halfVSide*up, right);

    frustum.positions[5]  = position;
    frustum.directions[5] = glm::cross(far*front - halfVSide*up, right);

    return frustum;
}



bool
idk::geometry::inFrustum( const CameraFrustum &frustum, const glm::mat4 &T, float radius )
{
    glm::vec3 position = glm::vec3(T[3]);
    float scale = glm::length(T[0]);

    if (scale != scale)
    {
        return false;
    }

    for (int i=0; i<6; i++)
    {
        float dist = distPlanePoint(
            frustum.positions[i],
            frustum.directions[i],
            position
        );

        if (dist < -scale*radius)
        {
            return false;
        }
    }

    return true;
}

