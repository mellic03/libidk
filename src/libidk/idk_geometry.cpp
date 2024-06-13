#include "idk_geometry.hpp"

#include "idk_assert.hpp"
#include "idk_log.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>



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


glm::vec3 nearestPointOnLineSegment(const glm::vec3& A, const glm::vec3& B, const glm::vec3& P)
{
    // Vector from A to B
    glm::vec3 AB = B - A;
    
    // Vector from A to P
    glm::vec3 AP = P - A;
    
    // Projection factor t of P onto the line AB (parametric position on the segment)
    float AB_dot_AB = glm::dot(AB, AB);
    float AB_dot_AP = glm::dot(AB, AP);
    float t = AB_dot_AP / AB_dot_AB;
    
    // Clamp t to the range [0, 1] to ensure the nearest point is within the segment
    t = glm::clamp(t, 0.0f, 1.0f);
    
    // Calculate the nearest point using the clamped t value
    glm::vec3 nearestPoint = A + t * AB;
    
    return nearestPoint;
}


glm::vec3
idk::geometry::line_point_NearestPoint( const glm::vec3 &A, const glm::vec3 &B,
                                        const glm::vec3 &p )
{
    // glm::vec3 AB    = glm::normalize(B - A);
    // glm::vec3 Ap    = glm::normalize(p - A);
    // glm::vec3 ortho = glm::cross(Ap, AB);

    // glm::vec3 O = A; // Origin of plane
    // glm::vec3 N = glm::cross(AB, ortho); // Normal of plane

    // float dist = idk::geometry::distPlanePoint(O, N, p);

    // glm::vec3 nearest = p + dist*(-N);

    // glm::vec3 An = glm::normalize(nearest - A);
    // glm::vec3 Bn = glm::normalize(nearest - B);


    // // Behind A, instead of between A and B.
    // if (glm::dot(AB, An) < 0.0f)
    // {
    //     nearest = A;
    // }

    // // Behind B, instead of between B and A.
    // else if (glm::dot(-AB, Bn) < 0.0f)
    // {
    //     nearest = B;
    // }

    // else
    // {
    // }

    // return nearest;
    return glm::vec3(0.0f);
}



glm::mat4 extractRotation( const glm::mat4 &M )
{
    glm::vec3 r_scale;
    glm::quat r_rot;
    glm::vec3 r_trans;
    glm::vec3 r_skew;
    glm::vec4 r_persp;
    glm::decompose(M, r_scale, r_rot, r_trans, r_skew, r_persp);
    return glm::mat4_cast(r_rot);
}


glm::mat4 extractScale( const glm::mat4 &M )
{
    glm::vec3 r_scale;
    glm::quat r_rot;
    glm::vec3 r_trans;
    glm::vec3 r_skew;
    glm::vec4 r_persp;
    glm::decompose(M, r_scale, r_rot, r_trans, r_skew, r_persp);
    return glm::scale(glm::mat4(1.0f), r_scale);
}


bool
idk::geometry::capsuleRectIntersection( const glm::vec3 &c_pos,
                                        float c_bot, float c_top, float c_rad,
                                        const glm::mat4 &rect, glm::vec3 &res )
{
    glm::vec3 top    = c_pos + glm::vec3(0.001f, c_top, 0.0f);
    glm::vec3 mid    = c_pos;
    glm::vec3 bottom = c_pos - glm::vec3(0.0f,   c_bot, 0.0f);

    glm::vec3 rect_pos = glm::vec3(rect[3]);
    glm::vec3 c_nearest = nearestPointOnLineSegment(bottom, top, rect_pos);


    res = glm::vec3(0.0f);
    glm::vec3 result = glm::vec3(0.0f);
    int count = 0;

    if (sphereRectIntersection(top, c_rad, rect, res))
    {
        res += result;
        count += 1;
    }

    if (sphereRectIntersection(mid, c_rad, rect, res))
    {
        res += result;
        count += 1;
    }

    if (sphereRectIntersection(bottom, c_rad, rect, result))
    {
        res += result;
        count += 1;
    }

    if (sphereRectIntersection(c_nearest, c_rad, rect, res))
    {
        res += result;
        count += 1;
    }

    if (count > 0)
    {
        res /= count;
    }

    return count > 0;
}



bool
idk::geometry::sphereRectIntersection( glm::vec3 s_pos, float s_radius, const glm::mat4 &rect,
                                       glm::vec3 &res )
{
    glm::vec3 r_scale;
    glm::quat r_rot;
    glm::vec3 r_trans;
    glm::vec3 r_skew;
    glm::vec4 r_persp;
    glm::decompose(rect, r_scale, r_rot, r_trans, r_skew, r_persp);
    glm::mat3 R = glm::mat3(glm::mat4_cast(r_rot));


    glm::vec3 local_pos = glm::inverse(R) * (s_pos - r_trans);
    glm::vec3 rect_min  = r_scale * glm::vec3(-0.5f);
    glm::vec3 rect_max  = r_scale * glm::vec3(+0.5f);

    glm::vec3 local_collision = glm::clamp(local_pos, rect_min, rect_max);
    glm::vec3 world_collision = (R * local_collision) + r_trans;

    float dist = glm::distance(s_pos, world_collision);

    if (dist <= s_radius)
    {
        glm::vec3 dir  = glm::normalize(world_collision - s_pos);
        glm::vec3 edge = s_pos + s_radius*dir;

        res = world_collision - edge;

        return true;
    }

    return false;
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

